#ifndef JSONRPCCONFIG_HPP
#define JSONRPCCONFIG_HPP


// calculate buffers with https://bblanchon.github.io/ArduinoJson/assistant/
#define INPUT_BUFFER_SIZE 200 // JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 70; 118 + 70
#define TRANS_BUFFER_SIZE 20
#define OUTPUT_BUFFER_SIZE 150 // JSON_OBJECT_SIZE(3) + 30; 76 + 70 = 146

#endif // JSONRPCCONFIG_HPP
