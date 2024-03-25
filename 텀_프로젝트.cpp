#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int topologySort(vector<int>& graph, vector<int>& indegree)
{
    int ret = 0;
    queue<int> q;
    for (int i=1; i<graph.size(); ++i)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        ++ret;

        int next = graph[cur];
        --indegree[next];

        if (indegree[next] == 0)
        {
            q.push(next);
        }
    }
    return ret;
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> graph(n+1);
        vector<int> indegree(n+1, 0);
        for (int i=1; i<n+1; ++i)
        {
            cin >> graph[i];
            ++indegree[graph[i]];
        }

        cout << topologySort(graph, indegree) << "\n";
    }
    return 0;
}
