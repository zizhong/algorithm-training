// You are given a string s. You can convert s to a palindrome by adding characters in front of it.
// Return the shortest palindrome you can find by performing this transformation.

const int N = 1e5 +10;
int nxt[N];
void calc_kmp_next(string& t) {
    int n = t.size();
    int j = -1;
    nxt[0] = j;
    for(int i = 1; i < n; i++) {
        while(j >= 0 && t[j+1] != t[i]) j = nxt[j];
        if (t[j+1] == t[i]) j++;
        nxt[i] = j;
    }
}
class Solution {
public:
    string shortestPalindrome(string& s) {
        int n = s.size();
        if (n <= 1) return s; 
        
        string t(2 * n + 1, ' ');
        for(int i = 0; i < 2 * n + 1; i++) {
            if (i < n) t[i] = s[i];
            else if (i == n) t[i] = '*';
            else t[i] = s[n + n - i];
        }
        calc_kmp_next(t);
        int l = nxt[(int)t.size() - 1];
        string r;
        for(int i = l + 1; i < s.size(); i++) r.push_back(s[(int)s.size() + l - i]);
        return r + s;
    }
};
