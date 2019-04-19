#include "StackingOrder.h"

namespace KWin
{

StackingOrder::StackingOrder(QObject *parent)
    : QObject(parent)
{
}

StackingOrder::~StackingOrder()
{
}

void StackingOrder::add(Toplevel *toplevel)
{
    Q_UNUSED(toplevel)
}

void StackingOrder::remove(Toplevel *toplevel)
{
    Q_UNUSED(toplevel)
}

void StackingOrder::replace(Toplevel *before, Toplevel *after)
{
    Q_UNUSED(before)
    Q_UNUSED(after)
}

void StackingOrder::raise(Toplevel *toplevel)
{
    Q_UNUSED(toplevel)
}

void StackingOrder::lower(Toplevel *toplevel)
{
    Q_UNUSED(toplevel)
}

void StackingOrder::restack(const ToplevelList &toplevels)
{
    Q_UNUSED(toplevels)
}

void StackingOrder::restack(Toplevel *below, Toplevel *above)
{
    Q_UNUSED(below)
    Q_UNUSED(above)
}

void StackingOrder::constrain(Toplevel *below, Toplevel *above)
{
    Q_UNUSED(below)
    Q_UNUSED(above)
}

void StackingOrder::unconstrain(Toplevel *below, Toplevel *above)
{
    Q_UNUSED(below)
    Q_UNUSED(above)
}

ToplevelList StackingOrder::toplevels() const
{
    return ToplevelList();
}

} // namespace KWin
