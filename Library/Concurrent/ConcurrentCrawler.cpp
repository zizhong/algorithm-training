class Solution {
public:
    mutex m;
    condition_variable cv;
    unordered_set<string> visited;
    queue<string> q;
    vector<thread> th;
    HtmlParser *htmlParser;
    string host_name;
    
    int n_running;
    bool done = false;
    vector<string> crawl(const string& startUrl, HtmlParser& htmlParser) {
        int thread_num = thread::hardware_concurrency();
        n_running = 0;
        done = false;
        if (thread_num == 0) thread_num = 16;
        this->htmlParser = &htmlParser;
        q.push(startUrl);
        host_name = parse_hostname(startUrl);
        for(int i = 0; i < thread_num; i++) {
            th.push_back(thread(&Solution::worker, this));
        }
        for(int i = 0; i < thread_num; i++) {
            th[i].join();
        }
        return vector<string>(visited.begin(), visited.end());
    }
    
    void worker() {
        while(!done) {
            string url;
            {
                unique_lock lk(m);
                if (q.empty() && n_running == 0) break;
                cv.wait(lk, [&]() {return q.size() > 0 || done;});
                if (done) return;
                url = q.front();
                q.pop();
                n_running++;
                visited.insert(url);
            }
            
            vector<string> v = htmlParser->getUrls(url);
            for(auto& u : v) {
                if (parse_hostname(u) == host_name) {
                    {
                        unique_lock lk(m);
                        if (visited.find(u) != visited.end()) continue;
                        visited.insert(u);
                        q.push(u);
                    }
                    cv.notify_all();
                }
            }
            worker_finish();
        }
    }
    void worker_finish() {
        unique_lock lk(m);
        n_running--;
        if (q.empty() && n_running == 0) {
            done = true;
            cv.notify_all();
        }
    }
    
    string parse_hostname(const string& url) {
        int idx = url.find("://");
        if (idx == -1) idx = 0;
        else idx += 3;
        int j = url.find('/', idx);
        if (j == -1) return url.substr(idx);
        return url.substr(idx, j - idx);
    }
};
