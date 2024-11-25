#include <iostream>
#include <string>

struct Pose {
    int32_t x;
    int32_t y;
    char heading;
    //重载，用于比较
    bool operator==(const Pose& other) const {
        return x == other.x && y == other.y && heading == other.heading;
    }
};

class Executor {
public:
    static Executor* NewExecutor() {
        return new Executor();
    }
    //默认
    Executor() : x_(0), y_(0), heading_('N') {}

    // 初始化接口
    void initialize(int32_t x, int32_t y, char heading) {
        x_ = x;
        y_ = y;
        heading_ = heading;
    }

    // 执行指令接口（批量执行）
    void executeCommands(const std::string &commands) {
        for (char command : commands) {
            switch (command) {
                case 'M': moveForward(); break;
                case 'L': turnLeft(); break;
                case 'R': turnRight(); break;
                default: break;  // 不处理非法指令
            }
        }
    }

    // 查询当前状态
    Pose Query() const {
        return Pose{x_, y_, heading_};
    }

private:
    int32_t x_;
    int32_t y_;
    char heading_;

    // 前进
    void moveForward() {
        switch (heading_) {
            case 'N': y_ += 1; break;
            case 'S': y_ -= 1; break;
            case 'E': x_ += 1; break;
            case 'W': x_ -= 1; break;
        }
    }

    // 左转
    void turnLeft() {
        switch (heading_) {
            case 'N': heading_ = 'W'; break;
            case 'W': heading_ = 'S'; break;
            case 'S': heading_ = 'E'; break;
            case 'E': heading_ = 'N'; break;
        }
    }

    // 右转
    void turnRight() {
        switch (heading_) {
            case 'N': heading_ = 'E'; break;
            case 'E': heading_ = 'S'; break;
            case 'S': heading_ = 'W'; break;
            case 'W': heading_ = 'N'; break;
        }
    }
};
