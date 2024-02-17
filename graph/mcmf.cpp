#include <ext/pb_ds/priority_queue.hpp>

ll INF64 = 2e18;

struct MCMF {
  struct edge {
    int to, rev;
    int cap, cost;
  };

  struct cmp {
    bool operator()(const auto& l, const auto& r) const {
      return l.second > r.second;
    }
  };

  int n;
  vector<vector<edge>> adj;
  vector<ll> dst;
  ll c = 0;
  __gnu_pbds::priority_queue<pair<ll, int>, cmp> q;
  vector<decltype(q)::point_iterator> its;
  vector<int> id;

  MCMF(int _n) {
    n = _n;
    adj.resize(n);
    id.resize(n);
  }

  void add_edge(int u, int v, int cap, int cost) {
    int i = ssize(adj[u]);
    int j = ssize(adj[v]) + (u == v);
    adj[u].push_back({v, j, cap, cost});
    adj[v].push_back({u, i, 0, -cost});
  }

  void reduce(int t) {
    for (int i = 0; i < n; i++) {
      for (edge& e : adj[i]) {
        if (dst[i] != INF64 && dst[e.to] != INF64) {
          e.cost += dst[i] - dst[e.to];
        }
      }
    }
    c += dst[t];
  }

  bool dijkstra(int s, int t) {
    dst.assign(n, INF64);
    its.assign(n, q.end());
    dst[s] = 0;
    q.push({s, 0});
    while (!q.empty()) {
      int u = q.top().first;
      q.pop();
      for (edge& e : adj[u]) {
        if (e.cap > 0) {
          ll d = dst[u] + e.cost;
          if (d < dst[e.to]) {
            dst[e.to] = d;
            if (its[e.to] == q.end()) {
              its[e.to] = q.push({e.to, dst[e.to]});
            } else {
              q.modify(its[e.to], {e.to, dst[e.to]});
            }
            id[e.to] = e.rev;
          }
        }
      }
    }
    reduce(t);
    return dst[t] != INF64;
  }

  pair<ll, ll> flow(int s, int t, ll cap) {
    ll ff = 0;
    ll cc = 0;
    while (ff < cap && dijkstra(s, t)) {
      ll f = cap - ff;
      for (int i = t; i != s;) {
        edge& e = adj[i][id[i]];
        f = min(f, (ll)adj[e.to][e.rev].cap);
        i = e.to;
      }
      for (int i = t; i != s;) {
        edge& e = adj[i][id[i]];
        e.cap += f;
        adj[e.to][e.rev].cap -= f;
        i = e.to;
      }
      ff += f;
      cc += f * c;
    }
    return {ff, cc};
  }
};
