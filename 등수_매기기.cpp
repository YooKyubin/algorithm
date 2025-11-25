#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> prediction(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> prediction[i];
    }
    sort(prediction.begin(), prediction.end());

    long long interval = 0;
    for (int i = 0 ; i < n; ++i)
    {
        interval += abs(prediction[i] - (i + 1));
    }
    cout << interval << endl;


    return 0;
}