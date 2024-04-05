#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct cell {
    int ptr;
    string value="EMPTY";
};

enum Command{
    UPDATE,
    MERGE,
    UNMERGE,
    PRINT
};

vector<string> split(string input, string delimiter) {
    vector<string> ret;
    size_t pos = 0;
    string token = "";
    while ((pos = input.find(delimiter)) != string::npos){
        token = input.substr(0, pos);
        ret.push_back(token);
        input.erase(0, pos + delimiter.size());
    }
    ret.push_back(input);

    return ret;
}

int find(int x, vector<cell>& table){
    if (table[x].ptr == x){
        return x;
    }
    else{
        return table[x].ptr = find(table[x].ptr, table);
    }
}

void merge(int x, int y, vector<cell>& table){ // union은  c++에서 예약어로 이미 있네?
    x = find(x, table);
    y = find(y, table);
    
    if (table[x].value == "EMPTY" && table[y].value != "EMPTY"){
        table[x].ptr = y;
    }
    else{
        table[y].ptr = x;
    }
}

vector<string> solution(vector<string> commands) {
    vector<string> answer;

    // 테이블 초기화
    vector<cell> table(50 * 50);
    for (int i=0; i < 50 * 50; ++i){
        table[i].ptr = i;
    }

    map<string, int> commandNum;
    commandNum["UPDATE"] = UPDATE;
    commandNum["MERGE"] = MERGE;
    commandNum["UNMERGE"] = UNMERGE;
    commandNum["PRINT"] = PRINT;

    for (string i: commands){
        vector<string> line;
        line = split(i, " ");
        
        string command = line[0];
        int r1;
        int c1;
        int r2;
        int c2;
        string value1;
        string value2;

        // map과 enum의 조합으로 switch 문을 작성하면 나중에 유지보수 할 때 매우매우 귀찮아 진다
        // command가 하나라도 늘어난다면 map, enum 초기화부분 수정과 case 추가를 매번 하드코딩으로 해야하기 때문이다.
        switch (commandNum[command]){
        case UPDATE:{
            if (line.size() == 3) { // 좌표 안주고 value 찾아야 하는거
                value1 = line[1];
                value2 = line[2];
                for (auto& i: table){
                    if (i.value == value1)
                        i.value = value2;
                }
            }
            else{
                r1 = stoi(line[1])-1;
                c1 = stoi(line[2])-1;
                value1 = line[3];
                int idx = r1 * 50 + c1;
                table[find(idx, table)].value = value1;
            }

            break;
        }
        case MERGE:{
            r1 = stoi(line[1])-1;
            c1 = stoi(line[2])-1;
            c2 = stoi(line[4])-1;
            r2 = stoi(line[3])-1;

            merge(r1 * 50 + c1, r2 * 50 + c2, table);
            break;
        }
        case UNMERGE:{
            r1 = stoi(line[1])-1;
            c1 = stoi(line[2])-1;

            int idx = r1 * 50 + c1;
            int root = find(idx, table);
            value1 = table[root].value;
            vector<int> target;

            for (int i=0; i < 50 * 50; ++i){
                if (table[find(i, table)].ptr == root){
                    target.push_back(i);
                }
            }

            for (int i: target){
                table[i].value = "EMPTY";
                table[i].ptr = i;
            }
            table[idx].value = value1;

            break;
        }
        case PRINT:{
            r1 = stoi(line[1])-1;
            c1 = stoi(line[2])-1;
        
            string res = table[find(r1 * 50 + c1, table)].value;
            answer.push_back(res);
            
            break;
        }
        
        default:
            break;
        }

    }

    return answer;
}

int main() {
    vector<string> commands {
        "UPDATE 1 1 A", "UPDATE 2 2 B", "UPDATE 3 3 C",
        "UPDATE 4 4 D", "MERGE 1 1 2 2", "MERGE 3 3 4 4", 
        "MERGE 1 1 4 4", "UNMERGE 3 3", "PRINT 1 1", 
        "PRINT 2 2", "PRINT 3 3", "PRINT 4 4"};
    // vector<string> commands {
    //     "UPDATE 1 1 menu", "UPDATE 1 2 category", "UPDATE 2 1 bibimbap", 
    //     "UPDATE 2 2 korean", "UPDATE 2 3 rice", "UPDATE 3 1 ramyeon",
    //     "UPDATE 3 2 korean", "UPDATE 3 3 noodle", "UPDATE 3 4 instant", 
    //     "UPDATE 4 1 pasta", "UPDATE 4 2 italian", "UPDATE 4 3 noodle", 
    //     "MERGE 1 2 1 3", "MERGE 1 3 1 4", "UPDATE korean hansik", 
    //     "UPDATE 1 3 group", "UNMERGE 1 4", "PRINT 1 3", "PRINT 1 4", "PRINT 2 3"
    // };
    for (auto i: solution(commands)){
        cout << i << endl;
    }
    return 0;
}
