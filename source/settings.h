#pragma once
#include "pch.h"
#include <imgui.h>

// ESG
DataPointer(int, esgFlag, 0x174B08C);

class Settings {
public:
	Settings() {};
	void RenderTab();
};
