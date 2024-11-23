#include <iostream>
#include <string>

class Executor {
public:
    // 静态工厂方法，返回一个Executor实例
    static Executor* NewExecutor() {
        return new Executor();
    }

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
    void getPosition(int32_t &x, int32_t &y, char &heading) const {
        x = x_;
        y = y_;
        heading = heading_;
    }

    // 重载==运算符，用于比较Pose
    bool operator==(const Executor &other) const {
        return x_ == other.x_ && y_ == other.y_ && heading_ == other.heading_;
    }

    void printPosition() {
        printf("x=%d, y=%d, heading:%c\n", x_, y_, heading_);
    }

private:
    int32_t x_;
    int32_t y_;
    char heading_;

    // 前进一格
    void moveForward() {
        switch (heading_) {
            case 'N': y_ += 1; break;
            case 'S': y_ -= 1; break;
            case 'E': x_ += 1; break;
            case 'W': x_ -= 1; break;
        }
    }

    // 左转90度
    void turnLeft() {
        switch (heading_) {
            case 'N': heading_ = 'W'; break;
            case 'W': heading_ = 'S'; break;
            case 'S': heading_ = 'E'; break;
            case 'E': heading_ = 'N'; break;
        }
    }

    // 右转90度
    void turnRight() {
        switch (heading_) {
            case 'N': heading_ = 'E'; break;
            case 'E': heading_ = 'S'; break;
            case 'S': heading_ = 'W'; break;
            case 'W': heading_ = 'N'; break;
        }
    }
};
