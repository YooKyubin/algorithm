#include <iostream>

using namespace std;

struct Node {
    bool isInit = false;
    int rank;
    int root;
};

Node* nodes;

void makeSet(int x){
    nodes[x].isInit = true;
    nodes[x].rank = 0;
    nodes[x].root = x;
}

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
    bool flag = false;

    cin >> n >> m;
    nodes = (Node*)malloc(sizeof(Node) * n);
    for (int i=0; i < m; i++){
        int v1, v2;
        cin >> v1 >> v2;
        
        // printf("v1: %d, v2: %d\n", nodes[v1].isInit, nodes[v2].isInit);
        
        if (flag) continue;

        if (!nodes[v1].isInit) makeSet(v1);
        if (!nodes[v2].isInit) makeSet(v2);

        if (findSet(v1) == findSet(v2)){
            answer = i + 1;
            flag = true;
        }
        
        unionSet(v1, v2);
    }
    cout << answer << endl;
    return 0;
}