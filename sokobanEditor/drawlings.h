#pragma once
#include <GLFW/glfw3.h>
#include "vec2.h"
#include "structures.h"
#include <vector>
#include "textures.h"

const int segments = 64;
const float radius = 6.0f;
constexpr float cellSize = 40.0f;

void drawPoints(std::vector<Vec2>& circles) {
    glColor3f(1.0f, 0.0f, 1.0f);

    for (auto c : circles) {
        glBegin(GL_TRIANGLE_FAN);

        glVertex2f(c.x, c.y);

        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * 3.1415926f * i / segments;

            float x = c.x + radius * cos(angle);
            float y = c.y + radius * sin(angle);

            glVertex2f(x, y);
        }

        glEnd();
    }

}
void drawGrid(int minX, int maxX,int minY, int maxY) {
    glColor3f(0.0f, 1.0f, 1.0f);

    glLineWidth(0.01f);
    glBegin(GL_LINES);


    for (float x = minX; x < maxX; x += cellSize) {
        for (float y = minY; y < maxY; y += cellSize) {
            glVertex2f(x, y);
            glVertex2f(x + cellSize, y);

            glVertex2f(x + cellSize, y);
            glVertex2f(x + cellSize, y + cellSize);

            glVertex2f(x + cellSize, y + cellSize);
            glVertex2f(x, y + cellSize);

            glVertex2f(x, y + cellSize);
            glVertex2f(x, y);
        }
    }

    glEnd();
}
void drawWalls(std::vector<Wall>& walls) {
    glLineWidth(4.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);

    for (auto& wall : walls)
    {

        glVertex2f(
            wall.start.x,
            wall.start.y);

        glVertex2f(
            wall.end.x,
            wall.end.y);
    }

    glEnd();
}
void drawBox(std::vector<Vec2> boxes) {
    glEnable(GL_TEXTURE_2D);
    GLuint boxTex = 0;
    float h = 40.0f * 0.5f;

    for (auto c : boxes) {
        boxTex = allTextures["box"];
        glBindTexture(GL_TEXTURE_2D, boxTex);

        glColor3f(1.0f, 1.0f, 1.0f);
        glPushMatrix();
        glTranslatef(c.x, c.y, 0.0f);

        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-h, -h);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(h, -h);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(h, h);

        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-h, h);

        glEnd();
        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);
}