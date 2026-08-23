#include "../../minirt.h" 

uint32_t	rgb_to_hex(uint8_t rgb[3])
{
	return (((uint32_t)rgb[0] << 24)
		| ((uint32_t)rgb[1] << 16)
		| ((uint32_t)rgb[2] << 8)
		| 0xFF);
}
