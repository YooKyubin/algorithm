#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int to;
    int weight;
    bool isDouble;

    bool operator>(Node input)
    {
        return this->weight > input.weight;
    }
};

template <typename T>
struct cmp
{
    bool operator()(T a, T b)
    {
        return a > b;
    }
};

int n, m;
vector<vector<Node>> graph[3];

int min(int a, int b)
{
    return a < b ? a : b;
}

vector<int> dijkstra(int start)
{
    priority_queue<Node, vector<Node>, cmp<Node>> pq;
    vector<int> dist(n+1, INT32_MAX);
    pq.push({start, 0});
    dist[start] = 0;
    
    while (!pq.empty())
    {
        int cur = pq.top().to;
        int curWeight = pq.top().weight;
        pq.pop();

        if (curWeight > dist[cur])
            continue;

        for (auto n : graph[1][cur])
        {
            int next = n.to;
            int nextWeight = curWeight + n.weight;

            if (nextWeight >= dist[next])
                continue;

            dist[next] = nextWeight;
            pq.push({next, nextWeight});
        }
    }

    return dist;
}

vector<vector<int>> dijkstra2(int start)
{
    priority_queue<Node, vector<Node>, cmp<Node>> pq;
    vector<vector<int>> dist(2);
    dist[0] = vector<int>(n+1, INT32_MAX);
    dist[1] = vector<int>(n+1, INT32_MAX);
    pq.push({start, 0, true});
    dist[true][1] = 0;
    
    while (!pq.empty())
    {
        int cur = pq.top().to;
        int curWeight = pq.top().weight;
        bool curIsDouble = pq.top().isDouble;
        pq.pop();
        
        if (curWeight > dist[curIsDouble][cur])
            continue;

        for (auto n : graph[!curIsDouble * 2][cur])
        {
            int next = n.to;
            int nextWeight = curWeight + n.weight;

            if (nextWeight >= dist[!curIsDouble][next])
                continue;

            dist[!curIsDouble][next] = nextWeight;
            pq.push({next, nextWeight, !curIsDouble});
        }
    }

    return dist;
}

int main () 
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i=0; i<3; ++i)
        graph[i].assign(n+1, vector<Node>());

    while (m--)
    {
        int a, b;
        int weight;
        cin >> a >> b >> weight;
        for (int i=0; i<3; ++i)
        {
            graph[i][a].push_back({b, weight * 1 << i});
            graph[i][b].push_back({a, weight * 1 << i});
        }
    }

    vector<int> foxDist = dijkstra(1);
    vector<vector<int>> wolfDist = dijkstra2(1);
    
    int cnt = 0;
    for (int i=1; i<n+1; ++i)
    {
        if (min(wolfDist[0][i], wolfDist[1][i]) > foxDist[i])
        {
            ++cnt;
        }
    }

    cout << cnt << endl;
    return 0;
}