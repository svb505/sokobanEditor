#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "structures.h"
#include <vector>
#include "saveToJson.h"
#include "vec2.h"

void setupGui(GLFWwindow* window){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui::StyleColorsDark();
}
void destroyGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
void renderGui(std::string mode,std::vector<Wall>& walls, std::vector<Vec2>& boxes, 
    std::vector<Vec2>& circles) {
    ImGui::Begin("Level editor");
    ImGui::Text("Current mode: %s", mode);
    ImGui::Text("Key B - Boxes mode");
    ImGui::Text("Key C - Circles mode");
    ImGui::Text("Key L - Lines mode");

    if (ImGui::Button("Save")) saveAll("maze.json",walls,boxes,circles);

    ImGui::Text("Walls count: %d", (int)walls.size());

    ImGui::End();
}
