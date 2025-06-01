#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    freopen("../../input.txt", "r", stdin);

    int numObjects = 0;
    int maxWeight = 0;
    cin >> numObjects >> maxWeight;

    vector<pair<int, int>> objects(numObjects);
    for (int i=0; i<numObjects; ++i)
    {
        int weight = 0;
        int value = 0;
        cin >> weight >> value; 

        objects[i].first = weight;
        objects[i].second = value;
    }


    // maxValueTable[i][j] = i 번째 물건까지 들어왔을 때, 최대 j 무게까지 담을 수 있는 배낭의 최대 가치
    vector<vector<int>> maxValueTable(numObjects, vector<int>(maxWeight + 1, 0));
    for (int i=0; i <= maxWeight; ++i)
    {
        int weight = objects[0].first;
        int value = objects[0].second;

        maxValueTable[0][i] = (i < weight) ? 0 : value;
    }

    for (int i = 1; i < numObjects; ++i)
    {
        for (int j = 0; j <= maxWeight; ++j)
        {
            int weight = objects[i].first;
            int value = objects[i].second;

            if (j < weight)
            {
                maxValueTable[i][j] = maxValueTable[i-1][j];
            }
            else
            {
                maxValueTable[i][j] = max(maxValueTable[i-1][j - weight] + value, maxValueTable[i-1][j]);
            }
        }
    }

    cout << maxValueTable.back().back() << endl;

    return 0;
}