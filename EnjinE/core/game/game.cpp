#include "game.h"

#include "sys/spawner.h"
#include "sys/physics.h"
#include "sys/glfw/glfw_events.h"
#include "sys/glfw/glfw_render.h"

game::game() {
}

game::~game()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(glfw);
    glfwTerminate();
}

int game::run()
{
    // init glfw
    {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            return 1;

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
        glfw = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);

        if (glfw == nullptr)
            return 1;
        glfwMakeContextCurrent(glfw);
        glfwSwapInterval(1); // Enable vsync
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        //ImGui::StyleColorsDark();
        ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(glfw, true);
#ifdef __EMSCRIPTEN__
        ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    spawner::makeWorld(reg);
    spawner::makePlayer(reg);

    // Главный цикл
    while (!glfwWindowShouldClose(glfw))
    {
        double now = glfwGetTime(); double deltaTime = now - lastUpdateTime;
        
        glfw_events::step(glfw);
        physics::step(reg);

        if ((now - lastFrameTime) >= fpsLimit) {

            glfw_opengl3_imgui_new_frame();
            glfw_render::frame(reg);
            glfw_opengl3_imgui_render(glfw);

            lastFrameTime = now;
        }   lastUpdateTime = now;
    }

    return 0;
}
