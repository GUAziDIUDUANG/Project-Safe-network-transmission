#include "RespondCodec.h"

//构造
RespondCodec::RespondCodec() {

  mRespondMsg = new RespondMsg;
  memset(mRespondMsg, 0, sizeof(mRespondMsg));
}

RespondCodec::RespondCodec(RespondMsg* msg) {

  mRespondMsg = new RespondMsg;
  memset(mRespondMsg, 0, sizeof(mRespondMsg));
  memcpy(mRespondMsg, msg, sizeof(msg));
}

//析构
RespondCodec::~RespondCodec() {

  delete mRespondMsg;
}

//编码
int RespondCodec::msgEncode(char** outData, int& len) {
  //编码报文类型(int)
  int retval = writeHeadNode(mRespondMsg->rv);
  if (0 != retval) {
    printf("encode mRespondMsg->rv failed...\n");
    return 25;
  }

  //编码客户端编号(char[])
  retval = writeNextNode(mRespondMsg->clientId, 
                         strlen(mRespondMsg->clientId));

  if (0 != retval) {
    printf("encode mRespondMsg->clientId failed...\n");
    return 26;
  }
  //编码认证码(char[])
  retval = writeNextNode(mRespondMsg->serverId, 
                          strlen(mRespondMsg->serverId));

  if (0 != retval) {
    printf("encode mRespondMsg->serverId failed...\n");
    return 27;
  }
  //编码服务端编号(char[])
  retval = writeNextNode(mRespondMsg->r2, 
                          strlen(mRespondMsg->r2));

  if (0 != retval) {
    printf("encode mRespondMsg->r2 failed...\n");
    return 28;
  }
  //编码客户端随机数(char[])
  retval = writeNextNode(mRespondMsg->seckeyid);

  if (0 != retval) {
    printf("encode mRespondMsg->seckeyid failed...\n");
    return 29;
  }
  //编码序列
  retval = packSequence(outData, len);

  if (0 != retval) {
    printf("packSequence failed...\n");
    return 30;
  }
  //释放内存
  freeSequnce();

  return 0;
}

//解码
int RespondCodec::msgDecode(char* inData, int inLen) {
  
  //参数检查
  if (NULL == inData || inLen <= 0) {
    printf("msgDecode: the parameter is invalid...\n");
    return 31;
  }

  //解码序列
  int retval = unpackSequence(inData, inLen);
  if (0 != retval) {
    printf("unpackSequence failed...\n");
    return 32;
  }

  //编码报文类型
  retval = readHeadNode(mRespondMsg->rv);
  if (0 != retval) {
    printf("decode rv failed...\n");
    return 33;
  }

  //编码客户端编号
  retval = readNextNode(mRespondMsg->clientId);
  if (0 != retval) {
    printf("decode clientId failed...\n");
    return 34;
  }

  //编码认证码
  retval = readNextNode(mRespondMsg->serverId);
  if (0 != retval) {
    printf("decode serverId failed...\n");
    return 35;
  }


  //编码服务端编号
  retval = readNextNode(mRespondMsg->r2);
  if (0 != retval) {
    printf("decode r2 failed...\n");
    return 36;
  }

  //编码客户端随机数
  retval = readHeadNode(mRespondMsg->seckeyid);
  if (0 != retval) {
    printf("decode seckeyid failed...\n");
    return 37;
  }

  //释放内存
  freeSequnce();

  return 0;
}

//释放内存报文请求结构体
int RespondCodec::msgMemFree(void** point) {
  if (NULL == point) {
    return 38;
  }
  else {
    delete *point;
    *point = NULL;
  }

  return 0;
}
