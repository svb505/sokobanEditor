#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "structures.h"
#include "vec2.h"

void saveAll(const std::string& path, int current,std::vector<Wall>& walls, std::vector<Vec2>& boxes,
    std::vector<Vec2>& circles);
