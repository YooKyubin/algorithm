#include <iostream>
#include <vector>

using namespace std;

int n;

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    vector<int> tops(n);
    for (int i=0; i<n; ++i)
    {
        cin >> tops[i];
    }

    vector<pair<int, int>> stack; // <value, idx>
    stack.reserve(n);

    vector<int> answer(n);

    for (int i=n-1; i>=0; --i)
    {
        while (!stack.empty() && stack.back().first < tops[i]) // 높이가 서로 다른 탑
        {
            answer[stack.back().second] = i;
            // int idx = stack.back().second;
            stack.pop_back();

        }

        stack.push_back({tops[i], i});
    }

    while(!stack.empty())
    {
        answer[stack.back().second] = -1;
        stack.pop_back();
    }

    for (auto i : answer)
    {
        cout << i+1 << " ";
    }cout << endl;

    return 0;
}