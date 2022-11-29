#include "NMEALine.h"
#include "NMEAMessage.h"
#include "NMEATalker.h"
#include "NMEAMsgType.h"
#include "NMEAGGAMessage.h"
#include "NMEAGLLMessage.h"
#include "NMEAGSAMessage.h"
#include "NMEAGSTMessage.h"
#include "NMEAGSVMessage.h"
#include "NMEARMCMessage.h"
#include "NMEATXTMessage.h"
#include "NMEAVDMVDOMessage.h"
#include "NMEAVTGMessage.h"

#include "Util/Logger.h"

#include <etl/string.h>
#include <etl/string_view.h>

NMEAMessage::NMEAMessage(NMEATalker &talker) : talker(talker) {
}

NMEATalker NMEAMessage::source() const {
    return talker;
}

bool NMEAMessage::extractConstantWord(NMEALine &nmeaLine, const char *messageType,
                                      const char *constantWord) {
    etl::string_view word;
    if (!nmeaLine.getWord(word)) {
        logger << logError << talker << " " << messageType << " message missing " << constantWord
               << " field" << eol;
        return false;
    }

    if (word != constantWord) {
        logger << logError << talker << " " << messageType << " message with bad " << constantWord
               << " field" << eol;
        return false;
    }

    return true;
}

NMEAMessage *parseNMEAMessage(NMEALine &nmeaLine) {
    etl::string_view tagView;
    if (!nmeaLine.getWord(tagView)) {
        logger << logWarning << "NMEA message missing tag" << eol;
        return NULL;
    }
    if (tagView.size() != 5) {
        logger << logWarning << "Bad NMEA tag '" << tagView << "'" << eol;
        return NULL;
    }

    etl::string<2> talkerCode(tagView.begin(), 2);
    NMEATalker talker(talkerCode);

    etl::string<3> msgTypeStr(tagView.begin() + 2, 3);
    enum NMEAMsgType msgType = parseNMEAMsgType(msgTypeStr);

    switch (msgType) {
        case NMEA_MSG_TYPE_GGA:
            return parseNMEAGGAMessage(talker, nmeaLine);

        case NMEA_MSG_TYPE_GLL:
            return parseNMEAGLLMessage(talker, nmeaLine);

        case NMEA_MSG_TYPE_GSA:
            return parseNMEAGSAMessage(talker, nmeaLine);

        case NMEA_MSG_TYPE_GST:
            return parseNMEAGSTMessage(talker, nmeaLine);

        case NMEA_MSG_TYPE_GSV:
            return parseNMEAGSVMessage(talker, nmeaLine);

        case NMEA_MSG_TYPE_RMC:
            return parseNMEARMCMessage(talker, nmeaLine);

        case NMEA_MSG_TYPE_TXT:
            return parseNMEATXTMessage(talker, nmeaLine);

        case NMEA_MSG_TYPE_VDM:
        case NMEA_MSG_TYPE_VDO:
            return parseNMEAVDMVDOMessage(talker, msgType, nmeaLine);

        case NMEA_MSG_TYPE_VTG:
            return parseNMEAVTGMessage(talker, nmeaLine);

        case NMEA_MSG_TYPE_UNKNOWN:
        default:
            logger << logWarning << "Unknown NMEA message type (" << msgTypeStr << ") from "
                   << talker << eol;
            return NULL;
    }
}
