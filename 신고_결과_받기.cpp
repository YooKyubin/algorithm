#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer(id_list.size());
    map<string, int> idx;
    for (int i=0; i < id_list.size(); i++){
        idx[id_list[i]] = i;
    }

    // map<string, vector<string>> reporter;
    vector<vector<string>> reporter(idx.size());
    for (auto i: report){
        vector<string> temp = split(i, " ");
        string a = temp[0];
        string b = temp[1];

        if (find(reporter[idx[b]].begin(), reporter[idx[b]].end(), a) == reporter[idx[b]].end()) {
            reporter[idx[b]].push_back(a);
        }
    }

    for (auto i: reporter) {
        if (i.size() >= k){
            for (string id: i){
                answer[idx[id]]++;
            }
        }
    }

    return answer;
}

int main() {
    vector<string> id_list {"muzi", "frodo", "apeach", "neo"};
    vector<string> report {"muzi frodo","apeach frodo","frodo neo","muzi neo","apeach muzi"};
    int k = 2;
    for (auto i: solution(id_list, report, k)){
        cout << i << " ";
    } cout << endl;
    return 0;
}

/*
날 신고한 사람들의 목록을 저장
*/