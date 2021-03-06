/* Copyright (C) 2009-2010 by Niels Holst [niels.holst@agrsci.dk] and co-authors.
** Copyrights reserved.
** Released under the terms of the GNU General Public License version 3.0 or later.
** See www.gnu.org/copyleft/gpl.html.
*/
#include "file_location_dialog.h"
#include "file_locations_forgiving.h"

#include <QFileDialog>
#include <QMessageBox>


FileLocationsForgiving::FileLocationsForgiving()
    : FileLocations() {
}

QDir FileLocationsForgiving::locationImpl(FileType fileType) {
    if (contain(fileType)) {
        QDir dir = locations[fileType];
        if (dir.exists()) return dir;
    }
    else if (lookupImpl(fileType))
        return locationImpl(fileType);
    return QDir();
}

bool FileLocationsForgiving::lookupImpl(FileType fileType, QString message) {
    QString msg = message + (message.isEmpty() ? "" : "\n\n") + hint(fileType);
    QMessageBox::information(0, "Guidance", msg);

    FileLocationDialog dialog(fileType);
    if (dialog.exec()) {
        setLocation(fileType, dialog.location());
        return true;
    }
    return false;
}

