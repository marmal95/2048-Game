#pragma once

#include <entityx/entityx.h>
#include <vector>
#include "move_trigger.hpp"

struct Animated;

class AnimateSystem : public entityx::System<AnimateSystem>, public entityx::Receiver<AnimateSystem>
{
public:
	AnimateSystem();
	void update(entityx::EntityManager&, entityx::EventManager&, entityx::TimeDelta);
	void configure(entityx::EventManager&) override;
	void receive(const MoveTrigger&);

private:
	void handleMoveTriggers(entityx::EntityManager&);
	void updateAnimation(entityx::Entity, Animated&, const entityx::TimeDelta);
	void animateLeft(entityx::Entity, Animated&, const entityx::TimeDelta);
	void animateRight(entityx::Entity, Animated&, const entityx::TimeDelta);
	void animateUp(entityx::Entity, Animated&, const entityx::TimeDelta);
	void animateDown(entityx::Entity, Animated&, const entityx::TimeDelta);
	void finishAnimation(entityx::Entity);
	void finishMove(entityx::EventManager&);
	sf::Vector2f calculateAnimationStep(const Animated&, const entityx::TimeDelta) const;

	std::vector<MoveTrigger> moveTriggers;
	std::size_t numberOfMoves{};
	bool processingMove{};
};