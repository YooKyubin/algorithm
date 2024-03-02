#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) { return a > b ? a : b; }

int n, m;
vector<vector<int>> board;

int main()
{
    // freopen("../../input.txt", "r", stdin);

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    board.resize(n, vector<int>(m));
    vector<vector<int>> dp(n, vector<int>(m));
    for(int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            cin >> board[i][j];
        }
    }

    // dp init
    dp[0][0] = board[0][0];
    for (int i=1; i<m; ++i)
    {
        dp[0][i] = dp[0][i-1] + board[0][i];
    }

    for (int i=1; i<n; ++i)
    {
        vector<int> right(m, 0);
        vector<int> left(m, 0);

        right[0] = board[i][0] + dp[i-1][0];
        for (int j=1; j<m; ++j)
        {
            right[j] = board[i][j] + max(right[j-1], dp[i-1][j]);
        }

        left[m-1] = board[i][m-1] + dp[i-1][m-1];
        for (int j=m-2; j>=0; --j)
        {
            left[j] = board[i][j] + max(left[j+1], dp[i-1][j]);
        }

        for (int j=0; j<m; ++j)
        {
            dp[i][j] = max(left[j], right[j]);
        }
    }

    cout << dp[n-1][m-1] << endl;
    return 0;
}