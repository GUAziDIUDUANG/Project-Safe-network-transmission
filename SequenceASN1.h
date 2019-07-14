#ifndef __02_SEQUENCEASN1_H__
#define __02_SEQUENCEASN1_H__
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
        Typename(const Typename&); \
        void operator=(const Typename&)
#include "BaseASN1.h"
#include "ItcastLog.h"

//对象化的ASN1操作类
class SequenceASN1 : public BaseASN1 {
public:
 //构造函数
SequenceASN1();
 //析构函数
 virtual ~SequenceASN1();

 //编码头结点
 int writeHeadNode(int iValue); //整型
 int writeHeadNode(char* sValue, int len); //字符串

 //编码普通节点
 int writeNextNode(int iValue); //整型
 int writeNextNode(char* sValue, int len);  //字符串
 
 //解码头结点
 int readHeadNode(int& iValue); //整型
 int readHeadNode(char* sValue);  //字符串

 //解码普通节点
 int readNextNode(int& iValue); //整型
 int readNextNode(char* sValue); //字符串

 //编码序列
 int packSequence(char** outData, int& outLen);
 //解码序列
 int unpackSequence(char* inData, int inLen);

 //释放序列
 void freeSequnce(ITCAST_ANYBUF* node = NULL);

 private:
  ITCAST_ANYBUF* m_header; //头节点
  ITCAST_ANYBUF* m_next; //尾节点
  ITCAST_ANYBUF* m_temp; //临时节点
  ItcastLog LogASN1;  //日志类

  //防止自动合成拷贝构造和重载赋值运算符
  DISALLOW_COPY_AND_ASSIGN(SequenceASN1);
};


#endif

