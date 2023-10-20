#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n, k;
    vector<vector<int>> dp;
    vector<pair<int, int>> stuff;

    cin >> n >> k;
    dp.assign(n+1, vector<int>(k+1, 0));
    stuff.resize(n+1);

    for (int i=1; i<n+1; ++i)
    {
        int weight, value;
        cin >> weight >> value;
        stuff[i] = {weight, value};
    }

    for (int i=1; i<n+1; ++i)
    {
        for (int j=1; j<k+1; ++j)
        {
            if (j - stuff[i].first < 0)
            {
                dp[i][j] = dp[i-1][j];
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - stuff[i].first] + stuff[i].second);
            }
        }
    }

    cout << dp[n][k] << endl;
    return 0;
}

/*
i번째 물건을 넣은 배낭의 수용가능 무게가 j일 때의 최대 가치
*/