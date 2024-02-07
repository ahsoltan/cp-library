mt19937_64 rng(2137);

struct treap {
  struct node {
    int val, sz;
    uint64_t pr;
    int l = -1, r = -1;
  };

  vector<node> t;

  int make(int val) {
    int a = ssize(t);
    node& x = t.emplace_back();
    x.val = val;
    x.pr = rng();
    pull(x);
    return a;
  }

  int size(int x) {
    return x != -1 ? t[x].sz : 0;
  }

  void pull(int x) {
    if (x != -1) {
      t[x].sz = 1 + size(t[x].l) + size(t[x].r);
    }
  }

  int merge(int x, int y) {
    if (x == -1 || y == -1) {
      return x != -1 ? x : y;
    }
    int a = -1;
    if (t[x].pr > t[y].pr) {
      t[x].r = merge(t[x].r, y);
      a = x;
    } else {
      t[y].l = merge(x, t[y].l);
      a = y;
    }
    pull(a);
    return a;
  }

  pair<int, int> split(int x, int k) {
    if (x == -1) {
      return {-1, -1};
    }
    auto a = pair(-1, -1);
    if (k <= size(t[x].l)) {
      auto [aa, bb] = split(t[x].l, k);
      t[x].l = bb;
      a = {aa, x};
    } else {
      auto [aa, bb] = split(t[x].r, k - size(t[x].l) - 1);
      t[x].r = aa;
      a = {x, bb};
    }
    pull(a.first);
    pull(a.second);
    return a;
  }
};
