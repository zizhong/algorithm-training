struct Matrix {
  Matrix(int n = 27) {
    this->n = n;
    mat.assign(n, vector<ll>(n, 0));
    identity();
  }
  void clear() {
    mat.assign(n, vector<ll>(n, 0));
  }
  void identity() {
    for (int i = 0; i < n; i++) mat[i][i] = 1;
  }
  void signal_char(int c) {
    for (int i = 0; i < n; i++) mat[i][c] = 1;
  }
  Matrix operator+(const Matrix &rhs) const {
    Matrix ret;
    ret.clear();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        ret.mat[i][j] = (mat[i][j] +0LL+ rhs.mat[i][j]) % mod;
      }
    }
    return ret;
  }
  Matrix operator*(const Matrix &rhs) const {
    Matrix ret;
    ret.clear();

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          ret.mat[i][j] = (mat[i][k] *1LL* rhs.mat[k][j] + ret.mat[i][j]) % mod;
        }
      }
    }
    return ret;
  }

  Matrix operator^(ll y) const {
     Matrix ret;
     if (y == 0) return ret;
     ret.mat = this->mat;
     if (y == 1) return ret;
     Matrix ret1 = (*this)^(y/2);
     if (y &1) return ret1 * ret * ret1;
     return ret1 * ret1;
  }
  vector<vector<ll>> mat;
  
  void init_recurrence(vector<int>& c) {
    assert(n == c.size());
    clear();
    for(int i = 0; i < n - 1; i++) mat[i][i+1] = 1;
    for(int i = 0; i < n; i++) mat[n-1][i] = c[i];
  }
  int n;
};


void solve(int ncase) {
    int n , k;
    cin >> n >> k;

    Matrix mat(k);
    vector<int> c(k,1);
    mat.init_recurrence(c);
    Matrix ret = mat^n;
    //for(auto &v : ret.mat) {for(auto i : v) cout << i << " "; cout << endl;}
    cout << ret.mat[k-1][0] << endl;
}
