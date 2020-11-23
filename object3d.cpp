#include "object3d.h"

Object3D::Object3D() noexcept
    : _colour(glm::vec4(1.0, 1.0, 1.0, 1.0))
{  }

Object3D::Object3D(colour_t colour) noexcept
    : _colour(colour)
{  }

Object3D::Object3D(const Object3D& oth) noexcept
    : _colour(oth._colour)
{  }

Object3D::Object3D(Object3D&& oth) noexcept
    : _colour(std::move(oth._colour))
{  }

Object3D::~Object3D() noexcept 
{  }

Object3D& Object3D::operator =(const Object3D& oth) noexcept
{ if(&oth != this) _colour = oth._colour; return *this; }

Object3D& Object3D::operator =(Object3D&& oth) noexcept
{ if(&oth != this) _colour = std::move(oth._colour); return *this; }

void Object3D::setColor(const colour_t& colour) noexcept
{ _colour = colour; }

colour_t Object3D::getColor() const noexcept
{ return _colour; }

void Object3D::setScale(const glm::vec3& scale) noexcept
{ _scale = scale; }

glm::vec3 Object3D::getScale() const noexcept
{ return _scale; }

void Object3D::setRotate(const Quaternion& rotate) noexcept
{ 
    auto vec = glm::normalize(glm::vec3(rotate.x, rotate.y, rotate.z));  
    
    _rotate.x = vec.x;
    _rotate.y = vec.y;
    _rotate.z = vec.z; 
    _rotate.w = rotate.w;

    _rotate.x *=  sin(_rotate.w / 2);
    _rotate.y *=  sin(_rotate.w / 2);
    _rotate.z *=  sin(_rotate.w / 2);
    _rotate.w = cos(_rotate.w/2);

}

Quaternion Object3D::getRotate() const noexcept
{ return _rotate; }

void Object3D::setOffset(const glm::vec3& offset) noexcept
{ _offset = offset; }

glm::vec3 Object3D::getOffset() const noexcept
{ return _offset; }

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