#include "pch.h"
#include "spirv_cross_dll_api.h"

Attempt::Attempt(int x)
{
	this->x = x;
}

int Attempt::adding(int y)
{
	return this->x + y;
}


