#ifndef __SYMLINK_API_H_INCLUDED__
#define __SYMLINK_API_H_INCLUDED__

#ifdef __cplusplus

/*!
 @file SymLinkApi.h
 @brief SymLinkApi�ṩ�鿴SymLink�豸�е���Ϣ�ķ���.
 @version 1.0
 @author Paul.Wen
 @date 2013��3��19��
 @details Copyright (c) 2008 ~ 2013,������˼�Ƽ����޹�˾.
 @note SymLinkApi��Windows�Ķ�̬��DLL��ʽ�ṩ,������Բ��ñ�׼C++ʵ��,���ô���ӿ���ķ�ʽ�ṩ,�ӿڲ���VS2005��д,ʹ��ǰȷ����װ��΢���������а�vcredist_x86.exe.
*/

//ͨѶ״̬
/*!״̬����*/
#define SYMAPI_STATUS_OK			0
/*!��ʼ״̬*/
#define SYMAPI_STATUS_NOCONNECT		1
/*!���ӶϿ�*/
#define SYMAPI_STATUS_DISCONNECT	2
/*!������*/
#define SYMAPI_STATUS_CONNECTING	3
/*!���ӳɹ�*/
#define SYMAPI_STATUS_CONNECTED		4
/*!���͵�¼����*/
#define SYMAPI_STATUS_LOGIN			5
/*!��¼����*/
#define SYMAPI_STATUS_LOGIN_OK		6
/*!��¼ʧ��(LastErr��ȡԭ��)*/
#define SYMAPI_STATUS_LOGIN_FAIL	7
/*!��ȡ���ݿ��*/
#define SYMAPI_STATUS_REQCONFIG		8
/*!��ȡ���ݿ������*/
#define SYMAPI_STATUS_REQCONFIG_OK	9
/*!��ȡ���ݿ��ʧ��*/
#define SYMAPI_STATUS_REQCONFIG_FAIL 10
/*!���ٻ�*/
#define SYMAPI_STATUS_REQALL		11
//���ٻ�����
#define SYMAPI_STATUS_REQALL_OK		12
/*!���ٻ�ʧ��*/
#define SYMAPI_STATUS_REQALL_FAIL	13
/*!���ݿ�汾�����仯*/
#define SYMAPI_STATUS_VER			14
/*!�ж��߻�������*/
#define SYMAPI_STATUS_TX			15

//������
/*!����*/
#define SYMAPI_ERR_OK				0
/*!���ʱ*/
#define SYMAPI_ERR_TIMEOUT			-1
/*!��ѹ��ʧ��*/
#define SYMAPI_ERR_UNCOMPRESS		-2
/*!���ݰ汾�ı�*/
#define SYMAPI_ERR_VER				-3
/*!δ����*/
#define SYMAPI_ERR_CONNECT			-4
/*!δ��ɳ�ʼ��*/
#define SYMAPI_ERR_INIT				-5
/*!����δ�ҵ�*/
#define SYMAPI_ERR_FIND				-6
/*!��������*/
#define SYMAPI_ERR_PARAM			-7
/*!���ö������*/
#define SYMAPI_ERR_CMDBUF			-8
/*!���ó�ʱ*/
#define SYMAPI_ERR_CMDTIME			-9
/*!���÷��ش���*/
#define SYMAPI_ERR_CMDERR			-10
/*!���ܱ���ֹ*/
#define SYMAPI_ERR_DISABLE			-11

//��½������

/*!�û���¼ʧ��*/
#define SYMAPI_ERR_LOGIN_FAIL		-1000
/*!�û�������*/
#define SYMAPI_ERR_LOGIN_USER		-1001
/*!�������*/
#define SYMAPI_ERR_LOGIN_PASS		-1002
/*!�û���ֹ*/
#define SYMAPI_ERR_LOGIN_INV		-1003
/*!���Ƶ�¼*/
#define SYMAPI_ERR_LOGIN_DIS		-1004
/*!�ظ���¼*/
#define SYMAPI_ERR_LOGIN_RE			-1009
/*!������Ҫ�û��ȵ�¼*/
#define SYMAPI_ERR_LOGIN_NULL		-1090
/*!�汾��һ��,��Ҫ����API*/
#define SYMAPI_ERR_LOGIN_VER		-1100


// ��ʷ��ѯ������

/*!TagID̫��,��ϵͳ��ʼ��ʱ����TagID����*/
#define QUERY_TASKID_ERROR			-10070
/*!��ѯ���ʹ���*/
#define QUERY_TYPE_ERROR			-10071
/*!��ѯʱ�����*/
#define QUERY_TIME_ERROR			-10072
/*!TagID������*/
#define TAGID_NOT_EXIST				-10073
/*!TagID�Ѵ���*/
#define TAGID_ALREADY_EXIST			-10074
/*Tag����̫��*/
#define TAG_COUNT_BIGGER			-10075
/*!TagID̫��*/
#define TAGID_BIGGER				-10076
/*!����ѯ��û������*/
#define QUERY_DATA_EMPTY			-10077
/*!����ѯ��û���ҵ�*/
#define QUERY_TAGID_NOTFOUND		-10078

/*!��ȡ������Ϣ���������*/
#define SYMAPI_INFO_TYPE_ALL		0
/*!��ȡ��������Ϣ*/
#define SYMAPI_INFO_TYPE_GROUP		1
/*!��ȡ����ĵ����*/
#define SYMAPI_INFO_TYPE_SELF		2

//������
/*!��*/
#define SYMAPI_DBTAGTYPE_NONE		0
/*!����*/
#define SYMAPI_DBTAGTYPE_INT		1
/*!����*/
#define SYMAPI_DBTAGTYPE_DOUBLE		2
/*!�ַ���*/
#define SYMAPI_DBTAGTYPE_STR		3
/*!��*/
#define SYMAPI_DBTAGTYPE_BLOCK		4
/*!�¼���*/
#define SYMAPI_DBTAGTYPE_EVENT		5
/*!ͨ���豸�¼�*/
#define SYMAPI_DBTAGTYPE_SLEVENT	6

#include <math.h>
#define DOUBLE_DATAMIN				0.00000001

//�ڴ����

/*!
 @brief �����ڴ�
 @param Len �����ڴ泤��
 @return ���ٵ��ڴ�ָ��
 @note Ϊ�˱�֤SymLinkApi���ⲿ������֮����ڴ����ʽһ��,���ýӿ����û��潻��ʱ,��Ҫ���øú��������ڴ�.
*/
char* SymLinkApiMallocMem(size_t Len);
/*!
 @brief �ͷ��ڴ�
 @param pBuf �ڴ�ָ��
 @note Ϊ�˱�֤SymLinkApi���ⲿ������֮����ڴ����ʽһ��,���ýӿ����û��潻��ʱ,��Ҫ���øú����ͷ��ڴ�.
*/
void SymLinkApiFreeMem(char* pBuf);

#pragma pack(push,1)

//�ַ�������
struct SymLinkApiString
{
	SymLinkApiString();
	~SymLinkApiString();

	SymLinkApiString(const SymLinkApiString& obj);
	SymLinkApiString& operator=(const SymLinkApiString& obj);
	SymLinkApiString& operator=(const char* pData);
	operator const char *() const; 

	//����ַ���
	void Clear();
	//��ȡ�ַ���
	const char* GetStr() const;

	//�ַ�������
	size_t nLen;
	//����ַ���
	char* pBuf;
};

//SOE
struct CDbCommSOE
{
	CDbCommSOE();
	~CDbCommSOE();

	/*!���SOE��¼*/
	void Clear();

	/*!SOEԴ,0-�ɼ�,1-����ڵ�*/
	int m_nSrc;
	/*!����handle*/
	int m_hRtdbTagHandle;

	/*!SOE����*/
	int	m_nKind;

	/*!����ֵ*/
	int	m_nValue;
	/*!������,Ϊ��ʱ�õ���������*/
	SymLinkApiString m_csActItem;
	/*!�������1*/
	SymLinkApiString m_csRData1;
	/*!�������2*/
	SymLinkApiString m_csRData2;
	/*!������*/
	int m_nReasonCode;
	/*!����ԭ��*/
	SymLinkApiString m_csReason;
};


struct CSLEventObject
{
	CSLEventObject();
	~CSLEventObject();
	void Clear();
	//������,ע��:��������Чֵ��������
	int	nHandle;

	//UID,�ڲ��Զ������ΨһID,�����ڲ���,ȷ�ϵȲ���
	unsigned int dwUID;
	//������,���ڴ�������е���·״̬��¼��
	unsigned int dwTransCode;	

	//����վ��,�¼�������Դͷ
	SymLinkApiString csSource;
	//����Դ:0-ϵͳ;1-ʵʱ����;2-�߼�����
	int nSourceModule;
	//�¼�������ҵ��ԭ��,����Դ������д
	SymLinkApiString csSourceReason;

	//��¼������,�����¼������������㷨
	int	nFCode1;
	int	nFCode2;

	//�¼�����Name-Desc
	int	nTypeID;
	SymLinkApiString csTagName;
	SymLinkApiString csTagDesc;

	//�¼��������һЩ����,��λʹ��
	unsigned int dwFunction;
	unsigned int dwFunctionData;

	//�¼�����ʱ��
	int  nTime;
	short nTimeMills;
	short nTimeFlag;

	//��ʱ����(��)
	int	nDelayParam;

	//��������
	int	nLevel;

	//�¼�����:�������������
	int			nStateCode;		//����״̬��L\LL\LLL;H\HH\HHH
	SymLinkApiString csContent;

	//����ֵ
	int val_nVT;
	union 
	{
		int val_nData;
		float val_fData;
		BYTE val_bData[4];
	};

	//���к�ȷ��
	int ack_nFlag;			//b01-��Ҫȷ��
	int ack_nRepeatTimeCyc;	//�����ȷ�ϣ��ظ���������(��)
	int ack_nRepeatCounter;	//�ظ����ͼ�����
	int ack_nRepeatCountMax;//�ظ����ʹ�������

	//�ɹ�Դͷ����ʹ�õ�һ���û�����
	int	nUserData;

	//�����ֶ�
	SymLinkApiString	csRsv;
};

//����������
struct TDB_BLOCK
{
	/*!�����ݴ洢��ʽ,0-������,1-ASC��*/
	int	m_nFormat;
	/*!Ԥ��,����Ա���ʹ��*/
	int	m_nFlag;
	/*!ͷ������*/
	int	m_nHeaderLen;
	/*!ͷ������*/
	unsigned char* m_pHeaderData;
	/*!���ݳ���*/
	int	m_nDataLen;
	/*!���ݲ���*/
	unsigned char* m_pData;
	/*!����*/
	SymLinkApiString m_csDesc;
};

//����������
struct CDbCommBlock  
{
	CDbCommBlock();
	~CDbCommBlock();

	CDbCommBlock& operator=(const CDbCommBlock&);
	CDbCommBlock(const CDbCommBlock&);

	/*!���������*/
	void Clear();

	/*!0-�ɼ�,1-����ڵ�,û���õ�*/
	int m_nSrc;
	/*!����handle*/
	int m_hRtdbTagHandle;
	/*!Keyû���õ�*/
	int m_nHisKey;
	/*!������*/
	TDB_BLOCK m_tBlock;	
};

//�������Ͷ���
struct SymLinkApiData
{
public:
	SymLinkApiData();
	SymLinkApiData(const SymLinkApiData& src);
	~SymLinkApiData();

	//���������
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
	
	/*!�������*/
	void Clear();
	/*!���ݱȽ�*/
	bool CompData(const SymLinkApiData& src) const;
	/*!��ȡ��������*/
	int GetInt();
	/*!��ȡ��������*/
	double GetDouble();
	/*!��ȡ�ַ�������*/
	const char* GetStr();
	
	/*!������*/
	unsigned char Type;
	/*!ʱ��,��λ��*/
	int	nTime;
	/*!ʱ��,��λ����*/
	short nTimeMills;
	/*!Ԥ��,����Ա���ʹ��*/
	short nFlag;
	/*!������*/
	int	nQuality;
	/*!�������*/
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
 @brief ����SOE�ڴ�
 @return ���ٵ�CDbCommSOE�ڴ�ָ��
*/
CDbCommSOE* SymLinkApiMallocSOE();
/*!
 @brief �ͷ�SOE�ڴ�
 @param pSOE �ڴ�ָ��
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
 @brief ����CSLEventObject�ڴ�
 @return ���ٵ�CSLEventObject�ڴ�ָ��
*/
CSLEventObject* SymLinkApiMallocSLEventObject();
/*!
 @brief �ͷ�SOE�ڴ�
 @param pSOE �ڴ�ָ��
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
 @brief ����CDbCommBlock�ڴ�
 @return ���ٵ�CDbCommBlock�ڴ�ָ��
*/
CDbCommBlock* SymLinkApiMallocBlock();
/*!
 @brief �ͷ�CDbCommBlock�ڴ�
 @param pBlock �ڴ�ָ��
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

//����ָ�붨��

/*!
 @brief ״̬�仯ʱ�Ļص�����
 @param ptr1 ָ�򱾶����ָ��
 @param ptr2 ָ������ߵ�ָ��
 @param nStatus ���״̬
*/
typedef void (*STATUS_CHANGE_FUNC)(void* ptr1, void* ptr2, int nStatus);

/*!
 @brief ���ݱ仯��Ļص�����
 @param ptr1 ָ�򱾶����ָ��
 @param ptr2 ָ������ߵ�ָ��
 @param nChangeCount ��仯����
 @param pChangeHandle �仯�ĵ�ID
*/
typedef void (*DATA_CHANGE_FUNC)(void* ptr1, void* ptr2, int nChangeCount, int* pChangeHandle);

/*!
 @brief ͨ���¼��仯��Ļص�����
 @param ptr1 ָ�򱾶����ָ��
 @param ptr2 ָ������ߵ�ָ��
 @param nChangeCount ��仯����
*/
typedef void (*SLEVENT_CHANGE_FUNC)(void* ptr1, void* ptr2, int nChangeCount);

//CSymLinkApi�ඨ��
class CSymLinkApi
{
public:
	/*!
	 @brief ���������ָ��
	 @param ptr ������ָ��
	*/
	virtual void SetCallerPtr(void* ptr) = 0;
	/*!
	 @brief ����״̬�仯ʱ�Ļص�����
	 @param hFunc �ص�����ָ��
	 @note �ص������ľ��嶨��,�μ�STATUS_CHANGE_FUNC
	*/
	virtual void SetStatusChangeFunc(STATUS_CHANGE_FUNC hFuncc) = 0;
	/*!
	 @brief �������ݱ仯��Ļص�����
	 @param hFunc �ص�����ָ��
	 @note �ص������ľ��嶨��,�μ�DATA_CHANGE_FUNC
	*/
	virtual void SetDataChangeFunc(DATA_CHANGE_FUNC hFunc) = 0;
	/*!
	 @brief ���ñ仯���湦��״̬
	 @param nStatus ����״̬
	 @note ����Ҫ��ȡ���ݱ仯���м�����ʱ,��������nStatus=1,���ú󼴿ɵ���GetDbTagChangeCount,GetDbTagChange�ȷ�����ȡ���ݱ仯�Ĺ�������,Ĭ��Ϊ�ر�״̬nStatus=0
	*/
	virtual void SetChangeBufStatus(int nStatus) = 0;
	/*!
	 @brief ���ö��߻��湦��״̬
	 @param nStatus	����״̬
	 @note ����Ҫ��ȡ���߻�������ʱ,��������nStatus=1,���ú󼴿ɵ���GetDbTagTxSaveCount,GetDbTagTxSave�ȷ�����ȡ���߻�������,Ĭ��Ϊ�ر�״̬(���߻��湦����Ҫ��дWindows����ʱ�ļ�,ȷ�������������ʱĿ¼�Ķ�дȨ�޼�����Ӧ�Ĵ��̿ռ�)nStatus=0
	*/
	virtual void SetTxSaveBufStatus(int nStatus) = 0;
	/*!
	 @brief ��ȡ������������ʱ��
	 @return ��ʱʱ��(��λ:����)
	 @note Ĭ��ֵΪ20000(20��)
	*/
	virtual int GetPackTimeOut() = 0;
	/*!
	 @brief ���÷�����������ʱ��
	 @param nTimeout ʱ��(��λ:����)
	 @note Ĭ��ֵΪ20000(20��)
	*/
	virtual void SetPackTimeOut(int nTimeout) = 0;
	/*!
	 @brief ��ȡ��·��ʱʱ��
	 @return ��ʱʱ��(��λ:����)
	 @note Ĭ��ֵΪ60000(60��)
	*/
	virtual int GetLinkTimeOut() = 0;
	/*!
	 @brief ������·��ʱʱ��
	 @param nTimeout ʱ��(��λ:����)
	 @note Ĭ��ֵΪ60000(60��)
	*/
	virtual void SetLinkTimeOut(int nTimeout) = 0;	
	/*!
	 @brief ��ȡ���ĵȴ�ʱ��
	 @return ��ʱʱ��(��λ:����)
	 @note Ĭ��ֵΪ10000(10��)
	*/
	virtual int GetCmdTimeOut() = 0;
	/*!
	 @brief ���ñ��ĵȴ�ʱ��
	 @param nTimeout ʱ��(��λ:����)
	 @note Ĭ��ֵΪ10000(10��)
	*/
	virtual void SetCmdTimeOut(int nTimeout) = 0;	
	/*!
	 @brief ��ȡ����ʱ��
	 @return ��ʱʱ��(��λ:����)
	 @note Ĭ��ֵΪ60000(60��)
	*/
	virtual int GetCallAllTimeOut() = 0;
	/*!
	 @brief ��������ʱ��
	 @param nTimeout ʱ��(��λ:����)
	 @note Ĭ��ֵΪ60000(60��)
	*/
	virtual void SetCallAllTimeOut(int nTimeout) = 0;	
	/*!
	 @brief ���ӷ�����
	 @param lpServerIP ������IP��ַ
	 @param nPort �������˿�
	 @param lpUser �û���
	 @param lpPass ����
	 @param nType ����(��ʱ��Ч,Ĭ��Ϊ0)
	 @return �������Ӷ����Ƿ�ɹ�
	 @note ���ӷ�����,�����첽ģʽ,�Ƿ��Ѿ�������,��Ҫ�ȴ��ص����������ж�GetStatus����ֵ,�ýӿ�ֻ��Ҫ����һ�μ���,�������ӷ������ɹ���,������ⲿ�����·�жϺ�,ģ����Զ�����ֱ������DisConnect����
	*/
	virtual bool ConnectServer(const char* lpServerIP, int nPort, const char *lpUser, const char *lpPass, int nType) = 0;
	/*!
	 @brief �Ͽ��ͻ�������
	*/
	virtual void DisConnect() = 0;
	/*!
	 @brief �õ����״̬
	 @return ���״̬
	 @note ״ֵ̬�ο�ͷ�ļ��еĺ궨��(0ʱΪ����״̬)
	*/
	virtual int GetStatus() = 0;
	/*!
	 @brief ��ȡ������Ϣ
	 @return ������Ϣ
	 @note ��GetStatus���ز�Ϊ0ʱ���Ե��øýӿڻ�ȡ������Ϣ,������Ϣ�ο�ͷ�ļ��еĺ궨��
	*/
	virtual int GetLastErr() = 0;
	/*!
	 @brief ��ȡ���ݿ�汾��Ϣ
	 @param nVer �汾��Ϣ
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	 @note �����ݿ�汾�����仯ʱ,�������ݿ����������Ϣ�����˸ı�
	*/
	virtual int GetDbVersion(int& nVer) = 0;
	/*!
	 @brief ��ȡ���ݿ�����Ϣ
	 @param lpRoot ���ݿ�ڵ�����(���ڵ�Ϊ"")
	 @param nType ���ݵ�����(0ȫ����Ϣ,1ȫ���ڵ���Ϣ,2���ڵ����Ϣ)
	 @param dbInfo ������Ϣ
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	 @note ��ȡ�Ľڵ���ϢΪxml������������:
	 @note <?xml version="1.0" encoding="GB2312"?>
	 @note <root>
	 @note  <dbgroup name="" longname=" " desc=" " typeid="">
	 @note   <dbtag name="" longname="" desc="" typeid="" vt="" handleid=""/>
	 @note  </dbgroup>
	 @note </root>
	 @note ���нڵ���ϢΪdbgroup,��������name����,longname������,desc����,typeid����ID,���ݵ���ϢΪdbtag,��������name����,longname������,desc����,typeid����ID,handleid��handle
	*/
	virtual int GetDbInfo(const char *lpRoot, int nType, SymLinkApiString& dbInfo) = 0;
	/*!
	 @brief ͨ����handle��ȡ���ݿ����Ϣ
	 @param nHandle ���ݿ��handle
	 @param tagInfo	������Ϣ
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	 @note ��ȡ�����ݵ���ϢΪxml������������:
	 @note <?xml version="1.0" encoding="GB2312"?>
	 @note <root name="" longname="" desc="" typeid="" vt="" handleid=""/>
	 @note ���а�������name����,longname������,desc����,typeid����ID,handleid��handle
	*/
	virtual int GetDbTagInfoByHandle(int nHandle, SymLinkApiString& tagInfo) = 0;
	/*!
	 @brief ͨ���㳤����ȡ���ݿ����Ϣ
	 @param lpName ���ݿ�㳤����
	 @param tagInfo	������Ϣ
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	 @note ��ȡ�����ݵ���ϢΪxml������������:
     @note <?xml version="1.0" encoding="GB2312"?>
     @note <root name="" longname="" desc="" typeid="" vt="" handleid=""/>
     @note ���а�������name����,longname������,desc����,typeid����ID,handleid��handle
	*/
	virtual int GetDbTagInfoByName(const char *lpName, SymLinkApiString& tagInfo) = 0;
	/*!
	 @brief ��ȡ���ݿ�㳤����
	 @param nHandle	���ݿ��handle
	 @param tagName	���ݵ㳤����
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	*/
	virtual int GetDbTagName(int nHandle, SymLinkApiString& tagName) = 0;
	/*!
	 @brief ��ȡ���ݿ��handle
	 @param lpName ���ݿ�㳤����
	 @param tagHandle ���ݵ�handle
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	*/
	virtual int GetDbTagHandle(const char *lpName, int& tagHandle) = 0;
	/*!
	 @brief ͨ����handle��ȡ���ݿ����ֵ
	 @param nHandle	���ݿ��handle
	 @param tagData	���ݵ�����
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	*/
	virtual int GetDbTagDataByHandle(int nHandle, SymLinkApiData& tagData) = 0;
	/*!
	 @brief ͨ���㳤����ȡ���ݿ����ֵ
	 @param lpName ���ݿ�㳤����
	 @param tagData ���ݵ�����
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	*/
	virtual int GetDbTagDataByName(const char *lpName, SymLinkApiData& tagData) = 0;
	/*!
	 @brief ��ȡ���ݱ仯�������
	 @param nCount ���ݸ���
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	 @note �ڲ���������СΪ�������2��,���������Сʱ�ᶪ�����ϵı仯����,�ӵ������ݱ仯��֪ͨ��,��Ҫ��ʱ��ȡ��ֹ���ݶ�ʧ
	*/
	virtual int GetDbTagChangeCount(int &nCount) = 0;
	/*!
	 @brief ��ȡ���ݱ仯��������
	 @param pHandleBuf �仯���ݵ����ݿ��handle
	 @param pDataBuf �仯����
	 @param nBufSize ǰ�����������ĸ���(��ʼֵΪ��������С,����ֵΪ��ȡ�����ݴ�С)
	 @param nHandle ָ�������ݿ��handle
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	 @note ��ȡ��������ʱ�����Ȼ�ȡ�������ĸ���Ȼ�󿪱���Ӧ�Ļ���ռ�,Ҳ�ɸ�����Ҫ���ٹ̶��Ļ�������ȡ(�������ٴ󻺴�һ�λ�ȡ��ʡ��������)
	*/
	virtual int GetDbTagChange(int *pHandleBuf, SymLinkApiData *pDataBuf, int& nBufSize, int nHandle = -1) = 0;
	/*!
	 @brief �������ݱ仯��������
	 @note ������仯��������ʱ���Ե��øú���ֱ������������,����GetDbTagChange�󻺴���Զ�����������ݲ����ٵ���ClearDbTagChange
	*/
	virtual void ClearDbTagChange() = 0;
	/*!
	 @brief ͨ���ݿ��handle�������ݿ������
	 @param nHandle �ݿ��handle
	 @param tagData	����
	 @param pResult	�������ݷ��ؽ��
	 @param pErrStr	�������ݷ�����Ϣ
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	*/
	virtual int SetDbTagDataByHandle(int nHandle, const SymLinkApiData& tagData, int* pResult = 0, SymLinkApiString *pErrStr = 0) = 0;
	/*!
	 @brief ͨ���ݿ�㳤�����������ݿ������
	 @param lpName �ݿ�㳤����
	 @param tagData	����
	 @param pResult	�������ݷ��ؽ��
	 @param pErrStr	�������ݷ�����Ϣ
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	*/
	virtual int SetDbTagDataByName(const char *lpName, const SymLinkApiData& tagData, int* pResult = 0, SymLinkApiString *pErrStr = 0) = 0;
	/*!
	 @brief ��ȡ���߻������
	 @param nCount ���ݸ���
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	 @note �������ݱ�����windows����ʱ�ļ���,Ϊ�˷�ֹ�ļ�����,��Ҫ��ʱ��ȡ����
	*/
	virtual int GetDbTagTxSaveCount(int &nCount) = 0;
	/*!
	 @brief ��ȡ���߻�������
	 @param pHandleBuf �������ݵ����ݿ��handle
	 @param pDataBuf ��������
	 @param nBufSize ǰ�����������ĸ���(��ʼֵΪ��������С,����ֵΪ��ȡ�����ݴ�С)
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	 @note ��ȡ��������ʱ�����Ȼ�ȡ�������ĸ���Ȼ�󿪱���Ӧ�Ļ���ռ�,Ҳ�ɸ�����Ҫ���ٹ̶��Ļ�������ȡ(�������ٴ󻺴�һ�λ�ȡ��ʡ��������)
	*/
	virtual int GetDbTagTxSave(int *pHandleBuf, SymLinkApiData *pDataBuf, int& nBufSize) = 0;
	/*!
	 @brief ������߻�������
	 @note ��������߻�������ʱ���Ե��øú���ֱ������������,����GetDbTagTxSave�󻺴���Զ�����������ݲ����ٵ���ClearDbTagTxSave
	*/
	virtual void ClearDbTagTxSave() = 0;

	/*!
	 @brief ͨ����Handle��ȡ���߻�������
	 @param tagHandle �������ݵ����ݿ��handle
	 @param startTime ��ȡ���ݵ���ʼʱ��
	 @param endTime ��ȡ���ݵĽ���ʱ��
	 @param pDataBuf ��������
	 @param nBufSize ǰ�����������ĸ���(��ʼֵΪ��������С,����ֵΪ��ȡ�����ݴ�С)
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	*/
	virtual int GetDbTagHistory(int tagHandle,time_t startTime,time_t endTime,SymLinkApiData* pDataBuf,int& nBufSize) = 0;
	/*!
	 @brief ͨ���㳤����ȡ���߻�������
	 @param lpTagName �������ݵ����ݿ�㳤��
	 @param startTime ��ȡ���ݵ���ʼʱ��
	 @param endTime ��ȡ���ݵĽ���ʱ��
	 @param pDataBuf ��������
	 @param nBufSize ǰ�����������ĸ���(��ʼֵΪ��������С,����ֵΪ��ȡ�����ݴ�С)
	 @return ����ִ�н��,�ο�ͷ�ļ��еĺ궨��
	*/
	virtual int GetDbTagHistory(const char* lpTagName,time_t startTime,time_t endTime,SymLinkApiData *pDataBuf,int& nBufSize) = 0;
	/*!
	 @brief ��ȡ��仯�������
	 @return �������
	 @note ����-1ʱ����ʹ��Ĭ�ϻ����С10000+2*�ܵ���
	*/
	virtual int GetChangeBufSize() = 0;
	/*!
	 @brief ���ñ��ĵȴ�ʱ��
	 @param nSize ʱ��(��λ:����)
	 @note ��СֵΪ1000��С��1000ʱʹ��Ĭ��ֵ�����С10000+2*�ܵ���
	*/
	virtual void SetChangeBufSize(int nSize) = 0;	

	//�������ݿ������,����Я��FOD/FOC�������� -Frank Added 2013.12.8
	virtual int SetDbTagDataByHandle2(int nHandle, const SymLinkApiData& tagData, int* pResult, SymLinkApiString *pErrStr,void* pReData,int& nReDataLen) = 0;
	virtual int SetDbTagDataByName2(const char *lpName, const SymLinkApiData& tagData, int* pResult, SymLinkApiString *pErrStr,void* pReData,int& nReDataLen) = 0;

	//SymLinkͨ���¼��ӿ� -Frank Added 2013.12.20
	virtual void SetSLEventChangeFunc(SLEVENT_CHANGE_FUNC hFunc) = 0;
	virtual int GetSLEventChangeCount(int &nCount) = 0;
	virtual int GetSLEventChange(SymLinkApiData *pDataBuf, int& nBufSize) = 0;
	virtual void ClearSLEventChange() = 0;
	//���ö�ʱ����,��λ:����,0-���Զ�ʱ
	virtual void SetTimeAdjust(int nMinutes) = 0;
	//����ÿһ�����ݴ���ĳ�ʱ����,����ڸ�ʱ�������ݴ�����,���ܻᶪ�����ֹ�������
	//��λ:����,��Ч����Ϊ:1-30�ڲ�Ĭ�ϲ���Ϊ5����;
	virtual void SetDealDataTimeout(int nMinutes) = 0;
	//���ÿͻ�������
	virtual void SetBrgClientKind(int nKind) = 0;
	//��ȡ���ݿ����ñ仯�ļ�����,<=0 δ��Ч
	virtual int GetDbConfigChangedCounter(int nFlag = 0) = 0;
	//�������ݽṹ����Ŀ¼,���������,�����Ĭ��·��
	virtual int SetCachePath(int nFlag,const char* sPath) = 0;
	//ȥ�����豸�ϻ�ȡ��ǩ������
	virtual int GetDbTagCacheBlob(const char *lpName,SymLinkApiData& tagData) = 0;

};

/*!
 @brief �½�CSymLinkApi����
 @param nType ��������(��ʱ��Ч,Ĭ��Ϊ0)
 @return CSymLinkApi����ָ��
*/
CSymLinkApi* CreateSymLinkApi(int nType);

/*!
 @brief ����CSymLinkApi����
 @param lpSymApi SymLinkApi����ָ��
*/
void FreeSymLinkApi(CSymLinkApi* lpSymApi);

#endif

#endif

