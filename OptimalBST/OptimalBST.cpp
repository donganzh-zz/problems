// CLRS3rd Section 15.5
//
// longwen6@gmail.com @ 2015-08-13

#include "VectorUtil.hpp"
#include "TupleUtil.hpp"
#include "IOUtil.hpp"
#include <cassert>
#include <stack>
#include <limits>
#include <algorithm>
using namespace std;

pair<Vector2D<double>, Vector2D<int>> optimalBinarySearchTree(
    const vector<double>& p, const vector<double>& q) {
  const long psize = p.size(), qsize = q.size(), n = qsize;
  assert(psize + 1 == n);
  Vector2D<double> e(n + 1, vector<double>(n)), w(n + 1, vector<double>(n));
  Vector2D<int> root(n, vector<int>(n));  // index
  for (int i = 1; i < n + 1; ++i) e[i][i - 1] = w[i][i - 1] = q[i - 1];
  for (int len = 1; len < n; ++len) {
    for (int i = 1, j = i + len - 1; j < n; ++i, ++j) {
      e[i][j] = numeric_limits<double>::infinity();
      w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
      for (int r = i; r <= j; ++r) {
        auto t = e[i][r - 1] + e[r + 1][j] + w[i][j];
        if (t < e[i][j]) e[i][j] = t, root[i][j] = r;
      }
    }
  }

  return {e, root};
}

template <typename T>
struct TreeNode {
  TreeNode<T>* left, *right;
  T val;
  TreeNode(const T& v, TreeNode<T>* l = nullptr, TreeNode<T>* r = nullptr)
      : left(l), right(r), val(v) {}
};

struct OptimalBSTConstructor {
  const vector<double>& p;
  const vector<double>& q;
  const Vector2D<int>& root;

  TreeNode<double>* construct(int i, int j) {
    auto r = root[i][j];
    auto node = new TreeNode<double>(p[r - 1]);
    node->left = r == i ? new TreeNode<double>(q[r - 1]) : construct(i, r - 1);
    node->right = r == j ? new TreeNode<double>(q[r]) : construct(r + 1, j);
    return node;
  }

  TreeNode<double>* operator()() { return construct(1, p.size()); }
};

void printDoubleVector2D(const Vector2D<double>& vv) {
  for (auto const& row : vv) {
    for (auto const& e : row) cout << setw(5) << e;
    cout << endl;
  }
}

template <typename T>
pair<vector<T>, vector<T>> inorderTraverse(const TreeNode<T>* root) {
  vector<T> p, q;
  stack<const TreeNode<T>*> stk;
  for (auto node = root; !stk.empty() || node;) {
    for (; node; node = node->left) stk.push(node);
    if (stk.empty()) continue;
    node = stk.top(), stk.pop();
    if (!node->left && !node->right)
      q.push_back(node->val);
    else
      p.push_back(node->val);
    node = node->right;
  }
  return {p, q};
}

using Arg = pair<vector<double>, vector<double>>;
using Res = pair<Vector2D<double>, Vector2D<int>>;

int main() {
  vector<Arg> args{
      Arg({0.15, 0.10, 0.05, 0.10, 0.20}, {0.05, 0.10, 0.05, 0.05, 0.05, 0.10}),
      Arg({0.04, 0.06, 0.08, 0.02, 0.1, 0.12, 0.14},
          {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05}),
  };

  for (auto const& arg : args) {
    cout << "p " << arg.first << endl;
    cout << "q " << arg.second << endl;
    auto res = apply(optimalBinarySearchTree, arg);
    // printDoubleVector2D(res.first);
    printDelimLine(80, '-');
    // printVector2D(cout, res.second);
    // printDelimLine(80, '-');
    auto tree = OptimalBSTConstructor{arg.first, arg.second, res.second}();
    auto pq = inorderTraverse(tree);
    cout << "p " << pq.first << endl;
    cout << "q " << pq.second << endl;
    printDelimLine(80, '^');
  }
}
