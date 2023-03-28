#include <iostream>
#include <vector>
#include <cstring>
// #include <algorithm>

using namespace std;

int n, m;
int* indegree;
int* totalCount;
bool* isBasic;
vector<vector<int>> requiredParts;
// vector<pair<int, int>> basicParts;

void order(int parts, int number){ // number <= 2,147,483,647: int32_t로 표현 가능

    // if (isBasic[parts]){
    //     basicParts.push_back({ parts, number });
    //     return;
    // }

    for (int i=1; i < n+1; i++){
        if (requiredParts[parts][i] == 0) continue;
        
        totalCount[i] += number * requiredParts[parts][i];
        if (--indegree[i] == 0){
            order(i, totalCount[i]);
        }
    }
}

int main(){
    cin >> n;
    cin >> m;

    indegree = (int*)malloc( sizeof(int) * n+1 );
    totalCount = (int*)malloc( sizeof(int) * n+1 );
    memset(totalCount, 0, sizeof(int) * n+1 );
    isBasic = (bool*)malloc( sizeof(bool) * n+1 );
    memset(isBasic, 1, sizeof(bool) * n+1 );
    requiredParts.assign( n+1, vector<int>(n+1) );

    for (int i=0; i < m; i++){
        int x, y, k;
        cin >> x >> y >> k;
        requiredParts[x][y] = k;
        isBasic[x] = false;
        indegree[y] += 1;
    }

    order(n, 1);
    
    // sort(basicParts.begin(), basicParts.end());
    // for (auto i: basicParts){
    //     cout << i.first << " " << i.second << "\n";
    // }
    for (int i=1; i<n+1; i++){
        if (isBasic[i]) 
            cout << i << " " << totalCount[i] << "\n";
    }

    return 0;
}

/*
이게 왜이리 비효율적으로 보였나 했더니 
필요한 부품을 한번에 주문하지 않고 이부품 주문했다가 저 부품 주문했다 하면서 중복으로 같은 부품을 주문하는 호출이 생기니까
비효율적일 수 밖에 없었다.

필요 부품을 한번에 모아서 주문하기 위해 위상정렬이 필요함
그래야 주문했던 부품 또 주문할 일이 없음, 일은 모을 수 있을때까지 모았다가 한방에 처리하자
*/