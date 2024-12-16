#pragma once
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Point.hpp"
#include "PoseHandler.hpp"

namespace adas
{

// Executor 接口类
class Executor
{
public:
    Executor(void) = default;
    virtual ~Executor(void) = default;

    Executor(const Executor&) = delete;
    Executor operator=(const Executor&) = delete;
    static Executor* NewExecutor(const Point& position = {0, 0}, const char direction = 'N') noexcept;

    // 初始化接口
    virtual void Initialize(int32_t x, int32_t y, char heading) = 0;

    // 执行指令接口（批量执行）
    virtual void ExecuteCommands(const std::string& commands) = 0;

    // Virtual methods that need to be overridden
    virtual void Move(int steps) = 0;
    virtual void TurnLeft() = 0;
    virtual void TurnRight() = 0;
    virtual void ToggleFastMode() = 0;
    virtual void ToggleBackMode() = 0;
    virtual bool IsFastMode() = 0;
    virtual bool IsBackMode() = 0;
    virtual char getDirection() const noexcept = 0;
    virtual Point GetCurrentPosition() const noexcept = 0;
    virtual Pose getPose() const noexcept = 0;
};
}  // namespace adas