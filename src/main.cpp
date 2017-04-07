#include "Arduino.h"
#include "ethernet/eth.hpp"
#include "jsonrpc/jsonrpc.hpp"
#include "jsonrpc/jrpcmethod.hpp"

//const char *sayHello(const char *name);
//DECLARE_JSON_STUB(sayHello, const char *, const char *)

// #define BUF_SZ 20
// char res_buff[BUF_SZ];
// const char * sayHello(const char *name){
//     memset(res_buff, 0, BUF_SZ);
//     const char *s1 = "Hello ";
//     size_t len1 = strlen(s1);
//     size_t len2 = strlen(name);
//     if ((len1 + len2 + 1) > BUF_SZ) {
//      return res_buff;
//     }
//     //const char *result = (const char *)(malloc(len1+len2+1));//+1 for the zero-terminator in real code you would check for errors in malloc here
//     memcpy(res_buff, s1, len1);
//     memcpy(res_buff + len1, name, len2 + 1); //+1 to copy the null-terminator
//     return res_buff;
// }
// DECLARE_JSON_STUB(sayHello, const char *, const char *)

String sayHello(String name){
    String ret("Hello ");
    ret.concat(name);
    return ret;
}
DECLARE_JSON_STUB(sayHello, String, String)



// int increment(int val){return val+1;}
// DECLARE_JSON_STUB(increment, int, int)

void setup() {
  //setup_jsonrpc(2);
  // REGISTER_JSON_STUB(sayHello)
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // while (!Serial) {
  //        ; // wait for serial port to connect. Needed for Leonardo only
  //}
  eETHInit();
  // eMBInit();

  //String tmp = sayHello("World");
  //Serial.println(tmp);

}

void loop() {
  // eMBPoll();
  eETHPoll();
}

//#define BUF_SZ 20
//char res_buff[BUF_SZ];
//volatile char res_buff[BUF_SZ];
//static char res_buff[BUF_SZ];
//const char *sayHello(const char *s2) {
// String sayHello(const char *s2) {
//   Serial.print("calling sayHello(");
//   Serial.print(s2);
//   Serial.println(")");
//
//   //memset(res_buff, 0, BUF_SZ);
//   //const char *s1 = "Hello ";
//   //size_t len1 = strlen(s1);
//   //size_t len2 = strlen(s2);
//   //if ((len1 + len2 + 1) > BUF_SZ) {
//   //  return res_buff;
//   //}
//   // const char *result = (const char *)(malloc(len1+len2+1));//+1 for the
//   // zero-terminator
//   // in real code you would check for errors in malloc here
//   //memcpy(res_buff, s1, len1);
//   //memcpy(res_buff + len1, s2, len2 + 1); //+1 to copy the null-terminator
//   //return res_buff;
//
//   String ret("Hello ");
//   ret += String(s2);
//   return ret;
// }
//DECLARE_JSON_STUB(sayHello, String, const char *)
