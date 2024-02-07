#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
    int dest;
    int weight;
};

bool operator>(const Edge& a, const Edge& b)
{
    return a.weight > b.weight;
}

int n, m, x;

vector<vector<Edge>> go;
vector<vector<Edge>> back;

int max(int a, int b) { return a > b ? a : b; }

vector<int> dijkstra(vector<vector<Edge>>& edges)
{
    vector<int> dist(n+1, INT32_MAX);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push({x, 0});
    dist[x] = 0;

    while (!pq.empty())
    {
        int cur = pq.top().dest;
        int curWeight = pq.top().weight;
        pq.pop();

        if (dist[cur] > curWeight)
            continue;

        for (auto& e : edges[cur])
        {
            int next = e.dest;
            int nextWeight = e.weight + curWeight;

            if (nextWeight >= dist[next])
                continue;

            dist[next] = nextWeight;
            pq.push({next, nextWeight});
        }
    }

    return dist;
}

int main()
{
    // freopen("../../input.txt", "r", stdin);

    cin >> n >> m >> x;
    go.resize(n+1);
    back.resize(n+1);

    for (int i=0; i<m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        go[a].push_back({b, c});
        back[b].push_back({a, c});
    }

    vector<int> goDist = dijkstra(go);
    vector<int> backDist = dijkstra(back);

    int maxTime = 0;
    for (int i=1; i<n+1; ++i)
    {
        maxTime = max(maxTime, goDist[i] + backDist[i]);
    }

    cout << maxTime << endl;

    return 0;
}