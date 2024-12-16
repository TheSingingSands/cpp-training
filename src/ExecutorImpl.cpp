#include "ExecutorImpl.hpp"

#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "Command.hpp"  // 包含所有命令类

namespace adas
{

// Executor 创建函数
Executor* Executor::NewExecutor(const Point& position, const char direction) noexcept
{
    return new ExecutorImpl(position, direction);
}

Executor* Executor::NewSportsCar(const Point& position, const char direction) noexcept
{
    return new SportsCarExecutor(position, direction);
}

Executor* Executor::NewBus(const Point& position, const char direction) noexcept
{
    return new BusExecutor(position, direction);
}

// ExecutorImpl 实现
Point ExecutorImpl::GetCurrentPosition() const noexcept
{
    return posehandler.GetCurrentPosision();
}

char ExecutorImpl::getDirection() const noexcept
{
    return posehandler.getDirection();
}

Pose ExecutorImpl::Query() const noexcept
{
    return posehandler.Query();
}

void ExecutorImpl::ExecuteCommands(const std::string& s) noexcept
{
    std::unordered_map<char, Command> commandMap{{'M', MoveCommand()},
                                                 {'L', TurnLeftCommand()},
                                                 {'R', TurnRightCommand()},
                                                 {'F', FastCommand()},
                                                 {'B', BackCommand()}};

    for (const auto cmd : s) {
        auto it = commandMap.find(cmd);
        if (it != commandMap.end()) {
            it->second(posehandler);  // 执行命令
        } else {
            std::cerr << "Unknown command: " << cmd << "\n";
        }
    }
}

// SportsCarExecutor 实现
Point SportsCarExecutor::GetCurrentPosition() const noexcept
{
    return posehandler.GetCurrentPosision();
}

char SportsCarExecutor::getDirection() const noexcept
{
    return posehandler.getDirection();
}

Pose SportsCarExecutor::Query() const noexcept
{
    return posehandler.Query();
}

void SportsCarExecutor::ExecuteCommands(const std::string& s) noexcept
{
    for (const auto cmd : s) {
        switch (cmd) {
        case 'M':                       // 跑车每次移动2格
            posehandler.ExecuteMove();  // 执行前进1格
            posehandler.ExecuteMove();  // 再执行前进1格
            break;
        case 'L':                           // 左转90度后前进1格
            posehandler.ExecuteTurnLeft();  // 执行左转
            posehandler.ExecuteMove();      // 执行前进1格
            break;
        case 'R':                            // 右转90度后前进1格
            posehandler.ExecuteTurnRight();  // 执行右转
            posehandler.ExecuteMove();       // 执行前进1格
            break;
        default:
            std::cerr << "Unknown command: " << cmd << "\n";
            break;
        }
    }
}

// BusExecutor 实现
Point BusExecutor::GetCurrentPosition() const noexcept
{
    return posehandler.GetCurrentPosision();
}

char BusExecutor::getDirection() const noexcept
{
    return posehandler.getDirection();
}

Pose BusExecutor::Query() const noexcept
{
    return posehandler.Query();
}

void BusExecutor::ExecuteCommands(const std::string& s) noexcept
{
    for (const auto cmd : s) {
        switch (cmd) {
        case 'M':                       // 公交车每次移动1格
            posehandler.ExecuteMove();  // 执行前进1格
            break;
        case 'L':                           // 前进1格后左转
            posehandler.ExecuteMove();      // 先执行前进1格
            posehandler.ExecuteTurnLeft();  // 然后执行左转
            break;
        case 'R':                            // 前进1格后右转
            posehandler.ExecuteMove();       // 先执行前进1格
            posehandler.ExecuteTurnRight();  // 然后执行右转
            break;
        default:
            std::cerr << "Unknown command: " << cmd << "\n";
            break;
        }
    }
}

}  // namespace adas