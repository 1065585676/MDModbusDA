#ifndef __SYMLINK_API_H_INCLUDED__
#define __SYMLINK_API_H_INCLUDED__

#ifdef __cplusplus

/*!
 @file SymLinkApi.h
 @brief SymLinkApi提供查看SymLink设备中点信息的方法.
 @version 1.0
 @author Paul.Wen
 @date 2013年3月19日
 @details Copyright (c) 2008 ~ 2013,北京旋思科技有限公司.
 @note SymLinkApi以Windows的动态库DLL方式提供,编程语言采用标准C++实现,采用纯虚接口类的方式提供,接口采用VS2005编写,使用前确保安装了微软的组件发行包vcredist_x86.exe.
*/

//通讯状态
/*!状态正常*/
#define SYMAPI_STATUS_OK			0
/*!初始状态*/
#define SYMAPI_STATUS_NOCONNECT		1
/*!连接断开*/
#define SYMAPI_STATUS_DISCONNECT	2
/*!连接中*/
#define SYMAPI_STATUS_CONNECTING	3
/*!连接成功*/
#define SYMAPI_STATUS_CONNECTED		4
/*!发送登录命令*/
#define SYMAPI_STATUS_LOGIN			5
/*!登录正常*/
#define SYMAPI_STATUS_LOGIN_OK		6
/*!登录失败(LastErr获取原因)*/
#define SYMAPI_STATUS_LOGIN_FAIL	7
/*!读取数据库点*/
#define SYMAPI_STATUS_REQCONFIG		8
/*!读取数据库点正常*/
#define SYMAPI_STATUS_REQCONFIG_OK	9
/*!读取数据库点失败*/
#define SYMAPI_STATUS_REQCONFIG_FAIL 10
/*!总召唤*/
#define SYMAPI_STATUS_REQALL		11
//总召唤正常
#define SYMAPI_STATUS_REQALL_OK		12
/*!总召唤失败*/
#define SYMAPI_STATUS_REQALL_FAIL	13
/*!数据库版本发生变化*/
#define SYMAPI_STATUS_VER			14
/*!有断线缓存数据*/
#define SYMAPI_STATUS_TX			15

//错误码
/*!正常*/
#define SYMAPI_ERR_OK				0
/*!命令超时*/
#define SYMAPI_ERR_TIMEOUT			-1
/*!解压缩失败*/
#define SYMAPI_ERR_UNCOMPRESS		-2
/*!数据版本改变*/
#define SYMAPI_ERR_VER				-3
/*!未连接*/
#define SYMAPI_ERR_CONNECT			-4
/*!未完成初始化*/
#define SYMAPI_ERR_INIT				-5
/*!数据未找到*/
#define SYMAPI_ERR_FIND				-6
/*!参数错误*/
#define SYMAPI_ERR_PARAM			-7
/*!调用队列溢出*/
#define SYMAPI_ERR_CMDBUF			-8
/*!调用超时*/
#define SYMAPI_ERR_CMDTIME			-9
/*!调用返回错误*/
#define SYMAPI_ERR_CMDERR			-10
/*!功能被禁止*/
#define SYMAPI_ERR_DISABLE			-11

//登陆错误码

/*!用户登录失败*/
#define SYMAPI_ERR_LOGIN_FAIL		-1000
/*!用户不存在*/
#define SYMAPI_ERR_LOGIN_USER		-1001
/*!密码错误*/
#define SYMAPI_ERR_LOGIN_PASS		-1002
/*!用户禁止*/
#define SYMAPI_ERR_LOGIN_INV		-1003
/*!限制登录*/
#define SYMAPI_ERR_LOGIN_DIS		-1004
/*!重复登录*/
#define SYMAPI_ERR_LOGIN_RE			-1009
/*!操作需要用户先登录*/
#define SYMAPI_ERR_LOGIN_NULL		-1090
/*!版本不一致,需要更新API*/
#define SYMAPI_ERR_LOGIN_VER		-1100


// 历史查询错误码

/*!TagID太大,比系统初始化时最大的TagID还大*/
#define QUERY_TASKID_ERROR			-10070
/*!查询类型错误*/
#define QUERY_TYPE_ERROR			-10071
/*!查询时间错误*/
#define QUERY_TIME_ERROR			-10072
/*!TagID不存在*/
#define TAGID_NOT_EXIST				-10073
/*!TagID已存在*/
#define TAGID_ALREADY_EXIST			-10074
/*Tag数量太大*/
#define TAG_COUNT_BIGGER			-10075
/*!TagID太大*/
#define TAGID_BIGGER				-10076
/*!被查询点没有数据*/
#define QUERY_DATA_EMPTY			-10077
/*!被查询点没有找到*/
#define QUERY_TAGID_NOTFOUND		-10078

/*!获取所有信息包括点和组*/
#define SYMAPI_INFO_TYPE_ALL		0
/*!获取所有组信息*/
#define SYMAPI_INFO_TYPE_GROUP		1
/*!获取自身的点和组*/
#define SYMAPI_INFO_TYPE_SELF		2

//点类型
/*!无*/
#define SYMAPI_DBTAGTYPE_NONE		0
/*!整形*/
#define SYMAPI_DBTAGTYPE_INT		1
/*!浮点*/
#define SYMAPI_DBTAGTYPE_DOUBLE		2
/*!字符串*/
#define SYMAPI_DBTAGTYPE_STR		3
/*!块*/
#define SYMAPI_DBTAGTYPE_BLOCK		4
/*!事件点*/
#define SYMAPI_DBTAGTYPE_EVENT		5
/*!通用设备事件*/
#define SYMAPI_DBTAGTYPE_SLEVENT	6

#include <math.h>
#define DOUBLE_DATAMIN				0.00000001

//内存管理

/*!
 @brief 开辟内存
 @param Len 开辟内存长度
 @return 开辟的内存指针
 @note 为了保证SymLinkApi和外部调用者之间的内存管理方式一致,调用接口设置缓存交互时,需要调用该函数开辟内存.
*/
char* SymLinkApiMallocMem(size_t Len);
/*!
 @brief 释放内存
 @param pBuf 内存指针
 @note 为了保证SymLinkApi和外部调用者之间的内存管理方式一致,调用接口设置缓存交互时,需要调用该函数释放内存.
*/
void SymLinkApiFreeMem(char* pBuf);

#pragma pack(push,1)

//字符串处理
struct SymLinkApiString
{
	SymLinkApiString();
	~SymLinkApiString();

	SymLinkApiString(const SymLinkApiString& obj);
	SymLinkApiString& operator=(const SymLinkApiString& obj);
	SymLinkApiString& operator=(const char* pData);
	operator const char *() const; 

	//清除字符串
	void Clear();
	//获取字符串
	const char* GetStr() const;

	//字符串长度
	size_t nLen;
	//存放字符串
	char* pBuf;
};

//SOE
struct CDbCommSOE
{
	CDbCommSOE();
	~CDbCommSOE();

	/*!清除SOE记录*/
	void Clear();

	/*!SOE源,0-采集,1-冗余节点*/
	int m_nSrc;
	/*!数据handle*/
	int m_hRtdbTagHandle;

	/*!SOE类型*/
	int	m_nKind;

	/*!动作值*/
	int	m_nValue;
	/*!动作项,为空时用点描述代替*/
	SymLinkApiString m_csActItem;
	/*!相关数据1*/
	SymLinkApiString m_csRData1;
	/*!相关数据2*/
	SymLinkApiString m_csRData2;
	/*!动作码*/
	int m_nReasonCode;
	/*!动作原因*/
	SymLinkApiString m_csReason;
};


struct CSLEventObject
{
	CSLEventObject();
	~CSLEventObject();
	void Clear();
	//对象句柄,注意:可能是无效值，请慎用
	int	nHandle;

	//UID,内部自动分配的唯一ID,可用于查重,确认等操作
	unsigned int dwUID;
	//传输码,用于传输过程中的链路状态记录等
	unsigned int dwTransCode;	

	//网络站点,事件产生的源头
	SymLinkApiString csSource;
	//计算源:0-系统;1-实时报警;2-逻辑报警
	int nSourceModule;
	//事件产生的业务原因,触发源定制填写
	SymLinkApiString csSourceReason;

	//记录功能码,用于事件服务器策略算法
	int	nFCode1;
	int	nFCode2;

	//事件对象Name-Desc
	int	nTypeID;
	SymLinkApiString csTagName;
	SymLinkApiString csTagDesc;

	//事件对象定义的一些功能,按位使用
	unsigned int dwFunction;
	unsigned int dwFunctionData;

	//事件发生时间
	int  nTime;
	short nTimeMills;
	short nTimeFlag;

	//延时参数(秒)
	int	nDelayParam;

	//报警级别
	int	nLevel;

	//事件内容:编码和文字描述
	int			nStateCode;		//报警状态：L\LL\LLL;H\HH\HHH
	SymLinkApiString csContent;

	//报警值
	int val_nVT;
	union 
	{
		int val_nData;
		float val_fData;
		BYTE val_bData[4];
	};

	//复叫和确认
	int ack_nFlag;			//b01-需要确认
	int ack_nRepeatTimeCyc;	//如果不确认，重复发送周期(秒)
	int ack_nRepeatCounter;	//重复发送计数器
	int ack_nRepeatCountMax;//重复发送次数限制

	//可供源头定制使用的一个用户数据
	int	nUserData;

	//保留字段
	SymLinkApiString	csRsv;
};

//块数据类型
struct TDB_BLOCK
{
	/*!块数据存储格式,0-二进制,1-ASC码*/
	int	m_nFormat;
	/*!预留,程序员灵活使用*/
	int	m_nFlag;
	/*!头部长度*/
	int	m_nHeaderLen;
	/*!头部数据*/
	unsigned char* m_pHeaderData;
	/*!数据长度*/
	int	m_nDataLen;
	/*!数据部分*/
	unsigned char* m_pData;
	/*!描述*/
	SymLinkApiString m_csDesc;
};

//完整块数据
struct CDbCommBlock  
{
	CDbCommBlock();
	~CDbCommBlock();

	CDbCommBlock& operator=(const CDbCommBlock&);
	CDbCommBlock(const CDbCommBlock&);

	/*!清除块数据*/
	void Clear();

	/*!0-采集,1-冗余节点,没有用到*/
	int m_nSrc;
	/*!数据handle*/
	int m_hRtdbTagHandle;
	/*!Key没有用到*/
	int m_nHisKey;
	/*!块数据*/
	TDB_BLOCK m_tBlock;	
};

//数据类型定义
struct SymLinkApiData
{
public:
	SymLinkApiData();
	SymLinkApiData(const SymLinkApiData& src);
	~SymLinkApiData();

	//运算符重载
	SymLinkApiData& operator=(int nData);
	SymLinkApiData& operator=(double dbData);
	SymLinkApiData& operator=(const char* pData);
	SymLinkApiData& operator=(const CDbCommSOE* pSOE);
	SymLinkApiData& operator=(const CSLEventObject* pSLEvent);
	SymLinkApiData& operator=(const CDbCommBlock* pBlock);
	SymLinkApiData& operator=(const SymLinkApiData& src);
	operator int() const; 
	operator double() const; 
	operator const char *() const; 
	
	/*!清除数据*/
	void Clear();
	/*!数据比较*/
	bool CompData(const SymLinkApiData& src) const;
	/*!获取整型数据*/
	int GetInt();
	/*!获取浮点数据*/
	double GetDouble();
	/*!获取字符串数据*/
	const char* GetStr();
	
	/*!点类型*/
	unsigned char Type;
	/*!时间,单位秒*/
	int	nTime;
	/*!时间,单位毫秒*/
	short nTimeMills;
	/*!预留,程序员灵活使用*/
	short nFlag;
	/*!质量戳*/
	int	nQuality;
	/*!存放数据*/
	union {
		int nData;
		struct {char* pBuf;
			   size_t nLen;
		}strData;
		struct {void* pBuf;
		       size_t nLen;
		}binData;
		double dbData;
		CDbCommSOE* pSOEData;
		CDbCommBlock* pBlockData;
		CSLEventObject* pSLEventObject;
	}Data;
};

#pragma pack(pop)


inline SymLinkApiString::SymLinkApiString()
{
	pBuf = NULL;
	nLen = 0;
}

inline SymLinkApiString::~SymLinkApiString()
{
	Clear();
}

inline SymLinkApiString::SymLinkApiString(const SymLinkApiString& obj)
{
	pBuf = NULL;
	nLen = 0;
	*this = obj.GetStr();
}

inline SymLinkApiString& SymLinkApiString::operator =(const SymLinkApiString& obj)
{
	*this = obj.GetStr();
	return *this;
}

inline SymLinkApiString& SymLinkApiString::operator=(const char *pData)
{
	Clear();
	if (pData != NULL)
	{
		nLen = strlen(pData);
		pBuf = SymLinkApiMallocMem(nLen+1);
		strcpy(pBuf, pData);
	}
	return *this;
}

inline SymLinkApiString::operator const char *() const
{
	if(pBuf != NULL)
		return pBuf;
	return "";
}

inline void SymLinkApiString::Clear()
{
	if(pBuf != NULL)
		SymLinkApiFreeMem(pBuf);
	pBuf = NULL;
	nLen = 0;
}

inline const char* SymLinkApiString::GetStr() const
{
	return *this;
}

/*!
 @brief 开辟SOE内存
 @return 开辟的CDbCommSOE内存指针
*/
CDbCommSOE* SymLinkApiMallocSOE();
/*!
 @brief 释放SOE内存
 @param pSOE 内存指针
*/
void SymLinkApiFreeSOE(CDbCommSOE* pSOE);

inline CDbCommSOE::CDbCommSOE()
	: m_nSrc(0),
	m_hRtdbTagHandle(0),
	m_nKind(0),
	m_nValue(0),
	m_nReasonCode(0)
{
}

inline CDbCommSOE::~CDbCommSOE()
{
	Clear();
}

inline void CDbCommSOE::Clear() 
{
}


/*!
 @brief 开辟CSLEventObject内存
 @return 开辟的CSLEventObject内存指针
*/
CSLEventObject* SymLinkApiMallocSLEventObject();
/*!
 @brief 释放SOE内存
 @param pSOE 内存指针
*/
void SymLinkApiFreeSLEventObject(CSLEventObject* pSLEventObject);

inline CSLEventObject::CSLEventObject()
	: nHandle(0),
	dwUID(0),
	dwTransCode(0),
	nSourceModule(0),
	nFCode1(0),
	nFCode2(0),
	nTypeID(0),
	dwFunction(0),
	dwFunctionData(0),
	nDelayParam(0),
	nLevel(0),
	nStateCode(0),
	val_nVT(0),
	val_nData(0),
	nUserData(0),
	ack_nFlag(0),
	ack_nRepeatTimeCyc(300),
	ack_nRepeatCounter(0),
	ack_nRepeatCountMax(3)
{

}

inline CSLEventObject::~CSLEventObject()
{
	Clear();
}

inline void CSLEventObject::Clear() {
}

/*!
 @brief 开辟CDbCommBlock内存
 @return 开辟的CDbCommBlock内存指针
*/
CDbCommBlock* SymLinkApiMallocBlock();
/*!
 @brief 释放CDbCommBlock内存
 @param pBlock 内存指针
*/
void SymLinkApiFreeBlock(CDbCommBlock* pBlock);

inline CDbCommBlock::CDbCommBlock()
	: m_nSrc(0),
	m_hRtdbTagHandle(0),
	m_nHisKey(0)
{
	memset(&m_tBlock, 0, sizeof(TDB_BLOCK));
}

inline CDbCommBlock::~CDbCommBlock()
{
	Clear();
}

inline CDbCommBlock& CDbCommBlock::operator=(const CDbCommBlock& obj)
{
	Clear();
	m_nSrc = obj.m_nSrc;
	m_hRtdbTagHandle = obj.m_hRtdbTagHandle;
	m_nHisKey = obj.m_nHisKey;
	m_tBlock = obj.m_tBlock;

	int nLen = m_tBlock.m_nDataLen;
	if (nLen > 0)
	{
		m_tBlock.m_pData = 
			(unsigned char*)SymLinkApiMallocMem(nLen);
		memcpy(m_tBlock.m_pData, obj.m_tBlock.m_pData, nLen);
	}

	nLen = m_tBlock.m_nHeaderLen;
	if (nLen > 0)
	{
		m_tBlock.m_pHeaderData =
			(unsigned char*)SymLinkApiMallocMem(nLen);
		memcpy(m_tBlock.m_pHeaderData, obj.m_tBlock.m_pHeaderData, nLen);
	}
	return *this;
}
inline CDbCommBlock::CDbCommBlock(const CDbCommBlock& obj)
	: m_nSrc(obj.m_nSrc),
	m_hRtdbTagHandle(obj.m_hRtdbTagHandle),
	m_nHisKey(obj.m_nHisKey)
{
	memset(&m_tBlock, 0, sizeof(TDB_BLOCK));
	*this = obj;
}
inline void CDbCommBlock::Clear()
{
	if (m_tBlock.m_pData)
		SymLinkApiFreeMem((char*)m_tBlock.m_pData);
	if (m_tBlock.m_pHeaderData)
		SymLinkApiFreeMem((char*)m_tBlock.m_pHeaderData);
}

//////////////////////////////////////////////////////////////////////////
inline SymLinkApiData::SymLinkApiData()
{
	nTime = nTimeMills = nFlag = nQuality = 0;
	Type = SYMAPI_DBTAGTYPE_NONE;
	memset(&Data,0,sizeof(Data));
}

inline SymLinkApiData::SymLinkApiData(const SymLinkApiData& src)
{
	nTime = nTimeMills = nFlag = nQuality = 0;
	Type = SYMAPI_DBTAGTYPE_NONE;
	memset(&Data,0,sizeof(Data));
	*this = src;
}

inline SymLinkApiData::~SymLinkApiData()
{
	Clear();
}

inline SymLinkApiData& SymLinkApiData::operator=(int nData)
{
	Clear();
	Type = SYMAPI_DBTAGTYPE_INT;
	Data.nData = nData;
	return *this;
}

inline SymLinkApiData& SymLinkApiData::operator=(double dbData)
{
	Clear();
	Type = SYMAPI_DBTAGTYPE_DOUBLE;
	Data.dbData = dbData;
	return *this;
}

inline SymLinkApiData& SymLinkApiData::operator=(const char *pData)
{
	Clear();
	if (pData != NULL)
	{
		Type = SYMAPI_DBTAGTYPE_STR;
		Data.strData.nLen = strlen(pData);
		Data.strData.pBuf = SymLinkApiMallocMem(Data.strData.nLen+1);
		strcpy(Data.strData.pBuf, pData);
	}
	return *this;
}

inline SymLinkApiData& SymLinkApiData::operator=(const CDbCommSOE *pSOE)
{
	Clear();
	if (pSOE != NULL)
	{
		Type = SYMAPI_DBTAGTYPE_EVENT;
		Data.pSOEData = SymLinkApiMallocSOE();
		*Data.pSOEData = *pSOE;
	}
	return *this;
}
inline SymLinkApiData& SymLinkApiData::operator=(const CSLEventObject *pSLEventObject)
{
	Clear();
	if (pSLEventObject != NULL)
	{
		Type = SYMAPI_DBTAGTYPE_SLEVENT;
		Data.pSLEventObject = SymLinkApiMallocSLEventObject();
		*Data.pSLEventObject = *pSLEventObject;
	}
	return *this;
}
inline SymLinkApiData& SymLinkApiData::operator=(const CDbCommBlock *pBlock)
{
	Clear();
	if (pBlock != NULL)
	{
		Type = SYMAPI_DBTAGTYPE_BLOCK;
		Data.pBlockData = SymLinkApiMallocBlock();
		*Data.pBlockData = *pBlock;
	}
	return *this;
}
inline SymLinkApiData& SymLinkApiData::operator=(const SymLinkApiData& src)
{
	Clear();
	this->Type = src.Type;
	this->nTime = src.nTime;
	this->nTimeMills = src.nTimeMills;
	this->nFlag = src.nFlag;
	this->nQuality = src.nQuality;
	if (src.Type == SYMAPI_DBTAGTYPE_INT)
	{
		*this = src.Data.nData;
	}
	else if (src.Type == SYMAPI_DBTAGTYPE_DOUBLE)
	{
		*this = src.Data.dbData;
	}
	else if (src.Type == SYMAPI_DBTAGTYPE_STR)
	{
		*this = src.Data.strData.pBuf;
	}
	else if (src.Type == SYMAPI_DBTAGTYPE_BLOCK)
	{
		*this =src.Data.pBlockData;
	}
	else if(src.Type == SYMAPI_DBTAGTYPE_EVENT)
	{
		*this = src.Data.pSOEData;
	}
	else if(src.Type == SYMAPI_DBTAGTYPE_SLEVENT)
	{
		*this = src.Data.pSLEventObject;
	}
	return *this;
}

inline SymLinkApiData::operator int() const
{
	if (Type == SYMAPI_DBTAGTYPE_INT)
	{
		return Data.nData;
	}
	else if (Type == SYMAPI_DBTAGTYPE_DOUBLE)
	{
		return int(Data.dbData);
	}
	else if (Type == SYMAPI_DBTAGTYPE_STR)
	{
		if (Data.strData.pBuf != NULL)
			return atol(Data.strData.pBuf);
	}
	return 0;
}

inline SymLinkApiData::operator double() const
{
	if (Type == SYMAPI_DBTAGTYPE_INT)
	{
		return Data.nData;
	}
	else if (Type == SYMAPI_DBTAGTYPE_DOUBLE)
	{
		return Data.dbData;
	}
	else if (Type == SYMAPI_DBTAGTYPE_STR)
	{
		if (Data.strData.pBuf != NULL)
			return atof(Data.strData.pBuf);
	}
	return 0;
}

inline SymLinkApiData::operator const char *() const
{
	if (Type == SYMAPI_DBTAGTYPE_STR)
	{
		if (Data.strData.pBuf != NULL)
			return Data.strData.pBuf;
	}
	return "";
}

inline void SymLinkApiData::Clear()
{
	if ((Type == SYMAPI_DBTAGTYPE_STR) && (Data.strData.pBuf != 0))
	{
		SymLinkApiFreeMem(Data.strData.pBuf);
		Data.strData.pBuf = NULL;
		Data.strData.nLen = 0;
	}
	if (Type == SYMAPI_DBTAGTYPE_BLOCK) 
	{
		SymLinkApiFreeBlock(Data.pBlockData);
	}
	if (Type == SYMAPI_DBTAGTYPE_EVENT) 
	{
		SymLinkApiFreeSOE(Data.pSOEData);	
	}
	if (Type == SYMAPI_DBTAGTYPE_SLEVENT) 
	{
		SymLinkApiFreeSLEventObject(Data.pSLEventObject);	
	}
	Type = SYMAPI_DBTAGTYPE_NONE;
	Data.strData.pBuf = NULL;
	Data.strData.nLen = 0;
}

inline bool SymLinkApiData::CompData(const SymLinkApiData& src) const
{
	if (Type == SYMAPI_DBTAGTYPE_INT)
	{
		if (src.Type == SYMAPI_DBTAGTYPE_INT)
		{
			return Data.nData==src.Data.nData;
		}
		else if (src.Type == SYMAPI_DBTAGTYPE_DOUBLE)
		{
			return fabs(Data.nData - src.Data.dbData) <= DOUBLE_DATAMIN;
		}
	}
	else if (Type == SYMAPI_DBTAGTYPE_DOUBLE)
	{
		if (src.Type == SYMAPI_DBTAGTYPE_INT)
		{
			return fabs(Data.dbData - src.Data.nData) <= DOUBLE_DATAMIN;
		}
		else if (src.Type == SYMAPI_DBTAGTYPE_DOUBLE)
		{
			return fabs(Data.dbData - src.Data.dbData) <= DOUBLE_DATAMIN;
		}
	}
	else if (Type == SYMAPI_DBTAGTYPE_STR)
	{
		if (src.Type == SYMAPI_DBTAGTYPE_STR)
		{
			const char *pDesc = (Data.strData.pBuf)?(Data.strData.pBuf):"";
			const char *pSrc = (src.Data.strData.pBuf)?(src.Data.strData.pBuf):"";
			return strcmp(pDesc,pSrc) == 0;
		}
	}
	else if (Type == SYMAPI_DBTAGTYPE_EVENT || Type == SYMAPI_DBTAGTYPE_BLOCK || Type == SYMAPI_DBTAGTYPE_SLEVENT)
	{
		return false;
	}
	return false;
}
 
inline int SymLinkApiData::GetInt()
{
	return *this;
}

inline double SymLinkApiData::GetDouble()
{
	return *this;
}

inline const char* SymLinkApiData::GetStr()
{
	return *this;
}

//函数指针定义

/*!
 @brief 状态变化时的回调函数
 @param ptr1 指向本对象的指针
 @param ptr2 指向调用者的指针
 @param nStatus 组件状态
*/
typedef void (*STATUS_CHANGE_FUNC)(void* ptr1, void* ptr2, int nStatus);

/*!
 @brief 数据变化后的回调函数
 @param ptr1 指向本对象的指针
 @param ptr2 指向调用者的指针
 @param nChangeCount 点变化个数
 @param pChangeHandle 变化的点ID
*/
typedef void (*DATA_CHANGE_FUNC)(void* ptr1, void* ptr2, int nChangeCount, int* pChangeHandle);

/*!
 @brief 通用事件变化后的回调函数
 @param ptr1 指向本对象的指针
 @param ptr2 指向调用者的指针
 @param nChangeCount 点变化个数
*/
typedef void (*SLEVENT_CHANGE_FUNC)(void* ptr1, void* ptr2, int nChangeCount);

//CSymLinkApi类定义
class CSymLinkApi
{
public:
	/*!
	 @brief 传入调用者指针
	 @param ptr 调用者指针
	*/
	virtual void SetCallerPtr(void* ptr) = 0;
	/*!
	 @brief 设置状态变化时的回调函数
	 @param hFunc 回调函数指针
	 @note 回调函数的具体定义,参见STATUS_CHANGE_FUNC
	*/
	virtual void SetStatusChangeFunc(STATUS_CHANGE_FUNC hFuncc) = 0;
	/*!
	 @brief 设置数据变化后的回调函数
	 @param hFunc 回调函数指针
	 @note 回调函数的具体定义,参见DATA_CHANGE_FUNC
	*/
	virtual void SetDataChangeFunc(DATA_CHANGE_FUNC hFunc) = 0;
	/*!
	 @brief 设置变化缓存功能状态
	 @param nStatus 缓存状态
	 @note 在需要获取数据变化的中间数据时,可以设置nStatus=1,设置后即可调用GetDbTagChangeCount,GetDbTagChange等方法获取数据变化的过程数据,默认为关闭状态nStatus=0
	*/
	virtual void SetChangeBufStatus(int nStatus) = 0;
	/*!
	 @brief 设置断线缓存功能状态
	 @param nStatus	缓存状态
	 @note 在需要获取断线缓存数据时,可以设置nStatus=1,设置后即可调用GetDbTagTxSaveCount,GetDbTagTxSave等方法获取断线缓存数据,默认为关闭状态(断线缓存功能需要读写Windows的临时文件,确保程序有相关临时目录的读写权限及其相应的磁盘空间)nStatus=0
	*/
	virtual void SetTxSaveBufStatus(int nStatus) = 0;
	/*!
	 @brief 获取发送心跳包的时间
	 @return 超时时间(单位:毫秒)
	 @note 默认值为20000(20秒)
	*/
	virtual int GetPackTimeOut() = 0;
	/*!
	 @brief 设置发送心跳包的时间
	 @param nTimeout 时间(单位:毫秒)
	 @note 默认值为20000(20秒)
	*/
	virtual void SetPackTimeOut(int nTimeout) = 0;
	/*!
	 @brief 获取链路超时时间
	 @return 超时时间(单位:毫秒)
	 @note 默认值为60000(60秒)
	*/
	virtual int GetLinkTimeOut() = 0;
	/*!
	 @brief 设置链路超时时间
	 @param nTimeout 时间(单位:毫秒)
	 @note 默认值为60000(60秒)
	*/
	virtual void SetLinkTimeOut(int nTimeout) = 0;	
	/*!
	 @brief 获取报文等待时间
	 @return 超时时间(单位:毫秒)
	 @note 默认值为10000(10秒)
	*/
	virtual int GetCmdTimeOut() = 0;
	/*!
	 @brief 设置报文等待时间
	 @param nTimeout 时间(单位:毫秒)
	 @note 默认值为10000(10秒)
	*/
	virtual void SetCmdTimeOut(int nTimeout) = 0;	
	/*!
	 @brief 获取总召时间
	 @return 超时时间(单位:毫秒)
	 @note 默认值为60000(60秒)
	*/
	virtual int GetCallAllTimeOut() = 0;
	/*!
	 @brief 设置总召时间
	 @param nTimeout 时间(单位:毫秒)
	 @note 默认值为60000(60秒)
	*/
	virtual void SetCallAllTimeOut(int nTimeout) = 0;	
	/*!
	 @brief 连接服务器
	 @param lpServerIP 服务器IP地址
	 @param nPort 服务器端口
	 @param lpUser 用户名
	 @param lpPass 密码
	 @param nType 类型(暂时无效,默认为0)
	 @return 创建连接对象是否成功
	 @note 连接服务器,采用异步模式,是否已经连接上,需要等待回调函数或者判断GetStatus返回值,该接口只需要调用一次即可,启动连接服务器成功后,如果遇外部情况链路中断后,模块会自动重试直到调用DisConnect方法
	*/
	virtual bool ConnectServer(const char* lpServerIP, int nPort, const char *lpUser, const char *lpPass, int nType) = 0;
	/*!
	 @brief 断开客户端连接
	*/
	virtual void DisConnect() = 0;
	/*!
	 @brief 得到组件状态
	 @return 组件状态
	 @note 状态值参考头文件中的宏定义(0时为正常状态)
	*/
	virtual int GetStatus() = 0;
	/*!
	 @brief 获取错误信息
	 @return 错误信息
	 @note 当GetStatus返回不为0时可以调用该接口获取错误信息,错误信息参考头文件中的宏定义
	*/
	virtual int GetLastErr() = 0;
	/*!
	 @brief 获取数据库版本信息
	 @param nVer 版本信息
	 @return 函数执行结果,参考头文件中的宏定义
	 @note 当数据库版本发生变化时,代表数据库点表等配置信息发生了改变
	*/
	virtual int GetDbVersion(int& nVer) = 0;
	/*!
	 @brief 获取数据库点表信息
	 @param lpRoot 数据库节点名称(根节点为"")
	 @param nType 数据的类型(0全部信息,1全部节点信息,2本节点的信息)
	 @param dbInfo 数据信息
	 @return 函数执行结果,参考头文件中的宏定义
	 @note 获取的节点信息为xml个数内容如下:
	 @note <?xml version="1.0" encoding="GB2312"?>
	 @note <root>
	 @note  <dbgroup name="" longname=" " desc=" " typeid="">
	 @note   <dbtag name="" longname="" desc="" typeid="" vt="" handleid=""/>
	 @note  </dbgroup>
	 @note </root>
	 @note 其中节点信息为dbgroup,包括属性name名称,longname长名称,desc描述,typeid类型ID,数据点信息为dbtag,包括属性name名称,longname长名称,desc描述,typeid类型ID,handleid点handle
	*/
	virtual int GetDbInfo(const char *lpRoot, int nType, SymLinkApiString& dbInfo) = 0;
	/*!
	 @brief 通过点handle获取数据库点信息
	 @param nHandle 数据库点handle
	 @param tagInfo	数据信息
	 @return 函数执行结果,参考头文件中的宏定义
	 @note 获取的数据点信息为xml个数内容如下:
	 @note <?xml version="1.0" encoding="GB2312"?>
	 @note <root name="" longname="" desc="" typeid="" vt="" handleid=""/>
	 @note 其中包括属性name名称,longname长名称,desc描述,typeid类型ID,handleid点handle
	*/
	virtual int GetDbTagInfoByHandle(int nHandle, SymLinkApiString& tagInfo) = 0;
	/*!
	 @brief 通过点长名获取数据库点信息
	 @param lpName 数据库点长点名
	 @param tagInfo	数据信息
	 @return 函数执行结果,参考头文件中的宏定义
	 @note 获取的数据点信息为xml个数内容如下:
     @note <?xml version="1.0" encoding="GB2312"?>
     @note <root name="" longname="" desc="" typeid="" vt="" handleid=""/>
     @note 其中包括属性name名称,longname长名称,desc描述,typeid类型ID,handleid点handle
	*/
	virtual int GetDbTagInfoByName(const char *lpName, SymLinkApiString& tagInfo) = 0;
	/*!
	 @brief 获取数据库点长点名
	 @param nHandle	数据库点handle
	 @param tagName	数据点长点名
	 @return 函数执行结果,参考头文件中的宏定义
	*/
	virtual int GetDbTagName(int nHandle, SymLinkApiString& tagName) = 0;
	/*!
	 @brief 获取数据库点handle
	 @param lpName 数据库点长点名
	 @param tagHandle 数据点handle
	 @return 函数执行结果,参考头文件中的宏定义
	*/
	virtual int GetDbTagHandle(const char *lpName, int& tagHandle) = 0;
	/*!
	 @brief 通过点handle获取数据库点数值
	 @param nHandle	数据库点handle
	 @param tagData	数据点数据
	 @return 函数执行结果,参考头文件中的宏定义
	*/
	virtual int GetDbTagDataByHandle(int nHandle, SymLinkApiData& tagData) = 0;
	/*!
	 @brief 通过点长名获取数据库点数值
	 @param lpName 数据库点长点名
	 @param tagData 数据点数据
	 @return 函数执行结果,参考头文件中的宏定义
	*/
	virtual int GetDbTagDataByName(const char *lpName, SymLinkApiData& tagData) = 0;
	/*!
	 @brief 获取数据变化缓存个数
	 @param nCount 数据个数
	 @return 函数执行结果,参考头文件中的宏定义
	 @note 内部缓存区大小为点个数的2倍,超过缓存大小时会丢弃最老的变化数据,接到有数据变化的通知后,需要及时获取防止数据丢失
	*/
	virtual int GetDbTagChangeCount(int &nCount) = 0;
	/*!
	 @brief 获取数据变化缓存数据
	 @param pHandleBuf 变化数据的数据库点handle
	 @param pDataBuf 变化数据
	 @param nBufSize 前两个缓存区的个数(初始值为缓存区大小,返回值为获取的数据大小)
	 @param nHandle 指定的数据库点handle
	 @return 函数执行结果,参考头文件中的宏定义
	 @note 获取缓存数据时可以先获取缓存区的个数然后开辟相应的缓存空间,也可根据需要开辟固定的缓存区获取(尽量开辟大缓存一次获取节省交互次数)
	*/
	virtual int GetDbTagChange(int *pHandleBuf, SymLinkApiData *pDataBuf, int& nBufSize, int nHandle = -1) = 0;
	/*!
	 @brief 清理数据变化缓存数据
	 @note 不处理变化缓存数据时可以调用该函数直接清理缓存数据,调用GetDbTagChange后缓存会自动清理相关数据不必再调用ClearDbTagChange
	*/
	virtual void ClearDbTagChange() = 0;
	/*!
	 @brief 通过据库点handle设置数据库点数据
	 @param nHandle 据库点handle
	 @param tagData	数据
	 @param pResult	设置数据返回结果
	 @param pErrStr	设置数据返回信息
	 @return 函数执行结果,参考头文件中的宏定义
	*/
	virtual int SetDbTagDataByHandle(int nHandle, const SymLinkApiData& tagData, int* pResult = 0, SymLinkApiString *pErrStr = 0) = 0;
	/*!
	 @brief 通过据库点长点名设置数据库点数据
	 @param lpName 据库点长点名
	 @param tagData	数据
	 @param pResult	设置数据返回结果
	 @param pErrStr	设置数据返回信息
	 @return 函数执行结果,参考头文件中的宏定义
	*/
	virtual int SetDbTagDataByName(const char *lpName, const SymLinkApiData& tagData, int* pResult = 0, SymLinkApiString *pErrStr = 0) = 0;
	/*!
	 @brief 获取断线缓存个数
	 @param nCount 数据个数
	 @return 函数执行结果,参考头文件中的宏定义
	 @note 缓存数据保存于windows的临时文件中,为了防止文件过大,需要及时获取数据
	*/
	virtual int GetDbTagTxSaveCount(int &nCount) = 0;
	/*!
	 @brief 获取断线缓存数据
	 @param pHandleBuf 缓存数据的数据库点handle
	 @param pDataBuf 缓存数据
	 @param nBufSize 前两个缓存区的个数(初始值为缓存区大小,返回值为获取的数据大小)
	 @return 函数执行结果,参考头文件中的宏定义
	 @note 获取缓存数据时可以先获取缓存区的个数然后开辟相应的缓存空间,也可根据需要开辟固定的缓存区获取(尽量开辟大缓存一次获取节省交互次数)
	*/
	virtual int GetDbTagTxSave(int *pHandleBuf, SymLinkApiData *pDataBuf, int& nBufSize) = 0;
	/*!
	 @brief 清理断线缓存数据
	 @note 不处理断线缓存数据时可以调用该函数直接清理缓存数据,调用GetDbTagTxSave后缓存会自动清理相关数据不必再调用ClearDbTagTxSave
	*/
	virtual void ClearDbTagTxSave() = 0;

	/*!
	 @brief 通过点Handle获取断线缓存数据
	 @param tagHandle 缓存数据的数据库点handle
	 @param startTime 获取数据的起始时间
	 @param endTime 获取数据的结束时间
	 @param pDataBuf 缓存数据
	 @param nBufSize 前两个缓存区的个数(初始值为缓存区大小,返回值为获取的数据大小)
	 @return 函数执行结果,参考头文件中的宏定义
	*/
	virtual int GetDbTagHistory(int tagHandle,time_t startTime,time_t endTime,SymLinkApiData* pDataBuf,int& nBufSize) = 0;
	/*!
	 @brief 通过点长名获取断线缓存数据
	 @param lpTagName 缓存数据的数据库点长名
	 @param startTime 获取数据的起始时间
	 @param endTime 获取数据的结束时间
	 @param pDataBuf 缓存数据
	 @param nBufSize 前两个缓存区的个数(初始值为缓存区大小,返回值为获取的数据大小)
	 @return 函数执行结果,参考头文件中的宏定义
	*/
	virtual int GetDbTagHistory(const char* lpTagName,time_t startTime,time_t endTime,SymLinkApiData *pDataBuf,int& nBufSize) = 0;
	/*!
	 @brief 获取点变化缓存个数
	 @return 缓存个数
	 @note 返回-1时代表使用默认缓存大小10000+2*总点数
	*/
	virtual int GetChangeBufSize() = 0;
	/*!
	 @brief 设置报文等待时间
	 @param nSize 时间(单位:毫秒)
	 @note 最小值为1000，小于1000时使用默认值缓存大小10000+2*总点数
	*/
	virtual void SetChangeBufSize(int nSize) = 0;	

	//设置数据库点数据,可以携带FOD/FOC返回数据 -Frank Added 2013.12.8
	virtual int SetDbTagDataByHandle2(int nHandle, const SymLinkApiData& tagData, int* pResult, SymLinkApiString *pErrStr,void* pReData,int& nReDataLen) = 0;
	virtual int SetDbTagDataByName2(const char *lpName, const SymLinkApiData& tagData, int* pResult, SymLinkApiString *pErrStr,void* pReData,int& nReDataLen) = 0;

	//SymLink通用事件接口 -Frank Added 2013.12.20
	virtual void SetSLEventChangeFunc(SLEVENT_CHANGE_FUNC hFunc) = 0;
	virtual int GetSLEventChangeCount(int &nCount) = 0;
	virtual int GetSLEventChange(SymLinkApiData *pDataBuf, int& nBufSize) = 0;
	virtual void ClearSLEventChange() = 0;
	//设置对时周期,单位:分钟,0-不对对时
	virtual void SetTimeAdjust(int nMinutes) = 0;
	//设置每一包数据处理的超时参数,如果在该时间内数据处理不完,可能会丢掉部分过程数据
	//单位:分钟,有效参数为:1-30内部默认参数为5分钟;
	virtual void SetDealDataTimeout(int nMinutes) = 0;
	//设置客户端类型
	virtual void SetBrgClientKind(int nKind) = 0;
	//获取数据库配置变化的计数器,<=0 未无效
	virtual int GetDbConfigChangedCounter(int nFlag = 0) = 0;
	//设置数据结构缓存目录,如果不设置,则采用默认路径
	virtual int SetCachePath(int nFlag,const char* sPath) = 0;
	//去网关设备上获取标签块数据
	virtual int GetDbTagCacheBlob(const char *lpName,SymLinkApiData& tagData) = 0;

};

/*!
 @brief 新建CSymLinkApi对象
 @param nType 调用类型(暂时无效,默认为0)
 @return CSymLinkApi对象指针
*/
CSymLinkApi* CreateSymLinkApi(int nType);

/*!
 @brief 销毁CSymLinkApi对象
 @param lpSymApi SymLinkApi对象指针
*/
void FreeSymLinkApi(CSymLinkApi* lpSymApi);

#endif

#endif

