#include "animate_system.hpp"
#include "animated.hpp"
#include "move_finished.hpp"

AnimateSystem::AnimateSystem()
    : moveTriggers{}, numberOfMoves{}, processingMove{}
{}

void AnimateSystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
{
    handleMoveTriggers(es);

    es.each<Animated>([&](entityx::Entity entity, Animated& animated) {
        updateAnimation(entity, animated, dt);
        });

    finishMove(events);
}

void AnimateSystem::configure(entityx::EventManager& eventManager)
{
    eventManager.subscribe<MoveTrigger>(*this);
}

void AnimateSystem::receive(const MoveTrigger& moveTrigger)
{
    moveTriggers.push_back(moveTrigger);
}

void AnimateSystem::handleMoveTriggers(entityx::EntityManager& es)
{
    if (moveTriggers.size())
    {
        processingMove = true;
        numberOfMoves += moveTriggers.size();
    }
    for (const auto& moveTrigger : moveTriggers)
    {
        auto animatedEntity = es.create();
        animatedEntity.assign<Animated>(Animated{ moveTrigger.srcTile, moveTrigger.tgtTile, moveTrigger.direction });
    }
    moveTriggers.clear();
}

void AnimateSystem::updateAnimation(entityx::Entity entity, Animated& animated, const entityx::TimeDelta dt)
{
    animated.leftTime -= static_cast<float>(dt);
    switch (animated.direction)
    {
    case Direction::Left:
        animateLeft(entity, animated, dt);
        break;
    case Direction::Right:
        animateRight(entity, animated, dt);
        break;
    case Direction::Up:
        animateUp(entity, animated, dt);
        break;
    case Direction::Down:
        animateDown(entity, animated, dt);
        break;
    }
}

void AnimateSystem::animateLeft(entityx::Entity entity, Animated& animated, const entityx::TimeDelta dt)
{
    if (animated.animatedTile.getPosition().x > animated.targetTile.getPosition().x)
        animated.animatedTile.move(-calculateAnimationStep(animated, dt));
    else
        finishAnimation(entity);
}

void AnimateSystem::animateRight(entityx::Entity entity, Animated& animated, const entityx::TimeDelta dt)
{
    if (animated.animatedTile.getPosition().x < animated.targetTile.getPosition().x)
        animated.animatedTile.move(calculateAnimationStep(animated, dt));
    else
        finishAnimation(entity);
}

void AnimateSystem::animateUp(entityx::Entity entity, Animated& animated, const entityx::TimeDelta dt)
{
    if (animated.animatedTile.getPosition().y > animated.targetTile.getPosition().y)
        animated.animatedTile.move(-calculateAnimationStep(animated, dt));
    else
        finishAnimation(entity);
}

void AnimateSystem::animateDown(entityx::Entity entity, Animated& animated, const entityx::TimeDelta dt)
{
    if (animated.animatedTile.getPosition().y < animated.targetTile.getPosition().y)
        animated.animatedTile.move(calculateAnimationStep(animated, dt));
    else
        finishAnimation(entity);
}

void AnimateSystem::finishAnimation(entityx::Entity entity)
{
    entity.destroy();
    --numberOfMoves;
}

void AnimateSystem::finishMove(entityx::EventManager& events)
{
    if (processingMove && numberOfMoves == 0)
    {
        processingMove = false;
        events.emit<MoveFinished>();
    }
}

sf::Vector2f AnimateSystem::calculateAnimationStep(const Animated& animated, const entityx::TimeDelta dt) const
{
    const auto distanceX = animated.targetTile.getPosition().x - animated.animatedTile.getPosition().x;
    const auto distanceY = animated.targetTile.getPosition().y - animated.animatedTile.getPosition().y;
    const auto currentStepX = std::fabs(static_cast<float>(dt) * (distanceX) / animated.leftTime);
    const auto currentStepY = std::fabs(static_cast<float>(dt) * (distanceY) / animated.leftTime);
    return { currentStepX, currentStepY };
}
