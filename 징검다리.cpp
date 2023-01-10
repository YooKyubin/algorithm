#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 거리 최솟값을 mid 로 만들기 위해 부셔야 하는 바위의 수가 n 보다 큰지 작은지 비교
bool check(int n, const vector<int>& rocks, int mid){
    int remove = 0;
    int i = 0;
    int j = i+1;
    while (j < rocks.size()) {
        if (rocks[j] - rocks[i] < mid){
            j++;
            remove += 1;
        }
        else {
            i = j;
            j++;
        }
    }
    cout << "mid: " << mid << " remove: " << remove << endl;
    return  remove <= n; // 가능한 값중 최대(왼쪽) 값을 구해야 하므로 remove가 n 인 경우, n-1 인 경우를 같은 경우로 생각하고 묶어야 함.

    // mid일 때 부셔야하는 바위의 수가 요구한 n 보다 크다면 (더 많은 바위를 부서야한다면),
    // mid값이 크다는 소리(mid가 크니까 거기에 맞춰서 부셔야하는 바위의 수가 많아짐)
    // 더 작은 mid 값이 필요함
}

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    int left = 0;
    int right = distance;

    rocks.push_back(0);
    rocks.push_back(distance);
    sort(rocks.begin(), rocks.end());


    while (left < right) {
        int mid = (left + right) / 2;

        if (check(n, rocks, mid)){
            answer = mid;
            left = mid+1; // 항상 작은 값을 올려쳐야 while 문이 종료되는건가?
        }
        else {
            right = mid;
        }
    }
    // cout << "start" << endl;
    // for (int i=0; i < distance; i++){
    //     check(3, rocks, i);
    // }
    // cout << endl;

    return answer;
}

int main() {
    int distance = 25;
    vector<int> rocks {2, 14, 11, 21, 17};
    int n = 2;
    cout << solution(distance, rocks, n) << endl;
    return 0;
}