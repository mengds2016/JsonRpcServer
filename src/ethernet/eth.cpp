#include "eth.hpp"
#include "ethconfig.hpp"

#include <jsonrpc/jsonrpc.hpp>

#include "Arduino.h"
#include <UIPEthernet.h>

// EthernetClient clients[NBR_ETH_CLIENTS];
EthernetServer tcpserver(SERVER_PORT);

void eETHInit() {
  const uint8_t mac[] = {MAC_ADDRESS};
  IPAddress ip(IP_ADDRESS);
  IPAddress gateway(GATEWAY);
  IPAddress subnet(SUBNETMASK);

  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);
  // Ethernet.begin(mac, IPAddress(IP_ADDRESS), IPAddress(GATEWAY),
  // IPAddress(SUBNETMASK));
  // start listening for clients
  tcpserver.begin();

  Serial.print("TCP Server address:");
  Serial.println(Ethernet.localIP());
} // end eETHInit

///======================================
void eETHPollEcho() {
  size_t size;

  if (EthernetClient client = tcpserver.available()) {
    if (client) {
      while ((size = client.available()) > 0) {
        uint8_t *msg = (uint8_t *)malloc(size);
        size = client.read(msg, size);
        Serial.write(msg, size);
        client.write(msg, size);
        // free(msg);
      }
    }
  }
} // end eETHPollEcho

///======================================
void eETHPoll() {
  size_t size;
  if (EthernetClient client = tcpserver.available()) {
    if (client) {
      client.setTimeout(200);
      if ((size = client.available()) > 0) {
        uint8_t *msg = (uint8_t *)malloc(size);
        size = client.read(msg, size);
        // Serial.write(msg,size);
        // client.write(msg,size);
        parseJsonRPC((char *)(msg), client);
        free(msg);
      }
      // sendError(client, JRPC_ERR_PARSEERROR);
    }
  }
} // end eETHPoll
