#pragma once

namespace mem
{
	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);

	void Patch(BYTE* dst, BYTE* src, unsigned int size);
	void Nop(BYTE* dst, unsigned int size);
}
