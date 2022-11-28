#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glabs/loader.hpp>
#include <cpputils/debug.hpp>

#include <gezzy/window.hpp>

Window::Window(const std::string_view title, glm::uvec2 size) : m_title(title), m_size(size) {
    logDebug("Initializing glfw");

    if (!glfwInit()) {
        throw std::runtime_error("ERROR: glfwInit()");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    logDebug("Creating glfw window");

    m_windowPtr = glfwCreateWindow(size.x, size.y, title.data(), NULL, NULL);
    if (!m_windowPtr) {
        glfwTerminate();
        throw std::runtime_error("ERROR: creating window");
    }

    glfwMakeContextCurrent(m_windowPtr);

    glfwSetWindowUserPointer(m_windowPtr, this);

    glfwSetWindowSizeCallback(m_windowPtr, [] (GLFWwindow* wnd, int w, int h) {
        static_cast<Window*>(glfwGetWindowUserPointer(wnd))->onResize(w, h);
    });

    glfwSwapInterval(1);

    GL::load(glfwGetProcAddress);
}

bool Window::update() {
    glfwSwapBuffers(m_windowPtr);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return !glfwWindowShouldClose(m_windowPtr);
}


void Window::setSize(int w, int h) {
    glfwGetWindowSize(m_windowPtr, &w, &h);
    m_size = glm::uvec2(w, h);
}

glm::uvec2 Window::getSize() {
    return m_size;
}

void Window::setPos(int x, int y) {
    glfwSetWindowPos(m_windowPtr, x, y);
}

void Window::onResize(int w, int h) {
    m_size = glm::uvec2(w, h);
    glViewport(0, 0, w, h); // Update opengl width height
}

GLFWwindow* Window::getGlfwWindowPtr() const {
    return m_windowPtr;
}

void Window::toggleFullScreen() {
    logDebug("Toggle fullscreen");
    //GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    //glfwSetWindowMonitor(window, monitor, 0, 0, width, height, GLFW_DONT_CARE);
}

Window::~Window() {
    logDebug("Destroy window");
    glfwDestroyWindow(m_windowPtr);
    glfwTerminate();
    GL::unload();
}
