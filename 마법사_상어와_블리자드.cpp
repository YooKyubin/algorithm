#include <iostream>
#include <vector>

using namespace std;

int m, n;
int score = 0;
pair<int, int> shark;
vector<vector<int>> location;
vector<int> blizardDirX = {0, -1, 1, 0, 0 };
vector<int> blizardDirY = {0, 0, 0,-1, 1 };

void makeLocation(int size){
    location.assign(size, vector<int>(size, 0));
    vector<int> dx = { 0, 1, 0, -1};
    vector<int> dy = { 1, 0, -1, 0};

    int i = 0;
    int j = -1;
    int arrIdx = n*n-2;
    int moveIdx = 0;
    int straightCnt = n * 2;
    while(straightCnt >= 3) { // 첫번째로 straight이 1이되는 경우까지만
        int straight = straightCnt / 2;
        while (straight--){
            i += dx[moveIdx];
            j += dy[moveIdx];
            location[i][j] = arrIdx;
            arrIdx--;
        }
        moveIdx = (moveIdx + 1) % 4;
        straightCnt--;
    }
}

void mat2arr2(vector<vector<int>>& mat, vector<int>& array){
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i == shark.first && j == shark.second) continue;
            int arrIdx = location[i][j];
            array[arrIdx] = mat[i][j];
        }
    }
}

void mat2arr(vector<vector<int>>& mat, vector<int>& array){
    // 7 6 6 5 5 4 4 3 3 2 2 1
    vector<int> dx = { 0, 1, 0, -1};
    vector<int> dy = { 1, 0, -1, 0};

    int i = 0;
    int j = -1;
    int arrIdx = n*n-2;
    int moveIdx = 0;
    int straightCnt = n * 2;
    while(straightCnt >= 3) { // 첫번째로 straight이 1이되는 경우까지만
        int straight = straightCnt / 2;
        while (straight--){
            i += dx[moveIdx];
            j += dy[moveIdx];
            // cout << i << " " << j << ": " << arrIdx << endl;
            // cout << "straightCnt " << straightCnt << endl;
            array[arrIdx] = mat[i][j];
            arrIdx--;
        }
        moveIdx = (moveIdx + 1) % 4;
        straightCnt--;
    }
}

void blizard(int dir, int len, vector<int>& arr){
    int dirX = blizardDirX[dir];
    int dirY = blizardDirY[dir];

    for (int i=1; i<=len; i++){
        int x = shark.first + dirX * i;
        int y = shark.second + dirY * i;
        int arrIdx = location[x][y];
        if (arr.size() > arrIdx){
            arr[arrIdx] = 0;
        }
    }
}

bool explosion(vector<int>& arr){
    vector<int> scores(4, 0);
    vector<int> newArr;
    int arrIdx = 0;
    bool isExplosion = false;
    while (arrIdx < arr.size()){
        int curColor = arr[arrIdx++];
        int curCount = 1;
        if (curColor < 1) continue;
        while (arrIdx < arr.size()){
            if (arr[arrIdx] < 1){
                arrIdx++;
                continue;
            }
            else if (curColor == arr[arrIdx]){
                curCount++;            
                arrIdx++;
            }
            else {
                break;
            }
        }
        if (curCount < 4){
            while(curCount--){
                newArr.push_back(curColor);
            }
        }
        else{
            isExplosion = true;
            scores[curColor] += curCount;
        }
    }

    for (int i=1; i<4; i++){
        score += scores[i] * i;
    }
    arr = newArr;
    return isExplosion;
}

void change(vector<int>& arr){
    int arrIdx = 0;
    vector<int> newArr;
    while (arrIdx < arr.size()){
        int curColor = arr[arrIdx++];
        int curCount = 1;
        while (arrIdx < arr.size()) {
            if (curColor == arr[arrIdx]){
                curCount++;            
                arrIdx++;
            }
            else {
                break;
            }
        }
        if (newArr.size() >= n*n -1) break;
        newArr.push_back(curCount);
        if (newArr.size() >= n*n-1) break;
        newArr.push_back(curColor);
        if (newArr.size() >= n*n-1) break;
    }
    arr = newArr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    vector<int> d(m);
    vector<int> s(m);
    makeLocation(n);
    shark = { n/2, n/2 };

    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cin >> matrix[i][j];
        }
    }

    for (int i=0; i<m;i++){
        cin >> d[i] >> s[i];
    }

    vector<int> array(n*n, 0);

    mat2arr2(matrix, array);

    for (int i=0; i<m; i++){
        int dir = d[i];
        int len = s[i];
        blizard(dir, len, array);
        bool flag = true;
        while(flag){
            flag = explosion(array);
        }
        change(array);

    }
    
    cout << score << endl;

    return 0;
}

/*

*/