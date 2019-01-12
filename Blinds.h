/*
  Blinds.h - Library for blinds control by the two relays (first relay turns on/off the power, the second one swithces the direction (up or down))
*/

// ensure this library description is only included once
#ifndef Blinds_h
#define Blinds_h

#include <Arduino.h>
#include <FS.h>

class Blinds {
    byte  pos;     // the requested position of the blinds (from 0 to 100)
	byte  cur_pos; // the current position of the blinds (from 0 to 100)
	int   p_pin;   // the pin for the power relay
	int   ud_pin;  // the pin for the up/down switching relay
	int   f_time;  // the full time for blinds to open (close)
	int   s_time;  // the one step time, changes the postion by one (full time divide by 100)
	bool  isMove;  // indicates, if the blinds are moving at the moment
	bool  fs_open; // the result of opening an SPIFFS. If true, FS is opened
	unsigned long m_time; //check the time while moving
  public:
    Blinds(int pow_pin, int up_dn_pin, int op_time);
    int  getPosition(void);
    void setPosition(int p);
	bool isMoving(void);
	void run(void);
  private:
    void stop(void);
	void move_up(void);
	void move_dn(void);
};

#endif