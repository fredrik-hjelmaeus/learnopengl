#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "hellotriangle.h"
#include <iostream>


// prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int Hellotriangle::init()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); 
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl; 
        return -1;
    }

    // Viewport
    // register callback so it resize viewpoer when window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Vertex input with indices prepared for indexed draws
    float vertices[] = {
       0.5f, 0.5, 0.0f, // top right
       0.5f, -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f, 0.0f // top left  
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    // Send vertex data to graphics card
    
        ///////////////////////////
        // Vertex Array Object ////
        ///////////////////////////
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);

        // bind vertex array object (VAO)
        glBindVertexArray(VAO);

        ///////////////////////////
        // Vertex buffer object ///
        ///////////////////////////
        unsigned int VBO;
        glGenBuffers(1, &VBO);

        // bind buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // copy vertices into buffer memory
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        ///////////////////////////
        // Element buffer object //
        ///////////////////////////
        unsigned int EBO;
        glGenBuffers(1, &EBO);

        // bind buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // copy indices into buffer memory
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
    

    // Process vertex data on graphics card
    
        /////////////////////////////////
        // Vertex Shader ////////////////
        /////////////////////////////////
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

        // shader object
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // attach shader source code to shader object
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

        // compile shader
        glCompileShader(vertexShader);

        // check for compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            // get error message
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

            // print error message
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        /////////////////////////////////
        // Fragment Shader //////////////
        /////////////////////////////////
        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0";
        
        // shader object
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // attach shader source code to shader object
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

        // compile shader
        glCompileShader(fragmentShader);

        // check for compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            // get error message
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

            // print error message
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        /////////////////////////////////
        // Shader Program ///////////////
        /////////////////////////////////
        
        // shader program object
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();

        // attach shaders to program
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        // link program
        glLinkProgram(shaderProgram);

        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success)
        {
            // get error message
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

            // print error message
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // activate the shader program object
        glUseProgram(shaderProgram);

        // delete shader objects ( no longer needed )
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        /////////////////////////////////////////////////
        // tell opengl how to interpret vertex data /////
        /////////////////////////////////////////////////
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        // enable vertex attribute
        glEnableVertexAttribArray(0);

    // draw in wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // loop
    while(!glfwWindowShouldClose(window))
    {
        // register input callback events
        processInput(window);

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw 
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // double buffer
        glfwSwapBuffers(window);
        
        // check for input events
        glfwPollEvents();
    }

    // clean up glfw
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    // Close on escape key
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}