struct DSU {
  int n, cnt;
  vector<int> p;

  DSU(int _n) {
    n = _n;
    cnt = n;
    p.resize(n, -1);
  }

  int get(int x) {
    return p[x] < 0 ? x : p[x] = get(p[x]);
  }

  int size(int x) {
    return -p[get(x)];
  }

  bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) {
      return false;
    }
    if (-p[x] < -p[y]) {
      swap(x, y);
    }
    p[x] += p[y];
    p[y] = x;
    cnt--;
    return true;
  }

  vector<vector<int>> groups() {
    vector<vector<int>> res(cnt);
    for (int i = 0; i < n; i++) {
      res[get(i)].push_back(i);
    }
    return res;
  }
};