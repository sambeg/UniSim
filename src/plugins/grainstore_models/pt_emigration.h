/* Copyright (C) 2009-2010 by Niels Holst [niels.holst@agrsci.dk] and co-authors.
** Copyrights reserved.
** Released under the terms of the GNU General Public License version 3.0 or later.
** See www.gnu.org/copyleft/gpl.html.
*/
#ifndef GRAINSTORE_PTEMIGRATION
#define GRAINSTORE_PTEMIGRATION
#include <QObject>
#include <usbase/model.h>

namespace grainstore{

class PtEmigration : public UniSim::Model
{
	Q_OBJECT
public: 
	PtEmigration(UniSim::Identifier name, QObject *parent=0);
	//standard methods
	void initialize();
	void reset();
	void update();

private:
	// parameters
	double Ninit, K, r;

	// state
	double density;

};

} //namespace
#endif
