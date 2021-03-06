
// EVP_Authenticated_MFCDlg.h: 头文件
//
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include<stdio.h>
#include <openssl/rand.h>
#include<iostream>
#include<string.h>
#include <ctime>
#include <WinSock2.h>

#pragma once


// CEVPAuthenticatedMFCDlg 对话框
class CEVPAuthenticatedMFCDlg : public CDialogEx
{
// 构造
public:
	CEVPAuthenticatedMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EVP_AUTHENTICATED_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现

public:
	int getFileSizeSystemCall(char * strFileName);
	void encrypt(char *Path1, unsigned char *aad, char *Path2, unsigned char *salt, int salt_len, int aad_len, const char *passwd);
	void handleErrors();
	int decrypt(unsigned char *Path1, unsigned char *password, unsigned char *Path2);

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString Plaintext_P;
	CString Ciphertext_P;
	CString Password;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	double F_s;
	CString V;
};
