#include <iostream>
#include <vector>

using namespace std;

int Solve(int n, const vector<int>& arr, bool (*cmp)(int, int))
{
    vector<bool> cmpResult(n, false);
    for (int i = 0; i < n; ++i)
    {
        cmpResult[i] = cmp(arr[i], arr[(i + 1) % n]);
    }

    int numTrue = 0;
    for (int i = 0; i < n; ++i)
    {
        if (cmpResult[i])
        {
            ++numTrue;
        }
    }

    if (numTrue == n-1)
    {
        for (int i = 0; i <n; ++i)
        {
            if (!cmpResult[i])
            {
                return (i + 1) % n;
            }
        }
    }

    if (numTrue == n)
    {
        return 0;
    }

    return INT32_MAX;
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    int solveGeaterEqual = Solve(n, arr, [](int src, int dst) -> bool {

        return src >= dst;
    });
    // cout << solveGeaterEqual << endl;
    
    int solveLessEqual = Solve(n, arr, [](int src, int dst) -> bool {
        
        return src <= dst;
    });
    // cout << solveLessEqual << endl;

    int answer = min(solveGeaterEqual, solveLessEqual);
    if (answer == INT32_MAX)
    {
        answer = -1;
    }
    cout << answer << endl;

    return 0;
}