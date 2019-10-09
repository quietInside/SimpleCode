
// CalculatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalculatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, EDIT_SHOW, mEdit);
	DDX_Control(pDX, IDC_EDIT2, m_Postfix);
	DDX_Control(pDX, IDC_EDIT1, m_expression);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BUTTON_1, &CCalculatorDlg::OnBnClicked1)
	ON_BN_CLICKED(BUTTON_2, &CCalculatorDlg::OnBnClicked2)
	ON_BN_CLICKED(BUTTON_3, &CCalculatorDlg::OnBnClicked3)
	ON_BN_CLICKED(BUTTON_4, &CCalculatorDlg::OnBnClicked4)
	ON_BN_CLICKED(BUTTON_5, &CCalculatorDlg::OnBnClicked5)
	ON_BN_CLICKED(BUTTON_6, &CCalculatorDlg::OnBnClicked6)
	ON_BN_CLICKED(BUTTON_7, &CCalculatorDlg::OnBnClicked7)
	ON_BN_CLICKED(BUTTON_8, &CCalculatorDlg::OnBnClicked8)
	ON_BN_CLICKED(BUTTON_9, &CCalculatorDlg::OnBnClicked9)
	ON_BN_CLICKED(BUTTON_0, &CCalculatorDlg::OnBnClicked0)
	ON_BN_CLICKED(BUTTON_CLEAR, &CCalculatorDlg::OnBnClickedClear)
	ON_BN_CLICKED(BUTTON_BACK, &CCalculatorDlg::OnBnClickedBack)
	ON_BN_CLICKED(BUTTON_LEFT, &CCalculatorDlg::OnBnClickedLeft)
	ON_BN_CLICKED(BUTTON_RIGHT, &CCalculatorDlg::OnBnClickedRight)
	ON_BN_CLICKED(BUTTON_DOT, &CCalculatorDlg::OnBnClickedDot)
	ON_BN_CLICKED(BUTTON_ADD, &CCalculatorDlg::OnBnClickedAdd)
	ON_BN_CLICKED(BUTTON_SUB, &CCalculatorDlg::OnBnClickedSub)
	ON_BN_CLICKED(BUTTON_MUL, &CCalculatorDlg::OnBnClickedMul)
	ON_BN_CLICKED(BUTTON_DIV, &CCalculatorDlg::OnBnClickedDiv)
	ON_BN_CLICKED(BUTTON_EQL, &CCalculatorDlg::OnBnClickedEql)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CFont* m_font = new CFont; //初始化字体
	m_font->CreateFont(36,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS,_T("Arial"));
	mEdit.SetFont(m_font,FALSE);
	lastPress = false;


	//listcontrol控件列表初始化
	CRect rect;
	CListCtrl *t = (CListCtrl *)GetDlgItem(IDC_LIST2);
	t->GetClientRect(&rect);
	t->ModifyStyle(0, LVS_REPORT);
	t->InsertColumn(0, _T("No"), LVCFMT_CENTER, rect.Width() / 3, 0);
	t->InsertColumn(1, _T("Type"), LVCFMT_CENTER, rect.Width() / 3, 1);
	t->InsertColumn(2, _T("Value"), LVCFMT_CENTER, rect.Width() / 3, 2);


	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 如果上一次按的是“=”按钮，清屏
void CCalculatorDlg::Clear()
{
	if (lastPress == true)
	{
		mEdit.SetWindowText(_T(""));
		lastPress = false;
	}
}

void CCalculatorDlg::OnBnClicked1()
{
	// 数字“1”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("1");
	mEdit.SetWindowText(str);
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClicked2()
{
	// 数字“2”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("2");
	mEdit.SetWindowText(str);
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClicked3()
{
	// 数字“3”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("3");
	mEdit.SetWindowText(str);
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClicked4()
{
	// 数字“4”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("4");
	mEdit.SetWindowText(str);
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClicked5()
{
	// 数字“5”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("5");
	mEdit.SetWindowText(str);
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClicked6()
{
	// 数字“6”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("6");
	mEdit.SetWindowText(str);
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClicked7()
{
	// 数字“7”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("7");
	mEdit.SetWindowText(str);
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClicked8()
{
	// 数字“8”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("8");
	mEdit.SetWindowText(str);
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClicked9()
{
	// 数字“9”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("9");
	mEdit.SetWindowText(str);
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClicked0()
{
	// 数字“0”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	if (str != "0")
	{
		str = str + _T("0");
		mEdit.SetWindowText(str);
	}
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClickedClear()
{
	// “清屏”按钮
	mEdit.SetWindowText(_T(""));
	m_Postfix.SetWindowText(_T(""));
	m_expression.SetWindowText(_T(""));
	CListCtrl *t = (CListCtrl *)GetDlgItem(IDC_LIST2);
	t->DeleteAllItems();
	mEdit.SetFocus();
}


void CCalculatorDlg::OnBnClickedBack()
{
	// “后退”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str.Left(str.GetLength()-1);
	mEdit.SetWindowText(str);
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClickedLeft()
{
	// “左括号”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
/*	if (str == "")
	{
		str = str + _T("(");
		mEdit.SetWindowText(str);
	}
	else
	{
		if(str.GetAt(str.GetLength()-1)<'0' || str.GetAt(str.GetLength()-1)>'9')
		{
			str = str + _T("(");
			mEdit.SetWindowText(str);
		}
	}*/
	str = str + _T("(");
	mEdit.SetWindowText(str);

	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClickedRight()
{
	// “右括号”按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	/*if(str != "")
	{
		if(str.GetAt(str.GetLength()-1)>='0' && str.GetAt(str.GetLength()-1)<='9')
		{
			str = str + _T(")");
			mEdit.SetWindowText(str);
		}
	}*/
	str = str + _T(")");
	mEdit.SetWindowText(str);

	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClickedDot()
{
	// "."按钮
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	/*if(str != "")
	{
		if(str.GetAt(str.GetLength()-1)>='0' && str.GetAt(str.GetLength()-1)<='9')
		{
			str = str + _T(".");
			mEdit.SetWindowText(str);
		}
	}*/
	str = str + _T(".");
	mEdit.SetWindowText(str);

	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClickedAdd()
{
	// 加号
	lastPress = false;
	CString str;
	mEdit.GetWindowText(str);
	/*if(str != "")
	{
		if(str.GetAt(str.GetLength()-1)!='+' && str.GetAt(str.GetLength()-1)!='-'
			&& str.GetAt(str.GetLength()-1)!='*' && str.GetAt(str.GetLength()-1)!='/')
		{
			str = str + _T("+");
			mEdit.SetWindowText(str);
		}
	}*/
	str = str + _T("+");
	mEdit.SetWindowText(str);

	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClickedSub()
{
	// 减号
	lastPress = false;
	CString str;
	mEdit.GetWindowText(str);
	/*if(str != "")
	{
		if(str.GetAt(str.GetLength()-1)!='+' && str.GetAt(str.GetLength()-1)!='-'
			&& str.GetAt(str.GetLength()-1)!='*' && str.GetAt(str.GetLength()-1)!='/')
		{
			str = str + _T("-");
			mEdit.SetWindowText(str);
		}
	}*/

	str = str + _T("-");
	mEdit.SetWindowText(str);

	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClickedMul()
{
	// 乘号
	lastPress = false;
	CString str;
	mEdit.GetWindowText(str);
	/*if(str != "")
	{
		if(str.GetAt(str.GetLength()-1)!='+' && str.GetAt(str.GetLength()-1)!='-'
			&& str.GetAt(str.GetLength()-1)!='*' && str.GetAt(str.GetLength()-1)!='/')
		{
			str = str + _T("*");
			mEdit.SetWindowText(str);
		}
	}*/
	str = str + _T("*");
	mEdit.SetWindowText(str);

	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClickedDiv()
{
	// 除号
	lastPress = false;
	CString str;
	mEdit.GetWindowText(str);
	/*if(str != "")
	{
		if(str.GetAt(str.GetLength()-1)!='+' && str.GetAt(str.GetLength()-1)!='-'
			&& str.GetAt(str.GetLength()-1)!='*' && str.GetAt(str.GetLength()-1)!='/')
		{
			str = str + _T("/");
			mEdit.SetWindowText(str);
		}
	}*/
	str = str + _T("/");
	mEdit.SetWindowText(str);

	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}


void CCalculatorDlg::OnBnClickedEql()
{
	// 等号，计算结果
	CString str;
	mEdit.GetWindowText(str);
	m_expression.SetWindowTextW(str);
	//if(str.Find('+')==-1 && str.Find('-')==-1 && str.Find('*')==-1 && str.Find('/')==-1)
		//return;
	//else
	lastPress = true;

	CT2CA pszConvertedAnsiString(str);  // 将 TCHAR 转换为 LPCSTR
	string exp_str(pszConvertedAnsiString); // 从 LPCSTR 构造 string

	if (exp_str != "")
	{
		Expression e(exp_str);
		if(e.test()>0)
		{
			string tmp;
			stringstream ss;
			ss << e.calculate();
			ss >> tmp;
			str = tmp.c_str();
		}
		else
		{
			if(e.test()==-1)
				str = "词法输入错误";
			else
				str = "语法输入错误";
		}

		vector<pair<string, int>>& v2 = e.GetSymbol();
		CListCtrl *t = (CListCtrl *)GetDlgItem(IDC_LIST2);
		t->DeleteAllItems();
		for (int i = 0; i < v2.size(); i++)
		{
			CString v1;
			v1.Format(_T("%d"), i);
			t->InsertItem(i,v1);
			t->SetItemText(i, 1, TypeDeal(v2[i].second));
			if (v2[i].second == 5)
			{
				CString v3(v2[i].first.c_str());
				t->SetItemText(i, 2, v3);
			}
		}
		CString v1(e.GetPostfix().c_str());
		m_Postfix.SetWindowText(v1);
		mEdit.SetWindowText(str);
	}
	mEdit.SetFocus();
	mEdit.SetSel(str.GetLength(), str.GetLength());
}

//返回记号名对应的符号
CString CCalculatorDlg::TypeDeal(int ParameterData)
{
	CString v2;
	switch (ParameterData)
	{
	case 1:
		v2 = _T("+");
		break;
	case 2:
		v2 = _T("-");
		break;
	case 3:
		v2 = _T("*");
		break;
	case 4:
		v2 = _T("/");
		break;
	case 5:
		v2 = _T("digit");
		break;
	case 6:
		v2 = _T("(");
		break;
	case 7:
		v2 = _T(")");
		break;
	default:
		break;
	}
	return v2;
}


