/* Include openGL libraries */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* Include other libraries */
#include <iostream>

/* Include user defined header files */
#include "openGLFun.h"


int main()
{

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    /* Initialize GLFW */
    openGL::initGLFW();

    /* Create window */
    GLFWwindow *window = glfwCreateWindow(800, 600, "openGL course", NULL, NULL); // Create window
    if (window == NULL)                                                           // Check if window properly created
    {
        std::cout << "Failed to create window!\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Set the current window as current to render

    /* GLAD initialization */
    if (openGL::initGLAD() == -1)
    {
        return -1;
    }

    /* Be ready for resize */
    glfwSetFramebufferSizeCallback(window, openGL::framebuffer_size_callback);

    /* -- SHADERS --*/
    /* -Vertex Shader- */
    /* Vertex shader OpenGL object creating */
    unsigned int vertexShader;  //Int to store vertexShader ID
    openGL::createVertexShader(vertexShader);     //Set shader ID to passed variable by reference 

    /* -Fragment Shader- */
    /* Fragment Shader OpenGL object creating */
    unsigned int fragmentShader; //Int to store fragmentShader ID
    openGL::createFragmentShader(fragmentShader);   //Set shader ID to passed variable by reference

    /* -- SHADER PROGRAM -- */
    /* Create shader program and delete previously created shaders*/
    unsigned int shaderProgram; //Create variable to store shader program ID
    openGL::createShaderProgram(vertexShader,fragmentShader,shaderProgram); //Create shaderProgram and delete shaders

    /* -- GEMOETRY --*/
    /* Define geometry */
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    


    /* --- VAO and EBO and VBO obcjects --- */

    /* VERTEX ARRAY OBJECT (VAO) */
    /* It is simmilar to VBO (Vertex buffer object) but instead of data
    it holds atributes such as size, stride etc. and allows to bind it 
    to some VBOs which allows for fast computing*/
    unsigned int VAO;   //Var to store VAO ID
    glGenVertexArrays(1, &VAO);  //Create VAO Object and store ID
    glBindVertexArray(VAO); //Bind Vertex Array to VAO                                                      1

    /* VBO - Vertex Buffer Objects */
    /* Memory created on GPU where vertex data is being stored */
    /* Sending data from CPU do GPU is slow, so it is faster to send
    data as big package and then vertex shaders has imidiate access 
    making it really fast to perform copmutations */
    /* VBO is a OpenGL object so we create the "pointer" to its 
    real place somewhere it the background */
    unsigned int VBO;   //Create variable to store VBO unique ID
    glGenBuffers(1, &VBO);  //Generate unique VBO ID and set it to variable

    glBindBuffer(GL_ARRAY_BUFFER,VBO);  //Bind VBO buffer to GL_ARRAY_BUFFER
    /* From now performing operations on GL_ARRAY_BUFFER will configure VBO*/
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW); //Send vertices to VBO buffer   2


    /* Element Buffer Objects - EBO */
    /* Used to eliminate reapting vertices.
    EBO is used to store indices that OpenGL
    used to decide what to draw */
    unsigned int indices[] = {
        0,1,3,  //First triangle
        1,2,3   //Second trangle
    };

    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);            //          3
    

    /* Preapre vertices interpretation information */
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);                   //          4
    /*
    First parameter (index) - set to 0 like in vertexShader location 
    Second parametr (size) - set to 3: 3D vector data(x,y,z)
    Third parameter (normalize) - if we want to normalize to (-1,1)
    Forth parameter (stride) - size of one data (3d vector -> 3xfloat)
    Fitht parameter (offset) - offset from the start of array */
    glEnableVertexAttribArray(0);   //Enable the array at location 0

    /* Set mode to wideframe */
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    /* Main loop */
    /* Renders each frame with each iteration */
    while (!glfwWindowShouldClose(window))
    {
        openGL::processInput(window); // Get user input and process it

        /* Start rendering */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set color that will be set with clear command
        glClear(GL_COLOR_BUFFER_BIT);         // Clear the current buffer with some color buffer

        /* Draw vertices */
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        /* End of rendering */

        glfwSwapBuffers(window); // Swap current pixels values for the window
        /* Double buffer
        One buffer is displayed to the user and the second one is being
        build in the background so no flickering is happening while rendering
        pixel by pixel but whole image is being drawn
        */
        glfwPollEvents(); // Check for events (e.g. keyboard interupts etc.) and calls callbacks
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate(); // Clear/delete created objects
    return 0;
}

