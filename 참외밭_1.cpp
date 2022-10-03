#include <iostream>

using namespace std;

int k;
// dx[0], y[0] 을 만들기 위해 길이를 7로 하였다.
int dx[7] = {0};
int y[7] = {0};
int direct[5][2] = {
    {0, 0},
    {1, 0},
    {-1,0},
    {0,-1},
    {0, 1}
};
int area = 0;

int main(){
    cin >> k;
    for(int i=1; i < 7; i++){
        int dir, len;
        cin >> dir >> len;

        // x의 변화량 만을 저장
        dx[i]= direct[dir][0] * len;
        // y의 좌표를 저장 (이전 좌표값 + 변화량)
        y[i] = y[i-1] + direct[dir][1] * len;

    }
    for(int i=1; i<7; i++){
        // x변화량 * y좌표값
        area += -dx[i] * y[i];
    }

    cout << area * k << endl;

    return 0;
}