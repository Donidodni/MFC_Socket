#include "pch.h"
#include "CDataSocket.h"
#include "MFC_day6_1Doc.h"

CDataSocket::CDataSocket(CMFCday61Doc* pDoc) 
:m_pDoc(0)
{
	m_pDoc = pDoc;
}

CDataSocket::~CDataSocket() {

}


void CDataSocket::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
	m_pDoc->ProcessReceive(this, nErrorCode);
}


void CDataSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
	m_pDoc->ProcessClose(this, nErrorCode);
}
