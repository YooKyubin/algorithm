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
vector<vector<pair<int, int>>> re_graph;
vector<int> indegree;
vector<int> re_indegree;
int start, arrival;
int maxDist = 0;

vector<int> forwardDist;
vector<int> reverseDist;

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
            int nextDist = edge.second;

            forwardDist[next] = max(forwardDist[next], curDist + nextDist);
            --indegree[next];
            if (indegree[next] == 0)
                q.push({next, forwardDist[next]});
            
        }
    }
}

int findCritical()
{
    queue<Node> q;
    q.push({arrival, 0});
    vector<bool> visited(n+1, false);
    int cnt = 0;
    
    while(!q.empty())
    {
        int cur = q.front().num;
        int curDist = q.front().dist;
        q.pop();

        for (auto edge : re_graph[cur])
        {
            int next = edge.first;
            int nextDist = edge.second + curDist;
            
            if (forwardDist[next] + nextDist == maxDist)
            {
                ++cnt;
                // cout << cur << "->" << next << endl;
                if(visited[next])
                    continue;
                
                visited[next] = true;
                q.push({next, nextDist});
            }

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
    re_graph.resize(n+1);

    indegree.resize(n+1, 0);
    re_indegree.resize(n+1, 0);

    forwardDist.resize(n+1, 0);
    reverseDist.resize(n+1, 0);

    for (int i=0; i<m; ++i)
    {
        int dest, to, dist;
        cin >> dest >> to >> dist;
        graph[dest].push_back({to, dist});
        ++indegree[to];

        re_graph[to].push_back({dest, dist});
        ++re_indegree[dest];

    }
    cin >> start >> arrival;

    topologySort();
    maxDist = forwardDist[arrival];
    int criticalPath = findCritical();

    cout << maxDist << endl;
    cout << criticalPath << endl;

    return 0;
}