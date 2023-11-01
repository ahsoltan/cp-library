ostream& operator<<(ostream& os, const pair<auto, auto>& x);

template<typename T, typename = T::value_type>
ostream& operator<<(ostream& os, const T& x) requires (!same_as<T, string>) {
  os << '{';
  string sep;
  for (const auto& v : x) {
    os << sep << v;
    sep = ", ";
  }
  return os << '}';
}

ostream& operator<<(ostream& os, const pair<auto, auto>& x) {
  return os << '(' << x.first << ", " << x.second << ')';
}

void __print(const auto&... x) {
  ((cerr << ' ' << x), ...);
  cerr << endl;
}

#define debug(...) cerr << '[' << #__VA_ARGS__ << "]:"; __print(__VA_ARGS__)
