#pragma once

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
        
        virtual void Update(Camera* camera) = 0;
    };

    class FlyCameraController : public ICameraController
    {
    public:
        void Update(Camera* camera) override;

        float Speed = 0.01f;
        float SprintMultiplier = 5.0f;
    };
}
