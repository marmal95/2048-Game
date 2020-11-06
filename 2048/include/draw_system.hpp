#pragma once

#include <entityx/entityx.h>

class DrawSystem : public entityx::System<DrawSystem>
{
public:
	void update(entityx::EntityManager&, entityx::EventManager&, entityx::TimeDelta);
};