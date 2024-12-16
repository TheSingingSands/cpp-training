#pragma once
#include "Executor.hpp"
#include "Point.hpp"
namespace adas
{

class PoseHandler
{
private:
    Point pose;
    size_t heading;
    bool is_fast;
    int forward;

public:
    PoseHandler() : pose(), heading(0), is_fast(0), forward(1) {};
    explicit PoseHandler(const Point& initial_pose, char head) noexcept;

    void ToggleFastMode() noexcept;
    void ToggleBackMode() noexcept;
    bool IsFastModeEnabled() const noexcept;
    void ExecuteMove() noexcept;
    void ExecuteTurnLeft() noexcept;
    void ExecuteTurnRight() noexcept;
    // bool IsBackModeEnabled() const noexcept;
    Point GetCurrentPosision() const noexcept;
    Pose Query() const noexcept;
    char getDirection() const noexcept;
};

}  // namespace adas
