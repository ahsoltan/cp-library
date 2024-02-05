#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#ifdef LOCAL
auto& operator<<(auto&, pair<auto, auto>);
template<typename T, typename = T::value_type>
auto& operator<<(auto& o, T x) {
  o << "{";
  string s;
  for (auto i : x) {
    o << s << i;
    s = ", ";
  }
  return o << "}";
}
auto& operator<<(auto& o, pair<auto, auto> x) {
  return o << "(" << x.first << ", " << x.second << ")";
}
#define debug(x...) cerr << "[" #x "]:", [] (auto...y) { ((cerr << " " << y), ...) << endl; }(x)
#else
#define debug(...) 2137
#endif

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}
