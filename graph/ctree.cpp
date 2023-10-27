struct ctree {
  int n;
  vector<vector<int>> adj;
  vector<int> sz, up;
  vector<bool> vis;

  ctree(int _n) {
    n = _n;
    adj.resize(n);
    sz.resize(n);
    up.resize(n, -1);
    vis.resize(n);
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int dfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
      if (!vis[v] && v != p) {
        dfs(v, u);
        sz[u] += sz[v];
      }
    }
  }
  
  int search(int u, int p, int s) {
    for (int v : adj[u]) {
      if (!vis[v] && v != p && sz[v] > s / 2) {
        return search(v, u, s);
      }
    }
    return u;
  }

  int build(int u = 0) {
    dfs(u, -1);
    int c = search(u, -1, sz[r]);
    vis[c] = true;
    for (int v : adj[c]) {
      if (!vis[v]) {
        up[build(v)] = c;
      }
    }
  }
};
