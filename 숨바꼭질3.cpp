// #include<iostream>
// #include<queue>
// #include<vector>

// using namespace std;

// const int MAX = 100001;
// vector<bool> visited;
// int n, k;
// int answer;

// //priority_queue를 위한 구조체 cmp
// struct cmp{
//     bool operator()(pair<int, int> a, pair<int, int> b){
//         return a.second > b.second;
//     }
// };

// void bfs(){
//     priority_queue< pair<int, int>, vector< pair<int, int> >, cmp > q;
//     q.emplace(n, 0);
//     visited[n] = true;
//     while (!q.empty()){
//         int v = q.top().first;
//         int t = q.top().second;
//         q.pop();
//         if(v == k){
//             answer = t;
//             return;
//         }

//         if(v * 2 < MAX && !visited[v*2]){
//             q.emplace(v*2, t);
//             visited[v*2] = true;
//         }
//         if(v+1 < MAX && !visited[v+1]){
//             q.emplace(v+1, t+1);
//             visited[v+1] = true;
//         }
//         if(v-1 >= 0 && !visited[v-1]){
//             q.emplace(v-1, t+1);
//             visited[v-1] = true;
//         }
//     }
// }

// int main(){
//     visited.assign(MAX, false);

//     cin >> n >> k;

//     bfs();

//     cout << answer << endl;

//     return 0;
// }


#include<iostream>
#include<queue>
#include<vector>

using namespace std;

const int MAX = 100001;
vector<bool> visited;
int n, k;
int answer;

void bfs(){
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > q;
    q.emplace(0,n);
    visited[n] = true;
    while (!q.empty()){
        int t = q.top().first;
        int v = q.top().second;
        q.pop();
        if(v == k){
            answer = t;
            return;
        }

        if(v * 2 < MAX && !visited[v*2]){
            //q.emplace(v*2, t);
            q.emplace(t, v*2);
            visited[v*2] = true;
        }
        if(v+1 < MAX && !visited[v+1]){
            //q.emplace(v+1, t+1);
            q.emplace(t+1, v+1);
            visited[v+1] = true;
        }
        if(v-1 >= 0 && !visited[v-1]){
            //q.emplace(v-1, t+1);
            q.emplace(t+1, v-1);
            visited[v-1] = true;
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