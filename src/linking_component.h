#pragma once
#include "component_interface.h"
#include "component_static_registrant.h"
#include "json11.hpp"

namespace test
{
    namespace mmc = minmod::component;

    class TestComponent;

    /* Component to test component linking.
     *
     * The <MakeLinks> function will allow safe pointer caching,
     * for any other component type on this <Id>
     */
    class LinkingComponent : public mmc::Interface
    {
    public: //- minmod::component::Factory Registration.
        /* Static <Id>.
         *
         * Needed for <StaticRegistrant> to work.
         *
         * @return a unique <Id> for this class.
         */
        static mmc::Id GetStaticId()
        {
            return 0xd8f2a84d; // CRC32 of "link"
        }

        /* Static <Name>.
         *
         * Needed for <StaticRegistrant> to work.
         *
         * @return a unique <Name> for this class.
         */
        static mmc::Name GetStaticName()
        {
            return "link";
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
        virtual void Deserialize(const json11::Json& /*json*/) override
        {
        }

        /* @inherit */
        virtual json11::Json Serialize() const override
        {
            return json11::Json::object{};
        }

        /* @inherit */
        //virtual void MakeLinks(mmc::Linker& liner) override;

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
        static mmc::StaticRegistrant<LinkingComponent> ms_StaticRegistrant;

    private: //- Private members.
        // Pointer to another component on this <Id>, tests the linking.
        TestComponent* m_test;
    };
}
