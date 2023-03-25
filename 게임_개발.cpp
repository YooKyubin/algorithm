#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> graph;

struct Node{
    int inDegree;  // visited 만들기 귀찮으니까 in_degree가 0이면 접근 가능, 음수면 visited == true로 합시다.
    int buildTime;
    int totalTime;
    int maxParentTime = 0;
};

Node* nodes;

void dfs(int v){
    nodes[v].totalTime = nodes[v].maxParentTime + nodes[v].buildTime;

    for (auto& child : graph[v]){
        nodes[child].inDegree -= 1;
        nodes[child].maxParentTime = 
            nodes[child].maxParentTime > nodes[v].totalTime ?
                nodes[child].maxParentTime :
                nodes[v].totalTime;
    }
    for(int i=0; i < n; i++){
        if (nodes[i].inDegree == 0){
            nodes[i].inDegree -= 1;
            dfs(i);
        }
    }

}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    graph.assign(n, vector<int>());
    nodes = (Node*)malloc(sizeof(Node) * n);

    for(int i=0; i < n; i++){
        cin >> nodes[i].buildTime;

        while(true){
            int input;
            cin >> input;
            if (input == -1) break;

            graph[input-1].push_back(i); // 실제 인덱스와 입력이 일치하지 않음
            nodes[i].inDegree++;
        }
    }

    for(int i=0; i < n; i++){
        if (nodes[i].inDegree == 0){
            nodes[i].inDegree -= 1;
            dfs(i);
        }
    }

    for (int i=0; i < n; i++){
        cout << nodes[i].totalTime << endl;
    }

    return 0;
}