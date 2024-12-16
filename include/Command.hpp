#pragma once
#include <functional>
#include <memory>
#include <string>

#include "ExecutorImpl.hpp"

namespace adas
{
using Command = std::function<void(PoseHandler& posehandler)>;

class MoveCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFastModeEnabled())
            poseHandler.ExecuteMove();
        poseHandler.ExecuteMove();
    }
};
class TurnLeftCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFastModeEnabled())
            poseHandler.ExecuteMove();
        poseHandler.ExecuteTurnLeft();
    }
};

class TurnRightCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFastModeEnabled())
            poseHandler.ExecuteMove();
        poseHandler.ExecuteTurnRight();
    }
};

class FastCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.ToggleFastMode();
    }
};

class BackCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.ToggleBackMode();
    }
};
}  // namespace adas
