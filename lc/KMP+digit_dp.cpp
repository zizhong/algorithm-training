//  https://leetcode.com/problems/find-all-good-strings/
const int mmod = 1e9 + 7;
void add_mmod(int &v, int a) {
  v = (v + 0LL + a) % mmod;
}
vector<int> get_kmp_next(string &s) {
  int len = s.size();
  vector<int> nxt(len, -1);
  int j = -1;
  for (int i = 1; i < len; i++) {
    while (j >= 0 && s[j + 1] != s[i]) j = nxt[j];
    if (s[j + 1] == s[i]) j++;
    nxt[i] = j;
  }
  return nxt;
}
int f[512][50][2];
class Solution {
 public:
  string evil;
  string s;
  int n;
  int ne;
  vector<int> kmp_nxt;
  // next[i][j] is for current length i, the next char j,
  // the length of the longest suffix match a prefix
  vector<vector<int>> next;
  void get_next() {
    ne = evil.size();
    next = vector<vector<int>>(ne + 1, vector<int>(26));
    kmp_nxt = get_kmp_next(evil);
    for (int i = 0; i < ne; i++) {
      for (int c = 0; c < 26; c++) {
        int j = i - 1;
        while (j >= 0 && evil[j + 1] != c + 'a') j = kmp_nxt[j];
        if (evil[j + 1] == c + 'a') j++;
        next[i][c] = j + 1;
      }
    }
  }
  int dfs(int idx, int mlen, int is_end) {
    if (idx == n) return 1;
    if (f[idx][mlen][is_end] != -1) return f[idx][mlen][is_end];
    int &ret = f[idx][mlen][is_end];
    ret = 0;
    int max_e = is_end > 0 ? (s[idx] - 'a') : 25;
    for (int i = 0; i <= max_e; i++) {
      if (next[mlen][i] == ne) continue;
      add_mmod(ret, dfs(idx + 1, next[mlen][i], is_end && (i == max_e)));
    }
    return ret;
  }
  int dp(string &s) {
    this->s = s;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < ne; j++) {
        for (int k = 0; k < 2; k++) {
          f[i][j][k] = -1;
        }
      }
    }
    return dfs(0, 0, 1);
  }
  int findGoodStrings(int n, string s1, string s2, string evil) {
    this->n = n;
    this->evil = evil;
    get_next();
    int j = -1;
    bool match = false;
    for (int i = 0; i < s1.size(); i++) {
      while (j >= 0 && evil[j + 1] != s1[i]) j = kmp_nxt[j];
      if (evil[j + 1] == s1[i]) j++;
      if (j + 1 == ne) {
        match = true;
        break;
      }
    }
    return (dp(s2) - dp(s1) + (match ? 0 : 1) + mmod) % mmod;
  }
};
