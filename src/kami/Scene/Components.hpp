#pragma once

#include "kami/core/uuid.hpp"
#include "kami/renderer/camera.hpp"
#include "kami/renderer/cameraController.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

namespace Kami {
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

	struct CameraComponent {
		Camera *camera;
		CameraController *cameraController;
		bool primary{true};

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct ModelComponent {
		UUID ID;

		ModelComponent() = default;
		ModelComponent(const ModelComponent&) = default;
	};

	struct ColorComponent{
    glm::vec3 color{};
  };
}