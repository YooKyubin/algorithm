#include <iostream>
#include <vector>

using namespace std;

constexpr int MOD = 1'000'000'000;

int main()
{
    freopen("../../input.txt", "r", stdin);
    int n;
    cin >> n;

    vector<vector<vector<int>>> dp (n, vector<vector<int>>(10, vector<int>(1 << 10, 0)));

    for (int i=1; i<10; ++i)
    {
        dp[0][i][1 << i] = 1;
    }

    for (int i=1; i<n; ++i)
    {
        for (int j=0; j<10; ++j)
        {
            for (int k=0; k < (1<<10); ++k)
            {
                int temp = 0;
                if (j > 0)
                {
                    temp += dp[i-1][j-1][k];
                    temp %= MOD;
                }
                if (j < 9)
                {
                    temp += dp[i-1][j+1][k];
                    temp %= MOD;
                }

                dp[i][j][k | (1 << j)] += temp;
                dp[i][j][k | (1 << j)] %= MOD;
            }
        }
    }
    
    int answer = 0;
    for (int i=0; i<10; ++i)
    {
        answer += dp[n-1][i][(1 << 10) - 1];
        answer %= MOD;
    }

    cout << answer << endl;

    return 0;
}