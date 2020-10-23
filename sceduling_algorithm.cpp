#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
    进程类
*/
class process
{
    public:
        int number;            // 进程序号
        int arrive_time;       //到达时间 
        int burst_time;        // 执行时间
        int waiting_time;      // 等待时间
        int finish_time;       //完成时间
        int turnaround_time;   // 周转时间
        float p_turnaround_time;   // 带权周转时间
        bool is_finished;          // 是否已运行
    public:
        process(int number,int arrive_time,int burst_time){
            this->number = number;
            this->arrive_time = arrive_time;
            this->burst_time = burst_time;
            this->is_finished = false;
        }
        process operator >(const process &p){
            if(arrive_time > p.arrive_time){
                return *this;
            }
            else
            {
                return p;
            }
        }  
        void output_information();  //输出信息
};
void calculate_tt(vector<process> &vec,int num_of_process);     //计算周转时间
void calculate_p_tt(vector<process> &vec,int num_of_process);    // 计算带权周转时间
float calculate_avg_tt(vector<process> &vec,int num_of_process);    // 计算平均周转时间
float calculate_avg_p_tt(vector<process> &vec,int num_of_process);    // 计算平均带权周转时间
void sort_by_at(vector<process> &vec,int num_of_processs);  //按照先后顺序排序
// 定义排序法则-- 按到达时间升序排序
bool compare(process a,process b){
	return a.arrive_time < b.arrive_time;
};
int main(int argc, char const *argv[])
{   
    vector<process> vec;
    int num_of_process;
    cout<<"Input number of processes (limit in 10)"<<endl;
    cin >> num_of_process;
    int i = 0;
    for (i = 0; i < num_of_process; i++)
    {
        cout << "please input number " << i + 1 << " process's arrive time and burst time"<<endl;
        int at;
        int bt;
        cin >> at >> bt;
        process p(i+1,at,bt); 
        vec.push_back(p);
    }
    int option;
    do{
        cout << "1. FCFS  2.SJF  3.HRRN  4.clear 0.exit"<<endl;
        cin>>option;
        switch (option)
        {
        case 1:{
                sort(vec.begin(),vec.end(),compare);
                vec[0].finish_time = vec[0].burst_time;
                vec[0].waiting_time = 0;
                for (int i = 1; i < num_of_process; i++)
                {
                    vec[i].finish_time = vec[i-1].finish_time + vec[i].burst_time;
                    vec[i].waiting_time = vec[i-1].finish_time - vec[i].arrive_time;   
                }
                calculate_tt(vec,num_of_process);
                calculate_p_tt(vec,num_of_process);
                for (int i = 0; i < num_of_process; i++)
                {
                    vec[i].output_information();
                }
                cout<<calculate_avg_tt(vec,num_of_process)<<"\t"<<calculate_avg_p_tt(vec,num_of_process)<<endl;
                cout<<endl;
        }
            break;
        case 2:{
            // do{
            //     int min_at = INT8_MAX;
            //     int index = 0;
            //     vec[0].finish_time = vec[0].burst_time;
            //     for (int i = 1; i < num_of_process; i++)
            //     {
            //         if (vec[i].arrive_time < min_at)
            //         {
            //             min_at = vec[i].arrive_time;
            //             index = i;
            //         }                
            //     }
            //     vec[i].finish_time = vec[i].arrive_time + vec[i].burst_time;
            //     num--;           
            // }while(num>0);  

            calculate_tt(vec,num_of_process);
            calculate_p_tt(vec,num_of_process);
            for (int i = 0; i < num_of_process; i++)
            {
                vec[i].output_information();
            }
            cout<<calculate_avg_tt(vec,num_of_process)<<"\t"<<calculate_avg_p_tt(vec,num_of_process)<<endl;
            cout<<endl;
        }
            break;
        case 3:
            break;
        case 4:system("clear");
            break;
        default:
            break;
        }
    }while(option);
}

void calculate_tt(vector<process> &vec,int num_of_process){
    for (int i = 0; i < num_of_process; i++)
    {
        vec[i].turnaround_time = vec[i].finish_time - vec[i].arrive_time;
    }
}

void calculate_p_tt(vector<process> &vec,int num_of_process){
    
    for (int i = 0; i < num_of_process; i++)
    {      
        vec[i].p_turnaround_time = vec[i].turnaround_time / vec[i].burst_time;
    }
}

float calculate_avg_tt(vector <process> &vec,int num_of_process){
    int sum = 0;
    for (int i = 0; i < num_of_process; i++)
    {   
         sum += vec[i].turnaround_time;
    }
    return sum / num_of_process;
}

float calculate_avg_p_tt(vector <process> &vec,int num_of_process){
    int sum = 0;
    for (int i = 0; i < num_of_process; i++)
    {   
         sum += vec[i].p_turnaround_time;
    }
    return  sum / num_of_process;
}

void sort_by_at(vector<process> &vec,int num_of_process){

    
}
void process::output_information(){
    cout<<"No\tAT\tFT\tBT\tWT\tTT\tPTT" <<endl;;
    cout << this->number<<"\t"<<this->arrive_time<<"\t"<<this->finish_time<<"\t"<<this->burst_time<<"\t"<<this->waiting_time<<"\t"<<this->turnaround_time<<"\t"<<this->p_turnaround_time<<endl; 
    cout<<endl;
}
