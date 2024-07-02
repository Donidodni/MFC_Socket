
// MFC_day6_1View.h: CMFCday61View 클래스의 인터페이스
//

#pragma once


class CMFCday61View : public CEditView
{
protected: // serialization에서만 만들어집니다.
	CMFCday61View() noexcept;
	DECLARE_DYNCREATE(CMFCday61View)

// 특성입니다.
public:
	CMFCday61Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCday61View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void AddMessage(LPCTSTR message);
};

#ifndef _DEBUG  // MFC_day6_1View.cpp의 디버그 버전
inline CMFCday61Doc* CMFCday61View::GetDocument() const
   { return reinterpret_cast<CMFCday61Doc*>(m_pDocument); }
#endif

