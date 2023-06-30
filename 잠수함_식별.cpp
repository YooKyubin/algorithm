#include <iostream>
#include <string>
#include <vector>

using namespace std;

string input;

bool check(int idx){
    if (input[idx] == '0'){ // 01
        if (input[idx+1] == '1') {
            if (idx+2 < input.size()){
                return check(idx+2); // true;
            }
            else {
                return true;
            }
        }
        else{
            return false;
        }
    }
    else { //if(input[idx] == '1'){ // 100~1~
        if (input[idx+1] == '0' && input[idx+2] == '0'){
            int i=2;
            int j=0;
            while(input[idx+i] == '0'){
                i++;
            } // input[idx+i] == '1'혹은 배열 밖의 인덱스
            if (idx+i >= input.size()) return false;
            
            while(input[idx+i+j] == '1'){
                j++;
            } // input[idx+i+j] == '0' 혹은 배열 밖의 인덱스
            if (idx+i+j >= input.size()) { // 1로 문자열이 끝남
                return true;
            }
            else if (input[idx+i+j-2] == '0') { // j < 1, 01로 패턴 종료
                return check(idx+i+j);
            }
            else {
                return check(idx+i+j) || check(idx+i+j-1);
            }
            // cout << idx+i+j << " " << idx+i+j-1 << endl;
            // bool ret1 = check(idx+i+j);
            // bool ret2 = check(idx+i+j-1);
            // cout << ret1 << " " << ret2 << endl;
            // return ret1 || ret2;

        }
        else {
            return false;
        }
    }
}

int main() {
    cin >> input;

    if (check(0)) {
        cout << "SUBMARINE" << endl;
    }
    else {
        cout << "NOISE" << endl;
    }

    return 0;
}