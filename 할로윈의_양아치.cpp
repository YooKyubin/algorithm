#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
vector<int> candys;
vector<int> head;
vector<int> numFriends;
vector<vector<int>> dp;

int max(int a, int b) { return a > b ? a : b; }

void Init()
{
    for (int i=0; i<=n; ++i)
    {
        head[i] = i;
    }
}

int Find(int x)
{
    if (head[x] == x)
        return x;

    return head[x] = Find(head[x]);
}

void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);

    if (x == y)
        return;

    head[x] = y;
    candys[y] += candys[x];
}

void CalDP(int num, int candy)
{
    dp.push_back(vector<int>(k, 0));
    int curIdx = (int)dp.size()-1;

    for (int i=0; i<k; ++i)
    {
        // dp[curIdx][i] = max(dp[curIdx-1][i], dp[curIdx][i-1]);

        // if (i >= num)
        //     dp[curIdx][i] = max(dp[curIdx][i], dp[curIdx - 1][i - num] + candy);

        if (i - num < 0)
        {
            dp[curIdx][i] = dp[curIdx-1][i];
        }
        else
        {
            dp[curIdx][i] = max(dp[curIdx-1][i], dp[curIdx-1][i - num] + candy);
        }
    }

}

int main()
{
    freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    candys.resize(n+1);
    head.resize(n+1);
    numFriends.resize(n+1, 0);
    dp.push_back(vector<int>(k, 0));

    for (int i=1; i<n+1; ++i)
    {
        cin >> candys[i];
    }

    Init();

    for (int i=0; i<m; ++i)
    {
        int a, b;
        cin >> a >> b;

        Union(a, b);
    }

    for (int i=1; i<n+1; ++i)
    {
        ++numFriends[Find(i)];
    }

    for (int i=1; i<n+1; ++i)
    {
        if (numFriends[i] == 0)
            continue;

        CalDP(numFriends[i], candys[i]);
    }

    // for (int i=0; i<dp.size(); ++i)
    // {
    //     for (int j=0; j<dp[i].size(); ++j)
    //     {
    //         cout << dp[i][j] << "\t";
    //     }
    //     cout << endl;
    // }

    cout << dp.back().back() << endl;

    return 0;
}