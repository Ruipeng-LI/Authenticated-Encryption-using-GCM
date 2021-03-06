
// EVP_Authenticated_MFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "EVP_Authenticated_MFC.h"
#include "EVP_Authenticated_MFCDlg.h"
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


// CEVPAuthenticatedMFCDlg 对话框



CEVPAuthenticatedMFCDlg::CEVPAuthenticatedMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EVP_AUTHENTICATED_MFC_DIALOG, pParent)
	, Plaintext_P(_T(""))
	, Ciphertext_P(_T(""))
	, Password(_T(""))
	, F_s(0)
	, V(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEVPAuthenticatedMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Plaintext_P);
	DDX_Text(pDX, IDC_EDIT2, Ciphertext_P);
	DDX_Text(pDX, IDC_EDIT3, Password);

	DDX_Text(pDX, IDC_EDIT4, F_s);
	DDV_MinMaxDouble(pDX, F_s, 0, DBL_MAX);
	DDX_Text(pDX, IDC_EDIT5, V);
}

BEGIN_MESSAGE_MAP(CEVPAuthenticatedMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CEVPAuthenticatedMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CEVPAuthenticatedMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CEVPAuthenticatedMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CEVPAuthenticatedMFCDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CEVPAuthenticatedMFCDlg 消息处理程序

BOOL CEVPAuthenticatedMFCDlg::OnInitDialog()
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

void CEVPAuthenticatedMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEVPAuthenticatedMFCDlg::OnPaint()
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
HCURSOR CEVPAuthenticatedMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEVPAuthenticatedMFCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog dlg(TRUE, NULL, _T("*.*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files (*.*)|*.*||"));
	if (dlg.DoModal() != IDOK) return;

	USES_CONVERSION;
	CString pa = dlg.GetPathName();
	char *PlainF = T2A(pa.GetBuffer(0));
	pa.ReleaseBuffer();
	int size = getFileSizeSystemCall(PlainF);
	double  size1 = size / 1024;
	//获取文件的绝对路径 
	UpdateData();
	Plaintext_P = dlg.GetPathName();
	F_s= size1;
	V = "";
	UpdateData(FALSE);
}
int  CEVPAuthenticatedMFCDlg::getFileSizeSystemCall(char * strFileName)
{
	struct stat temp;
	stat(strFileName, &temp);
	return temp.st_size;
}


void CEVPAuthenticatedMFCDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	BROWSEINFO bi;
	TCHAR path[MAX_PATH];
	ITEMIDLIST *pidl;
	//  
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = 0;
	bi.pszDisplayName = path;
	bi.lpszTitle = _T("请选择查找目录：");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	bi.lpfn = 0;
	bi.lParam = 0;
	bi.iImage = 0;
	if (pidl = SHBrowseForFolder(&bi))
	{
		SHGetPathFromIDList(pidl, path);
		UpdateData();
		Ciphertext_P = path;
		UpdateData(FALSE);
	}
}


void CEVPAuthenticatedMFCDlg::OnBnClickedButton3()   //加密
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData();
	UpdateData(FALSE);
	clock_t start, finish;
	start = clock();

	USES_CONVERSION;
	CString P = Plaintext_P;   //明文路径
	char *plain_P = T2A(P.GetBuffer(0));
	P.ReleaseBuffer();

	CString path = Plaintext_P;                       //解密好的明文保存路径
	int local = path.ReverseFind('.');
	int len = path.GetLength();
	path.Delete(0, local);
	CString name("\\Encrypt");
	CString Path = Ciphertext_P + name + path;
	//进行转换
	char *cipher_P = T2A(Path.GetBuffer(0));
	Path.ReleaseBuffer();

	CString pass = Password;
	char *passwd= T2A(pass.GetBuffer(0));
	pass.ReleaseBuffer();

	unsigned char salt[128];
	unsigned char aad[128];
	time_t t = time(&t);
	char *time = ctime(&t);
	RAND_seed(time, sizeof(time));

	RAND_bytes(salt, 128); //生成盐值salt
	RAND_bytes(aad, 128);

	int salt_len = sizeof(salt);
	int aad_len = sizeof(aad);


	encrypt((char *)plain_P, (unsigned char *)aad, (char *)cipher_P, (unsigned char *)salt, salt_len, aad_len, passwd);
	finish = clock();
	MessageBox(_T("加密成功！"), 0, 0);
	double duration = (double)(finish - start);
	duration = duration / 1000;
	double v = (F_s/ 1024) / duration;
	CString str;
	str.Format(_T("%.4f"), v); //格式化输出，%.5f是指保留小数点后5位小数
	UpdateData();
	V = str;
	Plaintext_P = "";
	Ciphertext_P="";
	Password="";
	UpdateData(FALSE);
}
void CEVPAuthenticatedMFCDlg::encrypt(char *Path1, unsigned char *aad, char *Path2, unsigned char *salt, int salt_len, int aad_len, const char *passwd)
{
	EVP_CIPHER_CTX *ctx;
	unsigned char tag[256] = { '\0' };
	int len;
	int ciphertext_len;
	unsigned char ciphertext[1184];  //保存密文的缓冲区
	unsigned char plaintext[1184];   //保存原文的缓冲区
	int plaintext_len;   //读取文件件的长度
	const int  ITERRATIVE_ROUND_FOR_KEY = 3;
	unsigned char key[EVP_MAX_KEY_LENGTH];      //秘钥
	unsigned char iv[EVP_MAX_IV_LENGTH];         //初始向量
	const EVP_CIPHER *type;
	OpenSSL_add_all_ciphers();
	OpenSSL_add_all_digests();
	type = EVP_aes_128_gcm();      //AES加密算法
	EVP_BytesToKey(
		type,
		EVP_md5(),
		salt,
		(const unsigned char *)passwd,
		(int)strlen(passwd),
		ITERRATIVE_ROUND_FOR_KEY,
		key,
		iv
	);


	FILE *fpIn;
	FILE *fp;
	FILE *fpOut;


	//打开待加密文件
	fpIn = fopen((const char *)Path1, "rb");
	if (fpIn == NULL)
	{
		handleErrors();
	}
	//打开保存密文的文件
	fpOut = fopen((const char *)Path2, "wb");
	if (fpOut == NULL)
	{
		fclose(fpIn);
		handleErrors();
	}
	fp = fopen("0.txt", "wb");
	if (fpOut == NULL)
	{
		fclose(fpIn);
		fclose(fpOut);
		handleErrors();
		
	}
	uint32_t eklen_n;

	eklen_n = htonl(aad_len);
	fwrite(&eklen_n, 1, sizeof eklen_n, fpOut);
	fwrite(aad, 1, aad_len, fpOut);


	eklen_n = htonl(salt_len);
	fwrite(&eklen_n, 1, sizeof eklen_n, fpOut);
	fwrite(salt, 1, salt_len, fpOut);



	int line = 0;

	/* Create and initialise the context */
	if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

	/* Initialise the encryption operation. */
	if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL))
		handleErrors();

	/* Set IV length if default 12 bytes (96 bits) is not appropriate */
	if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, sizeof(iv), NULL))
		handleErrors();

	/* Initialise key and IV */
	if (1 != EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv)) handleErrors();

	/* Provide any AAD data. This can be called zero or more times as
	 * required
	 */
	if (1 != EVP_EncryptUpdate(ctx, NULL, &len, aad, aad_len))
		handleErrors();
	/* Provide the message to be encrypted, and obtain the encrypted output.
	 * EVP_EncryptUpdate can be called multiple times if necessary
	 */
	for (;;)
	{
		plaintext_len = fread(plaintext, 1, 1024, fpIn);

		if (plaintext_len <= 0)//读取原文结束
			break;
		//加密

		if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
			handleErrors();
		fwrite(ciphertext, 1, len, fp);//保存密文到文件
		line = len;


	}

	/* Finalise the encryption. Normally ciphertext bytes may be written at
	 * this stage, but this does not occur in GCM mode
	 */
	if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + line, &len)) handleErrors();

	fwrite(ciphertext + line, 1, len, fp);//保存密文到文件


	/* Get the tag */
	if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag))
		handleErrors();
	int tag_len = strlen((const char *)tag);
	eklen_n = htonl(tag_len);
	fwrite(&eklen_n, 1, sizeof eklen_n, fpOut);
	fwrite(tag, 1, tag_len, fpOut);//保存密文到文件





	fclose(fp);
	EVP_CIPHER_CTX_free(ctx);
	fp = fopen("0.txt", "rb");
	if (fpOut == NULL)
	{
		
		fclose(fpIn);
		handleErrors();
		
	}
	for (;;)
	{
		plaintext_len = fread(plaintext, 1, 1024, fp);

		if (plaintext_len <= 0)//读取原文结束
			break;
		fwrite(plaintext, 1, plaintext_len, fpOut);//保存密文到文件
	}
	/* Clean up */

	fclose(fpIn);
	fclose(fpOut);
	fclose(fp);
	remove("0.txt");

}

void CEVPAuthenticatedMFCDlg::handleErrors()
{


	MessageBox(_T("出现错误！"), 0, 0);
	exit(0);
}

void CEVPAuthenticatedMFCDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData();
	UpdateData(FALSE);
	clock_t start, finish;
	start = clock();

	USES_CONVERSION;
	CString P = Plaintext_P;   //明文路径
	char *plain_P = T2A(P.GetBuffer(0));
	P.ReleaseBuffer();

	CString path = Plaintext_P;                       //解密好的明文保存路径
	int local = path.ReverseFind('.');
	int len = path.GetLength();
	path.Delete(0, local);
	CString name("\\F_Decrypt");
	CString Path = Ciphertext_P + name + path;
	//进行转换
	char *cipher_P = T2A(Path.GetBuffer(0));
	Path.ReleaseBuffer();

	CString pass = Password;
	char *passwd = T2A(pass.GetBuffer(0));
	pass.ReleaseBuffer();

	int select=decrypt((unsigned char *)plain_P, (unsigned char *)passwd, (unsigned char *)cipher_P);
	finish = clock();
	if (select == 1)
	{
		MessageBox(_T("解密成功,数据完整！"), 0, 0);
		double duration = (double)(finish - start);
		duration = duration / 1000;
		double v = (F_s / 1024) / duration;
		CString str;
		str.Format(_T("%.4f"), v); //格式化输出，%.5f是指保留小数点后5位小数
		UpdateData();
		V = str;
		Plaintext_P = "";
		Ciphertext_P = "";
		Password = "";
		UpdateData(FALSE);
	}
	
	else
	{
		UpdateData();
		V = "";
		Plaintext_P = "";
		Ciphertext_P = "";
		Password = "";
		UpdateData(FALSE);
	}
}

int CEVPAuthenticatedMFCDlg::decrypt(unsigned char *Path1, unsigned char *password, unsigned char *Path2)
{
	EVP_CIPHER_CTX *ctx;
	unsigned char aad[256];
	unsigned char salt[256];
	unsigned char tag[256] = { '\0' };
	const int  ITERRATIVE_ROUND_FOR_KEY = 3;
	unsigned char key[EVP_MAX_KEY_LENGTH];      //秘钥
	unsigned char iv[EVP_MAX_IV_LENGTH];         //初始向量



	int len;
	int ciphertext_len;
	int ret;
	unsigned char ciphertext[1184];  //保存密文的缓冲区
	unsigned char plaintext[1184];   //保存原文的缓冲区

	FILE *fpIn;
	FILE *fpOut;
	//打开待加密文件
	fpIn = fopen((const char *)Path1, "rb");
	if (fpIn == NULL)
	{
		handleErrors();
	}
	//打开保存密文的文件
	fpOut = fopen((const char *)Path2, "wb");
	if (fpOut == NULL)
	{
		
		fclose(fpIn);
		handleErrors();
	}
	uint32_t eklen_n;
	fread(&eklen_n, 1, sizeof eklen_n, fpIn);
	int aad_len = ntohl(eklen_n);
	if (aad_len > 256)
	{
		MessageBox(_T("密文已经被篡改，拒绝解密"), 0, 0);
		fclose(fpIn);
		fclose(fpOut);
		remove((const char *)Path2);
		return 0;
	}
	fread(aad, 1, aad_len, fpIn);



	fread(&eklen_n, 1, sizeof eklen_n, fpIn);
	int salt_len = ntohl(eklen_n);
	if (salt_len > 256)
	{
		MessageBox(_T("密文已经被篡改，拒绝解密"), 0, 0);
		fclose(fpIn);
		fclose(fpOut);
		remove((const char *)Path2);
		return 0;
	}
	fread(salt, 1, salt_len, fpIn);



	fread(&eklen_n, 1, sizeof eklen_n, fpIn);
	int tag_len = ntohl(eklen_n);
	fread(tag, 1, tag_len, fpIn);

	const EVP_CIPHER *type;
	OpenSSL_add_all_ciphers();
	OpenSSL_add_all_digests();
	type = EVP_aes_128_gcm();      //AES加密算法
	EVP_BytesToKey(
		type,
		EVP_md5(),
		salt,
		(const unsigned char *)password,
		(int)strlen((const char *)password),
		ITERRATIVE_ROUND_FOR_KEY,
		key,
		iv
	);
	if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

	/* Initialise the decryption operation. */
	if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL))
		handleErrors();

	/* Set IV length. Not necessary if this is 12 bytes (96 bits) */
	if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, sizeof(iv), NULL))
		handleErrors();

	/* Initialise key and IV */
	if (!EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv)) handleErrors();

	/* Provide any AAD data. This can be called zero or more times as
	 * required
	 */
	int line = 0;
	if (!EVP_DecryptUpdate(ctx, NULL, &len, aad, aad_len))
		handleErrors();
	for (;;)
	{
		ciphertext_len = fread(ciphertext, 1, 512, fpIn);

		if (ciphertext_len <= 0)//读取原文结束
			break;
		//加密
	/* Provide the message to be decrypted, and obtain the plaintext output.
	 * EVP_DecryptUpdate can be called multiple times if necessary
	 */
		if (!EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
			handleErrors();
		fwrite(plaintext, 1, len, fpOut);//保存密文到文件
		line = len;
	}

	/* Set expected tag value. Works in OpenSSL 1.0.1d and later */
	if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag))
		handleErrors();

	/* Finalise the decryption. A positive return value indicates success,
	 * anything else is a failure - the plaintext is not trustworthy.
	 */
	ret = EVP_DecryptFinal_ex(ctx, plaintext + line, &len);


	

	if (ret > 0)
	{
		/* Success */
		fwrite(plaintext + line, 1, len, fpOut);//保存密文到文件

	}
	else
	{
		/* Verify failed */
		MessageBox(_T("数据已经被篡改，拒绝解密"), 0, 0);
		EVP_CIPHER_CTX_free(ctx);
		fclose(fpIn);
		fclose(fpOut);
		remove((const char *)Path2);
		return 0;
	}

	/* Clean up */
	EVP_CIPHER_CTX_free(ctx);
	fclose(fpIn);
	fclose(fpOut);
	return 1;
}