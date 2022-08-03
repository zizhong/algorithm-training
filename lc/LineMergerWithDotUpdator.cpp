// https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/
struct LineMerger {
public:
    vector<int> e;
    int max_len = 0;
    LineMerger(int n) :  e(n, -1) {
    }
    void remove(int x) {
        if (e[x] == -1) return;
        int te = e[x];
        e[x] = e[te] = -1;
    }
    void add(int x) {
        int ts = x;
        int te = x;
        if (x - 1 >= 0 && e[x-1] != -1) {
            int a = x - 1;
            int b = e[x-1];
            if (a > b) swap(a, b);
            ts = min(a, ts);
            te = max(b, te);
            remove(x-1);
        }
        if (x + 1 < e.size() && e[x+1] != -1) {
            int a = x + 1;
            int b = e[x+1];
            if (a > b) swap(a, b);
            ts = min(a, ts);
            te = max(b, te);
            remove(x+1);
        }
        e[ts] = te;
        e[te] = ts;
        //cout << "add " << x << " " << ts << " " << te << endl;
        max_len = max(max_len, te - ts + 1);
    }
};
class Solution {
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        int n = nums.size();
        LineMerger lm(n);
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return nums[a] > nums[b];
        });
        for(auto x : idx) {
            lm.add(x);
            if (nums[x] > threshold/lm.max_len) return lm.max_len;
        }
        return -1;
    }
};
