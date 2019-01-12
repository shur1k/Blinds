/*
  Blinds.h - Library for checking the buttons, connected to Analog pin of Arduino
*/

#include "Blinds.h"

Blinds::Blinds(int pow_pin, int up_dn_pin, int op_time) {
	p_pin   = pow_pin;
	ud_pin  = up_dn_pin;
	f_time  = op_time;
	s_time  = f_time/100;
	pinMode(p_pin,  OUTPUT); 
    pinMode(ud_pin, OUTPUT);
	
	fs_open = SPIFFS.begin();
	
	if (fs_open) {
		File f = SPIFFS.open("/position.txt", "r");
		if (!f) {
		  File f = SPIFFS.open("/position.txt", "w");
		  if (f) {
			  f.println("0"); 
			  //Serial.println("New file loaded with 0");
		  }
		  //else Serial.println("Failed to open file for writing");
		  pos = 0;
		  cur_pos = pos;
		} 
		else {
		  while(f.available()) {
			String line = f.readStringUntil('\n');
			pos = line.toInt();
			cur_pos = pos;
		  }
		}
		if ((cur_pos < 0)||(cur_pos)>100) cur_pos = 0; 
		f.close();
	}
	else {
		pos = 0;
		cur_pos = pos;
	}	
    stop();
}

void Blinds::stop(void) {
	digitalWrite(p_pin,  LOW);
	digitalWrite(ud_pin, LOW);
	isMove = false;
    File f = SPIFFS.open("/position.txt", "w");
    if (f) {
		f.println(cur_pos);
		f.close();
		//Serial.println("Postiion saved");
	}
	//else {Serial.println("Failed to write SPIFFS");}
}

int Blinds::getPosition(void) {
	return cur_pos;
}

bool Blinds::isMoving(void) {
	return isMove;
}

void Blinds::move_up(void) {
	digitalWrite(p_pin,  HIGH);
	digitalWrite(ud_pin, HIGH);
}

void Blinds::move_dn(void) {
	digitalWrite(p_pin,  HIGH);
	digitalWrite(ud_pin, LOW);	
}

void Blinds::setPosition(int p) {
	pos = p;
	if (cur_pos == pos) return;
	isMove = true;
	m_time = millis();
    if ((pos - cur_pos) > 0) move_up();
    else move_dn();
}

void Blinds::run(void) {
	if (isMove) {
		if(millis() - m_time >= s_time) { //one step move
			if(cur_pos == pos) {stop(); return; }
			m_time = millis();
			if(pos - cur_pos > 0) cur_pos++; //moving up
			else cur_pos--; //moving down
			//Serial.print("one step: cur: ");Serial.print(cur_pos);Serial.print(", req_p: ");Serial.println(pos);
		}
	}
}