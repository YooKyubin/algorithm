#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

void dfs(string v, const vector<vector<string>>& tickets, 
    vector<bool>& visited, vector<string>& stack, vector<string>& answer){

    stack.push_back(v);
    if (stack.size() == tickets.size()+1){
        answer = stack;
        return;
    }
    
    // 이게 없으면 이미 answer를 구해도 dfs를 끝까지 돌림
    if (answer.size() != 0){
        return;
    }

    for (int i=0; i < tickets.size(); i++){
        if (tickets[i][0] == v && !visited[i]){
            visited[i] = true;
            dfs(tickets[i][1], tickets, visited, stack, answer);
            visited[i] = false;
            stack.pop_back();
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    sort(tickets.begin(), tickets.end(), 
        [](vector<string> a, vector<string> b)->bool{return a[1] < b[1];});

    vector<bool> visited(tickets.size(), false);
    vector<string> answer;
    vector<string> stack;
    
    dfs("ICN", tickets, visited, stack, answer);
    return answer;
}

int main() {
    // vector<vector<string>> tickets { { "ICN", "JFK" }, { "HND", "IAD" }, { "JFK", "HND" } };
    // vector<vector<string>> tickets { { "ICN", "JFK" }, { "JFK", "HND"}, {"HND", "ICN"}, {"JFK", "SFO"}, {"SFO", "ICN"}, {"JFK", "ATL"}, {"ATL", "ICN"}, {"JFK", "IAD"}, {"IAD", "ICN"} };
    vector<vector<string>> tickets {{"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL","SFO"}};

    for (auto i: solution(tickets)){
        cout << i << ", ";
    }
    cout << endl;
    return 0;
}