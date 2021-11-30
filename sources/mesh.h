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

    // No point to copies, objects of this class are completely static.
    // Use objects like a flyweight.
    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh& other) = delete;

    ~Mesh();

    void draw(const sf::Shader& shader);

    static Mesh createCube();

    // static Mesh createCylinder(segments >= 3);
    // static Mesh createSphere(segments >= 3);

private:
    // Helper functions:
    // connectQuad(indices)
    // connectRingToSingle(vector<indices>, center)
    // connectRingToRing(vector<indices>, vector<indices>)

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};

#endif // MESH_H
