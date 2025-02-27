#include<iostream>
#include<string>
#include"employee.h"
using namespace std;

Employee::Employee(int id,string name,int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DepId = dId;
}
void Employee::showInfo()
{
    Worker::showInfo();
    cout<<"\t岗位职责：完成经理交给的任务"<<endl;
}
string Employee::getDeptName()
{
    return string("员工");
}