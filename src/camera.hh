#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    float fov;

    float speed; // motion speed (translation)
    float sensitivity; // rotation speed

    float yaw; // rotation around Y axis
    float pitch; // rotation around X axis

    float last_mouse_x;
    float last_mouse_y;
    glm::vec2 mouse_pos;

    bool first_mouse_move; // to handle the big jump on the first mouse movement

    Camera();
    void invert_pitch();
};