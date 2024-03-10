
#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b != 0)
        return a / b;
    else
        throw std::invalid_argument("Division by zero");
}

int n;
vector<int> arr;
int maxVal = -INT32_MAX;
int minVal = INT32_MAX;

void search(int depth, int maxDepth, int output, const vector<int(*)(int, int)>& op, vector<bool>& visited)
{
    if (depth == maxDepth)
    {
        // max min
        maxVal = max(maxVal, output);
        minVal = min(minVal, output);
    }

    int(*preOP)(int, int) = nullptr;
    for (int i=0; i<op.size(); ++i)
    {
        if (visited[i])
            continue;
        
        if (preOP == op[i])
            continue;

        visited[i] = true;
        search(depth+1, maxDepth, op[i](output, arr[depth+1]), op, visited);
        visited[i] = false;

        preOP = op[i];
    }
}

int main()
{
    // freopen("../../input.txt", "r", stdin);

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    arr.resize(n);
    int (*basicOperations[4])(int, int) = {&add, &subtract, &multiply, &divide};
    vector< int(*)(int, int) > op;
    vector<bool> visited(n-1,false);
    for (int i=0; i<n; ++i)
        cin >> arr[i];

    for (int i=0; i<4; ++i)
    {
        int cnt;
        cin >> cnt;
        for (int j=0; j<cnt; ++j)
        {
            op.push_back(basicOperations[i]);
        }
    }

    search(0, n-1, arr[0], op, visited);

    cout << maxVal << endl;
    cout << minVal << endl;

    return 0;
}