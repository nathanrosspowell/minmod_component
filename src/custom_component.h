#pragma once
#include "component_interface.h"
#include "component_static_registrant.h"
#include "json11.hpp"

namespace test
{
    namespace mmc = minmod::component;

    /* Component example with no static members.
     *
     * The <Id> and <Name> of the class are dynamic,
     * this allows many custom registrations to the factory.
     */
    class CustomComponent : public mmc::Interface
    {
    public: //- Public functions.

        /* Constructor.
         * @id the <Id>, will be returned from <GetId>.
         * @name the <Name>, will be returned from <GetName>.
         * @max some dummy info to set.
         */
        CustomComponent(const mmc::Id id, const mmc::Name& name, const std::int32_t max);

        /* Default destructor.
         *
         * Make sure the correct constructor is called when we have polymophism.
         */
        virtual ~CustomComponent() = default;

        /* Dummy function.
         *
         * This prints out the dummy information in the class.
         */
        void Print();

    public: //- minmod::Component::Interface.

        /* @inherit */
        virtual mmc::Id GetId() const
        {
            return m_id;
        }

        /* @inherit */
        virtual mmc::Name GetName() const
        {
            return m_name;
        }

    private: //- minmod::Component::Interface.

        /* @inherit */
        virtual void Deserialize(const json11::Json& json) override;

        /* @inherit */
        virtual json11::Json Serialize() const override;

        /* @inherit */
        //virtual void MakeLinks(mmc::Linker& /*liner*/) override { }

        /* @inherit */
        virtual void Create() override { }

        /* @inherit */
        virtual void Destroy() override { }

    private:
        // Custom <Id>.
        const mmc::Id m_id;

        // Custom <Name>.
        const mmc::Name m_name;
        
        // Dummy info for the class.
        std::int32_t m_max;

        // Dummy info for the class.
        std::int32_t m_size;
    };
}
