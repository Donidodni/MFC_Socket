#include "pch.h"
#include "CListenSocket.h"
#include "MFC_day6_1Doc.h"

CListenSocket::CListenSocket(CMFCday61Doc* pDoc)
:m_pDoc(0)
{
	m_pDoc = pDoc;
}

CListenSocket::~CListenSocket() {

}

void CListenSocket::OnAccept(int nErrorCode)
{
	CSocket::OnAccept(nErrorCode);
	m_pDoc->ProcessAccept(nErrorCode);
}
