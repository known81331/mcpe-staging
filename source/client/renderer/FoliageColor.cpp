#include "FoliageColor.hpp"

bool FoliageColor::_isAvailable = false;

Texture FoliageColor::texture;

void FoliageColor::init(Texture texture)
{
	FoliageColor::texture = texture;
}

uint32_t FoliageColor::get(double x, double y)
{
	//printf("FoliageColor::get(%f, %f) -> %06x\n", x, y,  FoliageColor::texture.m_pixels[(int)((1.0 - y) * 255.0) << 8 | (int)((1.0 - x) * 255.0)]);
	y *= x;
	return FoliageColor::texture.m_pixels[(int)((1.0 - y) * 255.0) << 8 | (int)((1.0 - x) * 255.0)];
}

#ifdef EHN_PE_GRASS_COLOR
uint32_t FoliageColor::getEvergreenColor()
{
	return 0x619961;
}

uint32_t FoliageColor::getBirchColor()
{
	return 0x55A780;
}

uint32_t FoliageColor::getDefaultColor()
{
	return 0x18B548;
}

#else

//1
uint32_t FoliageColor::getEvergreenColor()
{
	return 0x619961;
}

//2
uint32_t FoliageColor::getBirchColor()
{
	return 0x80a755;
}

//3
uint32_t FoliageColor::getDefaultColor()
{
	return 0x48b518;
}

#endif