#pragma once
#include <cstdint>
#include <string>
#include "json11.hpp"
#include "component_types.h"

namespace minmod 
{
    namespace Component
    {
        class Interface;
        using SharedPtr = std::shared_ptr< Interface >;
        using WeakPtr = std::weak_ptr< Interface >;

        class Interface
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
            // Serialization.
            virtual void Deserialize(json11::Json json) =0;
            virtual json11::Json Serialize() const = 0;
            // Constructor and destructor replacements.
            virtual void Create() = 0;
            virtual void Destroy() = 0;
            // Insert/Erase other components.
            virtual void OnInsertComponent( Component::WeakPtr ptr ) = 0;
            virtual void OnEraseComponent( Component::WeakPtr ptr ) = 0;
        };
    }
}
