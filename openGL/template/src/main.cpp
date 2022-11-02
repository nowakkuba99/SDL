/* Include openGL libraries */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* Include other libraries */
#include <iostream>
#include <math.h>

/* Include image loader library */
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

/* Include user defined header files */
#include "openGLFun.h"
#include "shader.h"


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

    /* SHADER PROGRAM USING SHADER CLASS */
    Shader shaderProgram("path/shader/vertexShader.vs", "path/shader/fragmentShader.fs");
    
    
    /* -- GEMOETRY -- */
    /* Define geometry */
    float vertices[] = {
        //Vertexes          //Colors            //Texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,    // top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,    // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,    // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f,    // top left 
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   0.5f, 1.0f     // middle
    };
    
    /* -- TEXTURES -- */
    /* Load image from file */
    int width, height, nrChannels;
    unsigned char* data = stbi_load("resources/textures/container.jpg",&width,&height,&nrChannels,0);

    /* Create texture object */
    unsigned int texture;
    glGenTextures(1,&texture);  //Genereate 1 texture object
    glBindTexture(GL_TEXTURE_2D, texture);  //Bind texture as 2D texture

    /* Set texture parameters */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Generate texture from image */
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);   //Load image to texture
    glGenerateMipmap(GL_TEXTURE_2D);

    /* Delete image from memmory */
    stbi_image_free(data);



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
        //1,2,4  //One triangle
        0,1,3,  //First triangle
        1,2,3   //Second triangle
    };

    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);            //          3
    

    /* Preapre vertices interpretation information */
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);                   //          4
    /*
    First parameter (index) - set to 0 like in vertexShader location 
    Second parametr (size) - set to 3: 3D vector data(x,y,z)
    Third parameter (normalize) - if we want to normalize to (-1,1)
    Forth parameter (stride) - size of one data (3d vector + 3d color-> 6xfloat)
    Fitht parameter (offset) - offset from the start of array */
    glEnableVertexAttribArray(0);   //Enable the array at location 0

    //Color
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);   //Enable the array at location 1

    //Texture
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(6*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);

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
        //glUseProgram(shaderProgram);
        shaderProgram.makeActive();

        glBindVertexArray(VAO);                             //Bind the atributes
        glBindTexture(GL_TEXTURE_2D, texture);              //Bind the texture to the sampler
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
    

    glfwTerminate(); // Clear/delete created objects
    return 0;
}

