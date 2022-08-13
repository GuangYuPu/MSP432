#ifndef _USERCODE_DRIVER_H__
#define _USERCODE_DRIVER_H__

#include "spwm.h"
#include "pid.h"
#include "user_type_define.h"

void usercode_init()
{
    PID_init();
}

#endif