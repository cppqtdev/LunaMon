#ifndef MQTT_CONNECT_ACK_MESSAGE_H
#define MQTT_CONNECT_ACK_MESSAGE_H

#include "MQTTConnection.h"

#define MQTT_CONNACK_ACCEPTED                     0x00
#define MQTT_CONNACK_REFUSED_PROTOCOL_VERSION     0x01
#define MQTT_CONNACK_REFUSED_IDENTIFIER_REJECTED  0x02
#define MQTT_CONNACK_REFUSED_SERVER_UNAVAILABLE   0x03
#define MQTT_CONNACK_REFUSED_USERNAME_OR_PASSWORD 0x04
#define MQTT_CONNACK_REFUSED_NOT_AUTHORIZED       0x05

struct MQTTConnectAckVariableHeader {
  uint8_t flags;
  uint8_t returnCode;
};

#define MQTT_CONNACK_SESSION_PRESENT_MASK 0x01

bool sendMQTTConnectAckMessage(MQTTConnection *connection, bool sessionPresent, uint8_t errorCode);

#endif