
// MFCProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCProject.h"
#include "MFCProjectDlg.h"
#include "afxdialogex.h"
#include <string>
#include"Gaming.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DEFAULT_CREATE_DELETE_TIMER 2000


// CMFCProjectDlg dialog



CMFCProjectDlg::CMFCProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Skull = AfxGetApp()->LoadIcon(IDC_SKULL);
}

void CMFCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON3, AddCircle);
	DDX_Control(pDX, IDC_BUTTON1, DrawButton);
	DDX_Control(pDX, IDC_BUTTON2, GameButton);
	DDX_Control(pDX, IDC_BUTTON4, MenuButton);
	DDX_Control(pDX, IDC_BUTTON5, AddRectangle);
	DDX_Control(pDX, IDC_BUTTON6, RestartButton);
	DDX_Control(pDX, IDC_BUTTON7, LoadButton);
	DDX_Control(pDX, IDC_BUTTON8, SaveButton);
}

BEGIN_MESSAGE_MAP(CMFCProjectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCProjectDlg::OnGenerateCircleClick)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCProjectDlg::OnDrawClick)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCProjectDlg::OnGameClick)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCProjectDlg::OnMenuClick)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCProjectDlg::OnGenerateRectangleClick)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCProjectDlg::OnRestartClick)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCProjectDlg::OnLoadClick)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCProjectDlg::OnSaveClick)
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
	ON_WM_ENDSESSION()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CMFCProjectDlg message handlers

BOOL CMFCProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	this->MyInit();
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CMFCProjectDlg::MyInit()
{

	this->nTotalTimer = SetTimer(2, 50, NULL);
	DrawButton.ShowWindow(SW_SHOW);
	GameButton.ShowWindow(SW_SHOW);
	AddCircle.ShowWindow(SW_HIDE);
	AddRectangle.ShowWindow(SW_HIDE);
	MenuButton.ShowWindow(SW_HIDE);
	RestartButton.ShowWindow(SW_HIDE);
	SaveButton.ShowWindow(SW_HIDE);
	LoadButton.ShowWindow(SW_HIDE);

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.




void CMFCProjectDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	if (IsIconic())
	{
		

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		
		
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		if (this->eState==Draw)
		{
			for (int i = 0; i < 10; i++)
			{
				if (DrawBoard.FiguresArray[i]) // polymorphism, each object calls for his OnDraw function
				{
					DrawBoard.FiguresArray[i]->OnDraw(dc);

				}
			}
		}
		else if (this->eState==Game)
		{
			wstring sShowGameScore = L"Score: " + to_wstring(GameBoard.nScore);
			POINT p1 = { rect.Width() - 300 , 5};
			POINT p2 = { rect.Width() , 30};
			dc.DrawText(sShowGameScore.c_str(), CRect(p1, p2), DT_PATH_ELLIPSIS);

			if (this->Strikes >= OneStrike)
			{
				dc.DrawIcon((rect.Width() / 2) - 20, 5, Skull); // skull strike draw
			}
			if (this->Strikes >= TwoStrike)
			{
				dc.DrawIcon(rect.Width() / 2, 5, Skull);

			}
			if (this->Strikes == ThreeStrike)
			{
				dc.DrawIcon((rect.Width() / 2) + 20, 5, Skull);
				wstring sLastTry = L"Last Try!";
				POINT p1 = { rect.Width() - 100  , 5 };
				POINT p2 = { rect.Width(), 30 };
				dc.DrawText(sLastTry.c_str(), CRect(p1, p2), DT_PATH_ELLIPSIS); // Last try msg

			}
			for (int i = 0; i < 10; i++)
			{
				if (GameBoard.CirclesArray[i])
				{

					GameBoard.CirclesArray[i]->bIsShowingTimer = true; // shows timer on game state
					GameBoard.CirclesArray[i]->OnDraw(dc);


				}
			}
		}
		CDialogEx::OnPaint();
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCProjectDlg::OnTimer(UINT_PTR nIDEvent)
{
	POINT pMouse;
	CRect rect;
	GetClientRect(&rect);
	if (GetCursorPos(&pMouse))
	{
		ScreenToClient(&pMouse);
	}
	switch (this->eState)
	{
	case Menu:

		break;
	case Game:
		
		if ((this->nCreateTimer != 0) && (this->nTotalTimer != 0))
		{
			if (nIDEvent == this->nCreateTimer) // game circle create logic
			{

				CRect rect;
				CPoint point1, point2;
				GetClientRect(&rect);
				int HeightMfc = rect.Height();
				HeightMfc = HeightMfc - (HeightMfc / 4);
				int WidthMfc = rect.Width();
				WidthMfc = WidthMfc - (WidthMfc / 2);
				point1.x = GetNumInRange(150, (WidthMfc));
				point1.y = GetNumInRange(50, (HeightMfc));
				point2.x = point1.x + (GetNumInRange(30, 55));
				point2.y = point1.y + (GetNumInRange(30, 55));
				this->pShapePoint = point1;
				double dPointDistance = DistanceBetweenPoints(pShapePoint, point2);
				double dRadius = dPointDistance / 2;
				CPoint pMiddlePoint = FindMiddlePoint(pShapePoint, point2);
				pMiddlePoint.x -= dRadius;
				pMiddlePoint.y -= dRadius;
				Point pEdgeCirclePoint("", (double)pMiddlePoint.x, (double)pMiddlePoint.y);
				Circle NewCircle("", pEdgeCirclePoint, dRadius);
				NewCircle.SetRed(NewCircle.GetColorNumber());
				NewCircle.SetGreen(NewCircle.GetColorNumber());
				NewCircle.SetBlue(NewCircle.GetColorNumber());
				NewCircle.nExpireTime = (DEFAULT_CREATE_DELETE_TIMER / GameBoard.nRampUpNum) / 50; // sets each circle object expire time
				GameBoard.InsertIntoCircleArray(NewCircle, false);
				Invalidate();
				
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					if (GameBoard.CirclesArray[i])
					{
						if (GameBoard.CirclesArray[i]->nExpireTime <= 0)// if player missed circle & the circle 4sec timer is over, count strikes & delete circle.
						{
							GameBoard.RemoveFromCircleArray(i);
							Invalidate();
							if (this->Strikes == ZeroStrike) 
							{
								this->Strikes = OneStrike;
								if (GameBoard.nRampUpNum >= 1.25)
								{
									GameBoard.nRampUpNum -= 0.25;
								}
								
							}
							else if (this->Strikes == OneStrike)
							{
								this->Strikes = TwoStrike;
								if (GameBoard.nRampUpNum >= 1.25)
								{
									GameBoard.nRampUpNum -= 0.5;
								}

							}
							else if (this->Strikes == TwoStrike)
							{
								this->Strikes = ThreeStrike;
							}
							else if (this->Strikes == ThreeStrike)
							{
								string t = "Try Again!";
								string g = "Game Over!";
								this->eState = Gameover;
								KillTimer(this->nCreateTimer);
								GameBoard.ResetGame();
								MessageBoxA(NULL, t.c_str(), g.c_str(), MB_OK);
								this->OnMenuClick();
							}
						}
						else // if circle 4sec timer still hasnt ended, stay on the screen.
						{
							GameBoard.CirclesArray[i]->nExpireTime--;
							Invalidate();
						}
					}
				}
			}
		}
		break;
	case Draw:

		break;
	case Gameover:

		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMFCProjectDlg::OnDrawClick()
{
	this->eState = Draw;
	DrawButton.ShowWindow(SW_HIDE);
	GameButton.ShowWindow(SW_HIDE);
	RestartButton.ShowWindow(SW_HIDE);
	AddCircle.ShowWindow(SW_SHOW);
	AddRectangle.ShowWindow(SW_SHOW);
	MenuButton.ShowWindow(SW_SHOW);
	SaveButton.ShowWindow(SW_SHOW);
	LoadButton.ShowWindow(SW_SHOW);
	
}


void CMFCProjectDlg::OnGameClick()
{
	DrawButton.ShowWindow(SW_HIDE);
	GameButton.ShowWindow(SW_HIDE);
	RestartButton.ShowWindow(SW_SHOW);
	AddCircle.ShowWindow(SW_HIDE);
	AddRectangle.ShowWindow(SW_HIDE);
	MenuButton.ShowWindow(SW_SHOW);
	SaveButton.ShowWindow(SW_HIDE);
	LoadButton.ShowWindow(SW_HIDE);
	this->eState = Game;
	if (this->nCreateTimer)
	{
		KillTimer(this->nCreateTimer);
	}
	this->nCreateTimer = SetTimer(1, DEFAULT_CREATE_DELETE_TIMER / GameBoard.nRampUpNum, NULL);
	GameBoard.ResetGame();
	this->Strikes = ZeroStrike;
	
}

int CMFCProjectDlg::GetNumInRange(int iStart, int iRange)
{
	return rand() % iRange + iStart;
}


void CMFCProjectDlg::OnMenuClick()
{
	this->eState = Menu;
	DrawButton.ShowWindow(SW_SHOW);
	GameButton.ShowWindow(SW_SHOW);
	AddCircle.ShowWindow(SW_HIDE);
	AddRectangle.ShowWindow(SW_HIDE);
	MenuButton.ShowWindow(SW_HIDE);
	RestartButton.ShowWindow(SW_HIDE);
	SaveButton.ShowWindow(SW_HIDE);
	LoadButton.ShowWindow(SW_HIDE);
	AddRectangle.SetWindowTextW(_T("Add Rectangle"));
	AddCircle.SetWindowTextW(_T("Add Circle"));
	for (int i= 0; i < 10; i++)
	{
		if (this->DrawBoard.FiguresArray[i]) 
		{
			delete this->DrawBoard.FiguresArray[i];
			this->DrawBoard.FiguresArray[i] = NULL;

		}
	}
	KillTimer(this->nCreateTimer);
	this->nCreateTimer = 0;
	GameBoard.ResetGame();
	this->Strikes = ZeroStrike;
	Invalidate();

}


void CMFCProjectDlg::OnGenerateRectangleClick()
{
	this->ePhase = AddRectangleShape;
	AddRectangle.SetWindowTextW(_T("Creating Rectangle"));
	AddCircle.SetWindowTextW(_T("Add Circle"));

}


void CMFCProjectDlg::OnGenerateCircleClick()
{
	this->ePhase = AddCircleShape;
	AddCircle.SetWindowTextW(_T("Creating Circle"));
	AddRectangle.SetWindowTextW(_T("Add Rectangle"));

}

void CMFCProjectDlg::OnRestartClick()
{
	this->OnGameClick();
}


double DistanceBetweenPoints(CPoint p1, CPoint p2)
{
	double x = (p1.x - p2.x);
	double y = (p1.y - p2.y);

	return sqrt(x * x + y * y);
}

CPoint FindMiddlePoint(CPoint p1, CPoint p2)
{
	double x = (abs(p1.x - p2.x)) /2;
	double y = (abs(p1.y - p2.y)) /2;
	x += min(p1.x, p2.x);
	y += min(p1.y, p2.y);
	return CPoint(x, y);

}


void CMFCProjectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this->eState == Draw)
	{

		if (this->ePhase == AddCircleShape) // first point selection
		{

			this->ePhase = OnCircleClickScreen;
			this->pShapePoint = point;

		}
		else if (this->ePhase == OnCircleClickScreen) // second point selection
		{

			double dPointDistance = DistanceBetweenPoints(pShapePoint, point);
			double dRadius = dPointDistance / 2;
			CPoint pMiddlePoint = FindMiddlePoint(pShapePoint, point);
			pMiddlePoint.x -= dRadius;
			pMiddlePoint.y -= dRadius;
			Point pEdgeCirclePoint("", (double)pMiddlePoint.x, (double)pMiddlePoint.y);
			Circle NewCircle("", pEdgeCirclePoint, dRadius);
			NewCircle.SetRed(NewCircle.GetColorNumber());
			NewCircle.SetGreen(NewCircle.GetColorNumber());
			NewCircle.SetBlue(NewCircle.GetColorNumber());
			DrawBoard.InsertIntoFigureArray<Circle>(NewCircle);
			this->ePhase = AddCircleShape;
			Invalidate();

		}
		if (this->ePhase == AddRectangleShape) // first point selection
		{

			this->ePhase = OnRectangleClickScreen;
			this->pShapePoint = point;
		}
		else if (this->ePhase == OnRectangleClickScreen) // second points selection
		{

			Point p1("", this->pShapePoint.x, this->pShapePoint.y);
			Point p2("", point.x, point.y);
			MyRectangle NewRec("", p1, p2);
			NewRec.SetRed(NewRec.GetColorNumber());
			NewRec.SetGreen(NewRec.GetColorNumber());
			NewRec.SetBlue(NewRec.GetColorNumber());
			DrawBoard.InsertIntoFigureArray<MyRectangle>(NewRec);
			this->ePhase = AddRectangleShape;
			Invalidate();

		}
	}
	else if (this->eState == Game)
	{
		Point pMousePoint("", (double)point.x, (double)point.y);
		if (this->DeleteClickedCircle(pMousePoint)) // if true -> you point at an object -> delete it
		{
			GameBoard.nRampUpNum += SCORE_PER_SUCCESS;
			GameBoard.nScore += 10;
			Invalidate();
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}




void CMFCProjectDlg::OnLoadClick() //deserialization
{
	CTypedPtrArray<CObArray, Figure2D*>Array;
	CFile File;
	File.Open(_T(".\myfile.arc"), CFile::modeRead);
	CArchive Ar(&File, CArchive::load);
	Array.Serialize(Ar);
	Ar.Close();
	File.Close();
	int FigureIndex = 0;
	for (int i = 0; i < 10; i++)
	{
		this->DrawBoard.FiguresArray[i] = NULL;

	}
	for (int i = 0; i < Array.GetSize(); i++)
	{
		this->DrawBoard.FiguresArray[FigureIndex++] = Array.GetAt(i);
	}
	Invalidate();
}


void CMFCProjectDlg::OnSaveClick() //serialization
{
	CTypedPtrArray<CObArray, Figure2D*>Array;
	for (int i = 0; i < 10; i++)
	{
		if (this->DrawBoard.FiguresArray[i])
		{
			Array.Add(this->DrawBoard.FiguresArray[i]);
		}
	}
	CFile File;
	File.Open(_T(".\myfile.arc"), CFile::modeWrite | CFile::modeCreate);
	CArchive Ar(&File, CArchive::store);
	Array.Serialize(Ar);
	Ar.Close();
	File.Close();
}


BOOL CMFCProjectDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) // changes cursor to " + "
{
	if (this->eState == Draw && (this->ePhase==AddCircleShape || this->ePhase==AddRectangleShape) || (this->ePhase == OnCircleClickScreen || this->ePhase == OnRectangleClickScreen))
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		return TRUE;
	}
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}

bool CMFCProjectDlg::DeleteClickedCircle(Point &point) // checks if mouse cursor X,Y points at the targeted object and deletes it
{
	for (int i = 0; i < 10; i++)
	{
		if (GameBoard.CirclesArray[i] != NULL && GameBoard.CirclesArray[i]->isInside(&point))
		{
			GameBoard.RemoveFromCircleArray(i);
			return true;
		}
	}
	return false;
}


void CMFCProjectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCProjectDlg::OnEndSession(BOOL bEnding)
{

	KillTimer(this->nCreateTimer);
	KillTimer(this->nTotalTimer);
	CDialogEx::OnEndSession(bEnding);

}


void CMFCProjectDlg::OnRButtonDown(UINT nFlags, CPoint point) // changes circle color in draw game - right mouse click
{
	CPaintDC dc(this);
	Point pMyPoint("", (double)point.x, (double)point.y);
	for (int i = 0; i < 10; i++)
	{
		if (DrawBoard.FiguresArray[i] != NULL && DrawBoard.FiguresArray[i]->isInside(&pMyPoint))
		{
			DrawBoard.FiguresArray[i]->SetRed(Figure2D::GetColorNumber());
			DrawBoard.FiguresArray[i]->SetGreen(Figure2D::GetColorNumber());
			DrawBoard.FiguresArray[i]->SetBlue(Figure2D::GetColorNumber());
			Invalidate();
		}
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}



BOOL CMFCProjectDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) // rescale objects using mouse wheel up & down
{
	POINT pMouse;
	if (GetCursorPos(&pMouse))
	{
		ScreenToClient(&pMouse);
		Point pMyPoint("", (double)pMouse.x, (double)pMouse.y);
		for (int i = 0; i < 10; i++)
		{
			if (DrawBoard.FiguresArray[i] != NULL && DrawBoard.FiguresArray[i]->isInside(&pMyPoint))
			{
				if (zDelta > 0)
				{
					DrawBoard.FiguresArray[i]->Scale(1.1, 1.1);
					Invalidate();
				}
				else
				{
					DrawBoard.FiguresArray[i]->Scale(0.9, 0.9);
					Invalidate();
				}
			}
		}
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, point);
}
