#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int n, s;
vector<int> seq;
unordered_map<int, int> sumSet;
int64_t answer = 0;

void dfs(int depth, int maxDepth, int sum, bool filling)
{
    if (depth == maxDepth)
    {
        if (filling)
            ++sumSet[sum];

        else
            answer += sumSet[s - sum];

        return;
    }

    dfs(depth+1, maxDepth, sum+seq[depth], filling);
    dfs(depth+1, maxDepth, sum, filling);
}

int main() 
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> s;
    seq.resize(n);
    for (int i=0; i<n; i++)
    {
        cin >> seq[i];
    }

    dfs(n/2, n, 0, true);
    dfs(0, n/2, 0, false);
    
    if (s == 0)
        --answer;
    cout << answer << "\n";
    return 0;
}