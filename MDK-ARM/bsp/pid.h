/**
  ******************************************************************************
  * @file		 pid.h
  * @author  Ginger
  * @version V1.0.0
  * @date    2015/11/14
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#ifndef _PID_H
#define _PID_H

#include "stdint.h"
#include "mytype.h"
typedef enum
{

	PID_Position,
	PID_Speed
	
}PID_ID;

typedef struct _PID_TypeDef
{
	PID_ID id;
	
	float target;							//目标值
	float lastNoneZeroTarget;
	float kp;
	float ki;
	float kd;
	
	float   measure;					//测量值
	float   err;							//误差
	float   last_err;      		//上次误差
	
	float pout;
	float iout;
	float dout;
	
	float output;						//本次输出
	float last_output;			//上次输出
	
	float MaxOutput;				//输出限幅
	float IntegralLimit;		//积分限幅
	float DeadBand;			  //死区（绝对值）
	float ControlPeriod;		//控制周期
	float  Max_Err;					//最大误差
	
					  uint32_t thistime;
					uint32_t lasttime;
						uint8_t dtime;	
	
	void (*f_param_init)(struct _PID_TypeDef *pid,  //PID参数初始化
				   PID_ID id,
				   uint16_t maxOutput,
				   uint16_t integralLimit,
				   float deadband,
				   uint16_t controlPeriod,
					int16_t max_err,     
					int16_t  target,
				   float kp,
				   float ki,
				   float kd);
				   
	void (*f_pid_reset)(struct _PID_TypeDef *pid, float kp,float ki, float kd);		//pid三个参数修改
	float (*f_cal_pid)(struct _PID_TypeDef *pid, float measure);   //pid计算
}PID_TypeDef;
void all_pid_init(void);
void pid_init(PID_TypeDef* pid);
void pid_reset_chassis(u8 motornum,u32 kp, u32 ki, u32 kd);
void pid_reset_all_chassis(u32 kp, u32 ki, u32 kd);
void show_pid(u8 motornum);
void show_all_pid(void);
float PID_Control_Pitch(PID_TypeDef* pid, float measure);
float PID_Control_Yaw(PID_TypeDef* pid, float measure);
#endif

//extern PID_TypeDef pid_pitch;    
extern PID_TypeDef motor_pid[7];
extern PID_TypeDef chassis_yaw_speed,chassis_yaw;
extern PID_TypeDef pan_tilt_pitch,pan_tilt_pitch_speed,pan_tilt_roll,pan_tilt_roll_speed,pan_tilt_yaw,pan_tilt_yaw_speed;

