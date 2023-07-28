#include "kami/scene/entity.hpp"

namespace Kami {
	Entity::Entity(entt::entity handle, Scene* scene) : entityHandle(handle), scene(scene) { }
}