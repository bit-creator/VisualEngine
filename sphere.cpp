#include "sphere.h"

Sphere::Sphere(GLuint radius, GLuint subdivision) noexcept
    : _radius(radius)
    , _subdiv(subdivision)
    , VBO(GL_ARRAY_BUFFER)
    , EBO(GL_ELEMENT_ARRAY_BUFFER)
    , _vertices({
        glm::vec3(1., 0., 0.),          // 0 
        glm::vec3(0., 1., 0.),          // 1    
        glm::vec3(0., 0., 1.),          // 2

        glm::vec3(-1., 0., 0.),         // 3
        glm::vec3(0., -1., 0.),         // 4
        glm::vec3(0., 0., -1.),         // 5
        })
    , _indices(std::make_unique<std::vector<glm::uvec3>>(std::vector<glm::uvec3>{
        glm::uvec3(0, 1, 2),            // 1
        glm::uvec3(1, 2, 3),            // 2
        glm::uvec3(2, 3, 4),            // 3
        glm::uvec3(0, 2, 4),            // 4
        glm::uvec3(0, 1, 5),            // 5
        glm::uvec3(1, 3, 5),            // 6
        glm::uvec3(3, 4, 5),            // 7
        glm::uvec3(0, 4, 5)             // 8
    }))
{ setScale(glm::vec3(_radius, _radius, _radius)); div(_subdiv); setupBuffers(); }

Sphere::~Sphere() noexcept {  }



// void Sphere::flipAndPush() noexcept
// {

// }

void Sphere::div(GLuint sub) noexcept
{
    if(--sub == 0) return;
    indexArrayPtr tmp = std::make_unique<indexArray>(indexArray(_indices->size() * 4, glm::uvec3()));
    GLint index = -1;
    for (const auto& triangle : *_indices)
    {
        auto res = divTriangle(triangle);
        (*tmp)[++index] = res[0];
        (*tmp)[++index] = res[1];
        (*tmp)[++index] = res[2];
        (*tmp)[++index] = res[3];
    }
    std::swap(_indices, tmp);
    div(sub);
}

std::array<glm::uvec3, 4> Sphere::divTriangle(glm::uvec3 triangle) 
{
    auto point_1 = _vertices[triangle[0]];
    auto point_2 = _vertices[triangle[1]];
    auto point_3 = _vertices[triangle[2]];

    auto point_1_2 = glm::vec3(
        (point_1.x + point_2.x) / 2, 
        (point_1.y + point_2.y) / 2, 
        (point_1.z + point_2.z) / 2
    );
    
    auto point_1_3 = glm::vec3(
        (point_1.x + point_3.x) / 2, 
        (point_1.y + point_3.y) / 2, 
        (point_1.z + point_3.z) / 2
    );

    auto point_2_3 = glm::vec3(
        (point_2.x + point_3.x) / 2, 
        (point_2.y + point_3.y) / 2, 
        (point_2.z + point_3.z) / 2
    );

    point_1_3 = glm::normalize(point_1_3);
    point_1_2 = glm::normalize(point_1_2);
    point_2_3 = glm::normalize(point_2_3);

    _vertices.push_back(point_1_2);
    _vertices.push_back(point_1_3);
    _vertices.push_back(point_2_3);

    GLuint index_2_3 = _vertices.size() - 1;
    GLuint index_1_3 = index_2_3 - 1;
    GLuint index_1_2 = index_1_3 - 1;
    
    return std::array<glm::uvec3, 4>({
        glm::uvec3(triangle[0], index_1_2, index_1_3),
        glm::uvec3(triangle[1], index_1_2, index_2_3),
        glm::uvec3(triangle[2], index_1_3, index_2_3),
        glm::uvec3(index_2_3, index_1_2, index_1_3)
    });
}

void Sphere::render(const ShaderProgram& program) const noexcept
{
    program.enable();

    auto color = getColor();

    auto offset = getOffset();

    glm::mat3 mat = getModelMat();

    program.setUniform("uColor", color.r, color.g, color.b, color.w );
    program.setUniform("uModelMat", mat);
    program.setUniform("uPosition", offset);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    EBO.bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, _indices->size() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    EBO.unbind();
}


void Sphere::setupBuffers() const noexcept
{
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);

    VBO.bind();
    EBO.bind();

    VBO.loadRawData(_vertices.data(), _vertices.size() * 3 * sizeof(GLfloat));
    EBO.loadRawData(_indices->data(), _indices->size() * 3 * sizeof(GLuint));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    VBO.unbind();

    glBindVertexArray(0);
}


