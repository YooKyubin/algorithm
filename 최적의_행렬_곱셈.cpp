#include <string>
#include <vector>

using namespace std;

int CountOperation(
    int begin, 
    int end, 
    const vector<vector<int>>& matrix_sizes,
    vector<vector<int>>& min_num_operations)
{
    static unsigned long long countCall = 0;
    ++countCall;

    if (min_num_operations[begin][end] != 0)
    {
        return min_num_operations[begin][end];
    }

    if (end == begin)
    {
        return 0;
    }

    if (end - begin == 1)
    {
        return matrix_sizes[begin][0] * matrix_sizes[begin][1] * matrix_sizes[end][1];
    }

    int min_operations = INT32_MAX;

    for (int i = begin; i < end; ++i)
    {
        min_operations = min(min_operations, CountOperation(begin, i, matrix_sizes, min_num_operations)
        + CountOperation(i + 1, end, matrix_sizes, min_num_operations)
        + matrix_sizes[begin][0] * matrix_sizes[i][1] * matrix_sizes[end][1]);
    }

    min_num_operations[begin][end] = min_operations;
    return min_operations;
}

int solution(vector<vector<int>> matrix_sizes) 
{
    int answer = 0;
    int num_matrices = (int)matrix_sizes.size();

    vector<vector<int>> min_num_operations(num_matrices, vector<int>(num_matrices, 0));

    answer = CountOperation(0, num_matrices-1, matrix_sizes, min_num_operations);

    return answer;
}

#include <iostream>
int main()
{
    vector<vector<int>> matrix_sizes = 
    {{5, 3}, {3, 10}, {10, 6}};
    cout << solution(matrix_sizes) << endl;

    return 0;
}