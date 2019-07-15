#ifndef __RESPONDFACTORY_H__
#define __RESPONDFACTORY_H__
#include "RespondCodec.h"
#include "FactoryCodec.h"

class RespondFactory : public FactoryCodec {
 public:
	RespondFactory();
	~RespondFactory();

	//负责创建对应类的函数
	Codec* createCodec(void* arg = NULL) override;
};


#endif
