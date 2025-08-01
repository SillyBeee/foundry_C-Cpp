#ifndef MOTOR_H
#define MOTOR_H
#include "pid.h"
#include "cstdint"
#include "can.h"

#include "RTT_Logger.h"
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif


typedef enum
{
    NONE_PID,
    SPEED_LOOP,
    POSITION_LOOP,
} Pid_Type;

typedef enum
{
    VOLTAGE_CTL,
    CURRENT_CTL,
} Motor_CTL_Method;


typedef struct
{
    int16_t Position = 0;
    int16_t Speed = 0;
    int16_t Current = 0;
    int8_t Temperature = 0;
} GM_Motor_Status;


typedef enum
{
    MIT_MODE,
    MIT_TORQUE_MODE,
    POSITION_AND_SPEED_MODE,
    SPEED_MODE,
    NONE_MODE,
} Motor_Mode;


typedef struct
{
    uint16_t error_code = 0;
    float Position = 0;
    float Speed = 0;
    float Torque = 0;
    int Temperature_MOS = 0;
    int Temperature_Rotor = 0;
} DM_Motor_Status;


class Motor
{
public:
    Motor();
    virtual void Set_Angle(float angle, float speed = 0) = 0;
    virtual void Set_Speed(float speed) = 0;
    virtual void Pid_Update(float target) = 0;

    virtual void Set_Pid_Type(Pid_Type pid_type);

    virtual ~Motor() = 0;

    void Bind_CAN(CAN_HandleTypeDef* hcan);

protected:
    Pid_Type pid_type;
    CAN_HandleTypeDef* hcan;
};

#endif //MOTOR_H
