/* Copyright (C) 2009-2010 by Niels Holst [niels.holst@agrsci.dk] and co-authors.
** Copyrights reserved.
** Released under the terms of the GNU General Public License version 3.0 or later.
** See www.gnu.org/copyleft/gpl.html.
*/
#include <usbase/utilities.h>
#include "assimilation_max_given_temp_sla.h"
#include "plant.h"

using namespace UniSim;

namespace intercom{

AssimilationMaxGivenTempSla::AssimilationMaxGivenTempSla(UniSim::Identifier name, QObject *parent)
	: Model(name, parent)
{
    setState("amax", &amax);
}

void AssimilationMaxGivenTempSla::initialize()
{
    setParameter("pctN", &pctN, 0.040);
    weather = findOne<Model*>("weather");
    Model *plant = findAscendant<Plant*>("*");
    specificLeafArea = findOne<Model*>("specificLeafArea", plant);
}

void AssimilationMaxGivenTempSla::reset() {
    amax = 0.;
}

void AssimilationMaxGivenTempSla::update()
{
    double sla = specificLeafArea->state("sla");
    double Tday = weather->state("Tday");
    amax=(16.92-16.92*pow(0.88, Tday))*pctN/sla/10.;
    if (amax < 0.)
        amax = 0.;
}


} //namespace
