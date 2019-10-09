
// CalculatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCalculatorDlg �Ի���



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


// CCalculatorDlg ��Ϣ�������

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CFont* m_font = new CFont; //��ʼ������
	m_font->CreateFont(36,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS,_T("Arial"));
	mEdit.SetFont(m_font,FALSE);
	lastPress = false;


	//listcontrol�ؼ��б��ʼ��
	CRect rect;
	CListCtrl *t = (CListCtrl *)GetDlgItem(IDC_LIST2);
	t->GetClientRect(&rect);
	t->ModifyStyle(0, LVS_REPORT);
	t->InsertColumn(0, _T("No"), LVCFMT_CENTER, rect.Width() / 3, 0);
	t->InsertColumn(1, _T("Type"), LVCFMT_CENTER, rect.Width() / 3, 1);
	t->InsertColumn(2, _T("Value"), LVCFMT_CENTER, rect.Width() / 3, 2);


	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// �����һ�ΰ����ǡ�=����ť������
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
	// ���֡�1����ť
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
	// ���֡�2����ť
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
	// ���֡�3����ť
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
	// ���֡�4����ť
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
	// ���֡�5����ť
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
	// ���֡�6����ť
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
	// ���֡�7����ť
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
	// ���֡�8����ť
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
	// ���֡�9����ť
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
	// ���֡�0����ť
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
	// ����������ť
	mEdit.SetWindowText(_T(""));
	m_Postfix.SetWindowText(_T(""));
	m_expression.SetWindowText(_T(""));
	CListCtrl *t = (CListCtrl *)GetDlgItem(IDC_LIST2);
	t->DeleteAllItems();
	mEdit.SetFocus();
}


void CCalculatorDlg::OnBnClickedBack()
{
	// �����ˡ���ť
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
	// �������š���ť
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
	// �������š���ť
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
	// "."��ť
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
	// �Ӻ�
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
	// ����
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
	// �˺�
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
	// ����
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
	// �Ⱥţ�������
	CString str;
	mEdit.GetWindowText(str);
	m_expression.SetWindowTextW(str);
	//if(str.Find('+')==-1 && str.Find('-')==-1 && str.Find('*')==-1 && str.Find('/')==-1)
		//return;
	//else
	lastPress = true;

	CT2CA pszConvertedAnsiString(str);  // �� TCHAR ת��Ϊ LPCSTR
	string exp_str(pszConvertedAnsiString); // �� LPCSTR ���� string

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
				str = "�ʷ��������";
			else
				str = "�﷨�������";
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

//���ؼǺ�����Ӧ�ķ���
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


