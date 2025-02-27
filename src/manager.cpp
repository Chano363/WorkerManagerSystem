#include"manager.h"
Manager::Manager(int id,string name,int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DepId = dId;
}
void Manager::showInfo()
{
    Worker::showInfo();
    cout<<"\t岗位职责：完成老板交给的任务，并下发任务给员工"<<endl;
}
string Manager::getDeptName()
{
    return string("经理");
}