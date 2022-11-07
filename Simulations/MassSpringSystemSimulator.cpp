#include "MassSpringSystemSimulator.h"
#include <list>

MassSpringSystemSimulator::MassSpringSystemSimulator() {
	m_fMass = 0;
	m_fStiffness = 0;
	m_fDamping = 0;
	m_iIntegrator = 0;

	vector<Masspoint> masspoints;
	vector<Spring> springs;
}

void MassSpringSystemSimulator::setMass(float mass)
{
	m_fMass = mass;
}

void MassSpringSystemSimulator::setStiffness(float stiffness)
{
	m_fStiffness = stiffness;
}

void MassSpringSystemSimulator::setDampingFactor(float damping)
{
	m_fDamping = damping;
}

//---------------------------------//

int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 Velocity, bool isFixed)
{
	Masspoint m;
	m.mp_position = position;
	m.mp_velocity = Velocity;
	m.mp_isFixed = isFixed;

	masspoints.push_back(m);
	return 0; // Why return int?
}

void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength)
{
	Spring s;
	s.s_mp1 = masspoints[masspoint1];
	s.s_mp2 = masspoints[masspoint2];
	s.s_initLength = initialLength;
	springs.push_back(s);

}

//---------------------------------//

int MassSpringSystemSimulator::getNumberOfMassPoints()
{
	return masspoints.size();
}

int MassSpringSystemSimulator::getNumberOfSprings()
{
	return springs.size();
}

Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index)
{
	return masspoints[index].mp_position;
}

Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index)
{
	return masspoints[index].mp_velocity;
}

//---------------------------------//

void MassSpringSystemSimulator::applyExternalForce(Vec3 force)
{
}
