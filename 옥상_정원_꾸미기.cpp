#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    long long answer = 0;
    vector<pair<int, int>> stack;
    stack.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        int height;
        cin >> height;

        pair<int, int> curr = { i, height };

        while (!stack.empty())
        {
            pair<int, int> prev = stack.back();
            if (prev.second > curr.second)
            {
                break;
            }
            answer += curr.first - prev.first - 1;
            stack.pop_back();
        }
        stack.push_back(curr);
    }

    while (!stack.empty())
    {
        answer += n - stack.back().first - 1;
        stack.pop_back();
    }

    cout << answer << endl;

    return 0;
}