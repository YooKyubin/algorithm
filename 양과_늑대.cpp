#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct node {
    int left;
    int right;
    int value;
};

void dfs(const vector<node>& graph, int v, vector<bool>& visited, int& answer) {
    if (visited[v]){
        return;
    }
    visited[v] = true;
    int sheep = 0;
    int wolf = 0;

    for (int i=0; i < graph.size(); i++){
        if (v & (1 << i)){
            sheep += graph[i].value ^ 1;
            wolf += graph[i].value;
        }
    }

    if (sheep <= wolf) {
        return;
    }

    answer = answer < sheep ? sheep : answer;

    for (int i=0; i < graph.size(); i++){
        if (v & (1 << i)){
            if (graph[i].left != -1){
                dfs(graph, v | (1 << graph[i].left), visited, answer);
            }
            if (graph[i].right != -1){
                dfs(graph, v | (1 << graph[i].right), visited, answer);
            }
        }
    }

}

int solution(vector<int> info, vector<vector<int>> edges) {
    int answer = 0;
    vector<bool> visited( 1<<info.size() );
    vector<node> graph(info.size(), {-1,-1,0});
    queue<int> q;
    for (auto i: edges) {
        int p = i[0];
        int c = i[1];
        if (graph[p].left == -1){
            graph[p].left = c;
        }
        else{
            graph[p].right = c;
        }
    }
    for (int i=0; i < info.size(); i++){
        graph[i].value = info[i];
    }

    for (int i=0; i < graph.size(); i++){
        node n = graph[i];
        printf("node: %d, left: %d, right: %d, val: %d \n", i, n.left, n.right, n.value);
    }

    dfs(graph, 1, visited, answer);
    return answer;
}

int main() {
    vector<int> info {0,1,0,1,1,0,1,0,0,1,0};
    vector<vector<int>> edges {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{3,7},{4,8},{6,9},{9,10}};
    // vector<int> info {0,0,1,1,1,0,1,0,1,0,1,1};
    // vector<vector<int>> edges {{0,1},{1,2},{1,4},{0,8},{8,7},{9,10},{9,11},{4,3},{6,5},{4,6},{8,9}};
    cout << solution(info, edges) << endl;
    return 0;
}