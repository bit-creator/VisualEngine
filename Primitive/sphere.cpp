#include "sphere.h"

Sphere::Sphere(GLuint radius, GLuint subdivision) noexcept
    : _radius(radius)
    , _subdiv(subdivision)
    , VBO(GL_ARRAY_BUFFER)
    , EBO(GL_ELEMENT_ARRAY_BUFFER)
    , _vertices({
        glm::vec3(0., 1., 0.),          // 1    
        glm::vec3(0., 0., 1.),          // 2    
        glm::vec3(1., 0., 0.),          // 0 

        // glm::vec3(-1., 0., 0.),         // 3
        // glm::vec3(0., -1., 0.),         // 4
        // glm::vec3(0., 0., -1.),         // 5
        })
    , _indices(std::make_unique<std::vector<glm::uvec3>>(std::vector<glm::uvec3>{
        glm::uvec3(0, 1, 2),            // 1
        // glm::uvec3(1, 2, 3),            // 2
        // glm::uvec3(2, 3, 4),            // 3
        // glm::uvec3(0, 2, 4),            // 4
        // glm::uvec3(0, 1, 5),            // 5
        // glm::uvec3(1, 3, 5),            // 6
        // glm::uvec3(3, 4, 5),            // 7
        // glm::uvec3(0, 4, 5)             // 8
    }))
    , _SymetryPattern({
        glm::vec3(1.f, 1.f, 1.f),
        glm::vec3(-1.f, 1.f, 1.f),
        glm::vec3(-1.f, -1.f, 1.f),
        glm::vec3(1.f, -1.f, 1.f),
        glm::vec3(1.f, 1.f, -1.f),
        glm::vec3(-1.f, 1.f, -1.f),
        glm::vec3(-1.f, -1.f, -1.f),
        glm::vec3(1.f, -1.f, -1.f),
    })
{ div(_subdiv); setupBuffers(); }

Sphere::~Sphere() noexcept {  }



void Sphere::flipAndPush() noexcept
{
    _sphereVertex(8 * _vertices.size());
    // std::copy();

    int okt = 0;
    for(auto& oktant : _sphereVertex)
    {
        // for(auto& vertex : oktant)
        // {
            vertex *= _SymetryPattern[okt];
        // }
        ++okt;
    }
        
    // _sphereIndex[0] = *_indices;
    // _sphereIndex[1] = *_indices;
    // _sphereIndex[2] = *_indices;
    // _sphereIndex[3] = *_indices;
    // _sphereIndex[4] = *_indices;
    // _sphereIndex[5] = *_indices;
    // _sphereIndex[6] = *_indices;
    // _sphereIndex[7] = *_indices;


_sphereIndex.push_back(*_indices);
_sphereIndex.push_back(*_indices);
_sphereIndex.push_back(*_indices);
_sphereIndex.push_back(*_indices);
_sphereIndex.push_back(*_indices);
_sphereIndex.push_back(*_indices);
_sphereIndex.push_back(*_indices);
_sphereIndex.push_back(*_indices);

    okt = 0;
    for(auto& oktant : _sphereIndex)
    {
        // for(auto& vertex : oktant)
            vertex += (_indices->size() * 3 * okt);
        ++okt;
    }
}

static bool firstIter = true;

void Sphere::div(GLuint sub) noexcept
{
    flipAndPush();
    if(--sub == 0) 
    {
        for(auto& a : _sphereVertex)
            // for(auto& a : okt)
            std::cout << "( " << a.x << " " << a.y << " " << a.z << " )" << '\t';
        std::cout << std::endl;
        std::cout << std::endl;

        for(auto& a : _sphereIndex)
            // for(auto& a : okt)
            std::cout << "( " << a.x << " " << a.y << " " << a.z << " )" << '\t';
        std::cout << std::endl; 
std::cout << std::endl;     
std::cout << std::endl; 
std::cout << std::endl; 
std::cout << std::endl; 

        std::cout << _vertices.size() << "\t" ;
        std::cout << _indices->size() << "\t" ;


    return;
    }
    indexArrayPtr tmp = std::make_unique<indexArray>(indexArray(_indices->size() * 4, glm::uvec3()));
    GLint index = -1, pos = -1;
    for (const auto& triangle : *_indices)
    {
        auto res = divTriangle(triangle, ++pos);
        firstIter = false;
        (*tmp)[++index] = res[0];
        (*tmp)[++index] = res[1];
        (*tmp)[++index] = res[2];
        (*tmp)[++index] = res[3];
    }
    std::swap(_indices, tmp);
    div(sub);
}


std::array<glm::uvec3, 4> Sphere::divTriangle(glm::uvec3 triangle, GLint pos) 
{
    glm::vec3 point_1 = _vertices[triangle[0]];
    glm::vec3 point_2 = _vertices[triangle[1]];
    glm::vec3 point_3 = _vertices[triangle[2]];

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
    
    GLuint index_2_3;
    GLuint index_1_3; 
    GLuint index_1_2; 

        std::cout << pos << std::endl;
    if(pos % 4 == 0 || firstIter)
    {
        _vertices.push_back(point_2_3);
        _vertices.push_back(point_1_3);
        _vertices.push_back(point_1_2);

        index_2_3 = _vertices.size() - 3;
        index_1_3 = _vertices.size() - 2;
        index_1_2 = _vertices.size() - 1;

    return std::array<glm::uvec3, 4>({
        glm::uvec3(index_2_3, index_1_3, index_1_2),
        glm::uvec3(triangle[0], index_1_2, index_1_3),
        glm::uvec3(index_1_2, triangle[1], index_2_3),
        glm::uvec3(index_1_3, index_2_3, triangle[2])
    });
    }

    if(pos % 4 == 1)
    {
        index_2_3 = _vertices.size() - 3;

        _vertices.push_back(point_1_2);    
        _vertices.push_back(point_1_3);

        index_1_2 = _vertices.size() - 2;
        index_1_3 = _vertices.size() - 1;
    }

    if(pos % 4 == 2)
    {
        index_1_3 = _vertices.size() - 4;
        
        _vertices.push_back(point_1_2);
        _vertices.push_back(point_2_3);    

        index_1_2 = _vertices.size() - 2;
        index_2_3 = _vertices.size() - 1;
    }

    if(pos % 4 == 3)
    {
        index_1_2 = _vertices.size() - 5;
        
        _vertices.push_back(point_1_3);
        _vertices.push_back(point_2_3);    

        index_1_3 = _vertices.size() - 2;
        index_2_3 = _vertices.size() - 1;
    }
    
    // std::cout << std::size(_vertices) << std::endl;
    
    return std::array<glm::uvec3, 4>({
        glm::uvec3(index_2_3, index_1_3, index_1_2),
        glm::uvec3(triangle[0], index_1_2, index_1_3),
        glm::uvec3(index_1_2, triangle[1], index_2_3),
        glm::uvec3(index_1_3, index_2_3, triangle[2])
    });
}

void Sphere::render(const ShaderProgram& program) const noexcept
{
    program.enable();

    auto color = getColor();

    auto offset = getOffset();

    glm::mat3 mat = getModelMat();

    glm::mat3 nMat = glm::inverse(glm::transpose(mat));

    program.setUniform("uColor", color.r, color.g, color.b, color.w );
    program.setUniform("uModelMat", mat);
    program.setUniform("uPosition", offset);
    program.setUniform("uLightDir", glm::vec3(0., 0., -1.) * mat);
    program.setUniform("uNormalMat", nMat);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    EBO.bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, _sphereIndex.size() * _indices->size() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    EBO.unbind();
}


void Sphere::setupBuffers() const noexcept
{
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);

    VBO.bind();
    EBO.bind();

    VBO.loadData(_sphereVertex, GL_STATIC_DRAW);
    EBO.loadData(_sphereIndex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    VBO.unbind();

    glBindVertexArray(0);
}


