#include "MassSpringSystemSimulator.h"
#include <list>

MassSpringSystemSimulator::MassSpringSystemSimulator() {
	m_fMass = 0;
	m_fStiffness = 0;
	m_fDamping = 0;
	m_iIntegrator = 0;
	m_iGravity=false;
	m_iGround=false;

	first = true;

	m_vfMovableObjectPos = Vec3();
	m_vfMovableObjectFinalPos = Vec3();

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
	m.mp_mass = m_fMass;

	masspoints.push_back(m);
	return getNumberOfMassPoints()-1;
}

void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength)
{
	Spring s;
	s.smp1index = masspoint1;
	s.smp2index = masspoint2;
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

void MassSpringSystemSimulator::applyExternalForce(Vec3 force)
{
	// ???	
}

// ----------------------- UI Functions ----------------------- //

const char* MassSpringSystemSimulator::getTestCasesStr() {
	return "Empty, 1.1-(Euler),1.1-(Midpoint), Complex, Pyramid";
}

void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass* DUC)
{
	this->DUC = DUC;
	switch (m_iTestCase)
	{
	case 0:break;
	case 1:
		m_iIntegrator = 0;
		first = true;
		TwAddVarRW(DUC->g_pTweakBar, "Gravity", TW_TYPE_BOOLCPP, &m_iGravity, "");
		TwAddVarRW(DUC->g_pTweakBar, "Ground", TW_TYPE_BOOLCPP, &m_iGround, "");
		setMass(10);
		setStiffness(40);
		addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
		addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
		addSpring(0, 1, 1);
		
		break;
	case 2:
		m_iIntegrator = 2;
		first = true;
		TwAddVarRW(DUC->g_pTweakBar, "Gravity", TW_TYPE_BOOLCPP, &m_iGravity, "");
		TwAddVarRW(DUC->g_pTweakBar, "Ground", TW_TYPE_BOOLCPP, &m_iGround, "");
		setMass(10);
		setStiffness(40);
		addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
		addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
		addSpring(0, 1, 1);

		break;
	case 3:
		TwAddVarRW(DUC->g_pTweakBar, "Integration", TW_TYPE_INT32, &m_iIntegrator, "min=0 step=1");
		TwAddVarRW(DUC->g_pTweakBar, "Gravity", TW_TYPE_BOOLCPP , &m_iGravity, "");
		TwAddVarRW(DUC->g_pTweakBar, "Ground", TW_TYPE_BOOLCPP, &m_iGround, "");
		setMass(10);
		setStiffness(40);
		addMassPoint(Vec3(0, 1, 0), Vec3(0, -1, 0), false); //0
		addMassPoint(Vec3(1, 1, 0), Vec3(0, -1, 0), false); //1
		addMassPoint(Vec3(1.5, 1, 1), Vec3(0, -1, 0), false); //2
		addMassPoint(Vec3(0.5, 1, 2), Vec3(0, -1, 0), false); //3
		addMassPoint(Vec3(-0.5, 1, 1), Vec3(0, -1, 0), false); //4
		addMassPoint(Vec3(0, 2, 0), Vec3(0, 0, 0), false); //5
		addMassPoint(Vec3(1, 2, 0), Vec3(0, 0, 0), false); //6
		addMassPoint(Vec3(1.5, 2, 1), Vec3(0.5, 0, 0), false); //7
		addMassPoint(Vec3(0.5, 2, 2), Vec3(0, 0, 0.5), false); //8
		addMassPoint(Vec3(-0.5, 2, 1), Vec3(-0.5, 0, 0), false); //9
		addSpring(0, 1, 2);
		addSpring(1, 2, 2);
		addSpring(2, 3, 2);
		addSpring(3, 4, 2);
		addSpring(4, 0, 2);
		addSpring(5, 6, 2);
		addSpring(6, 7, 2);
		addSpring(7, 8, 2);
		addSpring(8, 9, 2);
		addSpring(9, 5, 2);
		addSpring(0, 5, 2);
		addSpring(1, 6, 2);
		addSpring(2, 7, 2);
		addSpring(3, 8, 2);
		addSpring(4, 9, 2);
		
		break;
	case 4:
		TwAddVarRW(DUC->g_pTweakBar, "Integration", TW_TYPE_INT32, &m_iIntegrator, "min=0 step=1");
		TwAddVarRW(DUC->g_pTweakBar, "Gravity", TW_TYPE_BOOLCPP, &m_iGravity, "");
		TwAddVarRW(DUC->g_pTweakBar, "Ground", TW_TYPE_BOOLCPP, &m_iGround, "");
		setMass(10);
		setStiffness(40);

		addMassPoint(Vec3(0, 0, 0), Vec3(0, 0, 0), false); //0
		addMassPoint(Vec3(0, 0, 1), Vec3(0, 0, 0), false); //1
		addMassPoint(Vec3(1, 0, 1), Vec3(0, 0, 0), false); //2
		addMassPoint(Vec3(1, 0, 0), Vec3(0, 0, 0), false); //3
		addMassPoint(Vec3(0.5, 2 , 0.5), Vec3(0, 1, 0), false); //4
		addSpring(0, 1, 2);
		addSpring(1, 2, 2);
		addSpring(2, 3, 2);
		addSpring(3, 0, 2);
		addSpring(4, 3, 2);
		addSpring(4, 2, 2);
		addSpring(4, 1, 2);
		addSpring(4, 0, 2);
		
	default:break;
	}
}

void MassSpringSystemSimulator::reset() {
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext* pd3dImmediateContext)
{
	for (Masspoint m : masspoints) {
		DUC->setUpLighting(Vec3(), 0.4 * Vec3(1, 1, 1), 100, 0.6 * Vec3(0.97, 0.86, 1));
		DUC->drawSphere(m.mp_position,(0.05, 0.05, 0.05));
	}
	for (Spring s : springs) {
		DUC->setUpLighting(Vec3(), 0.4 * Vec3(1, 1, 1), 100, 0.6 * Vec3(0.97, 0.86, 1));
		DUC->beginLine();
		DUC->drawLine(s.s_mp1.mp_position, Vec3(1, 1, 1), s.s_mp2.mp_position, Vec3(1, 1, 1));
		DUC->endLine();
	}
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase)
{
	m_iTestCase = testCase;
	masspoints.clear();
	springs.clear();
	switch (m_iTestCase)
	{
	case 0:
		cout << "Empty !\n";
		break;
	case 1:
		cout << "1.1-Euler !\n";
		break;
	case 3:
		cout << "Complex!\n";
		break;
	case 2:
		cout << "1.1-Midpoint !\n";
		break;
	case 4:
		cout << "Pyramid !\n";
		break;
	default:
		cout << "Empty Test!\n";
		break;
	}
}

void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed)
{
	// ???
}

void MassSpringSystemSimulator::simulateTimestep(float timeStep)
{
	//TO - DO

	// update current setup for each frame
	switch (m_iIntegrator)
	{// handling different cases
	case 0:
		for (int i = 0; i < getNumberOfMassPoints(); i++) {
			Masspoint m = masspoints.at(i);
			m.mp_force = Vec3(0, 0, 0);
			masspoints.at(i) = m;
		}
		for (int i = 0; i < getNumberOfSprings(); i++) {
			Spring s = springs.at(i);
			Vec3 F = ComputeForce(s);
			ApplyForce(s,F);
			springs.at(i) = s;
		}
		if (m_iGravity) {
			ApplyGravity();
		}
		eulerIntegratePositions(timeStep);
		eulerIntegrateVelocity(timeStep);

		
		if (m_iGround) {
			GroundCheck();
		}



		if (first && m_iTestCase == 1) {
			cout << "System after first timestep " << timeStep << "\n";
			for (int i = 0; i < getNumberOfMassPoints(); i++) {
				Masspoint m = masspoints.at(i);
				cout << "Point" << i << ": Pos=" << m.mp_position << " | Velocity= " << m.mp_velocity << "\n";
			}		
			first = false;
		}
		break;
	case 1:
		//TODO LEAPFROG
		break;
	case 2:
		midpointIntegrate(timeStep);



		if (first && m_iTestCase==2) {
			cout << "System after first timestep " << timeStep << "\n";
			for (int i = 0; i < getNumberOfMassPoints(); i++) {
				Masspoint m = masspoints.at(i);
				cout << "Point" << i << ": Pos=" << m.mp_position << " | Velocity= " << m.mp_velocity << "\n";
			}
			first = false;
		}
		break;
	default:
		break;
	}

	
}

Vec3 MassSpringSystemSimulator::ComputeForce(Spring s)
{
	Vec3 n = s.s_mp1.mp_position - s.s_mp2.mp_position;
	float norm = sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2));
	n = n / norm;

	float F = -m_fStiffness * (abs(PointDistance(s.s_mp1.mp_position, s.s_mp2.mp_position) - s.s_initLength));
	return n*F;
}

float MassSpringSystemSimulator::PointDistance(Vec3 a, Vec3 b) {
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

void MassSpringSystemSimulator::ApplyForce(Spring s, Vec3 F) {
	Masspoint m1 = masspoints.at(s.smp1index);
	Masspoint m2 = masspoints.at(s.smp2index);

	m1.mp_force = m1.mp_force + F;
	m2.mp_force = m2.mp_force - F;

	masspoints.at(s.smp1index) = m1;
	masspoints.at(s.smp2index) = m2;
}

void MassSpringSystemSimulator::ApplyGravity() {
	for (int i = 0; i < getNumberOfMassPoints(); i++) {
		Masspoint m = masspoints.at(i);
		m.mp_force = m.mp_force + (m.mp_mass * Vec3(0, -10, 0));
		masspoints.at(i) = m;
	}
}

void MassSpringSystemSimulator::GroundCheck() {
	for (int i = 0; i < getNumberOfMassPoints(); i++) {
		Masspoint m = masspoints.at(i);
		if (m.mp_position.y <= -1) {
			m.mp_position = Vec3(m.mp_position.x,-1,m.mp_position.z);
			if (m.mp_velocity.y < 0) {
				m.mp_velocity = Vec3(m.mp_velocity.x, -m.mp_velocity.y, m.mp_velocity.z);;
			}
		}
		masspoints.at(i) = m;
	}
}

void MassSpringSystemSimulator::eulerIntegratePositions(float timeStep) {
	for (int i = 0; i < getNumberOfMassPoints();i++) {
		Masspoint m = masspoints.at(i);
		m.mp_position = m.mp_position + (timeStep * m.mp_velocity);
		masspoints.at(i) = m;
	}
	for (int i = 0; i < getNumberOfSprings();i++) {
		Spring s = springs.at(i);
		s.s_mp1 = masspoints[s.smp1index];
		s.s_mp2 = masspoints[s.smp2index];
		springs.at(i) = s;
	}
}

void MassSpringSystemSimulator::eulerIntegrateVelocity(float timeStep) {
	for (int i = 0; i < getNumberOfMassPoints(); i++) {
		Masspoint m = masspoints.at(i);
		m.mp_velocity = m.mp_velocity + (timeStep * (m.mp_force/m.mp_mass));
		masspoints.at(i) = m;
	}
}

void MassSpringSystemSimulator::midpointIntegrate(float timeStep) {

	vector<Masspoint> midpoints;

	for (int i = 0; i < masspoints.size(); i++){
		midpoints.push_back(masspoints[i]);
	}

	for (int i = 0; i < getNumberOfMassPoints(); i++) {
		Masspoint m = masspoints.at(i);
		m.mp_force = Vec3(0, 0, 0);
		masspoints.at(i) = m;
	}

	for (int i = 0; i < getNumberOfSprings(); i++) {
		Spring s = springs.at(i);
		s.s_mp1 = masspoints[s.smp1index];
		s.s_mp2 = masspoints[s.smp2index];
		Vec3 F = ComputeForce(s);
		ApplyForce(s, F);
		springs.at(i) = s;
	}

	for (int i = 0; i < getNumberOfMassPoints(); i++) {
		Masspoint m = masspoints.at(i);
		m.mp_position = m.mp_position + ((timeStep / 2) * m.mp_velocity);
		m.mp_velocity = m.mp_velocity + ((timeStep / 2) * m.mp_force/ m.mp_mass);
		midpoints.at(i) = m;

		Masspoint n = masspoints.at(i);
		n.mp_force = Vec3(0, 0, 0);
		masspoints.at(i) = n;
	}

	for (int i = 0; i < getNumberOfSprings(); i++) {
		Spring s = springs.at(i);
		s.s_mp1 = midpoints[s.smp1index];
		s.s_mp2 = midpoints[s.smp2index];
		Vec3 F = ComputeForce(s);
		ApplyForce(s, F);
		springs.at(i) = s;
	}

	if (m_iGravity) {
		ApplyGravity();
	}

	for (int i = 0; i < getNumberOfMassPoints(); i++) {
		Masspoint m = masspoints.at(i);
		m.mp_position = m.mp_position + (timeStep * midpoints.at(i).mp_velocity);
		m.mp_velocity = m.mp_velocity + (timeStep * m.mp_force/m.mp_mass);
		masspoints.at(i) = m;
	}

	if (m_iGround) {
		GroundCheck();
	}
	
}


// ----------------------- Mouse Fuctions ----------------------- //

void MassSpringSystemSimulator::onClick(int x, int y)
{
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

void MassSpringSystemSimulator::onMouse(int x, int y)
{
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}