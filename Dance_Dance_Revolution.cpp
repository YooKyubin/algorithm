#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> weight;
vector<int> arr;
vector<vector<vector<int>>> memo;

int min(int a, int b) { return a < b ? a : b; }

int search(int idx, pair<int, int> pos)
{
    if (idx == arr.size())
        return 0;

    if (memo[idx][pos.first][pos.second] != -1)
        return memo[idx][pos.first][pos.second];

    int leftMove = INT32_MAX;
    if (pos.second != arr[idx])
        leftMove = search(idx+1, {arr[idx], pos.second}) + weight[pos.first][arr[idx]];

    int rightMove = INT32_MAX;
    if (pos.first != arr[idx])
        rightMove = search(idx+1, {pos.first, arr[idx]}) + weight[pos.second][arr[idx]];

    return memo[idx][pos.first][pos.second] = min(leftMove, rightMove);
}

int main()
{
    //freopen("input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    arr.reserve(100'000);
    while(true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        arr.push_back(n);
    }
    memo.resize(arr.size(), vector<vector<int>>(5, vector<int>(5, -1)));

    weight.resize(5, vector<int>(5, 1));
    weight = {
        {0, 2, 2, 2, 2},
        {100, 1, 3, 4, 3},
        {100, 3, 1, 3, 4},
        {100, 4, 3, 1, 3},
        {100, 3, 4, 3, 1}
    };

    pair<int, int> pos = {0, 0};

    int answer = 0;

    answer = search(0, pos);

    cout << answer << endl;

    return 0;
}