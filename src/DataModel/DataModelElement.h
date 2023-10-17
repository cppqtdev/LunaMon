#ifndef DATA_MODEL_ELEMENT_H
#define DATA_MODEL_ELEMENT_H

class DataModelSubscriber;

#include <stdint.h>

const unsigned maxDataModelSubscribers = 5;

class DataModelElement {
    private:
        const char *name;
        DataModelElement *parent;

    protected:
        bool isMultiLevelWildcard(const char *topicFilter);
        bool topicFilterMatch(const char *topicFilter, unsigned &offsetToNextLevel,
                              bool &lastLevel);
        void buildTopicName(char *topicNameBuffer);

    public:
        DataModelElement(const char *name, DataModelElement *parent);
        const char *elementName() const;
        // Returns true if one or more subscriptions were made
        virtual bool subscribeIfMatching(const char *topicFilter, DataModelSubscriber &subscriber,
                                         uint32_t cookie) = 0;
        virtual void unsubscribeIfMatching(const char *topicFilter,
                                           DataModelSubscriber &subscriber) = 0;
        virtual bool subscribeAll(DataModelSubscriber &subscriber, uint32_t cookie) = 0;
        virtual void unsubscribeAll(DataModelSubscriber &subscriber) = 0;
};

#endif