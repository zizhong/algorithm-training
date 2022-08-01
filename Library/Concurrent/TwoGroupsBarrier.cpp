class TwoGroupsBarrier {
 private:
  mutex m_mutex;
  condition_variable m_cv;
  vector<int> m_cnt;
  vector<int> m_inuse;
  vector<int> m_need;
  bool ok() {
    return m_cnt[0] >= m_need[0] &&
        m_cnt[1] >= m_need[1];
  }
  bool no_pending() {
    return m_inuse[0] == 0 && m_inuse[1] == 0;
  }
 public:
  TwoGroupsBarrier(int need1, int need2) {
    m_cnt = {0, 0};
    m_inuse = {0, 0};
    m_need = {need1, need2};
  }
    
  void handle(int x) {
    unique_lock<mutex> lk(m_mutex);
    m_cv.wait(lk, [&] { return no_pending(); });
    m_cnt[x]++;
    m_cv.wait(lk, [&] { return ok() || m_inuse[x] > 0; });
    if (m_inuse[x] > 0) {
      m_inuse[x]--;
      m_cv.notify_all();
      return;
    }
    if (ok()) {
      m_inuse = m_need;
      m_cnt[0] -= m_need[0];
      m_cnt[1] -= m_need[1];
    }
    m_inuse[x]--;
    m_cv.notify_all();
  };
};
class H2O {
public:
    TwoGroupsBarrier tgb;
    H2O() : tgb(2, 1) {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        tgb.handle(0);
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen) {
        tgb.handle(1);
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
    }
};

void solve(int ncase) {
  H2O h2o;
  string t = "HHHHOOOHH";
  vector<thread> v;
  for (auto c: t) {
    if (c == 'H') v.push_back(thread(&H2O::hydrogen, &h2o));
    else v.push_back(thread(&H2O::oxygen, &h2o));
  }
  for (auto &th: v) {
    th.join();
  }
}
