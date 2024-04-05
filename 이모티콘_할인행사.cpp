#include <iostream>
#include <string>
#include <vector>

using namespace std;

void dfs(vector<int>& stack, vector<vector<int>>& sale_prices, 
    vector<vector<int>>& users, vector<int>& answer){

    if (stack.size() == sale_prices.size()) {

        // 최종 확인 코드
        int total_price = 0;
        int account = 0;
        for (auto user: users){
            int user_total_price = 0;
            int buy = user[0] % 10 == 0 ? user[0] / 10 : (user[0] / 10 ) + 1;
            for (int i=0; i < stack.size(); i++){
                int rate = stack[i];
                if (rate >= buy) { // 고객이 살 수 있는 할인율
                    user_total_price += sale_prices[i][rate];
                }
            }

            if (user_total_price >= user[1]){
                account += 1;
                user_total_price = 0;
            }
            total_price += user_total_price;
        }

        if (answer[0] == account){
            if (answer[1] < total_price){
                answer[1] = total_price;
            }
        }
        else if(answer[0] < account){
            answer[0] = account;
            answer[1] = total_price;
        }
        return;
    }
    
    for (int j=1; j < 5; j++){
        stack.push_back(j);
        dfs(stack, sale_prices, users, answer);
        stack.pop_back();
    }

}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer(2, 0);
    vector<vector<int>> sale_prices(emoticons.size(), vector<int> (5));
    for (int i=0; i < emoticons.size(); i++){
        for (int j = 0; j < 5; j++){
            sale_prices[i][j] = emoticons[i] / 10 * (10 - j);
        }
    }

    vector<int> stack;
    dfs(stack, sale_prices, users, answer);

    return answer;
}

int main() {
    vector<vector<int>> users {{40, 10000}, {25, 10000}};
    vector<int> emoticons {7000, 9000};
    for (auto i: solution(users, emoticons)) {
        cout << i << " ";
    } cout << endl;


    cout << "----_---------" << endl;

    vector<int> v1 = {0, 1, 2,3,4,5,6,7,8,9};
    int* a = &v1[0];
    int* b = &v1[1];
    int* c = &v1[2];
    int* d = &v1[3];
    vector<int> v2;
    cout << &v1[0] << endl;
    cout << &v1 << endl;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;

    cout << endl;
    v2 = vector<int>(v1.begin()+2, v1.end()-4);
    v1 = vector<int>(v1.begin()+2, v1.end());
    // v1 = v2;
    cout << &v1[0] << endl;
    cout << &v1 << endl;

    cout << *a << endl;
    cout << *b << endl;
    cout << *c << endl;
    cout << *d << endl;
    cout << v1[3] << endl;
    free(a);
    free(b);
    free(c);
    free(d);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;

    return 0;
}