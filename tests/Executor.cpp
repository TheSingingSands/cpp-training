#include <gtest/gtest.h>
#include "Executor.h"

TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    int32_t x, y;
    char heading;
    executor->getPosition(x, y, heading);

    // then
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, 0);
    ASSERT_EQ(heading, 'N');
}

TEST(ExecutorTest, should_move_forward_when_execute_M_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->initialize(0, 0, 'N');

    // when
    executor->executeCommands("M");

    // then
    int32_t x, y;
    char heading;
    executor->getPosition(x, y, heading);
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, 1);
    ASSERT_EQ(heading, 'N');
}

TEST(ExecutorTest, should_turn_left_when_execute_L_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->initialize(0, 0, 'N');

    // when
    executor->executeCommands("L");

    // then
    int32_t x, y;
    char heading;
    executor->getPosition(x, y, heading);
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, 0);
    ASSERT_EQ(heading, 'W');
}

TEST(ExecutorTest, should_turn_right_when_execute_R_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->initialize(0, 0, 'N');

    // when
    executor->executeCommands("R");

    // then
    int32_t x, y;
    char heading;
    executor->getPosition(x, y, heading);
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, 0);
    ASSERT_EQ(heading, 'E');
}

TEST(ExecutorTest, should_execute_multiple_commands_correctly) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->initialize(0, 0, 'E');

    // when
    executor->executeCommands("MRMLMRM");

    // then
    int32_t x, y;
    char heading;
    executor->getPosition(x, y, heading);
    ASSERT_EQ(x, 2);
    ASSERT_EQ(y, -2);
    ASSERT_EQ(heading, 'S');
}

TEST(ExecutorTest, should_return_updated_position_after_commands) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->initialize(0, 0, 'N');
    
    // when
    executor->executeCommands("MMLMMR");

    // then
    int32_t x, y;
    char heading;
    executor->getPosition(x, y, heading);
    ASSERT_EQ(x, -2);
    ASSERT_EQ(y, 2);
    ASSERT_EQ(heading, 'N');
}
