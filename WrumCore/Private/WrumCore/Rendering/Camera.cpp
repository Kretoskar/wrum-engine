#include "PCH.h"
#include "WrumCore/Rendering/Camera.h"

namespace Wrum
{
    void Camera::Update()
    {
        _view = Mat4::LookAt(_position, _position + _forward, _up);
        _projection = Mat4::Perspective(
            _settings._FOVdeg, static_cast<float>(_settings._width) / static_cast<float>(_settings._height), _settings._nearPlane, _settings._farPlane);
        _viewProjection = _projection * _view;
    }
}