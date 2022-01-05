#ifndef NMEA_TENTHS_UINT16_H
#define NMEA_TENTHS_UINT16_H

#include "NMEALine.h"
#include "NMEATalker.h"

#include "DataModel/DataModelLeaf.h"

#include "Util/LoggableItem.h"
#include "Util/Logger.h"

class NMEATenthsUInt16 : public LoggableItem {
    private:
        uint16_t wholeNumber;
        uint8_t tenths;
        bool valuePresent;

    public:
        bool set(const String &decimalStr, bool optional);
        bool extract(NMEALine &nmeaLine, NMEATalker &talker, const char *msgType,
                     const char *fieldName, bool optional = false);
        bool hasValue() const;
        void publish(DataModelLeaf &leaf) const;
        virtual void log(Logger &logger) const override;
};

#endif