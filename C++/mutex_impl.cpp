class Mutex {
public:
  void Lock() {
    uint32_t c = 0;

    if (!state_.compare_exchange_strong(c, 1)) {
      if (c != 2) {
        c = state_.exchange(2);
      }

      while (c != 0) {
        futex::Wait(state_, 2);
        c = state_.exchange(2);
      }
    }
  }

  void Unlock() {
    if (state_.fetch_sub(1) > 1) {
      state_.store(0);
      futex::WakeOne(state_);
    }
  }

private:
  // 0 - means unlocked.
  // 1 - means locked, no waiters.
  // 2 - means locker, there are waiters.
  std::atomic<uint32_t> state_{0};
};
