#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool OOB (int x, int y, int n, int m){
    if ( 0 < x && x <= n && 0 < y && y <= m){
        return false;
    }
    else {
        return true;
    }
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";

    string command = "dlru";
    vector<int> dx {1, 0, 0, -1};
    vector<int> dy {0, -1, 1, 0};

    bool flag = false;

    int dist = abs(x-r) + abs(y-c);
    if ((k - dist) % 2 != 0 || dist > k) {
        return "impossible";
    }
    
    while (k--){
        for (int d=0; d < 4; d++){
            printf("i: %d, k: %d \n", d, k);
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (OOB(nx, ny, n, m)) continue;
            
            int remain = abs(nx - r) + abs(ny - c);
            if (remain > k) continue;

            x = nx;
            y = ny;
            answer += command[d];
            break;
        }


    }
    return answer;
}

int main() {
    // vector<int> a {3, 3, 1, 2, 3, 3,4};
    vector<int> a {3, 4, 2, 3, 3, 1, 5};
    int n = a[0];
    int m = a[1];
    int x = a[2];
    int y = a[3];
    int r = a[4];
    int c = a[5];
    int k = a[6];

    cout << solution(n, m, x, y, r, c, k) << endl;
    return 0;
}

/*
최적화가 없이 dfs 만 돌리면 시간초과가 발생
최적화1
    "impossible"인 경우를 미리 계산한다.

최적화2 
    문자열 사전 순으로 움직였기 때문에 남은 이동 횟수가 0 인데 위치가 r,c 인 경우가 처음 나오는 경우가 우리가 원하는 해이다.
    해를 찾았다면 다른 dfs를 멈춘다.

최적화3
    현 위치에서 목적지까지 최단 거리가 남은 움직임 수 보다 먼 경우를 제거


그리디 알고리즘 같기도 한것이 
dlru 순서로 하나씩 이동해보면서 목적지까지 갈 수 있다면 그 길이 결국 우리가 원하는 해이다.
하나 움직이고 목적지까지 갈 수 있는지 확인하고 된다면 이동, 안되면 다음 이동순서
*/
