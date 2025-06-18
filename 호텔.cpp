#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    // freopen("../../input.txt", "r", stdin);

    int quota;
    int numCities;
    cin >> quota >> numCities;

    // <비용, 고객>
    vector<pair<int, int>> cities(numCities);
    int maxCustomer = 0;
    for (int i=0; i<numCities; ++i)
    {
        cin >> cities[i].first >> cities[i].second;
        maxCustomer = max(maxCustomer, cities[i].second);
    }

    // vector<vector<int>> dpTable(numCities, vector<int>(quota + maxCustomer + 1, 0));
    // dp[j] == j명의 고객을 늘리는데 필요한 최소 비용
    vector<int> dp(quota + maxCustomer + 1, quota);
    dp[0] = 0;
    for (const pair<int, int>& city : cities)
    {
        int cost = city.first;
        int people = city.second;

        for (int i=0; i <= quota + maxCustomer; ++i)
        {
            if (i < people)
            {
                continue;
            }

            dp[i] = min(dp[i], dp[i - people] + cost);
        }
    }

    cout << *min_element(dp.begin() + quota, dp.end()) << endl;

    for (auto i  : dp)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}