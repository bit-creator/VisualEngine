#include "sphere.h"

Sphere::Sphere(GLuint subdivision) noexcept
    : Object3D()
    , _subdiv(subdivision)
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
{ div(_subdiv); setupBuffers(); }

Sphere::~Sphere() noexcept {  }

void Sphere::setNums() noexcept
{ _numIndex = _indices->size() * 3; _numVertex = _vertices.size(); }

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

void Sphere::render(const ShaderProgram& program) noexcept
{
    program.enable();

    auto material = getMaterial();

    auto offset = getOffset();

    glm::mat3 mat = getModelMat();

    glm::mat3 nMat = glm::inverse(glm::transpose(mat));

    program.setUniform("uAmbientColor", material->getColor(ColorTarget::Ambient));
    program.setUniform("uDiffuseColor", material->getColor(ColorTarget::Diffuse));
    program.setUniform("uSpecularColor", material->getColor(ColorTarget::Specular));
    program.setUniform("uRoughness", 1 / material->getRoughness());
    
    program.setUniform("uModelMat", mat);
    program.setUniform("uPosition", offset);
    program.setUniform("uLightDir", glm::vec3(0., 1., 1.) * mat);
    program.setUniform("uNormalMat", nMat);

    glPolygonMode(GL_FRONT_AND_BACK, material->getFill());

    EBO.bind();
    VAO.bind();
    glDrawElements(GL_TRIANGLES, _indices->size() * 3, GL_UNSIGNED_INT, 0);
    VAO.unbind();
    EBO.unbind();
}


void Sphere::setupBuffers() noexcept
{
    VAO.bind();
    VBO.bind();
    EBO.bind();

    VBO.loadData(_vertices, GL_STATIC_DRAW);
    EBO.loadData(*_indices, GL_STATIC_DRAW);
    
    VAO.addAttribute(Attribute::ATTRIB_POSITION, 3 * sizeof(GLfloat), 0);
    VAO.addAttribute(Attribute::ATTRIB_NORMAL, 3 * sizeof(GLfloat), 0);
    
    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();
}

