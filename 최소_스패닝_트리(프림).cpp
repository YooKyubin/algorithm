#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
    int to;
    int weight;

    bool operator>(Edge& input)
    {
        return this->weight > input.weight;
    }
};

bool operator>(const Edge& a, const Edge& b)
{
    return a.weight > b.weight;
}

int v, e;
vector<vector<Edge>> graph;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> v >> e;
    graph.resize(v+1);
    for (int i=0; i<e; ++i)
    {
        int a, b, weight;
        cin >> a >> b >> weight;
        graph[a].push_back({b, weight});
        graph[b].push_back({a, weight});
    }
    
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    vector<bool> visited(v+1, false);
    int totalCost = 0;
    vector<int> MST;
    pq.push({1, 0});
    
    while(!pq.empty())
    {
        int cur = pq.top().to;
        int curWeight = pq.top().weight;
        pq.pop();

        if (visited[cur])
            continue;

        MST.push_back(cur);
        totalCost += curWeight;
        visited[cur] = true;

        if (MST.size() == v)
            break;

        for (Edge e : graph[cur])
        {
            int next = e.to;
            int nextWeight = e.weight;

            if (visited[next])
                continue;

            pq.push(e);
        }

    }

    cout << totalCost << endl;
    return 0;
}