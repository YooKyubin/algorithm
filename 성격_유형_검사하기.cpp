#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> survey, vector<int> choices) {
    string answer = "";

    // init score
    unordered_map<char, int> score;
    string results = "RTCFJMAN"; // 사전 순으로 미리 정렬
    for (char i: results)
        score[i] = 0;
    
    // 각 항목 점수 부여
    while(!survey.empty()){
        string question = survey.back();
        int choice = choices.back();
        survey.pop_back();
        choices.pop_back();

        choice -= 4;
        char disagree = question[0];
        char agree = question[1];
        choice > 0 ? score[agree] += choice : score[disagree] += -choice;
    }

    // answer 결정
    for (int i=0; i < 4; i++){
        char res1 = results[i*2];
        char res2 = results[i*2 + 1]; 
        
        // 같은 경우는 미리 사전순으로 정렬 해두었기 때문에 앞의 것을 선택
        answer.push_back( score[res1] >= score[res2] ? res1 : res2 ); 
    }
    return answer;
}

int main() {
    vector<string> survey {"AN", "CF", "MJ", "RT", "NA"};
    vector<int> choices {5, 3, 2, 7, 5};
    cout << solution(survey, choices) << endl;
    return 0;
}

/*
RFMN
TCJA
*/