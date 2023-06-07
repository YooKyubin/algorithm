#include <iostream>
#include <vector>

using namespace std;

int v, e;
vector<vector<int>> graph;
vector<int> visited;

void dfs(int v) {
    visited[v] = true;
    for (int next : graph[v]){
        if (visited[next]) continue;
        dfs(next);
    }
}

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> v >> e;
    graph.assign(v+1, vector<int>());
    visited.assign(v+1, false);

    for (int i=0; i < e; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1);
    bool isSingle = true;
    for (int i=1; i < v+1; i++){
        if (!visited[i]) {
            isSingle = false;
            break;
        }
    }

    string answer = "NO";
    if (isSingle){
        int oddCount = 0;
        for (int i=1; i < v+1; i++){
            if (graph[i].size() % 2 != 0) oddCount++;
        }

        if (oddCount == 0 || oddCount == 2) answer = "YES";
    }

    cout << answer << endl;
    return 0;
}