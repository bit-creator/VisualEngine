/*
 * GlossyMaterialt.h
 *
 *  Created on: Apr 26, 2021
 *      Author: bit_creator
 */

#ifndef MATERIAL_GLOSSYMATERIAL_H_
#define MATERIAL_GLOSSYMATERIAL_H_

#include "../CreateAsPointer.hpp"
#include "Material.h"

class GlossyMaterial final :
		public Material,
		public SharedCreator < GlossyMaterial > {
private:
	glm::vec4								_color;
	float 									_1RefInd;
	float 									_2RefInd;

public:
	GlossyMaterial();
	virtual ~GlossyMaterial() noexcept override;

	void setUniforms(const ShaderProgram& prg) override;
	void unbindMaps() override;
	void bindMaps() override;
	void setDrawData(Draw &drawData) override;

	void set1RefInd(float firstRefInd);
	void set2RefInd(float secondRefInd);
	void setColor(const glm::vec4 &color);

	float get1RefInd() const;
	float get2RefInd() const;
	const glm::vec4& getColor() const;
};

using GlossyMatPtr = std::shared_ptr < GlossyMaterial >;

#endif /* MATERIAL_GLOSSYMATERIAL_H_ */
