#include <iostream>
#include <vector>

#define INF 10000000

using namespace std;

int n;
vector<vector<int>> weights;
vector<vector<int>> dp;
int start = 0;

int min(int a, int b) { return a < b ? a : b; }

int TSP(int cur, int visited)
{
    if (visited == (1 << n) - 1)
        return weights[cur][0] == 0 ? INF : weights[cur][0];

    if (dp[cur][visited] != 0)
        return dp[cur][visited];
    
    int ret = INF;
    for (int i=0; i<n; ++i)
    {
        if (weights[cur][i] == 0)
            continue;

        if (visited & 1 << i)
            continue;

        ret = min(ret, TSP(i, visited | 1 << i) + weights[cur][i]);
    }

    return dp[cur][visited] = ret;
}

int main() 
{
    cin >> n;
    weights.resize(n, vector<int>(n));
    dp.resize(n, vector<int>(1 << n, 0));
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            int weight;
            cin >> weight;
            weights[i][j] = weight;
        }
    }

    cout << TSP(start, 1 << start) << endl;

    return 0;
}