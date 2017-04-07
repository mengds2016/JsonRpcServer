#include "jrpcmethod.hpp"
#include "jrpcmethodlist.hpp"
#include "jsonrpc.hpp"

#include <ArduinoJson.h>

// It's better to use a char[] as shown here.
// If you use a const char* or a String, ArduinoJson will
// have to make a copy of the input in the JsonBuffer.
char JRPC_VER[] = "2.0";

char STR_NULL[] = "null";

char STR_JSONRPC[] = "jsonrpc";
char STR_ID[] = "id";
char STR_METHOD[] = "method";
char STR_PARAMS[] = "params";
char STR_ERROR[] = "error";
char STR_CODE[] = "code";
char STR_MESSAGE[] = "message";
char STR_RESULT[] = "result";

char STR_ERR_32000[] = "unkown";
char STR_ERR_32700[] = "Parse error";
char STR_ERR_32600[] = "Invalid Request";
char STR_ERR_32601[] = "Method not found";
char STR_ERR_32602[] = "Invalid params";
char STR_ERR_32603[] = "Internal error";

#define JRPC_ERR_NOERR 0x0
#define JRPC_ERR 0xFD00 //-32000

//-32000 (0x0) to -32099 (0x63)Server error   Reserved for
// implementation-defined server-errors.
#define JRPC_ERR_GENERIC (0x0 + JRPC_ERR) //-32000

// The error codes from and including -32768 to -32000 are reserved for
// pre-defined errors.
#define JRPC_ERR_PARSEERROR (0x2BC + JRPC_ERR)     //-32700
#define JRPC_ERR_INVALIDREQUEST (0x258 + JRPC_ERR) //-32600
#define JRPC_ERR_METHODNOTFOUND (0x259 + JRPC_ERR) //-32601
#define JRPC_ERR_INVALIDPARAMS (0x25A + JRPC_ERR)  //-32602
#define JRPC_ERR_INTERNALERR (0x25B + JRPC_ERR)    //-32603

///======================================
// "private" functions
void sendResult(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer,
                Print &_ostream, JsonObject &result, int id);
void sendError(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer,
               Print &_ostream, int16_t code);
void sendError(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer,
               Print &_ostream, int16_t code, char message[]);

///======================================

///======================================
void parseJsonRPC(char message[], Print &_ostream) {

  int id = 0;

  bool parse_ok = false;

  JRPCMethod *method = JRPCMethodList::end();

  {
    StaticJsonBuffer<INPUT_BUFFER_SIZE> jsonINBuffer;
    JsonObject &root = jsonINBuffer.parseObject(message);

    parse_ok = root.success();

    char *method_name = NULL;
    if (parse_ok) {

      method_name = root[STR_METHOD];
      //JsonObject &params = root[STR_PARAMS];
      id = root[STR_ID].as<int>();

      if (method_name != NULL) {
        // find method
        //Serial.print(method_name);
        if (JRPCMethodList::empty() == false) {

          for (JRPCMethod *it = JRPCMethodList::begin(); it != JRPCMethodList::end(); it = it->next()) {
            if (strcmp(it->name(), method_name) == 0) {
              method = it;
              // method_found = true;
              // call deserialize_params
              it->deserialize(root[STR_PARAMS]);
              break;
            }
          }
        }
      }
    }
    free(message);
  }

  if (method != JRPCMethodList::end()) { // method was found
    method->call_method();
  }

  {
    StaticJsonBuffer<OUTPUT_BUFFER_SIZE> jsonOUTBuffer;
    if (parse_ok == false) { // check if parsing input was ok
      Serial.print("parse error\n");
      sendError(jsonOUTBuffer, _ostream, JRPC_ERR_PARSEERROR);
    }

    if (method == JRPCMethodList::end()) { // method not found
      Serial.print("method was NOT found\n");
      sendError(jsonOUTBuffer, _ostream, JRPC_ERR_METHODNOTFOUND);
    }

    // method->serialize(jsonOUTBuffer);
    //JsonObject &result = jsonOUTBuffer.createObject();
    //result["answer"] = "Yea";

    JsonObject &result = method->serialize(jsonOUTBuffer);

    bool call_success = true;
    if (call_success) {
       sendResult(jsonOUTBuffer, _ostream, result, id);
    }
  }

} // end parse

///======================================
void sendError(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer,
               Print &_ostream, int16_t code) {
  switch (code) {
  case JRPC_ERR_PARSEERROR: {
    sendError(jsonOUTBuffer, _ostream, code, STR_ERR_32700);
    break;
  }
  case JRPC_ERR_INVALIDREQUEST: {
    sendError(jsonOUTBuffer, _ostream, code, STR_ERR_32600);
    break;
  }
  case JRPC_ERR_METHODNOTFOUND: {
    sendError(jsonOUTBuffer, _ostream, code, STR_ERR_32601);
    break;
  }
  case JRPC_ERR_INVALIDPARAMS: {
    sendError(jsonOUTBuffer, _ostream, code, STR_ERR_32602);
    break;
  }
  case JRPC_ERR_INTERNALERR: {
    sendError(jsonOUTBuffer, _ostream, code, STR_ERR_32603);
    break;
  }
  default: {
    sendError(jsonOUTBuffer, _ostream, code, STR_ERR_32000);
    break;
  }
  }
} // end sendError

///======================================
//  //{"jsonrpc": "2.0", "error": {"code": <CODE>, "message": <MESSAGE>}, "id":
//  null}
void sendError(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer,
               Print &_ostream, int16_t code, char message[]) {
  JsonObject &root = jsonOUTBuffer.createObject();
  root[STR_JSONRPC] = JRPC_VER;
  JsonObject &error = root.createNestedObject(STR_ERROR);
  error[STR_CODE] = code;
  error[STR_MESSAGE] = message;
  root[STR_ID] = (char *)0; // or (char*)NULL if you prefer
  root.printTo(_ostream);

} // end sendError

///======================================
////<-- {"jsonrpc": "2.0", "result": 19, "id": 1}
void sendResult(StaticJsonBuffer<OUTPUT_BUFFER_SIZE> &jsonOUTBuffer,
                Print &_ostream, JsonObject &result, int id) {

  JsonObject &root = jsonOUTBuffer.createObject();
  root[STR_JSONRPC] = JRPC_VER;
  root[STR_RESULT] = result;
  root[STR_ID] = id;
  root.printTo(_ostream);
} // end sendResult
