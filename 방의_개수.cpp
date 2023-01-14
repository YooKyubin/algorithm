#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

int solution(vector<int> arrows) {
    int answer = 0;
    vector<pair<int,int>> dir {{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}};
    map< pair<int,int>, set<pair<int,int>> > graph;
    map<pair<int,int>, bool> visited;

    pair<int,int> pos {0,0};
    for (auto i: arrows){
        for (int j = 1; j <= 2; j++) {

            visited[pos] = false;
            int x = pos.first + dir[i].first;
            int y = pos.second + dir[i].second;

            graph[pos].insert({x, y});
            graph[{x,y}].insert(pos);
            pos = {x,y};
            // cout << "dir: " << i  << ": " << x << ", " << y << endl;
        }
    }
    for (auto i: graph[{0,0}]){
        cout << i.first << ", " << i.second << "/ ";
    }
    cout << endl;

    /*
    이걸 dfs로 구현했다면 훨씬 깔끔한 코드가 나올 것 같다.
    depth 를 저장해두고 두 노드의 depth 차이가 1이 아니라면 바로 이전 노드가 아니라는 뜻이 된다.
    괜히 이거처럼 이전 노드를 따로 저장해서 지저분하게 생길 필요가 없을 것 같다.
    */
    queue< pair<pair<int,int>, pair<int,int>> > q;
    q.push({ {0,0}, {0,0} });
    while(!q.empty()){
        pair<int,int> v = q.front().first;
        pair<int,int> pre = q.front().second;
        visited[v] = true;
        q.pop();

        for (pair<int,int> i: graph[v]) {
            if (!visited[i]) {
                visited[i] = true;
                q.push({ i, v });
            }
            else if (pre != i) {
                cout << "v : " << v.first << ", " << v.second << endl;
                cout << "i : " << i.first << ", " << i.second << endl;
                cout << endl;
                answer += 1;
            }
        }
    }
    return answer/2;
}

int main() {
    vector<int> arrows {6, 6, 6, 4, 4, 4, 2, 2, 2, 0, 0, 0, 1, 6, 5, 5, 3, 6, 0};
    cout << solution(arrows) << endl;
    return 0;
}

/*
이미 밟은 곳을 다시 밟으면 방의 수 +1
한번 움직일때마다 1이 아닌 0.5씩 움직이는 걸로, 길이가 1인 정사각형의 대각선을 잇는 경우
근데 같은 곳을 계속 멤돌면 밟은 곳을 다시 밟는 경우지만, 방의 수는 늘어나지 않음
    - 일단 한번 쭉 돌고 양방향 간선으로 다 채워, 무적권 양방향이여야함: 0,0 -> 1,0 가는 간선과 1,0 -> 0,0 가는 간선은 같아야 함
    - 새로그린 그래프로 도는데 그 때 이미 방문한 곳 다시 들리면 그때 방개수 +1
        - 근데 전진 후진 하는 경우에도 +1이 되니까 
*/

/*
양방향 : { (arrows % 4), (arrows % 4 + 4) }
*/