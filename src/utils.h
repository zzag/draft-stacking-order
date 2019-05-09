#pragma once

// Qt
#include <QList>

namespace KWin
{

class Client;
class Toplevel;

typedef QList<Client *> ClientList;
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