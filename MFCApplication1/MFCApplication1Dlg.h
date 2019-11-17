
// MFCApplication1Dlg.h : 头文件
//

#pragma once
//wb第一步
#include <opencv2/core/core.hpp>
using namespace cv;

// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//wb第二步
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
