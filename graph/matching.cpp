struct matching {
  int n, m;
  vector<vector<int>> adj;
  vector<int> pb, pa;
  vector<int> lvl, it;

  matching(int _n, int _m) {
    n = _n;
    m = _m;
    adj.resize(n);
    pb.resize(n, -1);
    pa.resize(m, -1);
    it.resize(n);
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
  }

  bool bfs() {
    bool res = false;
    lvl.assign(n, -1);
    queue<int> q;
    for (int i = 0; i < n; i++) {
      if (pb[i] == -1) {
        q.push(i);
        lvl[i] = 0;
      }
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int j : adj[u]) {
        if (pa[j] == -1) {
          res = true;
        } else if (lvl[pa[j]] == -1) {
          lvl[pa[j]] = lvl[u] + 1;
          q.push(pa[j]);
        }
      }
    }
    return res;
  }

  bool dfs(int u) {
    for (auto& i = it[u]; i < ssize(adj[u]); i++) {
      int v = adj[u][i];
      if (pa[v] == -1 || (lvl[pa[v]] == lvl[u] + 1 && dfs(pa[v]))) {
        pb[u] = v;
        pa[v] = u;
        return true;
      }
    }
    return false;
  }

  int match() {
    int ans = 0;
    while (bfs()) {
      it.assign(n, 0);
      for (int i = 0; i < n; i++) {
        if (pb[i] == -1 && dfs(i)) {
          ans++;
        }
      }
    }
    return ans;
  }
};
