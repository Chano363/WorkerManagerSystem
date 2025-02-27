#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include"worker.h"

#define FILENAME "empFile.txt"
class WorkerManager
{
public:
    WorkerManager();
    ~WorkerManager();
    void clearScreen();
    void showMenu();
    void exitSystem();
    void addEmp();//添加职工
    void save();
    int  get_EmpNum();
    void init_Emp();
    void showEmp();
    void delEmp();
    Worker* findEmp(int id);
    Worker* findEmp(string name);
    void alterEmp();
    void sortEmp();
    void clearEmp();
private:
    int m_EmpNum;
    vector<Worker*>m_workers;
    bool m_FileIsEmpty;
};