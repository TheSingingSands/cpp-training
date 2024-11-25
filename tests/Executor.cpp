#include <gtest/gtest.h>
#include "Executor.h"

// 测试未初始化时的默认位置
TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    Pose target = {0, 0, 'N'};  // 默认值
    
    // then
    ASSERT_EQ(target, executor->Query());
}

// 测试执行'M'指令
TEST(ExecutorTest, should_move_forward_when_execute_M_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->initialize(0, 0, 'N');

    // when
    executor->executeCommands("M");

    // then
    Pose target = {0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

// 测试执行'L'指令
TEST(ExecutorTest, should_turn_left_when_execute_L_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->initialize(0, 0, 'N');

    // when
    executor->executeCommands("L");

    // then
    Pose target = {0, 0, 'W'}; 
    ASSERT_EQ(target, executor->Query());
}

// 测试执行'R'指令
TEST(ExecutorTest, should_turn_right_when_execute_R_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->initialize(0, 0, 'N');

    // when
    executor->executeCommands("R");

    // then
    Pose target = {0, 0, 'E'}; 
    ASSERT_EQ(target, executor->Query());
}

// 测试多条指令的执行
TEST(ExecutorTest, should_execute_multiple_commands_correctly) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->initialize(0, 0, 'E');

    // when
    executor->executeCommands("MRMLMRM");

    // then
    Pose target = {2, -2, 'S'}; 
    ASSERT_EQ(target, executor->Query());
}

// 测试复杂指令
TEST(ExecutorTest, should_return_updated_position_after_commands) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->initialize(-1, 2, 'N');
    
    // when
    executor->executeCommands("MMLMMRRM");

    // then
    Pose target = {-2, 4, 'E'};  
    ASSERT_EQ(target, executor->Query());
}

