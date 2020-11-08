#pragma once

#include <entityx/entityx.h>
#include <optional>
#include "game_finished.hpp"
#include <SFML/Graphics/Text.hpp>

class DrawSystem : public entityx::System<DrawSystem>, public entityx::Receiver<DrawSystem>
{
public:
    DrawSystem();
    void update(entityx::EntityManager&, entityx::EventManager&, entityx::TimeDelta);
    void configure(entityx::EventManager&) override;
    void receive(const GameFinished&);

private:
    void handleGameOver();

    std::optional<GameFinished> gameFinishedEvent;
    sf::Font font;
    sf::Text text;
};