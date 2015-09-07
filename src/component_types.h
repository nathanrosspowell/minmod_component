#pragma once

/* <minmod> : Minimal Modern C++ Libs.
 *
 * Minimal: What I decided as the basic needs for the system and nothing more.
 * Modern: Using features from C++11/14/17 when it makes sense, not just for the sake of it.
 */
namespace minmod
{
    /* Component namespace
     *
     * All component related code is under this namespace so the naming can be kept short.
     */
    namespace component
    {
        // The owner of a component.
        using OwnerId = std::int32_t;

        // The fast identifier for a component.
        using Id = std::uint32_t;

        // The slow identifier for a component.
        using Name = std::string;

        // The test for an invalid <Id>, returned in place of 'null'.
        static const Id INVALID_ID = 0;
    }
}

#ifdef NDEBUG
#define TRACE(format)
#define UNUSED(x) (void)(x)
#else
#define TRACE(format) std::cout << "[" << __FILE__ << "(" << __LINE__ << ")::" << __FUNCTION__ << "]" << format << std::endl;
#define UNUSED(x)
#endif
