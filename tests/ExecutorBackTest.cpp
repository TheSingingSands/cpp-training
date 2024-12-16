#include <gtest/gtest.h>

#include "Executor.hpp"
#include "ExecutorImpl.hpp"
#include "Point.hpp"

using namespace adas;

// 测试倒退状态下，执行前进
TEST(ExecutorBackTest, should_return_minor_1_given_command_is_BM)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    executor->ExecuteCommands("BM");

    // then
    const Pose expectedPose{0, -1, 'N'};
    ASSERT_EQ(executor->Query(), expectedPose);
}

// 测试加速与倒退状态下的左转
TEST(ExecutorBackTest, should_return_correct_pose_when_back_and_turn_left_in_reverse_without_acceleration)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0}, 'E'));

    // when
    executor->ExecuteCommands("BFL");  // 倒退并左转

    // then
    const Pose expectedPose{-1, 0, 'S'};
    ASSERT_EQ(executor->Query(), expectedPose);
}

// 测试加速与倒退状态下的右转
TEST(ExecutorBackTest, should_return_correct_pose_when_back_and_turn_right_in_reverse_without_acceleration)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0}, 'S'));

    // when
    executor->ExecuteCommands("FBR");  // 倒退并右转

    // then
    const Pose expectedPose{0, 1, 'E'};
    ASSERT_EQ(executor->Query(), expectedPose);
}

// 测试不包含加速指令，包含倒退状态的复杂指令
TEST(ExecutorBackTest, should_return_correct_pose_when_back_and_without_acceleration_given_complex_command_is_MBRMMBL)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    executor->ExecuteCommands("MBRMMBL");

    // then
    const Pose expectedPose{2, 1, 'S'};
    ASSERT_EQ(executor->Query(), expectedPose);
}

// 测试包含加速指令，包含倒退状态的复杂指令
TEST(ExecutorBackTest, should_return_correct_pose_when_back_and_with_acceleration_given_complex_command_is_MBFRMBRBBMFL)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    executor->ExecuteCommands("MBFRMBRBBMFL");

    // then
    const Pose expectedPose{1, 2, 'W'};
    ASSERT_EQ(executor->Query(), expectedPose);
}
