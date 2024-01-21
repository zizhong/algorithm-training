// https://leetcode.com/contest/weekly-contest-380/problems/find-beautiful-indices-in-the-given-array-ii/
void calc_kmp_next(const char *s, int len, vector<int> &next) {
  next.assign(len, -1);
  int j = -1;
  for (int i = 1; i < len; i++) {
    while (j >= 0 && s[i] != s[j + 1]) j = next[j];
    if (s[i] == s[j + 1]) j++;
    next[i] = j;
  }
}

vector<int> kmp_match(const string& s, const string& t) {
    vector<int> next;
    calc_kmp_next(t.c_str(), t.size(), next);
    int j = -1;
    vector<int> match(s.size());
    for(int i = 0; i < s.size(); i++) {
        while (j >= 0 && s[i] != t[j + 1]) j = next[j];
        if (s[i] == t[j + 1]) j++;
        if (j + 1 == t.size()) {
            match[i + 1 - t.size()] = 1;
            j = next[j];
        }
    }
    return match;
}

class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> va = kmp_match(s, a);
        vector<int> vb = kmp_match(s, b);
        //for(int i = 0; i < va.size(); i++) if (va[i]) cout << s.substr(i, a.size()) << endl;
        int n = s.size();
        const int INF = n + k + k;
        vector<int> rb(n, INF);
        for(int i= n - 1; i >= 0; i--) {
            if (i + 1 < n) rb[i] = rb[i+1];
            if (vb[i]) rb[i] = i;
        }
        vector<int> ret;
        int lb = -INF;
        for(int i = 0; i < s.size(); i++) {
            if (vb[i]) lb = i;
            if (va[i] && ((i - lb) <= k || (rb[i] - i) <= k)) {
                ret.push_back(i);
            }
        }
        return ret;
    }
};
