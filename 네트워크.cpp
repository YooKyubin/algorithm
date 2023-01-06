#include <iostream>
#include <string>
#include <vector>

using namespace std;

int dfs(int start, const vector<vector<int>>& computers, vector<bool>& visited){

    visited[start] = true;
    for(int i=0; i < computers.size(); i++){
        if (!visited[i] && i != start && computers[start][i] == 1){
            visited[i] = true;
            dfs(i, computers, visited);
        }
        
    }

    return 1; 
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    vector<bool> visited(n, false);
    vector<vector<int>> graph;
    
    for (int i=0; i < n; i++){
        if (!visited[i]){
            answer += dfs(i, computers, visited);
        }
    }

    return answer;
}

int main() {
    int n = 3;
    vector<vector<int>> computers {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}};
    // vector<vector<int>> computers {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};

    cout << solution(n, computers) << endl;
    return 0;
}