#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;
    
    if (n > s)
    {
        return vector<int>{-1};
    }
    
    int a = s / n;
    int b = s % n;
    
    answer.assign(n, a);
    for (int i=0; i<b; ++i)
    {
        ++answer[i];
    }
    reverse(answer.begin(), answer.end());

    return answer;
}

#include <iostream>

int main()
{
    int n = 2;
    int s = 9;
    for (int i : solution(n, s))
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}