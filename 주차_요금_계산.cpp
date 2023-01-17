#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

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

struct carState{
    int Time = 0;
    int Fee = 0;
};

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;

    map<string, carState> dict;
    for (string i: records) {
        vector<string> token = split(i, " ");
        vector<string> time = split(token[0], ":");
        int minute = stoi(time[0]) * 60 + stoi(time[1]);
        
        if (token[2] == "IN"){
            dict[token[1]].Time -= minute;
        }
        else{
            dict[token[1]].Time += minute;
        }
    }

    for (auto& i: dict){
        // string &car = i.first;
        carState &state = i.second;
        if (state.Time <= 0){
            state.Time += 23*60 + 59;
        }

        if (state.Time < fees[0]){
            state.Fee = fees[1];
        }
        else {
            state.Fee += fees[1];
            state.Time -= fees[0];
            if (state.Time % fees[2] != 0)
                state.Time = state.Time / fees[2]+1;
            else
                state.Time = state.Time / fees[2];
            state.Fee += state.Time * fees[3];
        }

    }
    
    // map은 key를 기준으로 오름차순 정렬을 해준다.
    for (auto i: dict){
        answer.push_back(i.second.Fee);
    }

    return answer;
}

int main() {
    vector<int> fees {120, 0, 60, 591};
    vector<string> records {
        "16:00 3961 IN","16:00 0202 IN","18:00 3961 OUT",
        "18:00 0202 OUT","23:58 3961 IN"
        };
        
    // vector<int> fees {180, 5000, 10, 600};
    // vector<string> records {
    //     "05:34 5961 IN", "06:00 0000 IN", "06:34 0000 OUT",
    //     "07:59 5961 OUT", "07:59 0148 IN", "18:59 0000 IN", 
    //     "19:09 0148 OUT", "22:59 5961 IN", "23:00 5961 OUT"
    //     };

    for (auto i: solution(fees, records)){
        cout << i << " ";
    }cout << endl;
    return 0;
}