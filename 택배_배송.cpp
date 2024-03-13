#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct Node
{
    int num;
    int weight;
};

bool operator>(const Node& a, const Node& b)
{
    return a.weight > b.weight;   
}

int n, m;

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    vector<vector<Node>> graph(n+1, vector<Node>());

    for (int i=0; i<m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }
    // function<bool(Node, Node)> op = [](Node& a, Node& b) -> bool { return a.weight > b.weight; };
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<int> dist (n+1, INT32_MAX);
    pq.push({1, 0});
    dist[1] = 0;

    while (!pq.empty())
    {
        int cur = pq.top().num;
        int weight = pq.top().weight;
        pq.pop();

        if (dist[cur] < weight)
            continue;

        for (auto n : graph[cur])
        {
            int next = n.num;
            int nextWeight = weight + n.weight;


            if (dist[next] > nextWeight)
            {
                pq.push({next, nextWeight});
                dist[next] = nextWeight;
            }
        }

    }

    cout << dist[n] << endl;

}