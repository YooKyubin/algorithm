#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> sns;
vector<int> memo_true;
vector<int> memo_false;
vector<bool> visited;
vector<vector<int>> directional;

void make_dir(int x){
    visited[x] = true;
    for (auto i: sns[x]){
        if (!visited[i]){
            directional[x].push_back(i);
            make_dir(i);
        }
    }
}

int dp(int x, bool early){ // 메모이제이션만 하면 될듯

    int ret = 0;
    if (early){
        if (memo_true[x] != 0){
            return memo_true[x];
        }
        ret += 1;
        for (auto i: directional[x]){
            ret += min( dp(i, false), dp(i, true) );
        }
        return memo_true[x] = ret;
    }
    else{
        if (memo_false[x] != 0){
            return memo_false[x];
        }
        for (auto i : directional[x]){
            ret += dp(i, true);
        }
        return memo_false[x] = ret;
    }
}

int main(){
    
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    sns.assign(n+1, vector<int>(0));
    directional.assign(n+1, vector<int>(0));
    memo_true.assign(n+1, 0);
    memo_false.assign(n+1, 0);
    visited.assign(n+1, false);

    for (int i=0; i < n-1; i++){
        int a, b;
        cin >> a >> b; // 사이클이 없는 트리니까 어딜 루트에 두어도 상관없는 그런 트리를 만들고 싶은데
        
        sns[a].push_back(b);
        sns[b].push_back(a);
    }

    make_dir(1);
    // int cnt = 0;
    // for (auto i: directional){
    //     cout << cnt++ << ": ";
    //     for (auto j: i){
    //         cout << j << " ";
    //     }cout << endl;
    // }

    int ans = min( dp(1, true), dp(1,false));
    cout << ans << endl;
    return 0;
}

/*
재귀함수로 죽여버리면 될듯ㅋㅋ

답 = min( 1번 노드가 얼리 어답터일 때, 아닐 때 )

1번 (루트) 노드가 어답터일 때{
    시그마 [ min(그 자식 노드들이 어답터 일때, 아닐때) ]
}
1번 (루트) 노드가 어답터가 아닐 때{
    시그마 [ 그 자식 노드들이 어답터일 때 ]
}

처음 입력 받은 수를 루트로 그러고 입력 받으며 바로바로 트리를 생성해보자
*/