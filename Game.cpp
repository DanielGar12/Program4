
#include "Game.h"

#include "GameDefines.h"
#include "Renderer.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "Descriptors.h"

#include "shellapi.h"


void CGame::Initialize() {
	
	initPhysics();

}

void CGame::initPhysics() {
	
    //definitions
	m_pConfig = new btDefaultCollisionConfiguration();
	m_pDispatcher = new btCollisionDispatcher(m_pConfig);
	m_pBroadphase = new btDbvtBroadphase();
	m_pSolver = new btSequentialImpulseConstraintSolver;

	m_pPhysicsWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pConfig);

	m_pPhysicsWorld->setGravity(btVector3(0, -9.8f, 0));
	
    //Ground plane
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
    btDefaultMotionState* groundMotion = new btDefaultMotionState(
        btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundCI(0.0f, groundMotion, groundShape, btVector3(0, 0, 0));
    m_pGroundBody = new btRigidBody(groundCI);
    m_pPhysicsWorld->addRigidBody(m_pGroundBody);

    //Falling cube
    btCollisionShape* cube = new btBoxShape(btVector3(1, 1, 1));
    btScalar mass = 1.0f;
    btVector3 inertia(0, 0, 0);
    cube->calculateLocalInertia(mass, inertia);

    btDefaultMotionState* cubeMotion = new btDefaultMotionState(
        btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
    btRigidBody::btRigidBodyConstructionInfo cubeCI(mass, cubeMotion, cube, inertia);
    m_pFallingBody = new btRigidBody(cubeCI);
    m_pPhysicsWorld->addRigidBody(m_pFallingBody);
}

// Step physics simulation
void CGame::Update() {
    if (!m_pPhysicsWorld) return;
    m_pPhysicsWorld->stepSimulation(1.0f / 60.0f);

    // displayu cube position
    btTransform trans;
    m_pFallingBody->getMotionState()->getWorldTransform(trans);
    btVector3 position = trans.getOrigin();
  
}

// Render frame 
void CGame::renderFrame() {
 
    btTransform trans;
    m_pFallingBody->getMotionState()->getWorldTransform(trans);
    btVector3 position = trans.getOrigin();

}

// Main game loop
void CGame::ProcessFrame() {
    Update();
    renderFrame();
}

// Cleanup 
void CGame::Cleanup() {
    if (m_pPhysicsWorld) {
        if (m_pFallingBody) {
            m_pPhysicsWorld->removeRigidBody(m_pFallingBody);
            delete m_pFallingBody->getMotionState();
            delete m_pFallingBody->getCollisionShape();
            delete m_pFallingBody;
            m_pFallingBody = nullptr;
        }
        if (m_pGroundBody) {
            m_pPhysicsWorld->removeRigidBody(m_pGroundBody);
            delete m_pGroundBody->getMotionState();
            delete m_pGroundBody->getCollisionShape();
            delete m_pGroundBody;
            m_pGroundBody = nullptr;
        }

        delete m_pPhysicsWorld;
        delete m_pSolver;
        delete m_pBroadphase;
        delete m_pDispatcher;
        delete m_pCollisionConfig;

        m_pPhysicsWorld = nullptr;
        m_pSolver = nullptr;
        m_pBroadphase = nullptr;
        m_pDispatcher = nullptr;
        m_pCollisionConfig = nullptr;
    }
}

CGame::~CGame() {
    Cleanup();
}