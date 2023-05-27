#include<iostream>
#include<queue>
#include<vector>

#define Node pair<int, int>

using namespace std;

const int MAX = 100001;
vector<bool> visited;
int n, k;
int answer;

void bfs(){
    priority_queue< Node, vector<Node>, greater<Node> > q;
    q.emplace(0,n);
    visited[n] = true;
    while (!q.empty()){
        int time = q.top().first;
        int cur = q.top().second;
        q.pop();
        if(cur == k){
            answer = time;
            return;
        }
        int next;
        
        next = cur * 2;
        if(next < MAX && !visited[next]){
            q.emplace(time, cur*2);
            visited[cur*2] = true;
        }
        next = cur + 1;
        if(next < MAX && !visited[next]){
            q.emplace(time+1, cur+1);
            visited[cur+1] = true;
        }
        next = cur - 1;
        if(next >= 0 && !visited[next]){
            q.emplace(time+1, cur-1);
            visited[cur-1] = true;
        }
    }
}

int main(){
    visited.assign(MAX, false);

    cin >> n >> k;
    bfs();
    cout << answer << endl;

    return 0;
}