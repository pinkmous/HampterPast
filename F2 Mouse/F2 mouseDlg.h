// F2 mouseDlg.h : header file
//
#pragma once
#include "afxwin.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Query.h"
using namespace std;

#define ALPHA_KEY_NO 26
#define AUXI_KEY_NO 20
#define LAMDA_KEY_NO 25
#define KEY_SIZE 40
#define KEY_DISTANCE 50
#define CANDIKEY_NO 8
#define CANDIKEY_SIZE 80
#define CANDIKEY_DISTANCE 85
#define WORD_MAX_LENGTH 100

class StrokePoint 
{
public:
	double x;
	double y;
	double time;
};
typedef vector<StrokePoint> Stroke;

class Key
{
public:
    CString letter;
	CString sletter;
	int size;
	CPoint location;
	bool inKey(CPoint);
};

// CF2mouseDlg dialog
class CF2mouseDlg : public CDialogEx
{
// Construction
public:
	CF2mouseDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_F2MOUSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	bool m_alphaflag;
	bool m_clickflag;
	double m_xpos;
	double m_ypos;
	double m_time;
	CPoint m_oldpoint;
	Stroke stroke;	

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CPoint m_tpos;
	CRect m_tcontrol;
	afx_msg void OnBnClickedPostest1();
	afx_msg void OnBnClickedPostest2();

    //key area general
	RECT m_alphaKeyArea;
	RECT m_auxiKeyArea;
    RECT m_lamdaKeyArea;
	RECT m_candidateArea;

	//alpha key area
	Key m_keys[ALPHA_KEY_NO];
	CString m_alphaalphebet[ALPHA_KEY_NO];
	CString m_salphaalphebet[ALPHA_KEY_NO];
	bool m_lockkey;
	int m_lockno;

	//auxilary key area
	Key m_auxikeys[AUXI_KEY_NO];
	CString m_auxialphebet[AUXI_KEY_NO];

	//lamda key area
	bool m_lamdaflag;
	bool m_capsLock;
	bool m_shift;
	Key m_lamdakeys[LAMDA_KEY_NO];
	CString m_lamdaalphebet[LAMDA_KEY_NO];
	CString m_slamdaalphebet[LAMDA_KEY_NO];

	//candidate key area
	bool m_candiflag;               //for mis-click out of key area
	Key m_candikeys[CANDIKEY_NO];
	CString m_candiword[CANDIKEY_NO];
	Key m_candiPageKey;
	bool m_candiPageflag;

	//display
	void setKeyInformation();
	void drawDisplay(CF2mouseDlg * background);

    //result
    CString m_word;
	CString m_sentence;
	CEdit m_sentEdit;
	int m_candiNo;
	//part2 CSC solution
    wordQuery *m_wQ;
	q_Result   m_qResult;
	int m_candipageno;
	int m_candipageindex;
	//destruction
	~CF2mouseDlg();

};
