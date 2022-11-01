#include <iostream>

#include"openGLFun.h"


/* OpenGL specific function bodies */
/* ----------------------------------- */
/* Resize buffer size while window size changed */
void openGL::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height); // Set ViewPort to proper values
}

/* Process user input given by key presses */
void openGL::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // If ESC pressed
    {
        glfwSetWindowShouldClose(window, true); // Set flag to close window
    }
}

/* Initliazie OpenGL v. 3.3 */
void openGL::initGLFW()
{
    /* Initialize GLFW */
    glfwInit();                                                    // Initialize GLFW library
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // Set openGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // Set openGL version to 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set openGL profile to core profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Set for MAC OS to set window forward
}

/* Initliaze GLAD */
int openGL::initGLAD()
{
    /* GLAD initialization */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }
    return 0;
}

/* Create basic vertex shader 
Parameters: unsigned int& vertexShader - variable to set shader ID to
Returns: -
*/
void openGL::createVertexShader(unsigned int& vertexShader)
{
    /* Now data is in GPU and vertex shader and fragment shader need to be created */
    /* VERTEX SHADER */
    /* Vertex shader need to be created in GLSL (OpenGL Shader Language) and
    needs to be defined for each OpenGl project - there is no default*/
    /* Vertex shader source code in GLSL */
    const char *vertexShaderSource = "#version 330 core\n"  //Open GL version 3.3
    "layout (location = 0) in vec3 aPos;\n"     //Set location to 0 and read input as 3D vector(x,y,z)
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" //Bind input data to gl_position (output) as 4D vector(x,y,z,w)
    "}\0";
    /* Vertex shader OpenGL object creating */
    vertexShader = glCreateShader(GL_VERTEX_SHADER);    //Create Vertex Shader object
    /* Attach the source code and compile */
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    /* Check if compilation is successful */
    int vertexShaderCompileStatus;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&vertexShaderCompileStatus);
    if(!vertexShaderCompileStatus)
    {
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
    }
}

/* Create basic fragment shader 
Parameters: unsigned int& vertexShader - variable to set shader ID to
Returns: -
*/
void openGL::createFragmentShader(unsigned int& fragmentShader)
{
    /* FRAGMENT SHADER */
    /* Fragment is all of a data needed to render a single pixel */
    /* It is used to calculate the color of pixels */
    /* Colors represented by: R,G,B, Opacity - nieprzezroczystość */
    /* Fragment shader source code */
    const char *fragmentShaderSource = "#version 330 core\n"    //openGl ver. 3.3
    "out vec4 FragColor;\n"     //Output 4D vector
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"    //Set output as constant color
    "}\n\0";
    /* Create OpenGL object - fragment shader */
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    /* Attach source and compile */
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    /* Check if compilation successful */
    int fragmentShaderCompileStatus;
    char infoLog[512];
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&fragmentShaderCompileStatus);
    if(!fragmentShaderCompileStatus)
    {
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
    }
}
/* Create basic shader Program
Parameters: vertexShader reference, fragmentShader reference, shaderProgram variable reference 
Returns: -
*/
void openGL::createShaderProgram(unsigned int &vertexShader, unsigned int &fragmentShader, unsigned int &shaderProgram)
{
    /* After few shaders are compiled we need to link them to the
    Shader program to run them while using app*/

    /* SHADER PROGRAM */
    /* While creating shader program we create a pipeline where we link 
    outputs of some shaders to inputs of another. Thats why link errors 
    may be created during the process*/
    shaderProgram = glCreateProgram();  //Create shader program object and store ID in var

    /* Attach shaders */
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    /* Link program */
    glLinkProgram(shaderProgram);
    /* Check if compilation successful */
    int shaderProgramCompileStatus;
    char infoLog[512];
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&shaderProgramCompileStatus);
    if(!shaderProgramCompileStatus)
    {
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    }

    /* Activate shaderProgram */
    glUseProgram(shaderProgram);

    /* Delete shader objects - already linked */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}