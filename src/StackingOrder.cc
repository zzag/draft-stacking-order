#include "StackingOrder.h"

namespace KWin
{

StackingOrder::StackingOrder(QObject *parent)
    : QObject(parent)
{
}

StackingOrder::~StackingOrder()
{
    qDeleteAll(m_constraints);
}

void StackingOrder::add(Toplevel *toplevel)
{
    m_toplevels << toplevel;
}

void StackingOrder::remove(Toplevel *toplevel)
{
    m_toplevels.removeOne(toplevel);

    for (int i = m_constraints.count() - 1; i >= 0; --i) {
        Constraint *constraint = m_constraints[i];
        const bool isBelow = (constraint->below == toplevel);
        const bool isAbove = (constraint->above == toplevel);
        if (!isBelow || !isAbove) {
            continue;
        }
        if (isBelow) {
            for (Constraint *child : constraint->children) {
                child->parents.removeOne(constraint);
            }
        } else {
            for (Constraint *parent : constraint->parents) {
                parent->children.removeOne(constraint);
            }
        }
        delete m_constraints.takeAt(i);
    }
}

void StackingOrder::replace(Toplevel *before, Toplevel *after)
{
    const int index = m_toplevels.indexOf(before);
    Q_ASSERT(index != -1);

    m_toplevels[index] = after;

    for (Constraint *constraint : m_constraints) {
        if (constraint->below == before) {
            constraint->below = after;
        } else if (constraint->above == before) {
            constraint->above = after;
        }
    }
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
    if (below == above) {
        return;
    }

    QVector<Constraint *> parents;
    QVector<Constraint *> children;
    for (Constraint *constraint : m_constraints) {
        if (constraint->below == below && constraint->above == above) {
            return;
        }
        if (constraint->below == above) {
            children << constraint;
        } else if (constraint->above == below) {
            parents << constraint;
        }
    }

    Constraint *constraint = new Constraint();
    constraint->parents = parents;
    constraint->below = below;
    constraint->above = above;
    constraint->children = children;
    m_constraints << constraint;

    for (Constraint *parent : qAsConst(parents)) {
        parent->children << constraint;
    }

    for (Constraint *child : qAsConst(children)) {
        child->parents << constraint;
    }
}

void StackingOrder::unconstrain(Toplevel *below, Toplevel *above)
{
    Constraint *constraint = nullptr;
    for (int i = 0; i < m_constraints.count(); ++i) {
        if (m_constraints[i]->below != below) {
            continue;
        }
        if (m_constraints[i]->above != above) {
            continue;
        }
        constraint = m_constraints.takeAt(i);
        break;
    }

    if (!constraint) {
        return;
    }

    for (Constraint *parent : constraint->parents) {
        parent->children.removeOne(constraint);
    }

    for (Constraint *child : constraint->children) {
        child->parents.removeOne(constraint);
    }

    delete constraint;
}

ToplevelList StackingOrder::toplevels() const
{
    return m_toplevels;
}

void StackingOrder::evaluateConstraints()
{
}

void StackingOrder::evaluateLayers()
{
}

} // namespace KWin
