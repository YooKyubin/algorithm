// 미해결
#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

int shiftRow(int shiftCnt, int i, int n){
    return (i + shiftCnt) % n;
}

vector<vector<int>> solution(vector<vector<int>> rc, vector<string> operations) {
    vector<vector<int>> answer(rc.size(), vector<int>(rc[0].size()));
    deque<int> rowIdx;
    vector<deque<int>> matrix(rc.size());
    for (int i=0; i < rc.size(); i++){
        rowIdx.push_back(i);

        for (int j=0; j < rc[i].size(); j++){
            matrix[i].push_back(rc[i][j]);
        }
    }
    int shiftCnt=0;
    for (auto op : operations){
        if (op == "ShiftRow"){
            shiftCnt += 1;
        }
        else{

            for (int i=matrix.size()-1; i > 0 ; i--){
                int temp = matrix[shiftRow(shiftCnt, i-1, rc.size())].back();
                matrix[shiftRow(shiftCnt, i-1, rc.size())].pop_back();
                matrix[shiftRow(shiftCnt, i, rc.size())].push_back(temp);
            }
            for (int i=1; i < matrix.size(); i++){
                int temp = matrix[shiftRow(shiftCnt, i, rc.size())].front();
                matrix[shiftRow(shiftCnt, i, rc.size())].pop_front();
                matrix[shiftRow(shiftCnt, i-1, rc.size())].push_front(temp);
            }

        }
        for (int i=0; i < rc.size(); i++) cout << shiftRow(shiftCnt, i, rc.size()) << " ";
        cout << endl; cout << 0 + shiftCnt << endl;
        for(int i=0; i < matrix.size(); i++){
            for (int j=0; j < matrix[i].size(); j++){
                cout << matrix[shiftRow(shiftCnt, i, rc.size())][j] << " ";
            }cout << endl;
        }
        cout << endl << endl;
    }

    for (int i=0; i < matrix.size(); i++){
        for(int j=0; j < matrix[0].size(); j++){
            answer[i][j] = matrix[shiftRow(shiftCnt, i, rc.size())][j];
        }
    }

    return answer;
}

int main() {
    vector<vector<int>> rc {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    vector<string> operations {"ShiftRow", "Rotate", "ShiftRow", "Rotate"};
    
    vector<vector<int>> answer = solution(rc, operations);
    for (int i=0; i < answer.size(); i++){
        for (int j=0; j < answer[i].size(); j++){
            cout << answer[i][j] << " ";
        }cout << endl;
    }
    return 0;
}

/*
*/