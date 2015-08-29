#pragma once
//- json11.
#include "json11.hpp"

namespace minmod
{
    namespace component
    {
        /* The interface for saveing and loading.
         *
         * Any class that wants to go into a save file needs to inherit from this interface.
         * It uses the <json11::Json> object to save/load the required member variables for the class.
         * It is up to the calling classes for how to use this data.
         * The <json11::Json> object that is returned can be easily nested inside of another <json11::Json> object.
         */
        class Serializer
        {
        public:
             
            /* Write-out function.
             *
             * Everything that can save should output to a <json11::Json> structure so it can be written to a file.
             * This should be an object with one *key, value* pair for each member.
             *
             * @return <json11::Json> structure which holds all of the member variables that are to be saved
             */
            virtual json11::Json Serialize() const = 0;

            /* Read-in function.
             * @json the data to read from.
             *
             * Each memeber in this <json11::Json> object should map directly to a member variable in this class.
             */
            virtual void Deserialize(const json11::Json& json) = 0;
        };
    }
}
