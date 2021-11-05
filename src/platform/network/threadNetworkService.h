#pragma once

#include <afxwin.h>

#include "NetServer.h"
// CthreadNetworkService

#include "structures.h"
#include "surfplus.h"

#include "../global/templateItem.h"
//#include "client/mgrImagePatches.h"
#include "../global/mgrDataPatches.h"

#define ROLLBACK_COUNT					10
#define MAX_SUBMIT_COUNT				20
#define	MAX_MARKED_COUNT				30
#define ROLLBACK_FINISHING_COUNT		5
#define MAX_SUBMIT_FINISHING_COUNT		18
#define	MAX_MARKED_FINISHING_COUNT		21

// Messages definition
#define	WM_EXIT_THREAD		WM_USER + 500
//	SKLSE 2007-04-02, jicheng, ��ĳЩ����ͨ��PostThreadMessage�ŵ��߳���, begin
#define	WM_SUBMIT_MARKS		WM_USER + 501
#define	WM_NEXT				WM_USER + 502
#define	WM_PREV				WM_USER + 503
//	SKLSE 2007-04-02, jicheng, ��ĳЩ����ͨ��PostThreadMessage�ŵ��߳���, ends

//class CMainFrame;
//class COutputWnd;

class CthreadNetworkService : public CWinThread
{
	DECLARE_DYNCREATE(CthreadNetworkService)

//enum Attribute {
//   normal =    0x00,
//   readOnly =  0x01,
//   hidden =    0x02,
//   system =    0x04,
//   volume =    0x08,
//   directory = 0x10,
//   archive =   0x20
//   };

public:
	templateItem * m_templateListHead;
	templateItem * m_templateListTail;

	templateItem * find ( int templateID, templateItem *templateListHead );
	templateItem * initialize ( int templateID, BYTE number, templateItem * &templateListHead, templateItem * &templateListTail );

	void	onReceiveTemplateFeature ( LPPACK_FEATURE_PATCH pPack );
//	void	onSetActiveTemplateGroupSucceed ( LPPACK_TEMPLATE_GROUP pPack );

// ���ýӿ�
public:
	BOOL	StartService ( );	// ��������
	BOOL	StopService ( )	;	// ֹͣ����

	void	ConnectServer ( ) { }
	BOOL	ConnectServer ( const char * strAddr, const u_short sinport );
	void	Logon ( CString strAccount, CString strPassword );
	void	Logon ( )	;
	void	Logout ( )	;
	void	ReLogin ( )	;
	void	RequestMission ( )	;
//	SKLSE 2006-12-10, jicheng, control channel state, begin
	void	Apply_for_normal_process ( );	// ������ֹ����״̬, ��ʼ��������
	void	Reset ( );	// �����Ա㿪ʼ��������
//	SKLSE 2006-12-10, jicheng, control channel state, ends

	void	Kick_out ( int iUserID );
	void	Kick_out ( int iUserID, int iTypeID );

	void	Paper_recycle ( int iUserID );
	void	Paper_recycle ( int iUserID, int iTypeID );

	void	OnReceiveFromServer( LPPACKAGE lpPackage );
	void	OnConnServerFailed( );

	void	SendPreGradToServer( int iMark, int iCutSheetID );
	void	SendSelectedToServer( int iCutSheetID );
	void	SendCutSheetListToServer( );

	void	sendLarge_Data_2_server ( int iDataType, int iLength, LPJPEG_BUFFER pBuffer );
	
	// ״̬���
	void	CheckServerState ( )	;
	void	CheckChannelState ( )	;
	void	AllLogout ( )			;
	void	ChannelLogout ( )		;

	// ��������
	void	SetAppPath( TCHAR* pPath );			// ����Ӧ�ó���ĵ�ǰ·���� payloadServer
//	void	SetOutputWnd( COutputWnd* pWnd );
//	void	SetMainFrame( CMainFrame* pWnd );
	void	SetServer ( const char * addr, const u_short nport );	// ���÷�������ַ
	void	SetServerPort ( UINT nPort );
	void	SetLogonInfo ( CString strAccount, CString strPassword );
	void	SetLogonInfo ( wchar_t * usr, wchar_t * pwd );
	void	SetBufferPtrList( LPLARGE_BUFFER pListLarge, LPSMALL_BUFFER pListSmall, LPCOMMAND_BUFFER pListCommand );

// ��������
protected:
	CString	m_strAccount	;	// �û��ʺ�
	CString	m_strPassword	;	// �û�����

	CString	m_strUserPath	;	// ��ǰ�ͻ����ͼƬ��·��
	TCHAR*	m_lpPathApp		;	// Ӧ�ó������ڵ�·��
	
	// Ϊ�Ծ��б����
	CRITICAL_SECTION	m_csPaperList;

	CMgrImagePatches * m_mgrImage;

// ��������
protected:
	// �ڴ����б�
	CPtrList * m_hHandleOfExlargeBufferList;
	CPtrList*	m_hHandleOfLargeBufferList;
	CPtrList*	m_hHandleOfNormalBufferList;
	CPtrList*	m_hHandleOfSmallBufferList;
	CPtrList*	m_hHandleOfCommandBufferList;

	// �ڴ滺���б�
	LPEXLARGE_BUFFER	m_lpExlargeBufferList;
	LPLARGE_BUFFER		m_lpLargeBufferList;
	LPNORMAL_BUFFER		m_lpNormalBufferList;
	LPSMALL_BUFFER		m_lpSmallBufferList;
	LPCOMMAND_BUFFER	m_lpCommandBufferList;

	CRITICAL_SECTION	m_csBuffer;	// �����б������

	LPEXLARGE_BUFFER	GetExlargeBuffer ( );
	LPLARGE_BUFFER		GetLargeBuffer ( );
	LPNORMAL_BUFFER		GetNormalBuffer ( );
	LPSMALL_BUFFER		GetSmallBuffer ( );
	LPCOMMAND_BUFFER	GetCommandBuffer ( );

	BOOL	InsertNode ( LPEXLARGE_BUFFER pNode );		// ��pNode���ظ�����Exlarge���������б����µ���ʹ��
	BOOL	InsertNode ( LPLARGE_BUFFER pNode );		// ��pNode���ظ�����Large���������б����µ���ʹ��
	BOOL	InsertNode ( LPNORMAL_BUFFER pNode );		// ��pNode���ظ�����Normal���������б����µ���ʹ��
	BOOL	InsertNode ( LPSMALL_BUFFER pNode );		// ��pNode���ظ�����Small���������б����µ���ʹ��
	BOOL	InsertNode ( LPCOMMAND_BUFFER pNode );		// ��pNode���ظ�����Command���������б����µ���ʹ��
	BOOL	InsertNode ( LPDATA_BUFFER pNode );			// ��pNode���ظ���Ӧ�����ӻ��������б����µ���ʹ��

	LPPAPER_CUTSHEET	m_lstPaperHead;	// payload�б��ͷ
	LPPAPER_CUTSHEET	m_lstPaperTail;	// payload�б��β

	LPPAPER_CUTSHEET	m_pPaperCurrent;// ��ǰ payload

// ����״̬
public:
	int				m_iCurrent	;	// ��ǰ���ڹ����� payload ���
	int				m_iMarking	;	// ��ǰ���ڽ��е� payload ���
	int				m_iTotal	;	// ��ǰ�б��� payload ����
	int				m_iMarkedCnt;	// �ܹ���ɵ� payload ����

	BOOL			m_bLogout	;

	BYTE			m_yHead		;
	ChannelState	m_enumState	;


// ������־
protected:
	BOOL	m_bJobServerStarted;

	int		m_iImageID;	// started from 0

// �ڲ�����
protected:
	void	RecvOnePaper( LPPACK_PAPER_FTP	lpPaperFTP );
	void	RecvCheckPaper( LPPACK_PAPERCHECK_FTP	lpPaperFTP );
	void	OnModifyPwdACK( LPUSER_MESSAGE lpUserMsg )	;
	LPCSTR	GetIpAddress( )	;
	int		GetOperator( )	;
	// protected before,public now 
public:
	void	ReturnDataBuffer ( LPDATA_BUFFER pDataBuffer );
	void	OnNetReloginOK( )							;
	void	OnKickout(int iUserID, int iTypeID)	;
	void	OnKickout ( int iUserID )				;

	void	HeadRequestPaper (int iUncheckedCnt);				// �鳤���� payload

	// ģ����ض���
//	void	requestFeature ( int templateID );
	void	requestFeature ( int groupID, int templateID, BYTE yOrder );
	void	requestActiveTemplateGroup (  );	// ��FETK��һ�������豸��ֻ��Ҫ����ģ��

	void	onReceiveTemplateGroup ( LPPACK_TEMPLATE_GROUP pPack );
	void	onReceiveTemplateInfo ( LPPACK_REGISTER_TEMPLATE pPack );

	//05-2-1,by Xy,End
protected:
	void	OnLoginACK ( LPUSER_MESSAGE lpUserMsg )		;
	void	OnAdminLoginACK ( LPUSER_MESSAGE lpUserMsg );
	void	OnLogoutACK ( LPUSER_MESSAGE lpUserMsg )	;
	void	OnSupressLogout ( LPUSER_MESSAGE lpUserMsg );
	void	OnChannelDone ( LPUSER_MESSAGE lpUserMsg )	;

	void	OnChannelState ( LPPACK_CHANNEL_STATE lpChannelState )	;

	void	OnServerPreGradedMarkEx ( LPPACK_PREGRADED_MARK_EX lpPreGradedMarkEx );

	// Paper service
	void	RequestMission (int iUncheckedCnt);					// �������(��Operator)���� payload
	void	RecyclePaper (BYTE yRecycleCnt, int iRemain);		// ���� payload ��������
	void	SubmitAllPaper2Server ( );							// �ǳ�ǰ�ݽ����� payload
	void	SubmitMarks2Server( int iSubmitCnt );				// ��������ύ iSubmitCnt �� results
//	void	SubmitPaper( LPCLIENT_PAPER_PACKED pPaperPacked );
//	void	PaperSubmitPacked( int M );
//	void	UpdateServerState();
	void	OnServerPaperRecycle( LPUSER_MESSAGE lpUserMsg );
	void	OnServerOnFinishing( );

//	SKLSE 2007-01-17, jicheng, store scripts to server, begin
#ifdef	SWITCH_STORE_SCRIPT
	void	Submit_script_2_server ( LPPAPER_CUTSHEET lpPaper );
	void	Recv_script ( LPPACK_SCRIPT_FTP lpScript_FTP );
#endif
//	SKLSE 2007-01-17, jicheng, store scripts to server, ends

//	SKLSE 2007-04-07, jicheng, Quality management, begin
#ifdef	SWITCH_QUALITY_MANAGEMENT
	void	Recv_quality_segment ( LPPACK_QUALITY_SEGMENT lpQuality_segment );
#endif
//	SKLSE 2007-04-07, jicheng, Quality management, ends

	// whu-jarrywhu-2005-02-02,begin
//	BOOL	FindCutSheetOnDisk(int iCutSheetID);
//	void	OnServerCheckCutSheet(LPUSER_MESSAGE lpUserMsg);
//	void	ClientCheckedResult(LPPACK_CHECKED_RESULT lpCheckedResult);
	// whu-jarrywhu-2005-02-02,end
public:
	//void	UpdateMarkedCnt();
	void	Client_modify_userinfo( CString strOldPwd, CString strPassword, CString strAccount );

	void	GetNextPaper();
	void	GetPrevPaper();
	// Timer Set
	//void	SetTimeoutDetect(int nSpan, BYTE bWho);
	//void	DisableTimeoutDetect(BYTE bWho);
	//void	GetPaperRequestTimeoutSpan();
	// whu-jarrywhu-2005-01-18,end

// �����ṩ��
protected:
	CNetServer*		m_pNet;

// whu-jarrywhu-2005-01-18,begin
public:
//	CMainFrame *	m_pMainFrame;
//	COutputWnd *	m_pOutputWnd;

	int		m_iUserID			;
	LPCHANNEL_INFO	m_pChannelInfo	;
	int		m_iOperator				;	// Channel��Operator
	int		m_iStepCount			;

protected:
	BOOL	m_bSubmitPaperLock		;	// payload �ݽ�ʱ��������
	int		m_iCount				;	// ��ǰ����������� payload �����������ﵽ30ʱ�ݽ�ǰ20
	int		m_iRollCount			;	// �����ع�����
	int		m_iPriority				;	// ��ǰδ��� payload ����

//	int		m_iLastRequestPendingCnt;	// ��ֹ������
	BOOL	m_bConnected			;	// �������ӱ�־

//	int		m_iVersion				;
// ʱ�Ӵ������
	//int     m_nTimeoutPaperRequest	;	// payload ����ʱ
 //   int     m_nTimeoutPaperSubmit	;	// payload �ݽ���ʱ
// �ٽ紦��
protected:
//	CCriticalSectionWrapper	m_csSubmit;

// whu-jarrywhu-2005-01-18,end

protected:
	CthreadNetworkService();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CthreadNetworkService();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

public:
	afx_msg void OnAppExitMessage ( WPARAM wParam, LPARAM lParam );
	afx_msg void OnSetOutputWnd ( WPARAM wParam, LPARAM lParam );
	afx_msg void OnSetMainFrameWnd ( WPARAM wParam, LPARAM lParam );

protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnTimer(UINT nIDEvent);

//	SKLSE 2007-03-30, jicheng, add CthreadNetworkService::Run(), begin
	virtual int Run();
//	SKLSE 2007-03-30, jicheng, add CthreadNetworkService::Run(), ends
};


