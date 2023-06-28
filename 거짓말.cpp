#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> root;
vector<vector<int>> partys;

int findSet(int x){
    if (root[x] == x){
        return x;
    }
    else{
        return root[x] = findSet(root[x]);
    }
}

void unionSet(int x, int y){
    int nx, ny;
    nx = findSet(x);
    ny = findSet(y);

    if (nx == ny) return;

    if (nx == 0 || ny == 0){
        root[nx] = 0;
        root[ny] = 0;
    }
    else {
        root[nx] = ny;
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
        
    // 1번째 줄 입력
    cin >> n >> m;
    root.assign(n+1, 0);
    partys.assign(m, vector<int>(0));
    for (int i=0; i<n+1; i++){
        root[i] = i;
    }

    // 2번째 줄 입력
    int repeat;
    cin >> repeat;
    for (int i=0; i<repeat; i++){
        int temp;
        cin >> temp;
        root[temp] = 0; // 진실을 아는 그룹은 0이 항상 root 가 되도록 한다.
    }

    // 3번째 줄 부터 입력
    for (int i=0; i<m; i++){
        int temp;
        cin >> temp;
        partys[i].assign(temp, 0);
        for (int j=0; j<temp; j++){
            cin >> partys[i][j];
        }
        for (int j=0; j<temp-1; j++){
            unionSet(partys[i][j], partys[i][j+1]);
        }
    }
    
    int answer = m;
    for (int i=0; i<m; i++){
        for (int j=0; j<partys[i].size(); j++){
            if (findSet(partys[i][j]) == 0){
                answer -= 1;
                break;
            }
        }
    }
    cout << answer << endl;

    return 0;
}