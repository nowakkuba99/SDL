/* Include openGL libraries */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* Include openGL math functions */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Include other libraries */
#include <iostream>
#include <math.h>

/* Include user defined header files */
#include "shader.h"
#include "camera.hpp"

/* Map general information */
#define MAP_SIZE (10.0f)
#define MAP_NUM_VERTICES (80)
#define MAP_NUM_TOTAL_VERTICES (MAP_NUM_VERTICES*MAP_NUM_VERTICES)
#define MAP_NUM_LINES (3* (MAP_NUM_VERTICES - 1) * (MAP_NUM_VERTICES - 1) + \
               2 * (MAP_NUM_VERTICES - 1))

/* Callback functions prototypes */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window, float deltaTime);

/* Global varialbes for camera pouropses */
Camera globalCamera(glm::vec3(0.0f,0.0f,3.0f));   // Create Camera object
float lastX=400, lastY=300;
bool firstMouse = true;

/* Heightmap vertex and index data */
static GLfloat map_vertices[3][MAP_NUM_TOTAL_VERTICES];
static GLuint  map_line_indices[2*MAP_NUM_LINES];




int main()
{
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    /* Initialize GLFW */
    glfwInit();                                                    // Initialize GLFW library
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // Set openGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // Set openGL version to 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set openGL profile to core profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Set for MAC OS to set window forward
    /* Create window */
    GLFWwindow *window = glfwCreateWindow(800, 600, "Wave Equation Solution", NULL, NULL); // Create window
    if (window == NULL)                                                           // Check if window properly created
    {
        std::cout << "Failed to create window!\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Set the current window as current to render

    /* GLAD initialization */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }
    
    /* Be ready for resize */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* SHADER PROGRAM USING SHADER CLASS */
    Shader programShader("path/shader/vertexShader.vs", "path/shader/fragmentShader.fs");

    /* Geometry */
    float vertices[] = {
        //Vertexes          //Colors            
         0.5f,  0.5f, 0.0f,  0.1f, 0.5f, 0.2f,    // top right
         0.5f, -0.5f, 0.0f,  0.1f, 0.5f, 0.2f,    // bottom right
        -0.5f, -0.5f, 0.0f,  0.1f, 0.5f, 0.2f,    // bottom left
        -0.5f,  0.5f, 0.0f,  0.1f, 0.5f, 0.2f,    // top left 
    };

    unsigned int indices[] = {
        0,1,2,  //First triangle
        0,2,3   //Second triangle
    };



    /* --- VAO, EBO and VBO obcjects --- */
    /* VERTEX ARRAY OBJECT (VAO) */
    unsigned int VAO;   //Var to store VAO ID
    glGenVertexArrays(1, &VAO);  //Create VAO Object and store ID
    glBindVertexArray(VAO); //Bind Vertex Array to VAO  
    /* VBO - Vertex Buffer Objects */
    unsigned int VBO;   //Create variable to store VBO unique ID
    glGenBuffers(1, &VBO);  //Generate unique VBO ID and set it to variable
    glBindBuffer(GL_ARRAY_BUFFER,VBO);  //Bind VBO buffer to GL_ARRAY_BUFFER
    /* EBO - Element Buffer objects */
    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW); //Send vertices to VBO buffer

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)0);  //Set attribute 0 - vertixes
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(0);   //Enable the array at location 1
    glEnableVertexAttribArray(1);   //Enable the array at location 1
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    programShader.makeActive();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(globalCamera.m_Zoom),800.0f/600.0f,0.1f,100.f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model,glm::radians(-70.0f),glm::vec3(1.0f,0.0f,0.0f));
    int modelLoc = glGetUniformLocation(programShader.shaderProgramID, "model");
    int viewLoc = glGetUniformLocation(programShader.shaderProgramID, "view");
    int projectionLoc = glGetUniformLocation(programShader.shaderProgramID, "projection");

    /* Enalbe depth testing */
    glEnable(GL_DEPTH_TEST);
    
    glm::mat4 view;
    float deltaTime = 0.0f;    //Time between 2 frames
    float lastFrame = 0.0f;    //Time of last frame

    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);  //Hide mouse and capture it
    glfwSetCursorPosCallback(window,mouseCallback);
    glfwSetScrollCallback(window,scrollCallback);

    /* Main loop */
    /* Renders each frame with each iteration */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window,deltaTime);
        /* Start rendering */
        programShader.makeActive();
        glBindVertexArray(VAO);                             //Bind the atributes
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set color that will be set with clear command
        glClear(GL_COLOR_BUFFER_BIT);         // Clear the current buffer with some color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the depth buffer


        /* Camera handling */
        view = globalCamera.getViewMatrix();
        projection = glm::perspective(glm::radians(globalCamera.m_Zoom),800.0f/600.0f,0.1f,100.f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        float currentFrame = glfwGetTime();
        deltaTime = currentFrame-lastFrame;
        lastFrame = currentFrame;
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        //glDrawArrays(GL_TRIANGLES,0,6);
        glBindVertexArray(0);
        /* End of rendering */

        glfwSwapBuffers(window); // Swap current pixels values for the window
        /* Double buffer
        One buffer is displayed to the user and the second one is being
        build in the background so no flickering is happening while rendering
        pixel by pixel but whole image is being drawn
        */
        glfwPollEvents(); // Check for events (e.g. keyboard interupts etc.) and calls callback
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    

    glfwTerminate(); // Clear/delete created objects
    return 0;
}

/**********************************************************************
 * Callback functions
 *********************************************************************/

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height); // Set ViewPort to proper values
}
void mouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos-lastX;
    float yoffset = lastY-ypos; //Reversed since y axis is goin up
    lastX = xpos;
    lastY = ypos;
    
    globalCamera.processMouseAction(xoffset,yoffset,true);
}
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    globalCamera.processScrollAction(yoffset);
}
void processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // If ESC pressed
    {
        glfwSetWindowShouldClose(window, true); // Set flag to close window
    }
    else
    {
        if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
        {
            globalCamera.processKeyboardAction(camera::FORAWRD,deltaTime);
        }
        
        if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
        {
            globalCamera.processKeyboardAction(camera::BACKWARD,deltaTime);
        }

        if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
        {
            globalCamera.processKeyboardAction(camera::LEFT,deltaTime);
        }

        if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
        {
            globalCamera.processKeyboardAction(camera::RIGHT,deltaTime);
        }
    }
}

/**********************************************************************
 * Geometry creation functions
 *********************************************************************/

/* Generate vertices and indices for the heightmap
 */
static void init_map(void)
{
    int i;
    int j;
    int k;
    GLfloat step = MAP_SIZE / (MAP_NUM_VERTICES - 1);
    GLfloat x = 0.0f;
    GLfloat z = 0.0f;
    /* Create a flat grid */
    k = 0;
    for (i = 0 ; i < MAP_NUM_VERTICES ; ++i)
    {
        for (j = 0 ; j < MAP_NUM_VERTICES ; ++j)
        {
            map_vertices[0][k] = x;
            map_vertices[1][k] = 0.0f;
            map_vertices[2][k] = z;
            z += step;
            ++k;
        }
        x += step;
        z = 0.0f;
    }
#if DEBUG_ENABLED
    for (i = 0 ; i < MAP_NUM_TOTAL_VERTICES ; ++i)
    {
        printf ("Vertice %d (%f, %f, %f)\n",
                i, map_vertices[0][i], map_vertices[1][i], map_vertices[2][i]);

    }
#endif
    /* create indices */
    /* line fan based on i
     * i+1
     * |  / i + n + 1
     * | /
     * |/
     * i --- i + n
     */

    /* close the top of the square */
    k = 0;
    for (i = 0 ; i < MAP_NUM_VERTICES  -1 ; ++i)
    {
        map_line_indices[k++] = (i + 1) * MAP_NUM_VERTICES -1;
        map_line_indices[k++] = (i + 2) * MAP_NUM_VERTICES -1;
    }
    /* close the right of the square */
    for (i = 0 ; i < MAP_NUM_VERTICES -1 ; ++i)
    {
        map_line_indices[k++] = (MAP_NUM_VERTICES - 1) * MAP_NUM_VERTICES + i;
        map_line_indices[k++] = (MAP_NUM_VERTICES - 1) * MAP_NUM_VERTICES + i + 1;
    }

    for (i = 0 ; i < (MAP_NUM_VERTICES - 1) ; ++i)
    {
        for (j = 0 ; j < (MAP_NUM_VERTICES - 1) ; ++j)
        {
            int ref = i * (MAP_NUM_VERTICES) + j;
            map_line_indices[k++] = ref;
            map_line_indices[k++] = ref + 1;

            map_line_indices[k++] = ref;
            map_line_indices[k++] = ref + MAP_NUM_VERTICES;

            map_line_indices[k++] = ref;
            map_line_indices[k++] = ref + MAP_NUM_VERTICES + 1;
        }
    }

#ifdef DEBUG_ENABLED
    for (k = 0 ; k < 2 * MAP_NUM_LINES ; k += 2)
    {
        int beg, end;
        beg = map_line_indices[k];
        end = map_line_indices[k+1];
        printf ("Line %d: %d -> %d (%f, %f, %f) -> (%f, %f, %f)\n",
                k / 2, beg, end,
                map_vertices[0][beg], map_vertices[1][beg], map_vertices[2][beg],
                map_vertices[0][end], map_vertices[1][end], map_vertices[2][end]);
    }
#endif
}