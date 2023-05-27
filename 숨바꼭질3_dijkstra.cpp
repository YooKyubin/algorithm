#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>


using namespace std;

int n, k;
const int MAX = 100001;
vector<int> dist;

void dijkstra(){
    dist[n] = 0;
    priority_queue< pair<int, int> > pri_q;
    pri_q.emplace(-dist[n], n);
    while(!pri_q.empty()){
        int v = pri_q.top().second;
        int t = -pri_q.top().first;
        pri_q.pop();

        if(t <= dist[v]){
            if(v*2 < MAX && t < dist[v*2]){
                dist[v*2] = t;
                pri_q.emplace(-dist[v*2], v*2);
            }
            if(v+1 < MAX && t+1 < dist[v+1]){
                dist[v+1] = t+1;
                pri_q.emplace(-dist[v+1], v+1);
            }
            if(v-1 >= 0 && t+1 < dist[v-1]){
                dist[v-1] = t+1;
                pri_q.emplace(-dist[v-1], v-1);
            }
        }
    }

    return;
}

int main(){
    cin >> n >> k;
    dist.assign(MAX, 100001);
    dijkstra();
    cout << dist[k] << endl;

    return 0;
}