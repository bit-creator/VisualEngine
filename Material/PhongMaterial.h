/*
 * PhongMaterial.h
 *
 *  Created on: Apr 26, 2021
 *      Author: bit_creator
 */

#ifndef PHONGMATERIAL_H_
#define PHONGMATERIAL_H_

#include "../CreateAsPointer.hpp"
#include "Material.h"

class PhongMaterial :
		public Material,
		public SharedCreator < PhongMaterial > {
private:
	TexPtr								_ambientMap  =nullptr;
	TexPtr								_diffuseMap  =nullptr;
	TexPtr								_specularMap =nullptr;

    Color       	                    _ambientColor;
    Color   	                        _diffuseColor;
    Color	                            _specularColor;

protected:
    PhongMaterial(MaterialType type);

public:
	PhongMaterial();
	virtual ~PhongMaterial() noexcept override;

	void setUniforms(const ShaderProgram& prg) override;
	virtual void setDrawData(Draw &drawData) override;
	virtual void bindMaps() override;
	void unbindMaps() override;

    void setAmbientColor(const Color color);
    void setDiffuseColor(const Color color);
    void setSpecularColor(const Color color);

    const Color& getAmbientColor() const;
    const Color& getDiffuseColor() const;
    const Color& getSpecularColor() const;

    void setAmbientTexture(TexPtr map);
    void setDiffuseTexture(TexPtr map);
    void setSpecularTexture(TexPtr map);

    TexPtr getAmbientTexture() const;
    TexPtr getDiffuseTexture() const;
    TexPtr getSpecularTexture() const;
};

using PhongMatPtr = std::shared_ptr < PhongMaterial >;

#endif /* PHONGMATERIAL_H_ */
