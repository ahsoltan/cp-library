struct dinic {
  struct edge {
    int to, rev;
    int cap;
  };

  int n;
  vector<vector<edge>> adj;
  vector<int> q, lvl, it;

  dinic(int _n) {
    n = _n;
    adj.resize(n);
    q.reserve(n);
    lvl.resize(n);
    it.resize(n);
  }

  void add_edge(int u, int v, int cap) {
    int i = ssize(adj[u]);
    int j = ssize(adj[v]) + (u == v);
    adj[u].push_back({v, j, cap});
    adj[v].push_back({u, i, 0});
  }

  bool bfs(int s, int t) {
    q.clear();
    lvl.assign(n, -1);
    lvl[s] = 0;
    q.push_back(s);
    for (int i = 0; i < ssize(q); i++) {
      int u = q[i];
      for (edge& e : adj[u]) {
        if (e.cap > 0 && lvl[e.to] == -1) {
          lvl[e.to] = lvl[u] + 1;
          q.push_back(e.to);
          if (e.to == t) {
            return true;
          }
        }
      }
    }
    return false;
  }

  ll dfs(int u, int t, ll cap) {
    if (u == t) {
      return cap;
    }
    ll f = 0;
    for (int& i = it[u]; i < ssize(adj[u]); i++) {
      edge& e = adj[u][i];
      if (e.cap > 0 && lvl[u] + 1 == lvl[e.to]) {
        ll add = dfs(e.to, t, min(cap - f, (ll)e.cap));
        e.cap -= add;
        adj[e.to][e.rev].cap += add;
        f += add;
      }
      if (f == cap) {
        return f;
      }
    }
    lvl[u] = -1;
    return f;
  }

  ll flow(int s, int t, ll cap) {
    ll f = 0;
    while (f < cap && bfs(s, t)) {
      it.assign(n, 0);
      f += dfs(s, t, cap - f);
    }
    return f;
  }
};
