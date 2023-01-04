#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer(size(prices));
    vector<int> stack;

    for (int i=0; i < size(answer); i++){
        answer[i] = size(answer) - i -1;
    }

    for(int i=0; i < size(prices); i++){
        if(stack.empty() || prices[stack.back()] < prices[i]){
            stack.push_back(i);
        }
        else{
            while (!stack.empty() && prices[stack.back()] > prices[i]){
                answer[stack.back()] = i - stack.back();
                stack.pop_back();
            }
            stack.push_back(i);
        }
    }
    return answer;
}

int main() {
    vector<int> test { 1, 2, 3, 2, 3, 1};
    for (auto i : solution(test)){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

/*

*/