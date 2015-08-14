// CLRS3rd Section 16.1
// longwen6@gmail.com @ 2015-08-14
//
#include "TupleUtil.hpp"
#include "VectorUtil.hpp"
#include "IOUtil.hpp"
#include "benchmark.hpp"
#include <algorithm>

using namespace std;

// first: beg time; second: end time
using Activity = pair<int, int>;

void helper(const vector<Activity>& s, int k, vector<Activity>& res) {
  const int size = s.size(), endTime = s[k++].second;
  while (k < size && s[k].first < endTime) ++k;
  if (k < size) res.push_back(s[k]), helper(s, k, res);
}
// assume s is already sorted by end time
vector<Activity> recActivitySelector(const vector<Activity>& s) {
  vector<Activity> res{s.front()};
  helper(s, 0, res);
  return res;
}

// assume s is already sorted by end time
vector<Activity> greedyActivitySelector(const vector<Activity>& s) {
  vector<Activity> res{s.front()};
  for (int k = 1, size = s.size(); k < size; ++k)
    if (s[k].first >= res.back().second) res.push_back(s[k]);
  return res;
}

vector<Activity> dynamicActivitySelector(const vector<Activity>& s) {
  const int size = s.size();
  Vector2D<int> c(size, vector<int>(size)), r(c);
  for (int len = 2; len < size; ++len) {
    for (int i = 0, j = i + len; j < size; ++i, ++j) {
      for (int k = i + 1; k < j; ++k) {
        // note that the first and last activity is not included (and should be)
        if (s[i].second <= s[k].first && s[k].second <= s[j].first) {
          int t = c[i][k] + c[k][j] + 1;
          if (t > c[i][j]) c[i][j] = t, r[i][j] = k;
        }
      }  // k
    }    // i, j
  }      // len

  // construct the result from matrix r
  vector<Activity> res{s.front()};  // the first is not included in r
  int i = 0, j = size - 1, idx = r[i][j];
  for (; i < j && idx != 0; i = idx, idx = r[i][j]) res.push_back(s[idx]);
  res.push_back(s.back());  // the last activity is not included in r
  return res;
}

int main() {
  vector<vector<Activity>> activities{{{1, 4},
                                       {3, 5},
                                       {0, 6},
                                       {5, 7},
                                       {3, 9},
                                       {5, 9},
                                       {6, 10},
                                       {8, 11},
                                       {8, 12},
                                       {2, 14},
                                       {12, 16}}};

  for (auto const& a : activities) {
    vector<Activity> res1, res2, res3;
    perf([&] { res1 = recActivitySelector(a); });
    perf([&] { res2 = greedyActivitySelector(a); });
    perf([&] { res3 = dynamicActivitySelector(a); });
    cout << res1.size() << " : " << res1 << endl;
    cout << res2.size() << " : " << res2 << endl;
    cout << res3.size() << " : " << res3 << endl;
  }
}
