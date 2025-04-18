/**
* Importing Graphics Modules
**/
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* Importing built-in modules
**/
#include <iostream>
#include <vector>
#include <functional>
#include <limits>
#include <cmath> 
#include <map>
#include <string>
#include <cstdlib>

/**
* Importing visualizations
**/
#include "visualizations/RotatingCube.h" // Add more files here as you build

/**
* Struct representing a math visualization
**/
struct Visualization {

    std::map<std::string, std::string> programInfo;
    std::function<void()> render;
    bool isEnabled;
};

/**
* All available visualizations listed here
**/
std::vector<Visualization> visualizations = {
    { getRotatingCubeInfo(), runRotatingCube, true},

    // Add more visualizations here
};

void showBanner() {
    std::cout << "Graphamatics (Version 1.0.0) / By 'Dinesh' \n \n";
}

/**
* Custom perspective matrix calculation (replacement for gluPerspective)
**/
void perspective(float fovY, float aspect, float zNear, float zFar, float* matrix) {
    float f = 1.0f / tan(fovY * 0.5f * 3.14159265f / 180.0f);
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

/** User Input Key Processing */
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_S && (mods & GLFW_MOD_CONTROL)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

/**
* Find the viusalization which is enabled
**/
int getEnabledVisualization() {
    int selected = -1;

    std::cout << "[INFO] Finding the Enabled Visualization .... \n";

    for (size_t i = 0; i < visualizations.size(); ++i) {
        if (visualizations[i].isEnabled == true) {
            selected = i;
        }
    }

    std::cout << "[INFO] Rendering the Visualization : " << visualizations[selected].programInfo["Name"] << "\n";
    
    return selected;
}


/**
* Run a single visualization in its own loop; exit back to menu on ESC
**/
void runVisualization(GLFWwindow* window, const Visualization& visualization) {

    while (!glfwWindowShouldClose(window)) {
        // Exit visualization if ESC is pressed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float proj[16];
        perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f, proj);
        glLoadMatrixf(proj);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -3.0f);
       
        visualization.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clear ESC key state before going back
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwPollEvents();
    }
}

/**
* Main function
**/
int main() {
    showBanner();

    if (!glfwInit()) return -1;

    // Get the primary monitor and its video mode
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    // Create full screen window using primary monitor's resolution
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Graphametics", primary, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }


    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_DEPTH_TEST);


    // Set viewport to match full screen dimensions
    glViewport(0, 0, mode->width, mode->height);

    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window)) {
        int selected = getEnabledVisualization();
        runVisualization(window, visualizations[selected]);
    }

    glfwTerminate();
    return 0;
}