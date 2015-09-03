/*
https://leetcode.com/problems/permutations-ii/

Given a collection of numbers that might contain duplicates, return all possible
unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1].
*/

#include "std.hpp"
using namespace std;

class Solution1 {
 public:
  vector<vector<int>> permuteUnique(vector<int>& num) {
    // https://leetcode.com/discuss/25279/a-simple-c-solution-in-only-20-lines
    vector<vector<int>> res;
    if (num.empty()) return res;
    sort(num.begin(), num.end());
    helper(num, 0, res);
    return res;
  }
  void helper(vector<int> num, int idx, vector<vector<int>>& res) {
    const int size = num.size();
    if (idx == size - 1) {
      res.push_back(move(num));
      return;
    }
    for (int k = idx; k < size; k++) {
      if (idx != k && num[idx] == num[k]) continue;
      swap(num[idx], num[k]);
      helper(num, idx + 1, res);
    }
  }
};

class Solution2 {
 public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    // https://leetcode.com/discuss/25279/a-simple-c-solution-in-only-20-lines
    vector<vector<int>> res;
    if (nums.empty()) return res;
    sort(nums.begin(), nums.end());
    helper(nums, 0, res);
    return res;
  }

  void helper(vector<int>& nums, int idx, vector<vector<int>>& res) {
    const int size = nums.size();
    if (idx == size - 1) {
      res.push_back(nums);
      return;
    }
    for (int i = idx; i < size; ++i) {
      if (i != idx && nums[i] == nums[idx]) continue;
      swap(nums[idx], nums[i]);
      helper(nums, idx + 1, res);
    }
    if (idx + 1 < size)
      rotate(nums.begin() + idx, nums.begin() + idx + 1, nums.end());
  }
};

class Solution3 {
 public:
  vector<vector<int>> permuteUnique(vector<int>& num) {
    // https://leetcode.com/discuss/20598/accepted-backtracking-c-solution-by-using-map-28ms
    vector<vector<int>> res;
    if (num.empty()) return res;
    vector<int> tmp;
    unordered_map<int, int> vmap;
    for (int i : num) vmap[i]++;
    helper(tmp, vmap, num.size(), res);
    return res;
  }

  void helper(vector<int>& tmp, unordered_map<int, int>& vmap, int n,
              vector<vector<int>>& res) {
    if (n <= 0) {
      res.push_back(tmp);
      return;
    }
    for (auto& p : vmap) {
      if (p.second <= 0) continue;
      tmp.push_back(p.first), --p.second;
      helper(tmp, vmap, n - 1, res);
      tmp.pop_back(), ++p.second;
    }
  }
};

class Solution4 {
 public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    // http://www.cnblogs.com/panda_lin/archive/2013/11/14/permutations_ii.html
    vector<vector<int>> res;
    if (nums.empty()) return res;
    vector<int> perm;

    sort(nums.begin(), nums.end());
    helper(nums, 0, perm, res);

    return res;
  }

  void helper(vector<int>& nums, int idx, vector<int>& perm,
              vector<vector<int>>& res) {
    int size = nums.size();

    if (idx == size) {
      res.push_back(perm);
      return;
    }
    for (int i = idx; i < size; ++i) {
      if (i != idx && nums[idx] == nums[i])
        continue;
      else
        swap(nums[idx], nums[i]);

      perm.push_back(nums[idx]);
      helper(nums, idx + 1, perm, res);
      perm.pop_back();
    }
    sort(nums.begin() + idx, nums.end());
  }
};

class Solution5 {
 public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> res;
    if (nums.empty()) return res;
    sort(nums.begin(), nums.end());
    res.push_back(nums);
    while (nextPermutation(nums.begin(), nums.end())) res.push_back(nums);
    return res;
  }

  using Iter = vector<int>::iterator;
  bool nextPermutation(Iter first, Iter last) {
    if (first == last) return false;
    auto iter = last - 1;
    if (first == iter) return false;
    while (true) {
      auto oldIter = iter;
      if (*--iter < *oldIter) {
        auto tmp = last - 1;
        while (*tmp <= *iter) --tmp;
        iter_swap(iter, tmp);
        reverse(oldIter, last);
        return true;
      }
      if (iter == first) {
        reverse(first, last);
        return false;
      }
    }
  }
};

class Solution6 {
 public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    // http://en.cppreference.com/w/cpp/algorithm/prev_permutation
    vector<vector<int>> res;
    if (nums.empty()) return res;
    sort(nums.begin(), nums.end(), greater<>{});
    res.push_back(nums);
    while (prevPermutation(nums.begin(), nums.end())) res.push_back(nums);
    return res;
  }

  using Iter = vector<int>::iterator;
  bool prevPermutation(Iter first, Iter last) {
    if (first == last) return false;
    auto iter = last - 1;
    if (first == iter) return false;
    while (true) {
      auto t1 = iter;
      if (*--iter > *t1) {
        auto t2 = last - 1;
        while (*t2 >= *iter) --t2  ;
        iter_swap(iter, t2);
        reverse(t1, last);
        return true;
      }
      if (iter == first) {
        reverse(first, last);
        return false;
      }
    }
  }
};

int main() {
  vector<int> num;
  int val;
  while (cin >> val) num.push_back(val);
  auto res1 = Solution1{}.permuteUnique(num);
  for (auto const& e : res1) cout << e << endl;
  cout << string(40, '-') << endl;

  auto res2 = Solution2{}.permuteUnique(num);
  for (auto const& e : res2) cout << e << endl;
  cout << string(40, '-') << endl;

  auto res3 = Solution3{}.permuteUnique(num);
  for (auto const& e : res3) cout << e << endl;
  cout << string(40, '-') << endl;

  auto res4 = Solution4{}.permuteUnique(num);
  for (auto const& e : res4) cout << e << endl;
  cout << string(40, '-') << endl;

  auto res5 = Solution5{}.permuteUnique(num);
  for (auto const& e : res5) cout << e << endl;
  cout << string(40, '-') << endl;

  auto res6 = Solution6{}.permuteUnique(num);
  for (auto const& e : res6) cout << e << endl;
  cout << string(40, '-') << endl;
}
