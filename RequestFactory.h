#ifndef __REQUESTFACTORY_H__
#define __REQUESTFACTORY_H__
#include "RequestCodec.h"
#include "FactoryCodec.h"

class RequestFactory : public FactoryCodec {
 RequestFactory();
 ~RequestFactory();

 public:
	Codec* createCodec(void* arg = NULL) override;
};

#endif
