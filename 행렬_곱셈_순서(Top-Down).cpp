#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> matrix;
vector<vector<int>> memo;

int min(int a, int b) { return a < b ? a : b; }

int dp(int a, int b)
{
    if (memo[a][b] != INT32_MAX)
        return memo[a][b];

    if (b - a == 1)
        return memo[a][b] = 0;
    else if (b - a == 2)
        return matrix[a].first * matrix[b-1].first * matrix[b-1].second;

    int minVal = INT32_MAX;

    for (int i=a+1; i<b; ++i)
    {
        int dpA = dp(a, i);
        int dpB = dp(i, b);

        minVal = min( minVal, dpA + dpB + matrix[a].first * matrix[i].first * matrix[b-1].second );
    }

    return memo[a][b] = minVal;
}

int main()
{
    // freopen("../../input.txt", "r", stdin);

    cin >> n;
    matrix.resize(n);
    memo.resize(n+1, vector<int>(n+1, INT32_MAX));
    for (int i=0; i<n; ++i)
    {
        cin >> matrix[i].first >> matrix[i].second;
    }

    cout << dp(0, n) << endl;


    return 0;
}

