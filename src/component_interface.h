#pragma once
//- stl.
#include <cstdint>
#include <string>
//- json11.
#include "json11.hpp"
//- minmod.
#include "component_types.h"
#include "component_serializer.h"

namespace minmod
{
    namespace component
    {
        class Linker;

        /* The interface to the component::Manager.
         *
         * Any class which wants to work in the coponent system has to implement this pure interface.
         * The only public functions are for infering the type.
         * The rest of the functions are private with access via friend classes only.
         */
        class Interface : public Serializer
        {
        public: //- Id functions.

            /* Get a unique <Id> for this class type.
             *
             * The <Id> has to be unique per type, not per instance.
             * It is adviced to use something like a CRC32 of the value used in <GetName>.
             *
             * @return A unique <Id> for this class.
             */
            virtual Id GetId() const = 0;

            /* Get a unique <Name> for this class type.
             *
             * The <Name> has to be unique per type, not per instance.
             * It is adviced to use something that matches the class name.
             * E.g. use "Position" for a `PositionComponent`.
             *
             * @return A unique <Name> for this class.
             */
            virtual Name GetName() const = 0;

        private: //- Linker interface.

            friend class Linker;

            /* Where to define dependencies on other componentMap, may be called multiple times.
             * @linker a <Linker> instance to record the links for this component.
             *
             * Each component has the opertunity to 'link' itself to others using the <Linker::Link> function.
             * Two functions are passed to it:
             *     1) A function taking the pointer to the component type when it's added
             *     2) A function taking when the component is removed
             *
             * The basic usage of this is to safely store and invalidate a member pointer.
             */
            virtual void MakeLinks(Linker& linker) = 0;

        private: //- Manager interface.

            friend class Manager;
            /* Constructor replacement. 
             *
             * This will be called once on the component.
             */

            virtual void Create() = 0;
            /* Destructor replacement. 
             *
             * This will be called once on the component.
             */
            virtual void Destroy() = 0;
        };

        /* A unique pointer to an interface.
         *
         * The manager will store one unique pointer for the lifetime of the component.
         * There will only be limited access to it and raw pointers to it should not be cached.
         */
        using UniquePtr = std::unique_ptr<Interface>;
    }
}
