#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<bool> CheckVisited(const vector<vector<int>>& graph, int start)
{
    queue<int> q;
    vector<bool> visited(graph.size(), false);

    q.push(start);
    visited[start] = true;

    while(!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (int next : graph[curr])
        {
            if (visited[next])
            {
                continue;
            }

            visited[next] = true;
            q.push(next);
        }
    }

    return visited;
}

bool CanVisitAll(const vector<vector<int>>& greater, const vector<vector<int>>& less, int start)
{
    vector<vector<bool>> visited(2);
    visited[0] = CheckVisited(greater, start); 
    visited[1] = CheckVisited(less, start); 

    bool result = true;
    for (int i = 1; i < greater.size(); ++i)
    {
        result &= visited[0][i] || visited[1][i];
    }

    return result;
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int n, m;
    cin >> n >> m;

    vector<vector<int>> greater(n + 1);
    vector<vector<int>> less(n + 1);

    for (int i = 0 ; i < m; ++i)
    {
        int src, dst;
        cin >> src >> dst;

        greater[src].push_back(dst);
        less[dst].push_back(src);
    }

    int answer = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (CanVisitAll(greater, less, i))
        {
            ++answer;
        }
    }

    cout << answer << endl;

    return 0;
}