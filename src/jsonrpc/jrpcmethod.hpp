#ifndef JRPCMETHOD_HPP
#define JRPCMETHOD_HPP

#include "Arduino.h"
#include <ArduinoJson.h>
#include "jsonrpcconfig.hpp"

//======================
template<typename ARG_1>
ARG_1 deserializeArg(JsonVariant& paras, int index = 0){
  if (paras.is<JsonArray &>()) {
    JsonArray &array = paras;
    return paras[index].as<ARG_1>();
  } else if (paras.is<JsonObject &>()) {
    JsonObject &object = paras;
    return ARG_1();
  } else {
    return ARG_1();
  }
}//end deserializeArg

//======================
template<typename RET_TYPE>
JsonObject& serializeRet(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer, RET_TYPE ret){
  JsonObject &result = jsonOUTBuffer.createObject();
  result["answer"] = ret;
  return result;
}

//======================
//template<typename RET_TYPE, typename ARG_1>
//using method_t = RET_TYPE (*)(ARG_1);
template<typename RET_TYPE, typename ... Types>
using method_t = RET_TYPE (*)(Types ... args);

class JRPCMethod;

//======================
class JRPCMethod {
public:
  JRPCMethod(const char* nme);

  const char* name() const;

  virtual void deserialize(JsonVariant paras) = 0;
  //virtual void operator ()() = 0;
  //virtual void call() { this->operator()();}
  virtual void call_method()=0;
  virtual JsonObject& serialize(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer) = 0 ;

  JRPCMethod* next()const;
private:
  const char* _name;
  JRPCMethod* _next;
}; //end JRPCMethod

//======================
template<typename RET_TYPE,  typename ARG_1>
class JRPCMethod_R_1ARG : public JRPCMethod{
  public:
  JRPCMethod_R_1ARG(const char* nme, method_t<RET_TYPE, ARG_1> meth):JRPCMethod(nme),_method(meth){}

  virtual void deserialize(JsonVariant paras) override {_arg1 = deserializeArg<ARG_1>(paras, 0);}
  //virtual void operator ()() override {_ret = _method(_arg1);}
  virtual void call_method() override {
    _ret = _method(_arg1);
    //Serial.println(sayHello(_arg1));
  }
  virtual JsonObject& serialize(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer) override {return serializeRet(jsonOUTBuffer, _ret); }
private:
  RET_TYPE _ret;
  ARG_1 _arg1;
  const method_t<RET_TYPE, ARG_1> _method;
};// end JRPCMethod_R_1ARG

//======================
template<typename RET_TYPE,  typename ARG_1,  typename ARG_2>
class JRPCMethod_R_2ARG : public JRPCMethod{
  public:
  JRPCMethod_R_2ARG(const char* nme, method_t<RET_TYPE, ARG_1, ARG_2> meth):JRPCMethod(nme),_method(meth){}

  virtual void deserialize(JsonVariant paras) override {
    _arg1 = deserializeArg<ARG_1>(paras, 0);
    _arg2 = deserializeArg<ARG_2>(paras, 1);
  }
  //virtual void operator ()() override {_ret = _method(_arg1, _arg2);}
  virtual void call_method() override {_ret = _method(_arg1, _arg2);}
  virtual JsonObject& serialize(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer) override {return serializeRet(jsonOUTBuffer, _ret); }
private:
  RET_TYPE _ret;
  ARG_1 _arg1;
  ARG_2 _arg2;
  const method_t<RET_TYPE, ARG_1, ARG_2> _method;
};// end JRPCMethod_R_2ARG

//======================
template<typename RET_TYPE,  typename ARG_1,  typename ARG_2, typename ARG_3>
class JRPCMethod_R_3ARG : public JRPCMethod{
  public:
  JRPCMethod_R_3ARG(const char* nme, method_t<RET_TYPE, ARG_1, ARG_2, ARG_3> meth):JRPCMethod(nme),_method(meth){}

  virtual void deserialize(JsonVariant paras) override {
    _arg1 = deserializeArg<ARG_1>(paras, 0);
    _arg2 = deserializeArg<ARG_2>(paras, 1);
    _arg3 = deserializeArg<ARG_3>(paras, 2);
  }
  //virtual void operator ()() override {_ret = _method(_arg1, _arg2, _arg3);}
  virtual void call_method() override {_ret = _method(_arg1, _arg2, _arg3);}
  virtual JsonObject& serialize(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer) override {return serializeRet(jsonOUTBuffer, _ret); }
private:
  RET_TYPE _ret;
  ARG_1 _arg1;
  ARG_2 _arg2;
  ARG_3 _arg3;
  const method_t<RET_TYPE, ARG_1, ARG_2, ARG_3> _method;
};// end JRPCMethod_R_3ARG

//======================
template<typename RET_TYPE,  typename ARG_1,  typename ARG_2, typename ARG_3, typename ARG_4>
class JRPCMethod_R_4ARG : public JRPCMethod{
  public:
  JRPCMethod_R_4ARG(const char* nme, method_t<RET_TYPE, ARG_1, ARG_2, ARG_3, ARG_4> meth):JRPCMethod(nme),_method(meth){}

  virtual void deserialize(JsonVariant paras) override {
    _arg1 = deserializeArg<ARG_1>(paras, 0);
    _arg2 = deserializeArg<ARG_2>(paras, 1);
    _arg3 = deserializeArg<ARG_3>(paras, 2);
    _arg4 = deserializeArg<ARG_4>(paras, 3);
  }
  //virtual void operator ()() override {_ret = _method(_arg1, _arg2, _arg3, _arg4);}
  virtual void call_method() override {_ret = _method(_arg1, _arg2, _arg3, _arg4);}
  virtual JsonObject& serialize(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer) override {return serializeRet(jsonOUTBuffer, _ret); }
private:
  RET_TYPE _ret;
  ARG_1 _arg1;
  ARG_2 _arg2;
  ARG_3 _arg3;
  ARG_4 _arg4;
  const method_t<RET_TYPE, ARG_1, ARG_2, ARG_3, ARG_4> _method;
};// end JRPCMethod_R_4ARG

//======================
template<typename RET_TYPE,  typename ARG_1,  typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5>
class JRPCMethod_R_5ARG : public JRPCMethod{
  public:
  JRPCMethod_R_5ARG(const char* nme, method_t<RET_TYPE, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5> meth):JRPCMethod(nme),_method(meth){}

  virtual void deserialize(JsonVariant paras) override {
    _arg1 = deserializeArg<ARG_1>(paras, 0);
    _arg2 = deserializeArg<ARG_2>(paras, 1);
    _arg3 = deserializeArg<ARG_3>(paras, 2);
    _arg4 = deserializeArg<ARG_4>(paras, 3);
    _arg5 = deserializeArg<ARG_5>(paras, 4);
  }
  //virtual void operator ()() override {_ret = _method(_arg1, _arg2, _arg3, _arg4, _arg5);}
  virtual void call_method() override {_ret = _method(_arg1, _arg2, _arg3, _arg4, _arg5);}
  virtual JsonObject& serialize(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer) override {return serializeRet(jsonOUTBuffer, _ret); }
private:
  RET_TYPE _ret;
  ARG_1 _arg1;
  ARG_2 _arg2;
  ARG_3 _arg3;
  ARG_4 _arg4;
  ARG_5 _arg5;
  const method_t<RET_TYPE, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5> _method;
};// end JRPCMethod_R_4ARG

// some preprocessor magic to count the number of arguments
#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1)
//#define DECLARE_JSON_STUB_IMPL2(METHOD, RET_TYPE, count, ...) DECLARE_JSON_STUB ## count (METHOD, RET_TYPE, __VA_ARGS__)
#define DECLARE_JSON_STUB_IMPL(METHOD, RET_TYPE, count, ...) DECLARE_JSON_STUB_IMPL2(METHOD, RET_TYPE, count, __VA_ARGS__)
#define DECLARE_JSON_STUB(METHOD, RET_TYPE, ...) DECLARE_JSON_STUB_IMPL(METHOD, RET_TYPE, VA_NARGS(__VA_ARGS__), __VA_ARGS__)
// some preprocessor magic to count the number of arguments

#define DECLARE_JSON_STUB_IMPL2(METHOD, RET_TYPE, count, ...) \
    using stub_##METHOD = JRPCMethod_R_ ## count ## ARG<RET_TYPE, __VA_ARGS__>; \
    static stub_##METHOD instance_stub_##METHOD(#METHOD, METHOD);


#endif // JRPCMETHOD_HPP
