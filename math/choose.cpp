vector<mint> _f = {1}, _fi = {1};

void _init(int n) {
  int k = ssize(_f);
  if (n < k) {
    return;
  }
  n *= 2;
  _f.resize(n + 1);
  _fi.resize(n + 1);
  for (int i = k; i <= n; i++) {
    _f[i] = _f[i - 1] * i;
  }
  _fi[n] = _f[n].inv();
  for (int i = n; i > k; i--) {
    _fi[i - 1] = _fi[i] * i;
  }
}

mint fact(int n) {
  _init(n);
  return _f[n];
}

mint inv_fact(int n) {
  _init(n);
  return _fi[n];
}

mint choose(int n, int k) {
  if (n < k || k < 0) {
    return 0;
  }
  _init(n);
  return _f[n] * _fi[k] * _fi[n - k];
}
