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

#include <boost/functional/hash.hpp>

#include "../object3d.h"
#include "../GL/buffer.h"
#include "../GL/vertexarray.h"

using indexArray    = std::vector<glm::uvec3>;
using indexArrayPtr = std::unique_ptr<indexArray>;

class Sphere : public Object3D
{
    private:
        GLuint                                                          _radius;
        GLuint                                                          _subdiv;

        mutable VertexArray                                             VAO;
        mutable Buffer                                                  VBO;
        mutable Buffer                                                  EBO;

        mutable std::vector<glm::vec3>                                  _vertices;
        mutable std::unique_ptr<std::vector<glm::uvec3>>                _indices;

    public:
        Sphere(GLuint radius, GLuint subdivision) noexcept;
        ~Sphere() noexcept;

        void render(const ShaderProgram& program) const noexcept override;
        void setupBuffers() const noexcept override;
        
    private:
        // void flipAndPush() noexcept;
        void div(GLuint sub) noexcept;
        std::array<glm::uvec3, 4> divTriangle(glm::uvec3 triangle);
};