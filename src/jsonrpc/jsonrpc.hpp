#ifndef JSONRPC_HPP
#define JSONRPC_HPP

#include "Arduino.h"
#include <ArduinoJson.h>
#include "jsonrpcconfig.hpp"

void parseJsonRPC(char message[], Print &_ostream);

#endif // JSONRPC_HPP
