#ifndef JRPCMETHODLIST_HPP
#define JRPCMETHODLIST_HPP

class JRPCMethod;

//======================
class JRPCMethodList{
    friend class JRPCMethod;
public:
  
  static JRPCMethod* begin();

  static JRPCMethod* end();

  static bool empty();

private:
  static JRPCMethod* _methlist;
}; //end JRPCMethodList

#endif // JRPCMETHODLIST_HPP
