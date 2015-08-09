#pragma once

namespace minmod
{
    namespace component
    {
        using OwnerId = std::size_t;
        using Id = std::size_t;
    }
}

// Debug traces
#define TRACE( format ) cout<<"["<<__FILE__<<"("<<__LINE__<<")::"<<__FUNCTION__<<"]"<<format<<endl;
