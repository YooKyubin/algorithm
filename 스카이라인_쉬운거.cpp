#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    int cnt = 0;
    vector<int> stack;
    cin >> n;
    while(n--)
    {
        int pos, height;
        cin >> pos >> height;

        while (!stack.empty() && stack.back() > height)
        {
            stack.pop_back();
        }
        if (stack.empty() || stack.back() < height)
        {
            stack.push_back(height);
            if (height != 0) ++cnt;
        }
    }
    cout << cnt << endl;
    return 0;
}