#pragma once

// Ein Enum um die verschiedenen Gegnertypen zu identifizieren.
namespace enemy {
    enum class EnemyType {
        STANDARD_VAMPIRE,
        // ... hier weitere Typen hinzufügen
    };
}

// Diese Datei dient als Sammelstelle für alle Gegner-Header.
#include "StandardVampire.h"


// #include "NeuerGegner.h" // Hier kommen zukünftige Gegner hin