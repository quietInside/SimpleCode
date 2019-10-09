#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

class Expression
{
public:
	Expression(string str);
	int test();         // �ⲿ�ӿڣ��жϱ��ʽ�Ƿ�Ϸ�
	double calculate();  // �ⲿ�ӿڣ�������ʽ��ֵ 
	string GetPostfix(); //��ú�׺���ʽ
	vector<pair<string, int>>& Expression::GetSymbol();  //��÷��ű�
private:
	vector<pair<string, int>> word;	//�ʷ��Ǻ���
	string expr;  // �������ʽ
	int idx;      // word�±�
	int sym;      // �����ֱ����
	int err;      // ����
	int word_analysis(vector<pair<string, int>>& , const string);
	void Next();
	void E();
	void T();
	void F();
	int Right;   // ������ʽtest���
	string m_Postfix;
private:
	int prior(int);        // ��ȡ����������ȼ�
	bool isOperator(int);  // ͨ�� �ֱ���� �ж��Ƿ��������
	vector<pair<string,int>> getPostfix(const vector<pair<string,int>>&);  // ��׺ת��׺
	void popTwoNumbers(stack<double>&, double&, double&);  // ��ջ��������������������
	double stringToDouble(const string&);  // ��stringת��Ϊdouble
	double expCalculate(const vector<pair<string, int>>&);  // �����׺���ʽ��ֵ
	void SetPostfix(const vector<pair<string, int>>& postfix);
};

