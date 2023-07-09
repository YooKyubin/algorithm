#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    string input;
    vector<char> stack;
    int cnt = 0;
    cin >> n >> k;
    cin >> input;
    
    for (int i=0; i<n; i++){
        while (!stack.empty() && input.at(i) > stack.back()){
            if (k==cnt) break;
            stack.pop_back();
            cnt++;
        }
        stack.push_back(input[i]);
    }

    for (int i=0; i < n-k; i++){
        cout << stack[i];
    }cout << endl;

    return 0;
}