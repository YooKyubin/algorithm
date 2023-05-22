#include <iostream>
#include <vector>
#include <queue>

#define INF 300000 * 10 + 1

using namespace std;

struct Edge {
    int vertex;
    int weight;

    bool operator> (const Edge& input){
        return weight > input.weight;
    }
};

struct cmp{
    bool operator()(Edge& a, Edge& b){
        return a > b;
    }
};

int V, E, k;
vector<vector<Edge>> graph;
vector<int> dist;

void dijkstra(int start){
    priority_queue<Edge, vector<Edge>, cmp> pq;
    dist[start] = 0;

    pq.push( {start, 0} );

    while (!pq.empty()){
        int vertex = pq.top().vertex;
        int weight = pq.top().weight;
        pq.pop();
        
        if (dist[vertex] < weight) continue; // visited 역할
        for (auto edge : graph[vertex]){
            int next = edge.vertex;
            int nextWeight = weight + edge.weight;

            if (nextWeight < dist[next]){
                dist[next] = nextWeight;
                pq.push( {next, nextWeight} );
            }
        }

    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin >> V >> E;
    cin >> k;

    graph.assign(V+1, vector<Edge>());
    dist = vector<int> (V+1, INF);

    while (E--){
        int u, v ,w;
        cin >> u >> v >> w;
        graph[u].push_back( {v, w} );
    }

    dijkstra(k);

    for (int i=1; i < dist.size(); i++){
        if (dist[i] != INF) cout << dist[i] << "\n";
        else cout << "INF" << "\n";
    }

    return 0;
}