#include "glfw_events.h"

void glfw_events::step(GLFWwindow* glfw)
{
    glfwPollEvents();
    if (glfwGetWindowAttrib(glfw, GLFW_ICONIFIED) != 0)
    {
        ImGui_ImplGlfw_Sleep(10);
    }
}
