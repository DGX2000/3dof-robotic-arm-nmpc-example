#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glm/glm.hpp>

#include <SFML/Graphics/Shader.hpp>

class Mesh
{
public:
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
    };

public:
    Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices);
    ~Mesh();

    void draw(sf::Shader* shader);

    static Mesh createCube();
    static Mesh createCylinder(unsigned int segments);
    static Mesh createSphere(unsigned int segments);

private:
    // Helper functions:
    static std::vector<unsigned int> connectQuad(unsigned int start[4]);
    static std::vector<unsigned int> connectRingToSingle(unsigned int ringStart,
                                                         unsigned int ringLength,
                                                         unsigned int center);
    static std::vector<unsigned int> connectRingToRing(unsigned int upperRingStart,
                                                       unsigned int lowerRingStart,
                                                       unsigned int ringLength);

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};

#endif // MESH_H
