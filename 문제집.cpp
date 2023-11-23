#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<vector<int>> edges;
vector<int> indegree;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    edges.resize(n+1, vector<int>());
    indegree.resize(n+1, 0);
    for (int i=0; i<m; ++i)
    {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        ++indegree[b];
    }

    priority_queue<int, vector<int>, greater<int>> q;
    for (int i=1; i<n+1; ++i)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int cur = q.top();
        q.pop();

        cout << cur << " ";

        for (int next : edges[cur])
        {
            --indegree[next];

            if (indegree[next] != 0)
                continue;

            q.push(next);
        }

    }
    cout << "\n";
    return 0;
}