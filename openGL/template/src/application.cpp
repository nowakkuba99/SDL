#include <iostream>

#include "appliaction.h"


// /* Global Variables definition */
// float lastX=400, lastY=300;
// // float yaw = -90.0f;
// // float pitch = 0.0f;
// // glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// bool firstMouse = true;
// //void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
// float fov = 45.0f;
// std::unique_ptr<Shader> globalShaderPointer =  std::unique_ptr<Shader> (new Shader("path/shader/vertexShader.vs", "path/shader/fragmentShader.fs"));
// std::unique_ptr<Camera> globalCamPointer = std::unique_ptr<Camera> (new Camera());


/* OpenGL specific function bodies */
/* ----------------------------------- */
/* Resize buffer size while window size changed */
void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height); // Set ViewPort to proper values
}

/* Process user input given by key presses */
void Application::processInput(GLFWwindow *window, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp, float deltaTime)
{
    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // If ESC pressed
    {
        glfwSetWindowShouldClose(window, true); // Set flag to close window
    }
    else
    {
        if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
        {
            cameraPos += cameraSpeed * cameraFront;
        }
        
        if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
        {
            cameraPos -= cameraSpeed * cameraFront;
        }

        if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
        {
            cameraPos -= glm::normalize(glm::cross(cameraFront,cameraUp)) * cameraSpeed;
        }

        if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
        {
            cameraPos += glm::normalize(glm::cross(cameraFront,cameraUp)) * cameraSpeed;
        }
    }
}
//void openGL::mouseCallback(GLFWwindow *window, double xpos, double ypos);

/* Initliazie OpenGL v. 3.3 */
void Application::initGLFW()
{
    /* Initialize GLFW */
    glfwInit();                                                    // Initialize GLFW library
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // Set openGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // Set openGL version to 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set openGL profile to core profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Set for MAC OS to set window forward
}

/* Initliaze GLAD */
int Application::initGLAD()
{
    /* GLAD initialization */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }
    return 0;
}
/*
void Application::mouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    if (m_FirstMouse) // initially set to true
    {
        m_LastX = xpos;
        m_LastY = ypos;
        m_FirstMouse = false;
    }

    float xoffset = xpos-m_LastX;
    float yoffset = m_LastY-ypos; //Reversed since y axis is goin up
    m_LastX = xpos;
    m_LastY = ypos;

    if(p_Camera != nullptr)
        p_Camera.get()->processMouseAction(xoffset,yoffset,true);
}

void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(p_Camera != nullptr)
        p_Camera.get()->processScrollAction(yoffset);
}
*/