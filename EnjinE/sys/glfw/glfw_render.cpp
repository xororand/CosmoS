#include "glfw_render.h"

#include "core/grafics/grafics.h"

#include "entt/entity/registry.hpp"

#include "comp/Sprite.h"

void glfw_render::frame(entt::registry&reg) {
    int width = 640;
    int height = 480;
    // texture handle
    GLuint texture;

    // generate texture
    glGenTextures(1, &texture);

    // bind the texture
    glBindTexture(GL_TEXTURE_2D, texture);
    // create some image data
    std::vector<GLubyte> image(4 * width * height);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            size_t index = j * width + i;
            image[4 * index + 0] = 0xFF * (j / 10 % 2) * (i / 10 % 2);  // R
            image[4 * index + 1] = 0xFF * (j / 13 % 2) * (i / 13 % 2);  // G
            image[4 * index + 2] = 0xFF * (j / 17 % 2) * (i / 17 % 2);  // B
            image[4 * index + 3] = 0xFF;                                // A
        }
    }

    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // set texture content
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture);
	//const auto view = reg.view<Sprite>();
	//for (auto e : view) {

	//}
}
