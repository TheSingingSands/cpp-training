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

// 测试带参构造函数
TEST(ExecutorTest, should_initialize_with_parametrized_constructor) {
    // given
    std::unique_ptr<Executor> executor(new Executor(114, -514, 'E',false));

    // when
    Pose target = {114, -514, 'E'};
    
    // then
    ASSERT_EQ(target, executor->Query());
}

// 测试执行'M'指令
TEST(ExecutorTest, should_move_forward_when_execute_M_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->Initialize(0, 0, 'N');

    // when
    executor->ExecuteCommands("M");

    // then
    Pose target = {0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

// 测试执行'L'指令
TEST(ExecutorTest, should_turn_left_when_execute_L_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->Initialize(0, 0, 'N');

    // when
    executor->ExecuteCommands("L");

    // then
    Pose target = {0, 0, 'W'}; 
    ASSERT_EQ(target, executor->Query());
}

// 测试执行'R'指令
TEST(ExecutorTest, should_turn_right_when_execute_R_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->Initialize(0, 0, 'N');

    // when
    executor->ExecuteCommands("R");

    // then
    Pose target = {0, 0, 'E'}; 
    ASSERT_EQ(target, executor->Query());
}

// 测试多条指令的执行
TEST(ExecutorTest, should_execute_multiple_commands_correctly) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->Initialize(0, 0, 'E');

    // when
    executor->ExecuteCommands("MRMLMRM");

    // then
    Pose target = {2, -2, 'S'}; 
    ASSERT_EQ(target, executor->Query());
}

// 测试复杂指令
TEST(ExecutorTest, should_return_updated_position_after_complex_commands) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->Initialize(-1, 2, 'N');
    
    // when
    executor->ExecuteCommands("MMLMMRRM");

    // then
    Pose target = {-2, 4, 'E'};  
    ASSERT_EQ(target, executor->Query());
}

// 加速状态下的前进
TEST(ExecutorFastTest, should_return_x_plus_2_given_status_is_fast_command_is_M_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor(0, 0, 'E',false));
    
    // when
    executor->ExecuteCommands("FM");
    
    // then
    const Pose target{2, 0, 'E'}; 
    ASSERT_EQ(target, executor->Query());
}

// 加速状态下的左转
TEST(ExecutorFastTest, should_return_N_and_x_plus_1_given_status_is_fast_command_is_L_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor(0, 0, 'E',false));
    
    // when
    executor->ExecuteCommands("FL");
    
    // then
    const Pose target{1, 0, 'N'}; 
    ASSERT_EQ(target, executor->Query());
}

// 加速状态下的右转
TEST(ExecutorFastTest, should_return_S_and_x_plus_1_given_status_is_fast_given_command_is_R_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor(0, 0, 'E',false));
    
    // when
    executor->ExecuteCommands("FR");
    
    // then
    const Pose target{1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

// 收到两次加速指令
TEST(ExecutorFastTest, should_return_y_plus_1_given_command_is_FFM_and_facing_is_N) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    
    // when
    executor->ExecuteCommands("FFM");
    
    // then
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

// 测试加速状态下，执行复杂指令 "RFMLFMRMLFFFML"
TEST(ExecutorFastTest, should_return_correct_pose_given_complex_command_is_RFMLFMRMLFFFML) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    
    // when
    executor->ExecuteCommands("RFMLFMRMLFFFML");
    
    // then
    const Pose target{4, 4, 'W'};
    ASSERT_EQ(target, executor->Query());
}

