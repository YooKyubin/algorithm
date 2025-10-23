#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//14:33
int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    
    vector<pair<int, int>> lines(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> lines[i].first >> lines[i].second;
    }
    sort(lines.begin(), lines.end());

    int length = 0;
    int src = -1'000'000'001;
    int dst = src;
    for (int i = 0; i < n; ++i)
    {
        if (dst < lines[i].first)
        {
            length += dst - src;
            src = lines[i].first;
        }
        dst = max(dst, lines[i].second);
    }

    length += dst - src;
    cout << length << endl;

    return 0;
}