#pragma once
#ifndef MINMOD_COMPONENT__COMPONENT_INTERFACE
#define MINMOD_COMPONENT__COMPONENT_INTERFACE

#include <cstdint>
#include <string>
#include "json11.hpp"
#include "component_types.h"

namespace minmod 
{
    class ComponentInterface
    {
    public:
        friend class ComponentManager;
        using SharedPtr = std::shared_ptr< ComponentInterface >;

    public:
        // It work with the interface, each component mush have the following static function:
        // static ComponentInterface::Id GetStaticId() = 0;
        // static std::string GetStaticName() = 0;

    private:
        virtual Component::Id GetId() const = 0;
        virtual std::string GetName() const = 0;
        virtual void Deserialize(json11::Json json) =0;
        virtual json11::Json Serialize() const = 0;
        virtual void Create() = 0;
        virtual void Destroy() = 0;

    };
}

#endif 
