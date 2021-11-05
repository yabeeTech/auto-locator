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
//	SKLSE 2007-04-02, jicheng, 将某些处理通过PostThreadMessage放到线程中, begin
#define	WM_SUBMIT_MARKS		WM_USER + 501
#define	WM_NEXT				WM_USER + 502
#define	WM_PREV				WM_USER + 503
//	SKLSE 2007-04-02, jicheng, 将某些处理通过PostThreadMessage放到线程中, ends

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

// 调用接口
public:
	BOOL	StartService ( );	// 启动服务
	BOOL	StopService ( )	;	// 停止服务

	void	ConnectServer ( ) { }
	BOOL	ConnectServer ( const char * strAddr, const u_short sinport );
	void	Logon ( CString strAccount, CString strPassword );
	void	Logon ( )	;
	void	Logout ( )	;
	void	ReLogin ( )	;
	void	RequestMission ( )	;
//	SKLSE 2006-12-10, jicheng, control channel state, begin
	void	Apply_for_normal_process ( );	// 请求终止测试状态, 开始正常服务
	void	Reset ( );	// 重置以便开始正常服务
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
	
	// 状态检查
	void	CheckServerState ( )	;
	void	CheckChannelState ( )	;
	void	AllLogout ( )			;
	void	ChannelLogout ( )		;

	// 参数设置
	void	SetAppPath( TCHAR* pPath );			// 传递应用程序的当前路径给 payloadServer
//	void	SetOutputWnd( COutputWnd* pWnd );
//	void	SetMainFrame( CMainFrame* pWnd );
	void	SetServer ( const char * addr, const u_short nport );	// 设置服务器地址
	void	SetServerPort ( UINT nPort );
	void	SetLogonInfo ( CString strAccount, CString strPassword );
	void	SetLogonInfo ( wchar_t * usr, wchar_t * pwd );
	void	SetBufferPtrList( LPLARGE_BUFFER pListLarge, LPSMALL_BUFFER pListSmall, LPCOMMAND_BUFFER pListCommand );

// 工作参数
protected:
	CString	m_strAccount	;	// 用户帐号
	CString	m_strPassword	;	// 用户密码

	CString	m_strUserPath	;	// 当前客户存放图片的路径
	TCHAR*	m_lpPathApp		;	// 应用程序所在的路径
	
	// 为试卷列表加锁
	CRITICAL_SECTION	m_csPaperList;

	CMgrImagePatches * m_mgrImage;

// 缓冲数据
protected:
	// 内存句柄列表
	CPtrList * m_hHandleOfExlargeBufferList;
	CPtrList*	m_hHandleOfLargeBufferList;
	CPtrList*	m_hHandleOfNormalBufferList;
	CPtrList*	m_hHandleOfSmallBufferList;
	CPtrList*	m_hHandleOfCommandBufferList;

	// 内存缓冲列表
	LPEXLARGE_BUFFER	m_lpExlargeBufferList;
	LPLARGE_BUFFER		m_lpLargeBufferList;
	LPNORMAL_BUFFER		m_lpNormalBufferList;
	LPSMALL_BUFFER		m_lpSmallBufferList;
	LPCOMMAND_BUFFER	m_lpCommandBufferList;

	CRITICAL_SECTION	m_csBuffer;	// 缓冲列表访问锁

	LPEXLARGE_BUFFER	GetExlargeBuffer ( );
	LPLARGE_BUFFER		GetLargeBuffer ( );
	LPNORMAL_BUFFER		GetNormalBuffer ( );
	LPSMALL_BUFFER		GetSmallBuffer ( );
	LPCOMMAND_BUFFER	GetCommandBuffer ( );

	BOOL	InsertNode ( LPEXLARGE_BUFFER pNode );		// 将pNode返回给旁视Exlarge缓冲数据列表供重新调度使用
	BOOL	InsertNode ( LPLARGE_BUFFER pNode );		// 将pNode返回给旁视Large缓冲数据列表供重新调度使用
	BOOL	InsertNode ( LPNORMAL_BUFFER pNode );		// 将pNode返回给旁视Normal缓冲数据列表供重新调度使用
	BOOL	InsertNode ( LPSMALL_BUFFER pNode );		// 将pNode返回给旁视Small缓冲数据列表供重新调度使用
	BOOL	InsertNode ( LPCOMMAND_BUFFER pNode );		// 将pNode返回给旁视Command缓冲数据列表供重新调度使用
	BOOL	InsertNode ( LPDATA_BUFFER pNode );			// 将pNode返回给相应的旁视缓冲数据列表供重新调度使用

	LPPAPER_CUTSHEET	m_lstPaperHead;	// payload列表表头
	LPPAPER_CUTSHEET	m_lstPaperTail;	// payload列表表尾

	LPPAPER_CUTSHEET	m_pPaperCurrent;// 当前 payload

// 工作状态
public:
	int				m_iCurrent	;	// 当前正在工作的 payload 序号
	int				m_iMarking	;	// 当前正在进行的 payload 序号
	int				m_iTotal	;	// 当前列表中 payload 数量
	int				m_iMarkedCnt;	// 总共完成的 payload 数量

	BOOL			m_bLogout	;

	BYTE			m_yHead		;
	ChannelState	m_enumState	;


// 工作标志
protected:
	BOOL	m_bJobServerStarted;

	int		m_iImageID;	// started from 0

// 内部动作
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

	void	HeadRequestPaper (int iUncheckedCnt);				// 组长申请 payload

	// 模板相关动作
//	void	requestFeature ( int templateID );
	void	requestFeature ( int groupID, int templateID, BYTE yOrder );
	void	requestActiveTemplateGroup (  );	// 与FETK不一样的是设备端只需要激活模板

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
	void	RequestMission (int iUncheckedCnt);					// 向服务器(或Operator)请求 payload
	void	RecyclePaper (BYTE yRecycleCnt, int iRemain);		// 回收 payload 给服务器
	void	SubmitAllPaper2Server ( );							// 登出前递交所有 payload
	void	SubmitMarks2Server( int iSubmitCnt );				// 向服务器提交 iSubmitCnt 份 results
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

// 服务提供者
protected:
	CNetServer*		m_pNet;

// whu-jarrywhu-2005-01-18,begin
public:
//	CMainFrame *	m_pMainFrame;
//	COutputWnd *	m_pOutputWnd;

	int		m_iUserID			;
	LPCHANNEL_INFO	m_pChannelInfo	;
	int		m_iOperator				;	// Channel的Operator
	int		m_iStepCount			;

protected:
	BOOL	m_bSubmitPaperLock		;	// payload 递交时锁定链表
	int		m_iCount				;	// 当前链表中已完成 payload 数量，当它达到30时递交前20
	int		m_iRollCount			;	// 用来回滚计数
	int		m_iPriority				;	// 当前未完成 payload 总数

//	int		m_iLastRequestPendingCnt;	// 防止包泛滥
	BOOL	m_bConnected			;	// 网络连接标志

//	int		m_iVersion				;
// 时钟处理参数
	//int     m_nTimeoutPaperRequest	;	// payload 请求超时
 //   int     m_nTimeoutPaperSubmit	;	// payload 递交超时
// 临界处理
protected:
//	CCriticalSectionWrapper	m_csSubmit;

// whu-jarrywhu-2005-01-18,end

protected:
	CthreadNetworkService();           // 动态创建所使用的受保护的构造函数
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


