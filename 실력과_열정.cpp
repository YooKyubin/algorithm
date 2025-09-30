#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    int a, b, k;
    cin >> a >> b >> k;

    const int sum = a + b;
    vector<int> mulCache(sum + 1, 0);
    for (int i =0 ; i< sum + 1; ++i)
    {
        mulCache[i] = (sum - i) * i;
    }
    // for (int i : mulCache)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    vector<vector<long long>> dp(n, vector<long long>(sum + 1, 0));
    for (int i = a + k; i < sum +1; ++i)
    {
        dp[0][i] = mulCache[i];
    }
    for (int i = a - k; i >= 0; --i)
    {
        dp[0][i] = mulCache[i];
    }

    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < sum+1; ++j)
        {
            long long preMax = INT32_MIN;

            for (int id = j + k; id < sum+1; ++id)
            {
                preMax = max(preMax, dp[i-1][id]);
            }
            for (int id = j - k; id >=0; --id)
            {
                preMax = max(preMax, dp[i-1][id]);
            }

            dp[i][j] = preMax + mulCache[j];
        }
    }

    cout << *max_element(dp.back().begin(), dp.back().end()) << endl;

    // for (auto& line : dp)
    // {
    //     for (int i : line)
    //     {
    //         cout << i << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}