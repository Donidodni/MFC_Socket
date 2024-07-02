#pragma once
#include <afxsock.h>

class CMFCday61Doc;

class CListenSocket :
    public CSocket
{
public:
    CListenSocket(CMFCday61Doc* pDoc);
    ~CListenSocket();
    CMFCday61Doc* m_pDoc;

    virtual void OnAccept(int nErrorCode);
};

