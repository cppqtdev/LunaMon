#include "NMEADate.h"

#include "Config.h"

#include "Util/Logger.h"

#include <etl/string.h>
#include <etl/string_view.h>
#include <etl/string_stream.h>
#include <etl/to_arithmetic.h>

#include <stddef.h>

bool NMEADate::set(const etl::string_view &dateView) {
    const size_t length = dateView.size();
    if (length == 0) {
        hasValue = false;
        return true;
    }

    if (length != 6) {
        return false;
    }

    etl::string_view dayView(dateView.data(), dateView.data() + 2);
    etl::to_arithmetic_result<uint8_t> dayResult = etl::to_arithmetic<uint8_t>(dayView);
    if (!dayResult.has_value()) {
        return false;
    }
    if (dayResult.value() > 31) {
        return false;
    }
    day = dayResult.value();

    etl::string_view monthView(dateView.data() + 2, dateView.data() + 4);
    etl::to_arithmetic_result<uint8_t> monthResult = etl::to_arithmetic<uint8_t>(monthView);
    if (!monthResult.has_value()) {
        return false;
    }
    if (monthResult.value() > 12) {
        return false;
    }
    month = monthResult.value();

    // NMEA 0183 has a problem with date fields having a two digit year. How this made it into a
    // specification is beyond my words. Make a year by using a century in the configuration.
    etl::string_view yearView(dateView.data() + 4, dateView.data() + 6);
    etl::to_arithmetic_result<uint8_t> yearResult = etl::to_arithmetic<uint8_t>(yearView);
    if (!yearResult.has_value()) {
        return false;
    }
    year = yearResult.value() + century;

    return true;
}

bool NMEADate::extract(NMEALine &nmeaLine, NMEATalker &talker, const char *msgType) {
    etl::string_view dateView;
    if (!nmeaLine.getWord(dateView)) {
        logger << logWarning << talker << " " << msgType << " message missing Date field" << eol;
        return false;
    }

    if (!set(dateView)) {
        logger << logWarning << talker << " " << msgType << " message with bad Date field '"
               << dateView << "'" << eol;
        return false;
    }

    return true;
}

void NMEADate::publish(DataModelStringLeaf &leaf) const {
    if (hasValue) {
        // We use the US format of mm/dd/yyyyy.
        etl::string<dateLength> dateStr;
        etl::string_stream dateStrStream(dateStr);
        dateStrStream << etl::setfill('0') << etl::setw(2) << month << etl::setw(1) << "/"
                      << etl::setw(2) << day << etl::setw(1) << "/" << etl::setw(4) << year;        
        leaf = dateStr;
    } else {
        leaf.removeValue();
    }
}

void NMEADate::log(Logger &logger) const {
    if (hasValue) {
        logger << month / 10 << month % 10 << "/" << day / 10 << day % 10 << "/" << year;
    } else {
        logger << "Unknown\xC2\xB0";
    }
}
