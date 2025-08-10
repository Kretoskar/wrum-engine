#pragma once

#include "WrumCore/Math/Vec3.h"
#include "WrumCore/Math/Mat4.h"

namespace Wrum
{
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
		Vec3 _position = Vec3::Zero;
		Vec3 _forward = {-0.5f, -0.5f, -0.5f};
		Vec3 _up = Vec3::GlobalUp;

		Mat4 _view;
		Mat4 _projection;
		Mat4 _viewProjection;

		CameraSettings _settings;

	public:

		Camera(Vec3 position, Vec3 forward, CameraSettings settings)
			: _position(position), _forward(forward), _settings(settings) {}

		virtual ~Camera() = default;
		
		virtual void Update(float width, float height);

		const Mat4& GetVPMatrix() const { return _viewProjection; }
		const Mat4& GetProjectionMatrix() const { return _projection; }
		const Mat4& GetViewMatrix() const { return _view; }

		Vec3 GetPosition() const { return _position; }
	};
}