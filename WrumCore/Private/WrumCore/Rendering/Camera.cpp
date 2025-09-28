#include "PCH.h"
#include "WrumCore/Rendering/Camera.h"
#include "WrumCore/Controllers/CameraController.h"

namespace Wrum
{
    void Camera::Update(float width, float height)
    {
        _settings._width = width;
        _settings._height = height;
        
        if (_controller)
        {
            _controller->Update();
        }
        
        _view = Mat4::LookAt(Position, Position + Forward, Up);
        _projection = Mat4::Perspective(
            _settings._FOVdeg, width / height, _settings._nearPlane, _settings._farPlane);
        _viewProjection = _projection * _view;
    }

    Vec3 Camera::GetRightVector() const
    {
        return Vec3::Cross(Forward, Up).Normalized();
    }
}
