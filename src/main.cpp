#include <gezzy/window.hpp>
#include <glabs/gl.hpp>

Window window {"h"};

GL::Shader s {
R"(
#version 330 core
in vec3 a_pos;
in vec4 a_color;

out vec4 color;

void main() {
    color = a_color;
    gl_Position = vec4(a_pos, 1.0);
}
)",
R"(
#version 330 core
in vec4 color;

out vec4 frag_color;
void main() {
    frag_color = color;
}
)"
};

int main() {
    GL::VBO<Vec3, GL::RGBA> vbo {
        {{-0.5, -0.5, 0.0}, 0xff0000ff_rgba},
        {{0.5, -0.5, 0.0}, 0x00ff00ff_rgba},
        {{0.0, 0.5, 0.0}, 0x0000ffff_rgba}
    };

    GL::VAO vao;
    vao.use();
    s.compile();
    s.attribLinker(vbo)
    .autoLink()
    .autoLink();
    vao.unuse();

    while (window.update()) {
        vao.use();
        s.use();

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
