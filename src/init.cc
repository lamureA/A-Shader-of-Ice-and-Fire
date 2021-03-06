#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "init.hh"

namespace Init
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void init_glfw()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    GLFWwindow *init_window(int width, int height)
    {
        GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL - A Shader of Ice and Fire", NULL, NULL);
        if (window == NULL)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw std::exception();
        }
        glfwMakeContextCurrent(window);
        return window;
    }

    void init_glad()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            throw std::exception();
        }
    }

    GLFWwindow *init_all(int width, int height)
    {
        // init GLFW
        init_glfw();

        // init GLFW window
        GLFWwindow *window = init_window(width, height);

        // set mouse input options for GLFW
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // init GLAD
        init_glad();

        // Set OpenGL options
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
        glEnable(GL_CLIP_DISTANCE0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // Patch option
        glPatchParameteri(GL_PATCH_VERTICES, 3);

        // tell the size of window to openGL
        glViewport(0, 0, width, height);

        // set resize callback
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        return window;
    }
}