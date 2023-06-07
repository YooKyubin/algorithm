#include <iostream>
#include <vector>

using namespace std;

int v, e;
vector<int> edgeCount;
vector<int> head;
vector<int> depth;

int find(int x){
    if (head[x] == x) return x;
    else return head[x] = find(head[x]);
}

void Union(int x, int y){
    x = find(x);
    y = find(y);

    if (x == y) return;

    if (depth[x] < depth[y]){
        head[x] = y;
    }
    else if (depth[x] > depth[y]){
        head[y] = x;
    }
    else {
        head[x] = y;
        depth[y]++;
    }
}

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> v >> e;
    edgeCount.assign(v+1, 0);
    head.assign(v+1, 0);
    for (int i=0; i<v+1; i++) head[i] = i;
    depth.assign(v+1, 0);

    for (int i=0; i < e; i++){
        int a, b;
        cin >> a >> b;
        edgeCount[a]++;
        edgeCount[b]++;
        Union(a, b);
    }
    
    string answer = "NO";
    bool isSingle = true;
    for (int i=1; i < v; i++){
        if (find(i) != find(i+1)) isSingle = false;
    }

    if (isSingle){
        int oddCount = 0;
        for (int i=1; i < v+1; i++){
            if (edgeCount[i] % 2 != 0) oddCount++;
        }
        if (oddCount == 0 || oddCount == 2) answer = "YES";
    }

    cout << answer << endl;
    return 0;
}