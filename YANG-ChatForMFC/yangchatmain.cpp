// yangchatmain.cpp: 实现文件
//

#include "pch.h"
#include "YANG Chat.h"
#include "afxdialogex.h"
#include "yangchatmain.h"
#include <json/json.h>
#include <fstream>
#pragma warning(disable:4996)
// yangchatmain 对话框

IMPLEMENT_DYNAMIC(yangchatmain, CDialogEx)

yangchatmain::yangchatmain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

yangchatmain::~yangchatmain()
{
}

void yangchatmain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(yangchatmain, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &yangchatmain::OnBnClickedButton1)

END_MESSAGE_MAP()


// yangchatmain 消息处理程序



// pass1 消息处理程序
#include <afxinet.h>
CString yangchatmain::UTF8ToUnicode25(char* UTF8)
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
#define _UNICODE
#include <tchar.h>


void yangchatmain::OnBnClickedButton1()
{
	CString url2;
	GetDlgItem(IDC_EDIT1)->GetWindowText(url2);
	wchar_t* unicodeStr = url2.GetBuffer();
	int unicodeLen = url2.GetLength();

	std::string utf8Str;
	for (int i = 0; i < unicodeLen; i++) {
		wchar_t ch = unicodeStr[i];
		if (ch < 0x80) {
			utf8Str += static_cast<char>(ch);
		}
		else if (ch < 0x800) {
			utf8Str += static_cast<char>((ch >> 6) | 0xc0);
			utf8Str += static_cast<char>((ch & 0x3f) | 0x80);
		}
		else {
			utf8Str += static_cast<char>((ch >> 12) | 0xe0);
			utf8Str += static_cast<char>(((ch >> 6) & 0x3f) | 0x80);
			utf8Str += static_cast<char>((ch & 0x3f) | 0x80);
		}
	}

	CString encodedUrl;
	int utf8Len = utf8Str.length();
	for (int i = 0; i < utf8Len; i++) {
		unsigned char ch = utf8Str[i];
		char hexStr[4];
		sprintf_s(hexStr, 4, "%%%02X", ch);
		encodedUrl += CString(hexStr);
		
	}
	// TODO: 在此添加控件通知处理程序代码
	int num2;
	CString asd = _T("http://www.emmapi.com/chatgpt?text=");
	CString asd1 = asd + encodedUrl;
	// TODO: 在此添加控件通知处理程序代码
	CInternetSession session(_T("HttpClient"));
	TCHAR* url = asd1.GetBuffer();;//https://v1.apigpt.cn/?q=你好&apitype=sql
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
		content = UTF8ToUnicode25(pch);//转换编码，不然就乱码了
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
			CString chatgpt = _T("YANG Chat:\n") + temp;
			SetDlgItemText(IDC_RICHEDIT21, chatgpt);
			//temp2 = root["data"][0]["desc"].asCString();
		

		}

	}
	pfile->Close();
	delete pfile;
	session.Close();




}

