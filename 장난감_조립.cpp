#include <iostream>
#include <vector>

using namespace std;

int n, m;

class Parts{
    public:
        bool isBasic = true;
        vector<int> requiredParts;
        int totalCount = 0;
        int indegree = 0;

        Parts(int n){
            requiredParts.assign(n+1, 0);
        }
};

vector<Parts> partsList;

void order(int p, int number){
    Parts& parts = partsList[p];
    
    // if (parts.isBasic){
    //     parts.totalCount = number;
    //     return;
    // }

    for (int i=1; i < n+1; i++){
        if (parts.requiredParts[i] != 0){
            partsList[i].indegree--;
            partsList[i].totalCount += number * parts.requiredParts[i];
            if (partsList[i].indegree == 0){
                order(i, partsList[i].totalCount);
            }
        }
    }
}

int main(){
    cin >> n;
    cin >> m;

    partsList.assign(n+1, Parts(n));

    for (int i=0; i < m; i++){
        int x, y, k;
        cin >> x >> y >> k;
        // requiredParts[x][y] = k;
        partsList[x].requiredParts[y] = k;
        partsList[x].isBasic = false;
        partsList[y].indegree += 1;
    }

    order(n, 1);

    for (int i=1; i <n+1; i++){
        if (partsList[i].isBasic){
            cout << i << " " << partsList[i].totalCount << "\n";
        }
    }

    for (auto i: partsList){
        for (auto j: i.requiredParts){
            cout << j << " ";
        }cout << endl;
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