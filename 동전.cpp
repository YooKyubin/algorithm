#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 12:48

int solution(int n, vector<int>& coins, int target)
{
    int answer = 0;

    vector<vector<int>> dp(n, vector<int>(target + 1, 0));
    for (int i = 0; i < target + 1; i += coins[0])
    {
        dp[0][i] = 1;
    }

    for (int i = 1; i < n; ++i)
    {
        int coin = coins[i];
        for (int j = 0; j < target + 1; ++j)
        {
            if (j < coin)
            {
                dp[i][j] = dp[i-1][j];
            }
            else
            {
                dp[i][j] = dp[i][j - coin] + dp[i-1][j];
            }
        }
    }

    answer = dp.back().back();
    return answer;
}

int main()
{
    freopen("input.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCase = 0;
    cin >> testCase;

    while (testCase--)
    {
        int n; 
        cin >> n;
        vector<int> coins(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> coins[i];
        }
        int target;
        cin >> target;

        cout << solution(n, coins, target) << "\n";
    }
    return 0;
}