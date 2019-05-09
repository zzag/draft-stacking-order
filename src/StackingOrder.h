#pragma once

// Own
#include "utils.h"

// Qt
#include <QObject>
#include <QVector>

// std
#include <functional>

namespace KWin
{

/**
 *
 **/
class Q_DECL_EXPORT StackingOrder : public QObject
{
    Q_OBJECT

public:
    explicit StackingOrder(QObject *parent = nullptr);
    ~StackingOrder() override;

    /**
     * Adds given Toplevel to the StackingOrder.
     *
     * The toplevel will be placed at the top of the layer it belongs to.
     *
     * Addition of a toplevel that is already present in the stacking order will
     * lead to undefined behavior.
     *
     * @param toplevel A toplevel to be added to the stacking order.
     **/
    void add(Toplevel *toplevel);

    /**
     * Removes given Toplevel from the StackingOrder.
     *
     * If there exist constraints that are applied to the given toplevel, then
     * they will be removed together with it. So, calling unconstrain() method
     * is optional.
     *
     * It's a fatal error to remove a toplevel that is not in the stacking order.
     *
     * @param toplevel A toplevel to be removed from the stacking order.
     **/
    void remove(Toplevel *toplevel);

    /**
     * Replaces the given toplevel with another one.
     *
     * Eventually a toplevel(e.g. Client, Unmanaged, etc) will become Deleted.
     * Deleted exists solely for animation purposes, e.g. fade out closed window,
     * etc. Given that those two are completely different objects, we need to
     * swap them directly in the stacking order to preserve stack position as
     * well applied constraints.
     *
     * Replacing a toplevel that is not part of the stacking order will lead
     * to a fatal error.
     *
     * @param before A toplevel to be replaced.
     * @param after The replacement.
     **/
    void replace(Toplevel *before, Toplevel *after);

    /**
     * Moves given Toplevel to the top of its layer.
     *
     * @param toplevel A toplevel to be raised.
     **/
    void raise(Toplevel *toplevel);

    /**
     * Moves given Toplevel to the bottom of its layer.
     *
     * @param toplevel A toplevel to be lowered.
     **/
    void lower(Toplevel *toplevel);

    /**
     *
     **/
    void restack(const ToplevelList &toplevels);

    /**
     *
     **/
    void restack(Toplevel *below, Toplevel *above);

    /**
     *
     **/
    void constrain(Toplevel *below, Toplevel *above);

    /**
     *
     **/
    void unconstrain(Toplevel *below, Toplevel *above);

    /**
     * Returns toplevels in the stacking order.
     *
     * The first value corresponds to the bottom-most toplevel, and the last
     * value corresponds to the top-most toplevel.
     **/
    ToplevelList toplevels() const;

    /**
     *
     **/
    void rebuild();

    /**
     * Returns the top-most toplevel in the given @p layer.
     *
     * If there is no such a toplevel, @c null will be returned.
     **/
    Toplevel *findTopMost(Layer layer);

    /**
     * Returns the top-most toplevel that satisfies given @p filter.
     *
     * If there is no such a toplevel, @c null will be returned.
     **/
    Toplevel *findTopMost(std::function<bool(const Toplevel *)> filter);

    /**
     * Returns the bottom-most toplevel in the given @p layer.
     *
     * If there is no such a toplevel, @c null will be returned.
     **/
    Toplevel *findBottomMost(Layer layer);

    /**
     * Returns the bottom-most toplevel that satisfies given @p filter.
     *
     * If there is no such a toplevel, @c null will be returned.
     **/
    Toplevel *findBottomMost(std::function<bool(const Toplevel *)> filter);

Q_SIGNALS:
    /**
     * Emitted when the stacking order has changed.
     **/
    void changed();

private:
    void evaluateConstraints();
    void evaluateLayers();
    void fixUp(int start, int end);

    ToplevelList m_toplevels;

    struct Constraint
    {
        Toplevel *below;
        Toplevel *above;
        QVector<Constraint *> parents;
        QVector<Constraint *> children;

        // Used to prevent cycles.
        bool enqueued = false;
    };
    QVector<Constraint *> m_constraints;

    Q_DISABLE_COPY(StackingOrder)
};

} // namespace KWin
