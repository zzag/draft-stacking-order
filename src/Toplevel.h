#pragma once

// Own
#include "utils.h"

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

private:
    int stackPosition() const;
    void setStackPosition(int position);

    int m_stackPosition = -1;
    Layer m_layer = NormalLayer;

    friend class StackingOrder;

    Q_DISABLE_COPY(Toplevel)
};

} // namespace KWin
