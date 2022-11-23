#ifndef B0726C13_7480_403E_8594_FA5F9ABA905E
#define B0726C13_7480_403E_8594_FA5F9ABA905E
#include <glad/glad.h>
#include <GLFW/glfw3.h>


/* Include openGL math functions */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Include other libraires */
#include "shader.h"
#include "camera.hpp"

/* Global Variables for callbacks */
// extern float lastX, lastY;
// // extern float yaw;
// // extern float pitch;
// // extern glm::vec3 cameraFront;
// extern bool firstMouse;
// extern float fov;
// extern std::unique_ptr<Camera> globalCamPointer;
// extern std::unique_ptr<Shader> globalShaderPointer;


class Application
{
public:
    /* --Define functions for openGL-- */
    /* -Callback functions- */
    // Callback for resizing window
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    // Callback for user input
    void processInput(GLFWwindow *window, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp, float deltaTime);
    // Callback for mouse input
    //void mouseCallback(GLFWwindow *window, double xpos, double ypos);
    /* Initialization functions */
    void initGLFW();
    int initGLAD();
};

#endif /* B0726C13_7480_403E_8594_FA5F9ABA905E */
