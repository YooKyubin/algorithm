#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> arrayA, vector<int> arrayB) {
    int answer = 0;
    vector<int> answers;
    int minA = 100000001;
    int maxA = 0;
    int minB = 100000001;
    int maxB = 0;
    
    for (auto i: arrayA){
        minA = minA > i ? i : minA;
        maxA = maxA > i ? maxA : i;
    }
    for (auto i: arrayB){
        minB = minB > i ? i : minB;
        maxB = maxB > i ? maxB : i;
    }
    
    for (int i = 1; i * i <= maxA; i++){
        bool pass = true;
        for (int j =0; j < arrayA.size(); j++){
            if (arrayA[j] % i != 0) {
                pass = false;
                break;
            }
            if (arrayB[j] % i == 0) {
                pass = false;
                break;
            }

        }
        if (pass)
            answers.push_back( i > maxA / i ? i : maxA / i);
    }
    for (int i = 1; i * i <= maxB; i++){
        bool pass = true;
        for (int j =0; j < arrayB.size(); j++){
            if (arrayB[j] % i != 0) {
                pass = false;
                break;
            }
            if (arrayA[j] % i == 0) {
                pass = false;
                break;
            }

        }
        if (pass)
            answers.push_back( i > maxB / i ? i : maxB / i);
    }
    
    for (int i: answers){
        cout << i << endl;
        answer = answer > i ? answer : i;
    }
    return answer;
}

int main() {
    vector<int> arrayA { 10, 20 };
    vector<int> arrayB { 5, 17 };
    cout << solution(arrayA, arrayB) << endl;
    return 0;
}