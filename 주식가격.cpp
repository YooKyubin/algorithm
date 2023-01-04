#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    vector<int> stack;
    answer.assign(size(prices), 0);

    for(int i=0; i < size(prices); i++){
        if(stack.empty() || stack.back() < prices[i]){
            cout << "stack_push: " << prices[i] << endl;
            stack.push_back(prices[i]);
        }
        else{
            cout << "pop index: " << i << endl;
            int t = 1;
            while (!stack.empty() && stack.back() > prices[i]){
                if (answer[i-t] == 0){
                    answer[i-t] = t;
                    cout << "answr index: " << i-t << ", pop element: " << stack.back() << endl;
                    stack.pop_back();
                }
                t = t+1;
            }
            stack.push_back(prices[i]);
        }
    }
    for (int i=0; i < size(answer); i++){
        if (answer[i] == 0){
            answer[i] = size(answer) - i -1;
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