#include "saveToJson.h"
#include <nlohmann//json.hpp>

#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "structures.h"
#include "vec2.h"
#include <fstream>

using json = nlohmann::json;

void saveAll(const std::string& path, std::vector<Wall>& walls, std::vector<Vec2>& boxes,
    std::vector<Vec2>& circles)
{
    json root;

    for (auto& wall : walls){
        root["walls"].push_back({
            {"x1", wall.start.x},
            {"y1", wall.start.y},
            {"x2", wall.end.x},
            {"y2", wall.end.y}
            });
    }
    for (auto& box : boxes) root["boxes"].push_back({ box.x,box.y });
    for (auto& circle : circles) root["circles"].push_back({ circle.x,circle.y });

    std::ofstream file(path);

    file << root.dump(4);
}
