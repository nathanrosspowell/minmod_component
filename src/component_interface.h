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
    namespace component
    {
        class Linker;
        class Interface : public Serializer
        {
        public:
            // Id function.
            using IdPair = std::pair<Id, std::string>;
            virtual IdPair GetId() const = 0;

        private:
            friend class Linker;
            // Where to define dependencies on other componentMap, may be called
            // multiple times.
            virtual void MakeLinks(Linker& linker) = 0;

        private:
            friend class Manager;
            // Constructor and destructor replacements. Only ever calle once.
            virtual void Create() = 0;
            virtual void Destroy() = 0;
        };
        using UniquePtr = std::unique_ptr<Interface>;
    }
}
