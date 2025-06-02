#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> MakeGraph(int n, const vector<vector<int>>& edge)
{
    vector<vector<int>> graph(n+1);
    for (const vector<int>& e : edge)
    {
        int src = e[0];
        int dst = e[1];

        graph[src].push_back(dst);
        graph[dst].push_back(src);
    }

    return graph;
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    const int start_node = 1;

    vector<vector<int>> graph = MakeGraph(n, edge);

    vector<int> distances(n+1, -1);
    
    queue<int> bfs_queue;
    bfs_queue.push(1);
    distances[1] = 0;

    while (!bfs_queue.empty())
    {
        int node = bfs_queue.front();
        bfs_queue.pop();

        for (int next_node : graph[node])
        {
            if (distances[next_node] != -1)
            {
                continue;
            }

            distances[next_node] = distances[node] + 1;
            bfs_queue.push(next_node);
        }
    }

    sort(distances.begin(), distances.end(), greater<int>());

    const int max_distance = distances.front();
    for (int dist : distances)
    {
        if (dist != max_distance)
        {
            break;
        }

        ++answer;
    }

    return answer;
}

#include <iostream>

int main()
{
    int n = 6;
    vector<vector<int>> edge = 
    {{3, 6}, {4, 3}, {3, 2}, {1, 3}, {1, 2}, {2, 4}, {5, 2}};

    cout << solution(n ,edge) << endl;

    return 0;
}