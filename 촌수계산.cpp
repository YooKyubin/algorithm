#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int n;
    cin >> n;
    int src, dst;
    cin >> src >> dst;

    int m;
    cin >> m;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int parent, child;
        cin >> parent >> child;

        graph[parent].push_back(child);
        graph[child].push_back(parent);
    }

    const int INF = -1;
    queue<int> q;
    vector<int> dist(n + 1, INF);
    q.push(src);
    dist[src] = 0;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (int next : graph[curr])
        {
            if (dist[next] != INF)
            {
                continue;
            }

            dist[next] = dist[curr] + 1;
            q.push(next);
        }
    }

    cout << dist[dst] << endl;

    return 0;
}