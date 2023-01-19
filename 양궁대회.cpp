#include <iostream>
#include <string>
#include <vector>

using namespace std;

int sum(const vector<int> &list){
    int s = 0;
    for (auto i: list)
        s += i;
    return s;
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer(info.size(), 0);
    int maxGap = 0;
    int count = 0;
    while (count < (1 << info.size())){
        vector<int> lion(info.size(), 0);
        int cost = n;
        int gap = 0;

        for (int i=0; i < info.size(); i++){
            if (count & 1<<i){
                gap += 10 - i;
                lion[i] = info[i] + 1;
            }
            else if (info[i] != 0){
                gap -= 10 - i;
                // lion[i] = 0;
            }
        }
        if (count == 22){
            printf("sum lion: %d, gap: %d \n", sum(lion), gap);
            for (auto i: lion){
                cout << i << " ";
            }cout << endl;
        }
        if (sum(lion) <= n && gap >= maxGap){
            if (sum(lion) < n){    
                lion[10] = n - sum(lion);
            } 
            cout << "check: " << count << ", gap: " << gap << endl;
            for (auto i: lion)
                cout << i << " ";
            cout << endl;

            if (gap == maxGap){
                for (int i =11; i >= 0; i--){
                    if (answer[i] > lion[i]){
                        break;
                    }
                    else if(answer[i] < lion[i]){
                        cout << "=====^^==this===^^======" << endl;
                        answer = lion;
                        break;
                    }
                }
            }
            else{
                maxGap = gap;
                answer = lion;
            }
        }
        count++;
    }
    if (maxGap == 0)
        return {-1};
    return answer;
}

int main(){
    // int n=1;
    // vector<int> info {1,0,0,0,0,0,0,0,0,0,0};
    int n = 5;
    vector<int> info {2,1,1,1,0,0,0,0,0,0,0};
    // int n = 9;
    // vector<int> info {0,0,1,2,0,1,1,1,1,1,1};
    // int n = 10;
    // vector<int> info {0,0,0,0,0,0,0,0,3,4,3};
    for (auto i: solution(n, info)){
        cout << i << " ";
    } cout << endl;
    return 0;
}

/*
그리드 탐색인줄 알았는데 완전탐색이었음
10개의 화살을 11개의 점수에 어떻게 분배할 것인지에 대한 중복조합 => 생각보다 경우의 수가 크지 않음
좀 더 생각해본다면 각 과녁 점수당 해당 점수를 얻을 것인지 아닌지에 대해서 모든 경우를 계산 => 경우의 수가 더 줄어듬
    - 근데 테스트 케이스 4번에서 막힘 남은 과녁 어떻게 처리할거임
*/