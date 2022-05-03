#ifndef __TIMER_POWER__
#define __TIMER_POWER__

#define POWER 14

#include <MenuProvider.h>

class Shutdown : public MenuProvider {
  public:
  static Shutdown* getInstance() { return (instance == NULL) ? instance = new Shutdown() : instance; }

  private:
  Shutdown() { title = "Shutdown"; }
  static Shutdown* instance;
  void init(Display*, UIProvider*);
  void refresh();
  void exit();
};

#endif