#include <string>
#include <vector>
#include "TupleUtil.hpp"
#include "VectorUtil.hpp"

long lengthLCS(const std::string& s1, const std::string& s2) {
  const long len1 = s1.size(), len2 = s2.size();
  std::vector<std::vector<int>> c(len1 + 1, std::vector<int>(len2 + 1, 0));
  for (long i = 0; i < len1; ++i) {
    for (long j = 0; j < len2; ++j) {
      if (s1[i] == s2[j])
        c[i + 1][j + 1] = c[i][j] + 1;
      else if (c[i + 1][j] <= c[i][j + 1])
        c[i + 1][j + 1] = c[i][j + 1];
      else
        c[i + 1][j + 1] = c[i + 1][j];
    }
  }
  return c[len1][len2];
}

void lcsHelper(const std::string& s1, const std::vector<std::vector<char>>& b,
               int i, int j, std::string& res) {
  if (i == 0 || j == 0) return;
  if (b[i][j] == '\\')
    lcsHelper(s1, b, i - 1, j - 1, res), res.push_back(s1[i - 1]);
  else if (b[i][j] == '|')
    lcsHelper(s1, b, i - 1, j, res);
  else
    lcsHelper(s1, b, i, j - 1, res);
}

std::string lcs(const std::string& s1, const std::string& s2) {
  const long len1 = s1.size(), len2 = s2.size();
  std::vector<std::vector<int>> c(len1 + 1, std::vector<int>(len2 + 1, 0));
  std::vector<std::vector<char>> b(len1 + 1, std::vector<char>(len2 + 1, ' '));
  for (long i = 0; i < len1; ++i) {
    for (long j = 0; j < len2; ++j) {
      if (s1[i] == s2[j])
        c[i + 1][j + 1] = c[i][j] + 1, b[i + 1][j + 1] = '\\';
      else if (c[i + 1][j] <= c[i][j + 1])
        c[i + 1][j + 1] = c[i][j + 1], b[i + 1][j + 1] = '|';
      else
        c[i + 1][j + 1] = c[i + 1][j], b[i + 1][j + 1] = '-';
    }
  }
  std::string res;
  lcsHelper(s1, b, len1, len2, res);
  return res;
}

std::vector<std::string> allLCS(const std::string& s1, const std::string& s2) {
  const long len1 = s1.size(), len2 = s2.size();
  std::vector<std::vector<int>> c(len1 + 1, std::vector<int>(len2 + 1, 0));
  std::vector<std::vector<char>> b(len1 + 1, std::vector<char>(len2 + 1, ' '));
  for (long i = 0; i < len1; ++i) {
    for (long j = 0; j < len2; ++j) {
      if (s1[i] == s2[j])
        c[i + 1][j + 1] = c[i][j] + 1, b[i + 1][j + 1] = '\\';
      else if (c[i + 1][j] <= c[i][j + 1])
        c[i + 1][j + 1] = c[i][j + 1], b[i + 1][j + 1] = '|';
      else
        c[i + 1][j + 1] = c[i + 1][j], b[i + 1][j + 1] = '-';
    }
  }
  std::vector<std::string> res;
  return res;
}

using namespace std;
using Args = std::tuple<const string, const string>;
using Res = long;
void printTestInfo(const string& funcName, const std::pair<Res, Args>& info) {
  cout << funcName << "(" << get<0>(info.second) << ", " << get<1>(info.second)
       << ") == " << info.first << "\n";
}

vector<pair<Res, Args>> testData{
    {Res(5), Args({"inthebeginning", "allthingsarelost"})},
    {Res(4), Args({"ABCBDAB", "BDCABA"})},
    {Res(4), Args({"cnblogs", "belong"})},
};

int main() {
  for (auto const& t : testData) {
    auto res = apply(lengthLCS, t.second);
    auto res2 = apply(lcs, t.second);
    cout << res2 << "\n";
    if (t.first != res) {
      printTestInfo("lengthLCS", t);
      cerr << "  WRONG RESULT: " << res << "\n";
    }
  }
}
