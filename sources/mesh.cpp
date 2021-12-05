#include "mesh.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Mesh::Mesh(std::vector<Vertex> &&vertices, std::vector<unsigned int> &&indices)
    : vertices(vertices), indices(indices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
                 &(this->vertices[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int),
                 &(this->indices[0]), GL_STATIC_DRAW);

    // Vertex.position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)nullptr);

    // Vertex.normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Mesh::draw(sf::Shader* shader)
{
    sf::Shader::bind(shader);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

Mesh Mesh::createCube()
{
    std::vector<Vertex> vertices
    {
        {{-0.5F, -0.5F, 0.5F}, {-1.0F, -1.0F, 1.0F}},   // 0 front-face bottom-left
        {{0.5F, -0.5F, 0.5F}, {1.0F, -1.0F, 1.0F}},   // 1 front-face bottom-right
        {{0.5F, 0.5F, 0.5F}, {1.0F, 1.0F, 1.0F}},   // 2 front-face top-right
        {{-0.5F, 0.5F, 0.5F}, {-1.0F, 1.0F, 1.0F}},   // 3 front-face top-left

        {{-0.5F, -0.5F, -0.5F}, {-1.0F, -1.0F, -1.0F}},   // 4 back-face bottom-left
        {{0.5F, -0.5F, -0.5F}, {1.0F, -1.0F, -1.0F}},   // 5 back-face bottom-right
        {{0.5F, 0.5F, -0.5F}, {1.0F, 1.0F, -1.0F}},   // 6 back-face top-right
        {{-0.5F, 0.5F, -0.5F}, {-1.0F, 1.0F, -1.0F}}    // 7 back-face top-left
    };

    std::vector<unsigned int> indices
    {
        0, 1, 3, 1, 2, 3,   // front
        4, 5, 7, 5, 6, 7,   // back
        0, 1, 4, 1, 5, 4,   // bottom
        1, 5, 2, 5, 6, 2,   // right
        3, 2, 7, 2, 6, 7,   // top
        4, 3, 7, 3, 0, 4    // left
    };

    return Mesh(std::move(vertices), std::move(indices));
}

Mesh Mesh::createCylinder(unsigned int segments)
{
    constexpr unsigned int UPPER_RING_CENTRE = 0;
    constexpr unsigned int LOWER_RING_CENTRE = 1;
    constexpr unsigned int UPPER_RING_START = 2;
    const unsigned int LOWER_RING_START = UPPER_RING_START + segments;



    std::vector<Vertex> vertices;
    vertices.resize(2*(segments+1));

    vertices[UPPER_RING_CENTRE].position = glm::vec3{0.0F, 0.5F, 0.0F};
    vertices[UPPER_RING_CENTRE].normal = glm::vec3{0.0F, 1.0F, 0.0F};

    vertices[LOWER_RING_CENTRE].position = glm::vec3{0.0F, -0.5F, 0.0F};
    vertices[LOWER_RING_CENTRE].normal = glm::vec3{0.0F, -1.0F, 0.0F};

    for(unsigned int i = 0; i < segments; ++i)
    {
        auto phi = (static_cast<float>(i) / static_cast<float>(segments)) * 2.0F * glm::pi<float>();

        auto x = glm::cos(phi);
        auto z = -glm::sin(phi);

        vertices[UPPER_RING_START+i].position = glm::vec3{x, 0.5F, z};
        vertices[UPPER_RING_START+i].normal = glm::vec3{x, 0.0F, z};

        vertices[LOWER_RING_START+i].position = glm::vec3{x, -0.5F, z};
        vertices[LOWER_RING_START+i].normal = glm::vec3{x, 0.0F, z};
    }



    std::vector<unsigned int> indices;
    auto upperIndices = connectRingToSingle(UPPER_RING_START, segments, UPPER_RING_CENTRE);
    auto lowerIndices = connectRingToSingle(LOWER_RING_START, segments, LOWER_RING_CENTRE);
    auto mantleIndices = connectRingToRing(UPPER_RING_START, LOWER_RING_START, segments);

    indices.insert(indices.end(), upperIndices.begin(), upperIndices.end());
    indices.insert(indices.end(), lowerIndices.begin(), lowerIndices.end());
    indices.insert(indices.end(), mantleIndices.begin(), mantleIndices.end());

    return Mesh(std::move(vertices), std::move(indices));
}

Mesh Mesh::createSphere(unsigned int segments)
{
    constexpr unsigned int UPPER_CENTRE = 0;
    constexpr unsigned int LOWER_CENTRE = 1;
    constexpr unsigned int UPPER_RING_START = 2;
    const unsigned int LOWER_RING_START = UPPER_RING_START + (segments-1)*segments;



    std::vector<Vertex> vertices;
    vertices.resize(2 + segments*segments);

    vertices[UPPER_CENTRE].position = glm::vec3{0.0F, 0.5F, 0.0F};
    vertices[UPPER_CENTRE].normal = glm::vec3{0.0F, 1.0F, 0.0F};

    vertices[LOWER_CENTRE].position = glm::vec3{0.0F, -0.5F, 0.0F};
    vertices[LOWER_CENTRE].normal = glm::vec3{0.0F, -1.0F, 0.0F};

    for(unsigned int i = 0; i < segments; ++i)
    {
        auto theta = (static_cast<float>(i) / static_cast<float>(segments)) * glm::pi<float>();
        for(unsigned int j = 0; j < segments; ++j)
        {
            auto phi = (static_cast<float>(j) / static_cast<float>(segments)) * 2.0F * glm::pi<float>();

            auto x = glm::sin(phi) * glm::sin(theta);
            auto y = glm::cos(theta);
            auto z = glm::cos(phi) * glm::sin(theta);

            vertices[UPPER_RING_START + i*segments + j].position = glm::vec3{x, y, z};
            vertices[UPPER_RING_START + i*segments + j].normal = glm::vec3{x, y, z};
        }
    }



    std::vector<unsigned int> indices;

    auto upperIndices = connectRingToSingle(UPPER_RING_START, segments, UPPER_CENTRE);
    auto lowerIndices = connectRingToSingle(LOWER_RING_START, segments, LOWER_CENTRE);
    indices.insert(indices.end(), upperIndices.begin(), upperIndices.end());
    indices.insert(indices.end(), lowerIndices.begin(), lowerIndices.end());

    for(unsigned int i = 0; i < segments-1; ++i)
    {
        auto currentUpperRingStart = UPPER_RING_START + i * segments;
        auto currentLowerRingStart = UPPER_RING_START + (i+1) * segments;

        auto mantleIndices = connectRingToRing(currentUpperRingStart, currentLowerRingStart, segments);
        indices.insert(indices.end(), mantleIndices.begin(), mantleIndices.end());
    }

    return Mesh(std::move(vertices), std::move(indices));
}

std::vector<unsigned int> Mesh::connectQuad(unsigned int indices[4])
{
    std::vector<unsigned int> output{indices[0], indices[1], indices[3],
                                     indices[1], indices[2], indices[3]};
    return output;
}

std::vector<unsigned int> Mesh::connectRingToSingle(unsigned int ringStart,
                                                    unsigned int ringLength,
                                                    unsigned int center)
{
    std::vector<unsigned int> output;

    for(std::size_t i = 0; i < ringLength; ++i)
    {
        output.emplace_back(center);
        output.emplace_back(ringStart + i);
        output.emplace_back(ringStart + (i+1) % ringLength);
    }

    return output;
}

std::vector<unsigned int> Mesh::connectRingToRing(unsigned int upperRingStart,
                                                  unsigned int lowerRingStart,
                                                  unsigned int ringLength)
{
    std::vector<unsigned int> output;

    for(unsigned int i = 0; i < ringLength; ++i)
    {
        unsigned int quadIndices[4]{upperRingStart + i,
                                    lowerRingStart + i,
                                    lowerRingStart + (i+1) % ringLength,
                                    upperRingStart + (i+1) % ringLength};

        auto connectedQuad = connectQuad(quadIndices);
        output.insert(output.end(), connectedQuad.begin(), connectedQuad.end());
    }

    return output;
}
