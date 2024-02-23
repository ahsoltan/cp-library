struct HLD {
  int n;
  vector<vector<int>> adj;
  vector<int> d, p, sz;
  vector<int> t, h, in, out;

  HLD(int _n) {
    n = _n;
    adj.resize(n);
    d.resize(n);
    p.resize(n, -1);
    sz.resize(n);
    t.reserve(n);
    h.resize(n);
    in.resize(n);
    out.resize(n);
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs1(int u) {
    sz[u] = 1;
    for (int& v : adj[u]) {
      adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
      p[v] = u;
      d[v] = d[u] + 1;
      dfs1(v);
      sz[u] += sz[v];
      if (sz[v] > sz[adj[u][0]]) {
        swap(adj[u][0], v);
      }
    }
  }

  void dfs2(int u, bool b) {
    in[u] = ssize(t);
    t.push_back(u);
    h[u] = b ? h[p[u]] : u;
    b = true;
    for (int v : adj[u]) {
      dfs2(v, b);
      b = false;
    }
    out[u] = ssize(t);
  }

  void build(int u = 0) {
    dfs1(u);
    dfs2(u, false);
  }
  
  int lca(int u, int v) {
    while (h[u] != h[v]) {
      if (d[h[u]] > d[h[v]]) {
        swap(u, v);
      }
      v = p[h[v]];
    }
    return d[u] < d[v] ? u : v;
  }

  int kth(int u, int k) {
    if (d[u] < k) {
      return -1;
    }
    int x = d[u] - k;
    while (d[h[u]] > x) {
      u = p[h[u]];
    }
    return t[in[h[u]] + x - d[h[u]]];
  }

  int kth(int u, int v, int k) {
    int w = lca(u, v);
    int du = d[u] - d[w];
    int dv = d[v] - d[w];
    if (k > du + dv) {
      return -1;
    }
    return k <= du ? kth(u, k) : kth(v, du + dv - k);
  }

  int dist(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
  }

  bool anc(int u, int v) {
    return in[u] <= in[v] && in[v] < out[u];
  }
};
