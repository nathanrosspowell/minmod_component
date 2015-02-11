#ifndef MINMOD_COMPONENT__COMPONENT_ID
#define MINMOD_COMPONENT__COMPONENT_ID
#pragma once

#include <cstdint>

class ComponentId
{
public:
    using Id = std:: int32_t;

    explicit ComponentId( Id newId );

private:
    Id m_id; 
};

#endif 
