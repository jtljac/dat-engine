#include "IWindow.h"

#include "IGpu.h"
#include "util/CVar.h"

using namespace DatEngine;

CVarInt windowWidthCVar("IWindowWidth", "The width of the game window", CVarCategory::Graphics, 1280, CVarFlags::Persistent);
CVarInt windowHeightCVar("IWindowHeight", "The height of the game window", CVarCategory::Graphics, 720, CVarFlags::Persistent);
CVarEnum windowModeCVar("EWindowMode", "How to display the game window", CVarCategory::Graphics, DatGpu::WindowMode::Windowed, CVarFlags::Persistent);

DatMaths::uvec2 IWindow::getDimensions() { return {}; }
