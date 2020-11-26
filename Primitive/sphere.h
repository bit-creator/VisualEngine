/**
 * @file sphere.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <memory>
#include <unordered_set>
#include <algorithm>

#include <boost/functional/hash.hpp>

#include "../object3d.h"
#include "../GL/buffer.h"

using indexArray    = std::vector<glm::uvec3>;

using indexArrayPtr = std::unique_ptr<indexArray>;

using indexOktant = std::vector <glm::uvec3>;
// using allIndexOktant = std::array <indexOktant, 8>;
using allIndexOktant = std::vector <glm::uvec3>;

using vertexOktant = std::vector <glm::vec3>;
// using allVertexOktant = std::array <vertexOktant, 8>;
using allVertexOktant = std::vector <glm::vec3>;


// struct _hasher { int64_t operator ()(glm::vec3 vertex) { 
//     size_t hash = *(int32_t*)&vertex.x; 
//     boost::hash_combine(hash, *(int32_t*)&vertex.y); 
//     boost::hash_combine(hash, *(int32_t*)&vertex.z);
//     return hash;     
// } };

// struct _equal  { bool operator ()(glm::vec3 vert_1, glm::vec3 vert_2) { 
//     return vert_1.x == vert_2.x 
//         && vert_1.y == vert_2.y 
//         && vert_1.z == vert_2.z; 
// }};

// using vertexTree = std::unordered_set < std::pair<glm::vec3, GLuint>, _hasher, _equal >; 

class Sphere : public Object3D
{
    private:
        GLuint                                                          _radius;
        GLuint                                                          _subdiv;

        mutable GLuint                                                  VAO;
        mutable Buffer                                                  VBO;
        mutable Buffer                                                  EBO;

        mutable vertexOktant                                            _vertices;
        mutable allVertexOktant                                         _sphereVertex;
        mutable std::unique_ptr<indexOktant>                            _indices;
        mutable allIndexOktant                                          _sphereIndex;
        mutable std::vector<glm::vec3>                               _SymetryPattern;
        // mutable vertexTree                                              _tree;  

    public:
        Sphere(GLuint radius, GLuint subdivision) noexcept;
        ~Sphere() noexcept;

        void render(const ShaderProgram& program) const noexcept override;
        void setupBuffers() const noexcept override;
        
    private:
        void flipAndPush() noexcept;
        void div(GLuint sub) noexcept;
        std::array<glm::uvec3, 4> divTriangle(glm::uvec3 triangle, GLint pos);
};