#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> matrix;
vector<vector<int>> dp;

int min(int a, int b) { return a < b ? a : b; }

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    matrix.resize(n);
    dp.resize(n+1, vector<int>(n+1, 0));
    for (int i=0; i<n; ++i)
    {
        cin >> matrix[i].first >> matrix[i].second;
    }

    for (int interval=2; interval<n+1; ++interval)
    {
        for (int left=0; left+interval < n+1; ++left)
        {
            int right = left + interval; 
            int minVal = INT32_MAX;
            for (int mid = left+1; mid < right; ++mid)
            {
                minVal = min( minVal, dp[left][mid] + dp[mid][right] + matrix[left].first * matrix[mid].first * matrix[right-1].second);
            }

            dp[left][right] = minVal;
        }
    }

    cout << dp[0][n] << endl;
    return 0;
}