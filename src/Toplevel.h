#pragma once

// Own
#include "utils.h"

// Qt
#include <QObject>

namespace KWin
{

class Q_DECL_EXPORT Toplevel : public QObject
{
    Q_OBJECT

public:
    explicit Toplevel(QObject *parent = nullptr);
    ~Toplevel() override;

    Layer layer() const;
    void setLayer(Layer layer);

private:
    Layer m_layer = NormalLayer;

    Q_DISABLE_COPY(Toplevel)
};

} // namespace KWin
