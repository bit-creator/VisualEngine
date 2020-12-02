#include "object3d.h"

Object3D::Object3D() noexcept
    : Node(NodeType::NODE_OBJECT)
    , VAO       (  )
    , VBO       ( GL_ARRAY_BUFFER )
    , EBO       ( GL_ELEMENT_ARRAY_BUFFER ) 
    , _material ( std::make_shared<Material>() )
{  }

Object3D::Object3D(MaterialPtr material) noexcept
    : Object3D()
{ _material = material; }

Object3D::~Object3D() noexcept 
{  }

void Object3D::setMaterial(MaterialPtr material) noexcept
{ _material = material; }

MaterialPtr Object3D::getMaterial() const noexcept
{ return _material; }

void Object3D::setGeometry(GeometryPtr geometry) noexcept
{ _geom = geometry; }

GeometryPtr Object3D::getGeometry() const noexcept
{ return _geom; }

void Object3D::render(const Camera& camera, ShaderProgram& program) noexcept
{
    program.enable();

    auto material = getMaterial();

    glm::mat4 ModelMat = getModelMat();
    glm::mat4 ViewMat = glm::inverse(glm::transpose(((Node)camera).getModelMat()));
    glm::mat4 ProjMat = camera.getProjectionMatrix();

    // std::cout << glm::to_string(ViewMat) << std::endl << std::endl;

    glm::mat3 nMat = glm::inverse(glm::transpose(ModelMat));

    program.setUniform("uAmbientColor", material->getColor(ColorTarget::Ambient));
    program.setUniform("uDiffuseColor", material->getColor(ColorTarget::Diffuse));
    program.setUniform("uSpecularColor", material->getColor(ColorTarget::Specular));
    program.setUniform("uRoughness", 1 / material->getRoughness());
    program.setUniform("uPerspectiveCamera", (int)camera.getType());
    
    program.setUniform("uMVPMat", ProjMat * ViewMat * ModelMat);
    program.setUniform("uModelMat", ModelMat);
    program.setUniform("uLightDir", glm::normalize(glm::vec3(0., 0., 1.)));
    program.setUniform("uNormalMat", nMat);

    glPolygonMode(GL_FRONT_AND_BACK, material->getPolygonsFillMode());

    _geom->bindBuffers();

    if (_geom->hasIndexes()) glDrawElements(_geom->getPoligonConnectMode(), _geom->getNumIndices(), GL_UNSIGNED_INT, 0);
    else glDrawArrays(_geom->getPoligonConnectMode() , 0, _geom->getNumVertexes());

    _geom->unbindBuffers();
}