#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


struct comp{
    bool operator()(vector<int> a, vector<int> b){
        return a[1] > b[1];
    }
};

int solution(vector< vector<int> > jobs);

int main(){
    // vector< vector<int> > jobs = { {1,3}, {2,9}, {3,6} };
    vector< vector<int> > jobs = { {0, 10}, {4, 10}, {5, 11}, {15, 2} };
    // vector< vector<int> > jobs = { {0, 10} };
    cout << solution(jobs) << endl;
    return 0;
}

int solution(vector< vector<int> > jobs) {
    int idx = 0;
    int current_time = 0;
    
    sort(jobs.begin(), jobs.end());
    cout << "length: " <<jobs.size() << endl;

    int answer = 0;
    priority_queue<vector<int>, vector< vector<int> >, comp> pq;

    while (idx < jobs.size() || !pq.empty()){
        if (pq.empty()){
            current_time = jobs[idx][0];
            cout << "idle push" << endl;
            pq.push(jobs[idx++]);
        }
        else{
            current_time += pq.top()[1];
            cout << "pqtop(): " << pq.top()[0] << ", " << pq.top()[1] << endl;
            answer += current_time - pq.top()[0];

            cout << "pq.pop() 제거: " << pq.top()[0] << endl;
            pq.pop();
            
            while (idx < jobs.size() && current_time > jobs[idx][0]){
                cout << "while push" << endl;
                pq.push(jobs[idx++]);
            }
        }
        cout << "current_time: " << current_time << endl;
        cout << "idx: " << idx << endl;
        cout << "pq.size(): " << pq.size() << endl;
        cout << endl;
    }
    return (int)(answer / jobs.size());
}

/*
작업 시간이 짧을수록 우선 순위가 높다.
요청 시간 기준으로 jobs정렬이 우선
현재 시간은 계속 가지고 가야할 것 같다.

초기 상태:
    - 힙에 아무것도 없음
    - jobs에서 다음 입력을 바로 가져옴

작업이 끝났을 때 요청된 다른 작업이 있는지 확인
(힙 안에 작업이 들어 있는지 확인)
    - 확인 방법
        - 요청시간 < 현재시간 인 작업들
        즉, 요청시간 > 현재시간이 될 때까지 jobs에서 하나씩 힙에 넣기
    - 작업이 없다면 가장 처음 상태와 같다?
    - 작업이 있다면 우선순위대로 작업을 처리한다.

초기상태에서 jobs에 접근하는 방법과
작업이 끝나고 jobs에 접근하는 방법을 꼬이지 않고
나이스하게 해결하는 것이 중요해보임
    - jobs에 접근하는 index를 전역변수로 설정
    - jobs에 접근하면 그 값을 pop() 하기
*/