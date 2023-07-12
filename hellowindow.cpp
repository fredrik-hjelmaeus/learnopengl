#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "hellowindow.h"
#include <iostream>


// prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int Hellowindow::init()
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

    // loop
    while(!glfwWindowShouldClose(window))
    {
        // register input callback events
        processInput(window);

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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