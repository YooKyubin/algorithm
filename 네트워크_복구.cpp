#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int n, m;
vector<vector<struct Edge>> graph;
vector<int> parent;

struct Edge
{
    int dest;
    int cost;

    bool operator>(Edge input)
    {
        return this->cost > input.cost;
    }
};

struct cmp
{
    bool operator()(int a, int b){
        return a > b;
    }
    bool operator()(Edge a, Edge b)
    {
        return a > b;
    }
};

void dijkstra(int start)
{
    priority_queue<Edge, vector<Edge>, cmp> pq;
    vector<int> dist(n+1, 10*(n-1) + 1); // 최대값 맞는지 잘 모르겟음..
    pq.push({1, 0});
    dist[1] = 0;
    
    while (!pq.empty())
    {
        int cur = pq.top().dest;
        int curCost = pq.top().cost;
        pq.pop();

        if (dist[cur] < curCost)
            continue;

        for (auto n : graph[cur])
        {
            int next = n.dest;
            int nextCost = curCost + n.cost;

            if (nextCost >= dist[next]) // 비용이 더 적을때만 갱신
                continue;

            dist[next] = nextCost;
            pq.push({next, nextCost});

            parent[next] = cur;
        }
    }

}

int main() 
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    graph.assign(n+1, vector<Edge>());
    parent.assign(n+1, 0);
    for (int i=0; i<m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    dijkstra(1);
    
    cout << n-1 << "\n";
    for (int i=2; i<n+1; ++i)
    {
        cout << i << " " << parent[i] << "\n";
    }

    return 0;
}