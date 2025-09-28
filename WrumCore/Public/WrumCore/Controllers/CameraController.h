#pragma once
#include "WrumCore/Math/Vec3.h"

namespace Wrum
{
    class Camera;
}

namespace Wrum
{
    class ICameraController
    {
    public:
        virtual ~ICameraController() = default;

        virtual void Init(Camera* camera) = 0;
        virtual void Update() = 0;
    };

    class FlyCameraController : public ICameraController
    {
    public:
        void Init(Camera* camera) override;
        void Update() override;
        
        float Speed = 0.01f;
        float SprintMultiplier = 5.0f;
        float Sensitivity = 100.0f;
        
    private:
        void OnMouseMoved(void* payload);

        bool _canLook = false;
        Camera* _camera = nullptr;
        Vec3 _newOrientation;
    };
}
