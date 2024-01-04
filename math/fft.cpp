struct FFT {
  int N;
  vector<int> rev;
  vector<mint> w;

  FFT(int k) {
    N = 1 << k;
    rev.resize(N);
    for (int i = 1; i < N; i++) {
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    }
#warning MOD = 998244353
    mint W = mint(3).pow(119 * ((1 << 23) / N));
    w.resize(N);
    mint ww = 1;
    for (int i = 0; i < N / 2; i++) {
      w[i + N / 2] = ww;
      ww *= W;
    }
    for (int i = N / 2 - 1; i > 0; i--) {
      w[i] = w[2 * i];
    }
  }

  void fft(vector<mint>& a) {
    int n = ssize(a);
    int s = __lg(N / n);
    for (int i = 0; i < n; i++) {
      int r = rev[i] >> s;
      if (i < r) {
        swap(a[i], a[r]);
      }
    }
    for (int i = 1; i < n; i *= 2) {
      for (int j = 0; j < n; j += 2 * i) {
        for (int k = 0; k < i; k++) {
          mint z = w[i + k] * a[j + k + i];
          a[j + k + i] = a[j + k] - z;
          a[j + k] += z;
        }
      }
    }
  }

  vector<mint> conv(vector<mint> a, vector<mint> b) {
    int n = ssize(a);
    int m = ssize(b);
    int k = 1;
    while (k < n + m - 1) {
      k *= 2;
    }
    a.resize(k);
    b.resize(k);
    fft(a);
    fft(b);
    for (int i = 0; i < k; i++) {
      a[i] *= b[i];
    }
    fft(a);
    reverse(a.begin() + 1, a.end());
    a.resize(n + m - 1);
    mint inv = mint(k).inv();
    for (int i = 0; i < n + m - 1; i++) {
      a[i] *= inv;
    }
    return a;
  }
};
