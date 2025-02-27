#include<iostream>
#include<windows.h>
#include<limits>
#include<cstdlib>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;
void test()
{
    Worker * worker = nullptr;
    worker = new Employee(1,"张三",1);
    worker->showInfo();
    delete worker;
    worker = new Boss(2,"李四",2);
    worker->showInfo();
    delete worker;
    worker = new Manager(3,"王五",3);
    worker->showInfo();
    delete worker;
}
int main()
{
    WorkerManager wm;
    int choice = 0;
    //test();
    while(true)
    {
        wm.showMenu();
        cout<<"please input your choice:"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 0:
                wm.exitSystem();
                break;
            case 1:
                wm.addEmp();
                break;
            case 2:
                wm.showEmp();
                break;
            case 3:
                wm.delEmp();
                break;
            case 4:
                wm.alterEmp();
                break;
            case 5:
                {
                    int id;
                    cout << "请输入要查找信息员工的编号" << endl;
                    cin >> id;
                    Worker* worker = wm.findEmp(id);
                    if (worker == nullptr)
                    {
                        cout << "该员工不存在!" << endl;
                    }
                    else
                    {
                        cout << "该员工姓名为" << worker->m_Name << " "
                            << "该员工职务为" << worker->getDeptName() << endl;
                    }
                    delete worker;
                    system("pause");
                    break;
                }
            case 6:
                wm.sortEmp();
                break;
            case 7:
                wm.clearEmp();
                break;
            default:
                wm.clearScreen();
                break;
        }
        wm.clearScreen();
    }
    system("pause");
    return 0;
}