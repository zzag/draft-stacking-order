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
 * This class is responsibe for maintaining the stacking order.
 *
 * Every toplevel has a layer assigned to it. Currently, there are 10 layers, from
 * bottom to top: desktop layer, below layer, normal layer, dock layer, above layer,
 * notification layer, active layer (used for placing fullscreen clients), critical
 * notifications layer, on screen display layer, and unmanaged layer. For more
 * details please take a look at Layer enum.
 *
 * The layer a toplevel is in depends on the window type, and some other things,
 * like whether the window is active. In rare cases, a client can be promoted to
 * upper layers if it's a dialog or an utility.
 **/
class Q_DECL_EXPORT StackingOrder : public QObject
{
    Q_OBJECT

public:
    explicit StackingOrder(QObject *parent = nullptr);
    ~StackingOrder() override;

    /**
     * Adds the given toplevel to the stacking order.
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
     * Removes the given toplevel from the stacking order.
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
     * Moves the given toplevel to the top of its layer.
     *
     * If the toplevel is a subject to constraints, then it's possible that two
     * or more toplevels will be raised together with @p toplevel.
     *
     * @param toplevel A toplevel to be raised.
     **/
    void raise(Toplevel *toplevel);

    /**
     * Moves the given toplevel to the bottom of its layer.
     *
     * @param toplevel A toplevel to be lowered.
     **/
    void lower(Toplevel *toplevel);

    /**
     * Restacks toplevels according to the specified order.
     *
     * If some of toplevels are constrained, then the desired order might be not
     * completely preserved.
     *
     * @param toplevels Desired order of toplevels.
     **/
    void restack(const ToplevelList &toplevels);

    /**
     * Restacks one toplevel below the other one.
     *
     * This method does nothing if @p below is already below @p above.
     *
     * It's a fatal error if any of two toplevels is not in the stacking order.
     **/
    void restack(Toplevel *below, Toplevel *above);

    /**
     * Creates a below-above constraint between the given two toplevels.
     *
     * This method adds a constraint that ensures @p below will be always kept
     * below @p above until unconstrain() method is called. The main difference
     * between this method and restack() is that the latter has temporary effect,
     * while the former has permanent effect.
     *
     * @param below A toplevel that has to be kept below @c above.
     * @param above A toplevel that has to be kept above @c below.
     **/
    void constrain(Toplevel *below, Toplevel *above);

    /**
     * Breaks below-above constraint between the given two toplevels.
     *
     * It is safe to call this method if there is no such a constraint between
     * @p below and @p above.
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
