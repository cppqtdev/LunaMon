#ifndef DATA_MODEL_UINT32_LEAF_H
#define DATA_MODEL_UINT32_LEAF_H

#include "DataModelRetainedValueLeaf.h"

#include <stdint.h>

class DataModelUInt32Leaf : public DataModelRetainedValueLeaf {
   private:
        uint32_t value;

    public:
        DataModelUInt32Leaf(const char *name, DataModelElement *parent);
        DataModelUInt32Leaf & operator = (const uint32_t value);
        DataModelUInt32Leaf operator ++ (int);
        DataModelUInt32Leaf operator -- (int);
        operator uint32_t() const;
        virtual void sendRetainedValue(DataModelSubscriber &subscriber) override;
};

#endif
