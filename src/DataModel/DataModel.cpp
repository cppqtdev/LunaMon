#include "DataModel.h"
#include "DataModelNode.h"
#include "DataModelElement.h"
#include "DataModelRoot.h"
#include "DataModelUInt32Leaf.h"
#include "DataModelStringLeaf.h"
#include "Config.h"

#include "StatsManager/StatCounter.h"
#include "StatsManager/StatsManager.h"

#include "Util/Logger.h"
#include "Util/Error.h"

#include <stdint.h>

DataModelUInt32Leaf sysBrokerClientsConnected("connected", &sysBrokerClientsNode);
DataModelUInt32Leaf sysBrokerClientsDisconnected("disconnected", &sysBrokerClientsNode);
DataModelUInt32Leaf sysBrokerClientsMaximum("maximum", &sysBrokerClientsNode);
DataModelUInt32Leaf sysBrokerClientsTotal("total", &sysBrokerClientsNode);

DataModelElement *sysBrokerClientsChildren[] = {
    &sysBrokerClientsConnected,
    &sysBrokerClientsDisconnected,
    &sysBrokerClientsMaximum,
    &sysBrokerClientsTotal,
    NULL
};
DataModelNode sysBrokerClientsNode("clients", &sysBrokerNode, sysBrokerClientsChildren);

DataModelUInt32Leaf sysBrokerUptime("uptime", &sysBrokerNode);

DataModelElement *sysBrokerChildren[] = {
    &sysBrokerClientsNode,
    &sysBrokerUptime,
    NULL
};
DataModelNode sysBrokerNode("broker", &sysNode, sysBrokerChildren);

DataModelElement *sysNodeChildren[] = {
    &sysBrokerNode,
    NULL
};
DataModelNode sysNode("$SYS", &dataModelRoot, sysNodeChildren);

DataModelLeaf nmeaDataModelMessagesBridged("messages", &nmeaDataModelBridgeNode);
DataModelLeaf nmeaDataModelMessageBridgeRate("messageRate", &nmeaDataModelBridgeNode);

DataModelElement *nmeaDataModelBridgeNodeChildren[] = {
    &nmeaDataModelMessagesBridged,
    &nmeaDataModelMessageBridgeRate,
    NULL
};
DataModelNode nmeaDataModelBridgeNode("nmeaDataModelBridge", &controllerIDNode,
                                      nmeaDataModelBridgeNodeChildren);

DataModelLeaf dataModelLeafUpdates("updates", &dataModelNode);
DataModelLeaf dataModelLeafUpdateRate("updateRate", &dataModelNode);

DataModelElement *dataModelNodeChildren[] = {
    &dataModelLeafUpdates,
    &dataModelLeafUpdateRate,
    NULL
};
DataModelNode dataModelNode("dataModel", &controllerIDNode, dataModelNodeChildren);

DataModelLeaf wifiNMEAMessages("messages", &wifiNMEANode);
DataModelLeaf wifiNMEAMessageRate("messageRate", &wifiNMEANode);

DataModelElement *wifiNMEANodeChildren[] = {
    &wifiNMEAMessages,
    &wifiNMEAMessageRate,
    NULL
};
DataModelNode wifiNMEANode("wifi", &nmeaNode, wifiNMEANodeChildren);

DataModelLeaf usbNMEAMessages("messages", &usbNMEANode);
DataModelLeaf usbNMEAMessageRate("messageRate", &usbNMEANode);

DataModelElement *usbNMEANodeChildren[] = {
    &usbNMEAMessages,
    &usbNMEAMessageRate,
    NULL
};
DataModelNode usbNMEANode("usb", &nmeaNode, usbNMEANodeChildren);

DataModelElement *nmeaNodeChildren[] = {
    &usbNMEANode,
    &wifiNMEANode,
    NULL
};
DataModelNode nmeaNode("nmea", &controllerIDNode, nmeaNodeChildren);

DataModelStringLeaf mqttSession1("1", &mqttSessionsNode, maxSessionDescriptionLength);
DataModelStringLeaf mqttSession2("2", &mqttSessionsNode, maxSessionDescriptionLength);
DataModelStringLeaf mqttSession3("3", &mqttSessionsNode, maxSessionDescriptionLength);
DataModelStringLeaf mqttSession4("4", &mqttSessionsNode, maxSessionDescriptionLength);
DataModelStringLeaf mqttSession5("5", &mqttSessionsNode, maxSessionDescriptionLength);

DataModelStringLeaf *mqttSessionDebugs[] = {
    &mqttSession1,
    &mqttSession2,
    &mqttSession3,
    &mqttSession4,
    &mqttSession5
};

DataModelElement *mqttSessionsNodeChildren[] = {
    &mqttSession1,
    &mqttSession2,
    &mqttSession3,
    &mqttSession4,
    &mqttSession5,
    NULL
};
DataModelNode mqttSessionsNode("sessions", &mqttNode, mqttSessionsNodeChildren);

DataModelStringLeaf mqttConnection1("1", &mqttConnectionsNode, maxConnectionDescriptionLength);
DataModelStringLeaf mqttConnection2("2", &mqttConnectionsNode, maxConnectionDescriptionLength);
DataModelStringLeaf mqttConnection3("3", &mqttConnectionsNode, maxConnectionDescriptionLength);
DataModelStringLeaf mqttConnection4("4", &mqttConnectionsNode, maxConnectionDescriptionLength);
DataModelStringLeaf mqttConnection5("5", &mqttConnectionsNode, maxConnectionDescriptionLength);

DataModelStringLeaf *mqttConnectionDebugs[] = {
    &mqttConnection1,
    &mqttConnection2,
    &mqttConnection3,
    &mqttConnection4,
    &mqttConnection5
};

DataModelElement *mqttConnectionsNodeChildren[] = {
    &mqttConnection1,
    &mqttConnection2,
    &mqttConnection3,
    &mqttConnection4,
    &mqttConnection5,
    NULL
};
DataModelNode mqttConnectionsNode("connections", &mqttNode, mqttConnectionsNodeChildren);

DataModelUInt32Leaf mqttConnectionCount("connectionCount", &mqttNode);

DataModelElement *mqttNodeChildren[] = {
    &mqttConnectionCount,
    &mqttConnectionsNode,
    &mqttSessionsNode,
    NULL
};
DataModelNode mqttNode("MQTT", &controllerIDNode, mqttNodeChildren);

DataModelStringLeaf error1("1", &errorsNode, maxErrorLength);
DataModelStringLeaf error2("2", &errorsNode, maxErrorLength);
DataModelStringLeaf error3("3", &errorsNode, maxErrorLength);
DataModelStringLeaf error4("4", &errorsNode, maxErrorLength);
DataModelStringLeaf error5("5", &errorsNode, maxErrorLength);

DataModelStringLeaf *errorDebugs[errorDebugSlots] = {
    &error1,
    &error2,
    &error3,
    &error4,
    &error5
};

DataModelElement *errorsNodeChildren[] = {
    &error1,
    &error2,
    &error3,
    &error4,
    &error5,
    NULL
};
DataModelNode errorsNode("errors", &controllerIDNode, errorsNodeChildren);

DataModelElement *controllerIDNodeChildren[] = {
    &errorsNode,
    &mqttNode,
    &nmeaNode,
    &dataModelNode,
    &nmeaDataModelBridgeNode,
    NULL
};
DataModelNode controllerIDNode(controllerID, &controllersNode, controllerIDNodeChildren);

DataModelElement *controllersNodeChildren[] = { &controllerIDNode, NULL };
DataModelNode controllersNode("controllers", &electronicsNode, controllersNodeChildren);

DataModelElement *electronicsNodeChildren[] = { &controllersNode, NULL };
DataModelNode electronicsNode("electronics", &dataModelRoot, electronicsNodeChildren);

DataModelLeaf positionLatitude("latitude", &positionNode);
DataModelLeaf positionLongitude("longitude", &positionNode);
DataModelLeaf positionTime("time", &positionNode);
DataModelLeaf positionDataValid("dataValid", &positionNode);
DataModelLeaf positionFAAModeindicator("faaModeIndicator", &positionNode);
DataModelLeaf positionSpeedOverGround("speedOverGround", &positionNode);
DataModelLeaf positionTrackMadeGood("trackMadeGood", &positionNode);
DataModelLeaf positionDate("date", &positionNode);
DataModelLeaf positionMagneticVariation("magneticVariation", &positionNode);
DataModelLeaf positionGPSQuality("gpsQuality", &positionNode);
DataModelLeaf positionNumberSatellites("numberSatellites", &positionNode);
DataModelLeaf positionHorizontalDilutionOfPrecision("horizontalDilutionOfPrecision", &positionNode);
DataModelLeaf positionAntennaAltitude("antennaAltitude", &positionNode);
DataModelLeaf positionGeoidalSeparation("geoidalSeparation", &positionNode);
DataModelLeaf positionGPSDataAge("gpsDataAge", &positionNode);
DataModelLeaf positionDifferentialReferenceStation("differentialReferenceStation", &positionNode);
DataModelLeaf positionSatelliteSelectionMode("satelliteSelectionMode", &positionNode);
DataModelLeaf positionFixMode("fixMode", &positionNode);
DataModelLeaf positionActiveSatellites("activeSatellites", &positionNode);
DataModelLeaf positionPDOP("pdop", &positionNode);
DataModelLeaf positionHDOP("hdop", &positionNode);
DataModelLeaf positionVDOP("vdop", &positionNode);
DataModelLeaf positionStandardDeviationOfRangeInputsRMS("standardDeviationOfRangeInputsRMS",
                                                        &positionNode);
DataModelLeaf positionStandardDeviationOfSemiMajorAxis("standardDeviationOfSemiMajorAxis",
                                                       &positionNode);
DataModelLeaf positionStandardDeviationOfSemiMinorAxis("standardDeviationOfSemiMinorAxis",
                                                       &positionNode);
DataModelLeaf positionOrientationOfSemiMajorAxis("orientationOfSemiMajorAxis", &positionNode);
DataModelLeaf positionStandardDeviationOfLatitudeError("standardDeviationOfLatitudeError",
                                                       &positionNode);
DataModelLeaf positionStandardDeviationOfLongitudeError("standardDeviationOfLongitudeError",
                                                        &positionNode);
DataModelLeaf positionStandardDeviationOfAltitudeError("standardDeviationOfAltitudeError",
                                                       &positionNode);

DataModelElement *positionNodeChildren[] = {
    &positionLatitude,
    &positionLongitude,
    &positionTime,
    &positionDataValid,
    &positionFAAModeindicator,
    &positionSpeedOverGround,
    &positionTrackMadeGood,
    &positionDate,
    &positionMagneticVariation,
    &positionGPSQuality,
    &positionNumberSatellites,
    &positionHorizontalDilutionOfPrecision,
    &positionAntennaAltitude,
    &positionGeoidalSeparation,
    &positionGPSDataAge,
    &positionDifferentialReferenceStation,
    &positionSatelliteSelectionMode,
    &positionFixMode,
    &positionActiveSatellites,
    &positionPDOP,
    &positionHDOP,
    &positionVDOP,
    &positionStandardDeviationOfRangeInputsRMS,
    &positionStandardDeviationOfSemiMajorAxis,
    &positionStandardDeviationOfSemiMinorAxis,
    &positionOrientationOfSemiMajorAxis,
    &positionStandardDeviationOfLatitudeError,
    &positionStandardDeviationOfLongitudeError,
    &positionStandardDeviationOfAltitudeError,
    NULL
};
DataModelNode positionNode("position", &navigationNode, positionNodeChildren);

DataModelElement *navigationNodeChildren[] = { &positionNode, NULL };
DataModelNode navigationNode("navigation", &dataModelRoot, navigationNodeChildren);

DataModelElement *topNodeChildren[] = {
    &sysNode,
    &electronicsNode,
    &navigationNode,
    NULL
};
DataModelRoot dataModelRoot(topNodeChildren);

DataModel::DataModel(StatsManager &statsManager) : root(dataModelRoot), leafUpdatesCounter() {
    statsManager.addStatsHolder(this);
}

bool DataModel::subscribe(const char *topicFilter, DataModelSubscriber &subscriber,
                          uint32_t cookie) {
    return root.subscribe(topicFilter, subscriber, cookie);
}

void DataModel::unsubscribe(const char *topicFilter, DataModelSubscriber &subscriber) {
    root.unsubscribe(topicFilter, subscriber);
}

void DataModel::unsubscribeAll(DataModelSubscriber &subscriber) {
    root.unsubscribeAll(subscriber);
}

void DataModel::leafUpdated() {
    leafUpdatesCounter++;
}

void DataModel::exportStats(uint32_t msElapsed) {
    leafUpdatesCounter.update(dataModelLeafUpdates, dataModelLeafUpdateRate, msElapsed);
}
