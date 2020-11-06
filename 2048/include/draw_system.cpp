#include "draw_system.hpp"
#include "grid.hpp"
#include "resource_manager.hpp"
#include "animated.hpp"

void DrawSystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
{
	auto& window = ResourcesManager::get_instance().window;
	es.each<Grid>([&](entityx::Entity entity, Grid& grid) {
		window.draw(grid.grid);
		for (const auto& gridRow : grid.tiles)
			for (const auto& tile : gridRow)
				window.draw(tile);
		});

	es.each<Animated>([&](entityx::Entity entity, Animated& animated) {
		window.draw(animated.animatedTile);
		});
}
