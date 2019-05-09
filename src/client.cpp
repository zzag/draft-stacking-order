#include "client.h"

namespace KWin
{

Client::Client(QObject *parent)
    : Toplevel(parent)
{
}

Group *Client::group() const
{
    return nullptr;
}

} // namespace KWin
