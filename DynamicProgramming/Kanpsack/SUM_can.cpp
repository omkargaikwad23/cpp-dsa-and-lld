#include <bits/stdc++.h>
using namespace std;

// can(3, {2, 1, 1}) -> "YES" (1, 1, 1) || (2, 1)

// memoization
map<int, bool> memo;
map<int, bool>::iterator itr;
bool can_get_sum(int targetSum, int arr[], int n)
{
  itr = memo.find(targetSum);
  if (itr != memo.end())
    return itr->second;
  if (targetSum == 0)
    return true;
  if (targetSum < 0)
    return false;

  for (int i = 0; i < n; i++)
  {
    int rem = targetSum - arr[i];
    if (can_get_sum(rem, arr, n))
    {
      memo[targetSum] = true;
      return true;
    }
  }
  memo[targetSum] = false;
  return false;
}

// tabulation
bool can_get_sum_tabu(int sum, int arr[], int n)
{
  bool table[sum + 1] = {false};
  table[0] = true;

  for (int i = 0; i < sum; i++)
  {
    if (table[i])
    {
      for (int j = 0; j < n; j++)
      {
        if (i + arr[j] <= sum)
          table[i + arr[j]] = true;
      }
    }
  }

  return table[sum];
}

int main()
{
  int targetSum, n, temp;
  cin >> targetSum >> n;
  // vector<int>v;
  int arr[n];
  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
  }

  bool ans = can_get_sum_tabu(targetSum, arr, n);
  if (ans)
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
  return 0;
}