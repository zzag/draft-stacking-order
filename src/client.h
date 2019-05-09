#pragma once

// Own
#include "toplevel.h"

namespace KWin
{

class Group;

class Client : public Toplevel
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);

    Group *group() const;

private:
    Q_DISABLE_COPY(Client)
};

} // namespace KWin
