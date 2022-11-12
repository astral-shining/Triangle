#pragma once
#include <string_view>
#include <glm/vec2.hpp>

class GLFWwindow;

class Window {
    GLFWwindow* m_windowPtr;
    std::string_view m_title;
    glm::uvec2 m_size;
    //bool m_fullscreen;
    
public:
    Window(const std::string_view title="None", glm::uvec2 size = {640, 480});
    bool update();
    void setSize(int w, int h);
    glm::uvec2 getSize();
    void setPos(int w, int h);
    void onResize(int w, int h);
    GLFWwindow* getGlfwWindowPtr() const;
    void toggleFullScreen();
    ~Window();
};

inline Window window {"h"};
