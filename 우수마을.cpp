#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> population;
vector<vector<int>> graph;
vector<vector<int>> dp;

void dfs_tree(int current, int parent){
    dp[current][true] = population[current];

    for (int child : graph[current]){
        if (child == parent) continue;
        
        dfs_tree(child, current);
        dp[current][false] += max(dp[child][false], dp[child][true]);
        dp[current][true] += dp[child][false];
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    graph.assign(n+1, vector<int>());
    population.assign(n+1, 0);
    dp.assign(n+1, vector<int>(2, 0));

    for (int i=1; i<n+1; i++){
        cin >> population[i];
    }

    for (int i=0; i<n-1; i++){
        int a,b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs_tree(1, -1);

    cout << max(dp[1][0], dp[1][1]) << endl;

    return 0;
}

/*
내가 우수마을이면, 자식은 일반마을만 호출
내가 일반마을이면, 자식은 둘 다 가능
    최대값을 찾아야 하기때문에 일반-일반-일반 의 경우는 발생하지 않아서 안심하고 그냥 돌려도 됨
*/