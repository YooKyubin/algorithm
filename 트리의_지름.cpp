#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<pair<int, int>>> graph; 

void dfs(int cur, vector<int>& dist)
{
    for (auto node : graph[cur])
    {
        int next = node.first;
        int nextDist = node.second;

        if (dist[next] != -1)
            continue;

        dist[next] = dist[cur] + nextDist;
        dfs(next, dist);
    }
}

pair<int, int> findFar(int start)
{
    vector<int> dist(n+1, -1);
    dist[start] = 0;
    dfs(start, dist);
    pair<int, int> ret = {0, 0};
    for (int i=1; i<=n; ++i)
    {
        if (ret.second < dist[i])
        {
            ret = {i, dist[i]};
        }
    }
    return ret;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    graph.resize(n+1);
    for (int i=1; i<=n; ++i)
    {
        int from;
        cin >> from;
        int dest, weight;
        while (true)
        {
            cin >> dest;
            if (dest == -1)
                break;
            cin >> weight;

            graph[from].push_back({dest, weight});
        }
    }

    pair<int, int> far = findFar(1);
    pair<int, int> ans = findFar(far.first);

    cout << ans.second << endl;

    return 0;
}