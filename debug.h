#include <boost/preprocessor.hpp>

template<typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& x);

template<typename T, typename>
ostream& operator<<(ostream& os, const T& x);

template<typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& x) {
  return os << '(' << x.first << ", " << x.second << ')';
}

template<typename T, typename = enable_if_t<!is_same_v<T, string>, typename T::value_type>>
ostream& operator<<(ostream& os, const T& x) {
  os << '{';
  string sep;
  for (const auto& v : x) {
    os << sep << v;
    sep = ", ";
  }
  return os << '}';
}

#define PRINT(r, _, i, x) << BOOST_PP_IF(i, " [", '[') << BOOST_PP_STRINGIZE(x) << ": " << (x) << ']'
#define debug(...) cerr BOOST_PP_SEQ_FOR_EACH_I(PRINT, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) << '\n'