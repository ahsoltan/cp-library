struct SCC {
  int n, cnt = 0;
  vector<vector<int>> adj;
  vector<int> p, low, in;
  stack<int> st;
  int tour = 0;

  SCC(int _n) {
    n = _n;
    adj.resize(n);
    p.resize(n, -1);
    low.resize(n);
    in.resize(n, -1);
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
  }

  void dfs(int u) {
    low[u] = in[u] = tour++;
    st.push(u);
    for (int v : adj[u]) {
      if (in[v] == -1) {
        dfs(v);
        low[u] = min(low[u], low[v]);
      } else {
        low[u] = min(low[u], in[v]);
      }
    }
    if (low[u] == in[u]) {
      int v = -1;
      do {
        v = st.top();
        st.pop();
        in[v] = n;
        p[v] = cnt;
      } while (v != u);
      cnt++;
    }
  }

  void build() {
    for (int i = 0; i < n; ++i) {
      if (in[i] == -1) {
        dfs(i);
      }
    }
    for (int i = 0; i < n; i++) {
      p[i] = cnt - 1 - p[i];
    }
  }

  vector<vector<int>> groups() {
    vector<vector<int>> res(cnt);
    for (int i = 0; i < n; i++) {
      res[p[i]].push_back(i);
    }
    return res;
  }
};
