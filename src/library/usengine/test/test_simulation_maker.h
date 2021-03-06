#ifndef TEST_MODEL_PARSER_H
#define TEST_MODEL_PARSER_H

#include <usbase/test/autotest.h>

namespace UniSim {
	class Simulation;	
}

class TestSimulationMaker : public QObject
{
    Q_OBJECT
private slots:
	void initTestCase();
	void testSimulation();
	void testModel();
	void testParameters();
	void testOutputOneXY();
	void testOutputManyXY();
	void testXmlQuery();
	void cleanupTestCase();
private:
    UniSim::Simulation *_simulation;
};

DECLARE_TEST(TestSimulationMaker)

#endif
