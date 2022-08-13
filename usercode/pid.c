#include "pid.h"
#include "user_type_define.h"

PID_t Control_Value[3]; 

void PID_init()
{
    for (int i = 0; i < 3; i++)
    {
        Control_Value[i].KP = 15;
        Control_Value[i].KI = 1;
        Control_Value[i].KD = 1;
    }
}

void PID_Caculate(float ref,float fdb,float *output,PID_t *pid)
{
    pid->fdb = fdb;
    pid->ref = ref;
    pid->cur_error = pid->ref - pid->fdb;
	pid->output += pid->KP * (pid->cur_error - pid->error[1]) + pid->KI * pid->cur_error + pid->KD * (pid->cur_error - 2 * pid->error[1] + pid->error[0]);
	*output = pid->output;
    pid->error[0] = pid->error[1];
	pid->error[1] = pid->ref - pid->fdb;
}