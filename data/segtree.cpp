struct segtree {
  struct node {
    
  };

  int n;
  vector<node> tree;

  segtree(int _n = 0) {
    n = 1;
    while (n < _n) {
      n *= 2;
    }
    tree.resize(2 * n);
  }

  node join(const node& a, const node& b) {
    
  }

  void push(int u, int len) {
    
  }

  template<typename F>
  void run(int u, int ul, int ur, int l, int r, bool mod, F&& f) {
    if (ul >= l && ur <= r) {
      f(u, ur - ul + 1);
      return;
    }
    if (ul > r || ur < l) {
      return;
    }
    push(u, ur - ul + 1);
    int mid = (ul + ur) / 2;
    run(2 * u, ul, mid, l, r, mod, f);
    run(2 * u + 1, mid + 1, ur, l, r, mod, f);
    if (mod) {
      tree[u] = join(tree[2 * u], tree[2 * u + 1]);
    }
  }

  node get(int l, int r) {
    node res;
    run(1, 0, n - 1, l, r, false, [&] (int u, int) {
      res = join(res, tree[u]);
    });
    return res;
  }

  void modify(int l, int r) {
    run(1, 0, n - 1, l, r, true, [&] (int u, int len) {
      
    });
  }
};