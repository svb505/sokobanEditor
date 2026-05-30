#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cmath>
#include "structures.h"
#include "vec2.h"
#include "drawlings.h"
#include "GUI.h"

std::vector<Wall> walls;
std::vector<Vec2> boxes;
std::vector<Vec2> circles;

bool firstPointSelected = false;
GridPoint selectedPoint;

constexpr int gridWidth = 200;
constexpr int gridHeight = 200;
constexpr float minX = -200;
constexpr float maxX = 200;
constexpr float minY = -200;
constexpr float maxY = 200;

std::string mode = "Lines";

GridPoint snapToCenters(float worldX, float worldY)
{
    int array[20] = { -180,-160,-140,-120,-100,-80,-60,-40,-20,0,20,40,60,80,100,120,140,
        160,180 };

    int closestX = 0;
    int closestY = 0;

    float bestDX = std::abs(array[0] - worldX);
    float bestDY = std::abs(array[0] - worldY);

    for (int i = 0; i < 20; i++)
    {
        float dx = std::abs(worldX - array[i]);
        if (dx < bestDX)
        {
            bestDX = dx;
            closestX = i;
        }
    }

    for (int i = 0; i < 20; i++)
    {
        float dy = std::abs(worldY - array[i]);
        if (dy < bestDY)
        {
            bestDY = dy;
            closestY = i;
        }
    }

    return {
        array[closestX],
        array[closestY]
    };
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) mode = "Lines";
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) mode = "Circles";
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) mode = "Boxes";
}
GridPoint mouseToGrid(GLFWwindow* window,double mouseX, double mouseY){
    int width;
    int height;

    glfwGetWindowSize(window, &width, &height);

    float worldX = minX + (mouseX / width) * (maxX - minX);

    float worldY = maxY - (mouseY / height) * (maxY - minY);

    int array[10] = { -180,-140,-100,-60,-20,20,60,100,140,180 };

    int bufX = abs(array[0] - worldX);
    int bufY = abs(array[0] - worldY);
    int minX = 0;
    int minY = 0;

    for (int i = 0; i < 10; i++) {
        if (bufX > (abs(worldX - array[i]))) {
            minX = i; 
            bufX = abs(array[i] - worldX);
        }
    }
    for (int i = 0; i < 10; i++) {
        if (bufY > (abs(worldY - array[i]))) {
            minY = i;
            bufY = abs(array[i] - worldY);
        }
    }

    worldX = array[minX];
    worldY = array[minY];

    GridPoint point;

    point.x = static_cast<int>(worldX);
    point.y = static_cast<int>(worldY);

    return point;
}
bool isInsideGrid(const GridPoint& p)
{
    return
        p.x >= minX &&
        p.x <= maxX &&
        p.y >= minY &&
        p.y <= maxY;
}
bool isValidWall(const GridPoint& start,const GridPoint& end){
    bool vertical =
        start.x == end.x;

    bool horizontal =
        start.y == end.y;

    return vertical || horizontal;
}
void onGridClick(GridPoint point)
{
    if (!isInsideGrid(point)) return;

    if (mode == "Boxes"){
        GridPoint snapped = snapToCenters(point.x, point.y);
        boxes.push_back({ snapped.x, snapped.y });
        return;
    }

    if (mode == "Circles"){
        GridPoint center = snapToCenters(point.x, point.y);
        circles.push_back({ center.x, center.y });
        return;
    }

    if (!firstPointSelected){
        selectedPoint = point;
        firstPointSelected = true;
        return;
    }

    if (!isValidWall(selectedPoint, point)){
        firstPointSelected = false;
        return;
    }

    walls.push_back({ selectedPoint, point });

    firstPointSelected = false;
}
int main(){
    if (!glfwInit()){
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(1200, 900, "Soban Editor", NULL, NULL);
    if (!window){
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200, 200, -200, 200, -200, 200);
    glMatrixMode(GL_MODELVIEW);

    LoadAllTextures();

    setupGui(window);

    static bool wasPressed = false;

    while (!glfwWindowShouldClose(window)){
        processInput(window);

        bool pressed =  glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

        if (pressed && !wasPressed){
            double mx;
            double my;

            glfwGetCursorPos(window, &mx, &my);

            GridPoint point = mouseToGrid(window,mx,my);

            onGridClick(point);
        }

        wasPressed = pressed;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderGui(mode,walls,boxes,circles);

        ImGui::Render();

        glClear(GL_COLOR_BUFFER_BIT);

        drawGrid(minX,maxX,minY,maxY);
        drawWalls(walls);
        drawBox(boxes);
        drawPoints(circles);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    destroyGui();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

