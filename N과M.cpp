#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<bool> visited;
vector<int> answer;

void dfs(int depth){
    if (depth == m) {
        for (int i: answer){
            cout << i << " ";
        } cout << "\n";
        return;
    }

    for (int i=1; i<n+1; i++){
        if (visited[i]) continue;
        visited[i] = true;
        answer.push_back(i);
        dfs(depth+1);
        answer.pop_back();
        visited[i] = false;
    }
}

int main() {
    cin >> n >> m;
    visited.assign(n+1, false);
    dfs(0);
    return 0;
}