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


---


#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

using FLIGHT = map<string, vector<pair<string, bool>>>;

bool DFS(const string& src, const int numFlights, FLIGHT& flights, vector<string>& answer)
{
    if (answer.size() == numFlights + 1)
    {
        return true;
    }
    
    for (auto& dst : flights[src])
    {
        if (dst.second)
        {
            continue;
        }
        
        dst.second = true;
        answer.push_back(dst.first);
        if (DFS(dst.first, numFlights, flights, answer))
        {
            return true;
        }
        answer.pop_back();
        dst.second = false;
    }

    return false;
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;

    FLIGHT flights;
    int numFlights = tickets.size();

    for (auto& ticket : tickets)
    {
        const string& src = ticket[0];
        const string& dst = ticket[1];

        flights[src].push_back({dst, false});
    }
    for (auto& flight : flights)
    {
        sort(flight.second.begin(), flight.second.end());
    }

    const string start = "ICN";
    answer.push_back(start);
    DFS(start, numFlights, flights, answer);

    return answer;
}

int main()
{
    // 도움이 되는 반례
        // 알파벳 순서로만 처리하면 문제가 되는 이유를 보여줌
        // 모든 티켓을 사용하는 경우를 우선 탐색해야 함
    vector<vector<string>> tickets = 
    {
        { "ICN", "JFK" },
        { "ICN", "JFK" },
        { "HND", "ICN" },
        { "JFK", "HND" },
        { "JFK", "ATL" }
    };

    for (string& str : solution(tickets))
    {
        cout << str << endl;
    }

    return 0;
}