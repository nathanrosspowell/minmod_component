#ifndef MINMOD_COMPONENT__COMPONENT_INTERFACE
#define MINMOD_COMPONENT__COMPONENT_INTERFACE
#pragma once

class ComponentInterface
{
private:
    virtual void Create() = 0;
    virtual void  Load() = 0;
    virtual void Ready() = 0;
    virtual void Update() = 0;
    virtual void Unload() = 0;
    virtual void Destroy() = 0;
};

#endif 
