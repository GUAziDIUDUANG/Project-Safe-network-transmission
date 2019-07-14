#ifndef __02_CODEC_H__
#define __02_CODEC_H__
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
        Typename(const Typename&); \
        void operator=(const Typename&)
#include "SequenceASN1.h"

//工厂模式基类
class Codec : public SequenceASN1 {
 public:
  //构造函数
  Codec();
  //析构函数
  ~Codec();

  //编码(虚函数)
  virtual int msgEncode(char** outData, int& len);
  //解码(虚函数)
  virtual int msgDecode(char* inData, int inLen);
  //内存释放(虚函数)
  virtual int msgMemFree(void** point);

 private:
  //防止自动生成拷贝构造和重载复制运算符
  DISALLOW_COPY_AND_ASSIGN(Codec);
};

#endif
