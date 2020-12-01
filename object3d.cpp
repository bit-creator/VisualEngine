#include "object3d.h"

Object3D::Object3D() noexcept
    : VAO       (  )
    , VBO       ( GL_ARRAY_BUFFER )
    , EBO       ( GL_ELEMENT_ARRAY_BUFFER ) 
    , _modelMat ( glm::mat4(1.0f) )
    , _material ( std::make_shared<Material>() )
    , _rotate   ( glm::quat(1.0f, 1.0f, 1.0f, 1.0f) )
    , _position   ( Vector(0.0f, 0.0f, 0.0f) )
    , _scale    ( Vector(1.0f, 1.0f, 1.0f) )
    , _dirtyTransform(true)
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

void Object3D::setScale(const glm::vec3& scale) noexcept
{ _scale = scale; _dirtyTransform = true; }

glm::vec3 Object3D::getScale() const noexcept
{ return _scale; }

void Object3D::setRotate(const glm::vec3& axis, const GLfloat angle) noexcept
{ _rotate = glm::angleAxis(angle, glm::normalize(axis)); _dirtyTransform = true; }

glm::quat Object3D::getRotate() const noexcept
{ return _rotate; }

void Object3D::setPosition(const glm::vec3& position) noexcept
{ _position = position; _dirtyTransform = true; }

glm::vec3 Object3D::getPosition() const noexcept
{ return _position; }

void Object3D::setGeometry(GeometryPtr geometry) noexcept
{ _geom = geometry; }

GeometryPtr Object3D::getGeometry() const noexcept
{ return _geom; }

glm::mat4 Object3D::getModelMat() noexcept
{
    if(!_dirtyTransform) return _modelMat;

    _modelMat = glm::mat4(1.0f);
    _modelMat = glm::translate(_modelMat, _position);
    
    _modelMat *= glm::toMat4(_rotate);
    
    _modelMat = glm::scale(_modelMat, _scale);
    
    _dirtyTransform = false;

    return _modelMat;
}

void Object3D::render(const Camera& camera, ShaderProgram& program) noexcept
{
    program.enable();

    auto material = getMaterial();

    glm::mat4 ModelMat = getModelMat();
    glm::mat4 ProjMat = camera.getProjectionMatrix();

    glm::mat3 nMat = glm::inverse(glm::transpose(ModelMat));

    program.setUniform("uAmbientColor", material->getColor(ColorTarget::Ambient));
    program.setUniform("uDiffuseColor", material->getColor(ColorTarget::Diffuse));
    program.setUniform("uSpecularColor", material->getColor(ColorTarget::Specular));
    program.setUniform("uRoughness", 1 / material->getRoughness());
    
    program.setUniform("uModelProjMat", ProjMat * ModelMat);
    program.setUniform("uModelMat", ModelMat);
    program.setUniform("uLightDir", glm::normalize(glm::vec3(0., 0., 1.)));
    program.setUniform("uNormalMat", nMat);

    glPolygonMode(GL_FRONT_AND_BACK, material->getPolygonsFillMode());

    _geom->bindBuffers();

    if (_geom->hasIndexes()) glDrawElements(_geom->getPoligonConnectMode(), _geom->getNumIndices(), GL_UNSIGNED_INT, 0);
    else glDrawArrays(_geom->getPoligonConnectMode() , 0, _geom->getNumVertexes());

    _geom->unbindBuffers();
}