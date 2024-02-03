struct node {
  int lo, hi;
  vector<int> s;
  node* l = 0;
  node* r = 0;

  node(int _lo, int _hi, auto st, auto ed) {
    lo = _lo;
    hi = _hi;
    if (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      s.reserve(ed - st + 1);
      s.push_back(0);
      for (auto it = st; it != ed; it++) {
        s.push_back(s.back() + (*it < mid));
      }
      auto k = stable_partition(st, ed, [&] (int x) {
        return x < mid;
      });
      if (k != st) {
        l = new node(lo, mid, st, k);
      }
      if (k != ed) {
        r = new node(mid, hi, k, ed);
      }
    }
  }

  int kth(int a, int b, int k) {
    if (lo + 1 == hi) {
      return lo;
    }
    int x = s[a];
    int y = s[b];
    return k < y - x ? l->kth(x, y, k) : r->kth(a - x, b - y, k - (y - x));
  }

  int count(int a, int b, int k) {
    if (lo >= k) {
      return 0;
    }
    if (hi <= k) {
      return b - a;
    }
    int x = s[a];
    int y = s[b];
    return (l ? l->count(x, y, k) : 0) + (r ? r->count(a - x, b - y, k) : 0);
  }

  int freq(int a, int b, int k) {
    if (hi <= k || k < lo) {
      return 0;
    }
    if (lo + 1 == hi) {
      return b - a;
    }
    int mid = (lo + hi) / 2;
    int x = s[a];
    int y = s[b];
    return k < mid ? (l ? l->freq(x, y, k) : 0) : (r ? r->freq(a - x, b - y, k) : 0);
  }
};
