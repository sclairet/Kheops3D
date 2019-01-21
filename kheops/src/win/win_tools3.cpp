

#include "core3.h"
#include <assert.h>
#include <windows.h>
#include "win_tools3.h"



namespace KHEOPS
{



EKey VirtualKeyCodeToKheopsKey( unsigned int inVirtualKeyCode)
{
	switch (inVirtualKeyCode)
	{
	case VK_LEFT:
		return eKeyLeft;

	case VK_UP:
		return eKeyUp;

	case VK_RIGHT:
		return eKeyRight;

	case VK_DOWN:
		return eKeyDown;

	case VK_SPACE:
		return  eKeySpace;

	default:
		return eUndefinedKey;
	}
}



} // namespace KHEOPS