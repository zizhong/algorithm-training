void calc_kmp_next(const char *s, int len, vector<int> &next) {
  next.assign(len, -1);
  int j = -1;
  for (int i = 1; i < len; i++) {
    while (j >= 0 && s[i] != s[j + 1]) j = next[j];
    if (s[i] == s[j + 1]) j++;
    next[i] = j;
  }
}
