#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long long DivideSnack(int length, const vector<int>& snacks)
{
    long long numSnack = 0;
    for (int snack : snacks)
    {
        numSnack += snack / length;
    }
    return numSnack;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int m, n;
    cin >> m >> n;

    vector<int> snacks(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> snacks[i];
    }

    int low = 0;
    int high = *max_element(snacks.begin(), snacks.end()) + 1;

    while (low + 1 < high)
    {
        int mid = (low + high) >> 1;

        if (DivideSnack(mid, snacks) >= m)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }
    cout << low << endl;

    return 0;
}