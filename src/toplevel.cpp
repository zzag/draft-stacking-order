#include "toplevel.h"

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

int Toplevel::screen() const
{
    return m_screen;
}

void Toplevel::setScreen(int screen)
{
    m_screen = screen;
}

NET::WindowType Toplevel::windowType() const
{
    return m_windowType;
}

void Toplevel::setWindowType(NET::WindowType type)
{
    m_windowType = type;
}

int Toplevel::stackPosition() const
{
    return m_stackPosition;
}

void Toplevel::setStackPosition(int position)
{
    m_stackPosition = position;
}

} // namespace KWin
