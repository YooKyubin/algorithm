#include <iostream>
#include <vector>

using namespace std;

int n, s;
vector<int> seq;
int answer = 0;

void dfs(int depth, int sum){

    if ( depth == n ) return;
    if ( sum + seq[depth] == s ) answer++;

    dfs(depth+1, sum+seq[depth]);
    dfs(depth+1, sum);
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> s;
    seq.reserve(n);
    for (int i=0; i<n; i++){
        cin >> seq[i];
    }

    dfs(0, 0);
    
    cout << answer << "\n";
    return 0;
}