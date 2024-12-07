#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>

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

// ICommand抽象类
class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void DoOperate(class Executor& executor) const noexcept= 0;
};

//四种命令对于ICommand的继承
class MoveCommand final: public ICommand {
public:
    void DoOperate(Executor& executor) const noexcept override;
};

class TurnLeftCommand final: public ICommand {
public:
    void DoOperate(Executor& executor)const noexcept override;
};

class TurnRightCommand final: public ICommand {
public:
    void DoOperate(Executor& executor)const noexcept override;
};

class FastCommand final: public ICommand {
public:
    void DoOperate(Executor& executor)const noexcept override;
};

class BackCommand final: public ICommand{
public:
    void DoOperate(Executor& executor)const noexcept override;
};
// Executor 类
class Executor {
public:
    // 静态工厂方法，返回 Executor 实例
    static Executor* NewExecutor() {
        return new Executor();
    }

    // 这里让测试代码中的写法相对统一
    static Executor* NewExecutor(int32_t x, int32_t y, char heading, bool isAccelerating = false, bool isBack = false) {
        return new Executor(x, y, heading, isAccelerating, isBack); 
    }

    // 默认构造函数
    Executor() : m_x(0), m_y(0), m_heading('N'), m_isAccelerating(false),m_isBack(false) {}

    // 带参构造函数
    Executor(int32_t x, int32_t y, char heading, bool isAccelerating = false,bool isBack = false) 
        : m_x(x), m_y(y), m_heading(heading), m_isAccelerating(isAccelerating), m_isBack(isBack) {}

    // 初始化接口
    void Initialize(int32_t x, int32_t y, char heading) {
        m_x = x;
        m_y = y;
        m_heading = heading;
        m_isAccelerating = false;   // 默认不加速
        m_isBack = false;   //默认不倒车
    }

    // 执行指令接口（批量执行）
    void ExecuteCommands(const std::string &commands) {
        for (char command : commands) {
            ICommand* cmd = nullptr;
            switch (command) {
                case 'M': cmd = new MoveCommand(); break;
                case 'L': cmd = new TurnLeftCommand(); break;
                case 'R': cmd = new TurnRightCommand(); break;
                case 'F': cmd = new FastCommand(); break;
                case 'B': cmd = new BackCommand(); break;
                default: break;  // 不处理非法指令
            }
            if (cmd) {
                cmd->DoOperate(*this);
                delete cmd;
            }
        }
    }

    // 查询当前状态
    Pose Query() const {
        return Pose{m_x, m_y, m_heading};
    }

private:
    int32_t m_x;
    int32_t m_y;
    char m_heading;
    bool m_isAccelerating;
    bool m_isBack;
    // 加速状态切换
    void Fast_Mode_Switch() {
        m_isAccelerating = !m_isAccelerating;
    }

    //倒车状态切换
    void Back_Mode_Switch() {
        m_isBack = !m_isBack;
    }

    void Move(int steps) {
        switch (m_heading) {
            case 'N': m_y += steps; break;
            case 'S': m_y -= steps; break;
            case 'E': m_x += steps; break;
            case 'W': m_x -= steps; break;
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

    friend class MoveCommand;
    friend class TurnLeftCommand;
    friend class TurnRightCommand;
    friend class FastCommand;
    friend class BackCommand;
};

// MoveCommand 的实现
void MoveCommand::DoOperate(Executor& executor) const noexcept{
    if(executor.m_isBack == false){
        if(executor.m_isAccelerating){executor.Move(1);}  // 如果是加速状态，先前进1格
        executor.Move(1);    //再前进一格
    }else{
        if(executor.m_isAccelerating){executor.Move(-1);}
        executor.Move(-1);   //再后退一格
    }
    
}

// TurnLeftCommand 的实现
void TurnLeftCommand::DoOperate(Executor& executor)const noexcept {
    if(executor.m_isBack == false){
        if(executor.m_isAccelerating){executor.Move(1);}  // 如果是加速状态，先前进1格
        executor.TurnLeft();  // 然后左转
    }else{
        if(executor.m_isAccelerating){executor.Move(-1);}
        executor.TurnRight();   //右转90度
    }
}

// TurnRightCommand 的实现
void TurnRightCommand::DoOperate(Executor& executor)const noexcept {
    if(executor.m_isBack == false){
        if(executor.m_isAccelerating){executor.Move(1);}  // 如果是加速状态，先前进1格
        executor.TurnRight();  // 然后右转
    }else{
        if(executor.m_isAccelerating){executor.Move(-1);}
        executor.TurnLeft();   //左转90度
    }

}

// FastCommand 的实现
void FastCommand::DoOperate(Executor& executor)const noexcept {
    executor.Fast_Mode_Switch();  // 切换加速状态
}
// BackCommand 的实现
void BackCommand::DoOperate(Executor& executor)const noexcept {
    executor.Back_Mode_Switch();    //切换倒车状态
}