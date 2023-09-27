#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct Node
{
    int num;
    int dist;
};

int n, m;
vector<vector<pair<int ,int>>> graph;
vector<int> indegree;

int start, arrival;
int maxDist = 0;

vector<int> forwardDist;

vector<vector<int>> parent;

int max(int a, int b) { return a > b ? a : b; }

void topologySort()
{
    queue<Node> q;
    q.push({start, 0});

    while(!q.empty())
    {
        int cur = q.front().num;
        int curDist = q.front().dist;
        q.pop();

        for (auto edge : graph[cur])
        {
            int next = edge.first;
            int nextDist = edge.second + curDist;

            // forwardDist[next] = max(forwardDist[next], nextDist);
            if (forwardDist[next] < nextDist)
            {
                forwardDist[next] = nextDist;
                parent[next].clear();
            }
            if (forwardDist[next] <= nextDist)
            {
                parent[next].push_back(cur);

            }
            --indegree[next];
            if (indegree[next] == 0)
                q.push({next, forwardDist[next]});
            
        }
    }
}

int findCritical()
{
    queue<int> q;
    q.push({arrival});
    vector<bool> visited(n+1, false);
    int cnt = 0;
    
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (auto next : parent[cur])
        {
            ++cnt;
            if (visited[next])
                continue;

            // cout << cur << " -> " << next << endl;
            visited[next] = true;
            q.push(next);
        }
    }

    return cnt;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin >> n;
    cin >> m;

    graph.resize(n+1);
    indegree.resize(n+1, 0);
    forwardDist.resize(n+1, 0);

    parent.resize(n+1);

    for (int i=0; i<m; ++i)
    {
        int dest, to, dist;
        cin >> dest >> to >> dist;
        graph[dest].push_back({to, dist});
        ++indegree[to];
    }
    cin >> start >> arrival;

    topologySort();
    maxDist = forwardDist[arrival];
    // for (int i=1; i<n+1; i++)
    // {
    //     cout << i << " -> " ;
    //     for (auto j : parent[i])
    //     {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }
    int criticalPath = findCritical();

    cout << maxDist << endl;
    cout << criticalPath << endl;

    return 0;
}