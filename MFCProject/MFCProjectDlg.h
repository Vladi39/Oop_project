
// MFCProjectDlg.h : header file
//

#pragma once
#include "Drawing.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Figure2D.h"
#include"Gaming.h"

enum GameMode
{
	Menu, Draw, Game, Gameover
};

enum Phase
{

	Awaiting,AddCircleShape,AddRectangleShape,OnCircleClickScreen,OnRectangleClickScreen
};

enum Strikes
{
	ZeroStrike, OneStrike, TwoStrike, ThreeStrike
};

// CMFCProjectDlg dialog
class CMFCProjectDlg : public CDialogEx
{
// Construction
public:
	CMFCProjectDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECT_DIALOG };
#endif

	protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
// Implementation
protected:
	HICON m_hIcon;
	HICON Skull;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	void MyInit();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	UINT nTotalTimer;
	UINT nCreateTimer;
	GameMode eState = Menu;
	Phase ePhase = Awaiting;
	CPoint pShapePoint;
	Drawing DrawBoard;
	Gaming GameBoard;
	Strikes Strikes;
	afx_msg void OnGenerateCircleClick();
	afx_msg void OnGameClick();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDrawClick();
	afx_msg void OnMenuClick();
	afx_msg void OnGenerateRectangleClick();
	afx_msg void OnRestartClick();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CButton AddCircle;
	CButton DrawButton;
	CButton GameButton;
	CButton MenuButton;
	CButton AddRectangle;
	CButton RestartButton;
	CButton LoadButton;
	CButton SaveButton;
	afx_msg void OnLoadClick();
	afx_msg void OnSaveClick();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	bool DeleteClickedCircle(Point &point);
	int GetNumInRange(int iStart, int iRange);
	afx_msg void OnEndSession(BOOL bEnding);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

double DistanceBetweenPoints(CPoint p1, CPoint p2);
CPoint FindMiddlePoint(CPoint p1, CPoint p2);
