struct node {
  int lo, hi;
  node* l = nullptr;
  node* r = nullptr;
  vector<int> b;

  node(const vector<int>& v, int _lo, int _hi) {
    lo = _lo;
    hi = _hi;
    if (lo == hi) {
      return;
    }
    int n = ssize(v);
    b.resize(n + 1);
    vector<int> vl, vr;
    int mid = (lo + hi) / 2;
    for (int i = 0; i < n; i++) {
      b[i + 1] = b[i];
      if (v[i] <= mid) {
        vl.push_back(v[i]);
        b[i + 1]++;
      } else {
        vr.push_back(v[i]);
      }
    }
    if (!vl.empty()) {
      l = new node(vl, lo, mid);
    }
    if (!vr.empty()) {
      r = new node(vr, mid + 1, hi);
    }
  }

  int kth(int ql, int qr, int k) {
    if (lo == hi) {
      return lo;
    }
    int c = b[qr + 1] - b[ql];
    if (k < c) {
      return l->kth(b[ql], b[qr + 1] - 1, k);
    }
    return r->kth(ql - b[ql], qr - b[qr + 1], k - c);
  }

  int count(int ql, int qr, int k) {
    if (ql > qr) {
      return 0;
    }
    if (lo == hi) {
      return qr - ql + 1;
    }
    int mid = (lo + hi) / 2;
    if (k <= mid) {
      return l ? l->count(b[ql], b[qr + 1] - 1, k) : 0;
    }
    return r ? r->count(ql - b[ql], qr - b[qr + 1], k) : 0;
  }

  int leq(int ql, int qr, int k) {
    if (lo > k) {
      return 0;
    }
    if (hi <= k) {
      return qr - ql + 1;
    }
    int mid = (lo + hi) / 2;
    if (k <= mid) {
      return l ? l->leq(b[ql], b[qr + 1] - 1, k) : 0;
    }
    return b.back() + (r ? r->leq(ql - b[ql], qr - b[qr + 1], k) : 0);
  }
};
