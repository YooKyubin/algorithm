#include <iostream>
#include <vector>

using namespace std;

int min(int a, int b) { return a < b ? a : b; }

// 블럭들 가라앉히기
void setBlock(int type, int x, int y, vector<vector<int>>& board)
{
    int newX = 5;
    board[x][y] = 0;

    for (int i=x+1; i<6; ++i)
    {
        if (board[i][y] == 0)
            continue;
        
        newX = i-1;
        break;
    }

    if (type == 2)
    {
        board[x][y+1] = 0;
        for (int i=x+1; i<6; ++i) // i의 시작 지점이 입력으로 받을 때와 블록이 사라져서 내려갈때가 다르다. 이건 입력부분에서 0으로 맞춰주면 될듯?
        {
            if (board[i][y+1] == 0)
                continue;
            
            newX = min(newX, i-1);
            break;
        }
    }

    board[newX][y] = type;
    if (type == 2)
        board[newX][y+1] = 3;
}

// 채워진 줄 찾고 삭제시키기
int checkRow(vector<vector<int>>& board)
{
    int cnt = 0;
    for (int row=0; row<6; ++row)
    {
        int cntZero = 0;
        for (int i=0; i<4; ++i)
        {   
            if (board[row][i] == 0)
                ++cntZero;

        }

        if (cntZero > 0)
            continue;

        for (int i=0; i<4; ++i)
            board[row][i] = 0;

        cnt += 1;
    }

    return cnt;
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int score = 0;
    vector<vector<int>> blue = vector<vector<int>>(6, vector<int>(4));
    vector<vector<int>> green = vector<vector<int>>(6, vector<int>(4));

    int n; cin >> n;

    while (n--)
    {
        int t, x, y;
        cin >> t >> x >> y;
        switch(t)
        {
            case(1):
                setBlock(1, 0, y, green);
                setBlock(1, 0, x, blue);
                break;
            case(2):
                setBlock(2, 0, y, green);
                setBlock(1, 0, x, blue); // 혹시 몰라서 아래에 있는 블록 먼저 떨구기
                setBlock(1, 0, x, blue);
                break;
            case(3):
                setBlock(1, 0, y, green);
                setBlock(1, 0, y, green);
                setBlock(2, 0, x, blue);
                break;
        }
        
        // 줄 채운거 삭제 시키고 밑으로 내리기
        while (true)
        {
            int temp = checkRow(green);
            if (temp == 0)
                break;
            
            score += temp;
            for (int i=5; i>= 0; --i) // 아랫줄부터 처리해야 한다.
                for (int j=0; j<4; ++j)
                    if (green[i][j] == 1 || green[i][j] == 2)
                        setBlock(green[i][j], i, j, green);
        }

        while (true)
        {
            int temp = checkRow(blue);
            if (temp == 0)
                break;

            score += temp;
            for (int i=5; i>=0; --i)
                for (int j=0; j<4; ++j)
                    if (blue[i][j] == 1 || blue[i][j] == 2)
                        setBlock(blue[i][j], i, j, blue);
        }

        // 0, 1 초과분 밀어넣기
        for (int qq = 0; qq < 2; ++qq)
            for (int i=0; i<4; ++i)
            {
                if (green[1][i] != 0)
                {
                    for (int r=5; r>=1; --r)
                    {
                        for (int c=0; c<4; ++c)
                        {
                            green[r][c] = green[r-1][c];
                        }
                    }
                    for (int c=0; c<4; ++c)
                        green[0][c] = 0;
                    break;
                }
            }

        for (int qq = 0; qq < 2; ++qq)
            for (int i=0; i<4; ++i)
            {
                if (blue[1][i] != 0)
                {
                    for (int r=5; r>=1; --r)
                    {
                        for (int c=0; c<4; ++c)
                        {
                            blue[r][c] = blue[r-1][c];
                        }
                    }
                    for (int c=0; c<4; ++c)
                        blue[0][c] = 0;
                    break;
                }
            }

    }
    
    // 남아있는거 계산
    int left = 0;
    for (int i=0; i<6; ++i)
    {
        for (int j=0; j<6; ++j)
        {
            if (green[i][j] != 0)
                ++left;
            if (blue[i][j] != 0)
                ++left;
        }
    }

    cout << score << endl;
    cout << left << endl;
    return 0;
}