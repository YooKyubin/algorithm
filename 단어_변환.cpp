#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

bool checkConnection(string a, string b){
    int count = 0;
    for (int i=0; i < a.size(); i++){
        if ( a[i] != b[i] ){
            count++;
        }
    }
    if (count == 1){
        // 아... 이게 사실 단어가 중복이 없어서 count == 1 이라고 해야 할 것 같기도 하고..
        return true;
    }
    else{
        return false;
    }
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    // vector<int> dist(words.size()+1, 0);
    queue<pair<int, string>> q;
    
    q.push( {0, begin} );
    // q.push( {words.size(), begin} );
    while (!q.empty()){
        string v = q.front().second;
        int dist = q.front().first;
        cout << v << ", " << dist << endl;
        q.pop();

        if (v == target){
            return dist;
        }
        if (dist >= words.size()+1){
            return 0;
        }

        for (int i=0; i < words.size(); i++){
            if (checkConnection(v, words[i])){
            // if (dist[i] != 0 && checkConnection(v, words[i])){
                q.push( {dist+1, words[i]} );
                // q.push( {i, words[i]} );
            }
        }

    }
    cout << "while end" << endl;
    return 0;
}

int main(){
    string begin = "hit";
    string target = "cog";
    // vector<string> words {"hot", "dot", "dog", "lot", "log", "cog"};
    // vector<string> words {"hot", "dot", "dog", "lot", "log"};
    vector<string> words {"hot", "dot", "dog", "cog"};
    cout << solution(begin, target, words) << endl;
    return 0;
}

/*
bfs,
1. 
큐에 {시작점으로부터의 거리, 노드} 를 저장해서



2.
이미 지나간 곳을 밟는 것은 의미가 없음, 안돼
1차원 배열에 시작점으로부터의 거리(연결 다리의 수)를 저장해서 최단거리 계산
{인덱스, 노드}
*/