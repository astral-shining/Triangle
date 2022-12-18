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

//#include <glm/ext/vector_float3.hpp>
//#include <glm/gtx/matrix_transform_2d.hpp>
//
struct A {
    int x;
    A(int x) : x(x) {
        printf("%s\n", __PRETTY_FUNCTION__);
    }
    A(const A& o) : x(o.x) {
        printf("%s\n", __PRETTY_FUNCTION__);
    }
    A(A&&) {
        printf("%s\n", __PRETTY_FUNCTION__);
    }
    ~A() {
        printf("%s\n", __PRETTY_FUNCTION__);
    }

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

    Vector<int> a {1,2,3,4};

    for (auto& i : a) {
        printf("%d\n", i);
    }

    while (window.update()) {
        vao.use();
        s.use();

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
