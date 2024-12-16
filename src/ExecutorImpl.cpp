#include "ExecutorImpl.hpp"

#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "Command.hpp"  // 包含所有命令类

namespace adas
{

Executor* Executor::NewExecutor(const Point& position, const char direction) noexcept
{
    return new ExecutorImpl(position, direction);
}
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
};

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
            it->second(posehandler);
        } else {
            std::cerr << "error" << cmd;
        }
    }
}

}  // namespace adas