#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, c;
vector<int> coordinates;

int calRouter(int minDist){
    int routerCnt = 1; // coordinates[0]집은 무조건 무조건 공유기 설치
    int curLoc = coordinates[0];
    for (int i=1; i < n; i++){
        int nextLoc = coordinates[i];
        if (nextLoc - curLoc >= minDist){
            routerCnt++;
            curLoc = nextLoc;
        }
    }
    return routerCnt;
}

bool check(int mid){
    int router = calRouter(mid);
    return router >= c;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> c;
    for (int i=0; i < n; i++){
        int loc;
        cin >> loc;
        coordinates.push_back(loc);
    }
    sort(coordinates.begin(), coordinates.end());

    int lo = 1;
    int hi = coordinates[n-1]+1;

    while (lo <= hi){
        int mid = (lo + hi) / 2;
        if (check(mid)){
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    int target = hi;

    cout << target << endl;

    return 0;
}

/*
mid 는 공유기 간의 최소 거리
*/