#ifndef __FACTORYCODEC_H__
#define __FACTORYCODEC_H__
#include "Codec.h"

class FactoryCodec {
 public:
  FactoryCodec();
	virtual ~FactoryCodec();

	//负责创建对应类的函数
	virtual Codec* createCodec(void* arg = NULL);
};


#endif
