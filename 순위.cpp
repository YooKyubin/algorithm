#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int bfs(vector<vector<int>>& graph, int start){
    vector<bool> visited(graph.size()+1, false);
    queue<int> q;
    int count = 0;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i: graph[v]){
            if (!visited[i]) {
                q.push(i);
                visited[i] = true;
                count += 1;
            }
        }
    }
    return count;
}

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    vector<vector<int>> in(n+1);
    vector<vector<int>> out(n+1);
    for (auto i: results){
        in[i[0]].push_back(i[1]);
        out[i[1]].push_back(i[0]);
    }
    for (auto i: in){
        for (auto j: i){
            cout << j << " ";
        }cout << endl;
    }

    vector<pair<int, int>> count(n+1, {0,0});

    for (int i=0; i < n+1; i++){
        count[i].first = bfs(in, i);
        count[i].second = bfs(out, i);
    }

    for (auto i: count){
        cout << "in : " << i.first << ", out: " << i.second << endl;
        if (i.first + i.second == n-1){
            answer += 1;
        }
    }

    return answer;
}

int main() {
    int n = 5;
    vector<vector<int>> results {{4, 3}, {4, 2}, {3, 2}, {1, 2}, {2, 5}};
    cout << solution(n, results) << endl;
    return 0;
}

/*
위상정렬 아닌거같은데?
해당 노드의 in + out = n -1을 만족해야 순위 결정 가능
in, out 값을 구하는 방법은 그냥 일반 그래프 순회하는 방법으로도 가능할듯
*/