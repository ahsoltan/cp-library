vector<int> suffix_array(const string& s) {
  int n = ssize(s);
  vector<int> p(n), cnt(26);
  for (int i = 0; i < n; i++) {
    cnt[s[i] - 'a']++;
  }
  for (int i = 1; i < 26; i++) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = 0; i < n; i++) {
    p[--cnt[s[i] - 'a']] = i;
  }
  vector<int> rnk(n);
  for (int i = 1; i < n; i++) {
    rnk[p[i]] = s[p[i]] == s[p[i - 1]] ? rnk[p[i - 1]] : i;
  }
  cnt.resize(n);
  vector<int> np(n), nrnk(n);
  for (int len = 1; len < n; len *= 2) {
    iota(cnt.begin(), cnt.end(), 0);
    for (int i = n - len; i < n; i++) {
      np[cnt[rnk[i]]++] = i;
    }
    for (int i = 0; i < n; i++) {
      if (p[i] - len >= 0) {
        np[cnt[rnk[p[i] - len]]++] = p[i] - len;
      }
    }
    nrnk[np[0]] = 0;
    for (int i = 1; i < n; i++) {
      int a = np[i - 1];
      int b = np[i];
      if (max(a, b) + len < n && rnk[a] == rnk[b] && rnk[a + len] == rnk[b + len]) {
        nrnk[b] = nrnk[a];
      } else {
        nrnk[b] = i;
      }
    }
    swap(p, np);
    swap(rnk, nrnk);
  }
  return p;
};

vector<int> build_lcp(const string& s, const vector<int>& sa) {
  int n = ssize(s);
  vector<int> pos(n);
  for (int i = 0; i < n; i++) {
    pos[sa[i]] = i;
  }
  vector<int> lcp(n - 1);
  int k = 0;
  for (int i = 0; i < n; i++) {
    if (pos[i] == 0) {
      continue;
    }
    while (i + k < n && s[i + k] == s[sa[pos[i] - 1] + k]) {
      k++;
    }
    lcp[pos[i] - 1] = k;
    k = max(0, k - 1);
  }
  return lcp;
}
