#include "kami/scene/entity.hpp"

namespace kami {
	Entity::Entity(entt::entity handle, Scene* scene) : entityHandle(handle), scene(scene) { }
}