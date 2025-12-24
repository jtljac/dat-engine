#include "Localisation.h"

#include <util/CVar.h>

using namespace DatEngine;

CVarString localeCVar("SLocale", "The locale the engine should use for localisation", CVarCategory::General, "en-US", CVarFlags::Persistent);

