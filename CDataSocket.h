#pragma once
#include <afxsock.h>

class CMFCday61Doc;


class CDataSocket :
    public CSocket
{
public:
    CDataSocket(CMFCday61Doc* pDoc);
    ~CDataSocket();
    CMFCday61Doc* m_pDoc;

    virtual void OnReceive(int nErrorCode);
    virtual void OnClose(int nErrorCode);
};

