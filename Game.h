/// \file Game.h
/// \brief Interface for the game class CGame.

#ifndef __L4RC_GAME_GAME_H__
#define __L4RC_GAME_GAME_H__

#include "Component.h"
#include "Common.h"
#include "Settings.h"
#include "Object.h"
#include "btBulletDynamicsCommon.h"



class CGame: 
  public LComponent, 
  public LSettings,
  public CCommon
{
  private:
    float m_fStartTime = 0; ///< Game start time.
  
   

    
    void initPhysics();
    void Update();
    void Cleanup();

 
    void renderFrame();

  public:
    ~CGame(); ///< Destructor.

    void Initialize(); ///< Initialize the game.
    void ProcessFrame(); ///< Process an animation frame.
}; //CGame

#endif //__L4RC_GAME_GAME_H__
