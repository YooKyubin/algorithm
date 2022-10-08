#include<iostream>
#include<queue>

#define MAX 1001 // 2 <= s  < 1000

using namespace std;

int s;
int visited[MAX][MAX] = {false};
int v;
int clip;
int t;

struct factor{
    int q_v;
    int q_clip;
    int q_t;
};

void bfs(){
    queue<factor> q;
    q.push({1,0,0}); // 화면, 클립보드, 시간
    visited[1][0] = true; //화면, 클립보드
    while (!q.empty()){
        v = q.front().q_v;
        clip = q.front().q_clip;
        t = q.front().q_t;

        if(v == s){
            return;
        }

        q.pop();
        
        // 화면의 이모티콘 하나를 삭제한다.
        if(v-1 > 0 && !visited[v-1][clip]){
            visited[v-1][clip] = true;
            q.push({v-1, clip, t + 1});
        }
        // 클립보드의 모든 이모티콘을 화면에 붙여넣기 한다.
        if(v+clip < MAX && clip > 0 && !visited[v+clip][clip]){
            visited[v+clip][clip] = true;
            q.push({v+clip, clip, t + 1});
        }
        // 화면읜 있는 이모티콘을 모두 복사하여 클립보드에 저장한다.
        if(!visited[v][v]){
            visited[v][v] = true;
            q.push({v, v, t + 1});
        }
    }
}

int main(){
    cin >> s;
    bfs();
    cout << t << endl;
    return 0;
}