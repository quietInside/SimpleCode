#include "stdafx.h"
#include "Expression.h"

// ���캯��
Expression::Expression( string str ):
	expr(str),
	idx(0),
	err(0),
	Right(1)
{

}

// �ⲿ�ӿ�
int Expression::test()
{
	if(!word.empty())  // �Ѿ�test����
	{
		return Right;
	}

	int err_num = word_analysis(word, expr); //�ʷ�����
	if (-1 == err_num)		
	{
		//�ʷ���������
		Right = -1;
	}
	else
	{
		// �ʷ���ȷ�������﷨����
		Next();
		E();
		if (sym == 0 && err == 0)  // ע��Ҫ�ж���������
			Right = 1;
		else
			Right = -2;
	}
	return Right;
}

//�����������ʽֵ
double Expression::calculate()
{
	if (test()>0)
	{
		return expCalculate(getPostfix(word));//getPostfix�������ɺ�׺���ʽ  expCalculate������ֵ
	}
	else
	{
		exit(0);
	}
}

/*--------------------------------�ʷ�����----------------------------*/
int Expression::word_analysis(vector<pair<string, int>>& word, const string expr)
{
	for (int i = 0; i<expr.length(); ++i)
	{
		// ����� + - x �� ( )
		if (expr[i] == '(' || expr[i] == ')' || expr[i] == '+'
			|| expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
		{
			string tmp;
			tmp.push_back(expr[i]);
			switch (expr[i])
			{
			case '+':
				word.push_back(make_pair(tmp, 1));
				break;
			case '-':
				word.push_back(make_pair(tmp, 2));
				break;
			case '*':
				word.push_back(make_pair(tmp, 3));
				break;
			case '/':
				word.push_back(make_pair(tmp, 4));
				break;
			case '(':
				word.push_back(make_pair(tmp, 6));
				break;
			case ')':
				word.push_back(make_pair(tmp, 7));
				break;
			}
		}
		// ��������ֿ�ͷ 
		else if ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == ' ')
		{
			string tmp;
			while ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == ' ')
			{
				if (expr[i] == ' ')
					++i;
				else{
					tmp.push_back(expr[i]);
					++i;
				}
			}
			if (expr[i] == '.')
			{
				++i;
				if ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == ' ')
				{
					tmp.push_back('.');
					while ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == ' ')
					{
						if (expr[i] == ' ')
							++i;
						else{
							tmp.push_back(expr[i]);
							++i;
						}
					}
				}
				else
				{
					return -1;  // .���治�����֣��ʷ�����
				}
			}
			word.push_back(make_pair(tmp, 5));
			--i;
		}
		else // �����.��ͷ
		{
			return -1;  // ��.��ͷ���ʷ�����
		}
	}
	return 0;
}

/*--------------------------------�﷨����----------------------------*/
// ����һ���ʵ��ֱ���
void Expression::Next()
{   
	if(idx < word.size())
		sym = word[idx++].second;
	else
		sym = 0;
}

// E �� E + T | E - T | T
//
void Expression::E()
{
	// E �� T { +T | -T }
	while(sym == 1 || sym == 2)
	{
		Next();
		T();
	}
}


// T �� F * T | F / T | F
void Expression::T()
{
	// T �� F { *F | /F }
	while(sym == 3 || sym == 4)
	{
		Next();
		F();
	}
}

// F �� (E) | d
void Expression::F()
{
	if (sym == 5)
	{
		Next();
	}
	else if(sym == 6)
	{
		Next();
		E();
		if (sym == 7)
		{
			Next();
		}
		else
		{
			err = -1;
		}
	}
	else
	{
		err = -1;
	}
}

//�Ƚ���������ȼ������ں�׺���ʽ���ɣ�
int Expression::prior(int sym)
{
	switch (sym)
	{
	case 1:
	case 2:
		return 1;
	case 3:
	case 4:
		return 2;
	default:
		return 0;
	}
}
//�ж��Ƿ�Ϊ�������+ - * /��
bool Expression::isOperator(int sym)
{
	switch (sym)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		return true;
	default:
		return false;
	}
}

//���ɺ�׺���ʽ
vector<pair<string,int>> Expression::getPostfix( const vector<pair<string,int>>& expr)
{
	vector<pair<string, int>> output;  // ���ջ
	stack<pair<string, int>> s;        // ������ջ����ʱ�洢�������
	for(int i=0; i<expr.size(); ++i)
	{
		pair<string, int> p = expr[i];
		if(isOperator(p.second))
		{
			//���������
			while(!s.empty() && isOperator(s.top().second) && prior(s.top().second)>=prior(p.second))
			{
				output.push_back(s.top());
				s.pop();
			}
			s.push(p);
		}
		else if(p.second == 6)
		{

			s.push(p);
		}
		else if(p.second == 7)
		{
			while(s.top().second != 6)
			{
				output.push_back(s.top());
				s.pop();
			}
			s.pop();
		}
		else
		{
			output.push_back(p);
		}
	}
	while (!s.empty())
	{
		output.push_back(s.top());
		s.pop();
	}
	return output;
}


void Expression::popTwoNumbers( stack<double>& s, double& first, double& second )
{
	first = s.top();
	s.pop();
	second = s.top();
	s.pop();
}

double Expression::stringToDouble( const string& str )
{
	double d;
	stringstream ss;
	ss << str;
	ss >> d;
	return d;
}
vector<pair<string, int>>& Expression::GetSymbol()
{
	return word;
}

string Expression::GetPostfix()
{
	return m_Postfix;
}
void Expression::SetPostfix(const vector<pair<string, int>>& postfix)
{
	for (int i = 0; i < postfix.size(); ++i)
	{
		m_Postfix = m_Postfix + postfix[i].first + " ";
	}
}

//�����׺���ʽ
double Expression::expCalculate( const vector<pair<string,int>>& postfix )
{
	SetPostfix(postfix);
	double first,second;
	stack<double> s;
	for(int i=0; i<postfix.size(); ++i)
	{
		pair<string,int> p = postfix[i];
		switch (p.second)
		{
		case 1:
			popTwoNumbers(s, first, second);
			s.push(second+first);
			break;
		case 2:
			popTwoNumbers(s, first, second);
			s.push(second-first);
			break;
		case 3:
			popTwoNumbers(s, first, second);
			s.push(second*first);
			break;
		case 4:
			popTwoNumbers(s, first, second);
			s.push(second/first);
			break;
		default:
			s.push(stringToDouble(p.first));
			break;
		}
	}
	double result = s.top();
	s.pop();
	return result;
}

