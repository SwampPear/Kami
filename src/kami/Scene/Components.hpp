#pragma once

#include "kami/core/uuid.hpp"
#include "kami/graphics/camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace kami {
	struct IDComponent {
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
	};

	struct TransformComponent {
    glm::vec3 translation{};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::vec3 rotation{};

		glm::mat4 mat4();
		glm::mat3 normalMatrix();
  };

	/*
	struct CameraComponent {
		Camera camera;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};*/
}