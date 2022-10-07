#include<iostream>
#include<algorithm>

using namespace std;

int N;
int **map;
int blue = 0;
int white = 0;

void div_conq(int i, int j, int n);
bool check(int i, int j, int n);

int main(){
    cin >> N;
    map = (int**)malloc(sizeof(int*) * N);
    for(int i =0; i< N; i++){
        map[i] = (int*)malloc(sizeof(int) * N);
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j ++){
            cin >> map[i][j];
        }
    }

    div_conq(0, 0, N);

    cout << white << '\n' << blue << '\n';

    return 0;
}

void div_conq(int i, int j, int n){
    if(!check(i, j, n)){
        div_conq(i, j, n/2);
        div_conq(i, j+n/2, n/2);
        div_conq(i+n/2, j, n/2);
        div_conq(i+n/2, j+n/2, n/2);
    }
}

bool check(int i, int j, int n){
    int cnt=0;

    for(int y=i; y < i+n; y ++){
        for(int x=j; x < j+n; x ++){
            if (map[x][y] == 0){
                cnt = cnt + 1;
            }
        }
    }

    if(cnt == n*n){
        white++;
        return true;
    }else if (cnt == 0){
        blue++;
        return true;
    }else{
        return false;
    }
    
}