#include "PCH.h"

#include "WrumCore/Controllers/CameraController.h"

#include "WrumCore/Controllers/InputController.h"
#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Math/MathCore.h"
#include "WrumCore/Math/Quat.h"
#include "WrumCore/Rendering/Camera.h"
#include "WrumCore/Window/Window.h"

namespace Wrum
{
    void FlyCameraController::Init(Camera* camera)
    {
        BIND_EVENT(MousePositionEvent::Type(), OnMouseMoved)
        _newOrientation = camera->Forward;
        _camera = camera;
    }

    void FlyCameraController::Update()
    {
        const CameraSettings& settings = _camera->GetCameraSettings();
        if (InputController::GetInput(Input::RightMouseButton) == InputState::Pressed)
        {
            glfwSetCursorPos(settings._window->GetGlfwWindow(), (settings._width / 2), (settings._height / 2));
            glfwSetInputMode(settings._window->GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        if (InputController::GetInput(Input::RightMouseButton) == InputState::Released)
        {
            glfwSetInputMode(settings._window->GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        
        if (!InputController::InputPressedOrHeld(Input::RightMouseButton))
        {
            _canLook = false;
            return;
        }

        _canLook = true;

        _camera->Forward = _newOrientation;
        
        float speed = Speed;
        
        if (InputController::InputPressedOrHeld(Input::LeftShift))
        {
            speed *= SprintMultiplier;
        }
        
        if (InputController::InputPressedOrHeld(Input::W))
        {
            _camera->Position += _camera->Forward * speed;
        }
        if (InputController::InputPressedOrHeld(Input::S))
        {
            _camera->Position += _camera->Forward * -speed;
        }
        if (InputController::InputPressedOrHeld(Input::A))
        {
            _camera->Position += _camera->GetRightVector() * -speed;
        }
        if (InputController::InputPressedOrHeld(Input::D))
        {
            _camera->Position += _camera->GetRightVector() * speed;
        }
    }

    void FlyCameraController::OnMouseMoved(void* payload)
    {
        if (!_canLook)
        {
            return;
        }

        const double posX = *static_cast<double*>(payload);
        const double posY = *reinterpret_cast<double*>(static_cast<char*>(payload) + sizeof(double));

        const CameraSettings& settings = _camera->GetCameraSettings();
        double height = settings._height;
        double width = settings._width;
        
        const float rotX = Sensitivity * static_cast<float>(posY - (height / 2)) / height;
        const float rotY = Sensitivity * static_cast<float>(posX - (width / 2)) / width;
        
        Vec3 newOrientation =
            Quat(MathCore::DegToRad(-rotX), Vec3::Cross(_camera->Forward, _camera->Up).Normalized()) * _camera->Forward;
		
        // TODO: maybe dot will be enough
        if (abs(Vec3::Angle(newOrientation, _camera->Up)) > MathCore::DegToRad(5.0f) && 
            abs(Vec3::Angle(newOrientation, _camera->Up * -1)) > MathCore::DegToRad(5.0f))
        {
            newOrientation = Quat(MathCore::DegToRad(-rotY), _camera->Up) * newOrientation;
        }

        _newOrientation = newOrientation;

        Window* window = settings._window;
        if (window)
        {
            glfwSetCursorPos(window->GetGlfwWindow(), (width / 2), (height / 2));
        }
    }
}


