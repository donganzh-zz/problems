#include "io_util.hpp"
#include "benchmark.hpp"
#include <vector>
using namespace std;

template <typename T>
using Grid = vector<vector<T>>;

const int kRowNum = 8, kColNum = 8;

inline Grid<bool> createBoard(int row, int col) {
  return Grid<bool>(row, vector<bool>(col, false));
}

inline void clearBoard(Grid<bool>& board) {
  for (auto r : board) r.assign(kColNum, false);
}

void drawBoard(const Grid<bool>& board) {
  for (auto const& r : board) {
    for (auto const& e : r) cout << ' ' << (e ? '#' : '-');
    cout << '\n';
  }
}

inline bool checkRow(const Grid<bool>& board, int row, int col) {
  for (int j = 0; j < col; ++j)
    if (board[row][j]) return false;
  return true;
}

inline bool checkDiag(const Grid<bool>& board, int row, int col) {
  for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
    if (board[i][j]) return false;
  for (int i = row, j = col; j >= 0 && i < kRowNum; ++i, --j)
    if (board[i][j]) return false;
  return true;
}

inline bool isSafe(const Grid<bool>& board, int row, int col) {
  return checkDiag(board, row, col) && checkRow(board, row, col);
}

void solve(Grid<bool>& board, int col) {
  static int count = 1;
  if (col >= kColNum) {
    drawBoard(board);
    cout << string(40, '-') << setw(2) << count++ << endl;
    return;
  }
  for (int row = 0; row < kRowNum; ++row) {
    if (isSafe(board, row, col)) {
      board[row][col] = true;  // try queen here
      solve(board, col + 1);
      board[row][col] = false;  // failed, remove, try again
    }
  }
}

int main() {
  auto board = createBoard(kRowNum, kColNum);
  perf([&] { solve(board, 0); });
}
