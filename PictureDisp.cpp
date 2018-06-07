// PictureDisp.cpp: implementation of the CPictureDisp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PictureDisp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPictureDisp::CPictureDisp()
  : m_pStream(0), m_pDisp(0)
{

}

CPictureDisp::~CPictureDisp()
{
	if (m_pDisp != 0) m_pDisp->Release();
	
	if (m_pStream != 0) m_pStream->Release();
}

CPictureDisp::operator IPictureDisp*() const
{
	return m_pDisp;
}

IPictureDisp* CPictureDisp::GetPictureDisp()
{
	return m_pDisp;
}

BOOL CPictureDisp::LoadResource(UINT uResID, LPCSTR lpType)
{
	HINSTANCE hInst = AfxGetInstanceHandle();
	
	HRSRC hRsrc     = ::FindResource(hInst, MAKEINTRESOURCE(uResID), lpType);
	if (hRsrc == 0) return FALSE;

	DWORD dwSize    = ::SizeofResource(hInst, hRsrc);
	
	HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
	if (hGlobal == 0) return FALSE;

	LPVOID lpData   = ::GlobalLock(hGlobal);
	if (lpData == 0) return FALSE;

	LPVOID lpSrc    = ::LockResource(::LoadResource(hInst, hRsrc));
	if (lpSrc == 0) return FALSE;
	
	memcpy(lpData, lpSrc, dwSize);
	
	::GlobalUnlock(hGlobal);
	::CreateStreamOnHGlobal(hGlobal, TRUE, &m_pStream);
	::FreeResource(hGlobal);

	if (m_pStream != 0)
	{
		return ::OleLoadPicture(m_pStream, dwSize, TRUE, IID_IPictureDisp, (void**)&m_pDisp) == S_OK ? TRUE : FALSE;
	}

	return FALSE;
}
