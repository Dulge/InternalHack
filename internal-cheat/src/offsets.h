#pragma once

#include "pch.h"

namespace offsets
{
	unsigned int health = 0xf8;
	unsigned int armour = 0xfc;
	unsigned int grenade = 0x158;
	std::vector<unsigned int> currentAmmo{ 0x374, 0x14, 0x0 };
	std::vector<unsigned int> clipAmmo{ 0x374, 0x14, 0x10 };
}