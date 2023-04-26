#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n;
string answer;
vector<bool> visited;


void dfs(int depth, int length, string& str){
    if (depth == length) {
        cout << answer << "\n";
        return;
    }
    
    char pre =' ';
    for (int i=0; i<str.size(); i++){
        if (visited[i] || str[i] == pre) continue;
        
        pre = str[i];
        visited[i] = true;
        answer.push_back(str[i]);
        dfs(depth+1, length, str);
        answer.pop_back();
        visited[i] = false;
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;

    while (n--){
        string input;
        cin >> input;
        
        sort(input.begin(), input.end());
        visited.assign(input.size(), false );
        dfs(0, input.size(), input);
        answer.clear();
        input.clear();
    }

    return 0;
}