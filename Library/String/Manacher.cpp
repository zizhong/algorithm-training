class Solution {
 public:
  string longestPalindrome(string s) {
    string ns(2 * s.size() + 1, '|');
    for (int i = 0; i < s.size(); i++) ns[2 * i + 1] = s[i];
    swap(s, ns);
    // Manacher's algorithm
    // The key is to use the previous palindrome info to speed up the new palindrome finding process.
    vector<int> d(s.size());
    int l = -1, r = 0;
    for (int i = 0; i < s.size(); i++) {
      if (i < r) {
        d[i] = min(d[l + r - i], r - i);
      }
      while ((i + d[i] + 1) < s.size() && (i - (d[i] + 1)) >= 0 && s[i + d[i] + 1] == s[i - (d[i] + 1)]) d[i]++;
      if (r < d[i] + i) {
        l = i - d[i];
        r = i + d[i];
      }
    }
    // End 
    int idx = max_element(d.begin(), d.end()) - d.begin();
    l = idx - d[idx];
    r = idx + d[idx];
    string ret;
    for (int i = l; i <= r; i++) if (i % 2) ret.push_back(s[i]);
    return ret;
  }
};
