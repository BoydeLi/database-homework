#include "p0_starter.h"
#include <vector>
#include <iostream>
using namespace std;
using namespace scudb;
int main(void)
{
	RowMatrix<int> a1(3,3);
	RowMatrix<int> a2(3,3);
	RowMatrix<int> a3(3,3);
	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	int input;
	cout << "�������һ��" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> input;
			v1.push_back(input);
		}
	}
	cout << "����������" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> input;
			v2.push_back(input);
		}
	}
	cout << "�����������" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> input;
			v3.push_back(input);
		}
	}
	a1.FillFrom(v1);
	a2.FillFrom(v2);
	a3.FillFrom(v3);
	cout << endl;
	cout << "���ھ���һ��" << endl;
	cout << "���������"<<a1.GetRowCount()<<endl;
	cout << "���������" << a1.GetColumnCount() << endl;
	cout << "�õ���һ��Ԫ�أ�" << a1.GetElement(0, 0) << endl;
	a1.SetElement(0, 0, 2);
	cout << "�ı��һ��Ԫ�ص�ֵΪ2  ----  " << "���´�ӡֵΪ:" << a1.GetElement(0, 0)<<endl;


	RowMatrixOperations<int> o1;
	
	std::unique_ptr<RowMatrix<int>> result_add = o1.Add(&a1, &a2);
	cout << endl;
	cout << "����1��2��ӵĽ����" << endl;
	for (int i = 0; i < result_add->GetRowCount(); i++)
	{
		for (int j = 0; j < result_add->GetColumnCount(); j++)
		{
			cout << result_add->GetElement(i, j)<<"  ";
		}
		cout << endl;
	}
	
	std::unique_ptr<RowMatrix<int>> result_multi = o1.Multiply(&a1, &a2);
	cout << endl;
	cout << "����1��2��˵Ľ����" << endl;
	for (int i = 0; i < a1.GetRowCount(); i++)
	{
		for (int j = 0; j < a2.GetColumnCount(); j++)
		{
			cout << result_multi->GetElement(i, j) << "  ";
		}
		cout << endl;
	}

	std::unique_ptr<RowMatrix<int>> result_gemm = o1.GEMM(&a1, &a2, &a3);
	cout << endl;
	cout << "����1��2��3�������Ľ����" << endl;
	for (int i = 0; i < a3.GetRowCount(); i++)
	{
		for (int j = 0; j < a3.GetColumnCount(); j++)
		{
			cout << result_gemm->GetElement(i, j) << "  ";
		}
		cout << endl;
	}
	return 0;
}