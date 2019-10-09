#include "stdafx.h"
#include "Expression.h"

// 构造函数
Expression::Expression( string str ):
	expr(str),
	idx(0),
	err(0),
	Right(1)
{

}

// 外部接口
int Expression::test()
{
	if(!word.empty())  // 已经test过了
	{
		return Right;
	}

	int err_num = word_analysis(word, expr); //词法分析
	if (-1 == err_num)		
	{
		//词法分析错误
		Right = -1;
	}
	else
	{
		// 词法正确，进行语法分析
		Next();
		E();
		if (sym == 0 && err == 0)  // 注意要判断两个条件
			Right = 1;
		else
			Right = -2;
	}
	return Right;
}

//计算算术表达式值
double Expression::calculate()
{
	if (test()>0)
	{
		return expCalculate(getPostfix(word));//getPostfix（）生成后缀表达式  expCalculate（）求值
	}
	else
	{
		exit(0);
	}
}

/*--------------------------------词法分析----------------------------*/
int Expression::word_analysis(vector<pair<string, int>>& word, const string expr)
{
	for (int i = 0; i<expr.length(); ++i)
	{
		// 如果是 + - x ÷ ( )
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
		// 如果是数字开头 
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
					return -1;  // .后面不是数字，词法错误
				}
			}
			word.push_back(make_pair(tmp, 5));
			--i;
		}
		else // 如果以.开头
		{
			return -1;  // 以.开头，词法错误
		}
	}
	return 0;
}

/*--------------------------------语法分析----------------------------*/
// 读下一单词的种别码
void Expression::Next()
{   
	if(idx < word.size())
		sym = word[idx++].second;
	else
		sym = 0;
}

// E → E + T | E - T | T
//
void Expression::E()
{
	// E → T { +T | -T }
	while(sym == 1 || sym == 2)
	{
		Next();
		T();
	}
}


// T → F * T | F / T | F
void Expression::T()
{
	// T → F { *F | /F }
	while(sym == 3 || sym == 4)
	{
		Next();
		F();
	}
}

// F → (E) | d
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

//比较运算符优先级（用于后缀表达式生成）
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
//判断是否为运算符（+ - * /）
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

//生成后缀表达式
vector<pair<string,int>> Expression::getPostfix( const vector<pair<string,int>>& expr)
{
	vector<pair<string, int>> output;  // 输出栈
	stack<pair<string, int>> s;        // 操作符栈（暂时存储运算符）
	for(int i=0; i<expr.size(); ++i)
	{
		pair<string, int> p = expr[i];
		if(isOperator(p.second))
		{
			//处理运算符
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

//计算后缀表达式
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

