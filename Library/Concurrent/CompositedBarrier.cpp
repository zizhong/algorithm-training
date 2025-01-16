/*
*
1. ++wait on enter and --pending on exit
  a) As to_pending will move wait to pending
2. Call the callback while holding lock
3. The wait logic is that only if
  a) Currently this index is pending
  b) OR there is no pending and there is a group ready
*/
struct CompositeBarrier {
    vector<int> need;
    vector<int> pending;
    vector<int> wait;
    mutex m;
    condition_variable cv;
    CompositeBarrier(const vector<int>& need_) : need(need_) {
        pending.resize(need.size());
        wait.resize(need.size());
    };
    bool ready() {
        for (int j = 0; j < need.size(); j++) {
            if (need[j] > wait[j])
                return false;
        }
        return true;
    }

    void to_pending() {
        for (int j = 0; j < need.size(); j++) {
            pending[j] += need[j];
            wait[j] -= need[j];
        }
    }
    bool no_pending() {
        for (auto x : pending)
            if (x)
                return false;
        return true;
    }
    void handle(int i, function<void()> callback) {
        {
            unique_lock<mutex> lk(m);
            wait[i]++;
            cv.wait(lk,
                    [&]() { return pending[i] > 0 || no_pending() && ready(); });
            if (pending[i] == 0) {
                to_pending();
            }
            pending[i]--;
           callback();
        }
        cv.notify_all();
    }
};

class H2O {
    CompositeBarrier cb;

public:
    H2O() : cb(CompositeBarrier({2, 1})) {}

    void hydrogen(function<void()> releaseHydrogen) {
        cb.handle(0, releaseHydrogen);
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        // releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen) {
        cb.handle(1, releaseOxygen);
        // releaseOxygen() outputs "O". Do not change or remove this line.
        // releaseOxygen();
    }
};
