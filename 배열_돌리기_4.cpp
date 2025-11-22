#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int constexpr MAX_VALUE = 100 * 50 * 50;

class Matrix
{
public:
    Matrix() = default;
    Matrix(const vector<vector<int>>& param)
    : elements(param)
    {}


    int ComputeValue()
    {
        int value = MAX_VALUE;
        for (auto& line : elements)
        {
            int lineSum = 0;
            for (int i : line)
            {
                lineSum += i; 
            }
            value = min(value, lineSum);
        }

        return value;
    }

    Matrix Rotate(int r, int c, int s)
    {
        const static vector<int> dirX = { 1, 0, -1, 0 };
        const static vector<int> dirY = { 0, 1, 0, -1 };

        Matrix rotatedMatrix = *this;

        --r;
        --c;

        for (int diameter = 1; diameter <= s; ++diameter)
        {
            int currX = r - diameter;
            int currY = c - diameter;
            int temp = elements[currX][currY];

            for (int i = 0; i <4; ++i)
            {
                for (int j = 0; j < diameter * 2; ++j )
                {
                    int nextX = currX + dirX[i];
                    int nextY = currY + dirY[i];

                    elements[currX][currY] = elements[nextX][nextY];
                    currX = nextX;
                    currY = nextY;
                }
            }

            elements[r - diameter][c - diameter + 1] = temp;
        }

        swap(rotatedMatrix, *this);
        return rotatedMatrix;
    }

    Matrix Rotate(const vector<int>& commmand)
    {
        return Rotate(commmand[0], commmand[1], commmand[2]);
    }

private:
    vector<vector<int>> elements;

};

int ComputeMinMatrixValue(const Matrix& matrix, const vector<vector<int>>& commands, vector<int>& permutaion)
{
    if (permutaion.size() == commands.size())
    {
        Matrix rotatedMatrix = matrix;
        for (int i : permutaion)
        {
            rotatedMatrix = rotatedMatrix.Rotate(commands[i]);
        }
        return rotatedMatrix.ComputeValue();
    }

    int minValue = MAX_VALUE;
    for (size_t i = 0; i < commands.size(); ++i)
    {
        if (find(permutaion.begin(), permutaion.end(), i) != permutaion.end())
        {
            continue;
        }

        permutaion.push_back((int)i);
        minValue = min(minValue, ComputeMinMatrixValue(matrix, commands, permutaion));
        permutaion.pop_back();
    }
    return minValue;
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    freopen("../../output.txt", "w", stdout);
    
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> elements(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> elements[i][j];
        }
    }

    Matrix matrix(elements);

    vector<vector<int>> commands(k, vector<int>(3));
    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> commands[i][j];
        }
    }

    vector<int> permutation;
    cout << ComputeMinMatrixValue(matrix, commands, permutation) << endl;

    return 0;
}