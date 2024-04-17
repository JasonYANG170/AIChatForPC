﻿
// YANG ChatDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "YANG Chat.h"
#include "YANG ChatDlg.h"
#include "afxdialogex.h"
#include "yangchatmain.h"
#include "afxdialogex.h"
#include <json/json.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CString edition = _T("V1.0.0");

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
// pass1 消息处理程序
#include <afxinet.h>
CString CYANGChatDlg::UTF8ToUnicode2(char* UTF8)
{

	DWORD dwUnicodeLen;        //转换后Unicode的长度
	TCHAR* pwText;            //保存Unicode的指针
	CString strUnicode;        //返回值
	//获得转换后的长度，并分配内存
	dwUnicodeLen = MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, NULL, 0);
	pwText = new TCHAR[dwUnicodeLen];
	if (!pwText)
	{
		return strUnicode;
	}
	//转为Unicode
	MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, pwText, dwUnicodeLen);
	//转为CString
	strUnicode.Format(_T("%s"), pwText);
	//清除内存
	delete[]pwText;
	//返回转换好的Unicode字串
	return strUnicode;
}


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CYANGChatDlg 对话框



CYANGChatDlg::CYANGChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_YANG_CHAT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYANGChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CYANGChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CYANGChatDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CYANGChatDlg 消息处理程序

BOOL CYANGChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CYANGChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CYANGChatDlg::OnPaint()
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

	CInternetSession session(_T("HttpClient"));
	TCHAR* url = _T("https://api.vvhan.com/api/qqsc?key=8f2807e6a7ebfbc168f4a1ecad286283");
	CHttpFile* pfile = (CHttpFile*)session.OpenURL(url);
	DWORD dwStatusCode;
	pfile->QueryInfoStatusCode(dwStatusCode);
	if (dwStatusCode == HTTP_STATUS_OK)
	{
		CString content;
		CString data;
		while (pfile->ReadString(data))
		{
			content += data;
		}
		char* pch;
		pch = new char[content.GetLength() * sizeof(TCHAR) + 1];
		memcpy(pch, content, content.GetLength() * sizeof(TCHAR));
		content = UTF8ToUnicode2(pch);//转换编码，不然就乱码了
		//AfxMessageBox(content);
		//CString content2;
	//	content2 = content.Left(content.Find('r'));
	//	content2 = content2.Right(content.GetLength() - 1 - content.ReverseFind(':'));
		//CString contenta;
	//	contenta = content.Left(content.Find('a'));
		//contenta = content.Right(content.GetLength() - 1 - content.ReverseFind(':'));

		CString str = content;
		Json::Reader reader;
		Json::Value root;
		CString temp;
		CString temp2;
		CString temp3;
		CString temp4;
		CString temp5;
		CString temp6;
		USES_CONVERSION;
		char* cJson = T2A(str.GetBuffer(0));
		str.ReleaseBuffer();
		if (reader.parse(cJson, root)) {
			temp = root["text"].asCString();
			//temp2 = root["data"][0]["desc"].asCString();
			if (edition == temp) {
				//MessageBox(temp);
			}
			else {
				CString tp = _T("已发布新版本\"");
				CString tp2 = _T("\"，为确保稳定性，请尽快更新！");
				CString tp3 = tp + temp + tp2;
				MessageBox(tp3);
			}
			//MessageBox(temp);

		}

	}
	pfile->Close();
	delete pfile;
	session.Close();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CYANGChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CYANGChatDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int num2;
	// TODO: 在此添加控件通知处理程序代码
	CInternetSession session(_T("HttpClient"));
	TCHAR* url = _T("https://api.vvhan.com/api/qqsc?key=492fa5701060de4b2f30e08cbbe2defe");
	CHttpFile* pfile = (CHttpFile*)session.OpenURL(url);
	DWORD dwStatusCode;
	pfile->QueryInfoStatusCode(dwStatusCode);
	if (dwStatusCode == HTTP_STATUS_OK)
	{
		CString content;
		CString data;
		while (pfile->ReadString(data))
		{
			content += data;
		}
		char* pch;
		pch = new char[content.GetLength() * sizeof(TCHAR) + 1];
		memcpy(pch, content, content.GetLength() * sizeof(TCHAR));
		content = UTF8ToUnicode2(pch);//转换编码，不然就乱码了
		//AfxMessageBox(content);
		//CString content2;
	//	content2 = content.Left(content.Find('r'));
	//	content2 = content2.Right(content.GetLength() - 1 - content.ReverseFind(':'));
		//CString contenta;
	//	contenta = content.Left(content.Find('a'));
		//contenta = content.Right(content.GetLength() - 1 - content.ReverseFind(':'));

		CString str = content;
		Json::Reader reader;
		Json::Value root;
		CString temp;
		CString temp2;
		CString temp3;
		CString temp4;
		CString temp5;
		CString temp6;
		USES_CONVERSION;
		char* cJson = T2A(str.GetBuffer(0));
		str.ReleaseBuffer();
		if (reader.parse(cJson, root)) {
			temp = root["text"].asCString();
			//temp2 = root["data"][0]["desc"].asCString();
		//	MessageBox(temp);
			num2 = _ttoi(temp);
		}

	}
	pfile->Close();
	delete pfile;
	session.Close();

	CString passw1;
	GetDlgItem(IDC_EDIT1)->GetWindowText(passw1);
	int num = _ttoi(passw1);
	if (num == num2) {
		//this->ShowWindow(SW_HIDE);
		yangchatmain dlg;
		dlg.DoModal();
	}
	else {
		MessageBox(_T("密码错误，请重新输入或寻求开发者帮助。"));
	}
	

}
