#pragma once

enum class Result {
    Success,
    Failure
};

enum class Direction {
    Left,
    Right,
    Up,
    Down
};

struct Coord {
    Coord(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    int x;
    int y;
    Coord move(Direction dir) const {
        switch(dir) {
        case Direction::Left:
            return Coord(x - 1, y);
        case Direction::Right:
            return Coord(x + 1, y);
        case Direction::Up:
            return Coord(x, y + 1);
        case Direction::Down:
            return Coord(x, y - 1);
        default:
            return *this;
        }
    }
    bool operator==(Coord cc) const {
        return x == cc.x && y == cc.y;
    }

    bool operator<(Coord cc) const {
        return x == cc.x ? y < cc.y : x < cc.x;
    }
};
