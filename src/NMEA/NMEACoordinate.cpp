#include "NMEACoordinate.h"

#include "DataModel/DataModel.h"
#include "DataModel/DataModelStringLeaf.h"

#include "Util/CharacterTools.h"
#include "Util/StringTools.h"
#include "Util/Logger.h"

#include <etl/string_view.h>
#include <etl/to_arithmetic.h>
#include <etl/string.h>
#include <etl/string_stream.h>

#include <stdint.h>

bool NMEACoordinate::setDegrees(const etl::string_view &degreesView, uint8_t maxDegrees) {
    etl::to_arithmetic_result<uint8_t> conversionResult = etl::to_arithmetic<uint8_t>(degreesView);
    if (!conversionResult.has_value()) {
        return false;
    }

    if (conversionResult.value() > maxDegrees) {
        return false;
    }

    degrees = conversionResult.value();
    return true;
}

bool NMEACoordinate::setMinutes(const etl::string_view &minutesView) {
    etl::string_view wholeMinutesView(minutesView.begin(), 2);
    etl::to_arithmetic_result<uint8_t> wholeResult = etl::to_arithmetic<uint8_t>(wholeMinutesView);
    if (!wholeResult.has_value()) {
        return false;
    }
    uint8_t wholeMinutes = wholeResult.value();
    if (wholeMinutes > 59) {
        return false;
    }

    if (minutesView.size() > 2) {
        if (minutesView[2] != '.') {
            return false;
        }

        if (minutesView.size() > 3) {
            etl::string_view decimalView(minutesView.begin() + 2, minutesView.end());
            etl::to_arithmetic_result<float> decimalResult = etl::to_arithmetic<float>(decimalView);
            if (!decimalResult.has_value()) {
                return false;
            }
            minutes = (float)wholeMinutes + decimalResult.value();
        } else {
            minutes = (float)wholeMinutes;
        }
    } else {
        minutes = (float)wholeMinutes;
    }

    return true;
}

// This prints the coordinate as unsigned and the caller is responsible for appending N/S or E/W.
void NMEACoordinate::log(Logger &logger) const {
    etl::string<20> coordinateStr;
    etl::string_stream coordinateStream(coordinateStr);

    coordinateStream << degrees << "\xC2\xB0" << etl::setprecision(5) << minutes << "'";

    logger << coordinateStr;
}

// We publish coordinates as a string containing a signed, floating point number of degrees.
// Clients are responsible for displaying the values in a way that matches the users preference.
void NMEACoordinate::publish(DataModelStringLeaf &leaf, bool isPositive) const {
    etl::string<coordinateLength> coordinateStr;
    etl::string_stream coordinateStream(coordinateStr);

    if (!isPositive) {
        coordinateStream << "-";
    }
    float coordinateFloat = degrees + minutes / 60;
    coordinateStream << etl::setprecision(4) << coordinateFloat;

    leaf = coordinateStr;
}
