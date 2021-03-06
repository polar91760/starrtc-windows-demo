#pragma once
#include "CUserManager.h"
#include "CVoipDataShowView.h"
#include "CChatManager.h"
#include "CVoipManager.h"
#include "CDataControl.h"
#include "CShowLiveDlg.h"
#include "CSqliteDB.h"
#include "CSoundManager.h"
// CVoipDlg 对话框

class CVoipDlg : public CDialogEx, public CLocalDataControl, public IVoipManagerListener, public CPicControlCallback, public IShowLiveCallback, public ISoundCallback
{
	DECLARE_DYNAMIC(CVoipDlg)

public:
	CVoipDlg(CUserManager* pUserManager, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CVoipDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VOIP_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	// voip callback
	/**
	 * 被叫方响应
	 * 被叫方收到主叫方的呼叫
	 * @param fromID
	 */
	virtual void onCalling(string fromID);

	/**
	 * 被叫方响应
	 * 主叫方在被叫方接听之前挂断（通话被取消）
	 * @param fromID
	 */
	virtual void onCancled(string fromID);

	/**
	 * 主叫方响应
	 * 被叫方拒绝接通（通话被拒绝）
	 * @param fromID
	 */
	virtual void onRefused(string fromID);

	/**
	 * 主叫方响应
	 * 被叫方线路忙（对方通话中）
	 * @param fromID
	 */
	virtual void onBusy(string fromID);

	/**
	 * 主叫方响应
	 * 被叫方接通（通话开始）
	 * @param fromID
	 */
	virtual void onConnected(string fromID);

	/**
	 * 对方已经挂断
	 * @param fromID
	 */
	virtual void onHangup(string fromID);

	/**
	 * voip报错
	 * @param errorCode
	 */
	virtual void onError(string errorCode);

	/**
	 * 收到实时数据
	 * @param data
	 */
	virtual void onReceiveRealtimeData(uint8_t* data, int length);
	/**
	 * 收到实时数据
	 */
	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen);
public:
	/**
	 * 停止视频回调
	 */
	virtual void stopLive();

	/**
	 * upid增加
	 */
	virtual void addUpId();
	/**
	 * 插入数据回调
	 */
	virtual void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	/**
	 * 裁剪视频数据
	 */
	virtual int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	/**
	 * 绘制
	 */
	virtual void drawPic(YUV_TYPE type, int w, int h, uint8_t* videoData, int videoDataLen);
	// msg callback
	/**
	 * 接收到消息
	 */
	virtual void onNewMessage(CIMMessage* var1);
	/**
	 * 发送消息成功回调
	 */
	virtual void onSendMessageSuccess(int msgIndex);
	/**
	 * 发送消息失败回调
	 */
	virtual void onSendMessageFailed(int msgIndex);

	// picture control callback
	/**
	 * 退出回调
	 */
	virtual void liveExit(void* pParam);
	/**
	 * 修改显示方式
	 */
	virtual void changeStreamConfig(void* pParam, int upid);
	/**
	 * 关闭当前视频
	 */
	virtual void closeCurrentLive(void* pParam);
	virtual void startFaceFeature(void* pParam);
	virtual void stopFaceFeature(void* pParam);
public:
	virtual void getLocalSoundData(char* pData, int nLength);
	virtual void querySoundData(char** pData, int* nLength);
private:
	CUserManager* m_pUserManager;
public:
	virtual BOOL OnInitDialog();
	void clearHistoryList();
	void getHistoryList();
	void addHistoryList(CHistoryBean* pHistoryBean);
	void resetHistoryList();
	CStatic m_ShowArea;
	//CVoipDataShowView* m_pDataShowView;
	
	CVoipManager* m_pVoipManager;
	CSoundManager* m_pSoundManager;
	CShowLiveDlg m_ShowLiveDlg;
	list<CHistoryBean*> mHistoryDatas;
	bool m_bConnect;
	CSqliteDB* m_pSqliteDB;
	afx_msg void OnPaint();
	int m_nUpId;
	int m_nAimUpId;
	CListCtrl m_VoipList;
	afx_msg void OnBnClickedButtonCreateVoip();
	afx_msg void OnNMClickListVoip(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_UserId;
	CEdit m_editSendMsg;
	CListBox m_HistoryMsg;
	afx_msg void OnBnClickedButtonVoipSendMsg();
	afx_msg void OnBnClickedButtonVoipStartLive();
};
