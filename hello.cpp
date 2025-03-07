#include<iostream>
using namespace std;
void TestAdd()
{
	int a, b;
	cin >> a >> b;
	if (Add(a, b) == a + b)
	{
		cout << "Success!" << endl;
	}
}
void PrintHello()
{
	cout << "hello!" << endl;
}
