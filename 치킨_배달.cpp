#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> dir { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int min(int a, int b) { return a < b ? a : b; }
int abs(int a) { return a > 0 ? a : -a; }

int n, m;
vector<vector<int>> city;
vector<pair<int, int>> houses;
vector<pair<int, int>> chickens;
vector<vector<int>> chickenDist;
int answer = INT32_MAX;

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= n;
}

int GetDist(vector<pair<int, int>>& chickenPos)
{
    int sumDist = 0;

    for (auto house : houses)
    {
        int minDist = 2 * n;
        for (auto chicken : chickenPos)
        {
            minDist = min(minDist, abs(house.first - chicken.first) + abs(house.second - chicken.second));
        }

        sumDist += minDist;
    }

    return sumDist;
}

void combination(int idx, int depth, int maxDepth, vector<int>& chickenIndices)
{
    if (depth == maxDepth)
    {
        vector<pair<int, int>> chickenPos;
        for (auto i : chickenIndices)
        {
            chickenPos.push_back(chickens[i]);
        }

        answer = min(answer, GetDist(chickenPos));

        return;
    }

    for (int i = idx; i < chickens.size(); ++i)
    {
        chickenIndices.push_back(i);
        combination(i+1, depth + 1, maxDepth, chickenIndices);
        chickenIndices.pop_back();
    }
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    city.resize(n, vector<int>(n));
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cin >> city[i][j];

            if (city[i][j] == 1)
                houses.push_back({i, j});
            else if (city[i][j] == 2)
                chickens.push_back({i, j});
        }
    }

    vector<int> test;
    combination(0, 0, m, test);

    cout << answer << endl;

    return 0;
}
