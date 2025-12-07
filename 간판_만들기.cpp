#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

const string target = "UOSPC";
const long long maxCost = 1'000'000'000LL * 5 + 1;

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);


    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    string moduleString;
    cin >> moduleString;

    vector<long long> cost(n);
    cost.resize(n, 0);
    for (int i = 0; i < n; ++i)
    {
        cin >> cost[i];
    }

    vector<long long> dp(6, maxCost);
    dp[0] = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 1; j < 6; ++j)
        {
            if (moduleString[i] == target[j - 1])
            {
                dp[j] = min(dp[j], dp[j-1] + cost[i]);
            }
        }
    }

    if (dp.back() == maxCost)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << dp.back() << endl;
    }

    return 0;
}