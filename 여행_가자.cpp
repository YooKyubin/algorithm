#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m;
int* depth;
int* root;

int findSet(int x){
    if (root[x] == x){
        return x;
    }
    else {
        return root[x] = findSet(root[x]);
    }
}

void unionSet(int x, int y){
    x = findSet(x);
    y = findSet(y);

    if (x == y) return;

    if (depth[x] > depth[y]){
        root[y] = x;
    }
    else if(depth[x] < depth[y]){
        root[x] = y;
    }
    else{
        root[x] = y;
        depth[y]++;
    }
}

int main(){
    cin.tie(0);
	cin.sync_with_stdio(false);
	ios_base::sync_with_stdio(false);

    cin >> n;
    cin >> m;
    depth = (int*)malloc(sizeof(int) * n);
    root = (int*)malloc(sizeof(int) * n);
    vector<int> plan(m);

    for(int i=0; i < n; i++){
        root[i] = i;
    }

    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            int temp;
            cin >> temp;

            if (temp == 1){
                unionSet(i, j);
            }
        }
    }
    
    for(int i=0; i < m; i++){
        int temp;
        cin >> temp;
        plan[i] = temp-1;
    }


    int target = findSet(plan[0]);
    string answer = "YES";
    for (int i=1; i < m; i++){
        if (target != findSet(plan[i])){
            answer = "NO";
            break;
        }
    }

    cout << answer << endl;
    return 0;
}