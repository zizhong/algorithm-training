//https://leetcode.com/submissions/detail/770005149/
class Solution {
public:
    bool isMatch(string s, string p) {
        int ns = s.size();
        int np = p.size();
        vector<vector<bool>> match(ns + 1, vector<bool>(np + 1, false));
        match[0][0] = true;
        for(int i = 0; i <= ns; i++) {
            for(int j = 0; j < np; j++) {
                if (!match[i][j]) continue;
                
                // * match zero
                if (j + 1 < np && p[j+1] == '*') {
                    match[i][j+2] = true;
                }
                
                // match one char forward
                if (i < ns && (s[i] == p[j] || p[j] == '.')) {
                    match[i+1][j+1] = true;
                }
                
                if (p[j] != '*') continue;
                // * match more
                for(int k = max(i-1, 0); k < ns; k++) {
                    if (s[k] == p[j-1] || p[j-1] == '.') {
                        match[k+1][j+1] = true;
                    } else {
                        break;
                    }
                }
            }
        }
        return match[ns][np];
    }
};
