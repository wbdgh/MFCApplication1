
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

//wb������
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//wb���Ĳ�
using namespace std;
using namespace cv;

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


// CMFCApplication1Dlg �Ի���



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
	, m_width(0)
	, m_height(0)
	, m_angle(0)
	, m_shear_ratio(0)
	, m_PseudoColorMode(0)
	, m_ShapenType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_WIDTH, m_width);
	//  DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDX_Text(pDX, IDC_ANGLE, m_angle);
	DDX_Text(pDX, IDC_SHEAR_RATIO, m_shear_ratio);
	DDX_Radio(pDX, IDC_RADIO1, m_PseudoColorMode);
	DDX_Radio(pDX, IDC_AVER, m_FilterType);
	DDX_Radio(pDX, IDC_RADIO7, m_ShapenType);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CMFCApplication1Dlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_RESIZE, &CMFCApplication1Dlg::OnBnClickedResize)
	ON_BN_CLICKED(IDC_ROTATION, &CMFCApplication1Dlg::OnBnClickedRotation)
	ON_BN_CLICKED(IDC_HSHEAR, &CMFCApplication1Dlg::OnBnClickedHshear)
	ON_BN_CLICKED(IDC_VSHEAR, &CMFCApplication1Dlg::OnBnClickedVshear)
	ON_BN_CLICKED(IDC_HISTEQ, &CMFCApplication1Dlg::OnBnClickedHisteq)
	ON_BN_CLICKED(IDC_PSEUDO, &CMFCApplication1Dlg::OnBnClickedPseudo)
	ON_BN_CLICKED(IDC_FILTER, &CMFCApplication1Dlg::OnBnClickedFilter)
	ON_BN_CLICKED(IDC_SHARP, &CMFCApplication1Dlg::OnBnClickedSharp)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
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
	namedWindow("view",WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hparent = ::GetParent(hWnd);
	::SetParent(hWnd,GetDlgItem(IDC_PIC)->m_hWnd);
	::ShowWindow(hparent,SW_HIDE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ô�ͼƬ·���Ĵ���
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,NULL);
	dlg.m_ofn.lpstrTitle = _T("��ͼ���ļ�");
	dlg.m_ofn.lpstrInitialDir="C:\\";
	dlg.m_ofn.lpstrFilter = "jpg (*.jpg)\0*.jpg\0bmp (*.bmp)\0*.bmp\0All Files (*.*) \0*.*\0\0";
	//�ж��Ƿ���ͼƬ
	if(dlg.DoModal() != IDOK)
		return;
	m_path = dlg.GetPathName();//��ȡͼƬ����·��
	//���ֽ��ַ����µ�CStringתchar*
	src = imread((LPSTR)(LPCSTR)m_path);

	/****** Unicode�ַ����� CString ת char*
	int nLength = m_path.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP, 0, m_path, nLength, NULL, 0, NULL, NULL);
	char* VoicePath = new char[nBytes + 1];
	memset(VoicePath, 0, nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, m_path, nLength, VoicePath, nBytes, NULL, NULL);
	VoicePath[nBytes] = 0;
	src = imread(VoicePath);
	*/


	//��ʾͼƬ
	Mat img;//�������ź��ͼƬ
	CRect rect;
	
	GetDlgItem(IDC_PIC)->GetClientRect(&rect);//��ȡͼ����ʾ��
	resize(src,img,Size(rect.Width(),rect.Height()),0,0);
	imshow("view",img);

	
}


void CMFCApplication1Dlg::OnBnClickedResize()
{
	// TODO: ���Ű�ť
	UpdateData(TRUE);
	Mat dst;
	resize(src,dst,Size(m_width,m_height),0,0);
	imshow("���ź�ͼ��",dst);
}


void CMFCApplication1Dlg::OnBnClickedRotation()
{
	// TODO: ��ת��ť
	UpdateData(TRUE);

	Mat rot_mat(2, 3, CV_32FC1);//��ת�任����
	Mat rotate_dst;
	
	// ������ת��ͼ��ߴ�
	double a = sin(m_angle  * CV_PI / 180);
	double b = cos(m_angle  * CV_PI / 180);
	int width = src.cols;
	int height = src.rows;
	int width_rotate = int(height * fabs(a) + width * fabs(b));
	int height_rotate = int(width * fabs(a) + height * fabs(b));

	//����ͼ����ת�任����
	Point center = Point(src.cols / 2, src.rows / 2);
	double angle = m_angle;
	double scale = 1;
	rot_mat = getRotationMatrix2D(center, angle, scale); 

	// �޸�����ƫ��
	rot_mat.at<double>(0, 2) += (width_rotate - width) / 2;    
	rot_mat.at<double>(1, 2) += (height_rotate - height) / 2; 

	/// ��תͼ��
	warpAffine(src, rotate_dst, rot_mat, Size(width_rotate, height_rotate));

	namedWindow("��ת��ͼ��");
	imshow("��ת��ͼ��", rotate_dst);

}


void CMFCApplication1Dlg::OnBnClickedHshear()
{
	// TODO: ˮƽ���а�ť
	UpdateData(TRUE);

	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	//������к�ͼ���С
	double ratio = m_shear_ratio;
	int dst_wid;
	int dst_hei;

	if (ratio < 0)
	{
		dst_wid = g_src.cols + g_src.rows*ratio*(-1);
	}
	else 
	{
		dst_wid = g_src.cols + g_src.rows*ratio;
	}

	dst_hei = g_src.rows;

	dst.create(Size(dst_wid, dst_hei), g_src.type());

	for (int i = 0; i<g_src.rows; i++)
	{
		if (ratio >= 0)
		for (int j = 0; j<g_src.cols; j++)
		{
			dst.at<uchar>(i, j + i*ratio) = g_src.at<uchar>(i, j);
		}
		else
		{
			int offset = (-1)*ratio*g_src.rows;
			for (int j = g_src.cols - 1; j >= 0; j--)
			{
				dst.at<uchar>(i, j + i*ratio + offset) = g_src.at<uchar>(i, j);
			}
		}
	}

	namedWindow("ˮƽ����");
	imshow("ˮƽ����", dst);

}


void CMFCApplication1Dlg::OnBnClickedVshear()
{
	// TODO: ��ֱ���а�ť
	UpdateData(TRUE);

	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	//������к�ͼ���С
	double ratio = m_shear_ratio;
	int dst_wid;
	int dst_hei;

	if (ratio < 0)
	{
		dst_hei = g_src.rows + g_src.cols*ratio*(-1);
	}
	else
	{
		dst_hei = g_src.rows + g_src.cols*ratio;
	}

	dst_wid = g_src.cols;

	dst.create(Size(dst_wid, dst_hei), g_src.type());

	for (int i = 0; i<g_src.rows; i++)
	{
		if (ratio >= 0)
		for (int j = 0; j<g_src.cols; j++)
		{
			dst.at<uchar>(i+j*ratio, j) = g_src.at<uchar>(i, j);
		}
		else
		{
			int offset = (-1)*ratio*g_src.cols;
			for (int j = g_src.cols - 1; j >= 0; j--)
			{
				dst.at<uchar>(i+j*ratio+offset, j) = g_src.at<uchar>(i, j);
			}
		}
	}

	namedWindow("��ֱ����");
	imshow("��ֱ����", dst);

}


void CMFCApplication1Dlg::OnBnClickedHisteq()
{
	// TODO: ֱ��ͼ����
	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst.create(g_src.size(), g_src.type());

	equalizeHist(g_src, dst);

	namedWindow("ֱ��ͼ����");
	imshow("ֱ��ͼ����", dst);

}


void CMFCApplication1Dlg::OnBnClickedPseudo()
{
	// TODO: α��ɫ
	Mat g_src, tmp_dst, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);
	dst.create(g_src.size(), CV_8UC3);
	UpdateData(TRUE);
	switch (m_PseudoColorMode)
	{
	case 0:
		for (int i = 0; i<g_src.rows; i++)
		{
			for (int j = 0; j<g_src.cols; j++)
			{
				int tmp = g_src.at<uchar>(i,j);

				if (tmp<60)
				{
					dst.at<Vec3b>(i,j)[0] = 255; //blue
					dst.at<Vec3b>(i, j)[1] = 0; //green
					dst.at<Vec3b>(i, j)[2] = 0; //red
				}
				else if (tmp<150)
				{
					dst.at<Vec3b>(i, j)[0] = 0; //blue
					dst.at<Vec3b>(i, j)[1] = 255; //green
					dst.at<Vec3b>(i, j)[2] = 0; //red				
				}
				else
				{
					dst.at<Vec3b>(i, j)[0] = 0; //blue
					dst.at<Vec3b>(i, j)[1] = 0; //green
					dst.at<Vec3b>(i, j)[2] = 255; //red				
				}
			}
		}
		break;
	case 1:
		for (int i = 0; i<g_src.rows; i++)
		{
			for (int j = 0; j<g_src.cols; j++)
			{
				int tmp = g_src.at<uchar>(i, j);


				if (tmp<64)
				{
					dst.at<Vec3b>(i, j)[0] = 255; //blue
					dst.at<Vec3b>(i, j)[1] = tmp; //green
					dst.at<Vec3b>(i, j)[2] = 0; //red
				}
				else if (tmp<128)
				{
					dst.at<Vec3b>(i, j)[0] = tmp; //blue
					dst.at<Vec3b>(i, j)[1] = 255; //green
					dst.at<Vec3b>(i, j)[2] = 0; //red				
				}
				else if (tmp<192)
				{
					dst.at<Vec3b>(i, j)[0] = 0; //blue
					dst.at<Vec3b>(i, j)[1] = 255; //green
					dst.at<Vec3b>(i, j)[2] = tmp; //red				
				}
				else
				{
					dst.at<Vec3b>(i, j)[0] = 0; //blue
					dst.at<Vec3b>(i, j)[1] = tmp; //green
					dst.at<Vec3b>(i, j)[2] = 255; //red				
				}
			}
		}
		break;
	case 2:
		break;
	}
	imshow("α��ɫ", dst);

}



void CMFCApplication1Dlg::OnBnClickedFilter()
{
	// �˲�
	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst.create(g_src.size(), g_src.type());

	UpdateData(TRUE);

	switch (m_FilterType)
	{
	case 0:
		blur(g_src, dst, Size(5, 5));       //��ֵ�˲�  
		namedWindow("��ֵ�˲�");
		imshow("��ֵ�˲�", dst);
		break;
	case 1:
		medianBlur(g_src, dst, 7);
		imshow("��ֵ�˲�", dst);
		break;
	case 2:
		GaussianBlur(g_src, dst, Size(3, 3), 0, 0);   //��˹�˲�  
		namedWindow("Gaussian�˲�");
		imshow("Gaussian�˲�", dst);
		break;
	}
}


void CMFCApplication1Dlg::OnBnClickedSharp()
{
	// ��
	Mat g_src, dst;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y,abs_dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst.create(g_src.size(), g_src.type());

	UpdateData(TRUE);

	switch (m_ShapenType)
	{
	case 0:
		Sobel(g_src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
		convertScaleAbs(grad_x, abs_grad_x);
		imshow("X����Sobel", abs_grad_x);

		//��4����Y�����ݶ�  
		Sobel(g_src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
		convertScaleAbs(grad_y, abs_grad_y);
		imshow("Y����Sobel", abs_grad_y);

		//��5���ϲ��ݶ�(����)  
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
		/*
		void Sobel (  
		InputArray src,//����ͼ  
		 OutputArray dst,//���ͼ  
		 int ddepth,//���ͼ������  
		 int dx,  
		 int dy,  
		 int ksize=3,  
		 double scale=1,  
		 double delta=0,  
		int borderType=BORDER_DEFAULT ); 
		��һ��������InputArray ���͵�src��Ϊ����ͼ����Mat���ͼ��ɡ�
		�ڶ���������OutputArray���͵�dst����Ŀ��ͼ�񣬺����������������Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
		������������int���͵�ddepth�����ͼ�����ȣ�֧������src.depth()��ddepth����ϣ�
		��src.depth() = CV_8U, ȡddepth =-1/CV_16S/CV_32F/CV_64F
		��src.depth() = CV_16U/CV_16S, ȡddepth =-1/CV_32F/CV_64F
		��src.depth() = CV_32F, ȡddepth =-1/CV_32F/CV_64F
		��src.depth() = CV_64F, ȡddepth = -1/CV_64F
		���ĸ�������int����dx��x �����ϵĲ�ֽ�����
		�����������int����dy��y�����ϵĲ�ֽ�����
		������������int����ksize����Ĭ��ֵ3����ʾSobel�˵Ĵ�С;����ȡ1��3��5��7��
		���߸�������double���͵�scale�����㵼��ֵʱ��ѡ���������ӣ�Ĭ��ֵ��1����ʾĬ���������û��Ӧ�����ŵġ����ǿ������ĵ��в���getDerivKernels����ؽ��ܣ����õ���������ĸ�����Ϣ��
		�ڰ˸�������double���͵�delta����ʾ�ڽ������Ŀ��ͼ���ڶ�������dst��֮ǰ��ѡ��deltaֵ����Ĭ��ֵ0��
		�ھŸ������� int���͵�borderType�����ǵ��������ˣ����������һ�����������߽�ģʽ��Ĭ��ֵΪBORDER_DEFAULT��������������ڹٷ��ĵ���borderInterpolate���õ�����ϸ����Ϣ��
		*/
		namedWindow("sobel");
		imshow("sobel", dst);
		break;

	case 1:
		Laplacian(g_src, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

		//��6���������ֵ���������ת����8λ  
		convertScaleAbs(dst, abs_dst);
		/*
		void Laplacian(InputArray src,OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, intborderType=BORDER_DEFAULT );
		��һ��������InputArray���͵�image������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɣ�����Ϊ��ͨ��8λͼ��
		�ڶ���������OutputArray���͵�edges������ı�Եͼ����Ҫ��ԴͼƬ��һ���ĳߴ��ͨ������
		������������int���͵�ddept��Ŀ��ͼ�����ȡ�
		���ĸ�������int���͵�ksize�����ڼ�����׵������˲����Ŀ׾��ߴ磬��С����Ϊ������������Ĭ��ֵ1��
		�����������double���͵�scale������������˹ֵ��ʱ���ѡ�ı������ӣ���Ĭ��ֵ1��
		������������double���͵�delta����ʾ�ڽ������Ŀ��ͼ���ڶ�������dst��֮ǰ��ѡ��deltaֵ����Ĭ��ֵ0��
		���߸������� int���͵�borderType���߽�ģʽ��Ĭ��ֵΪBORDER_DEFAULT��������������ڹٷ��ĵ���borderInterpolate()���õ�����ϸ����Ϣ��
		*/
		namedWindow("Laplace");
		imshow("Laplace", abs_dst);
		break;
	case 2:
		Canny(g_src, dst, 100, 150, 3);
		/*
		void Canny(InputArray image,OutputArray edges, double threshold1, double threshold2, int apertureSize=3,bool L2gradient=false )
		��һ��������InputArray���͵�image������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɣ�����Ϊ��ͨ��8λͼ��
		�ڶ���������OutputArray���͵�edges������ı�Եͼ����Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
		������������double���͵�threshold1����һ���ͺ�����ֵ��
		���ĸ�������double���͵�threshold2���ڶ����ͺ�����ֵ��
		�����������int���͵�apertureSize����ʾӦ��Sobel���ӵĿ׾���С������Ĭ��ֵ3��
		������������bool���͵�L2gradient��һ������ͼ���ݶȷ�ֵ�ı�ʶ����Ĭ��ֵfalse��
		*/
		namedWindow("Canny");
		imshow("Canny", dst);

	}

}
