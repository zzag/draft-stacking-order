#pragma once

// Own
#include "utils.h"

// KF
#include <NETWM>

// Qt
#include <QObject>

namespace KWin
{

class StackingOrder;

class Q_DECL_EXPORT Toplevel : public QObject
{
    Q_OBJECT

public:
    explicit Toplevel(QObject *parent = nullptr);
    ~Toplevel() override;

    Layer layer() const;
    void setLayer(Layer layer);

    int screen() const;
    void setScreen(int screen);

    NET::WindowType windowType() const;
    void setWindowType(NET::WindowType type);

private:
    /**
     * Used internally by the StackingOrder class.
     * @internal
     **/
    int stackPosition() const;
    void setStackPosition(int position);

    int m_stackPosition = -1;
    int m_screen = 0;
    Layer m_layer = NormalLayer;
    NET::WindowType m_windowType = NET::Normal;

    friend class StackingOrder;

    Q_DISABLE_COPY(Toplevel)
};

} // namespace KWin
