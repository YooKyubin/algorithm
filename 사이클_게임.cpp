/*
입력을 끝까지 받지 않고 사이클 완성되었을 때 break; 하면 훨씬 빨리 프로그램이 끝나긴함
당연하지만 isInit같은 변수 안쓰고 그냥 전부다 초기화하면 변수 하나가 줄어서 그런지 메모리도 더 적었음
*/
#include <iostream>

using namespace std;

struct Node {
    int rank;
    int root;
};

Node* nodes;

int findSet(int x){
    if (x == nodes[x].root){
        return x;
    }
    else {
        return nodes[x].root = findSet(nodes[x].root);
    }
}

void unionSet(int x, int y){
    x = findSet(x);
    y = findSet(y);

    if (x == y) return;

    if (nodes[x].rank > nodes[y].rank){
        nodes[y].root = x;
    }
    else if (nodes[x].rank < nodes[y].rank){
        nodes[x].root = y;
    }
    else {
        nodes[x].root = y;
        nodes[y].rank++;
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n, m;
    int answer = 0;

    cin >> n >> m;
    nodes = (Node*)malloc(sizeof(Node) * n);
    for (int i =0; i<n; i++){
        nodes[i].rank = 0;
        nodes[i].root = i;
    }

    for (int i=0; i < m; i++){
        int v1, v2;
        cin >> v1 >> v2;
        
        // isCycle
        if (findSet(v1) == findSet(v2)){
            answer = i + 1;
        }
        
        unionSet(v1, v2);
    }
    cout << answer << endl;
    return 0;
}