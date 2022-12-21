#include <gezzy/window.hpp>
#include <glabs/gl.hpp>

Window window {"h"};

GL::Shader s {
R"(
#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_color;

uniform mat3 mat;

out vec4 color;

void main() {
    color = a_color;
    gl_Position = vec4(a_pos * mat, 1.0);
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
    .linkAttributes({"a_pos", "a_color"});
    vao.unuse();

    String a {"hi"};
    

    Mat3 mat {1.f};
    float x{0.001f};
    while (window.update()) {
        vao.use();
        s.use();
        s.uniform("mat", mat);
        mat.rotate(x+=0.001f);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
