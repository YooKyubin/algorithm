#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

#define _INF (200 * 100'000)
#define INF _INF

using namespace std;

struct Node
{
    int to;
    int weight;

    bool operator>(const Node& other) const
    {
        if (weight == other.weight)
        {
            return to > other.to;
        }
        return weight > other.weight;
    }
};

vector<int> ComputeDistance(vector<vector<Node>>& graph, int start)
{
    vector<int> distance(graph.size(), INF);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, 0});
    distance[start] = 0;
    
    while (!pq.empty())
    {
        Node curr = pq.top();
        pq.pop();

        if (distance[curr.to] < curr.weight)
        {
            continue;
        }

        for (Node& next : graph[curr.to])
        {
            int nextWeight = next.weight + curr.weight;

            if (distance[next.to] < nextWeight)
            {
                continue;   
            }

            distance[next.to] = nextWeight;
            pq.push({next.to, nextWeight});
        }
    }

    return distance;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;

    vector<vector<Node>> graph(n + 1, vector<Node>());
    for (auto& fare : fares)
    {
        int src = fare[0];
        int dst = fare[1];
        int weight = fare[2];

        graph[src].push_back({dst, weight});
        graph[dst].push_back({src, weight});
    }

    vector<int> distanceStart = ComputeDistance(graph, s);
    vector<int> distanceA = ComputeDistance(graph, a);
    vector<int> distanceB = ComputeDistance(graph, b);


    int minDist = INF;
    for (int i=1; i<=n; ++i)
    {
        minDist = min(minDist, distanceStart[i] + distanceA[i] + distanceB[i]);
    }

    answer = minDist;

    return answer;
}


int main()
{
    int n = 6;
    int s = 4;
    int a = 6;
    int b = 2;
    vector<vector<int>> fares = 
    {{4, 1, 10}, {3, 5, 24}, {5, 6, 2}, {3, 1, 41}, {5, 1, 24}, {4, 6, 50}, {2, 4, 66}, {2, 3, 22}, {1, 6, 25}};

    cout << solution(n, s, a, b, fares) << endl;

    // priority_queue<int, vector<int>, less<int>> pq;
    // pq.push(0);
    // pq.push(1);
    // pq.push(4);
    // pq.push(3);

    // cout << pq.top() << endl;

    return 0;
}