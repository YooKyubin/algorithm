#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Structure
{
    bool pillar = false;
    bool beam = false;
};

class Board
{
public:
    Board(int n)
    {
        isExist.assign(n+1, vector<Structure>(n+1));
    }
    
    bool IsPillarExist(int x, int y) {return OOB(x, y) ? false : isExist[x][y].pillar;}
    bool IsBeamExist(int x, int y) {return OOB(x, y) ? false : isExist[x][y].beam;}
private:
    bool OOB(int x, int y) 
    {
        return x < 0 || x > (int)isExist.size() || y < 0 || y > (int)isExist.size();
    }


    bool CanExistPillar(int x, int y)
    {
        bool isFloor = y == 0;
        bool isOnBeam = ((x-1 >= 0) ? isExist[x-1][y].beam : false)
                        || isExist[x][y].beam;
        bool isOnPillar = (y-1 >= 0) ? isExist[x][y-1].pillar : false;

        return isFloor || isOnBeam || isOnPillar;
    }

    bool CanExistBeam(int x, int y)
    {
        bool isValidYMinus1 = y-1 >= 0;
        bool isValidXMinus1 = x-1 >= 0;
        bool isValidXPlus1 = x+1 <= (int)isExist.size();
        
        bool isOnPillar = (isValidYMinus1 ? isExist[x][y-1].pillar : false)
                        || ((isValidYMinus1 && isValidXPlus1) ? isExist[x+1][y-1].pillar : false);
        

        bool isConnected = (isValidXMinus1 ? isExist[x-1][y].beam : false)
                        && (x+1 < (int)isExist.size() ? isExist[x+1][y].beam : false);

        // isExist[x-1][y].beam && isExist[x+1][y].beam;
        // cout << "\nOn pillar: " << isOnPillar << ", isConnected: " << isConnected << endl;
        return isOnPillar || isConnected;
    }

    void BuildPillar(int x, int y)
    {
        if (CanExistPillar(x, y))
        {
            isExist[x][y].pillar = true;
        }
    }

    void BuildBeam(int x, int y)
    {
        if (CanExistBeam(x, y))
        {
            isExist[x][y].beam = true;
        }
    }

    void RemovePillar(int x, int y)
    {
        int n = isExist.size();
        isExist[x][y].pillar = false;

        // can remove
        bool andCondition = true;
        if (IsPillarExist(x, y+1))
        {
            andCondition &= CanExistPillar(x, y+1);
        }
        if (IsBeamExist(x-1, y+1))
        {
            andCondition &= CanExistBeam(x-1, y+1);
        }
        if (IsBeamExist(x, y+1))
        {
            andCondition &= CanExistBeam(x, y+1);
        }

        if (andCondition)
        {
            return;
        }
        else
        {
            isExist[x][y].pillar = true;
        }
    }

    void RemoveBeam(int x, int y)
    {
        int n = isExist.size();
        isExist[x][y].beam = false;

        bool removeCondition = true;
        if (IsPillarExist(x,y))
        {
            removeCondition &= CanExistPillar(x,y);
        }
        if (IsPillarExist(x+1, y))
        {
            removeCondition &= CanExistPillar(x+1, y);
        }
        if (IsBeamExist(x-1, y))
        {
            removeCondition &= CanExistBeam(x-1, y);
        }
        if (IsBeamExist(x+1, y))
        {
            removeCondition &= CanExistBeam(x+1, y);
        }

        if (removeCondition)
        {
            return;
        }
        else
        {
            isExist[x][y].beam = true;
        }
    }

public:
    void Perform(int x, int y, int a, int b)
    {
        typedef void(Board::*Act)(int, int);
        Act acts[2][2] = 
        {
            { RemovePillar, BuildPillar },
            { RemoveBeam, BuildBeam }
        };

        this->acts[a][b](x, y);

        // if (a == 0)
        // {
        //     if (b == 0)
        //     {
        //         RemovePillar(x, y);
        //     }
        //     else
        //     {
        //         BuildPillar(x, y);
        //     }
        // }
        // else
        // {
        //     if (b == 0)
        //     {
        //         RemoveBeam(x, y);
        //     }
        //     else
        //     {
        //         BuildBeam(x, y);
        //     }
        // }
    }

private:
    vector<vector<Structure>> isExist;
};

void PrintDebug(vector<vector<Structure>>& isExist)
{
    for (auto& line : isExist)
    {
        for (auto& s : line)
        {
            cout << s.pillar << s.beam << "  ";
        }
        cout << endl;
    }
    cout << endl;
}


vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;

    Board board(n);

    for (auto& command : build_frame)
    {
        int& x = command[0];
        int& y = command[1];
        int& a = command[2];
        int& b = command[3];

        board.Perform(x, y, a, b);
        cout << x << y << a << b << endl;
    }


    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            if (board.IsPillarExist(i, j))
            {
                answer.push_back({i, j, 0});
            }
            if (board.IsBeamExist(i, j))
            {
                answer.push_back({i, j, 1});
            }
        }
    }

    return answer;
}

/*
build_frame = [x, y, 종류, 설치]

기둥은 ( 0 )
    바닥 위에 있거나 
    보의 한쪽 끝 부분 위에 있거나, 또는 
    다른 기둥 위에 있어야 합니다.
보는  ( 1 )
    한쪽 끝 부분이 기둥 위에 있거나, 또는 
    양쪽 끝 부분이 다른 보와 동시에 연결되어 있어야 합니다.

삭제 0, 설치 1

return 값은 오름차순 정렬[x, y, 건축물]
*/

int main()
{
    int n = 5;
    // vector<vector<int>> build_frame = 
    // {
    //     {0,0,0,1},
    //     {2,0,0,1},
    //     {4,0,0,1},
    //     {0,1,1,1},
    //     {1,1,1,1},
    //     {2,1,1,1},
    //     {3,1,1,1},
    //     {2,0,0,0},
    //     {1,1,1,0},
    //     {2,2,0,1}
    // };
    // vector<vector<int>> build_frame = 
    // {
    //     {1,0,0,1},{1,1,1,1},{2,1,0,1},{2,2,1,1},
    //     {5,0,0,1},{5,1,0,1},{4,2,1,1},{3,2,1,1}
    // };
    vector<vector<int>> build_frame = 
    {
        {1, 0, 0, 1}, {2, 0, 0, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}, {1, 0, 0, 0}
    };

    freopen("output.txt", "w", stdout);

    for (auto line : solution(n, build_frame))
    {
        for (int i : line)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}