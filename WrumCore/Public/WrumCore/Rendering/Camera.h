#pragma once

#include "WrumCore/Math/Vec3.h"
#include "WrumCore/Math/Mat4.h"

namespace Wrum
{
	class ICameraController;
	
	struct CameraSettings
	{
		uint16 _width = 1920;
		uint16 _height = 1080;

		float _FOVdeg = 75.0f;
		float _nearPlane = 0.01f;
		float _farPlane = 1000;
	};
	
	class Camera
	{
	protected:
		Mat4 _view;
		Mat4 _projection;
		Mat4 _viewProjection;

		CameraSettings _settings;
		ICameraController* _controller;

	public:
		Camera(Vec3 position, Vec3 forward, CameraSettings settings, ICameraController* controller = nullptr)
			: Position(position), Forward(forward), _settings(settings), _controller(controller) {}

		virtual ~Camera() = default;
		void Update(float width, float height);

		const Mat4& GetVPMatrix() const { return _viewProjection; }
		const Mat4& GetProjectionMatrix() const { return _projection; }
		const Mat4& GetViewMatrix() const { return _view; }
		
		Vec3 GetRightVector() const;

		Vec3 Position = Vec3::Zero;
		Vec3 Forward = {-0.5f, -0.5f, -0.5f};
		Vec3 Up = Vec3::GlobalUp;
	};
}
