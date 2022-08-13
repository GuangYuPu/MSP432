#ifndef _PID_H__
#define _PID_H__

typedef struct{
    float KP;											//PID参数P
    float KI;											//PID参数I
    float KD;											//PID参数D
    float fdb;											//PID反馈值
    float ref;											//PID目标值
    float cur_error;									//当前误差
    float error[2];										//前两次误差
    float output;										//输出值
}PID_t;

void PID_init();
void PID_Caculate(float ref,float fdb,float *output,PID_t *pid);

extern PID_t Control_Value[3]; 

#endif