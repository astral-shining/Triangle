#include <cpputils/fastvector.hpp>
#include <glabs/gl.hpp>
#include <gezzy/window.hpp>

GL::Shader s {
R"(
#version 330 core
in vec3 a_pos;
in vec4 a_color;

out vec4 color;

uniform mat3 model;

void main() {
    color = a_color;
    gl_Position = vec4(model * a_pos, 1.0);
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
#include <glm/gtx/matrix_transform_2d.hpp>
int main() {
    GL::VAO vao;
    vao.use();
    GL::VBO<glm::vec3, GL::RGBA> vbo {
        {{-1.0, 1.0, 0.0}, {}},
        {{1.0, 1.0, 0.0}, {}},
        {{1.0, -1.0, 0.0}, {}},
        {{-1.0, -1.0, 0.0}, {}}
    };

    s.compile();
    s.attribLinker(vbo)
    .autoLinkAll();
    vao.unuse();
    glm::mat3 m { 0.5f };

    float x {};
    while (window.update()) {
        vao.use();
        vbo.bufferSubData(GL::HSVA(x, 1.f, 1.f, 1.f), 0);
        vbo.bufferSubData(GL::HSVA(x+90.f, 1.f, 1.f), 1);
        vbo.bufferSubData(GL::HSVA(x+180.f, 1.f, 1.f), 2);
        vbo.bufferSubData(GL::HSVA(x+270.f, 1.f, 1.f), 3);
        s.use();
        s.uniform("model", glm::rotate(m, x/32.f));
     
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        x+=1.f;
    }
}
