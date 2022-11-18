#ifndef MQTT_SESSION_H
#define MQTT_SESSION_H

class MQTTConnection;
class MQTTBroker;
class DataModelStringLeaf;

#include "DataModel/DataModelSubscriber.h"

#include "Util/PassiveTimer.h"

#include <etl/string.h>
#include <stdint.h>

using etl::string;
using etl::istring;

//
// MQTTSession
//
// This class maintains information on a MQTT Client Session per the definition of the protocol.
// It's worth highlighting that in MQTT, a session's lifespan is not necessarily one-to-one with the
// lifespan of the TCP/IP connection that created it. This allows for clients with connection issues
// to reconnect without starting from scratch with the topics that they publish or subscribe to.
//

const unsigned maxMQTTClientIDLength = 23;

// The time, in seconds that we wait before tearing down a Session that's lost it's Connection and
// hasn't had a new one established.
const uint16_t unconnectedSessionTearDownTime = 120;

class MQTTSession : public DataModelSubscriber {
    private:
        bool cleanSession;
        string<maxMQTTClientIDLength> clientID;
        MQTTConnection *connection;
        uint16_t keepAliveTime;
        PassiveTimer keepAliveTimer;
        PassiveTimer tearDownTimer;

        void unsubscribeAll();

    public:
        bool isConnected() const;
        bool matches(const istring &clientID) const;
        void begin(bool cleanSession, const istring &clientID, MQTTConnection *connection,
                   uint16_t keepAliveTime);
        void reconnect(bool newCleanSession, MQTTConnection *connection, uint16_t keepAliveTime);
        bool disconnect();
        void service(MQTTBroker *broker);
        void resetKeepAliveTimer();
        virtual const istring &name() const override;
        virtual void publish(const char *topic, const char *value, bool retainedValue) override;
        void updateSessionDebug(DataModelStringLeaf *debug);
};

#endif
