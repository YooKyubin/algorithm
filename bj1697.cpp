// 숨바꼭질
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int MAX = 100001;
int n, k, answer;
int dist[MAX];
bool visited[MAX] = {false};
int a[3];
queue<int> q;

void bfs(){
    int v;
    q.push(n);
    visited[n] = true;
    while (!q.empty()){
        v = q.front();
        q.pop();
        if (v == k){
            answer = dist[v];
            return;
        }
        a[0] = v+1;
        a[1] = v-1;
        a[2] = v*2;
        for (int i: a){
            if (i < MAX && i >= 0 && !visited[i]){
                q.push(i);
                visited[i] = true;
                dist[i] = dist[v] + 1;
            }
        }
    }

}

int main(){
    cin >> n >> k;

    bfs();
    cout << answer << endl;

    return 0;
}