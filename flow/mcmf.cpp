const int INF = 1e9;

struct MCMF {
  struct edge {
    int to, rev;
    int cap, cost;
  };

  struct ds {
    int u, val;

    friend bool operator<(const ds& lhs, const ds& rhs) {
      return lhs.val > rhs.val;
    }
  };

  int n;
  vector<vector<edge>> adj;
  vector<array<int, 3>> f;
  int c = 0;

  MCMF(int _n) {
    n = _n;
    adj.resize(n);
    f.resize(n);
  }

  void add_edge(int u, int v, int cap, int cost) {
    if (u == v) {
      assert(cost >= 0);
      return;
    }
    int i = adj[u].size();
    int j = adj[v].size();
    adj[u].push_back({v, j, cap, cost});
    adj[v].push_back({u, i, 0, -cost});
  }

  void reduce(const vector<int>& dst, int t) {
    for (int i = 0; i < n; i++) {
      for (edge& e : adj[i]) {
        if (dst[i] < INF && dst[e.to] < INF) {
          e.cost += dst[i] - dst[e.to];
        }
      }
    }
    c += dst[t];
  }

  bool init(int s, int t) {
    vector<int> dst(n, INF);
    queue<int> q;
    vector<bool> inq(n);
    dst[s] = 0;
    q.push(s);
    inq[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inq[u] = false;
      for (edge& e : adj[u]) {
        if (e.cap > 0 && dst[u] + e.cost < dst[e.to]) {
          dst[e.to] = dst[u] + e.cost;
          if (!inq[e.to]) {
            q.push(e.to);
            inq[e.to] = true;
          }
        }
      }
    }
    if (dst[t] == INF) {
      return false;
    }
    reduce(dst, t);
    return true;
  }

  bool dijkstra(int s, int t) {
    vector<int> dst(n, INF);
    priority_queue<ds> q;
    dst[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
      auto [u, d] = q.top();
      q.pop();
      if (d != dst[u]) {
        continue;
      }
      int i = 0;
      for (edge& e : adj[u]) {
        if (e.cap > 0) {
          int dd = d + e.cost;
          if (dd < dst[e.to]) {
            dst[e.to] = dd;
            f[e.to] = {u, i, e.rev};
            q.push({e.to, dd});
          }
        }
        i++;
      }
    }
    if (dst[t] == INF) {
      return false;
    }
    reduce(dst, t);
    return true;
  }

  pair<int, int> build(int s, int t, int cap) {
    if (!init(s, t)) {
      return {0, 0};
    }
    int flow = 0;
    int cost = 0;
    while (flow < cap && dijkstra(s, t)) {
      int add = cap - flow;
      for (int i = t; i != s; i = f[i][0]) {
        add = min(add, adj[f[i][0]][f[i][1]].cap);
      }
      flow += add;
      cost += c * add;
      for (int i = t; i != s; i = f[i][0]) {
        adj[f[i][0]][f[i][1]].cap -= add;
        adj[i][f[i][2]].cap += add;
      }
    }
    return {flow, cost};
  }
};
