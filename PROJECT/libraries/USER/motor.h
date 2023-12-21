#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "definitions.h"
#include "configuration.h"
#include "map.h"

extern void LEFT_MOTOR_FORWARD(void);
extern void LEFT_MOTOR_BACKWARD(void);
extern void LEFT_MOTOR_STOP(void);
extern void RIGHT_MOTOR_FORWARD(void);
extern void RIGHT_MOTOR_BACKWARD(void);
extern void RIGHT_MOTOR_STOP(void);
extern void FORWARD(void);
extern void BACKWARD(void);
extern void STOP(void);
extern void CLOCKWISE_ROTATION(void);
extern void COUNTER_CLOCKWISE_ROTATION(void);

extern void ONE_TICK_FORWARD(void);
extern void ONE_TICK_CLOCKWISE_ROTATION(void);
extern void ONE_TICK_COUNTER_CLOCKWISE_ROTATION(void);

extern void delay();

#endif