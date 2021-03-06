/***************************************************************************
 *   Copyright (C) 2005-2016 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "clienttransfermanager.h"

#include "client.h"
#include "clienttransfer.h"

INIT_SYNCABLE_OBJECT(ClientTransferManager)

void ClientTransferManager::onCoreTransferAdded(const QUuid &uuid)
{
    if (uuid.isNull()) {
        qWarning() << Q_FUNC_INFO << "Invalid transfer uuid" << uuid.toString();
        return;
    }

    auto transfer = new ClientTransfer(uuid, this);
    connect(transfer, SIGNAL(initDone()), SLOT(onTransferInitDone())); // we only want to add initialized transfers
    Client::signalProxy()->synchronize(transfer);
}


void ClientTransferManager::onTransferInitDone()
{
    Transfer *transfer = qobject_cast<Transfer *>(sender());
    Q_ASSERT(transfer);
    addTransfer(transfer);
}
