#include <gtest/gtest.h>

#include "Executor.hpp"
#include "ExecutorImpl.hpp"
#include "Point.hpp"

using namespace adas;

TEST(SportsCarTest, should_move_forward_two_steps_when_execute_M_command)
{
    std::unique_ptr<Executor> executor(Executor::NewSportsCar());

    executor->ExecuteCommands("M");

    const Pose target{0, 2, 'N'};  // 跑车每次移动2格
    ASSERT_EQ(executor->Query(), target);
}

TEST(SportsCarTest, should_turn_left_and_move_forward_when_execute_L_command)
{
    std::unique_ptr<Executor> executor(Executor::NewSportsCar());

    executor->ExecuteCommands("L");

    const Pose target{-1, 0, 'W'};  // 左转后，前进1格
    ASSERT_EQ(executor->Query(), target);
}

TEST(SportsCarTest, should_turn_right_and_move_forward_when_execute_R_command)
{
    std::unique_ptr<Executor> executor(Executor::NewSportsCar());

    executor->ExecuteCommands("R");

    const Pose target{1, 0, 'E'};  // 右转后，前进1格
    ASSERT_EQ(executor->Query(), target);
}

TEST(BusTest, should_move_forward_one_step_when_execute_M_command)
{
    std::unique_ptr<Executor> executor(Executor::NewBus());

    executor->ExecuteCommands("M");

    const Pose target{0, 2, 'N'};  // 公交车每次移动1格
    ASSERT_EQ(executor->Query(), target);
}

TEST(BusTest, should_turn_left_and_move_forward_when_execute_L_command)
{
    std::unique_ptr<Executor> executor(Executor::NewBus());

    executor->ExecuteCommands("L");

    const Pose target{0, 2, 'W'};  // 前进1格后左转
    ASSERT_EQ(executor->Query(), target);
}

TEST(BusTest, should_turn_right_and_move_forward_when_execute_R_command)
{
    std::unique_ptr<Executor> executor(Executor::NewBus());

    executor->ExecuteCommands("R");

    const Pose target{0, 2, 'E'};  // 前进1格后右转
    ASSERT_EQ(executor->Query(), target);
}
