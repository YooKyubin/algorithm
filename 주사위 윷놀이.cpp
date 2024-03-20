#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// start = 0, end = 21
vector<int> diceNum(10);
vector<int> nextIdx(33);
vector<int> score(33);
vector<int> shortcut(33);
// vector<bool> horseLocated(33, false);

int answer = 0;

void init()
{
    for (int i=0; i<=20; ++i)
    {
        score[i] = i * 2;
    }
    score[21] = 0;
    score[22] = 13;
    score[23] = 16;
    score[24] = 19;

    score[25] = 22;
    score[26] = 24;

    score[27] = 28;
    score[28] = 27;
    score[29] = 26;

    score[31] = 30;
    score[32] = 35;

    score[30] = 25;


    for (int i=0; i<33; ++i)
    {
        nextIdx[i] = i+1;
    }
    nextIdx[21] = 21;
    nextIdx[24] = 30;
    nextIdx[26] = 30;
    nextIdx[29] = 30;
    nextIdx[32] = 20;

    shortcut = nextIdx;

    shortcut[5] = 22;
    shortcut[10] = 25;
    shortcut[15] = 27;
}

void dfs(int diceIdx, int sum, vector<int> piece)
{
    if (diceIdx == 10)
    {
        answer = max(answer, sum);
        return;
    }

    for (int i=0; i<4; ++i)
    {
        if (piece[i] == 21)
            continue;

        vector<int> temp = piece;
        int step = diceNum[diceIdx];
        int selectedPiecePos = piece[i];
        for (int s = 0; s < step; ++s)
        {
            if (s == 0)
                selectedPiecePos = shortcut[selectedPiecePos];
            else
                selectedPiecePos = nextIdx[selectedPiecePos];
        }
        temp[i] = selectedPiecePos;

        auto findIter = find(piece.begin(), piece.end(), selectedPiecePos);
        if (findIter == piece.end() || selectedPiecePos == 21)
            dfs(diceIdx + 1, sum + score[selectedPiecePos], temp);
        // if (!horseLocated[selectedPiecePos] || selectedPiecePos == 21)
        // {
        //     horseLocated[piece[i]] = false;
        //     horseLocated[selectedPiecePos] = true;
        //     dfs(diceIdx+1, sum + score[selectedPiecePos], temp);
        //     horseLocated[piece[i]] = true;
        //     horseLocated[selectedPiecePos] = false;
        // }

    }
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    vector<int> piece(4, 0);  
    for (int i=0; i<10; ++i)
    {
        cin >> diceNum[i]; 
    }
    init();

    dfs(0, 0, piece);

    cout << answer << endl;
    return 0;
}