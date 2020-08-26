#include "pch.h"
#include "RigidBodyComponent.h"

bool nc::RigidBodyComponent::Create(void* data)
{
    m_owner = static_cast<GameObject*>(data);
    return true;
}

void nc::RigidBodyComponent::Destroy()
{

}

void nc::RigidBodyComponent::Read(const rapidjson::Value& value)
{
    nc::json::Get(value, "isDynamic", m_data.isDynamic);
    nc::json::Get(value, "lockAngle", m_data.lockAngle);
    nc::json::Get(value, "size", m_data.size);
    nc::json::Get(value, "density", m_data.density);
    nc::json::Get(value, "friction", m_data.friction);
}

void nc::RigidBodyComponent::Update()
{
    if (m_body == nullptr)
    {
        m_body = m_owner->m_engine->GetSystem<PhysicsSystem>()->CreateBody(m_owner->m_transform.position, m_data, m_owner);
    }

    m_owner->m_transform.position = m_body->GetPosition();
    m_owner->m_transform.angle = m_body->GetAngle();
}

void nc::RigidBodyComponent::ApplyForce(const Vector2& force)
{
    m_body->ApplyLinearImpulseToCenter(force, true);
}
