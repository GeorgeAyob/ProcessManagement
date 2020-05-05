#include<iostream>
#include<string>
using namespace std;

int totalTime=0;

class Algorithm
{
public:
    string name;
    int priority;
    float turnAroundTime;
    int arrivalTime;
    int endTime;
    int burstTime;
};

void FirstComeFirstSeve(Algorithm[], int n);
void PriorityPremptive(Algorithm[], int n);
void ShortestJobNext(Algorithm[], int n);
void Print(Algorithm[], int n);

int main()
{
    int n;
    Algorithm *process, Al;
    cout << "Enter the Number of Processes: " << endl;
    cin >> n;
    process = new Algorithm[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Process Name, Arrival Time, Priority and Execution Time"<<endl;
        cin >> process[i].name >> process[i].arrivalTime >> process[i].priority >> process[i].burstTime;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j >= 1; j--)
        {
            if (process[j].arrivalTime < process[j - 1].arrivalTime)
            {
                Al = process[j - 1];
                process[j - 1] = process[j];
                process[j] = Al;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (process[i].arrivalTime > totalTime)
            
            totalTime = process[i].arrivalTime;
        totalTime += process[i].burstTime;
    }
    cout << "First Come First Serve (fcfs)" << endl;
    FirstComeFirstSeve(process, n);
    cout << "Priority: Preemptive" << endl;
    PriorityPremptive(process, n);
    cout << "Shortest Job Next (SJN)" << endl;
    ShortestJobNext(process, n);
    system("pause");
    return 0;
}

void FirstComeFirstSeve(Algorithm a[], int n)
{
    Algorithm *b, tempprocess;
    b = new Algorithm[n];
    for (int i = 0; i < n; i++)
    {
        b[i].arrivalTime = a[i].arrivalTime;
        b[i].burstTime = a[i].burstTime;
        b[i].endTime = a[i].endTime;
        b[i].priority = a[i].priority;
        b[i].turnAroundTime = a[i].turnAroundTime;
        b[i].name = a[i].name;
    }
    int i;
    int temp;
    int btime = b[0].arrivalTime;
    b[0].endTime = btime + b[0].burstTime;
    btime = b[0].endTime;
    for (i = 1; i < n; i++)
    {
        temp = b[i].arrivalTime;
        if (temp > btime)
            btime = temp;
        b[i].endTime = btime + b[i].burstTime;
        btime = b[i].endTime;
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - 1; i++)
        {
            if (b[i].endTime > b[i + 1].endTime) {
                tempprocess.arrivalTime = b[i].arrivalTime;
                b[i].arrivalTime = b[i + 1].arrivalTime;
                b[i + 1].arrivalTime = tempprocess.arrivalTime;
                tempprocess.endTime = b[i].endTime;
                b[i].endTime = b[i + 1].endTime;
                b[i + 1].endTime = tempprocess.endTime;
                tempprocess.burstTime = b[i].burstTime;
                b[i].burstTime = b[i + 1].burstTime;
                b[i + 1].burstTime = tempprocess.burstTime;
                tempprocess.priority = b[i].priority;
                b[i].priority = b[i + 1].priority;
                b[i + 1].priority = tempprocess.priority;
                tempprocess.turnAroundTime = b[i].turnAroundTime;
                b[i].turnAroundTime = b[i + 1].turnAroundTime;
                b[i + 1].turnAroundTime = tempprocess.turnAroundTime;
                tempprocess.name = b[i].name;
                b[i].name = b[i + 1].name;
                b[i + 1].name = tempprocess.name;
            }
        }
    }
    Print(b, n);
}

void PriorityPremptive(Algorithm a[], int n)
{
    Algorithm *b, tempprocess;
    b = new Algorithm[n];
    for (int i = 0; i < n; i++)
    {
        b[i].arrivalTime = a[i].arrivalTime;
        b[i].burstTime = a[i].burstTime;
        b[i].endTime = a[i].endTime;
        b[i].priority = a[i].priority;
        b[i].turnAroundTime = a[i].turnAroundTime;
        b[i].name = a[i].name;
    }
    int  time = 0;
    while (time < totalTime)
    {
       int j = 0;
        for (int i = 0; i < n; i++)
        {
            if (b[i].arrivalTime <= time)
            {
                j = i + 1;
            }
        }
        if (j > 0)
        {
            int x = 0;
            int minpriority = b[0].priority;
            for (int i = 1; i < j; i++)
            {
                if (minpriority > b[i].priority)
                {
                    x = i;
                    minpriority = b[i].priority;
                }
                else
                    if (minpriority == b[i].priority)
                    {
                        if (b[x].arrivalTime > b[i].arrivalTime)
                        {
                            x = i;
                            minpriority = b[i].priority;
                        }
                        else if (b[x].arrivalTime == b[i].arrivalTime)
                        {
                            if (b[x].burstTime > b[i].burstTime)
                            {
                                x = i;
                                minpriority = b[i].priority;
                            }
                        }
                    }
            }
            time += b[x].burstTime;
            b[x].endTime = time;
            b[x].priority += 100;
            b[x].arrivalTime += 100;
        }
        else
        {
            time++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        b[i].priority -= 100;
        b[i].arrivalTime -= 100;
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - 1; i++)
        {
            if (b[i].endTime > b[i + 1].endTime) {
                tempprocess.arrivalTime = b[i].arrivalTime;
                b[i].arrivalTime = b[i + 1].arrivalTime;
                b[i + 1].arrivalTime = tempprocess.arrivalTime;
                tempprocess.endTime = b[i].endTime;
                b[i].endTime = b[i + 1].endTime;
                b[i + 1].endTime = tempprocess.endTime;
                tempprocess.burstTime = b[i].burstTime;
                b[i].burstTime = b[i + 1].burstTime;
                b[i + 1].burstTime = tempprocess.burstTime;
                tempprocess.priority = b[i].priority;
                b[i].priority = b[i + 1].priority;
                b[i + 1].priority = tempprocess.priority;
                tempprocess.turnAroundTime = b[i].turnAroundTime;
                b[i].turnAroundTime = b[i + 1].turnAroundTime;
                b[i + 1].turnAroundTime = tempprocess.turnAroundTime;
                tempprocess.name = b[i].name;
                b[i].name = b[i + 1].name;
                b[i + 1].name = tempprocess.name;
            }
        }
    }
    Print(b, n);
}
void ShortestJobNext(Algorithm a[], int n)
{
    Algorithm *b, tempprocess;
    b = new Algorithm[n];
    for (int i = 0; i < n; i++)
    {
        b[i].arrivalTime = a[i].arrivalTime;
        b[i].burstTime = a[i].burstTime;
        b[i].endTime = a[i].endTime;
        b[i].priority = a[i].priority;
        b[i].turnAroundTime = a[i].turnAroundTime;
        b[i].name = a[i].name;
    }
    int time = 0;
    int ct = 0;
    while (time < totalTime)
    {
        int j = 0;
        for (int i = 0; i < n; i++)
        {
            if (b[i].arrivalTime <= time)
            {
                j = i + 1;
            }
        }
        if (j > 0)
        {
            int x = 0;
            ct = b[0].burstTime;
            for (int i = 1; i < j; i++)
            {
                if (ct > b[i].burstTime)
                {
                    x = i;
                    ct = b[i].burstTime;
                }
            }
            time += b[x].burstTime;
            b[x].endTime = time;
            b[x].burstTime += 100;
            b[x].arrivalTime += 100;
        }
        else
        {
            time++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        b[i].burstTime -= 100;
        b[i].arrivalTime -= 100;
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - 1; i++)
        {
            if (b[i].endTime > b[i + 1].endTime) {
                tempprocess.arrivalTime = b[i].arrivalTime;
                b[i].arrivalTime = b[i + 1].arrivalTime;
                b[i + 1].arrivalTime = tempprocess.arrivalTime;
                tempprocess.endTime = b[i].endTime;
                b[i].endTime = b[i + 1].endTime;
                b[i + 1].endTime = tempprocess.endTime;
                tempprocess.burstTime = b[i].burstTime;
                b[i].burstTime = b[i + 1].burstTime;
                b[i + 1].burstTime = tempprocess.burstTime;
                tempprocess.priority = b[i].priority;
                b[i].priority = b[i + 1].priority;
                b[i + 1].priority = tempprocess.priority;
                tempprocess.turnAroundTime = b[i].turnAroundTime;
                b[i].turnAroundTime = b[i + 1].turnAroundTime;
                b[i + 1].turnAroundTime = tempprocess.turnAroundTime;
                tempprocess.name = b[i].name;
                b[i].name = b[i + 1].name;
                b[i + 1].name = tempprocess.name;
            }
        }
    }
    Print(b, n);
}
void Print(Algorithm a[], int n)
{
    int i = 0;
    float att = 0;
    for (i = 0; i < n; i++)
    {
        a[i].turnAroundTime = a[i].endTime - a[i].arrivalTime;
    }
    for (i = 0; i < n; i++)
    {
        att += a[i].turnAroundTime;
    }
    att = att / n;
    cout << "PID" << "\tStart " << "\tCompletion Time" << "\tTurn Around Time "<<endl;
    for (i = 0; i < n; i++)
    {
        cout << a[i].name << "\t " << a[i].arrivalTime << "\t\t" << a[i].endTime << "\t\t" << a[i].turnAroundTime << endl;
    }
    cout << "Order of Execution: ";
    for (i = 0; i < n; i++) {
        cout << a[i].name <<" ";
    }
    cout << endl;
    cout << "Average TAT: " << att;
    cout << endl;
}
