// CLRS3rd Section 15.2
//
// longwen6@gmail.com @ 2015-08-13

#include "VectorUtil.hpp"
#include "IOUtil.hpp"

#include <limits>
using namespace std;

// <p0, p1, ..., pn>, size of matrix Mi is p(i-1) x p(i), n matrix
pair<Vector2D<int>, Vector2D<int>> matrixChainMultiplication(
    const vector<int>& chain) {
  const long size = chain.size();            // size-1 matrix
  Vector2D<int> m(size, vector<int>(size));  // saving computation cost
  Vector2D<int> s(size, vector<int>(size));  // recording split point
  for (int len = 2; len < size; ++len) {     // len is the chain length
    // costs of computation Mi...Mj, where j-i+1 = len
    for (int i = 1, j = i + len - 1; j < size; ++i, ++j) {
      m[i][j] = std::numeric_limits<int>::max();
      for (int k = i; k < j; ++k) {
        auto tmp = m[i][k] + chain[i - 1] * chain[k] * chain[j] + m[k + 1][j];
        if (tmp < m[i][j]) m[i][j] = tmp, s[i][j] = k;
      }  // k
    }
  }  // len
  return {m, s};
}

void printOptimalParens(const Vector2D<int>& s, int i, int j) {
  if (i == j) {
    cout << 'm' << i;
    return;
  }
  cout << '(';
  printOptimalParens(s, i, s[i][j]);
  printOptimalParens(s, s[i][j] + 1, j);
  cout << ')';
}

int lookupChain(const vector<int>& c, Vector2D<int>& m, Vector2D<int>& s, int i,
                int j) {
  if (m[i][j] < numeric_limits<int>::max()) return m[i][j];
  if (i == j)
    m[i][j] = 0;
  else
    for (int k = i; k < j; ++k) {
      auto tmp = lookupChain(c, m, s, i, k) + lookupChain(c, m, s, k + 1, j) +
          c[i - 1] * c[k] * c[j];
      if (tmp < m[i][j]) m[i][j] = tmp, s[i][j] = k;
    }
  return m[i][j];
}

pair<Vector2D<int>, Vector2D<int>> matrixChainMultiplicationRec(
    const vector<int>& chain) {
  const long size = chain.size();
  Vector2D<int> m(size, vector<int>(size, numeric_limits<int>::max()));
  Vector2D<int> s(size, vector<int>(size));
  lookupChain(chain, m, s, 1, size - 1);
  return {m, s};
}

int main() {
  Vector2D<int> chains{{30, 35, 15, 5, 10, 20, 25}, {5, 10, 3, 12, 5, 50, 6}};
  for (auto const& c : chains) {
    cout << c << endl;
    printDelimLine(80, '-');
    auto res = matrixChainMultiplicationRec(c);
    printVector2D(cout, res.first);
    printDelimLine(80, '-');
    printVector2D(cout, res.second);
    printDelimLine(80, '-');
    printOptimalParens(res.second, 1, 6);
    cout << " costs: " << res.first[1][6] << endl;
    printDelimLine(80, '^');
  }
}
