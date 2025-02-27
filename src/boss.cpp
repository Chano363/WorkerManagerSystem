#include"boss.h"
using namespace std;

Boss::Boss(int id,string name,int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DepId = dId;
}
void Boss::showInfo()
{
    Worker::showInfo();
    cout<<"\t岗位职责：管理公司所有事务"<<endl;
}
string Boss::getDeptName()
{
    return string("总裁");
}