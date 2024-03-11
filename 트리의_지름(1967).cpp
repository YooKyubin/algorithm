#include <iostream>
#include <vector>

using namespace std;

int n;
int start = 1;
int maxDist = 0;

vector<vector<pair<int, int>>> graph;

void dfs(vector<int>& dist, int num)
{
    if (dist[num] > maxDist)
    {
        maxDist = dist[num];
        start = num;
    }

    for (auto next : graph[num])
    {
        int nextNum = next.first;
        int nextDist = next.second + dist[num];

        if (dist[nextNum] == -1)
        {
            dist[nextNum] = nextDist;
            dfs(dist, nextNum);
        }
    }
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    graph.resize(n+1);
    for (int i=0; i<n-1; ++i)
    {
        int a, b, dist;
        cin >> a >> b >> dist;
        graph[a].push_back({b, dist});
        graph[b].push_back({a, dist});
    }

    vector<int> test (n+1, -1);
    test[start] = 0;
    dfs(test, start);

    test.assign(n+1, -1);
    test[start] = 0;
    dfs(test, start);

    cout << maxDist << endl;

    return 0;
}