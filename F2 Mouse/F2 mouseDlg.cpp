// F2 mouseDlg.cpp : implementation file
//
#include "stdafx.h"
#include "F2 mouse.h"
#include "F2 mouseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
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

// CF2mouseDlg dialog

CF2mouseDlg::CF2mouseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CF2mouseDlg::IDD, pParent)
	, m_alphaflag(FALSE)
	, m_clickflag(FALSE)
	, m_lockkey(FALSE)
	, m_lockno(0)
	, m_xpos(0)
	, m_ypos(0)
	, m_time(0)
	, m_oldpoint(0)
	, m_candiNo(0)
	, m_candipageno(0)
	, m_candipageindex(0)
	, m_tpos(0,0)
	, m_word(_T(""))
	, m_sentence(_T(""))
	, m_lamdaflag(FALSE)
	, m_capsLock(FALSE)
	, m_shift(FALSE)
	, m_candiflag(FALSE)
	, m_candiPageflag(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	
	m_wQ=new wordQuery;
}

CF2mouseDlg::~CF2mouseDlg()
{
	delete m_wQ;
}

void CF2mouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X, m_xpos);
	DDX_Text(pDX, IDC_Y, m_ypos);
	DDX_Control(pDX, IDC_SENTENCE, m_sentEdit);
}

BEGIN_MESSAGE_MAP(CF2mouseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_POSTEST1, &CF2mouseDlg::OnBnClickedPostest1)
	ON_BN_CLICKED(IDC_POSTEST2, &CF2mouseDlg::OnBnClickedPostest2)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CF2mouseDlg message handlers
BOOL CF2mouseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_ALPHAKEYAREA)->GetWindowRect(&m_alphaKeyArea);
	GetDlgItem(IDC_AUXIKEY)->GetWindowRect(&m_auxiKeyArea);
	GetDlgItem(IDC_LAMDAKEY)->GetWindowRect(&m_lamdaKeyArea);
	GetDlgItem(IDC_RESULTAREA)->GetWindowRect(&m_candidateArea);
	ScreenToClient(&m_alphaKeyArea);
	ScreenToClient(&m_auxiKeyArea);
	ScreenToClient(&m_lamdaKeyArea);
	ScreenToClient(&m_candidateArea);
	for(int i=0;i<CANDIKEY_NO;i++)
	{
		m_candiword[i]="";   
	}
	m_wQ->loadIndex();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CF2mouseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CF2mouseDlg::OnPaint()
{
	//draw keys on keyboard
	setKeyInformation();
    drawDisplay(this);
	if (IsIconic())
	{
		//original part draw mouse cursor
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CF2mouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CF2mouseDlg::OnBnClickedPostest1()
{

	MessageBox(_T("Made By Xiang Chen & Han Wang\n\r All right reserved\n\rHave Fun!"));
}

void CF2mouseDlg::OnBnClickedPostest2()
{
	// TODO: Add your control notification handler code here
	m_sentence=_T("");
	m_sentEdit.SetWindowText(m_sentence);
	UpdateData(FALSE);
}

void CF2mouseDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//HWND hDlg=this->GetSafeHwnd();
	StrokePoint spoint;
    CDC *pdc=GetDC();
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	CPen *pOldPen=pdc->SelectObject(&pen);
	COLORREF cf = RGB(0,255,0);
    bool inalpharegion=FALSE;
	
	//alpha key area
	if(point.x>=m_alphaKeyArea.left&&point.x<=m_alphaKeyArea.right
		&&point.y>=m_alphaKeyArea.top&&point.y<=m_alphaKeyArea.bottom)
	   inalpharegion=TRUE;

	if(!inalpharegion&&m_alphaflag)
	{
	   m_alphaflag=FALSE;
       m_xpos=0;
       m_ypos=0;
	   UpdateData(FALSE);
	   InvalidateRect(&m_alphaKeyArea,1);  //region clearance
	 }

	if(m_alphaflag&&inalpharegion)
	{
		  //record point
		  m_candiNo=0;
		  m_qResult.clear();
	      m_xpos=point.x;
	      m_ypos=point.y;
		  m_time++;
		  spoint.x=m_xpos;
		  spoint.y=m_ypos;
		  spoint.time=m_time;
		  stroke.push_back(spoint);
          SetDlgItemText(IDC_word, m_word) ;
	      UpdateData(FALSE);

		  //read keys method 3		  
		  for(int i=0;i<ALPHA_KEY_NO;i++)
		  {
			  if(m_keys[i].inKey(point)&&m_lockkey==FALSE)
			  {
				  pdc->FillSolidRect(m_keys[i].location.x,m_keys[i].location.y, m_keys[i].size,m_keys[i].size,cf);
				  pdc->TextOut(m_keys[i].location.x,m_keys[i].location.y,m_keys[i].letter);
				  if(m_shift||m_capsLock)
				  {
				        m_word=m_word+m_keys[i].sletter;
						m_shift=FALSE;
				  }
				  else
				  {
					    m_word=m_word+m_keys[i].letter;
				  }
				  m_lockkey=TRUE;
				  m_lockno=i;
				  break;
			  }
		  }
		  if(!m_keys[m_lockno].inKey(point)&&m_lockkey==TRUE)
		  {	
				  m_lockkey=FALSE;
				  m_lockno=0;
		  }
        
		  //draw gesture
		  pdc->MoveTo(m_oldpoint);
		  pdc->LineTo(point);
		  m_oldpoint=point;
	}    

	ReleaseDC(pdc);
	DeleteObject(pOldPen);
	CDialogEx::OnMouseMove(nFlags, point);
}

void CF2mouseDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//alpha key area
	if(point.x>=m_alphaKeyArea.left&&point.x<=m_alphaKeyArea.right
		&&point.y>=m_alphaKeyArea.top&&point.y<=m_alphaKeyArea.bottom)
	{
		m_alphaflag=TRUE;
        m_oldpoint=point;
	}

	CDC *pdc=GetDC();
	COLORREF cf = RGB(0,255,0);
	//auxilary key area
	if(point.x>=m_auxiKeyArea.left&&point.x<=m_auxiKeyArea.right
		&&point.y>=m_auxiKeyArea.top&&point.y<=m_auxiKeyArea.bottom)
    for(int i=0;i<AUXI_KEY_NO;i++)
    {
			  if(m_auxikeys[i].inKey(point))
			  {
				  pdc->FillSolidRect(m_auxikeys[i].location.x,m_auxikeys[i].location.y, m_auxikeys[i].size,m_auxikeys[i].size,cf);
				  if(i<AUXI_KEY_NO-1)
				      pdc->TextOut(m_auxikeys[i].location.x,m_auxikeys[i].location.y,m_auxikeys[i].letter);
				  else
					  pdc->TextOut(m_auxikeys[i].location.x,m_auxikeys[i].location.y,CString("ENT"));
				  if(m_shift||m_capsLock)
				  {
					  m_sentence=m_sentence+m_auxikeys[i].sletter;
					  m_shift=FALSE;
				  }
				  else
				  {
					   if(m_sentence.GetLength()>0)
					   {
						   m_sentence=m_sentence.Left(m_sentence.GetLength()-1);	
						   m_sentence=m_sentence+m_auxikeys[i].letter+CString(" ");
					   }		   
					   else
						   m_sentence=m_sentence+m_auxikeys[i].letter+CString(" ");
				  }
				  break;
			  }
	}

	//lamda area
	m_lamdaflag=FALSE;
	if(point.x>=m_lamdaKeyArea.left&&point.x<=m_lamdaKeyArea.right
		&&point.y>=m_lamdaKeyArea.top&&point.y<=m_lamdaKeyArea.bottom)
	{
		//tab
		if(m_lamdakeys[19].inKey(point))
		{
			 m_lamdaflag=TRUE;
			 pdc->FillSolidRect(m_lamdakeys[19].location.x,m_lamdakeys[19].location.y,m_lamdakeys[19].size,m_lamdakeys[19].size,cf);
		     pdc->TextOut(m_lamdakeys[19].location.x,m_lamdakeys[19].location.y,m_lamdakeys[19].letter);
			  m_sentence=m_sentence+CString("	");
	    }
		//backspace
		if(m_lamdakeys[20].inKey(point))
		{
			 m_lamdaflag=TRUE;
			 pdc->FillSolidRect(m_lamdakeys[20].location.x,m_lamdakeys[20].location.y,m_lamdakeys[20].size*2.25,m_lamdakeys[20].size,cf);
		     pdc->TextOut(m_lamdakeys[20].location.x,m_lamdakeys[20].location.y,m_lamdakeys[20].letter);
			 m_sentence=m_sentence.Left(m_sentence.GetLength()-1);
	    }	
		//capsLock
		if(m_lamdakeys[21].inKey(point))
		{
			 m_lamdaflag=TRUE;
			 pdc->FillSolidRect(m_lamdakeys[21].location.x,m_lamdakeys[21].location.y,m_lamdakeys[21].size*2.25,m_lamdakeys[21].size,cf);
		     pdc->TextOut(m_lamdakeys[21].location.x,m_lamdakeys[21].location.y,m_lamdakeys[21].letter);
			 if(m_capsLock)
				 m_capsLock=FALSE;
			 else
				 m_capsLock=TRUE;
		}
		//shift
		if(m_lamdakeys[22].inKey(point))
		{
			 m_lamdaflag=TRUE;
			 pdc->FillSolidRect(m_lamdakeys[22].location.x,m_lamdakeys[22].location.y,m_lamdakeys[22].size*2.25,m_lamdakeys[22].size,cf);
		     pdc->TextOut(m_lamdakeys[22].location.x,m_lamdakeys[22].location.y,m_lamdakeys[22].letter);
		     if(m_shift)
				 m_shift=FALSE;
			 else
				 m_shift=TRUE;
		}
		//space
		if(m_lamdakeys[23].inKey(point))
		{
			 m_lamdaflag=TRUE;
			 pdc->FillSolidRect(m_lamdakeys[23].location.x,m_lamdakeys[23].location.y,m_lamdakeys[23].size*2.25,m_lamdakeys[23].size,cf);
		     pdc->TextOut(m_lamdakeys[23].location.x,m_lamdakeys[23].location.y,m_lamdakeys[23].letter);
		     m_sentence=m_sentence+CString(" ");
	    }	
		//enter
		if(m_lamdakeys[24].inKey(point))
		{
			 m_lamdaflag=TRUE;
			 pdc->FillSolidRect(m_lamdakeys[24].location.x,m_lamdakeys[24].location.y,m_lamdakeys[24].size*2.25,m_lamdakeys[24].size,cf);
		     pdc->TextOut(m_lamdakeys[24].location.x,m_lamdakeys[24].location.y,m_lamdakeys[24].letter);
		     m_sentence=m_sentence+CString("\r\n");
	    }	
		//others
		if(!m_lamdaflag)
		for(int i=0;i<LAMDA_KEY_NO-5;i++)
        {
			if(m_lamdakeys[i].inKey(point))
			{
				   pdc->FillSolidRect(m_lamdakeys[i].location.x,m_lamdakeys[i].location.y,m_lamdakeys[i].size,m_lamdakeys[i].size,cf);
				   //for shift and caps
				   if(i==2||i==3||i==6||i==7||i==8||i==18)
					   pdc->TextOut(m_lamdakeys[i].location.x,m_lamdakeys[i].location.y,m_lamdakeys[i].letter+CString("|")+m_lamdakeys[i].sletter);
			       else
				       pdc->TextOut(m_lamdakeys[i].location.x,m_lamdakeys[i].location.y,m_lamdakeys[i].letter);
				   if(m_shift||m_capsLock)
				   {
					   if(m_sentence.GetLength()>0)
					   {
						   m_sentence=m_sentence.Left(m_sentence.GetLength()-1);	
						   m_sentence=m_sentence+m_lamdakeys[i].sletter;
					   }		   
					   else
						   m_sentence=m_sentence+m_lamdakeys[i].sletter;
					   m_shift=FALSE;
				   }			        
				   else
				   {
					   if(m_sentence.GetLength()>0)
					   {
						   m_sentence=m_sentence.Left(m_sentence.GetLength()-1);	
						   m_sentence=m_sentence+m_lamdakeys[i].letter+CString(" ");
					   }		   
					   else
						   m_sentence=m_sentence+m_lamdakeys[i].letter+CString(" ");
				   }
				   break;
			}
	    }
	}

	//candidate area	
	if(point.x>=m_candidateArea.left&&point.x<=m_candidateArea.right
		&&point.y>=m_candidateArea.top&&point.y<=m_candidateArea.bottom)
	{
		 //shift pages
		if(m_candiPageKey.inKey(point))
		{
			 pdc->FillSolidRect(m_candiPageKey.location.x,m_candiPageKey.location.y,m_candiPageKey.size,m_candiPageKey.size/4,cf);
			 pdc->TextOut(m_candiPageKey.location.x,m_candiPageKey.location.y,CString("Next Page"));
			 m_candiPageflag=TRUE;
		}
		else
		{
			m_candipageno=0;
			m_candipageindex=0;
		    for(int i=0;i<CANDIKEY_NO;i++) 
            {
			    if(m_candikeys[i].inKey(point))
			    {
				    pdc->FillSolidRect(m_candikeys[i].location.x,m_candikeys[i].location.y, m_candikeys[i].size,m_candikeys[i].size/4,cf);
				    pdc->TextOut(m_candikeys[i].location.x,m_candikeys[i].location.y,m_candiword[i]);
				    m_sentence=m_sentence+m_candiword[i];
					m_candiflag=TRUE;
				    break;
			     }
	        }
			CString nstr("0");
			SetDlgItemText(IDC_Candino,nstr);
			UpdateData(FALSE);
		}
	}
    
	//display results
	SetDlgItemText(IDC_word, m_word) ;
	m_sentEdit.SetWindowText(m_sentence);  
	m_sentEdit.SetFocus();
	m_sentEdit.SetSel(m_sentence.GetLength(),m_sentence.GetLength());
	UpdateData(FALSE);
	ReleaseDC(pdc);
	//
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CF2mouseDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC *pdc=GetDC();
	COLORREF cf = RGB(255,0,0);

	//alpha key area result interaction with resultArea
	if(point.x>=m_alphaKeyArea.left&&point.x<=m_alphaKeyArea.right
		&&point.y>=m_alphaKeyArea.top&&point.y<=m_alphaKeyArea.bottom)
	{	
	     //calculating csc logical words
		 if(m_word.GetLength()>0)
     	 {
	          string st_word;
			  CString nstr;
	          char *writeword=new char[m_word.GetLength()+1];
	          for(int i=0;i<m_word.GetLength();i++)
		             writeword[i]=(char)m_word.GetAt(i);
	          writeword[m_word.GetLength()]='\0';
	          st_word=writeword;
	          m_wQ->getQResult(st_word,m_qResult);
			  m_candiNo=m_qResult.size();
			  m_candipageno=m_candiNo/8+1;
			  nstr.Format(_T("%d"),m_candiNo);
			  SetDlgItemText(IDC_Candino,nstr);
			  UpdateData(FALSE);
			  for(int i=0;i<CANDIKEY_NO&&i<m_candiNo;i++)
	          {
				  m_candiword[i]=CString(m_qResult.at(i).word.c_str())+CString(" ");
			  }
			  delete writeword;
	          //delete qResult;
		 }
	     for(int i=0;i<CANDIKEY_NO;i++)
	     {
		    pdc->FillSolidRect(m_candikeys[i].location.x,m_candikeys[i].location.y, m_candikeys[i].size,m_candikeys[i].size/4,cf);
		    pdc->TextOut(m_candikeys[i].location.x,m_candikeys[i].location.y,m_candiword[i]);
	     }
	     m_alphaflag=FALSE;
	     m_xpos=0;
	     m_ypos=0;
	     m_word=(_T(""));
		 InvalidateRect(&m_alphaKeyArea,1);
		 //for the *** damned shift
		 if(!m_shift)
         {
		    pdc->FillSolidRect(m_lamdakeys[22].location.x,m_lamdakeys[22].location.y,m_lamdakeys[22].size*2.25,m_lamdakeys[22].size,RGB(255,255,0));
			pdc->TextOut(m_lamdakeys[22].location.x+5,m_lamdakeys[22].location.y+5,m_lamdakeys[22].letter);
			pdc->Draw3dRect(m_lamdakeys[22].location.x,m_lamdakeys[22].location.y,m_lamdakeys[22].size*2.25,m_lamdakeys[22].size,RGB(0,0,0),RGB(0,0,0));
	     }
	}
	
	//auxillary key area display reset
	if(point.x>=m_auxiKeyArea.left&&point.x<=m_auxiKeyArea.right
		&&point.y>=m_auxiKeyArea.top&&point.y<=m_auxiKeyArea.bottom)
	    InvalidateRect(&m_auxiKeyArea,1);
	//InvalidateRect(&m_candidateArea,1);   //Invalidate不调用它们，可能发送WM_PAINT消息，如果你的OnPaint响应WM_PAINT消息的话，会被调用。

	//lamda key area information reset
	if(point.x>=m_lamdaKeyArea.left&&point.x<=m_lamdaKeyArea.right
		&&point.y>=m_lamdaKeyArea.top&&point.y<=m_lamdaKeyArea.bottom)
	{
		//dc.SetBkColor(RGB(0,255,0));
		InvalidateRect(&m_lamdaKeyArea,1);
	}

	//candidate key area information reset
	if(point.x>=m_candidateArea.left&&point.x<=m_candidateArea.right
		&&point.y>=m_candidateArea.top&&point.y<=m_candidateArea.bottom)
	{
		if(m_candiflag)
		{
			 for(int i=0;i<CANDIKEY_NO;i++)
	         {
		        m_candiword[i]="";
	         }
		     m_candiflag=FALSE;
		     InvalidateRect(&m_candidateArea,1);
		}
		if(m_candiPageflag)
		{
			 //m_candiNo
			 if(m_candipageindex<m_candipageno)
			    m_candipageindex++;
			 for(int i=0;i<CANDIKEY_NO;i++)
	         {
				 if(i+m_candipageindex*CANDIKEY_NO<m_qResult.size())
					 m_candiword[i]=CString(m_qResult.at(i+m_candipageindex*CANDIKEY_NO).word.c_str())+CString(" ");
				 else
		             m_candiword[i]=CString("");
	         }
			 m_candiPageflag=FALSE;
			 InvalidateRect(&m_candidateArea,1);
		}
	}
	ReleaseDC(pdc);
	CDialogEx::OnLButtonUp(nFlags, point);

	//core function about algorithms	
	char const filename[]="candiwords.txt";
    ofstream o_file;
    o_file.open(filename);
	o_file<<"candidate word list:"<<endl;
	o_file<<"word"<<"	"<<"frequency"<<endl;
    for(int i=0;i<m_candiNo;i++)
    {
		o_file<<m_qResult.at(i).word<<"     "<<m_qResult.at(i).freq<<endl;
    }
    o_file.close();

	//core function about algorithms
	/*
	char const filename[]="letter and stroke data.txt";
    ofstream o_file;
    o_file.open(filename);
	o_file<<"letter is:";
	o_file<<writeword<<endl;
    o_file<<"x pos"<<"      "<<"y pos"<<"     "<<"time"<<"     "<<endl;
    for(int i=0;i<m_time;i++)
    {
	   o_file<<stroke.at(i).x<<"     "<<stroke.at(i).y<<"     "<<stroke.at(i).time<<"     "<<endl;
    }
    o_file.close();*/
}

void CF2mouseDlg::setKeyInformation()
{
	//set key information 
	//key area alpha build alpha alphebet
	char *alphebet="bdkgcanimqflesyxjhtopvrwuz";
	char *salphebet="BDKGCANIMQFLESYXJHTOPVRWUZ";
	for(int i=0;i<ALPHA_KEY_NO;i++)
	{
		m_alphaalphebet[i].Format(_T("%c"),alphebet[i]);        //more to fix here CString str.Format(_T("%d"),number);
	    m_salphaalphebet[i].Format(_T("%c"),salphebet[i]);
	}	
	int index=0;
	for(int i=0;i<4;i++)
	{
			m_keys[i].letter=m_alphaalphebet[i];
			m_keys[i].sletter=m_salphaalphebet[i];
		    m_keys[i].size=KEY_SIZE;
		    m_keys[i].location.x=m_alphaKeyArea.left+20+(i+1)*KEY_DISTANCE;
			m_keys[i].location.y=m_alphaKeyArea.top+20;
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<6;j++)
		{
			index=i*6+j+4;
			m_keys[index].letter=m_alphaalphebet[index];
			m_keys[index].sletter=m_salphaalphebet[index];
		    m_keys[index].size=KEY_SIZE;
		    m_keys[index].location.x=m_alphaKeyArea.left+20+j*KEY_DISTANCE;
			m_keys[index].location.y=m_alphaKeyArea.top+20+(i+1)*KEY_DISTANCE;
		}
	}
	for(int i=22;i<26;i++)
	{
			m_keys[i].letter=m_alphaalphebet[i];
			m_keys[i].sletter=m_salphaalphebet[i];
		    m_keys[i].size=KEY_SIZE;
		    m_keys[i].location.x=m_alphaKeyArea.left+20+(i-21)*KEY_DISTANCE;
			m_keys[i].location.y=m_alphaKeyArea.top+20+4*KEY_DISTANCE;
	}

	//key area auxilary
	//key area auxi build auxi alphebet
	char *auxialphebet="1234567890+-*/=,.!?";
	for(int i=0;i<AUXI_KEY_NO-1;i++)
	{
		m_auxialphebet[i].Format(_T("%c"),auxialphebet[i]);        //more to fix here CString str.Format(_T("%d"),number);
	}
	m_auxialphebet[19]="\r\n";
	index=0;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<5;j++)
		{
			index=i*5+j;
			m_auxikeys[index].letter=m_auxialphebet[index];
		    m_auxikeys[index].size=KEY_SIZE;
		    m_auxikeys[index].location.x=m_auxiKeyArea.left+20+i*KEY_DISTANCE;
			m_auxikeys[index].location.y=m_auxiKeyArea.top+20+j*KEY_DISTANCE;
		}
	}

    //key area lamda
	//key area lamda build lamda alphebet
	index=0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			index=i*5+j;
		    m_lamdakeys[index].size=KEY_SIZE;
		    m_lamdakeys[index].location.x=m_lamdaKeyArea.left+20+i*KEY_DISTANCE;
			m_lamdakeys[index].location.y=m_lamdaKeyArea.top+20+j*KEY_DISTANCE;
		}
	}
	//sector 1
	m_lamdakeys[0].letter=";";
	m_lamdakeys[0].sletter=";";
	m_lamdakeys[1].letter=":";
	m_lamdakeys[1].sletter=":";
	//vaterieg
	m_lamdakeys[2].letter="{";
	m_lamdakeys[2].sletter="[";
	//vaterieg
	m_lamdakeys[3].letter="(";
	m_lamdakeys[3].sletter="<";
	m_lamdakeys[4].letter="@";
	m_lamdakeys[4].sletter="@";
	m_lamdakeys[5].letter="`";
	m_lamdakeys[5].sletter="`";
	//vaterieg
	m_lamdakeys[6].letter="'";
	m_lamdakeys[6].sletter="\""; //dont forget \
	//vaterieg
	m_lamdakeys[7].letter="}";
	m_lamdakeys[7].sletter="]";
	//vaterieg
	m_lamdakeys[8].letter=")";
	m_lamdakeys[8].sletter=">";
	m_lamdakeys[9].letter=".com";
	m_lamdakeys[9].sletter=".COM";
	//vaterieg
	m_lamdakeys[18].letter="\\";
	m_lamdakeys[18].sletter="/";

	//sector 2
	char *lalphabet2="&|%#_$*^";
	for(int i=10;i<18;i++)
	{
		m_lamdakeys[i].letter=lalphabet2[i-10];
		m_lamdakeys[i].sletter=lalphabet2[i-10];
	}

	//sector 3
	m_lamdakeys[19].letter="TAB";
	m_lamdakeys[20].letter="BACKSPACE";
    m_lamdakeys[21].letter="CAPSLOCK";
	m_lamdakeys[22].letter="SHIFT";
	m_lamdakeys[23].letter="SPACE";
	m_lamdakeys[24].letter="ENTER";
	
	//candikey area 
	//candikey intialization
	for(int i=0;i<CANDIKEY_NO;i++)
	{  
		m_candikeys[i].size=CANDIKEY_SIZE;
		m_candikeys[i].location.x=m_candidateArea.left+20+i*CANDIKEY_DISTANCE;
		m_candikeys[i].location.y=m_candidateArea.top+20;
	}
	m_candiPageKey.size=CANDIKEY_SIZE;
	m_candiPageKey.location.x=m_candidateArea.left+20+CANDIKEY_NO*CANDIKEY_DISTANCE;
	m_candiPageKey.location.y=m_candidateArea.top+20;
}

void CF2mouseDlg::drawDisplay(CF2mouseDlg * background)
{
	//draw alphabetical keysCRect rect;
	CPaintDC dc(background); 
	HBRUSH hB,hC,hD,hD2,hE,hF;
	CBrush hc(RGB(0,255,100));
	hB=CreateSolidBrush(RGB(100,255,0));
	hC=CreateSolidBrush(RGB(100,0,128));
	hD=CreateSolidBrush(RGB(255,255,0));
	hD2=CreateSolidBrush(RGB(0,255,0));
    hE=CreateSolidBrush(RGB(255,0,0));
	hF=CreateSolidBrush(RGB(0,127,255));

	//draw framework
	dc.FrameRect(&m_alphaKeyArea,&hc);
	dc.FrameRect(&m_auxiKeyArea,&hc);
	dc.FrameRect(&m_lamdaKeyArea,&hc);
	dc.FrameRect(&m_candidateArea,&hc);
	
	//alpha area
	SelectObject(dc,hB);
	dc.SetBkColor(RGB(100,255,0));
	for(int i=0;i<ALPHA_KEY_NO;i++)
	{
	   Rectangle(dc,m_keys[i].location.x,m_keys[i].location.y,m_keys[i].location.x+m_keys[i].size,m_keys[i].location.y+m_keys[i].size);
	   dc.TextOut(m_keys[i].location.x+5,m_keys[i].location.y+5,m_keys[i].letter);
	}

	//auxillary area
	SelectObject(dc,hC);
	dc.SetBkColor(RGB(100,0,128));
	for(int i=0;i<AUXI_KEY_NO-1;i++)
	{
	   Rectangle(dc,m_auxikeys[i].location.x,m_auxikeys[i].location.y,m_auxikeys[i].location.x+m_auxikeys[i].size,m_auxikeys[i].location.y+m_auxikeys[i].size);
	   dc.TextOut(m_auxikeys[i].location.x+5,m_auxikeys[i].location.y+5,m_auxikeys[i].letter);
	}
    Rectangle(dc,m_auxikeys[19].location.x,m_auxikeys[19].location.y,m_auxikeys[19].location.x+m_auxikeys[19].size,m_auxikeys[19].location.y+m_auxikeys[19].size);
	dc.TextOut(m_auxikeys[19].location.x+5,m_auxikeys[19].location.y+5,CString("ENT"));
    
	//lamda area
	SelectObject(dc,hD);
	dc.SetBkColor(RGB(255,255,0));
	for(int i=0;i<LAMDA_KEY_NO;i++)
	{
	   if(i<20)
	      Rectangle(dc,m_lamdakeys[i].location.x,m_lamdakeys[i].location.y,m_lamdakeys[i].location.x+m_lamdakeys[i].size,m_lamdakeys[i].location.y+m_lamdakeys[i].size);
	   else
	   {
		   Rectangle(dc,m_lamdakeys[i].location.x,m_lamdakeys[i].location.y,m_lamdakeys[i].location.x+m_lamdakeys[i].size*2.25,m_lamdakeys[i].location.y+m_lamdakeys[i].size);		   
	   }		  
	   dc.TextOut(m_lamdakeys[i].location.x+5,m_lamdakeys[i].location.y+5,m_lamdakeys[i].letter);
	}

	//for shift and caps
	dc.TextOut(m_lamdakeys[2].location.x+5,m_lamdakeys[2].location.y+5,m_lamdakeys[2].letter+CString("|")+m_lamdakeys[2].sletter);
	dc.TextOut(m_lamdakeys[3].location.x+5,m_lamdakeys[3].location.y+5,m_lamdakeys[3].letter+CString("|")+m_lamdakeys[3].sletter);
	dc.TextOut(m_lamdakeys[6].location.x+5,m_lamdakeys[6].location.y+5,m_lamdakeys[6].letter+CString("|")+m_lamdakeys[6].sletter);
	dc.TextOut(m_lamdakeys[7].location.x+5,m_lamdakeys[7].location.y+5,m_lamdakeys[7].letter+CString("|")+m_lamdakeys[7].sletter);
	dc.TextOut(m_lamdakeys[8].location.x+5,m_lamdakeys[8].location.y+5,m_lamdakeys[8].letter+CString("|")+m_lamdakeys[8].sletter);
	dc.TextOut(m_lamdakeys[18].location.x+5,m_lamdakeys[18].location.y+5,m_lamdakeys[18].letter+CString("|")+m_lamdakeys[18].sletter);
	if(m_capsLock)
    {
		  SelectObject(dc,hD2);
		  dc.SetBkColor(RGB(0,255,0));
	      Rectangle(dc,m_lamdakeys[21].location.x,m_lamdakeys[21].location.y,m_lamdakeys[21].location.x+m_lamdakeys[21].size*2.25,m_lamdakeys[21].location.y+m_lamdakeys[21].size);
		  dc.TextOut(m_lamdakeys[21].location.x+5,m_lamdakeys[21].location.y+5,m_lamdakeys[21].letter);
	}
    if(m_shift)
    {
		  SelectObject(dc,hD2);
		  dc.SetBkColor(RGB(0,255,0));
		  Rectangle(dc,m_lamdakeys[22].location.x,m_lamdakeys[22].location.y,m_lamdakeys[22].location.x+m_lamdakeys[22].size*2.25,m_lamdakeys[22].location.y+m_lamdakeys[22].size);
		  dc.TextOut(m_lamdakeys[22].location.x+5,m_lamdakeys[22].location.y+5,m_lamdakeys[22].letter);
	}
    if(!m_shift)
    {
		  SelectObject(dc,hD);
		  dc.SetBkColor(RGB(255,255,0));
		  Rectangle(dc,m_lamdakeys[22].location.x,m_lamdakeys[22].location.y,m_lamdakeys[22].location.x+m_lamdakeys[22].size*2.25,m_lamdakeys[22].location.y+m_lamdakeys[22].size);
		  dc.TextOut(m_lamdakeys[22].location.x+5,m_lamdakeys[22].location.y+5,m_lamdakeys[22].letter);
	}

	//candidate area
	SelectObject(dc,hE);
	dc.SetBkColor(RGB(255,0,0));
	for(int i=0;i<CANDIKEY_NO;i++)
	{
	    Rectangle(dc,m_candikeys[i].location.x,m_candikeys[i].location.y,m_candikeys[i].location.x+m_candikeys[i].size,m_candikeys[i].location.y+m_candikeys[i].size/4);
	    dc.TextOut(m_candikeys[i].location.x,m_candikeys[i].location.y,m_candiword[i]);
	}
	//page shift
	SelectObject(dc,hF);
	dc.SetBkColor(RGB(0,127,255));
    Rectangle(dc,m_candiPageKey.location.x,m_candiPageKey.location.y,m_candiPageKey.location.x+m_candiPageKey.size,m_candiPageKey.location.y+m_candiPageKey.size/4);
	dc.TextOut(m_candiPageKey.location.x,m_candiPageKey.location.y,CString("Next Page"));
	
	//release
	DeleteObject(hB);
	DeleteObject(hC);
    DeleteObject(hD);
	DeleteObject(hE);
	DeleteObject(hF);
}

bool Key::inKey(CPoint mp)
{
	if(mp.x>=location.x&&mp.x<=location.x+size&&mp.y>=location.y&&mp.y<=location.y+size)
		return TRUE;
	else
	    return FALSE;
}
//second part word query
