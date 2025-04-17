#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

// Custom function to create a perspective projection matrix
void perspective(float fovY, float aspect, float zNear, float zFar, float* matrix) {
    float f = 1.0f / tan(fovY * 0.5f * 3.14159265f / 180.0f); // convert degrees to radians
    matrix[0] = f / aspect;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = (zFar + zNear) / (zNear - zFar);
    matrix[11] = -1.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = (2.0f * zFar * zNear) / (zNear - zFar);
    matrix[15] = 0.0f;
}

void drawCube() {
    glBegin(GL_QUADS);

    // Front
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back
    glColor3f(0, 1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Top
    glColor3f(0, 0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    // Bottom
    glColor3f(1, 1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Right
    glColor3f(1, 0, 1);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Left
    glColor3f(0, 1, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Miniverse", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    glEnable(GL_DEPTH_TEST);

    float angle = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Projection matrix
        float proj[16];
        perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f, proj);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(proj);

        // Modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -3.0f);
        glRotatef(angle, 1.0f, 1.0f, 0.0f);

        drawCube();

        glfwSwapBuffers(window);
        glfwPollEvents();

        angle += 0.02f;
    }

    glfwTerminate();
    return 0;
}