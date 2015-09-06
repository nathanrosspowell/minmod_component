#pragma once
#include "component_interface.h"
#include "component_static_registrant.h"
#include "json11.hpp"

namespace test
{
    namespace mmc = minmod::component;

    /* Component to test the serialization interface.
     *
     * The members <m_x>, <m_y> and <m_z> are read/write from a <json11::Json> structure.
     */
    class TestComponent : public mmc::Interface
    {
    public:
        /* Constructor.
         *
         * Sets all the members to 0.
         */
        TestComponent();

        /* Destructor */
        virtual ~TestComponent();

        /* Print out the position.
         *
         * Used for debugging only.
         */
        void Print();

    public: //- minmod::component::Factory Registration.

        /* Static <Id>.
         *
         * Needed for <StaticRegistrant> to work.
         *
         * @return a unique <Id> for this class.
         */
        static mmc::Id GetStaticId()
        {
            return 0xaccf8b33; // CRC32 of "test".
        }

        /* Static <Name>.
         *
         * Needed for <StaticRegistrant> to work.
         *
         * @return a unique <Name> for this class.
         */
        static mmc::Name GetStaticName()
        {
            return "test";
        }

    public: //- minmod::component::Interface.

        /* @inherit */
        virtual mmc::Id GetId() const
        {
            return GetStaticId();
        }

        /* @inherit */
        virtual mmc::Name GetName() const
        {
            return GetStaticName();
        }

    private: //- minmod::component::Interface.

        /* @inherit */
        virtual void Deserialize(const json11::Json& json) override;

        /* @inherit */
        virtual json11::Json Serialize() const override;

        /* @inherit */
        virtual void MakeLinks(mmc::Linker& /*liner*/) override
        {
        }

        /* @inherit */
        virtual void Create() override
        {
        }

        /* @inherit */
        virtual void Destroy() override
        {
        }

    private: //- Private static members.

        // Static scoped typed registraion.
        static mmc::StaticRegistrant<TestComponent> ms_StaticRegistrant;

    private: //- Private members.

        // Dummy position data to test serialization.
        std::int32_t m_x = 0;

        // Dummy position data to test serialization.
        std::int32_t m_y = 0; 

        // Dummy position data to test serialization.
        std::int32_t m_z = 0;
    };
}
