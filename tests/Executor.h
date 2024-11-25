#pragma once
#include <iostream>
#include <string>

// 用于表示位置的结构体
struct Pose {
    int32_t x;
    int32_t y;
    char heading;

    // 重载，用于比较位置
    bool operator==(const Pose& other) const {
        return x == other.x && y == other.y && heading == other.heading;
    }
};

class Executor {
public:
    // 静态工厂方法，返回 Executor 实例
    static Executor* NewExecutor() {
        return new Executor();
    }

    // 默认构造函数
    Executor() : m_x(0), m_y(0), m_heading('N') {}

    // 带参构造函数
    Executor(int32_t x, int32_t y, char heading) : m_x(x), m_y(y), m_heading(heading) {}

    // 初始化接口
    void Initialize(int32_t x, int32_t y, char heading) {
        m_x = x;
        m_y = y;
        m_heading = heading;
    }

    // 执行指令接口（批量执行）
    void ExecuteCommands(const std::string &commands) {
        for (char command : commands) {
            switch (command) {
                case 'M': MoveForward(); break;
                case 'L': TurnLeft(); break;
                case 'R': TurnRight(); break;
                default: break;  // 不处理非法指令
            }
        }
    }

    // 查询当前状态
    Pose Query() const {
        return Pose{m_x, m_y, m_heading};
    }

private:
    // 成员变量
    int32_t m_x;
    int32_t m_y;
    char m_heading;

    // 前进一格
    void MoveForward() {
        switch (m_heading) {
            case 'N': m_y += 1; break;
            case 'S': m_y -= 1; break;
            case 'E': m_x += 1; break;
            case 'W': m_x -= 1; break;
        }
    }

    // 取模实现左转
    void TurnLeft() {
        static const char directions[] = {'N', 'E', 'S', 'W'};
        m_heading = directions[(FindDirectionIndex(m_heading) + 3) % 4];  // 逆时针转90度
    }

    // 取模实现右转
    void TurnRight() {
        static const char directions[] = {'N', 'E', 'S', 'W'};
        m_heading = directions[(FindDirectionIndex(m_heading) + 1) % 4];  // 顺时针转90度
    }

    // 查找索引
    int FindDirectionIndex(char dir) const {
        static const char directions[] = {'N', 'E', 'S', 'W'};
        for (int i = 0; i < 4; ++i) {
            if (directions[i] == dir) {
                return i;
            }
        }
        return -1;  //非法输入
    }
};
