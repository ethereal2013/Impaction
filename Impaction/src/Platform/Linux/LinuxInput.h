#pragma once
#include "Impaction/Core/Input.h"

namespace impct
{

    class LinuxInput : public Input
    {
    public:
        ~LinuxInput() override = default;
    protected:
        bool IsKeyPressedImpl(int keycode) override;
        bool IsMouseButtonPressedImpl(int button) override;
        std::pair<float, float> GetMousePosImpl() override;
        float GetMouseXImpl() override;
        float GetMouseYImpl() override;
    };

}