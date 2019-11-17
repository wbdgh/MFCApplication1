
// MFCApplication1Dlg.h : ͷ�ļ�
//

#pragma once
//wb��һ��
#include <opencv2/core/core.hpp>
using namespace cv;

// CMFCApplication1Dlg �Ի���
class CMFCApplication1Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//wb�ڶ���
	CString m_path;
	Mat src;


	afx_msg void OnBnClickedOpen();
//	CString m_width;
//	CString m_height;
	afx_msg void OnBnClickedResize();
	double m_width;
	double m_height;
	double m_angle;
	afx_msg void OnBnClickedRotation();
	double m_shear_ratio;
	afx_msg void OnBnClickedHshear();
	afx_msg void OnBnClickedVshear();
	int m_PseudoColorMode;
	afx_msg void OnBnClickedHisteq();
	afx_msg void OnBnClickedPseudo();
	afx_msg void OnBnClickedFilter();
	int m_FilterType;
	int m_ShapenType;
	afx_msg void OnBnClickedSharp();
};
