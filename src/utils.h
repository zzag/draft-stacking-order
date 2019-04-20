#pragma once

// Qt
#include <QList>

namespace KWin
{

class Toplevel;
typedef QList<Toplevel *> ToplevelList;

enum Layer {
    FirstLayer = 0,
    BelowLayer = FirstLayer,
    NormalLayer,
    AboveLayer,
    NumLayers
};

inline void operator++(Layer &layer)
{
    layer = static_cast<Layer>(layer + 1);
}

} // namespace KWin