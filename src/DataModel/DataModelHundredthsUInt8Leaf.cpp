#include "DataModelHundredthsUInt8Leaf.h"
#include "DataModelLeaf.h"

#include <etl/string.h>
#include <etl/string_stream.h>

#include <stdint.h>

constexpr size_t maxStringLength = 6;

DataModelHundredthsUInt8Leaf::DataModelHundredthsUInt8Leaf(const char *name,
                                                           DataModelElement *parent)
    : DataModelRetainedValueLeaf(name, parent) {
}

void DataModelHundredthsUInt8Leaf::set(uint8_t wholeNumber, uint8_t hundredths) {
    if (!hasValue() || this->wholeNumber != wholeNumber || this->hundredths != hundredths) {
        this->wholeNumber = wholeNumber;
        this->hundredths = hundredths;
        updated();
        etl::string<maxStringLength> valueStr;
        etl::string_stream valueStrStream(valueStr);
        valueStrStream << wholeNumber << "." << etl::setfill(0) << etl::setw(2) << hundredths;
        *this << valueStr;
    }
}

void DataModelHundredthsUInt8Leaf::sendRetainedValue(DataModelSubscriber &subscriber) {
    if (hasValue()) {
        etl::string<maxStringLength> valueStr;
        etl::string_stream valueStrStream(valueStr);
        valueStrStream << wholeNumber << "." << etl::setfill(0) << etl::setw(2) << hundredths;
        publishToSubscriber(subscriber, valueStr, true);
    }
}
