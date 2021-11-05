#ifndef _MGR_CHANNEL_H_
#define	_MGR_CHANNEL_H_

#include "Channel.h"

#include <functional>

#include "network/threadNetworkService.h"

#define	MAX_CHANNEL_NUMBER		10

class CMgrChannel
{
public:
	bool	createAllChannels ( short nCnt );

	void	setCaptureChannel ( int templateID, BYTE number, BYTE order );

	CthreadNetworkService *	m_pNetThread;

	//LPCHANNEL	createChannel_0 ( HWND hWnd=NULL );
	//LPCHANNEL	createChannel_1 ( HWND hWnd=NULL );
	//LPCHANNEL	createChannel_2 ( HWND hWnd=NULL );
	//LPCHANNEL	createChannel_3 ( HWND hWnd=NULL );
	//LPCHANNEL	createChannel_4 ( HWND hWnd=NULL );

	// for accessing dataCenter
	void	setIP ( const char * strIP );
	void	setPort ( short nPort );
	void	setUser ( const char * strUserName, const char * strPsw );
	void	setCaptureFolder ( const char * strFolder );
	bool	getJob ( );

	bool	connectServer ( );

	LPCHANNEL	m_ppChannel[10];

	void	onStart ( );
	void	onStop ( );
	void	onCapture ( );
	void	onCancel ( );

	void	loopCapture ( );

	bool	m_bCapture;

	HANDLE	m_hThreadCapture;

	CEdit*	m_pedtMsg;
	CEdit*	m_pedtMsg_1;
	CEdit*	m_pedtMsg_2;

	void	showMsg ( CString strMsg );
	void	showMsg_1 ( CString strMsg );
	void	showMsg_2 ( CString strMsg );

	static CMgrChannel*	getMgr ( ){return m_pThis;}

public:
	CMgrChannel ( );
	~CMgrChannel ( );

	void	setPlayWnd ( int i, HWND hWnd );
	void	setWndRect ( int i, CRect rcWnd );
	void	setPosDisplay ( int i, int iX, int iY );

protected:
	LPFUNC_DATA 	m_ppfData[10];
	LPFUNC_DEC		m_ppfDec[10];

	HWND	m_phWnd [ 10 ];
	CRect	m_rcWnd [ 10 ];
	int		m_iX [ 10 ];
	int		m_iY [ 10 ];

	// for dataCenter
	char	m_cIP[16];
	char	m_cUserName[100];
	char	m_cPassword[100];
//	char	m_filename[100];
	char	m_cFolderCapture [ 256 ];
	short	m_nPort;	// 这个是设备的端口号, 缺省为 8000

	static	CMgrChannel*	m_pThis;

public:
	void	addJPEG_buffer ( LPJPEG_BUFFER pBufferAdd );
	void	addDIB_buffer ( LPDIB_BUFFER pBufferAdd );

	LPJPEG_BUFFER	getJPEG_buffer ( );
	LPDIB_BUFFER	getDIB_buffer ( );

protected:
	LPJPEG_BUFFER	m_headerJPEG_buffer;
	LPJPEG_BUFFER	m_tailerJPEG_buffer;
	LPDIB_BUFFER	m_headerDIB_buffer;
	LPDIB_BUFFER	m_tailerDIB_buffer;

	// 网络内存句柄列表
//	CPtrList * m_hHandleOfExlargeBufferList;
	CPtrList*	m_hHandleOfLargeBufferList;
//	CPtrList*	m_hHandleOfNormalBufferList;
	CPtrList*	m_hHandleOfSmallBufferList;
	CPtrList*	m_hHandleOfCommandBufferList;

	// 网络内存缓冲列表
//	LPEXLARGE_BUFFER	m_lpExlargeBufferList;
	LPLARGE_BUFFER		m_lpLargeBufferList;
//	LPNORMAL_BUFFER		m_lpNormalBufferList;
	LPSMALL_BUFFER		m_lpSmallBufferList;
	LPCOMMAND_BUFFER	m_lpCommandBufferList;

	void	initJPEGBuffers ( );
	void	destroyJPEGBuffers ( );

	void	initNetBuffers ( );
	void	destroyNetBuffers ( );

	CRITICAL_SECTION	m_csBuffer;
};


#endif // !_MGR_CHANNEL_H_
