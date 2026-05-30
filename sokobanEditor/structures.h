#pragma once

struct GridPoint {
    int x;
    int y;
};

struct Wall {
    GridPoint start;
    GridPoint end;
};