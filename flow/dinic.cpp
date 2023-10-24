template<typename F>
struct dinic {
  struct edge {
    int to, rev;
    F cap;
  };

  int n;
  vector<vector<edge>> adj;
  vector<int> lvl, it;

  dinic(int _n) {
    n = _n;
    adj.resize(n);
    lvl.resize(n);
    it.resize(n);
  }

  void add_edge(int u, int v, F cap) {
    int i = ssize(adj[u]);
    int j = ssize(adj[v]);
    if (u == v) {
      j++;
    }
    adj[u].push_back({v, j, cap});
    adj[v].push_back({u, i, 0});
  }

  bool bfs(int s, int t) {
    lvl.assign(n, -1);
    queue<int> q;
    lvl[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (edge& e : adj[u]) {
        if (e.cap > 0 && lvl[e.to] == -1) {
          lvl[e.to] = lvl[u] + 1;
          q.push(e.to);
          if (e.to == t) {
            return true;
          }
        }
      }
    }
    return false;
  }

  F dfs(int u, int t, F cap) {
    if (u == t) {
      return cap;
    }
    F flow = 0;
    for (int& i = it[u]; i < ssize(adj[u]); i++) {
      edge& e = adj[u][i];
      if (e.cap > 0 && lvl[u] + 1 == lvl[e.to]) {
        F add = dfs(e.to, t, min(cap - flow, e.cap));
        e.cap -= add;
        adj[e.to][e.rev].cap += add;
        flow += add;
      }
      if (flow == cap) {
        return flow;
      }
    }
    lvl[u] = -1;
    return flow;
  }

  F build(int s, int t, F cap) {
    F flow = 0;
    while (flow < cap && bfs(s, t)) {
      it.assign(n, 0);
      flow += dfs(s, t, cap - flow);
    }
    return flow;
  }
};
