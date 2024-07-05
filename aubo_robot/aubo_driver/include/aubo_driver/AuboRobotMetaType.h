#ifndef AUBOROBOTMETATYPE_H
#define AUBOROBOTMETATYPE_H

#include <iostream>
#include <stdint.h>
#include <list>
#include <array>
#include <vector>
#include "robotiomatetype.h"


/**
 * General types
 */
typedef  uint8_t     boolean;
typedef  int8_t      int8;
typedef  int16_t     int16;
typedef  int32_t     int32;
typedef  uint8_t     uint8;
typedef  uint16_t    uint16;
typedef  uint32_t    uint32;
typedef  int64_t     int64;
typedef  uint64_t    uint64;
typedef  float       float32;
typedef  double      float64;

//#define  PACKED  __attribute__((__packed__))
#define  PACKED

#ifdef __cplusplus
extern "C" {
#endif


/**
 * 命名空间  aubo_robot_namespace
 **/
namespace  aubo_robot_namespace
{
enum CollisionMode {
    CollisionMode_Free,
    CollisionMode_Stuck,
    //CollisionMode_Adamittance,
};

enum {
    ARM_DOF = 6,   //机械臂关节数
};


/**
 * 机械臂类型
 **/
typedef enum
{
    ROBOT_I5    = 0,
    ROBOT_I7    = 1,
    ROBOT_I10_12= 2,
    ROBOT_I3S   = 3,
    ROBOT_I3    = 4,
    ROBOT_I5S   = 5,
    ROBOT_I5RX  = 501,
    ROBOT_I5A_02  = 502,
    ROBOT_I5A_03  = 503,
    ROBOT_I5L   = 6,
    ROBOT_I10S  = 7,
    ROBOT_I16   = 8,
    ROBOT_I20   = 9,
    ROBOT_I20_1500   = 901,
    ROBOT_I20_1650_A   = 902,
    ROBOT_I20TD = 10,
    ROBOT_G3 = 11,
    ROBOT_G6 = 12,
    ROBOT_F12B = 20,
    ROBOT_I12 = 21,
    ROBOT_I18 = 22,
    ROBOT_T6 = 23,
    ROBOT_I5_NET = 24,
    ROBOT_I20L_1900 = 25,
    ROBOT_I10_CM01 = 26,
    ROBOT_I20_BZL = 27,
    ROBOT_IS10 = 50,
    ROBOT_IS20 = 51,
    ROBOT_IS7 = 52,
}RobotType;


/**
  * DH参数
  **/
typedef struct
{
    double A3;
    double A4;
    double D1;
    double D2;
    double D5;
    double D6;

    // general dh model
    double alpha[ARM_DOF];
    double a[ARM_DOF];
    double d[ARM_DOF];
    double theta[ARM_DOF];
}RobotDhPara;

typedef enum
{
    RobotControllerErr_MotionCfgErr,    //only this is recoverable.
    RobotControllerErr_OverspeedProtect,
    RobotControllerErr_IkFailure,
    RobotControllerErr_OnlineTrajErr,
    RobotControllerErr_OfflineTrajErr,
    RobotControllerErr_StatusException,
}RobotControllerErrorCode;


typedef enum {
    RUN_TO_READY_POSITION,
    RUN_PROJECT,
    PAUSE_PROJECT,
    CONTINUE_PROJECT,
    SLOWLY_STOP_PROJECT,
    LOAD_PROJECT,
    ENTER_SAFEGUARD_MODE_BY_DI_EXTERNAL_SAFEGUARD_STOP,
    RELEASE_SAFEGUARD_MODE_IN_AUTOMATIC_MODE,
    RELEASE_SAFEGUARD_MODE_IN_MANUAL_MODE,
    MANUALLY_RELEASE_SAFEGUARD_MODE_PROMPT,
    ENTER_SAFEGUARD_MODE_BY_TRI_STATE_SWITCH,
    RELEASE_SAFEGUARD_MODE_BY_TRI_STATE_SWITCH,
    ENTER_REDUCE_MODE,
    RELEASE_REDUCE_MODE,
    REMOTE_CLEAR_ALARM_SIGNAL,
    PROJECT_STARTUP_IS_SAFETY,
    START_RUN_TO_READY_POSITION,
    STOP_RUN_TO_READY_POSITION
}InterfaceBoardSafeIoEventCode;


/**
 * 机械臂诊断信息
 **/
typedef struct PACKED
{
    uint8   armCanbusStatus;                // CAN通信状态:0x01~0x80：关节CAN通信错误（每个关节占用1bit） 0x00：无错误
    float   armPowerCurrent;                // 机械臂48V电源当前电流
    float   armPowerVoltage;                // 机械臂48V电源当前电压
    bool    armPowerStatus;                 // 机械臂48V电源状态（开、关）
    char    contorllerTemp;                 // 控制箱温度
    uint8   contorllerHumidity;             // 控制箱湿度
    bool    remoteHalt;                     // 远程关机信号
    bool    softEmergency;                  // 机械臂软急停
    bool    remoteEmergency;                // 远程急停信号
    bool    robotCollision;                 // 碰撞检测位
    bool    forceControlMode;               // 机械臂进入力控模式标志位
    bool    brakeStuats;                    // 刹车状态
    float   robotEndSpeed;                  // 末端速度
    int     robotMaxAcc;                    // 最大加速度
    bool    orpeStatus;                     // 上位机软件状态位
    bool    enableReadPose;                 // 位姿读取使能位
    bool    robotMountingPoseChanged;       // 安装位置状态
    bool    encoderErrorStatus;             // 磁编码器错误状态
    bool    staticCollisionDetect;          // 静止碰撞检测开关
    uint8   jointCollisionDetect;           // 关节碰撞检测 每个关节占用1bit 0-无碰撞 1-存在碰撞
    bool    encoderLinesError;              // 光电编码器不一致错误 0-无错误 1-有错误
    bool    jointErrorStatus;               // joint error status
    bool    singularityOverSpeedAlarm;      // 机械臂奇异点过速警告
    bool    robotCurrentAlarm;              // 机械臂电流错误警告
    uint8   toolIoError;                    // tool error
    bool    robotMountingPoseWarning;       // 机械臂安装位置错位（只在力控模式下起作用）
    uint16  macTargetPosBufferSize;         // mac缓冲器长度          预留
    uint16  macTargetPosDataSize;           // mac缓冲器有效数据长度   预留
    uint8   macDataInterruptWarning;        // mac数据中断           预留
    uint8   controlBoardAbnormalStateFlag;  //主控板(接口板)异常状态标志
}RobotDiagnosis;

typedef struct PACKED
{
    // 理论电流
    int32_t theory_current[6];
    // 碰撞阈值电流
    int32_t collision_threshold_current[6];
    // 过大力保护阈值电流
    int32_t overforce_threshold_current[6];
    // 外力电流（实际电流和理论电流之差）
    int32_t external_current[6];
}CollisionCurrent;

typedef struct PACKED
{
    uint8 orpePause;                    // 上位机暂停状态
    uint8 orpeStop;                     // 上位机停止状态
    uint8 orpeError[16];                // 上位机错误
    uint8 systemEmergencyStop;          // 解除系统紧急停止输出信号
    uint8 reducedModeError;             // 解除缩减错误
    uint8 safetyguardResetSucc;         // 防护重置成功
}OrpeSafetyStatus;


typedef struct PACKED
{
    uint16  robotReducedConfigJointSpeed[6];    //缩减配置 关节速度限制
    uint32  robotReducedConfigTcpSpeed;         //缩减配置 TCP速度限制
    uint32  robotReducedConfigTcpForce;         //缩减配置 TCP力（暂定为碰撞等级）
    uint32  robotReducedConfigMomentum;         //缩减配置 动量
    uint32  robotReducedConfigPower;            //缩减配置 功率
    uint8   robotSafeguradResetConfig;          //防护重 置设置
    uint8   robotOperationalModeConfig;         //操作模式设置
}RobotSafetyConfig;

typedef struct PACKED
{
    double maxTcpVelocity;               //末端速度
    double maxTcpAcceleration;           //末端加速度
    double maxJointVelocity[ARM_DOF];    //关节速度
    double maxJointAcceleration[ARM_DOF];//关节加速度
}RegulateSpeedModeParamConfig_t;

typedef struct PACKED
{
    double inertia[ARM_DOF];   //导纳系数之 惯量inertia
    double damping[ARM_DOF];   //导纳系数之 阻尼(b)damping
    double stiffness[ARM_DOF]; //导纳系数之 刚度(k)stiffness
}AdmittancePatam_t;

/**
 * @brief IO的类型枚举
 *
 **/
typedef enum
{
    RobotBoardControllerDI,    // 接口板控制器DI(数字量输入)　　　只读(一般系统内部使用)
    RobotBoardControllerDO,    // 接口板控制器DO(数字量输出)     只读(一般系统内部使用)
    RobotBoardControllerAI,    // 接口板控制器AI(模拟量输入)　   只读(一般系统内部使用)
    RobotBoardControllerAO,    // 接口板控制器AO(模拟量输出)　　　只读(一般系统内部使用)

    RobotBoardUserDI,          // 接口板用户DI(数字量输入)　　   可读可写
    RobotBoardUserDO,          // 接口板用户DO(数字量输出)      可读可写
    RobotBoardUserAI,          // 接口板用户AI(模拟量输入)      可读可写
    RobotBoardUserAO,          // 接口板用户AO(模拟量输出)      可读可写

    RobotToolDI,               // 工具端DI
    RobotToolDO,               // 工具端DO
    RobotToolAI,               // 工具端AI
    RobotToolAO,               // 工具端AO

}RobotIoType;

enum ModbusIOType
{
    ModbusDI,
    ModbusDO,
    ModbusAI,
    ModbusAO,

    ModbusIOTypeCount
};




/**
 * IO类型
 **/
typedef enum
{
    IO_IN = 0,        //输入
    IO_OUT            //输出
}ToolIOType;


/**
 * 工具的电源类型
 **/
typedef enum
{
    OUT_0V  = 0,
    OUT_12V = 1,
    OUT_24V = 2
}ToolPowerType;


typedef enum
{
    RobotToolIoTypeDI=RobotToolDI,      //工具端DI
    RobotToolIoTypeDO=RobotToolDO       //工具端DO
}RobotToolIoType;


typedef  enum              //ＩＯ状态
{
    IO_STATUS_INVALID = 0, //有效
    IO_STATUS_VALID        //无效
}IO_STATUS;

typedef enum
{
    TOOL_DIGITAL_IO_0 = 0,
    TOOL_DIGITAL_IO_1 = 1,
    TOOL_DIGITAL_IO_2 = 2,
    TOOL_DIGITAL_IO_3 = 3

}ToolDigitalIOAddr;

enum ToolSerialBaudRate
{
    TOOL_SERIAL_BAUD_1200 = 0,
    TOOL_SERIAL_BAUD_2400 = 1,
    TOOL_SERIAL_BAUD_4800 = 2,
    TOOL_SERIAL_BAUD_9600 = 3,
    TOOL_SERIAL_BAUD_19200 = 4,
    TOOL_SERIAL_BAUD_38400 = 5,
    TOOL_SERIAL_BAUD_57600 = 6,
    TOOL_SERIAL_BAUD_115200 = 7,
    TOOL_SERIAL_BAUD_230400 = 8,
    TOOL_SERIAL_BAUD_460800 = 9
};

enum ToolSerialStopBitNum
{
    TOOL_SERIAL_STOP_BIT_0 = 0,//0：1个停止位
    TOOL_SERIAL_STOP_BIT_1 = 1,//1：0.5个停止位
    TOOL_SERIAL_STOP_BIT_2 = 2,//2：2个停止位
    TOOL_SERIAL_STOP_BIT_3 = 3 //3：1.5个停止位
};

enum ToolSerialCheck
{
    TOOL_SERIAL_CHECK_1=1,//1：奇校验
    TOOL_SERIAL_CHECK_2=2//2：偶校验
};

enum ToolSerialCheckCmd
{
    TOOL_SERIAL_CHECK_CMD_0=0,//0：无校验
    TOOL_SERIAL_CHECK_CMD_1=1//1：有校验
};

enum ToolBusType
{
    FORCE_SENSOR=0,
    MODBUS_MASTER=1,
    SERIAL_PIPELINE=2
};


/**
  * 综合描述一个IO
  **/
typedef struct PACKED
{
    char        ioId[32];      //IO-ID 目前未使用
    RobotIoType ioType;        //IO类型
    char        ioName[32];    //IO名称
    int         ioAddr;        //IO地址
    double      ioValue;       //IO状态
}RobotIoDesc;


//接口板数字量数据
typedef struct
{
    uint8 addr ;
    uint8 value;
    uint8 type;
}RobotDiagnosisIODesc;

//接口板模拟量数据
typedef struct
{
    uint8  addr ;
    float  value;
    uint8 type;
}RobotAnalogIODesc;

typedef struct PACKED
{
    ToolIOType ioType;
    uint8      ioData;
}ToolDigitalStatus;


typedef enum {
    RobotToolNoError      = 0, //无错误
    RobotToolOverVoltage  = 1, //过压
    RobotToolUnderVoltage = 2, //欠压
    RobotToolOVerTemp     = 3, //过温
    RobotToolCanBusError  = 4  //CAN总线错误
}RobotToolErrorCode;






/**
 * @brief 机械臂启动完成状态
 */
enum ROBOT_SERVICE_STATE
{
    ROBOT_SERVICE_READY = 0,
    ROBOT_SERVICE_STARTING,
    ROBOT_SERVICE_WORKING,
    ROBOT_SERVICE_CLOSING,
    ROBOT_SERVICE_CLOSED,
    ROBOT_SETVICE_FAULT_POWER,
    ROBOT_SETVICE_FAULT_BRAKE,
    ROBOT_SETVICE_FAULT_NO_ROBOT,
    ROBOT_SETVICE_FAULT_SAFEGUARD_STOP
};


enum ROBOT_INIT_PHASE{
    ROBOT_INIT_PHASE_READY=0,
    ROBOT_INIT_PHASE_HANDSHAKE,
    ROBOT_INIT_PHASE_SET_POWER,
    ROBOT_INIT_PHASE_SET_BRAKE,
    ROBOT_INIT_PHASE_SET_COLLSION_CLASS,
    ROBOT_INIT_PHASE_SET_OTHER_CMD,
    ROBOT_INIT_PHASE_WORKING
};


typedef enum
{
    RobotModeSimulator,         // 机械臂仿真模式
    RobotModeReal               // 机械臂真实模式
}RobotWorkMode;



/**
 * @brief 机械臂运动控制命令
 */
typedef enum
{
    RobotMoveStop     = 0,       // 停止
    RobotMovePause    = 1,       // 暂停
    RobotMoveContinue = 2,       // 继续
}RobotMoveControlCommand;



/**
 * @brief 机械臂控制命令
 */
enum RobotControlCommand
{
    RobotRelease           = 0,    // 释放刹车
    RobotBrake             = 1,    // 刹车
    OverspeedWarning       = 2,    // 拖动示教速度过快报警
    OverspeedRecover       = 3,    // 解除拖动过速报警
    DisableForceControl    = 4,    // 失能力控
    EnableForceControl     = 5,    // 使能力控
    OrpeOpen               = 6,    // 打开上位机软件
    OrpeClose              = 7,    // 关闭上位机软件
    EnableReadPose         = 8,    // 打开读取位姿
    DisableReadPose        = 9,    // 关闭读取位姿
    MountingPoseChanged    = 10,   // 安装位置已改变
    MountingPoseUnChanged  = 11,   // 安装位置未改变
    EnableStaticCollisionDetect    = 12, // 打开静止碰撞检测
    DisableStaticCollisionDetect   = 13, // 关闭静止碰撞检测
    ClearSingularityOverSpeedAlarm = 14, // 解除机械臂奇异点过速警告
    ClearRobotCurrentAlarm         = 15,  // 解除机械臂电流错误警告
    SetCollisionFreeDrive = 0x10,//碰撞之后进入拖动示教模式
    SetCollisionStuck = 0x11,//碰撞之后进入停止模式
    SetCollisionAdamittance = 0x12,//碰撞之后进入导纳控制模式
    EnableNewTemperatureCompensation = 0x13, //打开新型温度补偿开关
    DisableNewTemperatureCompensation = 0x14, //关闭新型温度补偿开关
    EnterDragAndTeachMode=0x15,  //进入拖动示教模式
    ExitDragAndTeachMode=0x16,  //退出拖动示教模式
    EnablePayloadDetect = 0x22, //使能负载检测
    DisablePayloadDetect = 0x23, //失能负载检测
    RobotShutdown=0x24 ,  //上位机指令控制机械臂一类停机，并上传错误
    ClearRobotShutdown=0x25,   //清除上位机一类停机标志
    EnableFrictionCollisionDetect  = 0x26,//使能摩擦力模型碰撞检测功能
    DisableFrictionCollisionDetect = 0x27, //失能摩擦力模型碰撞检测功能
    EnableCollisionStuckBrake = 0x28,   //使能碰撞stuck模式锁刹车
    DisableCollisionStuckBrake = 0x29,  //失能能碰撞stuck模式锁刹车
    EnableNewForceTeach = 0x2a, //打开新型拖动示教开关
    DisableNewForceTeach = 0x2b, //关闭新型拖动示教开关

};


enum ROBOT_DI_ACTION{
    IN_CLEAR_ALARM = 0,
    IN_ACTION_MAX
};

enum ROBOT_DO_ACTION{
    OUT_LINKAGE_RUNNING = 0,
    OUT_LINKAGE_STOP,
    OUT_LINKAGE_PAUSE,
    OUT_LINKAGE_ORIGIN_POSE,
    OUT_ACTION_MAX
};


/**
 * @brief 位置信息
 **/
struct Pos
{
    double x;
    double y;
    double z;
};



/**
 * @brief 位置信息的共用体描述
 **/
union cartesianPos_U
{
    Pos position;
    double positionVector[3];
};



/**
 * @brief 姿态的四元素表示方法
 **/
struct Ori
{
    double w;
    double x;
    double y;
    double z;
};

/**
 * @brief 姿态的欧拉角表示方法
 **/
struct Rpy
{
    double rx;
    double ry;
    double rz;
};

typedef struct
{
    double jointPos[ARM_DOF];
}JointParam;


/**
  * @brief 描述关节的速度和加速度
  */
typedef struct
{
    double jointPara[ARM_DOF];
}JointVelcAccParam;


/**
 * 关节碰撞补偿（范围0.00~0.51度）
 **/
typedef struct
{
    double jointOffset[ARM_DOF];
}RobotJointOffset;


/**
 * @brief 机械臂的路点信息
 **/
typedef struct
{
    cartesianPos_U cartPos;            // 机械臂的位置信息(x,y,z)

    Ori            orientation;        // 机械臂姿态信息,四元素(w,x,y,z)

    double         jointpos[ARM_DOF];  // 机械臂关节角信息

    int    id;          // 路点ID

}wayPoint_S;

typedef struct
{
    double data[6];
}ForceSensorData;

typedef struct
{
    Pos position;

    Ori quaternion;

}PositionAndQuaternion;


/**
 *  @brief 描述运动属性中的偏移属性
 */
typedef struct
{
    bool  ena;                       // 是否使能偏移

    float relativePosition[3];       // 偏移量 x,y,z

    Ori   relativeOri;               // 姿态偏移

}MoveRelative;


typedef struct
{
    double minValue;
    double maxValue;

}RangeOfMotion;

/**
 * 关节运动范围
 */

typedef struct
{
    bool   enable;                        // 是否使能偏移

    RangeOfMotion rangeValues[ARM_DOF];    //运动范围

}JointRangeOfMotion;




/**
 * @brief 示教模式枚举
 **/
enum teach_mode
{
    NO_TEACH = 0,
    JOINT1,
    JOINT2,
    JOINT3,
    JOINT4,
    JOINT5,
    JOINT6,
    MOV_X,
    MOV_Y,
    MOV_Z,
    ROT_X,
    ROT_Y,
    ROT_Z
};


/**
 * @brief 运动轨迹枚举
 **/
enum move_track
{
    NO_TRACK = 0,

    //for moveJ and moveL
    TRACKING,

    //cartesian motion for moveP
    ARC_CIR,
    CARTESIAN_MOVEP,
    CARTESIAN_CUBICSPLINE,
    CARTESIAN_UBSPLINEINTP,
    CARTESIAN_GNUBSPLINEINTP,
    CARTESIAN_LOOKAHEAD,

    //joint motion for moveP
    JIONT_CUBICSPLINE,
    JOINT_UBSPLINEINTP,
    JOINT_GNUBSPLINEINTP,
    JOINT_TOPF,

    JOINT_MOVE_PROCESS,           // moveP in ARAL
    SPEEDJ,                       // moveP in ARAL
    SPEEDL,                       // moveP in ARAL
    POLYLINE,                     // moveGroup：多段直线
    JOINT_GNUBSPLINEINTP_ENDSPEED,// moveGroup：关节空间B样条+末端速度限制

    ARC = 90,
    CIRCLE,
    ARC_ORI_ROTATED,
    CIRCLE_ORI_ROTATED,

    ORI_POSITION_ROTATE_CIRCUMFERENCE=101,

};


/**
 * @brief 工具姿态标定的方法枚举
 *
 */

enum ToolKinematicsOriCalibrateMathod
{
    ToolKinematicsOriCalibrateMathod_Invalid = -1,

    ToolKinematicsOriCalibrateMathod_xOxy,                   // 原点、x轴正半轴、x、y轴平面的第一象限上任意一点
    ToolKinematicsOriCalibrateMathod_yOyz,                   // 原点、y轴正半轴、y、z轴平面的第一象限上任意一点
    ToolKinematicsOriCalibrateMathod_zOzx,                   // 原点、z轴正半轴、z、x轴平面的第一象限上任意一点
    ToolKinematicsOriCalibrateMathod_TxRBz_TxyPBzAndTyABnz,  // 工具x轴平行反向于基坐标系z轴; 工具xOy平面平行于基坐标系z轴、工具y轴与基坐标系负z轴夹角为锐角
    ToolKinematicsOriCalibrateMathod_TyRBz_TyzPBzAndTzABnz,  // 工具y轴平行反向于基坐标系z轴; 工具yOz平面平行于基坐标系z轴、工具z轴与基坐标系负z轴夹角为锐角
    ToolKinematicsOriCalibrateMathod_TzRBz_TzxPBzAndTxABnz,  // 工具z轴平行反向于基坐标系z轴; 工具zOx平面平行于基坐标系z轴、工具x轴与基坐标系负z轴夹角为锐角

    ToolKinematicsOriCalibrateMathodCount
};



/**
 * 该结构体描述工具惯量
 *
 * 注：该结构体属于冗余数据类型，使用时把所有参数都设置为{0,0,0,0,0,0}．
 **/
typedef struct
{
    double xx;
    double xy;
    double xz;
    double yy;
    double yz;
    double zz;
}ToolInertia;


/**
 * 工具动力学参数描述
 *
 * 注意：
 * 　　　机械臂上电之前，安装在机器人末端的工具发生改变时都需要重新设置工具的动力学参数．
 * 　　　一般情况下，工具的动力学参数和运动学参数是需要一起设置的；
 * 切记：
 * 　　　该参数如果不能正确设置会影响机械臂的安全等级和运动轨迹．
 **/
typedef struct
{
    double      positionX;    // 工具重心的X坐标

    double      positionY;    // 工具重心的Y坐标

    double      positionZ;    // 工具重心的Z坐标

    double      payload;      // 工具重量

    ToolInertia toolInertia;  // 工具惯量　预留　使用是全部设置为0

}ToolDynamicsParam;


/** 工具描述　工具的运动学参数
 *
 *  该工具用于描述一个工具或者工具的运动学参数．
 */
typedef struct
{
    Pos        toolInEndPosition;     // 工具相对法兰盘的位置

    Ori        toolInEndOrientation;  // 工具相对法兰盘的姿态

}ToolInEndDesc;

typedef ToolInEndDesc ToolKinematicsParam;
typedef ToolInEndDesc RobotCameraCalib;







/**
  * 焊接摇摆结构体
  */
typedef struct
{
    bool   weaveEnable;
    int    weaveType;
    double weaveStep;
    double weaveAmplitude;
    double weaveHoldDistance;
    double weaveAngle;
}WeaveMove;


typedef struct PACKED{
    uint8 type;   //机械臂辨识参数类型
    uint8 length; //参数数据长度
    uint8 data[256];//参数实际数据
}RobotRecongnitionParam;


/**
 * 坐标系类型枚举
 **/
enum coordinate_refer
{
    BaseCoordinate = 0,  // 基座坐标系
    EndCoordinate,       // 末端坐标系或工具坐标系
    WorldCoordinate,     // 用户坐标系
};


/**
 * 用户坐标系标定方法枚举
 *
 * 描述:3点标定坐标系　３个示教点的含义．
 **/
enum CoordCalibrateMathod
{
    Origin_AnyPointOnPositiveXAxis_AnyPointOnPositiveYAxis,            // 原点、x轴正半轴、y轴正半轴
    Origin_AnyPointOnPositiveYAxis_AnyPointOnPositiveZAxis,            // 原点、y轴正半轴、z轴正半轴
    Origin_AnyPointOnPositiveZAxis_AnyPointOnPositiveXAxis,            // 原点、z轴正半轴、x轴正半轴
    Origin_AnyPointOnPositiveXAxis_AnyPointOnFirstQuadrantOfXOYPlane,  // 原点、x轴正半轴、x、y轴平面的第一象限上任意一点
    Origin_AnyPointOnPositiveXAxis_AnyPointOnFirstQuadrantOfXOZPlane,  // 原点、x轴正半轴、x、z轴平面的第一象限上任意一点
    Origin_AnyPointOnPositiveYAxis_AnyPointOnFirstQuadrantOfYOZPlane,  // 原点、y轴正半轴、y、z轴平面的第一象限上任意一点
    Origin_AnyPointOnPositiveYAxis_AnyPointOnFirstQuadrantOfYOXPlane,  // 原点、y轴正半轴、y、x轴平面的第一象限上任意一点
    Origin_AnyPointOnPositiveZAxis_AnyPointOnFirstQuadrantOfZOXPlane,  // 原点、z轴正半轴、z、x轴平面的第一象限上任意一点
    Origin_AnyPointOnPositiveZAxis_AnyPointOnFirstQuadrantOfZOYPlane,  // 原点、z轴正半轴、z、y轴平面的第一象限上任意一点

    CoordTypeCount,
};

/**
 * 坐标系描述
 *
 * 该结构体描述一个坐标系。系统通过该结构体描述一个坐标系(基座坐标系, 用户坐标系, 末端坐标系或工具坐标系)。
 *
 * 坐标系分３种类型: 基座坐标系(BaseCoordinate);
 *                用户坐标系(WorldCoordinate);
 *                末端坐标系或工具坐标系(EndCoordinate);
 *
 * 定义:
 *      基座坐标系 是　根据机械臂基座建立的坐标系;
 *      用户坐标系 是  用户坐标系定义在工件上，在机器人动作允许范围内的任意位置，设定任意角度的X、Y、Z轴，原点位于机器人抓取的工件上，坐标系的方向根据客户需要任意定义。
 *      末端坐标系 是　安装在机器人末端的工具坐标系，原点及方向都是随着末端位置与角度不断变化的，该座标系实际是将基础座标系通过旋转及位移变化而来的；法兰盘是一个特殊的末端坐标系.
 *
 * 结构体参数描述：
 *      coordType    　　　　坐标系类型,描述坐标系属于那种类型
 * 　　　methods　　　 　　　　用户坐标系的标定方法　　　　　仅在coordType为用户坐标系(WorldCoordinate)时有效；
 * 　　　wayPointArray[3]　　标定用户坐标系的３个路点信息　仅在coordType为用户坐标系(WorldCoordinate)时有效；
 * 　　　toolDesc　　　　　　　末端工具描述　　　当coordType＝WorldCoordinate　表示标定用户坐标系时，安装在机器人末端的工具;
 *                                         当coordType＝EndCoordinate　 描述是哪个工具的坐标系
 *
 * 使用说明:
 *      基座坐标系
 *              coordType=BaseCoordinate
 * 　　　　　　　　其他参数默认
 *      用户坐标系
 *              coordType=WorldCoordinate
 * 　　　　　　　　methods　　　　　　　　为标定方法
 * 　　　　　　　　wayPointArray[3]　　　标定坐标系的３个路点
 * 　　　　　　　　toolDesc　　　　　　　　标定用户坐标系时，安装在机器人末端的工具
 * 　　　末端坐标系或工具坐标系
 *              coordType=EndCoordinate
 * 　　　　　　　　methods　　　　　　　　缺省，不需要设置
 * 　　　　　　　　wayPointArray[3]　　　缺省，不需要设置
 * 　　　　　　　　toolDesc　　　　　　　　机器人末端的工具
 *
 *　备注：
 * 　   法兰盘为特殊的工具,工具描述中的位置设置为(0,0,0)，姿态信息设置为(1,0,0,0)
 * 　　　其结构体定义为
 *      ｛
 *          pos{0,0,0},
 *          Ori{1,0,0,0}
 *      ｝  //伪代码
 *
 *      该结构同时用于用户坐标系的标定．一般通过示教3个示教点实现，第一个示教点是用户坐标系的原点；第二个和第三个示教点的选择根据标定方法来确定,遵循右手手法．
 */
typedef struct
{
    coordinate_refer      coordType;          // 坐标系类型

    CoordCalibrateMathod  methods;            // 用户坐标系的标定方法

    JointParam            wayPointArray[3];   //　用于标定用户坐标系的３个点(关节角)

    ToolInEndDesc         toolDesc;           //　工具描述

}CoordCalibrateByJointAngleAndTool;

typedef struct
{
    //用于位置标定点的数量
    int posCalibrateNum ;
    //位置标定点
    wayPoint_S posCalibrateWaypoint[4];
    //用于姿态标定点的数量
    int oriCalibrateNum;
    //姿态标定点
    wayPoint_S oriCalibrateWaypoint[3];
    //姿态标定方法
    ToolKinematicsOriCalibrateMathod  CalibrateMathod;
}ToolCalibrate;


typedef struct
{
    double jointMaxAcc[ARM_DOF];  //关节型运动的最大加速度
    double jointMaxVelc[ARM_DOF]; //关节型运动的最大速度
    double endMaxLineAcc;         //末端型运动的最大加速度
    double endMaxLineVelc;        //末端型运动的最大速度

    MoveRelative relative;        //偏移参数
    CoordCalibrateByJointAngleAndTool relativeOnCoord;   //偏移量基于那个坐标系

    double blendRadius;           //交融半径
    ToolInEndDesc toolInEndDesc;  //工具属性
}MoveProfile_t;

/**
 * @brief 机械臂状态枚举
 **/
enum RobotState
{
    RobotStopped = 0,    //停止
    RobotRunning,        //运行
    RobotPaused,         //暂停
    RobotResumed         //恢复
};



/**
 * 机械臂重力分量x y z
 **/
typedef struct PACKED
{
    float x;
    float y;
    float z;
}RobotGravityComponent;



/**
 * 机械臂关节版本信息
 **/
typedef struct PACKED
{
    char hw_version[8];  //硬件版本信息

    char sw_version[16]; //固件版本信息
}JointVersion;


/**
 *  关节ID信息
 **/
typedef struct PACKED
{
    char productID[16];

}JointProductID;


/**
 *　该结构体描述设备信息
 **/
typedef struct PACKED
{
    uint8 type;                       // 设备型号、芯片型号：上位机主站：0x01  接口板0x02
    char revision[16];                // 设备版本号，eg:V1.0
    char manu_id[16];                 // 厂家ID，"OUR "的ASCII码0x4F 55 52 00
    char joint_type[16];              // 机械臂类型
    JointVersion joint_ver[8];        // 机械臂关节及工具端信息
    char desc[64];                    // 设备描述字符串以0x00结束
    JointProductID jointProductID[8]; // 关节ID信息
    char slave_version[16];           // 从设备版本号 - 字符串表示，如“V1.0.0
    char extio_version[16];           // IO扩展板版本号 -字符串标志，如“V1.0.0

}RobotDevInfo;


/**
 * 描述机械臂的关节状态
 */
typedef struct PACKED
{
    int    jointCurrentI;       // 关节电流    Current of driver
    int    jointSpeedMoto;      // 关节速度    Speed of driver
    float  jointPosJ;           // 关节角      Current position in radian
    float  jointCurVol;         // 关节电压    Rated voltage of motor. Unit: mV
    float  jointCurTemp;        // 当前温度    Current temprature of joint
    int    jointTagCurrentI;    // 电机目标电流 Target current of motor
    float  jointTagSpeedMoto;   // 电机目标速度 Target speed of motor
    float  jointTagPosJ;        // 目标关节角　 Target position of joint in radian
    uint16 jointErrorNum;       // 关节错误码   Joint error of joint num

}JointStatus;

typedef struct PACKED
{
    uint16 JointSYS_ID;             /*!< 电机驱动器ID*/
    uint16 JointModelType;          /*!< 关节类型 */
    uint16 JointFWVer;              /*!< 关节固件版本*/
    uint16 JointReduRatio;          /*!< 关节减速比 */
    uint16 JointCANBaudrate;        /*!< 关节CAN总线波特率*/
    uint16 JointEnableOnPower;      /*!< 驱动上电使能标志*/
    uint16 JointRes;                /*!< 电机内阻（mΩ）*/
    uint16 JointInduc;              /*!< 电机电感（mH）*/
    uint16 JointRatedVolue;         /*!< 电机额定电压（0.1V）*/
    uint16 JointRatedCurrent;       /*!< 电机额定电流（mA）*/
    uint16 JointEncLines;           /*!< 码盘线数*/
    uint16 JointHallValue;          /*!< 当前霍尔状态（1~6）*/
    int16  JointThermistorValue;    /*!< 热敏电阻温度，如果没有热敏电阻，值为-200*/
}JointInitData;

typedef struct PACKED
{
    uint16  JointCurVol;              /*!< 关节当前电压 */
    uint16  JointCurTemp;             /*!< 关节当前温度*/
    uint16  JointWorkMode;            /*!< 关节工作模式 */
    uint16  JointDriEnable;           /*!< 关节驱动器使能标志 */
    uint16  JointOpenPwm;             /*!< 关节开环占空比 */
    int32_t JointTagCurrent;          /*!< 关节当前的目标电流 */
    int32_t JointTagSpeed;            /*!< 关节当前的目标速度 */
    int32_t JointTagPos;              /*!< 关节当前的目标位置 */

    uint16  JointMaxCur;			   /*!< 关节当前的最大电流 */
    uint16  JointMaxSpeed;			   /*!< 关节当前的最大速度 */
    uint16  JointMaxAcc;              /*!< 关节当前的最大加速度 */
    int32_t JointMINPos;              /*!< 关节最小位置 */
    int32_t JointMAXPos;              /*!< 关节最大位置 */

    uint16  JointSEVLock;             /*!< 关节三环参数锁定标志 */
    uint16  JointCurP;                /*!< 关节电流P参数 */
    uint16  JointCurI;                /*!< 关节电流I参数 */
    uint16  JointCurD;                /*!< 关节电流D参数 */
    uint16  JointSpeedP;              /*!< 关节速度P参数 */
    uint16  JointSpeedI;              /*!< 关节速度I参数 */
    uint16  JointSpeedD;              /*!< 关节速度D参数 */
    uint16  JointSpeedDS;             /*!< 关节速度死区 */
    uint16  JointPosP;                /*!< 关节位置P参数 */
    uint16  JointPosI;                /*!< 关节位置I参数 */
    uint16  JointPosD;                /*!< 关节位置D参数 */
    uint16  JointPosDS;               /*!< 关节位置DS参数 */

}JointCommonData;


//关节减速比
typedef enum
{
    RATIO_TYPE_51  = 0x01,
    RATIO_TYPE_81  = 0x02,
    RATIO_TYPE_101 = 0x03,
    RATIO_TYPE_121 = 0x04,
    RATIO_TYPE_161 = 0x05,
}JointRatioType;

//关节型号
typedef enum
{
    MODULE_TYPE_14 = 0x01,
    MODULE_TYPE_17 = 0x02,
    MODULE_TYPE_20 = 0x03,
    MODULE_TYPE_25 = 0x04,
    MODULE_TYPE_32 = 0x05,
    MODULE_TYPE_40 = 0x06,
}JointModuleType;

//关节电机型号
typedef enum
{
    MOTO_TYPE_YET       = 0x01,
    MOTO_TYPE_YET_OLD   = 0x02,
    MOTO_TYPE_ZY        = 0x03,
    MOTO_TYPE_ZY_PRO    = 0x04,
}JointMotorType;

//关节类型参数信息
typedef struct PACKED
{
    uint16_t joint_type;
    uint16_t motor_encoder_line;
    uint16_t reduce_ratio;
    uint16_t joint_software_version;
    uint32_t res1;
    uint32_t res2;
}JointTypeParameter;


/**
 * @brief 离线轨迹相关枚举
 */
enum Robot_Dyn_identify_traj
{
    Dyn_identify_traj_none = 0,
    Dyn_identify_traj_robot,      //submode: 0/1 <-> internal/hybrid
    Dyn_identify_traj_tool,       //submode: 0/1 <-> tool only/tool+friction
    Dyn_identify_traj_tool_abort
};



/**
 *  @brief 接口板固件升级枚举
 */
typedef enum
{
    update_master_board_firmware_trans_start = 1,
    update_master_board_firmware_trans_data  = 2,
    update_master_board_firmware_trans_end   = 3,
    update_slave_board_firmware_trans_start  = 4,
    update_slave_board_firmware_trans_data   = 5,
    update_slave_board_firmware_trans_end    = 6
}update_board_firmware_cmd;



typedef struct
{
    bool trackEnable;            //T
    wayPoint_S currentRoadPoint; //R
    wayPoint_S nextRoadPoint;    //R
    int timeInterval;            //T
    double currentPosError[3];   //T
    double maxVel;     //T
    double maxAcc;     //T
    bool paraChanged;  //RT
}SeamTracking;

typedef struct PACKED{
    uint16 cmd;          //请求指令 0x01-读 0x02-写
    uint16 baseDataLen;  //基座信息长度
    uint16 jointDataLen; //关节信息长度
}RobotArmParamHeader;

//位置姿态类型枚举
typedef enum
{
    POSITION_MM_AND_RPY_ANGLE_SPACE_SPLIT = 1,   //位置(单位:毫米)+ 姿态(欧拉角 单位：角度制)  空格分割
    POSITION_M_AND_QUATERNION_COMMA_SPLIT = 10,  //位置(单位:米)  + 姿态(四元素)  逗号分割
}POSITION_ORIENTATION_TYPE;

typedef struct PACKED{
    RobotArmParamHeader header;
    uint8 base[382]; //底座参数数据    //RobotBaseParameters
    uint8 joints[512]; //关键参数数据  //RobotJointsParameter
}RobotArmParam;

typedef struct PACKED{
    uint16 robot_type;        //robot type
    uint16 auth_type;         //auth type
    uint32 robot_expire;      //robot expire
    uint8 reserve[12];        //reserve
    uint32 robot_duration;    //robot duration
    uint32 joint_duration[6]; //joint duration
}RobotInfo;

typedef struct PACKED{
    double K[6] ;        //motor torque constant
    double IA[4];        //rotor inertia
    double M[1] ;        //link mass
    double MXYZ[13];     //center of mass
    double IXYZ[28];     //Inertia parameter
    double CB[6]   ;     //current bias
}RobotDynamicsParameters;

typedef struct PACKED{
    double FP[6];                 //friction compensation percent
    double FD[6];                 //damp coefficient
    double FK[6];                 //stiffness coefficient
    double FM[6];                 //mass coefficient
    double pos_limit[6];          //position limit
    double velocity_limit[6];     //velocity limit
    double acceleration_limit[6]; //acceleration limit
}RobotHandguidingParameters;

typedef struct PACKED{
    double da[6]    ;//compensation a
    double dd[6]    ;//compensation d
    double dalpha[6];//compensation alpha
    double dbeta[6] ;//compensation beta
    double dratio[6];//compensation ratio
    double dtheta[6];//compensation theta
}RobotKinematicsParameters;

typedef struct PACKED{
    uint16 FL[6];        //load friction compensation
    uint16 FR[6];        //reserved friction compensation
    int16  tmp_a[6];      //tmp_coefficient_a
    uint16 tmp_b[6];     //tmp_coefficient_b
    int16  posvel_a1[6];  //positive_vel_a1
    uint16 posvel_b1[6]; //positive_vel_b1
    int16  posvel_a2[6];  //positive_vel_a2
    uint16 posvel_b2[6]; //positive_vel_b2
    uint16 posvel_c2[6]; //positive_vel_c2
    int16  negvel_a1[6];  //negative_vel_a1
    int16  negvel_b1[6];  //negative_vel_b1
    uint16 negvel_a2[6]; //negative_vel_a2
    uint16 negvel_b2[6]; //negative_vel_b2
    int16  negvel_c2[6];  //negative_vel_c2
}RobotFrictionParameters;

typedef struct PACKED{
    RobotInfo info;
    RobotDynamicsParameters dynamicParam;
    RobotHandguidingParameters handguidingParam;
    RobotKinematicsParameters kinematicsParam;
}RobotBaseParameters;

typedef struct PACKED{
    RobotFrictionParameters frictionParam;
}RobotJointsParameter;

typedef struct PACKED
{
    int16_t err;                // 错误码
    int16_t vol;                // 电压
    int16_t temp;               // 温度
    int32_t sys_cur;            // 电流
    int32_t sys_speed;          // 速度
    int32_t sys_pos;            // 位置
    int16_t screwlock_ctl_word; // 控制字
    int16_t actual_torque;      // 力矩
    int16_t screwlock_status;   // 锁付状态
    int16_t res[4];             // 备用
}ScrewerStatus;

typedef enum
{
    LL_INFO=0,
    LL_DEBUG,
    LL_WARN,
    LL_ERROR,
    LL_FATAL
}LOG_LEVEL;

class PlannerResult
{
public:
    enum DescribeSpace
    {
        NOT_DEFINED             = -1,   // 未定义
        JOINT                   = 0,    // 关节空间描述
        CARTESIAN               = 1,    // 笛卡尔空间描述
        FULL                    = 2     // 全空间描述
    };// 机械臂状态描述枚举

    double                          time;                               // 轨迹点对应的路径完成时间, 取值[0, duration]
    double                          id = -1;                            // 路径ID
    DescribeSpace                   type{DescribeSpace::NOT_DEFINED};   // 路径点类型
    std::array<double, 6>           pose;                               // 笛卡尔空间位姿
    std::array<double, ARM_DOF>     joint;                              // 关节空间构型
    std::array<double, 6>           xd, xdd;                            // 轨迹点对应的笛卡尔空间速度 加速度
    std::array<double, ARM_DOF>     qd, qdd;                            // 轨迹点对应的关节空间速度 加速度
    std::array<double, ARM_DOF>     effort;                             // 轨迹点对应的关节电流
    std::array<double, 6>           wrench;                             // 轨迹点对应的TCP处的力/力矩
    double                          line_speed;                         // 末端速度
    bool                            is_key;                             // 轨迹过渡点

    PlannerResult() {}

    PlannerResult(const PlannerResult &other) {
        time = other.time;
        id = other.id;
        type = other.type;
        for (int i = 0; i < ARM_DOF; i++) {
            joint[i] = other.joint[i];
            qd[i] = other.qd[i];
            qdd[i] = other.qdd[i];
            effort[i] = other.effort[i];
        }
        for (int i = 0; i < 6; i++) {
            pose[i] = other.pose[i];
            xd[i] = other.xd[i];
            xdd[i] = other.xdd[i];
            wrench[i] = other.wrench[i];
        }
        line_speed = other.line_speed;
        is_key = other.is_key;
    }

}; // 轨迹规划结果

class AnalyseResult
{
public:
    double                          id = -1;                            // 路径ID
    double                          line_speed;                         // 末端速度

    AnalyseResult() {}

    AnalyseResult(const AnalyseResult &other) {
        id = other.id;
        line_speed = other.line_speed;
    }

}; // 轨迹评估结果


/**********************NC相关数据结构*********************************/
enum Nc_PointShape_type{
    Line = 0,
    Cir,
    JIONT
};

enum Io_Status{
    Off = 0,
    On,
    None

};

enum Nc_Point_BaseOrUser
{
    User = 0,
    Base
};

enum Nc_Rise_or_Fall
{
    Start_point = 0,
    End_point,
    RF_None
};

struct Nc_Points_attributes{
    Nc_Points_attributes(double abd,bool is_abd = false,double ls=0,double as=0):
        line_speed(ls),acc_speed(as),AheadBlendDis(abd),is_ABD(is_abd){}
    double AheadBlendDis;
    bool is_ABD;
    double line_speed;
    double acc_speed;
};

struct Nc_Points{
    Nc_Points(double abd = 0, bool is_abd = true):
    type(Nc_PointShape_type::Line),io_status(Io_Status::None),NP_attribute(abd,is_abd)
    {}
    aubo_robot_namespace::wayPoint_S wp;
    Nc_PointShape_type type;
    Io_Status io_status;
    Nc_Points_attributes NP_attribute;
};

enum Nc_Move_Mode{
    Nc_IS_IDLE=0,//表示当前nc的状态为空闲
    Nc_IS_WORKING,//表示当前nc的状态为工作中，此时无法打开新的nc线程
};

struct Nc_IkError
{
    Nc_IkError(int ln = 0,int Ikret = 0):Line_number(ln),Ik_Ret(Ikret){}
    int Line_number;
    int Ik_Ret;
};

typedef struct{
    Nc_Move_Mode mode;
    double progress;//表示当前nc的进度 值为0-1
}Nc_Move_Status;

enum Nc_Move_Cmd{
    PAUSE_Nc = 0,
    CONTINUE_Nc,
    KILL_Nc,
    Default_Nc,
};

enum NC_Import_File_Type{
    NONE = 0,
    NC,
    AUBO
};
/*********************************************************************/

/**
 * 描述机械臂事件类型　　　event define
 *
 * 机械臂的很多信息（故障，通知）是通过事件通知到客户的，所有在使用SDK时，
 * 务必注册接收事件的回调函数。
 */
typedef enum{
    RobotEvent_armCanbusError,            //机械臂CAN总线错误  已过时，不建议使用
    RobotEvent_remoteHalt,                //远程关机
    RobotEvent_remoteEmergencyStop,       //机械臂远程急停
    RobotEvent_jointError,                //关节错误        PS:已过时，不建议使用

    RobotEvent_forceControl,              //力控制
    RobotEvent_exitForceControl,          //退出力控制

    RobotEvent_softEmergency,             //软急停
    RobotEvent_exitSoftEmergency,         //退出软急停

    RobotEvent_collision,                 //碰撞           已过时，不建议使用　已用RobotEventJointCollision(2123) 替代
    RobotEvent_collisionStatusChanged,    //碰撞状态改变    已过时，不建议使用　已用RobotEventJointCollision(2123) 替代
    RobotEvent_tcpParametersSucc,         //工具动力学参数设置成功   系统事件，用户可以忽略
    RobotEvent_powerChanged,              //机械臂电源开关状态改变
    RobotEvent_ArmPowerOff,               //机械臂电源关闭          不建议使用　　已用RobotEventArmPowerOff(2600) 替代
    RobotEvent_mountingPoseChanged,       //安装位置发生改变
    RobotEvent_encoderError,              //编码器错误             不建议使用

    RobotEvent_encoderLinesError,         //编码器线数不一致        不建议使用　　已用RobotEventEncoderLineError（2203）替代
    RobotEvent_singularityOverspeed,      //奇异点超速
    RobotEvent_currentAlarm,              //机械臂电流异常
    RobotEvent_toolioError,               //机械臂工具端错误
    RobotEvent_robotStartupPhase,         //机械臂启动阶段     系统事件，用户可以忽略
    RobotEvent_robotStartupDoneResult,    //机械臂启动完成结果  系统事件，用户可以忽略
    RobotEvent_robotShutdownDone,         //机械臂关机结果     系统事件，用户可以忽略
    RobotEvent_atTrackTargetPos,          //机械臂轨迹运动到位信号通知   系统事件，用户可以忽略

    RobotSetPowerOnDone,                  //设置电源状态完成
    RobotReleaseBrakeDone,                //机械臂刹车释放完成  系统事件，用户可以忽略
    RobotEvent_robotControllerStateChaned,//机械臂控制状态改变  系统事件，用户可以忽略
    RobotEvent_robotControllerError,      //机械臂控制错误----一般是算法规划出现问题时返回
    RobotEvent_socketDisconnected,        //socket断开连接

    RobotEvent_robotControlException,
    RobotEvent_trackPlayInterrupte,

    RobotEvent_staticCollisionStatusChanged,  //不建议使用 已过时
    RobotEvent_MountingPoseWarning,

    RobotEvent_MacDataInterruptWarning,
    RobotEvent_ToolIoError,                 //
    RobotEvent_InterfacBoardSafeIoEvent,    //安全IO通知型事件

    RobotEvent_RobotHandShakeSucc,          //系统事件，用户可以忽略
    RobotEvent_RobotHandShakeFailed,        //系统事件，用户可以忽略

    RobotEvent_RobotErrorInfoNotify,        //不建议使用 已过时

    RobotEvent_InterfacBoardDIChanged,      //通知型事件 DI状态改变
    RobotEvent_InterfacBoardDOChanged,      //通知型事件 DO状态改变
    RobotEvent_InterfacBoardAIChanged,      //通知型事件 AI状态改变
    RobotEvent_InterfacBoardAOChanged,      //通知型事件 AO状态改变

    RobotEvent_UpdateJoint6Rot360Flag,       //系统事件，用户可以忽略

    RobotEvent_RobotMoveControlDone,         //系统事件，用户可以忽略
    RobotEvent_RobotMoveControlStopDone,     //系统事件，用户可以忽略
    RobotEvent_RobotMoveControlPauseDone,    //系统事件，用户可以忽略
    RobotEvent_RobotMoveControlContinueDone, //系统事件，用户可以忽略

    //主从模式切换
    RobotEvent_RobotSwitchToOnlineMaster,    //通知型事件  进入联动主模式
    RobotEvent_RobotSwitchToOnlineSlave,     //通知型事件  进入联动从模式

    RobotEvent_ConveyorTrackRobotStartup,    //系统事件，用户可以忽略
    RobotEvent_ConveyorTrackRobotCatchup,    //系统事件，用户可以忽略

    RobotEvent_exceptEvent = 100,


    RobotEventInvalid                         =1000,   // 无效的事件

    /**
     * RobotControllerErrorEvent  控制器异常事件 1001~1499
     *
     * 事件处理建议
     * 建议采取措施:停止当前运动
     *
     * PS: 这些事件会引起机械臂运动的错误返回
     *     使用时尽量用枚举变量　　枚举变量值只是为了查看日志方便
     *
     **/
    RobotEventMoveJConfigError                 = 1001,  // moveJ configuration error 关节运动属性配置错误
    RobotEventMoveLConfigError                 = 1002,  // moveL configuration error 直线运动属性配置错误
    RobotEventMovePConfigError                 = 1003,  // moveP configuration error 轨迹运动属性配置错误
    RobotEventInvailConfigError                = 1004,  // invail configuration      无效的运动属性配置
    RobotEventWaitRobotStopped                 = 1005,  // please wait robot stopped 等待机器人停止
    RobotEventJointOutRange                    = 1006,  // joint out of range        超出关节运动范围
    RobotEventFirstWaypointSetError            = 1007,  // please set first waypoint correctly in modep    请正确设置MODEP第一个路点
    RobotEventConveyorTrackConfigError         = 1008,  // configuration error for conveyor tracking       传送带跟踪配置错误
    RobotEventConveyorTrackTrajectoryTypeError = 1009,  // unsupported conveyor tracking trajectory type   传送带轨迹类型错误
    RobotEventRelativeTransformIKFailed        = 1010,  // inverse kinematics failure due to invalid relative transform  相对坐标变换逆解失败
    RobotEventTeachModeCollision               = 1011,  // collision in teach-mode  示教模式发生碰撞
    RobotEventextErnalToolConfigError          = 1012,  // configuration error for external tool and hand workobject     运动属性配置错误,外部工具或手持工件配置错误

    RobotEventTrajectoryAbnormal               = 1101,  // Trajectory is abnormal 轨迹异常
    RobotEventOnlineTrajectoryPlanError        = 1102,  // Trajectory is abnormal,online planning failed  轨迹规划错误
    RobotEventOnlineTrajectoryTypeIIError      = 1103,  // Trajectory is abnormal,type II online planning failed 二型在线轨迹规划失败
    RobotEventIKFailed                         = 1104,  // Trajectory is abnormal,inverse kinematics failed 逆解失败
    RobotEventAbnormalLimitProtect             = 1105,  // Trajectory is abnormal,abnormal limit protection 动力学限制保护
    RobotEventConveyorTrackingFailed           = 1106,  // Trajectory is abnormal,conveyor tracking failed  传送带跟踪失败
    RobotEventConveyorOutWorkingRange          = 1107,  // Trajectory is abnormal,exceeding the conveyor working range 超出传送带工作范围
    RobotEventTrajectoryJointOutOfRange        = 1108,  // Trajectory is abnormal,joint out of range 关节超出范围
    RobotEventTrajectoryJointOverspeed         = 1109,  // Trajectory is abnormal,joint overspeed 关节超速
    RobotEventOfflineTrajectoryPlanFailed      = 1110,  // Trajectory is abnormal,Offline track planning failed 离线轨迹规划失败
    RobotEventTrajectoryJointAccOutOfRange     = 1111,  // Trajectory is abnormal,joint acc out of range 轨迹异常,关节加速度超限

    RobotEventForceModeException               = 1120,  // 力控模式异常
    RobotEventForceModeIKFailed                = 1121,  // Trajectory is abnormal,force control mode ik failed 轨迹异常，力控模式下失败
    RobotEventForceModeTrackJointverspeed      = 1122,  // Trajectory is abnormal,joint overspeed 关节超速

    RobotEventControllerIKFailed               = 1200,  // The controller has an exception and the inverse kinematics failed 控制器异常，逆解失败
    RobotEventControllerStatusException        = 1201,  // The controller has an exception and the status is abnormal 控制器异常，状态异常
    RobotEventControllerTrackingLost           = 1202,  // Exception that joint tracking is lost, 关节跟踪误差过大.
    RobotEventMonitorErrTrackingLost           = 1203,  // Exception that joint tracking is lost, 关节跟踪误差过大.
    RobotEventMonitorErrNoArrivalInTime        = 1204,  // not used 预留
    RobotEventMonitorErrCurrentOverload        = 1205,  // not used 预留
    RobotEventMonitorErrJointOutOfRange        = 1206,  // Exception that joint out of range  　机械臂关节超出限制范围
    RobotEventMonitorErrFifoDataTimeNotRead    = 1207,  // controller fifo data timeout was not read 队列中数据超时未被读取

    RobotEventMoveEnterStopState               = 1300,  // Movement enters the stop state 运动进入到stop阶段


    /**
     * RobotHardwareErrorEvent  来自硬件反馈的异常事件 2001~2999
     *
     * 事件处理建议
     * RobotEventJointEncoderPollustion   建议采取措施:警告性通知
     * RobotEventDriveVersionError        建议采取措施:警告性通知
     * RobotEventJointCollision           建议采取措施: 如需回复当前运动，调用暂停函数  恢复的时候先调用碰撞回复函数，在调用continue函数
                                                      如不需回复当前运动，调用停止函数  恢复的时候调用碰撞回复函数可以
     * 其余的事件　　  建议采取措施:停止当前运动
     **/

    RobotEventHardwareErrorNotify              = 2001,  // Robot hardware error 机械臂硬件错误

    RobotEventJointError                       = 2101,  // Robot joint error 机械臂关节错误
    RobotEventJointOverCurrent                 = 2102,  // Robot joint over current.  机械臂关节过流
    RobotEventJointOverVoltage                 = 2103,  // Robot joint over voltage.　 机械臂关节过压
    RobotEventJointLowVoltage                  = 2104,  // Robot joint low voltage.　  机械臂关节欠压
    RobotEventJointOverTemperature             = 2105,  // Robot joint over temperature. 机械臂关节过温
    RobotEventJointHallError                   = 2106,  // Robot joint hall error. 机械臂关节霍尔错误
    RobotEventJointEncoderError                = 2107,  // Robot joint encoder error. 机械臂关节编码器错误
    RobotEventJointAbsoluteEncoderError        = 2108,  // Robot joint absolute encoder error. 机械臂关节绝对编码器错误
    RobotEventJointCurrentDetectError          = 2109,  // Robot joint current position error. 机械臂关节当前位置错误
    RobotEventJointEncoderPollustion           = 2110,  // Robot joint encoder pollustion.     机械臂关节编码器污染        建议采取措施:警告性通知
    RobotEventJointEncoderZSignalError         = 2111,  // Robot joint encoder Z signal error. 机械臂关节编码器Z信号错误
    RobotEventJointEncoderCalibrateInvalid     = 2112,  // Robot joint encoder calibrate　invalid. 机械臂关节编码器校准失效
    RobotEventJoint_IMU_SensorInvalid          = 2113,  // Robot joint IMU sensor invalid. 机械臂关节IMU传感器失效
    RobotEventJointTemperatureSensorError      = 2114,  // Robot joint temperature sensor error. 机械臂关节温度传感器出错
    RobotEventJointCanBusError                 = 2115,  // Robot joint CAN BUS error. 机械臂关节CAN总线出错
    RobotEventJointCurrentError                = 2116,  // Robot joint current error. 机械臂关节当前电流错误
    RobotEventJointCurrentPositionError        = 2117,  // Robot joint current position error. 机械臂关节当前位置错误
    RobotEventJointOverSpeed                   = 2118,  // Robot joint over speed. 机械臂关节超速
    RobotEventJointOverAccelerate              = 2119,  // Robot joint over accelerate. 机械臂关节加速度过大错误
    RobotEventJointTraceAccuracy               = 2120,  // Robot joint trace accuracy. 机械臂关节跟踪精度错误
    RobotEventJointTargetPositionOutOfRange    = 2121,  // Robot joint target position out of range.  机械臂关节目标位置超范围
    RobotEventJointTargetSpeedOutOfRange       = 2122,  // Robot joint target speed out of range. 机械臂关节目标速度超范围
    RobotEventJointCollision                   = 2123,  // Robot joint collision. 机械臂碰撞    　　　建议采取措施:暂停当前运动
    RobotEventJointSlaveOverCurrent            = 2124,  // Robot joint slave over current! 从机过流
    RobotEventJointSlaveOverVoltage            = 2125,  // Robot joint slave over voltage! 从机过压
    RobotEventJointSlaveLowVoltage             = 2126,  // Robot joint slave low voltage! 从机欠压
    RobotEventJointSlavePositionDiffOver       = 2127,  // Robot joint position deviation between master and slave is too big! 主从机位置偏差过大
    RobotEventJointSlaveSpeedDiffOver          = 2128,  // Robot joint speed deviation between master and slave is too big! 主从机速度偏差过大
    RobotEventJointSlaveAbsoluteEncoderError   = 2129,  // Robot joint slave abs encoder! 从机绝对编码器错误
    RobotEventJointSlaveCurrentDetectError     = 2130,  // Robot joint slave detect current! 从机电流检测错误
    RobotEventJointSlaveEncoderPollustion      = 2131,  // Robot joint slave encoder pollustion! 从机编码器污染
    RobotEventJointSlaveEncoderZSignalError    = 2132,  // Robot joint slave enocder z signal! 从机编码器Z信号错误
    RobotEventJointSlaveCommunication          = 2133,  // Robot joint communication between master and slave error! 主从机之间通信错误

    RobotEventDataAbnormal                     = 2200,  // Robot data abnormal 机械臂信息异常
    RobotEventRobotTypeError                   = 2201,  // Robot type error 机械臂类型错误
    RobotEventAccelerationSensorError          = 2202,  // Robot acceleration sensor error 机械臂加速度计芯片错误
    RobotEventEncoderLineError                 = 2203,  // Robot encoder line error  机械臂编码器线数错误
    RobotEventEnterDragAndTeachModeError       = 2204,  // Robot enter drag and teach mode error 机械臂进入拖动示教模式错误
    RobotEventExitDragAndTeachModeError        = 2205,  // Robot exit drag and teach mode error 机械臂退出拖动示教模式错误
    RobotEventMACDataInterruptionError         = 2206,  // Robot MAC data interruption error 机械臂MAC数据中断错误
    RobotEventDriveVersionError                = 2207,  // Drive version error 驱动器版本错误(关节固件版本不一致)
    RobotEventToolNotExist                     = 2208,  // Robot tool do not exist! 工具端不存在
    RobotEventPowerOnCheckError                = 2209,  // Robot power on check error! 上电自检错误
    RobotEventDriverVersionTooLow              = 2210,  // Robot driver firmware version is too low! 驱动器版本过低
    RobotEventTargetPosDataBufferOverflow      = 2211,  // Robot target pos data buffer overflow! 目标位置数据溢出
    RobotEventRobotArmNotConnected             = 2212,  // Robot arm is not connected! 机械臂未连接
    RobotEventPayloadError                     = 2213,  // Robot payload error! 负载错误

    RobotEventInitAbnormal                     = 2300,  // Robot init abnormal  机械臂初始化异常
    RobotEventDriverEnableFailed               = 2301,  // Robot driver enable failed  机械臂驱动器使能失败
    RobotEventDriverEnableAutoBackFailed       = 2302,  // Robot driver enable auto back failed  机械臂驱动器使能自动回应失败
    RobotEventDriverEnableCurrentLoopFailed    = 2303,  // Robot driver enable current loop failed  机械臂驱动器使能电流环失败
    RobotEventDriverSetTargetCurrentFailed     = 2304,  // Robot driver set target current failed  机械臂驱动器设置目标电流失败
    RobotEventDriverReleaseBrakeFailed         = 2305,  // Robot driver release brake failed  机械臂释放刹车失败
    RobotEventDriverEnablePostionLoopFailed    = 2306,  // Robot driver enable postion loop failed  机械臂使能位置环失败
    RobotEventSetMaxAccelerateFailed           = 2307,  // Robot set max accelerate failed  设置最大加速度失败
    RobotEventSetPositionLoopWorkModeFailed    = 2308,  // Robot set position loop work mode failed! 设置位置环工作模式失败
    RobotEventCalcuateGravityComponentFailed   = 2309,  // Robot calculate the gravity component failed! 计算重力分量错误
    RobotEventSetMaxVelocityFailed             = 2310,  // Robot set max velocity failed! 设置最大速度失败
    RobotEventEnableCANSyncFrameFailed         = 2311,  // Robot enable can synchronization frame failed! 使能CAN同步帧失败

    RobotEventSafetyError                      = 2400,  // Robot Safety error  机械臂安全出错
    RobotEventExternEmergencyStop              = 2401,  // Robot extern emergency stop  机械臂外部紧急停止
    RobotEventSystemEmergencyStop              = 2402,  // Robot system emergency stop  机械臂系统紧急停止
    RobotEventTeachpendantEmergencyStop        = 2403,  // Robot teachpendant emergency stop  机械臂示教器紧急停止
    RobotEventControlCabinetEmergencyStop      = 2404,  // Robot control cabinet emergency stop  机械臂控制柜紧急停止
    RobotEventProtectionStopTimeout            = 2405,  // Robot protection stop timeout  机械臂保护停止超时
    RobotEventEeducedModeTimeout               = 2406,  // Robot reduced mode timeout  机械臂缩减模式超时

    RobotEventSystemAbnormal                   = 2500,  // Robot systen abnormal  机械臂系统异常
    RobotEvent_MCU_CommunicationAbnormal       = 2501,  // Robot mcu communication error  机械臂mcu通信异常
    RobotEvent485CommunicationAbnormal         = 2502,  // Robot RS485 communication error  机械臂485通信异常
    RobotEvent220VDetectionBoardAbnormal       = 2503,  // Robot 220v detection board abnormal  220V掉电板检测错误

//#if 0 // 非实时版本
    RobotEventCurrentJointOutRange             = 2550,  // Joint out of Range
//#else
    RobotEventSoftEmergency                    = 2550,   // 软急停
    RobotEventSoftEmergencyExit                = 2551,   // 软急停退出
//#endif

    RobotEventArmPowerOff                      = 2600,  //Disconnecting the contactor causes the arm 48V power off 控制柜接触器断开导致机械臂48V断电

    RobotEventHardwareErrorNotifyMaximumIndex  = 2999,  // 索引

    RobotEventNotifyEvent                      = 3000,  // Robot notification event 机械臂通知性事件
    RobotEventNotifyCollisionLevelChange       = 3001,  // Robot Collision level change 机械臂事件通知-碰撞等级被改变
    RobotEventNotifyEnterFlexibleControlMode   = 3010,  // 进入柔性控制模式通知
    RobotEventNotifyExitFlexibleControlMode    = 3011,  // 退出柔性控制模式通知
    RobotEventNotifyEnterSpeedReducedMode      = 3015,  // 进入速度缩减模式通知
    RobotEventNotifyExitSpeedReducedMode       = 3016,  // 退出速度缩减模式通知

    RobotEventNotifyStopCurrentMove            = 3100,  // 停止掉当前运动


    RobotEventNotifyScriptFinishSucc            = 3200,  // 脚本运行结束:成功
    RobotEventNotifyScriptFinishFailed          = 3201,  // 脚本运行结束:失败
    RobotEventNotifyScriptRunInterruptedByStopOperation = 3202,  //脚本运行中断:被stop操作中断

    RobotEventNotifyScriptRunLabel              = 3300,  //通知性事件:脚本运行标签
    RobotEventNotifyScriptTraceInfo             = 3301,  //通知性事件:脚本Print
    RobotEventNotifyScriptSetVariable          = 3302,  // 通知性事件:设置示教器全局变量值

    RobotEventNotifyJointUpdateFinishSucc       = 3400,  // 关节驱动升级结束：成功
    RobotEventNotifyJointUpdateFinishFailed     = 3401,  // 关节驱动升级结束：失败
    RobotEventNotifyJointUpdating               = 3402,  // 关节驱动升级中
    RobotEventNotifyJointNoProgram              = 3410,  // 关节在上电后检测到没有程序，需要升级

    RobotEventMoveGroupCurrentWaypointId        = 3500,  // moveGroup当前路点id
    RobotEventMoveGroupPaused                    = 3501,  // moveGroup暂停完成
    RobotEventMoveGroupResumed                   = 3502,  // moveGroup恢复完成
    RobotEventMoveGroupStopped                   = 3503,  // moveGroup停止完成
    RobotEventMoveGroupAtTargrtPos               = 3504,  // moveGroup运行结束

    //unknown event
    robot_event_unknown = 10000,

    //user event
    RobotEvent_User    = 9000,                            // first user event id
    RobotEvent_MaxUser = 9999                             // last user event id

}RobotEventType;


/** 事件类型 **/
typedef struct{
    RobotEventType  eventType;       //事件类型号
    int             eventCode;       //
    std::string     eventContent;    //事件内容
}RobotEventInfo;


/**
 *  接口函数 错误码定义  成功返回InterfaceCallSuccCode(0);失败返回对应的错误号
 *
 *　下面是错误代码列表
 *       21000 ~ 21999错误码　　表示错由于控制器异常事件导致的
 *       22000 ~ 22999错误码　　表示错由于硬件层异常事件导致的
 */
enum
{
    InterfaceCallSuccCode = 0,          //接口调用成功的返回值
};

typedef enum
{
    ErrnoSucc = InterfaceCallSuccCode,       // 成功

    ErrCode_Base                           = 10000,
    ErrCode_Failed                         = 10001, // 通用失败 failed
    ErrCode_ParamError                     = 10002, // 参数错误 parameters error
    ErrCode_ConnectSocketFailed            = 10003, // 连接失败 socket connect failed Socket
    ErrCode_SocketDisconnect               = 10004, // Socket断开连接　socket disconnected Socket
    ErrCode_CreateRequestFailed            = 10005, // 创建请求失败 create request failed
    ErrCode_RequestRelatedVariableError    = 10006, // 请求相关的内部变量出错 internal error
    ErrCode_RequestTimeout                 = 10007, // 请求超时 timout
    ErrCode_SendRequestFailed              = 10008, // 发送请求信息失败 send request failed
    ErrCode_ResponseInfoIsNULL             = 10009, // 响应信息为空 response is null
    ErrCode_ResolveResponseFailed          = 10010, // 解析响应失败 parse response failed
    ErrCode_FkFailed                       = 10011, // 正解出错 fk failed
    ErrCode_IkFailed                       = 10012, // 逆解出错 ik failed
    ErrCode_ToolCalibrateError             = 10013, // 工具标定参数有错 tool coordinate paramter error
    ErrCode_ToolCalibrateParamError        = 10014, // 工具标定参数有错 tool coordinate paramter error
    ErrCode_CoordinateSystemCalibrateError = 10015, // 坐标系标定失败 user coordinate calibrate failed
    ErrCode_BaseToUserConvertFailed        = 10016, // 基坐标系转用户座标失败 base coordinate convert to user coordinate fialed
    ErrCode_UserToBaseConvertFailed        = 10017, // 用户坐标系转基座标失败 user coordinate convert to base coordinate fialed


    ErrCode_MotionRelatedVariableError     = 10018, // 运动相关的内部变量出错 move funcation paramters error
    ErrCode_MotionRequestFailed            = 10019, // 运动请求失败 call move funcation failed
    ErrCode_CreateMotionRequestFailed      = 10020, // 生成运动请求失败 create request failed
    ErrCode_MotionInterruptedByEvent       = 10021, // 运动被事件中断 move funcation interrupt
    ErrCode_MotionWaypointVetorSizeError   = 10022, // 运动相关的路点容器的长度不符合规定 parameter error
    ErrCode_ResponseReturnError            = 10023, // 服务器响应返回错误 server reponse error
    ErrCode_RealRobotNoExist               = 10024, // 真实机械臂不存在，因为有些接口只有在真是机械臂存在的情况下才可以被调用 real robot no exist

    ErrCode_moveControlSlowStopFailed      = 11025, // 调用缓停接口失败 call function failed, server side error
    ErrCode_moveControlFastStopFailed      = 11026, // 调用急停接口失败 call function failed, server side error
    ErrCode_moveControlPauseFailed         = 11027, // 调用暂停接口失败 call function failed, server side error
    ErrCode_moveControlContinueFailed      = 11028, // 调用继续接口失败 call function failed, server side error


    //20000~21000 的异常码是为了版本兼容  后续会逐渐取消
    ErrCode_collision                      = 20008,  //碰撞
    ErrCode_robotControllerError           = 20026,  //控制器异常


    /**
     * 控制器返回的异常
     **/
    ErrCodeMoveJConfigError                 = 21001,  // moveJ configuration error 关节运动属性配置错误
    ErrCodeMoveLConfigError                 = 21002,  // moveL configuration error 直线运动属性配置错误
    ErrCodeMovePConfigError                 = 21003,  // moveP configuration error 轨迹运动属性配置错误
    ErrCodeInvailConfigError                = 21004,  // invail configuration      无效的运动属性配置
    ErrCodeWaitRobotStopped                 = 21005,  // please wait robot stopped 等待机器人停止
    ErrCodeJointOutRange                    = 21006,  // joint out of range        超出关节运动范围
    ErrCodeFirstWaypointSetError            = 21007,  // please set first waypoint correctly in modep    请正确设置MODEP第一个路点
    ErrCodeConveyorTrackConfigError         = 21008,  // configuration error for conveyor tracking       传送带跟踪配置错误
    ErrCodeConveyorTrackTrajectoryTypeError = 21009,  // unsupported conveyor tracking trajectory type   传送带轨迹类型错误
    ErrCodeRelativeTransformIKFailed        = 21010,  // inverse kinematics failure due to invalid relative transform  相对坐标变换逆解失败
    ErrCodeTeachModeCollision               = 21011,  // collision in teach-mode  示教模式发生碰撞
    ErrCodeextErnalToolConfigError          = 21012,  // configuration error for external tool and hand workobject     运动属性配置错误,外部工具或手持工件配置错误

    ErrCodeTrajectoryAbnormal               = 21101,  // Trajectory is abnormal 轨迹异常
    ErrCodeOnlineTrajectoryPlanError        = 21102,  // Trajectory is abnormal,online planning failed  轨迹规划错误
    ErrCodeOnlineTrajectoryTypeIIError      = 21103,  // Trajectory is abnormal,type II online planning failed 二型在线轨迹规划失败
    ErrCodeIKFailed                         = 21104,  // Trajectory is abnormal,inverse kinematics failed 逆解失败
    ErrCodeAbnormalLimitProtect             = 21105,  // Trajectory is abnormal,abnormal limit protection 动力学限制保护
    ErrCodeConveyorTrackingFailed           = 21106,  // Trajectory is abnormal,conveyor tracking failed  传送带跟踪失败
    ErrCodeConveyorOutWorkingRange          = 21107,  // Trajectory is abnormal,exceeding the conveyor working range 超出传送带工作范围
    ErrCodeTrajectoryJointOutOfRange        = 21108,  // Trajectory is abnormal,joint out of range 关节超出范围
    ErrCodeTrajectoryJointOverspeed         = 21109,  // Trajectory is abnormal,joint overspeed 关节超速
    ErrCodeOfflineTrajectoryPlanFailed      = 21110,  // Trajectory is abnormal,Offline track planning failed 离线轨迹规划失败
    ErrCodeTrajectoryJointAccOutOfRange     = 21111,  // Trajectory is abnormal,joint acc out of range 轨迹异常,关节加速度超限

    ErrCodeForceModeException               = 21120,  // 力控模式异常
    ErrCodeForceModeIKFailed                = 21121,  // Trajectory is abnormal,force control mode ik failed 轨迹异常，力控模式下失败
    ErrCodeForceModeTrackJointverspeed      = 21122,  // Trajectory is abnormal,joint overspeed 关节超速

    ErrCodeControllerIKFailed               = 21200,  // The controller has an exception and the inverse kinematics failed 控制器异常，逆解失败
    ErrCodeControllerStatusException        = 21201,  // The controller has an exception and the status is abnormal 控制器异常，状态异常
    ErrCodeControllerTrackingLost           = 21202,  // Exception that joint tracking is lost, 关节跟踪误差过大.
    ErrCodeMonitorErrTrackingLost           = 21203,  // Exception that joint tracking is lost, 关节跟踪误差过大.
    ErrCodeMonitorErrNoArrivalInTime        = 21204,  // not used 预留
    ErrCodeMonitorErrCurrentOverload        = 21205,  // not used 预留
    ErrCodeMonitorErrJointOutOfRange        = 21206,  // Exception that joint out of range  　机械臂关节超出限制范围
    ErrCodeFifoDataTimeNotRead              = 21207,  // 缓存区超时未更新

    ErrCodeMoveEnterStopState               = 21300,  // Movement enters the stop state 运动进入到stop阶段
    ErrCodeMoveInterruptedByEvent           = 21301,  // Movement interrupted by the event 运动被未知事件中断

    /**
     * 来自硬件层返回的异常
     **/
    ErrCodeHardwareErrorNotify              = 22001,  // Robot hardware error 机械臂硬件错误  不能区分是哪种硬件异常才会返回该错误

    ErrCodeJointError                       = 22101,  // Robot joint error 机械臂关节错误
    ErrCodeJointOverCurrent                 = 22102,  // Robot joint over current.  机械臂关节过流
    ErrCodeJointOverVoltage                 = 22103,  // Robot joint over voltage.　 机械臂关节过压
    ErrCodeJointLowVoltage                  = 22104,  // Robot joint low voltage.　  机械臂关节欠压
    ErrCodeJointOverTemperature             = 22105,  // Robot joint over temperature. 机械臂关节过温
    ErrCodeJointHallError                   = 22106,  // Robot joint hall error. 机械臂关节霍尔错误
    ErrCodeJointEncoderError                = 22107,  // Robot joint encoder error. 机械臂关节编码器错误
    ErrCodeJointAbsoluteEncoderError        = 22108,  // Robot joint absolute encoder error. 机械臂关节绝对编码器错误
    ErrCodeJointCurrentDetectError          = 22109,  // Robot joint current position error. 机械臂关节当前位置错误
    ErrCodeJointEncoderPollustion           = 22110,  // Robot joint encoder pollustion.     机械臂关节编码器污染        建议采取措施:警告性通知
    ErrCodeJointEncoderZSignalError         = 22111,  // Robot joint encoder Z signal error. 机械臂关节编码器Z信号错误
    ErrCodeJointEncoderCalibrateInvalid     = 22112,  // Robot joint encoder calibrate　invalid. 机械臂关节编码器校准失效
    ErrCodeJoint_IMU_SensorInvalid          = 22113,  // Robot joint IMU sensor invalid. 机械臂关节IMU传感器失效
    ErrCodeJointTemperatureSensorError      = 22114,  // Robot joint temperature sensor error. 机械臂关节温度传感器出错
    ErrCodeJointCanBusError                 = 22115,  // Robot joint CAN BUS error. 机械臂关节CAN总线出错
    ErrCodeJointCurrentError                = 22116,  // Robot joint current error. 机械臂关节当前电流错误
    ErrCodeJointCurrentPositionError        = 22117,  // Robot joint current position error. 机械臂关节当前位置错误
    ErrCodeJointOverSpeed                   = 22118,  // Robot joint over speed. 机械臂关节超速
    ErrCodeJointOverAccelerate              = 22119,  // Robot joint over accelerate. 机械臂关节加速度过大错误
    ErrCodeJointTraceAccuracy               = 22120,  // Robot joint trace accuracy. 机械臂关节跟踪精度错误
    ErrCodeJointTargetPositionOutOfRange    = 22121,  // Robot joint target position out of range.  机械臂关节目标位置超范围
    ErrCodeJointTargetSpeedOutOfRange       = 22122,  // Robot joint target speed out of range. 机械臂关节目标速度超范围
    ErrCodeJointCollision                   = 22123,  // Robot joint collision. 机械臂碰撞    　　　建议采取措施:暂停当前运动

    ErrCodeDataAbnormal                     = 22200,  // Robot data abnormal 机械臂信息异常
    ErrCodeRobotTypeError                   = 22201,  // Robot type error 机械臂类型错误
    ErrCodeAccelerationSensorError          = 22202,  // Robot acceleration sensor error 机械臂加速度计芯片错误
    ErrCodeEncoderLineError                 = 22203,  // Robot encoder line error  机械臂编码器线数错误
    ErrCodeEnterDragAndTeachModeError       = 22204,  // Robot enter drag and teach mode error 机械臂进入拖动示教模式错误
    ErrCodeExitDragAndTeachModeError        = 22205,  // Robot exit drag and teach mode error 机械臂退出拖动示教模式错误
    ErrCodeMACDataInterruptionError         = 22206,  // Robot MAC data interruption error 机械臂MAC数据中断错误
    ErrCodeDriveVersionError                = 22207,  // Drive version error 驱动器版本错误(关节固件版本不一致)

    ErrCodeInitAbnormal                     = 22300,  // Robot init abnormal  机械臂初始化异常
    ErrCodeDriverEnableFailed               = 22301,  // Robot driver enable failed  机械臂驱动器使能失败
    ErrCodeDriverEnableAutoBackFailed       = 22302,  // Robot driver enable auto back failed  机械臂驱动器使能自动回应失败
    ErrCodeDriverEnableCurrentLoopFailed    = 22303,  // Robot driver enable current loop failed  机械臂驱动器使能电流环失败
    ErrCodeDriverSetTargetCurrentFailed     = 22304,  // Robot driver set target current failed  机械臂驱动器设置目标电流失败
    ErrCodeDriverReleaseBrakeFailed         = 22305,  // Robot driver release brake failed  机械臂释放刹车失败
    ErrCodeDriverEnablePostionLoopFailed    = 22306,  // Robot driver enable postion loop failed  机械臂使能位置环失败
    ErrCodeSetMaxAccelerateFailed           = 22307,  // Robot set max accelerate failed  设置最大加速度失败

    ErrCodeSafetyError                      = 22400,  // Robot Safety error  机械臂安全出错
    ErrCodeExternEmergencyStop              = 22401,  // Robot extern emergency stop  机械臂外部紧急停止
    ErrCodeSystemEmergencyStop              = 22402,  // Robot system emergency stop  机械臂系统紧急停止
    ErrCodeTeachpendantEmergencyStop        = 22403,  // Robot teachpendant emergency stop  机械臂示教器紧急停止
    ErrCodeControlCabinetEmergencyStop      = 22404,  // Robot control cabinet emergency stop  机械臂控制柜紧急停止
    ErrCodeProtectionStopTimeout            = 22405,  // Robot protection stop timeout  机械臂保护停止超时
    ErrCodeEeducedModeTimeout               = 22406,  // Robot reduced mode timeout  机械臂缩减模式超时

    ErrCodeSystemAbnormal                   = 22500,  // Robot systen abnormal  机械臂系统异常
    ErrCode_MCU_CommunicationAbnormal       = 22501,  // Robot mcu communication error  机械臂mcu通信异常
    ErrCode485CommunicationAbnormal         = 22502,  // Robot RS485 communication error  机械臂485通信异常

    ErrCodeSoftEmergency                    = 22550,  // 软急停

    ErrCodeArmPowerOff                      = 22600,  //Disconnecting the contactor causes the arm 48V power off 控制柜接触器断开导致机械臂48V断电

}RobotErrorCode;


enum class MoveModeType : int
{
    NONE = 0,
    MOVE_GROUP,
    SERVOJ,
    FORCE_TEACH,
    TRAJECTORY_ANALYSE,
};

class IdAction
{
public:
    enum IdActionType
    {
        WAIT_COND = 0,
        WAIT_TIME,
        SET,
        MOVE_EVENT,
    };

    int id;
    IdActionType type;
    double wait_time_ms;
    std::string script;
    double move_event_percent;
};

struct FtSensorCalibResult
{
    double error;               // 标定误差
    std::array<double, 6> offset;           // 传感器偏置
    double payload_mass;        // 负载质量
    std::array<double, 3> payload_center;   // 负载重心
};// 末端传感器辨识结果

enum class ConveyerTrackingType
{
    LINE_SENSOR = 0,    // 直线传送带-无视觉
    LINE_VISION,        // 直线传送带-有视觉
};

enum class EncoderType
{
    INTERNAL = 0,    // 接口板直接获取
    EXTERNAL,        // 通过外部编码器板读取
};

struct EncoderParam
{
    EncoderType type;   // 内部读取还是外部读取
    std::string com;    // 串口号（外部读取时才有用）
    int id;             // 编码器 id（预留给外部读取用）
    int resolution;     // 编码器线数
};

enum class CameraType
{
    CAMERA_2D_USERCOORD = 0,    // 2D相机-返回工件坐标系下偏移
    CAMERA_2D_BASECOORD,        // 2D相机-返回机器人基坐标系下偏移
    CAMERA_3D,                  // 3D相机
};

enum class CameraProtocolType
{
    OK_X_Y_RZ_COMMA = 0,    // OK,x,y,rz or NG,x,y,rz
    OK_X_Y_RZ_TIME_ENCODER_COMMA = 1,
};

struct CameraParam
{
    std::string ip;                 // 相机 ip
    int port;                       // 相机 端口
    CameraType type;                // 相机种类
    std::string request_str;        // 请求拍照报文
    CameraProtocolType protocol;    // 相机回传报文协议种类
};

struct ConveyerParam
{
    CoordCalibrateByJointAngleAndTool conveyer_coord;   // 传送带坐标系, X轴为传送带方向
    double conveyer_coord_offset;                       // 传送带坐标系原点与同步开关距离
    int encoder_dir;                                    // 编码器与转送带方向关系，1：两者一致，-1：两者相反
    double encoder_pulse_per_meter;                     // 每米距离对应的脉冲数
    double range_of_start_window[2];                    // 启动窗口上下限（conveyer_coord 下描述）
    double max_distance;                                // 允许跟随的最大距离（conveyer_coord 下描述）
    std::string sync_di_name;                           // 同步开关接入的DI
    double sync_min_dist;                               // 同步开关最小检测距离
};

struct TrackingParam
{
    ConveyerTrackingType type;  // 跟踪类型
    double teach_point_offset;  // 示教点时工件与同步开关距离
    double photo_point_offset;  // 对于 VISION 模式，拍照取模板时工件与同步开关距离
    double rotate_center[2];    // 对于 VISION 模式，示教点处旋转中心在传送带坐标系下的xy
    double extern_offset;       // 传送带方向外部补偿值
    double virtul_sync_sig_dist;// 虚拟同步开关信号距离（在真实同步开关信号之后，virtul_sync_sig_dist 距离后自动添加一个工件到零点）
    int virtual_sync_sig_number;// 虚拟同步开关信号添加的次数s
};

typedef struct PACKED
{
    int32_t encoder_count;  //编码器读数
    int32_t encoder_speed;  //编码器速度  脉冲数/秒
    uint8_t encoder_dir;    //编码器方向 0-反  1-正
}ExternEncoderStatus;

enum class ConveyerTrackingResult : int
{
    NORMAL = 0,
    OUTOFDISTANCE,
};

}
#ifdef __cplusplus
}
#endif



/**
 * @brief             获取实时关节状态回调函数类型.
 * @param jointStatus　当前的关节状态;
 * @param size　　　　　上一个参数（jointStatus）的长度;
 * @param arg　　　　　　使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*RealTimeJointStatusCallback)(const aubo_robot_namespace::JointStatus *jointStatus, int size, void *arg);


/**
 * @brief              获取实时路点信息的回调函数类型.
 * @param wayPoint　   当前的路点信息;
 * @param arg　　　　　　使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*RealTimeRoadPointCallback)  (const aubo_robot_namespace::wayPoint_S  *wayPoint, void *arg);


/**
 *@brief         获取实时末端速度的回调函数类型
 *@param speed   当前的末端速度;
 *@param arg　　　使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*RealTimeEndSpeedCallback)  (double speed, void *arg);


/**
 *@brief         获取实时Movep执行进度的回调函数类型
 *@param num   当前的Movep执行进度;
 *@param arg　　　使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*RealTimeMovepStepNumNotifyCallback)  (int num, void *arg);


/**
 * @brief      获取机械臂事件信息的回调函数类型
 * @param arg  使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*RobotEventCallback)         (const aubo_robot_namespace::RobotEventInfo *eventInfo, void *arg);

/**
 * @brief      日志输出对应的回调函数类型
 * @param logLevel  日志级别;
 * @param str       日志信息;
 */
typedef void (*RobotLogPrintCallback) (aubo_robot_namespace::LOG_LEVEL logLevel, const char *str, void *arg);

/**
 *@brief         获取实时Tcp末端速度的回调函数类型
 *@param speed   当前的Tcp末端速度;
 *@param arg　　　使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*RealTimeTcpEndSpeedCallback)  (double speed, void *arg);

/**
 *@brief         获取轨迹规划结果的回调函数类型
 *@param speed   轨迹规划结果;
 *@param arg　　　使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*PlannerResultCallback)  (std::vector<aubo_robot_namespace::PlannerResult> &plannerResult, void *arg);

/**
 *@brief         获取轨迹评估结果的回调函数类型
 *@param speed   轨迹评估结果;
 *@param arg　　　使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*AnalyseResultCallback)  (std::vector<aubo_robot_namespace::AnalyseResult> &analyseResult, void *arg);


/**
 *@brief         获取nc进程状态的回调函数类型
 *@param status   当前的nc进程状态;
 *@param arg　　　使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*NcStatusCallback)  (aubo_robot_namespace::Nc_Move_Status status, void *arg);

/**
 *@brief         获取nc路点集合的回调函数类型
 *@param NC_PosList   路点集合;
 *@param arg　　　使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*NcGetPointCallback)  (std::list<aubo_robot_namespace::Nc_Points> NC_PosList, void *arg);

/**
 *@brief         获取nc逆解失败的回调函数类型
 *@param      Nc_IkError
 *@param arg　　　使用者在注册回调函数中传递的第二个参数;
 */
typedef void (*NcGetIkErorCallback)  (aubo_robot_namespace::Nc_IkError NcIkError, void *arg);

#endif // AUBOROBOTMETATYPE_H
