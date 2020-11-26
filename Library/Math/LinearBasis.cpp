struct LinearBasis {
  static const int MAXL = 60;
  long long a[MAXL + 1];

  LinearBasis() {
    std::fill(a, a + MAXL + 1, 0);
  }
  // return true if t is belongs to be the linear basis
  bool insert(long long t) {
    // 逆序枚举二进制位
    for (int j = MAXL; j >= 0; j--) {
      // 如果 t 的第 j 位为 0，则跳过
      if (!(t & (1ll << j))) continue;
      // 如果 a[j] != 0，则用 a[j] 消去 t 的第 j 位上的 1
      if (a[j]) t ^= a[j];
      else {
        // 找到可以插入 a[j] 的位置

        // 用 a[0...j - 1] 消去 t 的第 [0, j) 位上的 1
        // 如果某一个 a[k] = 0 也无须担心，因为这时候第 k 位不存在于线性基中，不需要保证 t 的第 k 位为 0
        for (int k = 0; k < j; k++) if (t & (1ll << k)) t ^= a[k];
        // 用 t 消去 a[j + 1...L] 的第 j 位上的 1
        for (int k = j + 1; k <= MAXL; k++) if (a[k] & (1ll << j)) a[k] ^= t;
        // 插入到 a[j] 的位置上
        a[j] = t;
        // 不要忘记，结束插入过程
        return true;
      }
      // 此时 t 的第 j 位为 0，继续寻找其最高位上的 1
    }
    // 如果没有插入到任何一个位置上，则表明 t 可以由 a 中若干个元素的异或和表示出，即 t 在 span(a) 中
    return false;
  }
};
