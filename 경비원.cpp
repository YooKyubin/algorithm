#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int w, h;
    cin >> w >> h;

    int n;
    cin >> n;

    // 북, 남, 서, 동
    vector<vector<int>> stores(4);
    for (int i = 0; i < n; ++i)
    {
        int id, offset;
        cin >> id >> offset;

        --id;
        stores[id].push_back(offset);
    }

    int manID, manOffset;
    cin >> manID >> manOffset;
    --manID;

    int totalDistance = 0;

    switch (manID)
    {
    case 0:
        for (int i : stores[0])
        {
            totalDistance += abs(i - manOffset);
        }
        
        for (int i : stores[1])
        {
            totalDistance += h;
            totalDistance += min(i + manOffset, w - i + w - manOffset);
        }

        for (int i : stores[2])
        {
            totalDistance += manOffset;
            totalDistance += i;
        }

        for (int i : stores[3])
        {
            totalDistance += w - manOffset;
            totalDistance += i;
        }
        break;

    case 1:
        for (int i : stores[0])
        {
            totalDistance += h;
            totalDistance += min(i + manOffset, w - i + w - manOffset);
        }

        for (int i : stores[1])
        {
            totalDistance += abs(i - manOffset);
        }

        for (int i : stores[2])
        {
            totalDistance += manOffset;
            totalDistance += h - i;
        }

        for (int i : stores[3])
        {
            totalDistance += w - manOffset;
            totalDistance += h - i;
        }
        break;

    case 2:
        for (int i : stores[0])
        {
            totalDistance += manOffset;
            totalDistance += i;
        }

        for (int i : stores[1])
        {
            totalDistance += h - manOffset;
            totalDistance += i;
        }

        for (int i : stores[2])
        {
            totalDistance += abs(i - manOffset);
        }

        for (int i : stores[3])
        {
            totalDistance += w;
            totalDistance += min(i + manOffset, h - i + h - manOffset);
        }
 
        break;

    case 3:
        for (int i : stores[0])
        {
            totalDistance += manOffset;
            totalDistance += w - i;
        }

        for (int i : stores[1])
        {
            totalDistance += h - manOffset;
            totalDistance += w - i;
        }

        for (int i : stores[2])
        {
            totalDistance += w;
            totalDistance += min(i + manOffset, h - i + h - manOffset);
        }
        
        for (int i : stores[3])
        {
            totalDistance += abs(i - manOffset);
        }
        break;
    }

    cout << totalDistance << endl;

    return 0;
}