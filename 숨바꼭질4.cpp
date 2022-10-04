#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define MAX_SIZE (100001)
int n, k;
int answer;
vector<int> pre_node(MAX_SIZE, -1);
vector<int> dist(MAX_SIZE, 0);
vector<bool> visited(MAX_SIZE, false);
queue<int> q;
int next_loc[3];
vector<int> node_seq;

void bfs(){
    int v;
    q.push(n);
    visited[n] = true;
    while (!q.empty()){
        v = q.front();
        q.pop();
        if(v == k){
            answer = dist[v];
            return;
        }
        next_loc[0] = v + 1;
        next_loc[1] = v - 1;
        next_loc[2] = v * 2;

        for(int i: next_loc){
            if(i < MAX_SIZE && i >= 0 && !visited[i]){
                dist[i] = dist[v] + 1;
                q.push(i);
                visited[i] = true;
                // 현재 노드의 이전 노드를 저장
                pre_node[i] = v;
            }
        }
    }
}

int main(){
    cin >> n >> k;


    bfs();

    cout << answer << endl;

    // n 부터 k 까지의 노드들의 순서가 거꾸로 저장된다.
    int idx = k;
    for(int i = 0; i < answer + 1; i ++){
        node_seq.push_back(idx);
        idx = pre_node[idx];
    }

    // 반대인 순서들을 뒤에서 부터 출력한다.
    for(int i = answer; i > -1; i--){
        cout << node_seq[i] << " ";
    }
    cout << endl;

    return 0;
}