#include <glad/glad.h>
#include <iostream>
#include "fbo.hh"

void FBO::init(int width, int height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);

    // Create a color attachment texture
    glGenTextures(color_textures.size(), &(color_textures[0]));
    for (int i = 0; i < color_textures.size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, color_textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, color_textures[i], 0);
    }
    if (color_textures.size() > 1)
    {
        std::vector<unsigned int> v;
        for (int j = 0; j < color_textures.size(); j++)
            v.push_back(GL_COLOR_ATTACHMENT0 + j);

        glDrawBuffers(color_textures.size(), &(v[0]));
    }

    // Create a depth attachment texture
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);


    // Now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

FBO::FBO(int width, int height, int nb_data)
{
    glGenFramebuffers(1, &fbo_id);
    color_textures = std::vector<GLuint>(nb_data);

    init(width, height);
}

void FBO::realloc(int width, int height)
{
    glDeleteTextures(color_textures.size(), &(color_textures[0]));
    glDeleteTextures(1, &depth_texture);

    init(width, height);
}