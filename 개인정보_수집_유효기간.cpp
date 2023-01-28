#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string input, string delimiter){
    vector<string> ret;
    size_t pos;
    string token ="";
    while ( (pos = input.find(delimiter)) != string::npos ){
        token = input.substr(0,pos);
        ret.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    ret.push_back(input);

    return ret;
}

int dateToNum(string day){
    vector<int> date;
    for(auto i: split(day, ".")){
        date.push_back(stoi(i));
    }
    int yyyy = date[0];
    int mm = date[1];
    int dd = date[2];

    return (yyyy - 2000) * 12 * 28 + mm * 28 + dd;
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    string c = "check point";
    int cp = 0;
    int today_d = dateToNum(today);

    vector<int> terms_d( (int)'Z' - (int)'A' );
    for (auto term: terms){
        vector<string> temp = split(term, " ");
        int idx = (int)temp[0].c_str()[0] - (int)'A';
        int term_d = stoi(temp[1]) * 28;

        terms_d[idx] = term_d;
    }

    for (int i=0; i < privacies.size(); i++){
        vector<string> temp = split(privacies[i], " ");
        int idx = (int)temp[1].c_str()[0] - (int)'A';
        int date = dateToNum(temp[0]);

        cout << "i: " << i << ", ";
        cout << "date: " << date << ", ";
        cout << "terms_d[idx]: " << terms_d[idx] << ", ";
        cout << "today_d: " << today_d << ", " << endl;

        if (date + terms_d[idx] - 1 < today_d) {
            answer.push_back( i+1 );
        }
    }

    return answer;
}

int main(){
    string today = "2022.05.19";
    vector<string> terms {"A 6", "B 12", "C 3"};
    vector<string> privacies {"2021.05.02 A", "2021.07.01 B", "2022.02.19 C", "2022.02.20 C"};

    for (auto i: solution(today, terms, privacies)){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}