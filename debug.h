#pragma once

#include <boost/preprocessor.hpp>

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

#define PRINT(r, _, i, x) << BOOST_PP_IF(i, " [", '[') << BOOST_PP_STRINGIZE(x) << ": " << (x) << ']'
#define debug(...) cerr BOOST_PP_SEQ_FOR_EACH_I(PRINT, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) << '\n'
