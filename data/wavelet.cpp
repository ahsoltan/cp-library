vector<int> _b;

struct node {
  int lo, hi, s;
  node* lc = nullptr;
  node* rc = nullptr;

  node(int _lo, int _hi, auto st, auto ed) {
    lo = _lo;
    hi = _hi;
    if (lo + 1 == hi) {
      return;
    }
    int mid = (lo + hi) / 2;
    s = ssize(_b);
    _b.push_back(0);
    for (auto it = st; it != ed; it++) {
      _b.push_back(_b.back() + (*it < mid));
    }
    auto k = stable_partition(st, ed, [&] (int x) {
      return x < mid;
    });
    if (k != st) {
      lc = new node(lo, mid, st, k);
    }
    if (k != ed) {
      rc = new node(mid, hi, k, ed);
    }
  }

  int kth(int l, int r, int k) {
    if (lo + 1 == hi) {
      return lo;
    }
    int x = _b[s + l];
    int y = _b[s + r];
    if (k < y - x) {
      return lc->kth(x, y, k);
    }
    return rc->kth(l - x, r - y, k - (y - x));
  }

  int leq(int l, int r, int k) {
    if (k < lo || hi <= k) {
      return 0;
    }
    if (lo + 1 == hi) {
      return r - l;
    }
    int x = _b[s + l];
    int y = _b[s + r];
    int mid = (lo + hi) / 2;
    if (k < mid) {
      return (lc ? lc->leq(x, y, k) : 0);
    }
    return (y - x) + (rc ? rc->leq(l - x, r - y, k) : 0);
  }
};
