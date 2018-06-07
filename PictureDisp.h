// PictureDisp.h: interface for the CPictureDisp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTUREDISP_H__3A6AEACF_6D66_4AC2_9D75_FD32B3EBE1A3__INCLUDED_)
#define AFX_PICTUREDISP_H__3A6AEACF_6D66_4AC2_9D75_FD32B3EBE1A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPictureDisp  
{
public:
	CPictureDisp();
	virtual ~CPictureDisp();

public:
	BOOL LoadResource(UINT uResID, LPCSTR lpType);
	operator IPictureDisp* () const;
	IPictureDisp* GetPictureDisp();

private:
	IStream* m_pStream;
	IPictureDisp* m_pDisp;
};

#endif // !defined(AFX_PICTUREDISP_H__3A6AEACF_6D66_4AC2_9D75_FD32B3EBE1A3__INCLUDED_)
