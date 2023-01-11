#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    int maxNum = 0;
    queue<int> q;
    vector<int> dist(n+1);
    vector<vector<int>> graph(n+1);
    for (auto e: edge){
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    for (int i=0; i < graph.size(); i++){
        cout << i << " : ";
        for (auto n: graph[i]){
            cout << n << " ";
        }
        cout << endl;
    }

    q.push(1);
    while (!q.empty()){
        int v = q.front();
        q.pop();

        for (int i: graph[v]){
            if (dist[i] == 0) {
                q.push(i);
                dist[i] = dist[v] + 1;
                maxNum = max(dist[i], maxNum);
            }
        }
    }
    for(int i: dist){
        cout << i << " ";
    }
    cout << endl;
    for(int i=2; i < dist.size()+1; i++){
        if (dist[i] == maxNum){
            answer++;
        }
    }


    return answer;
}

int main(){
    int n = 6;
    vector<vector<int>> edge { {3, 6}, {4, 3}, {3, 2}, {1, 3}, {1, 2}, {2, 4}, {5, 2} };
    cout << solution(n, edge) << endl;
    return 0;
}