#include "object3d.h"

Object3D::Object3D() noexcept
    : _material(std::make_shared<Material>())
{  }

Object3D::Object3D(MaterialPtr material) noexcept
    : _material(material)
{  }

Object3D::Object3D(const Object3D& oth) noexcept
    : _material(oth._material)
    , _scale(oth._scale)
    , _rotate(oth._rotate)
    , _offset(oth._offset)
{  }

Object3D::Object3D(Object3D&& oth) noexcept
    : _material(std::move(oth._material))
    , _scale(std::move(oth._scale))
    , _rotate(std::move(oth._rotate))
    , _offset(std::move(oth._offset))
{  }

Object3D::~Object3D() noexcept 
{  }

void Object3D::setMaterial(MaterialPtr material) noexcept
{ _material = material; }

MaterialPtr Object3D::getMaterial() const noexcept
{ return _material; }

void Object3D::setScale(const glm::vec3& scale) noexcept
{ _scale = scale; }

glm::vec3 Object3D::getScale() const noexcept
{ return _scale; }

void Object3D::setRotate(const glm::vec3& axis, const GLfloat& angle) noexcept
{ 
    auto _axis = glm::normalize(axis);  
    
    _rotate.x = _axis.x * sin(angle / 2);
    _rotate.y = _axis.y * sin(angle / 2);
    _rotate.z = _axis.z * sin(angle / 2);
    _rotate.w = cos(angle / 2);

}

Quaternion Object3D::getRotate() const noexcept
{ return _rotate; }

void Object3D::setOffset(const glm::vec3& offset) noexcept
{ _offset = offset; }

glm::vec3 Object3D::getOffset() const noexcept
{ return _offset; }

glm::mat3 Object3D::getModelMat() const noexcept
{
    glm::mat3 mRotate = generateRotateMatrix(_rotate);

    glm::mat3 mScale(_scale.x, 0.,      0.,
                       0.,      _scale.y, 0.,
                       0.,      0.,      _scale.z);

    return mRotate * mScale;
}

glm::mat3x3 generateRotateMatrix(Quaternion rotate) noexcept
{
    auto xy = 2 * rotate.x * rotate.y;
    auto xz = 2 * rotate.x * rotate.z;
    auto yz = 2 * rotate.y * rotate.z;
    auto xx = 2 * rotate.x * rotate.x;
    auto yy = 2 * rotate.y * rotate.y;
    auto zz = 2 * rotate.z * rotate.z;
    auto xw = 2 * rotate.x * rotate.w;
    auto yw = 2 * rotate.y * rotate.w;
    auto zw = 2 * rotate.z * rotate.w;

    /**
     * value naemed (valval) impliment aka (2valval) 
    */
    return glm::mat3x3
    (
        /**************************************************************/
        /**/ 1 - yy - zz, /**/ xy - zw,       /**/ xz + yw,       /**/
        /**************************************************************/
        /**/ xy + zw,       /**/ 1 - xx - zz, /**/ yz - xw,       /**/      
        /**************************************************************/
        /**/ xz - yw,       /**/ yz + xw,       /**/ 1 - xx - yy  /**/
        /**************************************************************/
    );
}