#ifndef __TIMER_POWER__
#define __TIMER_POWER__

#define POWER 5

#include <MenuProvider.h>

class Shutdown : public MenuProvider {
  public:
  Shutdown() { title = "Shutdown"; }

  private:
  void init(Display*, UIProvider*);
  void refresh();
  void exit();
};

#endif