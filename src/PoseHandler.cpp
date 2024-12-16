#include "PoseHandler.hpp"

namespace adas
{
const std::vector<Point> direction = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const std::vector<char> dname = {'N', 'E', 'S', 'W'};
PoseHandler::PoseHandler(const Point& initialPose, char direction) noexcept : pose(initialPose), is_fast(0), forward(1)
{
    switch (direction) {
    case 'N':
        heading = 0;
        break;
    case 'E':
        heading = 1;
        break;
    case 'S':
        heading = 2;
        break;
    case 'W':
        heading = 3;
        break;
    default:
        heading = 0;
        break;
    }
}

void PoseHandler::ExecuteMove() noexcept
{
    pose += direction[heading] * forward;
}

void PoseHandler::ExecuteTurnLeft() noexcept
{
    if (forward == 1) {
        heading = heading == 0 ? 3 : heading - 1;
    } else {
        heading = heading == 3 ? 0 : heading + 1;
    }
}

void PoseHandler::ExecuteTurnRight() noexcept
{
    if (forward == 1) {
        heading = heading == 3 ? 0 : heading + 1;
    } else {
        heading = heading == 0 ? 3 : heading - 1;
    }
}

void PoseHandler::ToggleFastMode() noexcept
{
    // 切换加速模式
    is_fast = !is_fast;
}

void PoseHandler::ToggleBackMode() noexcept
{
    // 切换倒车模式
    forward = -forward;
}

bool PoseHandler::IsFastModeEnabled() const noexcept
{
    return is_fast;  // 返回加速模式是否激活
}

char PoseHandler::getDirection() const noexcept
{
    return dname[heading];
}

Point PoseHandler::GetCurrentPosision() const noexcept
{
    return pose;
}

Pose PoseHandler::Query() const noexcept
{
    return Pose{GetCurrentPosision(), getDirection()};
}

}  // namespace adas
