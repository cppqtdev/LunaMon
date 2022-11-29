#ifndef NMEA_FAA_MODE_INDICATOR_H
#define NMEA_FAA_MODE_INDICATOR_H

#include "NMEA/NMEALine.h"
#include "NMEA/NMEATalker.h"

#include "DataModel/DataModelLeaf.h"

#include "Util/LoggableItem.h"
#include "Util/Logger.h"

#include <etl/string_view.h>

class NMEAFAAModeIndicator : public LoggableItem {
    private:
        enum FAAMode {
            FAA_MODE_NONE,
            FAA_MODE_AUTONOMOUS,
            FAA_MODE_CAUTION,
            FAA_MODE_DIFFERENTIAL,
            FAA_MODE_ESTIMATED,
            FAA_MODE_RTK_FLOAT,
            FAA_MODE_MANUAL,
            FAA_MODE_DATA_NOT_VALID,
            FAA_MODE_PRECISE,
            FAA_MODE_RTK_INTEGER,
            FAA_MODE_SIMULATED,
            FAA_MODE_UNSAFE
        };
        FAAMode faaMode;

        bool set(etl::string_view &faaModeView);

    public:
        NMEAFAAModeIndicator();
        bool extract(NMEALine &nmeaLine, NMEATalker &talker, const char *msgType);
        bool hasValue() const;
        void publish(DataModelStringLeaf &leaf) const;
        virtual void log(Logger &logger) const override;
};

#endif
