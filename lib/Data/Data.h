#ifndef __TIMER_DATA__
#define __TIMER_DATA__

class Data {
  unsigned long time;
  unsigned char state;

  public:
  Data() {};
  Data(unsigned long _time, unsigned char _state)
      : time(_time)
      , state(_state) { }

  unsigned long getTime() const { return time; }
  unsigned char getState() const { return state; }
  void setTime(unsigned long _time) { time = _time; }
  void setState(unsigned char _state) { state = _state; }
};

#endif