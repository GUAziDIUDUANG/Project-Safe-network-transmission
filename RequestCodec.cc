#include "RequestCodec.h"

//构造
RequestCodec::RequestCodec() {

  mRequestMsg = new RequestMsg;
  memset(mRequestMsg, 0, sizeof(mRequestMsg));
}

RequestCodec::RequestCodec(RequestMsg* msg) {

  mRequestMsg = new RequestMsg;
  memset(mRequestMsg, 0, sizeof(mRequestMsg));
  memcpy(mRequestMsg, msg, sizeof(msg));
}

//析构
RequestCodec::~RequestCodec() {

  delete mRequestMsg;
}

//编码
int RequestCodec::msgEncode(char** outData, int& len) {
  //编码报文类型(int)
  int retval = writeHeadNode(mRequestMsg->cmdType);
  if (0 != retval) {
    printf("encode mRequestMsg->cmdType failed...\n");
    return 25;
  }

  //编码客户端编号(char[])
  retval = writeNextNode(mRequestMsg->clientId, 
                         strlen(mRequestMsg->clientId));

  if (0 != retval) {
    printf("encode mRequestMsg->clientId failed...\n");
    return 26;
  }
  //编码认证码(char[])
  retval = writeNextNode(mRequestMsg->authCode, 
                          strlen(mRequestMsg->authCode));

  if (0 != retval) {
    printf("encode mRequestMsg->authCode failed...\n");
    return 27;
  }
  //编码服务端编号(char[])
  retval = writeNextNode(mRequestMsg->serverId, 
                          strlen(mRequestMsg->serverId));

  if (0 != retval) {
    printf("encode mRequestMsg->serverId failed...\n");
    return 28;
  }
  //编码客户端随机数(char[])
  retval = writeNextNode(mRequestMsg->r1, 
                          strlen(mRequestMsg->r1));

  if (0 != retval) {
    printf("encode mRequestMsg->r1 failed...\n");
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
int RequestCodec::msgDecode(char* inData, int inLen) {
  
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
  retval = readHeadNode(mRequestMsg->cmdType);
  if (0 != retval) {
    printf("decode cmdType failed...\n");
    return 33;
  }

  //编码客户端编号
  retval = readNextNode(mRequestMsg->clientId);
  if (0 != retval) {
    printf("decode clientId failed...\n");
    return 34;
  }

  //编码认证码
  retval = readNextNode(mRequestMsg->authCode);
  if (0 != retval) {
    printf("decode authCode failed...\n");
    return 35;
  }


  //编码服务端编号
  retval = readNextNode(mRequestMsg->serverId);
  if (0 != retval) {
    printf("decode serverId failed...\n");
    return 36;
  }

  //编码客户端随机数
  retval = readHeadNode(mRequestMsg->r1);
  if (0 != retval) {
    printf("decode r1 failed...\n");
    return 37;
  }

  //释放内存
  freeSequnce();

  return 0;
}

//释放内存报文请求结构体
int RequestCodec::msgMemFree(void** point) {
  if (NULL == point) {
    return 38;
  }
  else {
    delete *point;
    *point = NULL;
  }

  return 0;
}
