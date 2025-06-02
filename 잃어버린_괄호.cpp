#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Print(vector<int>& numbers, vector<char>& operators)
{
    for (auto i : numbers)
    {
        cout << i << " ";
    }
    cout << endl;

    for (auto c : operators)
    {
        cout << c << " ";
    }
    cout << endl;
    
}


int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    freopen("../../input.txt", "r", stdin);

    string input;
    cin >> input;

    vector<int> numbers;
    vector<char> operators;
    // 맨 앞에는 + 연산자가 숨어 있다고 생각하고 문제를 풀었다. 그래야 일괄적으로 처리 가능하다.
    operators.push_back('+');

    // 연산자, 숫자 별로 나누어서 배열을 구성했다.
    int prevNumBeiginIndex = 0;
    for (size_t i=0; i < input.size(); ++i)
    {
        if (input[i] == '-' || input[i] == '+')
        {
            numbers.push_back( stoi( input.substr(prevNumBeiginIndex, i) ) );
            prevNumBeiginIndex = i + 1;
            operators.push_back(input[i]);
        }
    }
    numbers.push_back( stoi (input.substr(prevNumBeiginIndex, input.size()) ) );
    
    // 실질적인 연산.
    int buffer = 0;
    int answer = 0;
    // 뒤에서 부터 순회
    for (int i = static_cast<int>(operators.size() - 1); i >= 0; --i)
    {
        if (operators[i] == '-')
        {
            // -연산이면 현재까지 더해둔 모든 값과 현재숫자까지 뺀다.
            answer -= buffer + numbers[i];
            buffer = 0;
        }
        else
        {
            // 나중에 다 더해서 - 연산자가 나오면 이값을 빼기 위해 바로 더하지 않고 버퍼에 더한 값을 쌓아둔다. 
            buffer += numbers[i];
        }
    }

    cout << answer + buffer << endl;

    return 0;
}
