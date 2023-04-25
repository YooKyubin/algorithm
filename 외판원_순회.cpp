#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int cost;
int totalCost;
vector<vector<int>> w;
vector<bool> visited;

void dfs(int v, int depth){
    if (depth == n-1){
        // 마지막에서도 처음으로 돌아가는 길이 있는지 확인해야한다.
        if (w[v][0] == 0) return;

        cost += w[v][0];
        totalCost = min(cost, totalCost);
        cost -= w[v][0];
    }

    for (int i=0; i<n; i++){
        if (w[v][i] == 0 || visited[i]) continue;

        visited[i] = true;
        cost += w[v][i];
        dfs(i, depth+1);
        cost -= w[v][i];
        visited[i] = false;
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> n;
    
    totalCost = 10000001;
    cost = 0;
    w.assign(n, vector<int>(n));
    visited.assign(n, false);

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cin >> w[i][j];
        }
    }
    
    visited[0] = true;
    dfs(0, 0);

    cout << totalCost << endl;

    return 0;
}