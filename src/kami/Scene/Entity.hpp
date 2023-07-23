#pragma once

#include "kami/Scene/UUID.hpp"
#include "kami/Scene/Scene.hpp"
#include "kami/Scene/Components.hpp"

#include "entt/entt.hpp"

#include <cassert>

namespace kami {
	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			//assert(!HasComponent<T>() && "Entity already has component!");
			T& component = scene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
			//scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args) {
			T& component = scene->registry.emplace_or_replace<T>(entityHandle, std::forward<Args>(args)...);
			//scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent() {
			//assert(HasComponent<T>() && "Entity does not have component!");
			return scene->registry.get<T>(entityHandle);
		}

		/*
		template<typename T>
		bool HasComponent() {
			return scene->registry.has<T>(entityHandle);
		}
		*/

		template<typename T>
		void RemoveComponent() {
			//assert(HasComponent<T>() && "Entity does not have component!");
			scene->registry.remove<T>(entityHandle);
		}

		operator bool() const { return entityHandle != entt::null; }
		operator entt::entity() const { return entityHandle; }
		operator uint32_t() const { return (uint32_t)entityHandle; }

		UUID GetUUID() { return GetComponent<IDComponent>().ID; }
		const std::string& GetName() { return GetComponent<TagComponent>().Tag; }

		bool operator==(const Entity& other) const {
			return entityHandle == other.entityHandle && scene == other.scene;
		}

		bool operator!=(const Entity& other) const {
			return !(*this == other);
		}
	private:
		entt::entity entityHandle{ entt::null };
		Scene* scene = nullptr;
	};

}