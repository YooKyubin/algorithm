#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Delta {
    string command = "dlru";
    vector<int> dx {1, 0, 0, -1};
    vector<int> dy {0, -1, 1, 0};
};

bool OOB (int x, int y, int n, int m){
    if ( 0 < x && x <= n && 0 < y && y <= m){
        return true;
    }
    else {
        return false;
    }
}

void dfs(int x, int y, vector<int>& info, const Delta& delta, string& answer, string& stack, int depth, bool& dfsExit){
    if (dfsExit){
        return;
    }
    int n = info[0];
    int m = info[1];
    int r = info[2];
    int c = info[3];
    int k = info[4];

    if (k - depth < abs(x-r) + abs(y-c)){
        return;
    }

    // printf("x: %d, y: %d, depth: %d\n", x, y, depth);
    if (depth == k){
        if (x == r && y == c){
            // cout << stack << endl;
            answer = stack;
            dfsExit = true;
        }
        return;
    }
    
    for (int d=0; d < 4; d++){
        int nextX = x + delta.dx[d];
        int nextY = y + delta.dy[d];
        if (OOB(nextX, nextY, n, m)){
            stack += delta.command[d];
            dfs(nextX, nextY, info, delta, answer, stack, depth+1, dfsExit);
            stack = stack.erase(stack.size()-1);
        }
    }
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    string stack = "";
    vector<int> info {n, m, r, c, k};
    Delta delta;
    bool dfsExit = false;
    int remain = abs(x-r) + abs(y-c);
    if ((k - remain) % 2 != 0 || remain > k) {
        answer = "impossible";
    }
    else {
        dfs(x, y, info, delta, answer, stack, 0, dfsExit);
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
*/