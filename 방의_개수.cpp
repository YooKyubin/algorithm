#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<pair<int,int>> dir {{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}};

void dfs(pair<int,int> v, int depth, 
    map< pair<int,int>, set<int> >& graph, map< pair<int,int>, int >& visited, int& answer) {
        
    visited[v] = depth;

    for (auto i: graph[v]) {
        pair<int,int> newPos = { v.first + dir[i].first, v.second + dir[i].second };
        if (visited[newPos] == 0) {
            dfs(newPos, depth+1, graph, visited, answer);
        }
        else if (depth - visited[newPos] > 1) {
            answer += 1;
        }
    }
    
    
}

int solution(vector<int> arrows) {
    int answer = 0;
    map< pair<int,int>, set<int> > graph;
    map< pair<int,int>, int > visited;

    pair<int, int> pos {0,0};
    for (auto i: arrows) {
        for (int j=0; j < 2; j++){
            graph[pos].insert(i);
            visited[pos] = 0;
            int x = pos.first + dir[i].first;
            int y = pos.second + dir[i].second;
            pos = { x,y };
            graph[pos].insert( (i+4) % 8);
        }
    }

    // for (auto i: graph[{-2,0}]) {
    //     cout << i << endl;
    // }

    dfs( {0,0}, 1, graph, visited, answer );


    return answer;
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
양방향 : { (arrows), ((arrows + 4) % 8) }
*/