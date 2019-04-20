#include "Toplevel.h"

namespace KWin
{

Toplevel::Toplevel(QObject *parent)
    : QObject(parent)
{
}

Toplevel::~Toplevel()
{
}

Layer Toplevel::layer() const
{
    return m_layer;
}

void Toplevel::setLayer(Layer layer)
{
    m_layer = layer;
}

} // namespace KWin
