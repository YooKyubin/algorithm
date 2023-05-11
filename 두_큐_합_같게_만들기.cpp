#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int64_t sum(const vector<int>& list){
    int64_t ret = 0;
    for (int i=0; i < list.size(); i++) ret += list[i];
    return ret;
}

int solution(vector<int> queue1, vector<int> queue2) {
    int answer = -1;

    vector<int> totalQueue; // totalQueue = queue1 + queue2
    totalQueue.insert(totalQueue.end(), queue1.begin(), queue1.end());
    totalQueue.insert(totalQueue.end(), queue2.begin(), queue2.end());

    int64_t totalSum = sum(totalQueue);
    int64_t sumOfQ1 = sum(queue1);
    int64_t target = totalSum / 2;
    int i = queue1.size();
    int j = 0;
    int cnt = 0;
    if (totalSum % 2 != 0) return -1;
    while (i != j && cnt <= totalQueue.size() * 2){ // 진짜 이상한 테스트케이스 하나 있는데 그거 잘못걸리면 무한 루프 걸려서 cnt의 최대 한도 정해둠

        if ( sumOfQ1 == target ){
            answer = cnt;
            break;
        }
        else if (sumOfQ1 > target){
            sumOfQ1 -= totalQueue[j++];
        }
        else if ( sumOfQ1 < target){
            sumOfQ1 += totalQueue[i++];
        }
        
        // 배열 크기 이상의 인덱스 접근을 막아야 함
        if (j == totalQueue.size()) j = j % totalQueue.size();
        if (i == totalQueue.size()) i %= totalQueue.size();

        cnt++;
    }

    return answer;
}

int main() {
    vector<int> queue1 {2,1};
    vector<int> queue2 {2,3,4,5,6,7,8}; // 이 테스트케이스 너무 신비로움
    // vector<int> queue1 {3, 2, 7, 2};
    // vector<int> queue2 {4, 6, 5, 1};
    // vector<int> queue1 {1, 2, 1, 2};
    // vector<int> queue2 {1, 10, 1, 2};
    cout << solution(queue1, queue2) << endl;
    return 0;
}

/*
이거 완전 주어진 배열에서 부분배열의 합이 전체 배열합의 절반이되는 부분배열 찾기 문제, 누적합
*/