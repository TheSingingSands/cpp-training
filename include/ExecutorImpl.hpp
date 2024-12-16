#pragma once
#include <memory>
#include <unordered_map>

#include "Executor.hpp"
namespace adas
{

class ExecutorImpl final : public Executor
{
private:
    PoseHandler posehandler;

public:
    explicit ExecutorImpl(const Point& point, char d) noexcept : posehandler(point, d) {};

    ExecutorImpl() noexcept : posehandler() {};

    Point GetCurrentPosition() const noexcept override;

    char getDirection() const noexcept override;

    Pose Query() const noexcept override;

    void ExecuteCommands(const std::string& command) noexcept override;
};
}  // namespace adas