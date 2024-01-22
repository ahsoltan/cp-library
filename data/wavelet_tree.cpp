struct wavelet_tree {
  int n;
  vector<vector<int>> b;
  vector<int> v;
  bool s;

  wavelet_tree(vector<int> _v, bool _s = true) {
    n = ssize(_v);
    v = _v;
    s = _s;
    sort(v.begin(), v.end());
    if (s) {
      for (int i = 0; i < n; i++) {
        _v[i] = lower_bound(v.begin(), v.end(), _v[i]) - v.begin();
      }
    }
    b.resize(max(0, 2 * n - 1));
    build(0, 0, n, _v.begin(), _v.end());
  }

  void build(int u, int lo, int hi, auto l, auto r) {
    if (lo + 1 == hi || l == r) {
      return;
    }
    int mid = (lo + hi) / 2;
    b[u].reserve(r - l + 1);
    b[u].push_back(0);
    for (auto it = l; it != r; it++) {
      b[u].push_back(b[u].back() + (*it < mid));
    }
    auto k = stable_partition(l, r, [&] (int x) {
      return x < mid;
    });
    build(u + 1, lo, mid, l, k);
    build(u + (mid - lo) * 2, mid, hi, k, r);
  }

  int kth(int l, int r, int k) {
    int u = 0;
    int lo = 0;
    int hi = n;
    while (lo + 1 < hi) {
      int x = b[u][l];
      int y = b[u][r];
      int mid = (lo + hi) / 2;
      if (k < y - x) {
        u += 1;
        hi = mid;
        l = x;
        r = y;
      } else {
        u += (mid - lo) * 2;
        lo = mid;
        l -= x;
        r -= y;
        k -= y - x;
      }
    }
    return v[lo];
  }

  int count(int l, int r, int k) {
    if (s) {
      k = lower_bound(v.begin(), v.end(), k) - v.begin();
    }
    int ans = 0;
    int u = 0;
    int lo = 0;
    int hi = n;
    while (lo + 1 <= hi && lo < k && l < r) {
      if (lo + 1 == hi) {
        ans += r - l;
        break;
      }
      int x = b[u][l];
      int y = b[u][r];
      int mid = (lo + hi) / 2;
      if (k < mid) {
        u += 1;
        hi = mid;
        l = x;
        r = y;
      } else {
        ans += y - x;
        u += (mid - lo) * 2;
        lo = mid;
        l -= x;
        r -= y;
      }
    }
    return ans;
  }

  int freq(int l, int r, int k) {
    if (s) {
      int x = lower_bound(v.begin(), v.end(), k) - v.begin();
      if (x == n || v[x] != k) {
        return 0;
      }
      k = x;
    }
    int u = 0;
    int lo = 0;
    int hi = n;
    while (lo + 1 < hi && l < r) {
      int x = b[u][l];
      int y = b[u][r];
      int mid = (lo + hi) / 2;
      if (k < mid) {
        u += 1;
        hi = mid;
        l = x;
        r = y;
      } else {
        u += (mid - lo) * 2;
        lo = mid;
        l -= x;
        r -= y;
      }
    }
    return r - l;
  }
};
