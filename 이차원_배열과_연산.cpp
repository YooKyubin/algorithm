#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int num;
    int cnt;
};

struct cmp
{
    bool operator()(const Node& a, const Node& b)
    {
        if (a.cnt == b.cnt)
        {
            return a.num > b.num;
        }

        return a.cnt > b.cnt;
    }
};

int max(int a, int b) { return a > b ? a : b; }

int r, c, k;

void RowCal(int& rCnt, int& cCnt, vector<vector<int>>& matrix)
{
    priority_queue<Node, vector<Node>, cmp> pq;
    int nextCCnt = 0;
    for (int i=0; i<rCnt; ++i)
    {
        vector<int> cnts(101, 0);
        for (int j=0; j<cCnt; ++j)
        {
            ++cnts[ matrix[i][j] ];
        }

        for (int j=1; j<101;  ++j)
        {
            if (cnts[j] == 0)
                continue;
            pq.push({ j, cnts[j] });
        }

        matrix[i] = vector<int>(100, 0);

        int x = i;
        int y = 0;
        while (!pq.empty())
        {
            int num = pq.top().num;
            int cnt = pq.top().cnt;
            pq.pop();

            if (cnt == 0)
            {
                break;
            }

            matrix[x][y] = num;
            ++y;
            if (y >= 100)
                break;

            matrix[x][y] = cnt;
            ++y;
            if (y >= 100)
                break;
        }
        nextCCnt = max(nextCCnt, y);

    }
    cCnt = nextCCnt;
}

void Transpose(vector<vector<int>>& dest, const vector<vector<int>>& rcs)
{
    for (int i=0; i<100; ++i)
    {
        for (int j=0; j<100; ++j)
        {
            dest[i][j] = rcs[j][i];
        }
    }
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin >> r >> c >> k;
    --r;
    --c;
    vector<vector<int>> matrix(100, vector<int>(100));
    int answer = 0;
    int rCnt = 3;
    int cCnt = 3;

    for (int i=0; i<3; ++i)
    {
        for (int j=0; j<3; ++j)
        {
            cin >> matrix[i][j];
        }
    }

    while (matrix[r][c] != k && answer <= 100)
    {
        if (rCnt >= cCnt)
        {
            RowCal(rCnt, cCnt, matrix);
        }
        else
        {  
            vector<vector<int>> temp(100, vector<int>(100));
            Transpose(temp, matrix);

            RowCal(cCnt, rCnt, temp);

            Transpose(matrix, temp);
        }

        ++answer;
    }

    if (answer ==  101)
        answer = -1;

    cout << answer << endl;

    return 0;
}