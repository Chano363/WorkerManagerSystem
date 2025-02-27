#include<iostream>
#include<cstdlib>
#include<fstream>
#include<algorithm>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

using namespace std;

WorkerManager::WorkerManager()
{
    ifstream infile;
    infile.open(FILENAME, ios::in);
    //文件不存在
    if (!infile.is_open())
    {
        //cout << "文件不存在" << endl;
        this->m_EmpNum = 0;
        this->m_FileIsEmpty = true;
        infile.close();
        return;
    }
    char ch;
    infile >> ch;
    if (infile.eof())
    {
        //cout << "文件为空" << endl;
        this->m_EmpNum = 0;
        this->m_FileIsEmpty = true;
        infile.close();
        return;
    }
    int num = this->get_EmpNum();
    cout << "职工人数为：" << num << endl;
    this->m_EmpNum = num;
    this->m_FileIsEmpty = false;
    this->init_Emp();
}


WorkerManager::~WorkerManager()
{

}
void WorkerManager::clearScreen()
{
    cout << "\033[2J\033[1;1H";
}
void WorkerManager::showMenu() {
    cout << "********************************************\n"
         << "0.退出管理程序\n"
         << "1.增加职工信息\n"
         << "2.显示职工信息\n"
         << "3.删除离职职工\n"
         << "4.修改职工信息\n"
         << "5.查找职工信息\n"
         << "6.按照编号排序\n"
         << "7.清空所有文档\n"
         << "********************************************" << endl;
    cout.flush();
}

void WorkerManager::exitSystem()
{
    cout<<"欢迎下次使用"<<endl;
    system("pause");
    exit(0);
}

void WorkerManager::addEmp()
{
    cout<<"请输入添加职工数量："<<endl;
    int addNum = 0;
    cin>>addNum;
    if(addNum > 0)
    {
        this->m_EmpNum += addNum;
        for(int i = 0;i < addNum;i++)
        {
            int id;
            string name;
            int dSelect;
            cout<<"请输入第"<<i+1<<"个新职工编号："<<endl;
            cin>>id;
            while (true)
            {
                if (this->findEmp(id) != nullptr)
                {
                    cout << "系统中编号不能重复,请重新输入！" << endl;
                    cin >> id;
                }
            }
            cout<<"请输入第"<<i+1<<"个新职工姓名："<<endl;
            cin>>name;
            cout<<"请选择该职工的岗位："<<endl;
            cout<<"1.普通职工"<<endl;
            cout<<"2.经理"<<endl;
            cout<<"3.总裁"<<endl;
            cin>>dSelect;
            Worker *worker = NULL;
            switch(dSelect)
            {
                case 1:
                    worker = new Employee(id,name,1);
                    break;
                case 2:
                    worker = new Manager(id,name,2);
                    break;
                case 3:
                    worker = new Boss(id,name,3);
                    break;
                default:
                    break;
            }

            this->m_workers.push_back(worker);
            cout<<"添加成功"<<endl;
            this->m_FileIsEmpty = false;
        } 
        this->save();
    }
    else
    {
        cout<<"输入有误"<<endl;
    }
    system("pause");
}

void WorkerManager::save()
{
    ofstream outfile;
    outfile.open(FILENAME, ios::out);
    for(auto worker:this->m_workers)
    outfile << worker->m_Id << " "
            << worker->m_Name << " "
            << worker->m_DepId << endl;
    outfile.close();
}
int WorkerManager::get_EmpNum()
{
    ifstream infile;
    infile.open(FILENAME, ios::in);
    int id;
    string name;
    int dId;
    int num = 0;
    while (infile >> id && infile >> name && infile >> dId)
    {
        num++;
    }
    infile.close();
    return num;
}
void WorkerManager::init_Emp()
{
    ifstream infile(FILENAME);
    int id, dId;
    string name;
    while (infile >> id && infile >> name && infile >> dId)
    {
        Worker* worker = nullptr;
        switch (dId)
        {
        case 1:
            worker = new Employee(id,name,dId);
            break;
        case 2:
            worker = new Manager(id, name, dId);
            break;
        case 3:
            worker = new Boss(id, name, dId);
            break;
        default:
            break;
        }
        this->m_workers.push_back(worker);
    }
}
void WorkerManager::showEmp()
{
    for (auto worker : this->m_workers)
    {
        cout << "职工编号" << worker->m_Id << " "
            << "职工姓名" << worker->m_Name << " "
            << "部门编号" << worker->m_DepId << endl;
    }
    system("pause");
}
void WorkerManager::delEmp()
{
    cout << "请输入要删除职工的编号" << endl;
    int id;
    cin >> id;
    Worker* worker = this->findEmp(id);
    if (worker == nullptr)
    {
        cout << "该员工不存在" << endl;
        return;
    }
    this->m_workers.erase(find(m_workers.begin(),m_workers.end(),worker));
    this->save();//将文件覆盖掉
    cout << "删除成功" << endl;
    system("pause");
}
Worker* WorkerManager::findEmp(int id)
{
    Worker* obj = nullptr;
    for (auto worker : this->m_workers)
    {
        if (worker->m_Id == id)
        {
            obj = worker;
            break;
        }
    }
    return obj;
}
Worker* WorkerManager::findEmp(string name)
{
    Worker* obj = nullptr;
    for (auto worker : this->m_workers)
    {
        if (worker->m_Name == name)
        {
            obj = worker;
            break;
        }
    }
    return obj;
}
void WorkerManager::alterEmp()
{
    cout << "1.按编号查找" << endl;
    cout << "2.按姓名查找" << endl;
    int op; cin >> op;
    int id;
    string name;
    Worker* worker = nullptr;
    if (op == 1) {
        cout << "请输入要更改信息员工的编号" << endl;
        cin >> id;
        worker = this->findEmp(id);
        while (worker == nullptr)
        {
            cout << "该编号不存在，请重新输入！" << endl;
            cin >> id;
            worker = this->findEmp(id);
        }
    }
    else
    {
        cout << "请输入要更改信息员工的姓名" << endl;
        cin >> name;
        worker = this->findEmp(name);
        while (worker == nullptr)
        {
            cout << "该姓名不存在，请重新输入！" << endl;
            cin >> name;
            worker = this->findEmp(name);
        }
    }
    int pos = find(this->m_workers.begin(), this->m_workers.end(), worker) - this->m_workers.begin() - 1;
    int dId;
    cout << "请输入该员工的姓名" << endl;
    cin >> name;
    cout << "请选择该职工的岗位：" << endl;
    cout << "1.普通职工" << endl;
    cout << "2.经理" << endl;
    cout << "3.总裁" << endl;
    cin >> dId;
    switch (dId)
    {
    case 1:
        worker = new Employee(id, name, 1);
        break;
    case 2:
        worker = new Manager(id, name, 2);
        break;
    case 3:
        worker = new Boss(id, name, 3);
        break;
    default:
        break;
    }
    this->m_workers[pos] = worker;
    cout << "修改成功！" << endl;
    system("pause");
}
void m_sort(int L, int R, vector<Worker*>&vec,int op)
{
    int l = L, r = R;
    if (l > r) return;
    Worker* temp = vec.front();
    if (op == 1)
    {
        while (l < r)
        {
            while (l < r && vec[r]->m_Id > temp->m_Id)r--;
            vec[l] = vec[r];
            while (l < r && vec[l]->m_Id <= temp->m_Id)l++;
            vec[r] = vec[l];
        }
        vec[l] = temp;
    }
    else
    {
        while (l < r)
        {
            while (l < r && vec[r]->m_Id < temp->m_Id)r--;
            vec[l] = vec[r];
            while (l < r && vec[l]->m_Id >= temp->m_Id)l++;
            vec[r] = vec[l];
        }
        vec[l] = temp;
    }
    m_sort(L, l - 1, vec, op);
    m_sort(l + 1, R, vec, op);
    return;
}
void WorkerManager::sortEmp()
{
    cout << "1.按编号升序排序" << endl;
    cout << "2.按编号降序排序" << endl;
    int op;
    cin >> op;
    m_sort(0, this->m_workers.size() - 1, this->m_workers,op);
    this->save();
    cout << "排序完毕" << endl;
    system("pause");
}
void WorkerManager::clearEmp()
{
    this->m_workers.clear();
    this->save();
    cout << "清理完毕" << endl;
    system("pause");
}