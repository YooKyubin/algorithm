#include <iostream>
#include <vector>

using namespace std;

int n, q;
vector<int> land;

int GetOwner(int idx, int num)
{
    if (idx > n)
        return 0;

    if (land[idx] == 0 || land[idx] > num)
    {
        land[idx] = num;
        GetOwner(idx*2, num);
        GetOwner(idx*2 + 1, num);
        return 0;
    }
    else 
    {
        return land[idx];
    }
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> q;
    land.resize(n+1, 0);

    for (int i=0; i<q; ++i)
    {
        int idx;
        cin >> idx;
        cout << GetOwner(idx, idx) << "\n";
    }
    return 0;
}
