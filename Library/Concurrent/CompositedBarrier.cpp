
class CompositedBarrier {
 private:
  mutex m_mutex;
  condition_variable m_cv;
  vector<int> m_cnt;
  vector<int> m_inuse;
  vector<int> m_need;
  int m_group;
  bool enough() {
    for (int i = 0; i < m_group; i++) {
      if (m_cnt[i] < m_need[i]) return false;
    }
    return true;
  }
  bool in_pending() {
    for (int i = 0; i < m_group; i++) {
      if (m_inuse[i] > 0) return true;
    }
    return false;
  }
  void to_pending() {
    for (int i = 0; i < m_group; i++) {
      m_inuse[i] = m_need[i];
      m_cnt[i] -= m_need[i];
    }
  }
 public:
  CompositedBarrier(const vector<int> &need_) {
    m_need = need_;
    m_group = need_.size();
    m_cnt.assign(need_.size(), 0);
    m_inuse.assign(need_.size(), 0);
  }
  void handle(int x) {
    unique_lock<mutex> lk(m_mutex);
    m_cv.wait(lk, [&] { return !in_pending(); });
    m_cnt[x]++;
    m_cv.wait(lk, [&] { return enough() || m_inuse[x] > 0; });
    if (m_inuse[x] > 0) {
      m_inuse[x]--;
      m_cv.notify_all();
      return;
    }
    if (enough()) {
      to_pending();
    }
    m_inuse[x]--;
    m_cv.notify_all();
  };
};
class H2O {
public:
    CompositedBarrier cb;
    H2O() : cb({2, 1}) {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        cb.handle(0);
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen) {
        cb.handle(1);
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
    }
};
