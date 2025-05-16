#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

using namespace std;

struct Task
{
    Task(const string& _name, int _startTime, int _duration)
        : name(_name)
        , startTime(_startTime)
        , duration(_duration)
    {}
    string name;
    int startTime;
    int duration;
};

int ConvertStringTimeToMinute(const string& time)
{
    int hour = stoi( time.substr(0, 2) );
    int minute = stoi( time.substr(3, 2) );
    
    return hour * 60 + minute;
}

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    
    vector<Task> tasks;
    tasks.reserve(plans.size());
    
    // 과제에 대한 정보를 분 단위로 통일( 형 변환 )
    for (auto plan : plans)
    {
        string name = plan[0];
        int startTime = ConvertStringTimeToMinute(plan[1]);
        int duration = stoi(plan[2]);
        
        Task task(name, startTime, duration);
        tasks.push_back(task);
    }
    
    // 시작시간 정렬
    sort(tasks.begin(), tasks.end(), [](const Task& Src, const Task& Dst)->bool
         {
            return Src.startTime < Dst.startTime;
         });
    
    int currentTime = 0;
    vector<Task> taskStack;
    for (Task& task : tasks)
    {
        int usableTime = task.startTime - currentTime;
        
        // 주어진 시간 내에 스택에 쌓인 순서대로 과제처리
        while(!taskStack.empty() && usableTime > 0)
        {
            taskStack.back().duration -= usableTime;
            usableTime = -1 * taskStack.back().duration;
            if (taskStack.back().duration <= 0)
            {
                answer.push_back(taskStack.back().name);
                taskStack.pop_back();
            }
        }
        
        currentTime = task.startTime;
        taskStack.push_back(task);
    }
    
    // stack에 있는거 차례대로 마무리
    while (!taskStack.empty())
    {
        answer.push_back(taskStack.back().name);
        taskStack.pop_back();
    }
    
    return answer;
}