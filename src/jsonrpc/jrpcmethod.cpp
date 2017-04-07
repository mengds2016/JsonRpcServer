#include "jrpcmethod.hpp"
#include "jrpcmethodlist.hpp"

///======================================
template <> const char *deserializeArg(JsonVariant &paras, int index) {
  if (paras.is<JsonArray &>()) {
    JsonArray &array = paras;
    return array[index].as<char*>();
  } else if (paras.is<JsonObject &>()) {
    //JsonObject &object = paras;
    //return paras[index].as<char*>();
    return NULL;
  } else {
    return NULL;
  }
}
///======================================
// template <>
// JsonObject & serializeRet(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer, const char *ret)
// {
//   //Serial.println("serializeRet");
//   JsonObject &result = jsonOUTBuffer.createObject();
//   result["answer"] = ret;
//   return result;
// }

// template <>
// JsonObject & serializeRet(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer, String ret)
// {
//   Serial.print("serializeRet ");
//   Serial.println(ret);
//   JsonObject &result = jsonOUTBuffer.createObject();
//   result["answer"] = ret;
//   return result;
// }

// template <>
// JsonObject & serializeRet(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer, int ret)
// {
//   JsonObject &result = jsonOUTBuffer.createObject();
//   result["answer"] = ret;
//   return result;
// }

JRPCMethod::JRPCMethod(const char* nme):
  _name(nme)
{
  _next = JRPCMethodList::_methlist;
  JRPCMethodList::_methlist = this;
}

const char* JRPCMethod::name() const{
  return _name;
}

JRPCMethod* JRPCMethod::next()const {
  return _next;
}
