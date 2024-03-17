#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> countToMinNum { 9, 9, 1, 7, 4, 2, 0, 8, 99, 99 }; // 0 or 6

string GetMax(int n)
{
    string nums;
    for (int i=0; i< n/2; ++i)
    {
        nums.push_back('1');
    }
    if (n % 2 == 1)
    {
        nums[0] = '7';
    }

    return nums;
}

int main()
{
    // freopen("../../input.txt", "r", stdin);

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    vector<uint64_t> dp(101);
    for (int i=0; i<=9; ++i)
    {
        dp[i] = countToMinNum[i];
    }
    dp[6] = 6;

    for (int i=8; i < 101; ++i)
    {
        dp[i] = dp[i-2] * 10 + countToMinNum[2];
        for (int j=2; j<=7; ++j)
        {
            dp[i] = min(dp[i], dp[i-j] * 10 + countToMinNum[j]);
        }
    }
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        int n;
        cin >> n;

        cout << dp[n] << " " << GetMax(n) << "\n";
    }

    return 0;

}