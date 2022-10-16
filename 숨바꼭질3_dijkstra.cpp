#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>


using namespace std;

int n, k;
const int MAX = 100001;
vector<int> dist;
vector<bool> visited;

bool cmp(pair<int, int> a, pair<int, int> b){
    return a.second > b.second;
}

void dijkstra(){
    dist[n] = 0;
    visited[n] = true;
    int v = n;
    priority_queue< pair<int, int> > pri_q;
    pri_q.emplace(-dist[n], n);
    while(!pri_q.empty()){
        int v = pri_q.top().second;
        int t = -pri_q.top().first;
        pri_q.pop();
        visited[v] = true;

        if(!(t > dist[v])){ // 이 조건이 없으면 시간초과 난다.
            if(v*2 < MAX && !visited[v*2]){
                dist[v*2] = min(t, dist[v*2]);
                pri_q.emplace(-dist[v*2], v*2);
            }
            if(v+1 < MAX && !visited[v+1]){
                dist[v+1] = min(t+1, dist[v+1]);
                pri_q.emplace(-dist[v+1], v+1);
            }
            if(v-1 >= 0 && !visited[v-1]){
                dist[v-1] = min(t+1, dist[v-1]);
                pri_q.emplace(-dist[v-1], v-1);
            }
        }

    }

    return;
}

int main(){
    cin >> n >> k;
    dist.assign(MAX, MAX);
    visited.assign(MAX, false);

    dijkstra();

    cout << dist[k] << endl;

    return 0;
}
