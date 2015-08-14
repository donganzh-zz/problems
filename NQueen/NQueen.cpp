#include <vector>
#include <iostream>
#include <string>
#include "io_util.hpp"
using namespace std;

class Solution {
 public:
  using Grid = vector<string>;
  bool checkRow(const Grid& board, int row, int col) {
    for (int j = 0; j < col; ++j)
      if (board[row][j] == 'Q') return false;
    return true;
  }

  bool checkDiag(const Grid& board, int row, int col, int n) {
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
      if (board[i][j] == 'Q') return false;
    for (int i = row, j = col; i < n && j >= 0; ++i, --j)
      if (board[i][j] == 'Q') return false;
    return true;
  }

  bool isSafe(const Grid& board, int row, int col, int n) {
    return checkRow(board, row, col) && checkDiag(board, row, col, n);
  }

  void solver(Grid& board, int col, int n, vector<Grid>& res) {
    if (col >= n) {
      res.push_back(board);
      return;
    }
    for (int row = 0; row < n; ++row) {
      if (isSafe(board, row, col, n)) {
        board[row][col] = 'Q';
        solver(board, col + 1, n, res);
        board[row][col] = '.';
      }
    }
  }

  vector<vector<string>> solveNQueens(int n) {
    vector<Grid> res;
    Grid board(n, string(n, '.'));
    solver(board, 0, n, res);
    return res;
  }
};

int main() {
  int n;
  while (cin >> n) {
    auto res = Solution{}.solveNQueens(n);

    for (int i = 0; i < res.size(); ++i) {
      printSequence(res[i]);
      cout << string(40, '-') << endl;
    }
    cout << res.size() << endl;
  }
}
