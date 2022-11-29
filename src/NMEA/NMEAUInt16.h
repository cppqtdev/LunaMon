#ifndef NMEA_UINT16_H
#define NMEA_UINT16_H

#include "NMEALine.h"
#include "NMEATalker.h"

#include "DataModel/DataModelUInt16Leaf.h"

#include "Util/LoggableItem.h"
#include "Util/Logger.h"

#include <etl/string_view.h>

class NMEAUInt16 : public LoggableItem {
    private:
        uint16_t value;
        bool valuePresent;

        bool set(const etl::string_view &valueView, bool optional, uint16_t maxValue);

    public:
        bool extract(NMEALine &nmeaLine, NMEATalker &talker, const char *msgType,
                     const char *fieldName, bool optional = false, uint16_t maxValue = 0xffff);
        bool hasValue() const;
        uint16_t getValue() const;
        void publish(DataModelUInt16Leaf &leaf) const;
        virtual void log(Logger &logger) const override;
};

#endif
