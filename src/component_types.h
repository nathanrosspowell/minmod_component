#pragma once

namespace minmod
{
    namespace component
    {
        using OwnerId = std::int32_t;
        using Id = std::uint32_t;
        static const Id INVALID_ID = 0;
    }
}

// Debug traces
#define TRACE(format) std::cout << "[" << __FILE__ << "(" << __LINE__ << ")::" << __FUNCTION__ << "]" << format << std::endl;
