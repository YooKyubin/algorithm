#include <iostream>
#include <unordered_map>

using namespace std;

struct Node{
    string name;
    string root;
    int depth;
    int size;
};

unordered_map<string, Node> Network;

Node makeSet(string name){
    Node x;
    x.name = name;
    x.root = name;
    x.depth = 0;
    x.size = 1;

    return x;
}

string findSet(const string& person){
    Node& x = Network[person];
    if (x.root == x.name){
        return x.name;
    }
    else{
        x.root = findSet(x.root);
        return x.root;
    }
}

void unionSet(string p1, string p2){
    p1 = findSet(p1);
    p2 = findSet(p2);

    Node& x = Network[p1];
    Node& y = Network[p2];

    if (x.name == y.name) return;

    if (x.depth > y.depth){
        y.root = x.name; // y.root = x.root;
        x.size += y.size;
    }
    else if (x.depth < y.depth){
        x.root = y.name;
        y.size += x.size;
    }
    else{
        x.root = y.name;
        y.size += x.size;

        y.depth++;
    }
}

int main(){
    cin.tie(0);
	cin.sync_with_stdio(false);
	ios_base::sync_with_stdio(false);

    int n, f;

    cin >> n;
    while (n--){
        cin >> f;
        for (int i=0; i < f; i++){
            string p1, p2;
            cin >> p1 >> p2;
            
            if (Network.find(p1) == Network.end()) Network[p1] = makeSet(p1);
            if (Network.find(p2) == Network.end()) Network[p2] = makeSet(p2);
            unionSet(p1, p2);

            cout << Network[findSet(p1)].size << "\n";
        }
        Network.clear();
    }

    return 0;
}

/*
매번 돌면서 셀 필요없이 그 크기를 따로 저장하면 되지
루트로 가서 그 루트의 size를 가져오면 된다.
합치는 경우면 두개의 루트 노드가 각 size를 합친값을 새 루트노드에 넣으면 되는거잖아ㄴ
*/