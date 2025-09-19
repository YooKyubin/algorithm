#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Vec
{
    int x = 0;
    int y = 0;

    Vec operator+(const Vec& other) const
    {
        return {x + other.x, y + other.y};
    }
    Vec operator*(int scalar) const
    {
        return {x * scalar, y * scalar};
    }
};

bool OOB(const Vec& v)
{
    return v.x < 0 || v.x >= 4 || v.y < 0 || v.y >= 4;
}

int BFS(Vec start, Vec end, vector<vector<int>>& board)
{
    static const vector<Vec> dirs {{0,1}, {1, 0}, {-1, 0}, {0, -1} };

    queue<Vec> q;
    vector<vector<int>> visited(4, vector<int>(4, -1));
    visited[start.x][start.y] = 0;

    q.push(start);

    while (!q.empty())
    {
        Vec curr = q.front();
        q.pop();

        vector<Vec> nextPositions;
        for (const Vec& dir : dirs)
        {
            Vec next = curr + dir;
            if ( !OOB(next) )
            {
                nextPositions.push_back(next);
            }

            for (int i=1; i <= 4; ++i)
            {
                next = curr + dir * i;
                
                if (OOB(next))
                {
                    next = curr + dir * (i -1);
                    nextPositions.push_back(curr + dir * (i - 1));
                    break;
                }
                if (board[next.x][next.y] != 0)
                {   
                    nextPositions.push_back(next);
                    break;
                }
            }
        }

        for (Vec next : nextPositions)
        {
            if (visited[next.x][next.y] == -1)
            {
                visited[next.x][next.y] = visited[curr.x][curr.y] + 1;
                q.push(next);
            }
        }
    }

    // for (auto line : visited)
    // {
    //     for (auto i : line)
    //     {
    //         cout << i << " ";
    //     }
    //     cout << endl;
    // }

    return visited[end.x][end.y];
}

int MakePermutation(
    vector<vector<int>>& outPermutation, vector<int>& curr, int visitedBit, int maxLength, 
    vector<vector<int>>& board, const vector<vector<Vec>>& cardPositions, Vec prePos)
{
    if (curr.size() == maxLength)
    {
        outPermutation.push_back(curr);
        return 0;
    }

    int minDist = INT32_MAX;
    for (int i = 1; i <= maxLength; ++i)
    {
        if (visitedBit & (1 << i))
        {
            continue;
        }

        curr.push_back(i);
        visitedBit |= 1 << i;

        Vec srcPos = cardPositions[i][0];
        Vec dstPos = cardPositions[i][1];

        // pre -> src -> dst
        int preSrc = BFS(prePos, srcPos, board);
        board[srcPos.x][srcPos.y] = 0;
        int srcDst = BFS(srcPos, dstPos, board);
        board[dstPos.x][dstPos.y] = 0;
        int dstEnd = MakePermutation(outPermutation, curr, visitedBit, maxLength, board, cardPositions, dstPos);
        board[srcPos.x][srcPos.y] = i;
        board[dstPos.x][dstPos.y] = i;
        int srcDist = preSrc + srcDst + dstEnd;

        // pre -> dst -> src
        int preDst = BFS(prePos, dstPos, board);
        board[dstPos.x][dstPos.y] = 0;
        int dstSrc = BFS(dstPos, srcPos, board);
        board[srcPos.x][srcPos.y] = 0;
        int srcEnd = MakePermutation(outPermutation, curr, visitedBit, maxLength, board, cardPositions, srcPos);
        board[srcPos.x][srcPos.y] = i;
        board[dstPos.x][dstPos.y] = i;
        int dstDist = preDst + dstSrc + srcEnd;

        // cout << "visited  ";
        // for (int id : curr)
        // {
        //     cout << id << " ";
        // }
        // cout << endl;
        // cout << "prePos: " << prePos.x << ", " << prePos.y << " ";
        // cout << "srcPos: " << srcPos.x << ", " << srcPos.y << " ";
        // cout << "dstPos: " << dstPos.x << ", " << dstPos.y << endl;

        // for (auto& line : board)
        // {
        //     for (int a : line)
        //     {
        //         cout << a << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "preSrc: " << preSrc << ", preDst: " << preDst << endl;
        // cout << "srcDst: " << srcDst << ", dstSrc: " << dstSrc << endl;
        // cout << "dstEnd: " << dstEnd << ", srcEnd: " << srcEnd << endl;
        // cout << "srcDist: " << srcDist << ", dstDist: " << dstDist << "\n" << endl;

        curr.pop_back();
        visitedBit &= ~(1 << i);

        minDist = min(minDist, min(srcDist, dstDist));
    }
    
    return minDist;
}

void MakeRoute(vector<vector<int>>& board, const Vec& start)
{
    vector<vector<Vec>> cardPositions(7);

    int maxLength = 0;
    for (int i=0; i<(int)board.size(); ++i)
    {
        for (int j = 0; j < (int)board.size(); ++j)
        {
            int card = board[i][j];
            if (card != 0)
            {
                maxLength = max(maxLength, card);
                cardPositions[card].push_back({i, j});
            }
        }
    }
    vector<vector<int>> permutations;
    vector<int> curr;
    int visitiedBit = 0;
    MakePermutation(permutations, curr, visitiedBit, maxLength, board, cardPositions, start);
}

int solution(vector<vector<int>> board, int r, int c) {
    int answer = 0;

    vector<vector<Vec>> cardPositions(7);
    int maxLength = 0;

    for (int i=0; i<(int)board.size(); ++i)
    {
        for (int j = 0; j < (int)board.size(); ++j)
        {
            int card = board[i][j];
            if (card != 0)
            {
                maxLength = max(maxLength, card);
                cardPositions[card].push_back({i, j});
            }
        }
    }
    vector<vector<int>> permutations;
    vector<int> curr;
    int visitiedBit = 0;
    answer = MakePermutation(permutations, curr, visitiedBit, maxLength, board, cardPositions, {r, c});
    answer += maxLength * 2;
    return answer;
}

int main()
{
    freopen("output.txt", "w", stdout);

    vector<vector<int>> board = {
        {1,0,0,3},
        {2,0,0,0},
        {0,0,0,2},
        {3,0,1,0}};
    int r = 1;
    int c = 0;

    cout << solution(board, r, c) << endl;


    board = {
            {1,0,0,3},
            {0,0,0,0},
            {0,0,0,2},
            {3,1,1,0}};

    cout << BFS({3,0}, {0, 0}, board) << endl;

    return 0;
}