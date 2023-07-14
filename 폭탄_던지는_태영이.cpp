#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> h;
vector<vector<int64_t>> bombs;
vector<vector<int64_t>> prefixSum;

bool OOB(int i, int j){
    return i < 0 || i >= n || j < 0 || j >=n;
}

void addPrefixSum(int i, int j, int64_t num){
    if (!OOB(i, j)){
        prefixSum[i][j] += num;
    }
}

int64_t getPrefixSum(int i, int j){
    if (!OOB(i, j)){
        return prefixSum[i][j];
    }
    else {
        return 0;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    h.assign(n, vector<int>(n));
    bombs.assign(n, vector<int64_t>(n));
    prefixSum.assign(n, vector<int64_t>(n));

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cin >> h[i][j];
        }
    }
    
    for (int i=0; i < n-(m)/2; i++){
        for(int j=0; j < n-(m)/2; j++){
            int64_t curPrefix = getPrefixSum(i-1, j) + getPrefixSum(i, j-1) + getPrefixSum(i, j) - getPrefixSum(i-1, j-1);
            int64_t bomb = h[i][j] - curPrefix;
            prefixSum[i][j] = h[i][j];
            addPrefixSum(i+m, j, -bomb);
            addPrefixSum(i, j+m, -bomb);
            addPrefixSum(i+m, j+m, bomb);
            
            bombs[i+m/2][j+m/2] -= bomb;
        }
    }

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout << bombs[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}