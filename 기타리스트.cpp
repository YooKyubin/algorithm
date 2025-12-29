#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int Adjust(vector<vector<int>>& memo, const vector<int>& intervals, int curr, int id, int m)
{
    if (memo[id][curr] != -2)
    {
        return memo[id][curr];
    }

    if (id == intervals.size())
    {
        return memo[id][curr] = curr;
    }

    int interval = intervals[id];

    int lastVolume = -1;
    if (curr + interval <= m)
    {
        int ret = Adjust(memo, intervals, curr + interval, id + 1, m);
        lastVolume = std::max(lastVolume, ret);
    }

    if (curr - interval >= 0)
    {
        int ret = Adjust(memo, intervals, curr - interval, id + 1, m);
        lastVolume = std::max(lastVolume, ret);
    }

    return memo[id][curr] = lastVolume;
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, s, m;
    cin >> n >> s >> m;

    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -2));
    vector<int> intervals(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> intervals[i];
    }

    cout << Adjust(memo, intervals, s, 0, m) << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    // freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, s, m;
    cin >> n >> s >> m;

    vector<int> intervals(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> intervals[i];
    }

    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][s] = true;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m + 1; ++j)
        {
            if (dp[i][j])
            {
                if (j + intervals[i] <= m)
                {
                    dp[i+1][j + intervals[i]] = true;
                }
                if (j - intervals[i] >= 0)
                {
                    dp[i+1][j - intervals[i]] = true;
                }
            }
        }
    }

    int maxVolume = -1;
    for (int i = m; i >= 0; --i)
    {
        if (dp[n][i])
        {
            maxVolume = i;
            break;
        }
    }

    cout << maxVolume << endl;

    return 0;
}