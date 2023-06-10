/*
for (int i=0; i<l; i++)
    for (int j=0; j<l; j++)
        offsetX = pow(2,l) * i;
        offsetY = pow(2,l) * j;
offsetX = i / 2**l;
offsetY = j / 2**1;
1. x,y = (2**l - 1) - (x - offset) + offset, y;
2. x,y = x, (2**l - 1) - (y - offset) + offset;
3. x,y = (y - offsetY), -(x - offsetX) + (2**l - 1);
4. x,y = -(y - offsetY) + (2**l - 1), (x - offsetX);
5. x,y = -x + (2**l-1), y 후 1번 연산
6. x,y = x, -y + (2**l-1) 후 2번 연산
7. x,y = -y + (2**N - 1), x 후 4번 연산
8. x,y = y, -x + (2**N - 1) 후 3번 연산
*/

#include <iostream>
#include <vector>

#define Pos pair<int, int>

using namespace std;

int N, R, n;
vector<vector<int>> table;

int pow(int n, int exp){
    int res = 1;
    for (int i=0; i<exp; i++) res *= n;
    return res;
}

void printTable(){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout << table[i][j] << " ";
        } cout << endl;
    }
}

vector<vector<int>> func1(int l){
    vector<vector<int>> res(n, vector<int>(n, 0));
    int pow2l = pow(2,l);
    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            int offsetX = i - i % pow2l;
            int nextX = (pow2l - 1) - (i - offsetX) + offsetX;
            int nextY = j;
            res[nextX][nextY] = table[i][j];
        }
    }
    return res;
}
vector<vector<int>> func2(int l){
    vector<vector<int>> res(n, vector<int>(n, 0));
    int pow2l = pow(2,l);
    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            int offsetY = j - j % pow2l;
            int nextX = i;
            int nextY = (pow2l - 1) - (j - offsetY) + offsetY;
            res[nextX][nextY] = table[i][j];
        }
    }
    return res;
}
vector<vector<int>> func3(int l){
    vector<vector<int>> res(n, vector<int>(n, 0));
    int pow2l = pow(2,l);
    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            int offsetX = i - i % pow2l;
            int offsetY = j - j % pow2l;
            int nextX = (j - offsetY) + offsetX;
            int nextY = -(i - offsetX) + (pow2l - 1) + offsetY;
            res[nextX][nextY] = table[i][j];
        }
    }
    return res;
}
vector<vector<int>> func4(int l){
    vector<vector<int>> res(n, vector<int>(n, 0));
    int pow2l = pow(2,l);
    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            int offsetX = i - i % pow2l;
            int offsetY = j - j % pow2l;
            int nextX = -(j - offsetY) + (pow2l - 1) + offsetX;
            int nextY = (i - offsetX) + offsetY;
            res[nextX][nextY] = table[i][j];
        }
    }
    return res;
}
vector<vector<int>> func5(int l){
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            int nextX = -i + (n-1);
            int nextY = j;
            res[nextX][nextY] = table[i][j];
        }
    }
    table = res;
    res = func1(l);
    return res;
}
vector<vector<int>> func6(int l){
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            int nextX = i;
            int nextY = -j + (n-1);
            res[nextX][nextY] = table[i][j];
        }
    }
    table = res;
    res = func2(l);
    return res;
}
vector<vector<int>> func7(int l){
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            int nextX = j;
            int nextY = -i + (n-1);
            res[nextX][nextY] = table[i][j];
        }
    }
    table = res;
    res = func4(l);
    return res;
}
vector<vector<int>> func8(int l){
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            int nextX = -j + (n-1);
            int nextY = i;
            res[nextX][nextY] = table[i][j];
        }
    }
    table = res;
    res = func3(l);
    return res;
}



int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> N >> R;
    n = pow(2, N);
    // cout << n << endl;
    table.assign(n, vector<int>(n, 0));
    // vector<vector<int>> temp(n, vector<int>(n));
    for (int i=0; i < n; i++){
         for (int j=0; j < n; j++){
            cin >> table[i][j];
        }
    }
    
    for (int i=0; i < R; i++){
        int k, l;
        cin >> k >> l;

        switch(k){
            case 1: table = func1(l); break;
            case 2: table = func2(l); break;
            case 3: table = func3(l); break;
            case 4: table = func4(l); break;
            case 5: table = func5(l); break;
            case 6: table = func6(l); break;
            case 7: table = func7(l); break;
            case 8: table = func8(l); break;
        }
    }
    printTable();
    return 0;
}