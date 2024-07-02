
// MFC_day6_1View.cpp: CMFCday61View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_day6_1.h"
#endif

#include "MFC_day6_1Doc.h"
#include "MFC_day6_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCday61View

IMPLEMENT_DYNCREATE(CMFCday61View, CEditView)

BEGIN_MESSAGE_MAP(CMFCday61View, CEditView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCday61View 생성/소멸

CMFCday61View::CMFCday61View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCday61View::~CMFCday61View()
{
}

BOOL CMFCday61View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 자동 래핑을 사용합니다.

	return bPreCreated;
}


// CMFCday61View 인쇄

BOOL CMFCday61View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 CEditView 준비
	return CEditView::OnPreparePrinting(pInfo);
}

void CMFCday61View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 시작 인쇄
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMFCday61View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 종료 인쇄
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CMFCday61View 진단

#ifdef _DEBUG
void CMFCday61View::AssertValid() const
{
	CEditView::AssertValid();
}

void CMFCday61View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMFCday61Doc* CMFCday61View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCday61Doc)));
	return (CMFCday61Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCday61View 메시지 처리기


void CMFCday61View::AddMessage(LPCTSTR message)
{
	int len = GetWindowTextLength();
	GetEditCtrl().SetSel(len, len);
	GetEditCtrl().ReplaceSel(message);
}
