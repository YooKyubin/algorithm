#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Subject{
    string name;
    int startTime;
    int remain;
};

vector<string> split(string input, string delimiter) {
    vector<string> ret;
    size_t pos = 0;
    string token = "";
    while ((pos = input.find(delimiter)) != string::npos){
        token = input.substr(0, pos);
        ret.push_back(token);
        input.erase( 0, pos + delimiter.length() );
    }
    ret.push_back(input);

    return ret;
}

bool compare(Subject a, Subject b){
    return a.startTime < b.startTime;
}

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    vector<Subject> new_plans;
    vector<Subject> stack;
    int currentTime = 0;

    for (auto plan: plans){
        Subject temp;

        vector<string> tokens;
        tokens = split(plan[1], ":");

        temp.name = plan[0];
        temp.startTime = stoi(tokens[0]) * 60 + stoi(tokens[1]);
        temp.remain = stoi(plan[2]);

        new_plans.push_back(temp);
    }

    sort(new_plans.begin(), new_plans.end(), compare);
    
    currentTime = new_plans[0].startTime;
    for (int i=0; i < new_plans.size(); i++){
        Subject sub = new_plans[i];

        while (!stack.empty() && sub.startTime >= stack.back().remain + currentTime){
            currentTime += stack.back().remain;
            answer.push_back(stack.back().name);
            stack.pop_back();
        }

        if (!stack.empty()){
            stack.back().remain -= sub.startTime - currentTime;
        } 
        currentTime = sub.startTime;
        stack.push_back(sub);
    }

    while (!stack.empty()){
        answer.push_back(stack.back().name);
        stack.pop_back();
    }

    return answer;
}



int main(){
    
    vector<vector<string>> plans {{"science", "12:40", "50"},
                                    {"music", "12:20", "40"},
                                    {"history", "14:00", "30"},
                                    {"computer", "12:30", "100"}};
    // vector<vector<string>> plans {{"aaa", "12:00", "20"},
    //                                 {"bbb", "12:10", "30"}, 
    //                                 {"ccc", "12:40", "10"}};
    for (auto i: solution(plans)){
        cout << i << " ";
    }cout << endl;

    return 0;
}


/*
포문 돌때마다
새로우 과제 하나씩 인데
진행중인 과제 vs 새로운 과제 => 새로운 과제
시작 시간 + 
스택이 비어있다면 넘어가지만 비어있지 않다면 가장 뒤의 녀석을 가져와서 진행중인 과제로 설정
진행중인 과제가 끝나기 전이라면 (새로운 과제의 시작 시간)과 (진행중인 과제의 남은 시간 + current time) 비교해서 
새로운 과제의 시작시간이 더 크지 않은 경우에 새로운 과제가 처리되고 진행중이던 놈은 스택으로 들어감


스택에서 하나 뽑고(스택이 비었으면 그냥 넘어가지만) 포문 인덱스에 맞는 녀석과 비교해
새로운 놈의 시작 시각과 스택에서 갓 뽑은 놈의 끝나는 시각을 비교해서 더 작은 놈이 진행돼
    스택에서 갓 뽑은 놈이 진행된다면 끝나는 시각이 current time이 되고, answer 로 바로 흘러가기 문제 없음
        그러고 스택에서 또 뽑기 while 이죠?
    새로운 놈이 진행된다면 currnet time은 새로운 놈의 시작 시각이 됩니다. ? 근데 이건 그냥 스택에 집어 넣는 거 아님?
    새로운 놈이 진행된다면 그냥 스택에 넣죠? 스택에 넣는데, 
    넣을 때 스택에서 갓 뽑혓던 놈의 남은 시간은 (새로운 놈 시작 시각 - 현재 시각) 을 빼줘야 함 -= 이거 사용

그럼 정리하면 
새로운 놈 할당
while 스택이 안 비었음 && 새로운 놈 시작 시각 >= 스택 마지막의 끝나는 시각(current + remain) {
    current time += 스택 마지막 놈의 남은 시간
    스택 마지막 놈 answer 에 추가
}

스택 마지막 놈의 remain -= 새로운 놈의 시작 시각 - current time

마지막은 새로운 놈이 스택의 오야봉이 되는거임 (추가)
*/