#include <iostream>
#include <vector>
#include <queue>

#define MAXNUM 100000
#define Node pair<int, int>

using namespace std;

bool OOB(int cur){
    return cur > MAXNUM || cur < 0;
}

int main () {
    int n, k;
    cin >> n >> k;
    
    vector<int> cnt(MAXNUM+1, 0);
    vector<int> dist(MAXNUM+1, -1);
    // vector<bool> visited(MAXNUM+1, false);
    queue<Node> q;

    q.push({n, 0});
    cnt[n] = 1;
    dist[n] = 0;
    // visited[n] = true;

    while (!q.empty()){
        int current = q.front().first;
        int time = q.front().second;
        q.pop();

        for (auto next: {current *2, current +1, current -1}){
            if (OOB(next)) continue;

            // if (!visited[next]){ // 첫 방문
            if (dist[next] == -1){
                dist[next] = time+1;
                cnt[next] = cnt[current];
                q.push({ next, time+1 });
                // visited[next] = true;
            }
            else if (dist[next] == time+1){ // 첫 방문은 아닌데 같은 시간에 도착함
                cnt[next] += cnt[current];
            }
            
        }
    }

    cout << dist[k] << endl;
    cout << cnt[k] << endl;
    return 0;
}