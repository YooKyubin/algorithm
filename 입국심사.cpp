#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool check(int64_t mid, int n, const vector<int>& times) {
    long long sum = 0; // 시간(mid)안에 해결 가능한 사람 수

    for (auto time: times){
        sum += mid / time;
        // if (sum >= n) {
        //     break;
        // }
    }
    cout << "   mid: " << mid << " , sum: " << sum << endl;
    return sum >= n;
    // if (sum < n){
    //     return false; // 시간이 모자르다 => 더 큰 시간이 필요하다.
    // }
    // else if(sum >= n){
    //     return true; // 시간이 알맞거나 넘치다. => 해당 mid 포함하는 더 작은 수들의 범위가 필요.
    // }
}

long long solution(int n, vector<int> times) {
    long long answer = 0;
    int64_t lo = 0;
    int64_t hi = 0;
    for (int64_t i: times) hi = max(i, hi); 
    hi = hi * n;
    // 이렇게 안하고 그냥 sort(times.begin(), times.end()) 로 하는게 더 좋앗을 지도

    while (lo < hi){
        int64_t mid = (lo + hi) / 2;

        if (check(mid, n, times)){
            answer = mid;
            hi = mid;
        }
        else{
            lo = mid + 1;
        }
    }
    cout << endl;
    for(int i =0; i<60; i++){
        check(i, n, times);
    }
    cout << endl;

    return answer;
}

int main() {

    // int n = 7; 
    // vector<int> times { 10, 10 };
    int32_t n = 6; 
    vector<int> times { 7, 10 };

    cout << solution(n, times) << endl;
    return 0;
}

/*
사람을 막대기로 생각하고, 줄을 막대기 이어 붙인거로 생각해
심사관 앞에 사람들을 줄 세운다.
사람 한 명의 길이는 심사관의 심사 시간 
사람 한명 단위로 자를 수 있다.
임의의 수로 딱 줄을 잘랐을 때
    - 사람의 수가 n 보다 많아야 한다.(해당 시간에 n명의 사람을 처리하고도 시간이 남았다는 뜻)
    - 심사관앞에 있는 사람의 수를 구하는 식 = (해당 임의의 수 (=시간) / 심사 시간) 
    - 모든 심사관 앞의 사람을 더했는데 그 값이 n 보다 많으면 
        - sum < n 시간이 모잘라
        - sum >= n 시간이 딱 맞거나 남아! 괜찮아 해결 가능해!
*/