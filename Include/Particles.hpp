/*
    Particles.hpp:

        - It implements a class that stores all the information related to all particles, including their position, velocity, mass, etc.
*/
#pragma once

#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.hpp>
#include <Camera.hpp>
#include <Scene.hpp>
#include <Textures.hpp>
#include <ParticleType.hpp>

class Particles 
{
public:
    Particles(GLuint nParticles, std::string texture_path, std::string point_cloud_path[2], float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed, float minSize, float maxSize);
    Particles(GLuint nParticles, std::string texture_path);
    Particles(GLuint nParticles, std::string texture_path, float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed, float minSize, float maxSize);

    // Draw one particle according to its index in the VAO and its characteristics
    void Draw(Shader shader, Camera camera);

private:
    // Attributes
    GLuint nParticles;

    // Attributes
    std::vector<glm::vec4> positions;
    std::vector<glm::vec4> positions_2;
    std::vector<glm::vec4> positions_3;
    std::vector<glm::vec4> velocities;
    std::vector<float> masses;
    std::vector<float> radiuses;
    std::vector<glm::vec4> colors;
    std::vector<glm::vec4> colors_2;
    std::vector<glm::vec4> colors_3;
    std::vector<float> sizes;
    GLuint spriteTexture;
    Texture *texture;

    // Buffers
    GLuint positionBuffer;
    GLuint position_2Buffer;
    GLuint position_3Buffer;
    GLuint velocityBuffer;
    GLuint massBuffer;
    GLuint radiusBuffer;
    GLuint colorBuffer;
    GLuint color_2Buffer;
    GLuint color_3Buffer;
    GLuint sizeBuffer;

    // VAO
    GLuint VAO;

    // Functions
    void getSpriteTexture(char* texture_path);
    void generateValues(GLuint nParticles, float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed, float minSize, float maxSize, bool sphere);
    void groupValues();
    void transferDataToGPU();
};

#endif