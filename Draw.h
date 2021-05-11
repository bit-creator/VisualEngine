/*
 * Draw.h
 *
 *  Created on: 19 квіт. 2021 р.
 *      Author: IAbernikhin
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <functional>
#include <string>
#include <bitset>

static constexpr int NUM_OF_BINARY_PARAM = 8;

struct Draw {
	int						 	_type 			=0;
	int							_attribHash 	=0;
	int 						_renderTargets 	=0;
	int							_numOfLight 	=1;

	bool						_hasAmbientMap  =false;
	bool						_hasDiffuseMap  =false;
	bool						_hasSpecularMap =false;
	bool						_hasRougnessMap =false;
	bool						_hasNormalMap   =false;
	bool						_hasHeightMap	=false;
	bool						_hasSkyBoxMap   =false;

	bool						_hasPerspectiveCamera =false;

	std::string genDefines() const;

	friend bool operator ==(const Draw& lhs, const Draw& rhs) noexcept;
};

template <  >
struct std::hash<Draw> {
	size_t operator ()(const Draw& draw) const noexcept {
		// same as boost::hash_combine()
		auto hasher = [](size_t& seed, size_t val) mutable -> void {
			seed ^= val + 0x9e3779b9 + (seed<<6) + (seed>>2);
		};

		size_t seed = draw._type;

		hasher(seed, draw._attribHash);
		hasher(seed, draw._renderTargets);
		hasher(seed, draw._numOfLight);

		std::bitset<NUM_OF_BINARY_PARAM> param;

		param[0] = draw._hasAmbientMap;
		param[1] = draw._hasDiffuseMap;
		param[2] = draw._hasSpecularMap;
		param[3] = draw._hasRougnessMap;
		param[4] = draw._hasNormalMap;
		param[5] = draw._hasHeightMap;
		param[6] = draw._hasSkyBoxMap;
		param[7] = draw._hasPerspectiveCamera;

		hasher(seed, param.to_ullong());

		return seed;
	}
};

#endif /* DRAW_H_ */
