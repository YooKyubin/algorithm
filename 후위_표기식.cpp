#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string fomu;
    vector<pair<char, int>> operatorStack;
    vector<char> answer;
    cin >> fomu;

    int globalPri = 0;
    for (auto ch : fomu)
    {
        int localPri;
        switch(ch)
        {
            case('('):
                globalPri += 2;
                break;
            case(')'):
                globalPri -= 2;
                break;

            case('+'):
            case('-'):
                localPri = 1;
                
                while (!operatorStack.empty() && operatorStack.back().second >= localPri + globalPri)
                {
                    answer.push_back(operatorStack.back().first);
                    operatorStack.pop_back();
                }
                operatorStack.push_back({ch, localPri+globalPri});
                break;

            case('*'):
            case('/'):
                localPri = 2;
                
                while (!operatorStack.empty() && operatorStack.back().second >= localPri + globalPri)
                {
                    answer.push_back(operatorStack.back().first);
                    operatorStack.pop_back();
                }
                operatorStack.push_back({ch, localPri+globalPri});
                break;

            default:
                answer.push_back(ch);
                break;
        }
    }
    while (!operatorStack.empty())
    {
        answer.push_back(operatorStack.back().first);
        operatorStack.pop_back();
    }
        
    for(auto a  : answer)
        cout << a;
    cout << endl;
    return 0;
}