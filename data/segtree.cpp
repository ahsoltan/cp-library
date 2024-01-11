struct segtree {
  struct node {

  };

  int n;
  vector<node> t;

  segtree(int _n) {
    n = _n;
    t.resize(2 * n - 1);
  }

  node join(const node& a, const node& b) {

  }

  void push(int u, int len) {
    
  }

  template<typename F>
  void rec(int u, int lo, int hi, int l, int r, bool mod, F&& f) {
    if (l <= lo && hi <= r) {
      f(u, hi - lo);
      return;
    }
    push(u, hi - lo);
    int mid = (lo + hi) / 2;
    if (mid > l) {
      rec(u + 1, lo, mid, l, r, mod, f);
    }
    if (mid < r) {
      rec(u + (mid - lo) * 2, mid, hi, l, r, mod, f);
    }
    if (mod) {
      t[u] = join(t[u + 1], t[u + (mid - lo) * 2]);
    }
  }

  node get(int l, int r) {
    bool in = false;
    node res;
    rec(0, 0, n, l, r, false, [&] (int u, int) {
      res = in ? join(res, t[u]) : t[u];
      in = true;
    });
    return res;
  }

  void modify(int l, int r) {
    rec(0, 0, n, l, r, true, [&] (int u, int len) {

    });
  }
};
