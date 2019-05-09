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
     * @todo More doc.
     **/
    void add(Toplevel *toplevel);

    /**
     * Removes given Toplevel from the StackingOrder.
     *
     * @todo More doc.
     **/
    void remove(Toplevel *toplevel);

    /**
     *
     **/
    void replace(Toplevel *before, Toplevel *after);

    /**
     * Moves given Toplevel to the top of its layer.
     *
     * @todo More doc.
     **/
    void raise(Toplevel *toplevel);

    /**
     * Moves given Toplevel to the bottom of its layer.
     *
     * @todo More doc.
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
     * Returns toplevels in the StackingOrder.
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
    void shift(int start, int end);

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
