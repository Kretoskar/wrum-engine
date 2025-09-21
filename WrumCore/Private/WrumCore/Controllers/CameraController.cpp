#include "PCH.h"

#include "WrumCore/Controllers/CameraController.h"

#include "WrumCore/Controllers/InputController.h"
#include "WrumCore/Rendering/Camera.h"

namespace Wrum
{
    void FlyCameraController::Update(Camera* camera)
    {
        if (!InputController::InputPressedOrHeld(Input::RightMouseButton))
        {
            return;
        }

        float speed = Speed;
        
        if (InputController::InputPressedOrHeld(Input::LeftShift))
        {
            speed *= SprintMultiplier;
        }
        
        if (InputController::InputPressedOrHeld(Input::W))
        {
            camera->Position += camera->Forward * speed;
        }
        if (InputController::InputPressedOrHeld(Input::S))
        {
            camera->Position += camera->Forward * -speed;
        }
        if (InputController::InputPressedOrHeld(Input::A))
        {
            camera->Position += camera->GetRightVector() * -speed;
        }
        if (InputController::InputPressedOrHeld(Input::D))
        {
            camera->Position += camera->GetRightVector() * speed;
        }
    }
}
