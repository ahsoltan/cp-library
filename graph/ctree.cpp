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
 
  void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
      if (!vis[v] && v != p) {
        dfs(v, u);
        sz[u] += sz[v];
      }
    }
  }
  
  int build(int u = 0) {
    dfs(u, -1);
    int c = u;
    bool ok = false;
    while (!ok) {
      ok = true;
      for (int v : adj[c]) {
        if (!vis[v] && sz[v] < sz[c] && sz[v] > sz[u] / 2) {
          c = v;
          ok = false;
          break;
        }
      }
    }
    vis[c] = true;
    for (int v : adj[c]) {
      if (!vis[v]) {
        up[build(v)] = c;
      }
    }
    return c;
  }
};
