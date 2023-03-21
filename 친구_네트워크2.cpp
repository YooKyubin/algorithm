#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> depth;
vector<int> root;
vector<int> length;

unordered_map<string, int> Network;

void makeSet(int idx){
    root.push_back(idx);
    depth.push_back(0);
    length.push_back(1);
}

int findSet(int x){
    if (root[x] == x){
        return x;
    }
    else{
        return root[x] = findSet(root[x]);
    }
}

void unionSet(int x, int y){
    x = findSet(x);
    y = findSet(y);

    if (x == y) return;

    if (depth[x] > depth[y]){
        root[y] = x;
        length[x] += length[y];
    }
    else if(depth[x] < depth[y]){
        root[x] = y;
        length[y] += length[x];
    }
    else{
        root[x] = y;
        depth[y]++;
        length[y] += length[x];
    }
}


int main(){
    cin.tie(NULL);
	ios_base::sync_with_stdio(false);

    int n, f;

    cin >> n;
    for (int i=0; i<n; i++){
        cin >> f;
        int idx = 0;
        for (int i=0; i < f; i++){
            string p1, p2;
            cin >> p1 >> p2;
            
            if (Network.find(p1) == Network.end()){
                Network[p1] = idx++;
                makeSet(Network[p1]);
            } 
            if (Network.find(p2) == Network.end()){
                Network[p2] = idx++;
                makeSet(Network[p2]);
            }

            unionSet(Network[p1], Network[p2]);

            cout << length[findSet(Network[p1])] << "\n";
        }
        Network.clear();
        length.clear();
        depth.clear();
        root.clear();
    }

    return 0;
}

/*
노드 스트럭트를 만들어서 하는 것이 비효율 적인지 아닌지 확인
root같은건 string 으로 할것임 
이것도 안되면 root 도 int로 변경해서 사용
*/