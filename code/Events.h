#ifndef EVENTS_H
#define EVENTS_H

enum Events {
	EV_SCHUTSTART,
	EV_EMERGENCY,
	EV_RESUME,
	EV_RIGHTDOOROPENED,
	EV_RIGHTDOORCLOSED,
	EV_LEFTDOOROPENED,
	EV_LEFTDOORCLOSED,
	EV_WATER_LOW,
	EV_WATER_HIGH,
	EV_DOORSHALTED,
	EV_WATERLEVEL_ABOVE_VALVE2,
	EV_WATERLEVEL_ABOVE_VALVE3,
	EV_VALVESCLOSED
};

#endif