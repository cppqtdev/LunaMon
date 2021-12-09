#ifndef MQTT_STRING_H
#define MQTT_STRING_H

class Logger;

class MQTTString {
  private:
    uint8_t lengthMSB;
    uint8_t lengthLSB;
    char characterData[];

  public:
    uint16_t length() const;
    uint32_t size() const;
    // Returns false if too long to copy. maxLength is max in source and
    // does not include nil.
    bool copyTo(char *cString, unsigned maxLength) const;

  friend Logger;
};

#endif