#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;
    vector temp(board.size()+1, vector<int>(board[0].size()+1, 0));
    for (auto i: skill){
        int r1 = i[1];
        int c1 = i[2];
        int r2 = i[3];
        int c2 = i[4];
        int degree = i[5];

        if (i[0] == 1) degree *= -1; 

        temp[r1][c1] += degree;
        temp[r1][c2+1] -= degree;
        temp[r2+1][c1] -= degree;
        temp[r2+1][c2+1] += degree;

    }
    for (int i=0; i < temp.size(); i++){
        for (int j=1; j < temp[0].size(); j ++){
            temp[i][j] += temp[i][j-1];
        }
    }
    for (int i=1; i < temp.size(); i++){
        for (int j=0; j < temp[0].size(); j ++){
            temp[i][j] += temp[i-1][j];
        }
    }

    for (int i=0; i < board.size(); i++){
        for (int j=0; j < board[0].size(); j ++){
            int a = board[i][j] + temp[i][j];
            if (board[i][j] + temp[i][j] > 0) answer++;
            cout << a << " ";
        }
        cout << endl;
    }
    return answer;
}

int main() {
    vector<vector<int>> board {{5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5}};
    vector<vector<int>> skill {{1,0,0,3,4,4},{1,2,0,2,3,2},{2,1,0,3,1,2},{1,0,1,3,3,1}};
    //type, r1, c1, r2, c2, degree
    cout << solution(board, skill) << endl;
    return 0;
}