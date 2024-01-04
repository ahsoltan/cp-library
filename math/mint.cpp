const int MOD = 998244353;
 
struct mint {
  uint32_t val;
 
  mint(ll v = 0) {
    v %= MOD;
    if (v < 0) {
      v += MOD;
    }
    val = v;
  }
 
  mint& operator+=(const mint& other) {
    val += other.val;
    if (val >= MOD) {
      val -= MOD;
    }
    return *this;
  }
 
  mint& operator-=(const mint& other) {
    val += MOD - other.val;
    if (val >= MOD) {
      val -= MOD;
    }
    return *this;
  }
 
  mint& operator*=(const mint& other) {
    val = (uint64_t)val * other.val % MOD;
    return *this;
  }
 
  mint& operator/=(const mint& other) {
    return *this *= other.inv();
  }
 
  friend mint operator+(mint a, const mint& b) { return a += b; }
  friend mint operator-(mint a, const mint& b) { return a -= b; }
  friend mint operator*(mint a, const mint& b) { return a *= b; }
  friend mint operator/(mint a, const mint& b) { return a /= b; }
 
  mint pow(ll exp) const {
    mint a = *this;
    mint res = 1;
    while (exp > 0) {
      if (exp & 1) {
        res *= a;
      }
      a *= a;
      exp /= 2;
    }
    return res;
  }
 
  mint inv() const {
    assert(val != 0);
    return pow(MOD - 2);
  }
 
  friend ostream& operator<<(ostream& os, const mint& m) {
    return os << m.val;
  }
};
