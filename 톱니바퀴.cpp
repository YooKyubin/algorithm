#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Rotate(const vector<string>& gears, vector<int>& heads, int id, int dir, vector<bool>& visited)
{
    int head = heads[id];
    int tail = (heads[id] + 4) % 8 ;

    int left = id - 1;
    if (left >= 0 && !visited[left])
    {
        visited[left] = true;
        int leftHead = heads[left];

        if (gears[left][leftHead] != gears[id][tail])
        {
            Rotate(gears, heads, left, dir * -1, visited);
        }
    }

    int right = id + 1;
    if (right < 4 && !visited[right])
    {
        visited[right] = true;
        int rightTail = (heads[right] + 4) % 8;

        if (gears[right][rightTail] != gears[id][head])
        {
            Rotate(gears, heads, right, dir * -1, visited);
        }
    }

    heads[id] = (heads[id] - dir + 8) % 8;
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    vector<string> gears(4);
    for (int i = 0; i < 4; ++i)
    {
        cin >> gears[i];
    }
    vector<int> heads(4, 2);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int id, dir;
        cin >> id >> dir;
        id -= 1; // 0-bsae
        
        vector<bool> visited(4, false);
        visited[id] = true;
        Rotate(gears, heads, id, dir, visited);
    }

    int score = 0;
    for (int i = 0; i < 4; ++i)
    {
        int isS = gears[i][(heads[i] - 2 + 8) % 8] - '0';
        score += isS * (1 << i);
    }
    cout << score << endl;

    return 0;
}