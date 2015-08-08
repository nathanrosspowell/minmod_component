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
        class Linker;
        class Interface : public Serializer
        {
        public:
            friend class Manager;
            // Id functions.
            virtual Id GetId() const = 0;
            virtual std::string GetName() const = 0;

        private:
            // Where to define dependencies on other components, may be called multiple times.
            virtual void MakeLinks(Linker& linker) = 0;
            // Constructor and destructor replacements. Only ever calle once.
            virtual void Create() = 0;
            virtual void Destroy() = 0;
        };
        using UniquePtr = std::unique_ptr< Interface >;
    }
}
