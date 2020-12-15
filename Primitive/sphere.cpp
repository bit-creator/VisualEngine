#include "sphere.h"

using indexArray    = std::vector<glm::uvec3>;
using indexArrayPtr = std::unique_ptr<indexArray>;

Sphere::Sphere(GLuint subdivision) noexcept
    : Geometry()
    , _subdiv(subdivision)
    , _vertices({
        { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2() },          // 0
        { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2() },          // 1
        { glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2() },          // 2

        { glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2() },         // 3
        { glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2() },         // 4
        { glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2() },         // 5
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
{
	div(_subdiv);
	refreshUV();
	setNum(_indices->size() * 3,  _vertices.size(), true);
	setupBuffers();
}

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
    auto point_1 = _vertices[triangle[0]]._coord;
    auto point_2 = _vertices[triangle[1]]._coord;
    auto point_3 = _vertices[triangle[2]]._coord;

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

    _vertices.push_back({point_1_2});
    _vertices.push_back({point_1_3});
    _vertices.push_back({point_2_3});

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

void Sphere::setupBuffers() noexcept
{
    VAO.bind();
    VBO.bind();
    EBO.bind();

    VBO.loadData(_vertices, GL_STATIC_DRAW);
    EBO.loadData(*_indices, GL_STATIC_DRAW);
    
    VAO.addAttribute(Attribute::ATTRIB_POSITION, 5 * sizeof(GLfloat), 0);
    VAO.addAttribute(Attribute::ATTRIB_NORMAL, 5 * sizeof(GLfloat), 0);
    VAO.addAttribute(Attribute::ATTRIB_TEX, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    
    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();
}

glm::vec2 genSphereUV(glm::vec3 c) {
	return glm::vec2(
		std::atan((c.z / c.x)) / (2.0f * M_PI),
		1 - (std::asin(c.y) / M_PI) + 0.5f
	);
}

void Sphere::refreshUV() {
	for ( Vertex& vert : _vertices )
		vert._texCoord = genSphereUV(vert._coord);
}
