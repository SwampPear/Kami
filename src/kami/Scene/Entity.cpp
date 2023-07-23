#include "kami/Scene/Entity.hpp"

namespace kami {
	Entity::Entity(entt::entity handle, Scene* scene) : entityHandle(handle), scene(scene) { }
}