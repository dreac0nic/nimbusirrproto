#include <irrlicht.h>

using namespace irr;
using namespace core;

class RTSControlReceiver : public IEventReceiver
{
public:
  virtual bool OnEvent(const SEvent& event)
  {
    if(event.EventType == EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    
    return false;
  }
  
  virtual bool IsKeyDown(EKEY_CODE keyCode) const
  {
    return KeyIsDown[keyCode];
  }
  
  RTSControlReceiver()
  {
    for(u32 key = 0; key < KEY_KEY_CODES_COUNT; ++key)
      KeyIsDown[key] = false;
  }
  
private:
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
};
