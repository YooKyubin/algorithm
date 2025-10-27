#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, length, maxWeight;
    cin >> n >> length >> maxWeight;
    
    vector<int> trucks(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> trucks[i];
    }

    queue<int> bridge;
    for (int i = 0; i < length; ++i)
    {
        bridge.push(0);
    }
    int weight = 0;
    int elapsed = 0;

    for (int truck : trucks)
    {
        while (weight + truck - bridge.front() > maxWeight)
        {
            bridge.push(0);
            // cout << bridge.front() << " ";
            weight -= bridge.front();
            bridge.pop();
            ++elapsed;
        }

        weight += truck;
        bridge.push(truck);
        // cout << bridge.front() << " ";
        weight -= bridge.front();
        bridge.pop();
        ++elapsed;
    }

    // while (!bridge.empty())
    // {
    //     cout << bridge.front() << " ";
    //     bridge.pop();
    //     ++elapsed;
    // }

    elapsed += length;
    cout << elapsed << endl;

    return 0;
}