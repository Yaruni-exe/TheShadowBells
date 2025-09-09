#pragma once

// Ein Enum um die verschiedenen Gegnertypen zu identifizieren.
namespace enemy {
    enum class EnemyType {
        STANDARD_VAMPIRE,
        SPECIAL_VAMPIRE,
        // ... hier weitere Typen hinzufügen
    };
}

// Diese Datei dient als Sammelstelle für alle Gegner-Header.
#include "StandardVampire.h"
#include "SpecialVampire.h"
