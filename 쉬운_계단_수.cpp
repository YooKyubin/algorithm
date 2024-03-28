#include <iostream>
#include <vector>

using namespace std;

constexpr int MOD = 1'000'000'000;

int main()
{
    // freopen("../../input.txt", "r", stdin);
    int n;
    cin >> n;

    vector<vector<int>> dp(n, vector<int>(10, 0));
    for (int i=1; i < 10; ++i)
    {
        dp[0][i] = 1;
    }

    for (int i=1; i<n; ++i)
    {
        dp[i][0] = dp[i-1][1];
        dp[i][9] = dp[i-1][8];
        for (int j=1; j<9; ++j)
        {
            dp[i][j] = ( dp[i-1][j-1] + dp[i-1][j+1] ) % MOD;
        }
    }

    int answer = 0;
    for (int i=0; i<10; ++i)
    {
        answer += dp[n-1][i];
        answer %= MOD;
    }

    cout << answer << endl;

    return 0;
}