#pragma once

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

private:
    Q_DISABLE_COPY(Toplevel)
};

} // namespace KWin
