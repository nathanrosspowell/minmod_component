#pragma once
#include "json11.hpp"

namespace minmod 
{
    namespace Component
    {
        class Serializer
        {
        public:
            // Serialization.
            virtual void Deserialize(json11::Json json) =0;
            virtual json11::Json Serialize() const = 0;
        };
    }
}
