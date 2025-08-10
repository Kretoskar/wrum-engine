#include "PCH.h"
#include "WrumCore/Rendering/Camera.h"

namespace Wrum
{
    void Camera::Update(float width, float height)
    {
        _view = Mat4::LookAt(_position, _position + _forward, _up);
        _projection = Mat4::Perspective(
            _settings._FOVdeg, width / height, _settings._nearPlane, _settings._farPlane);
        _viewProjection = _projection * _view;
    }
}