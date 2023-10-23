mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node {
  node* l = nullptr;
  node* r = nullptr;
  node* p = nullptr;
  int sz = 1;
  int val;
  unsigned long long pr;

  node(int a) {
    val = a;
    pr = rng();
  }
};

int size(node* x) {
  return x ? x->sz : 0;
}

void pull(node* x) {
  x->sz = 1 + size(x->l) + size(x->r);
  (x->l && (x->l->p = x));
  (x->r && (x->r->p = x));
}

node* merge(node* l, node* r) {
  if (!l || !r) {
    return l ? l : r;
  }
  node* res;
  if (l->pr > r->pr) {
    l->r = merge(l->r, r);
    res = l;
  } else {
    r->l = merge(l, r->l);
    res = r;
  }
  pull(res);
  return res;
}

pair<node*, node*> split(node* x, int n) {
  if (!x) {
    return {nullptr, nullptr};
  }
  pair<node*, node*> res;
  if (n <= size(x->l)) {
    auto [l, r] = split(x->l, n);
    res = {l, x};
    x->l = r;
  } else {
    auto [l, r] = split(x->r, n - size(x->l) - 1);
    res = {x, r};
    x->r = l;
  }
  pull(x);
  (res.first && (res.first->p = nullptr));
  (res.second && (res.second->p = nullptr));
  return res;
}
