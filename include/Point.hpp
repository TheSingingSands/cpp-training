#pragma once
#include <iostream>

namespace adas
{
struct Point {
    int x = 0, y = 0;

    Point() = default;

    Point(int xCoordinate, int yCoordinate) : x(xCoordinate), y(yCoordinate)
    {
    }

    bool operator==(const Point& otherPoint) const noexcept
    {
        return x == otherPoint.x && y == otherPoint.y;
    }

    void operator+=(const Point& otherPoint) noexcept
    {
        x += otherPoint.x, y += otherPoint.y;
    }

    void operator-=(const Point& otherPoint) noexcept
    {
        x -= otherPoint.x, y -= otherPoint.y;
    }

    Point operator+(const Point& otherPoint) const noexcept
    {
        return {x + otherPoint.x, y + otherPoint.y};
    }

    Point operator-(const Point& otherPoint) const noexcept
    {
        return {x - otherPoint.x, y - otherPoint.y};
    }

    Point operator*(int scalar) const noexcept
    {
        return {scalar * x, scalar * y};
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) noexcept
    {
        return os << point.x << " " << point.y;
    }
};

// 用于表示位置和朝向的结构体
struct Pose {
    Point position;
    char headingDirection;

    Pose() noexcept : position({0, 0}), headingDirection('N')
    {
    }

    explicit Pose(const Point& initialPosition, char initialHeading) noexcept
        : position(initialPosition), headingDirection(initialHeading)
    {
    }

    explicit Pose(int xCoordinate, int yCoordinate, char initialHeading) noexcept
        : position(xCoordinate, yCoordinate), headingDirection(initialHeading)
    {
    }

    bool operator==(const Pose& otherPose) const noexcept
    {
        return position == otherPose.position && headingDirection == otherPose.headingDirection;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pose& pose) noexcept
    {
        return os << "Position: " << pose.position << " Heading: " << pose.headingDirection;
    }
};
}  // namespace adas
