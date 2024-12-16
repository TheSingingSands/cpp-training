#include <gtest/gtest.h>

#include "Executor.hpp"
#include "ExecutorImpl.hpp"
#include "Point.hpp"

using namespace adas;

// 测试未初始化时的默认位置
TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    const Pose target{0, 0, 'N'};  // 默认值

    // then
    ASSERT_EQ(executor->Query(), target);
}

// 测试带参构造函数
TEST(ExecutorTest, should_initialize_with_parametrized_constructor)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({114, -514}, 'E'));

    // when
    const Pose target{114, -514, 'E'};

    // then
    ASSERT_EQ(executor->Query(), target);
}

// 测试执行'M'指令
TEST(ExecutorTest, should_move_forward_when_execute_M_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    executor->ExecuteCommands("M");

    // then
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(executor->Query(), target);
}

// 测试执行'L'指令
TEST(ExecutorTest, should_turn_left_when_execute_L_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    executor->ExecuteCommands("L");

    // then
    const Pose target{0, 0, 'W'};
    ASSERT_EQ(executor->Query(), target);
}

// 测试执行'R'指令
TEST(ExecutorTest, should_turn_right_when_execute_R_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    executor->ExecuteCommands("R");

    // then
    const Pose target{0, 0, 'E'};
    ASSERT_EQ(executor->Query(), target);
}

// 测试多条指令的执行
TEST(ExecutorTest, should_execute_multiple_commands_correctly)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0}, 'E'));

    // when
    executor->ExecuteCommands("MRMLMRM");

    // then
    const Pose target{2, -2, 'S'};
    ASSERT_EQ(executor->Query(), target);
}

// 测试复杂指令
TEST(ExecutorTest, should_return_updated_position_after_complex_commands)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({-1, 2}, 'N'));

    // when
    executor->ExecuteCommands("MMLMMRRM");

    // then
    const Pose target{-2, 4, 'E'};
    ASSERT_EQ(executor->Query(), target);
}
