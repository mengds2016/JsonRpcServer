#include "jrpcmethodlist.hpp"
#include "jrpcmethod.hpp"

#define JRPC_METHOD_LIST_END nullptr

JRPCMethod* JRPCMethodList::_methlist = JRPC_METHOD_LIST_END;

JRPCMethod* JRPCMethodList::begin() {
  return _methlist;
}

JRPCMethod* JRPCMethodList::end() {
  return JRPC_METHOD_LIST_END;
}

bool JRPCMethodList::empty() {
  return _methlist == end();
}
