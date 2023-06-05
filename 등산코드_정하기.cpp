// 미해결
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int number;
    int intensity;

    bool operator > (const Node& a){
        return intensity > a.intensity;
    }
    Node(){}
    Node(int n, int i) {
        number = n;
        intensity = i;
    }
};

struct cmp {
    bool operator()(Node& a, Node& b){
        return a.intensity > b.intensity;
    }
};

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer;
    priority_queue< Node, vector<Node>, cmp > pq;
    vector<vector<Node>> graph(n+1, vector<Node>());
    vector<bool> isGate(n+1, false);
    vector<bool> isSummit(n+1, false);

    for (int gate: gates) isGate[gate] = true; 
    for (int summit: summits) isSummit[summit] = true; 

    for (auto path: paths){
        int a = path[0];
        int b = path[1];
        int len = path[2];
        Node nodeA(a, len); 
        Node nodeB(b, len);
        
        if ( !isSummit[a] && !isGate[b]) graph[a].push_back(nodeB);
        if ( !isSummit[b] && !isGate[a]) graph[b].push_back(nodeA);
    }
    
    return answer;
}

int main() {
    int n = 6;
    vector<vector<int>> paths {{1, 2, 3}, {2, 3, 5}, {2, 4, 2}, {2, 5, 4}, {3, 4, 4}, {4, 5, 3}, {4, 6, 1}, {5, 6, 1}};
    vector<int> gates {1, 3};
    vector<int> summits {5};
    for (auto i: solution(n, paths, gates, summits)) cout << i << " ";
    cout << endl;
    return 0;
}

/*
for (int i=0; i < graph.size(); i++){
        cout << i << ": ";
        for (int j=0; j < graph[i].size(); j++){
            cout << graph[i][j].intensity << " ";
        }
        cout << endl;
    }
*/