#include <iostream>
#include <vector>
#include <string>
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
    vector<int> indegree(n + 1, 0);
    vector<int> durations(n + 1);
    vector<vector<int>> graph(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        int duration;
        int numProdecessor;
        cin >> duration >> numProdecessor;

        durations[i] = duration;
        indegree[i] += numProdecessor;

        for (int j = 0; j < numProdecessor; ++j)
        {
            int src;
            cin >> src;
            graph[src].push_back(i);
        }
    }

    vector<int> dist(n + 1, 0);

    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
            dist[i] = durations[i];
        }
    }

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (int next : graph[curr])
        {
            --indegree[next];
            dist[next] = max(dist[next], dist[curr] + durations[next]);

            if (indegree[next] == 0)
            {
                q.push(next);
            }
        }
    }

    cout << *(max_element(dist.begin(), dist.end())) << endl;

    return 0;
}