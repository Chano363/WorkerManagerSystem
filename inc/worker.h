#pragma once
#include<iostream>
#include<string>
using namespace std;
class Worker
{
public:
    virtual void showInfo()//显示个人信息
    {
        cout << "职工编号：\t" << this->m_Id
            << "职工姓名：\t" << this->m_Name
            << "岗位：" << this->getDeptName();
    }
    virtual string getDeptName() = 0;//获取岗位名称
    int m_Id;//职工编号
    string m_Name;//职工姓名
    int m_DepId;//职工所在部门名称编号
};
