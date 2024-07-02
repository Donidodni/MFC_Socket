
// MFC_day6_1Doc.cpp: CMFCday61Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_day6_1.h"
#endif

#include "MFC_day6_1Doc.h"
#include "CListenSocket.h"
#include "CDataSocket.h"
#include "MFC_day6_1View.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCday61Doc

IMPLEMENT_DYNCREATE(CMFCday61Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCday61Doc, CDocument)
END_MESSAGE_MAP()


// CMFCday61Doc 생성/소멸

CMFCday61Doc::CMFCday61Doc() noexcept
{
	 m_pListenSocket = NULL;
	 m_pDataSocket = NULL;
}

CMFCday61Doc::~CMFCday61Doc()
{
	if (m_pListenSocket != NULL)
		delete m_pListenSocket;
	if (m_pDataSocket != NULL)
		delete m_pDataSocket;
}

BOOL CMFCday61Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if (!m_viewList.IsEmpty())
	{
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(nullptr);
	}

	ASSERT(m_pListenSocket == NULL);
	
	m_pListenSocket = new CListenSocket(this);
	if (m_pListenSocket->Create(8000) ){
		if (m_pListenSocket->Listen()) {
			AfxMessageBox(_T("서버 시작"), MB_ICONINFORMATION);
			return true;
		} 
	}
	AfxMessageBox(_T("실행중 서버 있음 \n 종료함"), MB_ICONERROR);

	return FALSE;
}




// CMFCday61Doc serialization

void CMFCday61Doc::Serialize(CArchive& ar)
{
	// CEditView에는 모든 serialization을 처리하는 edit 컨트롤이 들어 있습니다.
	if (!m_viewList.IsEmpty())
	{
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
	}
#ifdef SHARED_HANDLERS

	if (m_viewList.IsEmpty() && ar.IsLoading())
	{
		CFile* pFile = ar.GetFile();
		pFile->Seek(0, FILE_BEGIN);
		ULONGLONG nFileSizeBytes = pFile->GetLength();
		ULONGLONG nFileSizeChars = nFileSizeBytes/sizeof(TCHAR);
		LPTSTR lpszText = (LPTSTR)malloc(((size_t)nFileSizeChars + 1) * sizeof(TCHAR));
		if (lpszText != nullptr)
		{
			ar.Read(lpszText, (UINT)nFileSizeBytes);
			lpszText[nFileSizeChars] = '\0';
			m_strThumbnailContent = lpszText;
			m_strSearchContent = lpszText;
		}
	}
#endif
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCday61Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(m_strThumbnailContent, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCday61Doc::InitializeSearchContent()
{
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 전체 텍스트 파일 콘텐츠를 검색 콘텐츠로 사용합니다.
	SetSearchContent(m_strSearchContent);
}

void CMFCday61Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCday61Doc 진단

#ifdef _DEBUG
void CMFCday61Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCday61Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCday61Doc 명령


void CMFCday61Doc::DeleteContents()
{
	if (m_pListenSocket != NULL) {
		delete m_pListenSocket;
		m_pListenSocket = NULL;
	}

	if (m_pDataSocket != NULL) {
		delete m_pDataSocket;
		m_pDataSocket = NULL;
	}

	CDocument::DeleteContents();
}




void CMFCday61Doc::PrintMessage(LPCTSTR message)
{
	CFrameWnd* pMainFrm = (CFrameWnd*)AfxGetMainWnd();
	CMFCday61View* pView = (CMFCday61View*)pMainFrm->GetActiveView();
	pView->AddMessage(message);
}

void CMFCday61Doc::ProcessAccept(int nErrorCode)
{
	CString PeerAddr;
	UINT PeerPort;
	CString str;

	ASSERT(nErrorCode == 0);

	if (m_pDataSocket == NULL) {
		m_pDataSocket = new CDataSocket(this);
		if (m_pListenSocket->Accept(*m_pDataSocket)) {
			m_pDataSocket->GetPeerName(PeerAddr, PeerPort);
			str.Format(_T("IP 주소: %s , 포트 번호 : %d \r\n"), PeerAddr, PeerPort);
			PrintMessage(str);
		}
		else {
			delete m_pDataSocket;
			m_pDataSocket = NULL;
		}
	}
}

void CMFCday61Doc::ProcessReceive(CDataSocket* pSocket, int nErrorCode)
{
	TCHAR buf[256 + 1];
	int nbytes = pSocket->Receive(buf, 256);
	buf[nbytes] = _T('\0');
	PrintMessage(buf);
}

void CMFCday61Doc::ProcessClose(CDataSocket* pSocket, int nErrorCode)
{
	pSocket->Close();
	delete m_pDataSocket;
	m_pDataSocket = NULL;
	PrintMessage(_T("빠이"));
}
