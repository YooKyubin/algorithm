#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<pair<int, int>> walk;
vector<pair<int, int>> bike;
vector<vector<int>> memo;

int max(int a, int b) { return a > b ? a : b; }

int dp(int idx, int time)
{
    if (idx == n)
        return 0;

        

    if (memo[idx][time] != -1)
        return memo[idx][time];

    int walkVal = -INT32_MAX;
    int bikeVal = -INT32_MAX;
    
    if (time + walk[idx].first <= k)
    {
        walkVal = dp(idx+1, time + walk[idx].first) + walk[idx].second;
    }
    if (time + bike[idx].first <= k)
    {
        bikeVal = dp(idx+1, time + bike[idx].first) + bike[idx].second;
    }

    return memo[idx][time] = max(walkVal, bikeVal);
}

int main() 
{
    cin >> n >> k;
    
    walk.resize(n);
    bike.resize(n);
    memo.assign(n, vector<int>(k+1, -1));

    for(int i=0; i<n; ++i)
    {
        cin >> walk[i].first >> walk[i].second;
        cin >> bike[i].first >> bike[i].second;
    }

    int maxVal = dp(0, 0);

    cout << maxVal << endl;
    return 0;
}