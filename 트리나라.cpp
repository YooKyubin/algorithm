#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<vector<int>> graph;
vector<vector<int>> tree;
vector<vector<vector<int>>> dp;
const int64_t MOD = 1e9 + 7;

void makeTree(int current, int parent){
    for (int child : graph[current]){
        if (child == parent) continue;

        tree[current].push_back(child);
        makeTree(child, current);
    }
}

int64_t countSubtree(int root, int exclusion, int kount){
    if (kount == 0) return 1;
    if (exclusion == tree[root].size()) return kount==1; // 루트만 남았는데 세야할 노드 수가 1이 아닌경우
    if (dp[root][exclusion][kount] != -1) return dp[root][exclusion][kount]; // 이미 계산한 적이 있는 값

    int64_t ret = 0; 
    int child = tree[root][exclusion];
    for (int i=0; i < kount; i++){
        ret += countSubtree(child, 0, i) * countSubtree(root, exclusion+1, kount-i);
        ret %= MOD;
    }
    return dp[root][exclusion][kount] = ret;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    
    graph.assign(n+1, vector<int>());
    tree.assign(n+1, vector<int>());
    dp.assign(n+1, vector<vector<int>>(n+1, vector<int>(n+1, -1)));

    for (int i=0; i < n-1; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    makeTree(1, -1);
    
    int answer = 0;
    for(int i=1; i < n+1; i++){
        answer += countSubtree(i, 0, k);
        answer %= MOD;
    }
    cout << answer << "\n";
    return 0;
}