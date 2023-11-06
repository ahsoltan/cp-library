vector<int> z(const string& s) {
  int n = ssize(s);
  vector<int> f(n);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i <= r) {
      f[i] = min(r - i + 1, f[i - l]);
    }
    while (f[i] < n - i && s[i + f[i]] == s[f[i]]) {
      f[i]++;
    }
    if (i + f[i] - 1 > r) {
      l = i;
      r = i + f[i] - 1;
    }
  }
  return f;
}
