#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<vector<int>> graph(n+1);

    for (int i=0; i<n-1; ++i)
    {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> parent(n+1, 0);
    vector<bool> visited(n+1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (int next : graph[cur])
        {
            if (visited[next])
                continue;

            parent[next] = cur;
            visited[next] =true;
            q.push(next);
        }
    }

    for (int i=2; i<n+1; ++i)
    {
        cout << parent[i] << "\n";
    }
    return 0;
}