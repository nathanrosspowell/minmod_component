#pragma once
#include "json11.hpp"

namespace minmod
{
    namespace component
    {
        class Serializer
        {
        public:
            // Serialization.
            virtual void Deserialize(const json11::Json& json) = 0;
            virtual json11::Json Serialize() const = 0;
        };
    }
}
