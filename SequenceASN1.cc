#include "SequenceASN1.h"

 //构造函数
SequenceASN1::SequenceASN1() 
  : m_header(NULL),m_next(NULL),m_temp(NULL) {}

 //析构函数
SequenceASN1::~SequenceASN1() {

}

 //编码头结点 //整型
int SequenceASN1::writeHeadNode(int iValue) {

  //参数判断
  if (NULL == iValue) {
    printf("writeHeadNode-int: the parameter in invalid...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 3, 
                 "writeHeadNode-int: the parameter in invalid...\n");
    return 3;
  }

  int retval = DER_ItAsn1_WriteInteger(static_cast<ITCAST_UINT32>(iValue),
                                       &m_header);
  if (0 != retval) {
    printf("writeHeadNode-int failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 11, 
                 "writeHeadNode-int failed...\n");
    return 11;
  }

  m_next = m_header->next;

  return 0;
}

 
 //编码头结点 //字符串
int SequenceASN1::writeHeadNode(char* sValue, int len) {

  //参数判断
  if (NULL == sValue || len <= 0) {
    printf("writeHeadNode-char: the parameter is invalid...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 4, 
                 "writeHeadNode-char: the parameter is invalid...\n");
    return 4;
  }

  int retval = EncodeChar(sValue, len, &m_header);
  if (0 != retval) {
    printf("writeHeadNode-char failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 12, 
                 "writeHeadNode-char failed...\n");
    return 12;
  }

  m_next = m_header->next;

  return 0;
}

 //编码普通节点//整型
int SequenceASN1::writeNextNode(int iValue) {

  //参数判断
  if (NULL == iValue) {
    printf("writeNextNode-int: the parameter in invalid...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 3, 
                 "writeNextNode-int: the parameter in invalid...\n");
    return 3;
  }

  int retval = DER_ItAsn1_WriteInteger(static_cast<ITCAST_UINT32>(iValue), 
                                       &m_next);
  if (0 != retval) {
    printf("writeNextNode-int failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 13, 
                 "writeNextNode-int failed...\n");
    return 13;
  }

  m_next = m_next->next;

  return 0;

}

 //编码普通节点//字符串
int SequenceASN1::writeNextNode(char* sValue, int len) {

  //参数判断
  if (NULL == sValue || len <= 0) {
    printf("writeNextNode-char: the parameter is invalid...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 4, 
                 "writeNextNode-char: the parameter is invalid...\n");
    return 4;
  }

  int retval = EncodeChar(sValue, len, &m_next);
  if (0 != retval) {
    printf("writeNextNode-char failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 14, 
                 "writeNextNode-char failed...\n");
    return 14;
  }

  m_next = m_next->next;

  return 0;

}
 
 //解码头结点//整型
int SequenceASN1::readHeadNode(int& iValue) {

  //头结点判断
  if (NULL == m_header) {
    printf("m_header == NULL\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 50, 
                 "m_header == NULL\n");
    return 50;
  }

  ITCAST_UINT32 temp = -1;
  int retval = DER_ItAsn1_ReadInteger(m_header, &temp);
  iValue = static_cast<int>(temp);

  if (0 != retval) {
    printf("readHeadNode-int failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 15, 
                 "readHeadNode-int failed...\n");
    return 15;
  }

  m_next = m_header->next;
  return 0;
}

 //解码头结点//字符串
int SequenceASN1::readHeadNode(char* sValue) {

  //头结点判断
  if (NULL == m_header) {
    printf("m_header == NULL\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 50, 
                 "m_header == NULL\n");
    return 50;
  }

  int retval = DecodeChar(m_header, &sValue, NULL);//bug
  if (0 != retval) {
    printf("readHeadNode-cahr failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 16, 
                 "readHeadNode-cahr failed...\n");
    return 16;
  }

  m_next = m_header->next;
  return 0;
}

 //解码普通节点//整型
int SequenceASN1::readNextNode(int& iValue) {

  //节点判断
  if (NULL == m_next) {
    printf("m_next == NULL\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 51, 
                 "m_next == NULL\n");
    return 51;
  }

  ITCAST_UINT32 temp = -1;
  int retval = DER_ItAsn1_ReadInteger(m_header, &temp);
  iValue = static_cast<int>(temp);

  if (0 != retval) {
    printf("readHeadNode-int failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 17, 
                 "readHeadNode-int failed...\n");
    return 17;
  }

  m_next = m_next->next;
  return 0;
}

 //解码普通节点//字符串
int SequenceASN1::readNextNode(char* sValue) {

  //节点判断
  if (NULL == m_next) {
    printf("m_next == NULL\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 51, 
                 "m_next == NULL\n");
    return 51;
  }

  int retval = DecodeChar(m_next, &sValue, NULL);//bug
  if (0 != retval) {
    printf("readHeadNode-int failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 18, 
                 "readHeadNode-int failed...\n");
    return 18;
  }

  m_next = m_next->next;
  return 0;
}

 //编码序列
int SequenceASN1::packSequence(char** outData, int& outLen) {

  ITCAST_ANYBUF* tmp_anybuf = NULL;
  int retval = DER_ItAsn1_WriteSequence(m_header, &tmp_anybuf);
  if (0 != retval) {
    printf("packSequence failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 20, 
                 "packSequence failed...\n");
    return 20;
  }

  //传出数据
  *outData = static_cast<char*>(malloc(tmp_anybuf->dataLen + 1));
  if (NULL == *outData) {
    printf("malloc failed..\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 21, 
                 "malloc failed...\n");
    return 21;
  }

  memset(*outData, 0, tmp_anybuf->dataLen + 1);
  memcpy(*outData, tmp_anybuf->pData, tmp_anybuf->dataLen);
  outLen = tmp_anybuf->dataLen;

  //释放内存
  free(tmp_anybuf);
  tmp_anybuf == NULL;
  this->freeSequnce(m_header);

  return 0;
}


 //解码序列
int SequenceASN1::unpackSequence(char* inData, int inLen) {
  
  //参数检查
  if (NULL == inData || inLen <= 0) {
    printf("unpackSequence: the parameter is invalid...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 22, 
                 "unpackSequence: the parameter is invalid...\n");
    return 22;
  }

  // 解码
  int retval = DER_ITCAST_String_To_AnyBuf(&m_temp, 
                                             reinterpret_cast<unsigned char*>(inData),
                                             inLen);

  if (0 != retval) {
    printf("string to ANUBUF failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 23, 
                 "string to ANUBUF failed...\n");
    return 23;
  }

  retval = DER_ItAsn1_ReadSequence(m_temp, &m_header);
  if (0 != retval) {
    printf("unpackSequence failed...\n");
    LogASN1.Log(__FILE__, 
                 __LINE__, 
                 ItcastLog::ERROR, 
                 24, 
                 "unpackSequence failed...\n");
    return 24;
  }

  //释放内存
  free(m_temp);
  m_temp = NULL;
  return 0;
}

 //释放序列
void SequenceASN1::freeSequnce(ITCAST_ANYBUF* node) {
  
  if (NULL == node) {
   DER_ITCAST_FreeQueue(m_header);
  }
  else {
    DER_ITCAST_FreeQueue(node);
  }
    m_header = NULL;
    m_next = NULL;
    m_temp = NULL;
}



