#include <iostream>
#include <vector>

using namespace std;

int T, n, m;
vector<vector<bool>> edges;
vector<int> indegree;
vector<int> pre_ranking;
vector<int> new_ranking;

// 간선의 방향과 indegree값을 변경한다
void swapEdge(int a, int b){
    if ((edges[a][b] = !edges[a][b])){
        indegree[a]--;
        indegree[b]++;
    }
    if ((edges[b][a] = !edges[b][a])){
        indegree[a]++;
        indegree[b]--;
    }
    // int winner, loser;
    // if (edges[a][b]){
    //     winner = a;
    //     loser = b;
    // }
    // else{
    //     winner = b;
    //     loser = a;
    // }
    // edges[winner][loser] = false;
    // edges[loser][winner] = true;
    // indegree[winner]++;
    // indegree[loser]--;
}

void dfs(int v, vector<int>& new_ranking){
    // indegree[v] -= 1;
    cout << "call " << v << endl;
    new_ranking.push_back(v);

    for (int i=1; i < n+1; i++){
        if (!edges[v][i]) continue;

        if (--indegree[i] == 0) {
            cout << "call chlid " << i << endl; 
            dfs(i, new_ranking);
        }
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> T;
    while (T--){
        cin >> n;
        
        // 초기화
        edges.assign(n+1, vector<bool>(n+1, false));
        indegree.assign(n+1, 0);
        pre_ranking.clear();
        new_ranking.clear();

        for (int i=0; i < n; i++){
            int input;
            cin >> input;
            pre_ranking.push_back(input);
        }
        
        // 간선 생성: 자신보다 낮은 모든 팀에 간선 생성, 꼴등 팀은 indegree가 가장 높다.
        for (int i=0; i<n; i++){
            for (int j=i+1; j<n; j++){
                int winner = pre_ranking[i];
                int loser = pre_ranking[j];

                edges[winner][loser] = true;
                indegree[loser]++;
            }
        }

        for (int i=1; i < n+1; i++){
            cout << "indegree: " << indegree[i] << endl;
        }
        
        cin >> m;
        for (int i=0; i<m; i++){
            int a, b;
            cin >> a >> b;
            swapEdge(a, b);
        }

        for (int i=0; i<n+1; i++){
            for (int j=0; j <n+1; j++){
                cout << edges[i][j] << " ";
            }cout << endl;
        }
        
        // 위상정렬 순회
        for (int i=1; i<n+1; i++){
            if (indegree[i] == 0){
                dfs(i, new_ranking);
                break; // 이걸 안했더니 dfs 한번 쭉 돌고 나서 for 문이 돌게 될때 그때 indegree가 0인 놈을 호출해버림
            }
        }
        
        // 사이클 검사 (데이터의 일관성 검사)
        bool isCycle = false;
        for (int i=1; i<n+1; i++){
            // dfs 를 돌고 난 뒤에 indegree의 값이 0 이상인 노드가 있다면 사이클이 발생해서 모든 노드를 순회하지 못한 것이다.
            if (indegree[i] > 0) {
                isCycle = true;
            }
        }
        if (isCycle) {
            cout << "IMPOSSIBLE";
        }
        else {
            for (auto i: new_ranking) 
                cout << i << " ";
        }
        cout << "\n";
    }
    return 0;
}