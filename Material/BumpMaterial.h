/*
 * BumpMaterial.h
 *
 *  Created on: Apr 26, 2021
 *      Author: bit_creator
 */

#ifndef MATERIAL_BUMPMATERIAL_H_
#define MATERIAL_BUMPMATERIAL_H_

#include "../CreateAsPointer.hpp"
#include "PhongMaterial.h"

class BumpMaterial final : virtual
		public PhongMaterial
//		public SharedCreator < BumpMaterial >
{
private:
	TexPtr								_normalMap   =nullptr;
	TexPtr								_heightMap   =nullptr;

public:
	BumpMaterial();
	virtual ~BumpMaterial() noexcept override;
	float 				_scale = 0.2;

	void bindMaps() override;
	void setDrawData(Draw &drawData) override;
	void setUniforms(const ShaderProgram& prg) override;
	void unbindMaps() override;

    void setNormalTexture(TexPtr map);
    void setHeightTexture(TexPtr map);

    TexPtr getNormalTexture() const noexcept;
    TexPtr getHeightTexture() const noexcept;
};

using BumpMatPtr = std::shared_ptr < BumpMaterial >;

#endif /* MATERIAL_BUMPMATERIAL_H_ */
