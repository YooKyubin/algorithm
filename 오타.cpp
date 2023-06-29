#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string input;
    int answer = 0;
    cin >> input;
    vector<int> number(input.size());
    vector<int> accRight(input.size());
    vector<int> accLeft(input.size());
    for (int i=0; i < input.size(); i++){
        if (input[i] == '(') number[i] = 1;
        else number[i] = -1;
    }
    accRight = number;
    accLeft = number;
    for (int i=1; i < input.size(); i++){
        accLeft[i] += accLeft[i-1];
        accRight[input.size()-i-1] += accRight[input.size()-i];
    }
    if (accLeft[accLeft.size()-1] == -2){
        for (int i=0; i<input.size(); i++){
            if (input[i] == ')')
                answer++;
            if (accLeft[i] == -1 ){
                break;
            }
        }
    }
    else if (accLeft[accLeft.size()-1] == 2){ // 오른쪽부터 누적합을 계산
        for (int i=0; i<input.size(); i++){
            if (input[input.size()-i-1] == '(')
                answer++;
            if (accRight[input.size()-i-1] == 1){
                break;
            }
        }
    }
    cout << answer << endl;
    return 0;
}

/*
*/