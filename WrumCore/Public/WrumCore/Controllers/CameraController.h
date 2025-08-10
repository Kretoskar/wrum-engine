#pragma once

namespace Wrum
{
    class CameraController
    {
    public:
        virtual ~CameraController() = default;
        
        virtual void Update() = 0;
        virtual void GetVelocity() = 0;
        virtual void GetOrientation() = 0;
    };

    class FlyCameraController : public CameraController
    {
    public:
        void Update() override;
        void GetVelocity() override;
        void GetOrientation() override;
    };
}
