#pragma once
// stl
#include <cstdint>
#include <string>
// json
#include "json11.hpp"
// minmod
#include "component_types.h"
#include "component_serializer.h"

namespace minmod 
{
    namespace Component
    {
        class Interface : public Serializer
        {
        public:
            friend class Manager;

        public:
            // To work with the interface, each component mush have the following static function:
            // static Interface::Id GetStaticId() = 0;
            // static std::string GetStaticName() = 0;

        private:
            // Id functions.
            virtual Id GetId() const = 0;
            virtual std::string GetName() const = 0;
            // Constructor and destructor replacements.
            virtual void Create() = 0;
            virtual void Destroy() = 0;
            // Insert/Erase other components.
            virtual void OnInsertComponent( Interface* ptr ) = 0;
            virtual void OnEraseComponent( Interface* ptr ) = 0;
        };

        using UniquePtr = std::unique_ptr< Interface >;
    }
}
