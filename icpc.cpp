// main.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#ifdef LOCAL
auto& operator<<(auto& os, pair<auto, auto> x);
template<typename T, typename = T::value_type>
auto& operator<<(auto& os, T x) requires (!same_as<T, string>) {
  os << '{';
  string sep;
  for (const auto& v : x) {
    os << sep << v;
    sep = ", ";
  }
  return os << '}';
}
auto& operator<<(auto& os, pair<auto, auto> x) {
  return os << '(' << x.first << ", " << x.second << ')';
}
#define debug(x) cerr << '[' << #x << ": " << (x) << "]\n"
#else
#define debug(...) 2137
#endif

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

// .vimrc
set autoindent expandtab tabstop=2 shiftwidth=2 nu ic timeoutlen=1000 ttimeoutlen=10 hidden smartindent
syntax enable
colorscheme retrobox
inoremap {<cr> {<cr>}<esc>O <bs>
nnoremap ; :
nnoremap : ;
nnoremap <space>` :b#<cr>
filetype indent on

// Makefile
CXXFLAGS=-std=c++20 -Wall -Wextra -Wshadow -fsanitize=address,undefined -g -DLOCAL

// test
#!/bin/bash
for i in {0..2137}
do
  echo "$i" | ./gen > test.in
  ./slow < test.in > slow.out
  ./fast < test.in > fast.out
  if diff -b slow.out fast.out > /dev/null
  then
    echo "$i OK"
  else
    echo "$i NIEOK"
    break
  fi
done
