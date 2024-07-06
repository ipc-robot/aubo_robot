/**
CopyRight © AUBO Robotics Technology Co.Ltd. All Rights Reserved

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. Neither the name of mosquitto nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/



#ifndef SERVICEINTERFACE_H
#define SERVICEINTERFACE_H

#include <vector>
#include <list>
#include "AuboRobotMetaType.h"        //接口需要用到的数据类型
//#define SIM_ROBOT_MODE
class RobotControlServices;
class RobotMoveService;
class RobotIoService;
class RobotConveyorTrack;
class robotOtherService;
class ForceControl;
class RobotLogPrint;
class HanWeiServices;

class Nc_Move;

class ServiceInterface    /** 对外接口类 : 为用户提供开发接口 **/
{
public:
    typedef struct
    {
        aubo_robot_namespace::wayPoint_S flangeWayPoint;

        aubo_robot_namespace::Pos endPosition;

        aubo_robot_namespace::Ori endOrientation;

    }FlangeAndToolInfo;


    /**
     * @brief 构造函数
     */
    ServiceInterface();
    
    /**
     * @brief 析构函数
     */
    ~ServiceInterface();

public: /** 数据类型初始化*/
    static void initPosDataType(aubo_robot_namespace::Pos &postion);

    static void initOriDataType(aubo_robot_namespace::Ori &ori);

    static void initMoveRelativeDataType(aubo_robot_namespace::MoveRelative &moveRelative);

    static void initWayPointDataType(aubo_robot_namespace::wayPoint_S &wayPoint);

    static void initToolInEndDescDataType(aubo_robot_namespace::ToolInEndDesc &toolInEndDesc);

    static void initCoordCalibrateByJointAngleAndToolDataType(aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &coord);

    static void initToolInertiaDataType(aubo_robot_namespace::ToolInertia &toolInertia);

    static void initToolDynamicsParamDataType(aubo_robot_namespace::ToolDynamicsParam &toolDynamicsParam);


    /**********************************************************************************************************************************************
     ***********　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　机械臂系统接口　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　**********
     **********************************************************************************************************************************************/

public:

    /**
     * @brief 登录　　与机械臂服务器建立网络连接；
     *        该接口的成功是调用其他接口的前提。
     *
     * @param host     机械臂服务器的IP地址
     * @param port     机械臂服务器的端口号
     * @param userName 用户名  默认为Aubo
     * @param possword 密码 　 默认为123456
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceLogin(const char* host, int port, const char *userName, const char* password);

    int  robotServiceLogin(const char* host,
                           int port,
                           const char *userName,
                           const char* password,
                           aubo_robot_namespace::RobotType &robotType,
                           aubo_robot_namespace::RobotDhPara &robotDhPara);

    /**
     * @brief robotServiceGetConnectStatus   获取当前的连接状态
     * @param connectStatus　　　　　　　　　　　输出参数
     */
    void robotServiceGetConnectStatus(bool &connectStatus);


    /**
     * @brief 退出登录
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceLogout();

    int  robotServiceRobotHandShake(bool isBlock);


    /**********************************************************************************************************************************************
     *****　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　状态推送　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*******
     **********************************************************************************************************************************************/
public:

    /**
     * @brief robotServiceSetRealTimeJointStatusPush   设置是否允许实时关节状态推送
     * @param enable   true表示允许　　　false表示不允许
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetRealTimeJointStatusPush(bool enable);


    /**
     * @brief robotServiceRegisterRealTimeJointStatusCallback   注册用于获取关节状态的回调函数
     *        注册回调函数后,服务器实时推送当前的关节状态信息.
     * @param ptr   获取实时关节状态信息的函数指针，当ptr==NULL时，相当于取消回调函数的注册,取消该推送信息也可以通过该接口robotServiceSetRealTimeJointStatusPush进行。
     * @param arg   这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterRealTimeJointStatusCallback(RealTimeJointStatusCallback ptr, void  *arg);



    /**
     * @brief robotServiceSetRealTimeRoadPointPush   设置是否允许实时路点信息推送
     * @param enable　　true表示允许　　　false表示不允许
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetRealTimeRoadPointPush(bool enable);

    /**
     * @brief robotServiceRegisterRealTimeRoadPointCallback   注册用于获取实时路点的回调函数
     *        注册回调函数后,服务器会推送当前的路点信息　当ptr==NULL时，相等于取消回调函数的注册。
     * @param ptr  获取实时路点信息的函数指针，当ptr==NULL时，相当于取消回调函数的注册,取消该推送信息也可以通过该接口robotServiceSetRealTimeRoadPointPush进行。
     * @param arg　这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterRealTimeRoadPointCallback(const RealTimeRoadPointCallback ptr, void  *arg);


    /**
     * @brief robotServiceSetRealTimeEndSpeedPush   设置是否允许实时末端速度推送
     * @param enable   true表示允许　　　false表示不允许
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetRealTimeEndSpeedPush(bool enable);

    /**
     * @brief robotServiceRegisterRealTimeEndSpeedCallback   注册用于获取实时末端速度的回调函数
     * @param ptr  获取实时末端速度的函数指针　当ptr==NULL时，相等于取消回调函数的注册，取消该推送信息也可以通过该接口robotServiceSetRealTimeEndSpeedPush进行。
     * @param arg　这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterRealTimeEndSpeedCallback(const RealTimeEndSpeedCallback ptr, void  *arg);


    /**
     * @brief robotServiceRegisterRobotEventInfoCallback  注册用于获取机械臂事件信息的回调函数
     *              注:关于事件信息信息的推送没有提供是否允许推送的接口，因为机械臂的很多重要通知都是通过事件推送实现的,所以事件信息是系统默认推送的,不允许取消的。
     * @param ptr   获取机械臂事件信息的函数指针　当ptr==NULL时，相等于取消回调函数的注册。
     * @param arg　　这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterRobotEventInfoCallback(RobotEventCallback ptr, void  *arg);

    //注册movep进度通知的回调函数
    int  robotServiceRegisterMovepStepNumNotifyCallback(RealTimeMovepStepNumNotifyCallback ptr, void  *arg);

    //注册日志输出回调函数
    int  robotServiceRegisterLogPrintCallback(RobotLogPrintCallback ptr, void  *arg);

    /**
     * @brief robotServiceSetRealTimeTcpEndSpeedPush   设置是否允许实时Tcp末端速度推送
     * @param enable   true表示允许　　　false表示不允许
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetRealTimeTcpEndSpeedPush(bool enable);

    /**
     * @brief robotServiceRegisterRealTimeTcpEndSpeedCallback   注册用于获取实时Tcp末端速度的回调函数
     * @param ptr  获取实时末端速度的函数指针　当ptr==NULL时，相等于取消回调函数的注册，取消该推送信息也可以通过该接口 robotServiceSetRealTimeTcpEndSpeedPush 进行。
     * @param arg　这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterRealTimeTcpEndSpeedCallback(const aubo_robot_namespace::ToolKinematicsParam &toolKinematicsParam, const RealTimeTcpEndSpeedCallback ptr, void  *arg);

    /**
     * @brief robotServiceSetPlannerResultPush   设置是否允许轨迹规划结果推送
     * @param enable   true表示允许　　　false表示不允许
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetPlannerResultPush(bool enable);

    /**
     * @brief robotServiceRegisterPlannerResultCallback   注册用于获取轨迹规划结果的回调函数
     * @param ptr  获取轨迹规划结果的函数指针　当ptr==NULL时，相等于取消回调函数的注册。
     * @param arg　这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterPlannerResultCallback(const PlannerResultCallback ptr, void  *arg);

    /**
     * @brief robotServiceSetAnalyseResultPush   设置是否允许轨迹评估结果推送
     * @param enable   true表示允许　　　false表示不允许
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetAnalyseResultPush(bool enable);

    /**
     * @brief robotServiceRegisterAnalyseResultCallback   注册用于获取轨迹评估结果的回调函数
     * @param ptr  获取轨迹规划结果的函数指针　当ptr==NULL时，相等于取消回调函数的注册。
     * @param arg　这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterAnalyseResultCallback(const AnalyseResultCallback ptr, void  *arg);

    /**
     * @brief robotServiceRegisterNcStatusCallback   注册用于获取nc进程状态的回调函数
     * @param ptr  获取nc进程状态的函数指针　当ptr==NULL时，相等于取消回调函数的注册。
     * @param arg　这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterNcStatusCallback(const NcStatusCallback ptr, void  *arg);

    /**
     * @brief robotServiceRegisterNcGetPointCallback   注册用于获取nc_point的回调函数
     * @param ptr  获取nc_point的函数指针　当ptr==NULL时，相等于取消回调函数的注册。
     * @param arg　这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterNcGetPointCallback(const NcGetPointCallback ptr, void  *arg);

    /**
     * @brief robotServiceRegisterNcGetIkErorCallback   注册用于获取nc_point的回调函数
     * @param ptr  获取NcGetIkEror的函数指针　当ptr==NULL时，相等于取消回调函数的注册。
     * @param arg　这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterNcGetIkErorCallback(const NcGetIkErorCallback ptr, void  *arg);

private:
    /**
     * @brief 接受服务器推送的实时关节状态 并进行处理  (SDK内部使用,开发者不需要关心)
     * @param jointStatus   机械臂关节状态,输入参数
     * @param size          jointStatus数组的长度   长度为6,因为有6个关节
     */
    static void  recvRealTimeJointStatusPushCallback(const aubo_robot_namespace::JointStatus *jointStatus, int size, void *arg);

    static void  recvRealTimeWaypointPushCallback(const aubo_robot_namespace::wayPoint_S *waypoint,void *arg);

    /**
     * @brief 接受服务器推送的实时末端速度 并进行处理  (SDK内部使用,开发者不需要关心)
     * @param speed
     */
    static void  recvRealTimeEndSpeedPushCallback(double speed, void *arg);


    /**
     * @brief 接收服务器推送的事件并进行处理  (SDK内部使用,开发者不需要关心)
     * @param eventInfo  事件信息  输入参数
     */
    static void  recvRobotEventPushCallback(const aubo_robot_namespace::RobotEventInfo *info, void *arg);

    /**
     * @brief 接收服务器推送Movep执行进度  (SDK内部使用,开发者不需要关心)
     * @param
     */
    static void  recvMovepProgressNotifyCallback(int num, void *arg);

    /**
     * @brief 接受服务器推送的实时Tcp末端速度 并进行处理  (SDK内部使用,开发者不需要关心)
     * @param speed
     */
    static void  recvRealTimeTcpEndSpeedPushCallback(double speed, void *arg);

    /**
     * @brief 接受服务器推送的轨迹规划结果 并进行处理  (SDK内部使用,开发者不需要关心)
     * @param speed
     */
    static void  recvPlannerResultPushCallback(std::vector<aubo_robot_namespace::PlannerResult> &plannerResults, void *arg);

    /**
     * @brief 接受服务器推送的轨迹评估结果 并进行处理  (SDK内部使用,开发者不需要关心)
     * @param speed
     */
    static void  recvAnalyseResultPushCallback(std::vector<aubo_robot_namespace::AnalyseResult> &analyseResults, void *arg);
    /**
     * @brief 接受nc推送的NC_STATUS结果 并进行处理  (SDK内部使用,开发者不需要关心)[目前暂时为nc直接推送，不经过服务器]
     * @param speed
     */
    static void  recvNcStatusPushCallback(aubo_robot_namespace::Nc_Move_Status NcStatus, void *arg);
    /**
     * @brief 接受nc推送的NC_point结果 并进行处理  (SDK内部使用,开发者不需要关心)[目前暂时为nc直接推送，不经过服务器]
     * @param speed
     */
    static void  recvNcGetPointCallback(std::list<aubo_robot_namespace::Nc_Points> point_list, void *arg);
    /**
     * @brief 接受nc推送的NC_IkError结果 并进行处理  (SDK内部使用,开发者不需要关心)[目前暂时为nc直接推送，不经过服务器]
     * @param speed
     */
    static void  recvNcGetIkErrorCallback(aubo_robot_namespace::Nc_IkError IkError, void *arg);



    /*******************************************************************机械臂运动接口相关的接口*************************************************************
     * 运动属性包含:
     *          0:关节型运动的最大速度和加速度;  (当运动类型为关节型运动时有效)
     *          1:末端型运动的最大速度和加速度;  (当运动类型为末端型运动时有效)
     *          2:路点信息缓存(轨迹运动使用);
     *          3:交融半径(轨迹运动子类型MOVEP使用);
     *          4:圆的圈数(当轨迹类型为ARC_CIR时有效，当圆的圈数属性（CircularLoopTimes）为０时，表示圆弧轨迹;当圆的圈数属性（CircularLoopTimes）大于０时，表示圆轨迹。)
     *          5:偏移量属性　　(除示教运动外的所有运动有效)
     *          6:工具参数属性
     *          7:设置示教坐标系(仅适用于示教运动)
     *
     *
     * 本机械臂接口支持下面几种运动，3大类:
     *          1:关节运动    对应接口函数为 robotServiceJointMove();
     *          2:直线运动    对应接口函数为 robotServiceLineMove();
     *          3:轨迹运动    其中轨迹运动又可以分为 ARC_CIR, CARTESIAN_MOVEP, CARTESIAN_CUBICSPLINE,CARTESIAN_UBSPLINEINTP,JIONT_CUBICSPLINE,JOINT_UBSPLINEINTP;
     *                       对应接口函数为 robotServiceTrackMove();
     *根据上面的运动扩展接口:
     *          1:
     *
     *
     **************************************************************************************************************************************************/

public:

    /**
     * @brief robotServiceInitGlobalMoveProfile   初始化全局的运动属性
     *        调用此函数时机械臂不运动，该函数初始化各个运动属性为默认值。
     * 　　　　初始化后各属性的默认值为:
     *              0:关节型运动的最大速度和加速度属性:　关节最大速度默认为25度米每秒；关节最大加速度默认为25度米每秒方
     *              1:末端型运动的最大速度和加速度属性:  末端最大速度默认为３米每秒;末端最大加速度３米每秒方
     *              2:路点信息缓存属性:　　默认路点缓存为空
     *              3:交融半径属性:       默认为0.02米
     *              4:圆的圈数属性:       默认为0
     *              5:偏移量属性属性:     默认没有偏移
     *              6:工具参数属性属性:   无工具即工具的位置为０００;
     *              7:示教坐标系属性:　   示教坐标系为基座标系
     *
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceInitGlobalMoveProfile();


    /**
     * 设置和获取　关节型　运动的最大速度和加速度
     * 关节型运动包含：
     * 　　　　关节运动；
     * 　　　　示教运动中的关节示教（JOINT1，JOINT2，JOINT3，JOINT4，JOINT5，JOINT6）
     * 　　　　轨迹运动下的（JIONT_CUBICSPLINE，JOINT_UBSPLINEINTP）
     *
     * 注意：用户在设置速度和加速度时，需要根据运动的类型设置，
     * 　　　关节型运动设置关节型运动的最大速度和加速度,关节型运动的最大速度是180度每秒，最大加速度为180度每秒方;
     * 　　　末端型运动会设置末端型运动的最大速度和加速度，末端型运动的最大速度为2米每秒，最大加速度为2米每秒方;
     *
     **/
    int   robotServiceSetGlobalMoveJointMaxAcc (const aubo_robot_namespace::JointVelcAccParam  &moveMaxAcc);

    int   robotServiceSetGlobalMoveJointMaxVelc(const aubo_robot_namespace::JointVelcAccParam  &moveMaxVelc);

    void  robotServiceGetGlobalMoveJointMaxAcc (aubo_robot_namespace::JointVelcAccParam        &moveMaxAcc);

    void  robotServiceGetGlobalMoveJointMaxVelc(aubo_robot_namespace::JointVelcAccParam        &moveMaxVelc);


    /**
     * 设置和获取　末端型　运动的最大速度和加速度
     * 末端型包含：　直线运动（MODEL）；
     * 　　　　示教运动中的位置示教和姿态示教（MOV_X，MOV_Y，MOV_Z，ROT_X，ROT_Y，ROT_Z）；
     * 　　　　轨迹运动下的（ARC_CIR,　CARTESIAN_MOVEP,　CARTESIAN_CUBICSPLINE,　CARTESIAN_UBSPLINEINTP）
     *
     * 注意：用户在设置速度和加速度时，需要根据运动的类型设置，
     *      关节型运动设置关节型运动的最大速度和加速度,关节型运动的最大速度是180度每秒，最大加速度为180度每秒方;
     * 　　　末端型运动会设置末端型运动的最大速度和加速度，末端型运动的最大速度为2米每秒，最大加速度为2米每秒方;
     *
     **/
    int   robotServiceSetGlobalMoveEndMaxLineAcc (double  moveMaxAcc);

    int   robotServiceSetGlobalMoveEndMaxLineVelc(double  moveMaxVelc);

    void  robotServiceGetGlobalMoveEndMaxLineAcc (double  &moveMaxAcc);

    void  robotServiceGetGlobalMoveEndMaxLineVelc(double  &moveMaxVelc);

    int   robotServiceSetGlobalMoveEndMaxAngleAcc (double  moveMaxAcc);

    int   robotServiceSetGlobalMoveEndMaxAngleVelc(double  moveMaxVelc);

    void  robotServiceGetGlobalMoveEndMaxAngleAcc (double  &moveMaxAcc);

    void  robotServiceGetGlobalMoveEndMaxAngleVelc(double  &moveMaxVelc);

    /**
      *　设置加加速度
      */
    int   robotServiceSetJerkAccRatio(double acc);

    void  robotServiceGetJerkAccRatio(double  &acc);

    int   robotServiceSetAngleJerkAccRatio(double acc);

    void  robotServiceGetAngleJerkAccRatio(double  &acc);

    int robotServiceSetCommonJerkRatio(double ratio);
    int robotServiceResetCommonJerkRatio();

    /** 运动属性中的路点设置与获取　多用于轨迹运动**/
    void  robotServiceClearGlobalWayPointVector();

    /**
     * @brief robotServiceAddGlobalWayPoint  添加路点，一般用于robotServiceTrackMove中
     * @param wayPoint　　法兰盘中心基于基座标系的路点信息
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int   robotServiceAddGlobalWayPoint(const aubo_robot_namespace::wayPoint_S &wayPoint);

    /**
     * @brief robotServiceAddGlobalWayPoint  添加路点，一般用于robotServiceTrackMove中
     * @param jointAngle　　　  关节信息
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     **/

    int   robotServiceAddGlobalWayPoint(const double jointAngle[aubo_robot_namespace::ARM_DOF]);

    void  robotServiceGetGlobalWayPointVector(std::vector<aubo_robot_namespace::wayPoint_S> &wayPointVector);


    /** 运动属性之交融半径的设置与获取　交融半径的方位：0.0m~0.05m  注意：交融半径必须大于0.0**/
    float robotServiceGetGlobalBlendRadius();

    int   robotServiceSetGlobalBlendRadius(float value);


    double  robotServiceGetTrackPlaybackCycle();

    int robotServiceSetTrackPlaybackCycle(double second);


    /** 运动属性之圆轨迹时圆的圈数
     * 当轨迹类型为ARC_CIR时有效，当圆的圈数属性（CircularLoopTimes）为０时，表示圆弧轨迹;
     *                        当圆的圈数属性（CircularLoopTimes）大于０时，表示圆轨迹。
     **/
    int   robotServiceGetGlobalCircularLoopTimes();

    void  robotServiceSetGlobalCircularLoopTimes(int times);


    /**
     * @brief robotServiceSetMoveRelativeParam   设置运动属性中的偏移属性
     * @param relativeMove      基于基座标系的偏移
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceSetMoveRelativeParam(const aubo_robot_namespace::MoveRelative &relativeMoveOnBase);              //基于基座标系

    /**
     * @brief robotServiceSetMoveRelativeParam   设置运动属性中的偏移属性
     * @param relativeMoveOnUserCoord      基于用户坐标系(下面参数userCoord)下的偏移
     * @param userCoord        用户坐标系
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceSetMoveRelativeParam(const aubo_robot_namespace::MoveRelative   &relativeMoveOnUserCoord,
                                          const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoord);  //基于自定义坐标系


    /** 跟随模式之提前到位　当前仅适用于关节运动**/
    int  robotServiceSetNoArrivalAhead();

    int  robotServiceSetArrivalAheadDistanceMode(double distance /*米*/);

    int  robotServiceSetArrivalAheadTimeMode(double second /*秒*/);

    int  robotServiceSetArrivalAheadBlendDistanceMode(double distance /*米*/);


    /**
     * @brief robotServiceSetTeachCoordinateSystem   设置示教运动的坐标系
     * @param coordSystem　　　用户坐标系    通过该参数确定一个坐标系,具体使用参考类型定义处的使用说明
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetTeachCoordinateSystem(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &coordSystem);


    /**
     * @brief robotServiceJointMove   运动接口之关节运动
     *        属于关节型运动,调用该函数机械臂开始运动
     * @param wayPoint　　目标路点信息
     * @param IsBolck    IsBolck==true  代表阻塞，机械臂运动直到到达目标位置或者出现故障后返回。
     *                   IsBolck==false 代表非阻塞，立即返回，运动指令发送成功就返回，函数返回后机械臂开始运动。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceJointMove(aubo_robot_namespace::wayPoint_S   &wayPoint,     bool IsBolck);

    int robotServiceJointMove(double jointAngle[aubo_robot_namespace::ARM_DOF], bool IsBolck);

    int robotServiceJointMove(aubo_robot_namespace::MoveProfile_t  &moveProfile, double jointAngle[aubo_robot_namespace::ARM_DOF], bool IsBolck);

    //基于跟随模式的轴动接口
    int robotServiceFollowModeJointMove(double jointAngle[aubo_robot_namespace::ARM_DOF]);

    /**
     * @brief robotServiceLineMove    运动接口之直线运动
     *        属于末端型运动,调用该函数机械臂开始运动
     * @param wayPoint　　　目标路点信息
     * @param IsBolck      参考robotServiceJointMove函数的解释
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceLineMove(aubo_robot_namespace::wayPoint_S   &wayPoint,      bool IsBolck);

    int robotServiceLineMove(double jointAngle[aubo_robot_namespace::ARM_DOF],  bool IsBolck);

    int robotServiceLineMove(aubo_robot_namespace::MoveProfile_t  &moveProfile, double jointAngle[aubo_robot_namespace::ARM_DOF],  bool IsBolck);

    /**
     * @brief robotServiceRotateMove   运动接口之保持当前位置变换姿态做旋转运动
     * @param rotateAxis    转轴[x,y,z]    当绕Ｘ转，[１，０，０]
     * @param rotateAngle　 转角
     * @param IsBolck      是否阻塞
     * @return
     */
    int robotServiceRotateMove(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoord, const double rotateAxisOnUserCoord[3], double rotateAngle,  bool IsBolck);
    /** 旋转运动到目标路点 **/
    int robotServiceRotateMoveToWaypoint(const aubo_robot_namespace::wayPoint_S &targetWayPointOnBaseCoord,bool IsBolck);

    /**
     * @brief robotServiceGetRotateTargetWaypiont  根据当前位姿及基坐标系下表示的旋转轴、旋转角，获取目标位姿
     * @param originateWayPointOnBaseCoord 起始路点信息
     * @param rotateAxisOnBaseCoord 基坐标系下表示的旋转轴
     * @param rotateAngle 旋转角
     * @param targetWayPointOnBaseCoord 目标路点信息 （传出参数）
     * @return
     */
    int robotServiceGetRotateTargetWaypiont(const aubo_robot_namespace::wayPoint_S &originateWayPointOnBaseCoord,const double rotateAxisOnBaseCoord[], double rotateAngle,aubo_robot_namespace::wayPoint_S &targetWayPointOnBaseCoord);

    /**
     * @brief robotServiceGetRotateAxisUserToBase 将用户坐标系描述的旋转轴变换到基坐标系下描述
     * @param oriOnUserCoord 用户坐标系姿态
     * @param rotateAxisOnUserCoord 用户坐标系下描述的旋转轴
     * @param rotateAxisOnBaseCoord 基坐标系下描述的旋转轴（传出参数）
     * @return
     */
    int robotServiceGetRotateAxisUserToBase(const aubo_robot_namespace::Ori &oriOnUserCoord,const double rotateAxisOnUserCoord[], double rotateAxisOnBaseCoord[]);

    /**
     * @brief robotServiceTrackMove   运动接口之轨迹运动
     *
     * @param subMoveMode   当subMoveMode==ARC_CIR,　CARTESIAN_MOVEP,　CARTESIAN_CUBICSPLINE,　CARTESIAN_UBSPLINEINTP时，该运动属于末端型运动；
     *                      当subMoveMode==JIONT_CUBICSPLINE，JOINT_UBSPLINEINTP时，该运动属于关节型运动；
     *
     *                      当subMoveMode==ARC_CIR　表示圆或者圆弧　　　　当圆的圈数属性（CircularLoopTimes）为０时，表示圆弧轨迹，
     * 　　　　　　　　　　　　　　　　　　　　　　　　　　　　                当圆的圈数属性（CircularLoopTimes）大于０时，表示圆轨迹。
     *
     *                      当subMoveMode==CARTESIAN_MOVEP 　　　　　表示MOVEP轨迹，需要用户这只交融半径的属性。
     *
     *                      当subMoveMode==JOINT_UBSPLINEINTP　　　 轨迹复现接口
     *
     * @param IsBolck　　　　参考robotServiceJointMove函数的解释
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceTrackMove(aubo_robot_namespace::move_track subMoveMode, bool IsBolck);



    /**
     * @brief robotMoveLineToTargetPosition     保持当前位姿通过直线运动的方式运动到目标位置,其中目标位置是通过相对当前位置的偏移给出
     * @param userCoord                         用户坐标系　该坐标系参数（userCoord）,表示下面的偏移量参数(relativeMoveOnUserCoord)是基于该平面的。
     * @param toolInEndDesc                     工具参数　　　当没有使用工具时，将此参数设置为０；
     * @param relativeMoveOnUserCoord           基于用户坐标系下的偏移
     * @param IsBolck　　　　　　　　　　　　　　　　是否阻塞　　　参考robotServiceJointMove函数的解释
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotMoveLineToTargetPositionByRelative(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoord,
                                      const aubo_robot_namespace::MoveRelative    &relativeMoveOnUserCoord,      //目标位置相对当前位置的偏移
                                      bool IsBolck);                                                  //是否阻塞


    /** 保持当前位姿通过关节运动的方式运动到目标位置   参数描述参考robotMoveLineToTargetPosition **/
    int robotMoveJointToTargetPositionByRelative(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoord,
                                       const aubo_robot_namespace::MoveRelative    &relativeMoveOnUserCoord,      //目标位置相对当前位置的偏移
                                       bool IsBolck = false);                                          //是否阻塞


    /**
     * @brief robotMoveLineToTargetPosition   保持当前位姿通过直线运动的方式运动到目标位置。
     * @param userCoord                       用户坐标系　该坐标系参数（userCoord）,表示下面的目标位置(positionOnUserCoord)是基于该平面的。
     * @param positionOnUserCoord             基于用户平面表示的目标位置
     * @param toolInEndDesc                   工具参数　　　当没有使用工具时，将此参数设置为０;
     * @param IsBolck　　　　　　　　　　　　　　　是否阻塞　　　参考robotServiceJointMove函数的解释
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    //不进行运动
    int getJointAngleByTargetPositionKeepCurrentOri(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &coordSystem,
                                                    const aubo_robot_namespace::Pos &toolEndPositionOnUserCoord,
                                                    const aubo_robot_namespace::ToolInEndDesc   &toolInEndDesc,     //相对于用户坐标系的目标位置
                                                    double jointAngle[aubo_robot_namespace::ARM_DOF]);


    int robotMoveLineToTargetPosition(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool  &userCoord,
                                      const aubo_robot_namespace::Pos             &toolEndPositionOnUserCoord,
                                      const aubo_robot_namespace::ToolInEndDesc   &toolInEndDesc,     //相对于用户坐标系的目标位置
                                      bool IsBolck = false);                                          //是否阻塞


    /** 保持当前位姿通过关节运动的方式运动到目标位置   参数描述参考robotMoveLineToTargetPosition **/
    int robotMoveJointToTargetPosition(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool     &userCoord,
                                       const aubo_robot_namespace::Pos             &toolEndPositionOnUserCoord,
                                       const aubo_robot_namespace::ToolInEndDesc   &toolInEndDesc,    //相对于用户坐标系的目标位置
                                       bool  IsBolck = false);                                        //是否阻塞


    /**
     * @brief 开始示教
     * @param mode        示教关节:JOINT1,JOINT2,JOINT3, JOINT4,JOINT5,JOINT6,   位置示教:MOV_X,MOV_Y,MOV_Z   姿态示教:ROT_X,ROT_Y,ROT_Z
     * @param direction   运动方向   正方向true  反方向false
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceTeachStart(aubo_robot_namespace::teach_mode mode, bool direction);
    int robotServiceSpeedMove(int mode,const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoord, const double direction[]);

    /**
      * @brief 获取机械臂运动轨迹（目前支持轴动及笛卡尔直线运动）
      * @param mode       运动类型： 0为轴动，1为笛卡尔直线运动
      * @param  cycle         轨迹点的更新步长，单位:秒
      * @param joint_start   起始点六个关节弧度值
      * @param joint_end   终点六个关节弧度值
      * @param wayPoint_Vector   两点之间轨迹路点的六个关节角度值
      * @return　调用成功返回ErrnoSucc;错误返回错误号
      */
    int robotServiceGetTrack(int mode, double cycle, const double joint_start[], const double joint_end[], std::vector<aubo_robot_namespace::wayPoint_S> &wayPoint_Vector);

    /** @brief  结束Speedl示教 */
    int robotServiceSpeedlTeachStop();
    /** @brief  结束示教 */
    int robotServiceTeachStop();


    /**
     * @brief 机械臂运动控制   停止,暂停,继续
     * @param cmd    控制命令
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  rootServiceRobotMoveControl(aubo_robot_namespace::RobotMoveControlCommand cmd);

    int  robotMoveFastStop();

    int  robotMoveStop();

    // 等待非阻塞运动到位或结束
    int  robotWaitMotionFinish(int timeout_ms = 0);

    /**
     * @brief robotSetReducePara
     * @param jerkRatio    [0.1,20]
     * @param acc          6维数组，
     *                     1，末端型运动，只使用acc[0] 最大加速度
     *                     2，轴动，使用acc[0,5] 关节最大加速度
     * @param size
     * @return 0 成功，其他失败
     */
    int  robotSetReducePara(const double jerkRatio, const double acc[], int size);



    /** 离线轨迹 **/
    int robotServiceOfflineTrackWaypointAppend(const std::vector<aubo_robot_namespace::wayPoint_S> &wayPointVector);

    int robotServiceOfflineTrackWaypointAppend(const char *fileName);

    int robotServiceOfflineTrackWaypointClear ();

    int robotServiceOfflineTrackMoveStartup   (bool  IsBolck);

    int robotServiceOfflineTrackMoveStop      ();


    /** tcp转can透传　**/
    int  robotServiceEnterTcp2CanbusMode();

    int  robotServiceLeaveTcp2CanbusMode();

    int  robotServiceSetRobotPosData2Canbus(double jointAngle[aubo_robot_namespace::ARM_DOF]);

    int  robotServiceSetRobotPosData2Canbus(const std::vector<aubo_robot_namespace::wayPoint_S> &wayPointVector);


    int  startupOfflineExcitTrajService(const char *trackFile, aubo_robot_namespace::Robot_Dyn_identify_traj type, int subtype, bool isBolck);

    int  getDynIdentifyResultsService(std::vector<int> &paramVector);

    int startServoj();

    int stopServoj();

    int servoj(const double q[6], double duration, double smooth_scale, double delay_sacle, bool is_last_point = false);

    int startMoveGroup(aubo_robot_namespace::MoveModeType type = aubo_robot_namespace::MoveModeType::MOVE_GROUP,
                       bool conveyer = false,
                       int conveyer_index = 0);

    int addIdActionToMoveGroup(const aubo_robot_namespace::IdAction &action);

    int setEndOfMoveGroup();

    int waitMoveGroupFinished();

    int setVelForTrajectoryAnalyse(double vel, double interval);

    int fcSensorOn();
    int fcSensorOff();
    int fcGetSensorData(std::vector<double> &data);
    int fcGetTCPwrenchData(std::vector<double> &data);
    int fcSensorCalibration(const std::vector<std::array<double, aubo_robot_namespace::ARM_DOF> > &joints,
                            const std::vector<aubo_robot_namespace::ForceSensorData> &force_datas,
                            aubo_robot_namespace::FtSensorCalibResult &result);

    int ctSetEncoderParam(const aubo_robot_namespace::EncoderParam &param, int index = 0);
    int ctInitConveyer(int index = 0);
    int ctEnableSimConveyer(bool sim, int index = 0);
    int ctStartConveyer(double vel, int index = 0);
    int ctStopConveyer(int index = 0);
    int ctResetEncoder(int index = 0);
    int ctGetEncoderData(aubo_robot_namespace::ExternEncoderStatus &encoder_data, int index = 0);
    int ctSetConveyerParam(const aubo_robot_namespace::ConveyerParam &param, int index = 0);
    int ctSetTrackingParam(const aubo_robot_namespace::TrackingParam &param, int index = 0);
    int ctSetCameraParam(const aubo_robot_namespace::CameraParam &param, int index = 0);
    int ctAppendWorkpiece(double x = 0, double y = 0, double rz = 0, int index = 0);
    int ctGetAllWorkpiece(std::vector<std::vector<double> > &workpieces, int index = 0);
    int ctGetTrackingResult(aubo_robot_namespace::ConveyerTrackingResult &result, int index = 0);

    /*******************************************************************工具接口*************************************************************
     * 工具接口：正解接口,
     *         逆解接口,
     *         工具标定接口
     *         坐标系标定接口
     * 　　　　　基座标系转用户坐标系接口
     * 　　　　　用户坐标系转基坐标系接口
     *
     **************************************************************************************************************************************************/

public:
    /**
     * @brief 正解　　　　　此函数为正解函数，已知关节角求对应位置的位置和姿态。
     * @param jointAngle  六个关节的关节角  　　　输入参数   单位:弧度(rad)
     * @param size        关节角数组长度   规定为6个
     * @param wayPoint    正解结果    　　　输出参数
     * 　　　结果示例: 六个关节角 {'joint': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
     *              位置 'pos': [-0.06403157614989634, -0.4185973810159096, 0.816883228463401],
     *              姿态 'ori': [-0.11863209307193756, 0.3820514380931854, 0.0, 0.9164950251579285]}
     *
     * @return　调用成功返回ErrnoSucc;错误返回错误号  调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceRobotFk(const double *jointAngle, int size, aubo_robot_namespace::wayPoint_S &wayPoint);


    /**
     * @brief 逆解　　　　　此函数为机械臂逆解函数，根据位置信息(x,y,z)和对应位置的参考姿态(w,x,y,z)得到对应位置的关节角信息。
     *      机器人运动学方程的逆解，也称机器人的逆运动学问题。
     *      逆运动学问题：对某个机器人，当给出机器人手部（法兰盘中心）在基座标系中所处的位置和姿态时，求出其对应的关节角信息。
     * @param position   目标路点的位置   　　　单位:米   输入参数
     * @param ori        目标路点的参考姿态            　输入参数　　　　例如：可以获取当前位置位姿作为此参数，这样相当于保持当前姿态
     * @param wayPoint   计算结果----目标路点信息
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceRobotIk(const double *startPointJointAngle,const aubo_robot_namespace::Pos &position, const aubo_robot_namespace::Ori &ori, aubo_robot_namespace::wayPoint_S &wayPoint);

    int robotServiceRobotIk(const aubo_robot_namespace::Pos &position, const aubo_robot_namespace::Ori &ori, std::vector<aubo_robot_namespace::wayPoint_S> &wayPointVector);


    //工具标定
    int robotServiceToolCalibration(const std::vector<aubo_robot_namespace::wayPoint_S> &wayPointPosVector,  char poseCalibMethod,
                                    aubo_robot_namespace::ToolInEndDesc &toolInEndDesc);

    /**
     * @brief toolCalibration         　工具标定　　该函数能标定出工具的位置信息和姿态信息
     * @param wayPointPosCalibVector　　提供４个或４个以上的点用于位置标定
     * @param wayPointOriCalibVector　　提供两个点用于姿态标定
     * @param poseCalibMethod　　　　　　标定方法
     * @param toolInEndDesc　　　　　　　标定的结果
     * @return
     */
    int robotServiceToolCalibration(const std::vector<aubo_robot_namespace::wayPoint_S> &wayPointPosCalibVector,
                                    const std::vector<aubo_robot_namespace::wayPoint_S> &wayPointOriCalibVector,
                                    aubo_robot_namespace::ToolKinematicsOriCalibrateMathod poseCalibMethod,
                                    aubo_robot_namespace::ToolInEndDesc &toolInEndDesc);

    /**
     * @brief robotServiceCheckUserCoordinate    检查提供的参数是否标定出一个坐标系
     * @param coordSystem　　　　坐标系提供的参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceCheckUserCoordinate(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool  &coordSystem);

    int robotServiceUserCoordinateCalibration(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool  &coordSystem, double bInWPos[3], double bInWOri[9], double wInBPos[3]);

    int robotServiceOriMatrixToQuaternion(double eerot[], aubo_robot_namespace::Ori &result);



    /**
     * @brief baseToUserCoordinate                基座标系转用户坐标系
     *
     *        概述:  将法兰盘中心基于基座标系下的位置和姿态　转成　工具末端基于用户座标系下的位置和姿态。
     *
     *      　扩展1:  法兰盘中心可以看成是一个特殊的工具，即工具的位置为(0,0,0)姿态为（1,0,0,0）
     * 　　　　　　　  因此当工具为(0,0,0)时，相当于将法兰盘中心基于基座标系下的位置和姿态　转成　法兰盘中心基于用户座标系下的位置和姿态。
     *
     * 　　　　扩展2:  用户坐标系也可以选择成基座标系，　　即：userCoord.coordType = BaseCoordinate
     *               因此当用户平面为基座标系时，相当于将法兰盘中心基于基座标系下的位置和姿态　转成　工具末端基于基座标系下的位置和姿态，
     *               即在基座标系加工具。
     *
     * @param flangeCenterPositionOnBase          基于基座标系的法兰盘中心位置信息（x,y,z）  单位(m)
     * @param flangeCenterOrientationOnBase       基于基座标系的姿态信息(w, x, y, z)
     * @param userCoord                           用户坐标系    通过该参数确定一个坐标系
     * @param toolInEndDesc                       工具信息
     * @param toolEndPositionOnUserCoord          基于用户座标系的工具末端位置信息    输出参数
     * @param toolEndOrientationOnUserCoord       基于用户座标系的工具末端姿态信息    输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    static int baseToUserCoordinate( const aubo_robot_namespace::Pos            &flangeCenterPositionOnBase,    //基于基座标系的法兰盘中心位置信息
                                     const aubo_robot_namespace::Ori            &flangeCenterOrientationOnBase, //基于基座标系的姿态信息
                                     const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoord,  //用户坐标系
                                     const aubo_robot_namespace::ToolInEndDesc  &toolInEndDesc,                 //工具参数
                                     aubo_robot_namespace::Pos                  &toolEndPositionOnUserCoord,    //基于用户座标系的工具末端位置信息
                                     aubo_robot_namespace::Ori                  &toolEndOrientationOnUserCoord  //基于用户座标系的工具末端姿态信息
                                     );


    /**
     * @brief baseToBaseAdditionalTool        　基坐标系转基座标得到工具末端点的位置和姿态
     *
     * @param flangeCenterPositionOnBase       基于基座标系的法兰盘中心位置信息
     * @param flangeCenterOrientationOnBase    基于基座标系的姿态信息
     * @param toolInEndDesc                    工具信息
     * @param toolEndPositionOnUserCoord       基于基座标系的工具末端位置信息    输出参数
     * @param toolEndOrientationOnUserCoord    基于基座标系的工具末端姿态信息    输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    static int baseToBaseAdditionalTool( const aubo_robot_namespace::Pos            &flangeCenterPositionOnBase,   //基于基座标系的法兰盘中心位置信息
                                         const aubo_robot_namespace::Ori            &flangeCenterOrientationOnBase, //基于基座标系的法兰盘姿态信息
                                         const aubo_robot_namespace::ToolInEndDesc  &toolInEndDesc,                 //工具信息
                                         aubo_robot_namespace::Pos                  &toolEndPositionOnBase,    //基于基座标系的工具末端位置信息
                                         aubo_robot_namespace::Ori                  &toolEndOrientationOnBase  //基于基座标系的工具末端姿态信息);
                                         );


    /**
     * @brief userToBaseCoordinate                用户坐标系位置和姿态信息转基座标系下位置和姿态信息
     *
     *        概述:  将工具末端基于用户座标系下的位置和姿态　转成　法兰盘中心基于基座标系下的位置和姿态。
     *
     *      　扩展1:  法兰盘中心可以看成是一个特殊的工具，即工具的位置为(0,0,0)姿态为（1,0,0,0）
     * 　　　　　　　  因此当工具工具的位置为(0,0,0)姿态为（1,0,0,0）时，表示toolEndPositionOnUserCoord和toolEndOrientationOnUserCoord是无工具的。
     *
     * 　　　　扩展2:  用户坐标系也可以选择成基座标系，　　即：userCoord.coordType = BaseCoordinate
     *               因此当用户平面为基座标系时，相当于 将工具末端基于基座标系下的位置和姿态　转成　法兰盘中心基于基座标系下的位置和姿态，
     *               即在基座标系去工具.
     *
     *       扩展３:  利用该函数和逆解组合实现　　　　　当用户提供自定义坐标系（特殊为基座标系）下工具末端的位置和姿态　得到　基座标系下法兰盘中心的位置和姿态
     * 　　　　　　　　然后在逆解，得到目标路点。
     *
     * @param toolEndPositionOnUserCoord          基于用户座标系的工具末端位置信息
     * @param toolEndOrientationOnUserCoord       基于用户座标系的工具末端姿态信息
     * @param userCoord                           用户坐标系    通过该参数确定一个坐标系
     * @param toolInEndDesc                       工具信息
     * @param flangeCenterPositionOnBase          基于基座标系的法兰盘中心位置信息
     * @param flangeCenterOrientationOnBase       基于基座标系的姿态信息
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     *
     * 注：这个的坐标系转换不支持末端系　　即不支持userCoord==EndCoordinate,如果userCoord==EndCoordinate会报参数错误(ErrCode_ParamError)
     */
    static int userToBaseCoordinate( const aubo_robot_namespace::Pos            &toolEndPositionOnUserCoord,    //基于用户座标系的工具末端位置信息
                                     const aubo_robot_namespace::Ori            &toolEndOrientationOnUserCoord, //基于用户座标系的工具末端姿态信息
                                     const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoord,  //用户坐标系
                                     const aubo_robot_namespace::ToolInEndDesc  &toolInEndDesc,                 //工具信息
                                     aubo_robot_namespace::Pos                  &flangeCenterPositionOnBase,    //基于基座标系的法兰盘中心位置信息
                                     aubo_robot_namespace::Ori                  &flangeCenterOrientationOnBase  //基于基座标系的法兰盘中心姿态信息
                                     );


    /**
     * @brief userCoordPointToBasePoint    将空间内一个基于用户坐标系的位置信息(x,y,z)　转换成基于　基座标下的位置信息(x,y,z)
     *
     * @param userCoordPoint        用户坐标系下的位置信息 x,y,z（必须的基于下面参数提供的坐标系下的）
     * @param userCoordSystem　　　　用户坐标系描述    通过该参数确定一个坐标系　不能为末端坐标系　如果userCoord==EndCoordinate会报参数错误(ErrCode_ParamError)
     * @param basePoint　　　　　　　　基于基坐标系下的位置信息x,y,z
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     *
     * 注：这个的坐标系转换不支持末端系　　即不支持userCoord==EndCoordinate,如果userCoord==EndCoordinate会报参数错误(ErrCode_ParamError)
     */
    static int userCoordPointToBasePoint(const aubo_robot_namespace::Pos &userCoordPoint,
                                         const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoordSystem,
                                         aubo_robot_namespace::Pos &basePoint);


    //法兰盘姿态转成工具姿态
    static int endOrientation2ToolOrientation(aubo_robot_namespace::Ori &tcpOriInEnd, const aubo_robot_namespace::Ori &endOri,  aubo_robot_namespace::Ori &toolOri);

    //工具姿态转成法兰盘姿态
    static int toolOrientation2EndOrientation(aubo_robot_namespace::Ori &tcpOriInEnd, const aubo_robot_namespace::Ori &toolOri, aubo_robot_namespace::Ori &endOri);

    //根据位置获取目标路点信息
    static int getTargetWaypointByPosition(const aubo_robot_namespace::wayPoint_S       &sourceWayPointOnBaseCoord,
                                           const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoordSystem,
                                           const aubo_robot_namespace::Pos              &toolEndPosition,
                                           const aubo_robot_namespace::ToolInEndDesc    &toolInEndDesc,
                                           aubo_robot_namespace::wayPoint_S             &targetWayPointOnBaseCoord);



    /**
     * @brief quaternionToRPY     四元素转欧拉角
     * @param ori　　　　　姿态的四元素表示方法
     * @param rpy　　　　　姿态的欧拉角表示方法
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int quaternionToRPY(const aubo_robot_namespace::Ori &ori, aubo_robot_namespace::Rpy &rpy);

    /**
     * @brief RPYToQuaternion    欧拉角转四元素
     * @param rpy       姿态的欧拉角表示方法
     * @param ori       姿态的四元素表示方法
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int RPYToQuaternion(const aubo_robot_namespace::Rpy &rpy, aubo_robot_namespace::Ori &ori);


    /**
     * @brief 坐标变换(F_c_a = F_c_b * F_b_a)
     * @param F_b_a: a 相对于 b 的位姿
     * @param F_c_b: b 相对于 c 的位姿
     * @return a 相对于 c 的位姿
     */
    int poseTrans(const aubo_robot_namespace::PositionAndQuaternion &F_b_a,
                  const aubo_robot_namespace::PositionAndQuaternion &F_c_b,
                  aubo_robot_namespace::PositionAndQuaternion &F_c_a);

    /**
     * @brief 齐次变换矩阵的逆
     * @param F_b_a: a 相对于 b 的位姿
     * @return b 相对于 a 的位姿
     */
    int poseInv(const aubo_robot_namespace::PositionAndQuaternion &F_b_a,
                aubo_robot_namespace::PositionAndQuaternion &F_a_b);


    int userCoord2Pose(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoord,
                       aubo_robot_namespace::PositionAndQuaternion &F_b_u);

    /**
     * @brief getErrDescByCode  根据错误号获取错误信息
     * @param code　　错误号
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    std::string getErrDescByCode(aubo_robot_namespace::RobotErrorCode code);

    /**
      * @brief 计算圆心半径
      * @param p1: 第一点x,y,z
      * @param p2: 第二点x,y,z
      * @param p3: 第三点x,y,z
      * @param radius:半径
      * @return　调用成功返回ErrnoSucc;错误返回错误号
      */
    int computedCircleRadius(const double p1[3], const double p2[3], const double p3[3], float &radius);

    /**********************************************************************************************************************************************
     ************************************************************机械臂控制接口**********************************************************************
     **********************************************************************************************************************************************/
public:

    /**
     * @brief 机械臂控制
     * @param cmd   控制命令
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  rootServiceRobotControl(const aubo_robot_namespace::RobotControlCommand cmd);


    /**
     * @brief 设置机械臂的电源状态
     * @param value
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServicePowerControl(bool value);

    int  robotServiceReleaseBrake();



    /**
     * @brief rootServiceRobotStartup    启动机械臂-----该操作会完成机械臂的上电，松刹车，设置碰撞等级，设置动力学参数等功能。
     * @param toolDynamicsParam　　　　　　动力学参数
     * @param collisionClass　　　　　　　　碰撞等级
     * @param readPose                   是否允许读取位置　　　默认是true
     * @param staticCollisionDetect      
     * @param boardBaxAcc
     * @param result
     * @param IsBolck
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int rootServiceRobotStartup(const aubo_robot_namespace::ToolDynamicsParam &toolDynamicsParam, uint8 collisionClass, bool readPose,
                                bool staticCollisionDetect, int boardBaxAcc, aubo_robot_namespace::ROBOT_SERVICE_STATE &result, bool IsBolck = true);


    /**
     * @brief    关机
     * @param IsBolck        是否阻塞
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRobotShutdown(bool IsBolck = true);


    /**********************************************************************************************************************************************
     **********************************************************************************************************************************************
     ************************************************************关于末端工具的接口*******************************************************************
     **********************************************************************************************************************************************
     **********************************************************************************************************************************************/
public:
    /** 设置无工具的动力学参数　**/
    int  robotServiceSetNoneToolDynamicsParam();

    /** 设置工具的动力学参数　 **/
    int  robotServiceSetToolDynamicsParam(const aubo_robot_namespace::ToolDynamicsParam &toolDynamicsParam);

    /** 获取工具的动力学参数　 **/
    int  robotServiceGetToolDynamicsParam(aubo_robot_namespace::ToolDynamicsParam &toolDynamicsParam);

    /** 设置无工具运动学参数　 **/
    int  robotServiceSetNoneToolKinematicsParam();

    /** 设置工具的运动学参数　 **/
    int  robotServiceSetToolKinematicsParam(const aubo_robot_namespace::ToolKinematicsParam &toolKinematicsParam);

    /** 获取工具的运动学参数　 **/
    int  robotServiceGetToolKinematicsParam(aubo_robot_namespace::ToolKinematicsParam &toolKinematicsParam);



    /**********************************************************************************************************************************************
     ************************************************************机械臂相关参数设置与获取的接口*********************************************************
     **********************************************************************************************************************************************/
public:

    /**
     * @brief robotServiceGetRobotWorkMode　　　获取当前机械臂模式
     * @param mode   输出参数　　仿真或真实的枚举类型
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetRobotWorkMode(aubo_robot_namespace::RobotWorkMode &mode);

    /**
     * @brief robotServiceSetRobotWorkMode  设置当前机械臂模式   仿真或真实
     * @param mode　　　仿真或真实的枚举类型
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetRobotWorkMode(aubo_robot_namespace::RobotWorkMode mode);

    /**
     * @brief robotServiceSetEnableForceTeachWhenProjectIsRunning  在工程运行的时候使能/失能力控模式
     * @param enable  true:使能  false:失能
     * @return
     */
    int robotServiceSetEnableForceTeachWhenProjectIsRunning(bool enable);

    /**
     * @brief robotServiceSetRobotWorkMode  获取重力分量
     * @param mode　　　输出参数　　仿真或真实的枚举类型
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetRobotGravityComponent(aubo_robot_namespace::RobotGravityComponent  &gravityComponent);

    //业务接口: 获取当前碰撞等级
    int robotServiceGetRobotCollisionCurrentService(int &collisionGrade);

    //
    int robotServiceSetRobotCollisionClass(int grade, aubo_robot_namespace::CollisionMode collisionMode);

    //业务接口: 设置碰撞等级
    int robotServiceSetRobotCollisionClass(int grade);

    //业务接口:获取设备信息
    int robotServiceGetRobotDevInfoService(aubo_robot_namespace::RobotDevInfo &devInfo);
    int robotServiceGetInterfaceBoardVersionMajor(int &version_major);

    //设置最大加速度
    int robotServiceSetRobotMaxACC(int maxAcc);

    //碰撞恢复
    int robotServiceCollisionRecover();

    int robotServiceJointPosRecover(bool confirm);

    int robotServiceGetRobotCurrentState(aubo_robot_namespace::RobotState &state);

    int robotServiceGetMacCommunicationStatus(bool  &value);


    /**
     * @brief robotServiceGetIsRealRobotExist  获取是否存在真实机械臂
     * @param value   输出参数　　存在为true,不存在为false
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetIsRealRobotExist(bool &value);

    /**
     * @brief robotServiceGetJoint6Rotate360EnableFlag   获取６关节旋转360使能标志
     * @param value
     * @return
     */
    int robotServiceGetJoint6Rotate360EnableFlag(bool &value);

    /**
     * @brief robotServiceGetRobotJointStatus   获取机械臂关节状态
     * @param jointStatus    关节角缓冲区　　输出参数
     * @param size           关节角缓冲区长度
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetRobotJointStatus(aubo_robot_namespace::JointStatus *jointStatus, int size);

    int robotServiceGetRobotJointTypeParameter(aubo_robot_namespace::JointTypeParameter *jointTypeParam, int size);


    /**
     * @brief robotServiceGetRobotDiagnosisInfo   获取机械臂诊断信息
     * @param robotDiagnosisInfo   输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetRobotDiagnosisInfo(aubo_robot_namespace::RobotDiagnosis &robotDiagnosisInfo);


    /**
     * @brief robotServiceGetJointAngleInfo   获取机械臂当前关节角信息
     * @param jointParam    输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetJointAngleInfo(aubo_robot_namespace::JointParam &jointParam);
    
    
    int robotServiceGetCorrectedWaypoint(const aubo_robot_namespace::wayPoint_S source, aubo_robot_namespace::wayPoint_S &waypint);


    /**
     * @brief robotServiceGetCurrentWaypointInfo   获取机械臂当前路点信息
     * @param wayPoint   输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetCurrentWaypointInfo(aubo_robot_namespace::wayPoint_S &wayPoint);

    int robotServiceGetTargetWaypointFromController(aubo_robot_namespace::wayPoint_S &wayPoint);

    int robotServerGetToolForceSensorData(aubo_robot_namespace::ForceSensorData &data);

    /**
     * @brief robotServiceSetJointRangeOfMotion    设置关节运动范围
     * @param rangeOfMotion
     * @return
     */
    int robotServiceSetJointRangeOfMotion(const aubo_robot_namespace::JointRangeOfMotion &rangeOfMotion);


    /**
     * @brief robotServiceGetJointRangeOfMotion    获取关节运动范围
     * @param rangeOfMotion
     * @return
     */
    int robotServiceGetJointRangeOfMotion(aubo_robot_namespace::JointRangeOfMotion &rangeOfMotion);
    int robotServiceGetJointPositionLimit(aubo_robot_namespace::JointRangeOfMotion &rangeOfMotion);
    int robotServiceGetJointPositionLimitBoard(aubo_robot_namespace::JointRangeOfMotion &rangeOfMotion);


    /*****************************************************************************************************************************************************/
    /*      安全ＩＯ相关                                                                                                                      */
    /*                                                                                                                                      */
    /****************************************************************************************************************************************************/

    int robotServiceSetRobotAtOriginPose();

    /**
     * @brief 通知接口板上位机暂停状态
     * @param data
     * @return
     */
    int robotServiceSetRobotOrpePause(uint8 data);

    /**
     * @brief 通知接口板上位机停止状态
     * @param data
     * @return
     */
    int robotServiceSetRobotOrpeStop(uint8 data);

    /**
     * @brief 通知机械臂工程启动，服务器同时开始检测安全IO
     * @return
     */
    int robotServiceSetRobotProjectStartup();

    /**
     * @brief 通知机械臂工程停止，服务器停止检测安全IO
     * @return
     */
    int robotServiceSetRobotProjectStop();

    /**
     * @brief 通知接口板上位机错误
     * @param 16个字节的错误数据，每个错误占一个bit
     * @return
     */
    int robotServiceSetRobotOrpeError(uint8 data[], int len);

    /**
     * @brief 解除系统紧急停止输出信号 0-无动作 1-解除
     * @param data
     * @return
     */
    int robotServiceClearSystemEmergencyStop(uint8 data);

    /**
     * @brief 解除缩减模式错误 0-无效 1-解除
     * @param data
     * @return
     */
    int robotServiceClearReducedModeError(uint8 data);

    /**
     * @brief 防护重置成功 0-无动作 1-解除
     * @param data
     * @return
     */
    int robotServiceRobotSafetyguardResetSucc(uint8 data);

    /**
     * @brief 设置机械臂运动进入缩减模式
     * @return
     */
    bool robotServiceEnterRobotReduceMode();

    /**
     * @brief 设置机械臂运动退出缩减模式
     * @return
     */
    bool robotServiceExitRobotReduceMode();



    /**********************************************************************************************************************************************
     ************************************************************关于接口板IO的接口**********************************************************************
     **********************************************************************************************************************************************/
public:
    /**
     * @brief 获取接口板指定IO集合的配置信息
     * @param ioType         IO类型的集合    输入参数
     * @param configVector   IO配置信息的集合 输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetBoardIOConfig(const std::vector<aubo_robot_namespace::RobotIoType> &ioType, std::vector<aubo_robot_namespace::RobotIoDesc> &configVector);


    /**
     * @brief 获取接口板指定IO集合的状态信息
     * @param ioType
     * @param statusVector
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetBoardIOStatus(const std::vector<aubo_robot_namespace::RobotIoType>  ioType, std::vector<aubo_robot_namespace::RobotIoDesc> &statusVector);

    /**
     * @brief 根据接口板IO类型和名称设置IO状态
     * @param type     IO类型
     * @param name     IO名称
     * @param value    IO状态
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetBoardIOStatus(aubo_robot_namespace::RobotIoType type, std::string name, double value);

    /**
     * @brief 根据接口板IO类型和地址设置IO状态
     * @param type    IO类型
     * @param addr    IO地址
     * @param value   IO状态
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetBoardIOStatus(aubo_robot_namespace::RobotIoType type, int    addr,      double value);

    /**
     * @brief 根据接口板IO类型和名称设置脉冲
     * @param type    IO类型
     * @param addr    IO地址
     * @param value   IO状态
     * @param duration 脉冲时长(ms)
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetBoardIOPulse(aubo_robot_namespace::RobotIoType type, std::string name, double value, int millisecond);

    /**
     * @brief 根据接口板IO类型和地址设置脉冲
     * @param type    IO类型
     * @param addr    IO地址
     * @param value   IO状态
     * @param duration 脉冲时长(ms)
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetBoardIOPulse(aubo_robot_namespace::RobotIoType type, int addr, double value, int millisecond);

    /**
     * @brief 根据接口板IO类型和名称获取IO状态
     * @param type     IO类型
     * @param name     IO名称
     * @param value    IO状态
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetBoardIOStatus(aubo_robot_namespace::RobotIoType type, std::string name, double &value);

    /**
     * @brief 根据接口板IO类型和地址获取IO状态
     * @param type    IO类型
     * @param addr    IO地址
     * @param value   IO状态
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetBoardIOStatus(aubo_robot_namespace::RobotIoType type, int    addr,      double &value);



    /**
     * @brief 返回当前机械臂是否运行在联机模式
     * @param isOnlineMode  true：联机 false：非联机
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceIsOnlineMode(bool &isOnlineMode);

    /**
     * @brief 返回当前机械臂是否运行在联机主模式
     * @param isOnlineMode  true：联机主模式 false：联机从模式
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceIsOnlineMasterMode(bool &isOnlineMasterMode);


    int robotServiceSetDIAction(aubo_robot_namespace::ROBOT_DI_ACTION action, int addr);
    int robotServiceGetDIAction(aubo_robot_namespace::ROBOT_DI_ACTION action, int &addr);
    int robotServiceSetDIAction(aubo_robot_namespace::ROBOT_DI_ACTION action, std::string name);
    int robotServiceGetDIAction(aubo_robot_namespace::ROBOT_DI_ACTION action, std::string &name);

    int robotServiceSetDOAction(aubo_robot_namespace::ROBOT_DO_ACTION action, int addr);
    int robotServiceGetDOAction(aubo_robot_namespace::ROBOT_DO_ACTION action, int &addr);
    int robotServiceSetDOAction(aubo_robot_namespace::ROBOT_DO_ACTION action, std::string name);
    int robotServiceGetDOAction(aubo_robot_namespace::ROBOT_DO_ACTION action, std::string &name);


public:
    //业务接口: 获取机械臂安全配置
    int  robotServiceGetRobotSafetyConfig(aubo_robot_namespace::RobotSafetyConfig &safetyConfig);

    //业务接口: 获取机械臂安全配置
    int  robotServiceSetRobotSafetyConfig(const aubo_robot_namespace::RobotSafetyConfig &safetyConfig);

    //业务接口: 获取机械臂安全状态
    int  robotServiceGetOrpeSafetyStatus(aubo_robot_namespace::OrpeSafetyStatus &safetyStatus);






    /**********************************************************************************************************************************************
     ************************************************************关于tool IO的接口**********************************************************************
     **********************************************************************************************************************************************/
public:

    /**
     * @brief 设置工具端电源电压类型
     * @param type   电源电压类型
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetToolPowerVoltageType  (aubo_robot_namespace::ToolPowerType type);


    /**
     * @brief  获取工具端电源电压类型
     * @param  输出参数   接口调用成功后返回的电源电压类型
     * @return
     */
    int robotServiceGetToolPowerVoltageType  (aubo_robot_namespace::ToolPowerType &type);


    /**
      * @brief 获取工具端的电源电压
      * @param value   输出参数
      * @return
      */
    int robotServiceGetToolPowerVoltageStatus(double &value);

    /**
     * @brief robotServiceSetToolPowerTypeAndDigitalIOType  设置工具端电源电压类型and所有数字量IO的类型
     * @param type
     * @param io0
     * @param io1
     * @param io2
     * @param io3
     * @return
     */
    int robotServiceSetToolPowerTypeAndDigitalIOType(aubo_robot_namespace::ToolPowerType type,
                                                     aubo_robot_namespace::ToolIOType io0,
                                                     aubo_robot_namespace::ToolIOType io1,
                                                     aubo_robot_namespace::ToolIOType io2,
                                                     aubo_robot_namespace::ToolIOType io3);


    /**
     * @brief 设置工具端数字量IO的类型    输入或者输出
     * @param 地址
     * @param 类型  输入或者输出
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetToolDigitalIOType(aubo_robot_namespace::ToolDigitalIOAddr addr,  aubo_robot_namespace::ToolIOType type);


    /**
     * @brief 获取工具端所有数字量IO的状态
     * @param statusVector    输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetAllToolDigitalIOStatus(std::vector<aubo_robot_namespace::RobotIoDesc> &statusVector);

    /**
     * @brief 根据地址设置工具端数字量IO的状态
     * @param addr    IO地址
     * @param value   IO状态
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetToolDOStatus          (aubo_robot_namespace::ToolDigitalIOAddr addr, aubo_robot_namespace::IO_STATUS value);

    /**
     * @brief 根据名称设置工具端数字量IO的状态
     * @param addr    IO地址
     * @param value   IO状态
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetToolDOStatus(std::string name,        aubo_robot_namespace::IO_STATUS value);

    /**
     * @brief 根据地址设置工具端数字量IO的脉冲
     * @param addr    IO地址
     * @param value   IO状态
     * @param duration   脉冲时长(ms)
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetToolDOPulse(int addr, double value, int millisecond);

    /**
     * @brief 根据名称设置工具端数字量IO的脉冲
     * @param addr    IO地址
     * @param value   IO状态
     * @param duration   脉冲时长(ms)
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetToolDOPulse(std::string name, double value, int millisecond);

    /**
     * @brief 根据名称获取工具端IO的状态
     * @param name     IO名称
     * @param value    IO状态  输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetToolIoStatus(std::string name, double &value);

    /**
     * @brief 获取工具端所有AI的状态
     * @param 输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetAllToolAIStatus       (std::vector<aubo_robot_namespace::RobotIoDesc> &statusVector);

    int robotServiceSetToolSerialConfig(aubo_robot_namespace::ToolBusType type,
                                        aubo_robot_namespace::ToolSerialBaudRate baud,
                                        aubo_robot_namespace::ToolSerialStopBitNum stop,
                                        aubo_robot_namespace::ToolSerialCheck check,
                                        aubo_robot_namespace::ToolSerialCheckCmd check_cmd);

    int robotServiceGetToolSerialConfig(aubo_robot_namespace::ToolBusType &type,
                                        aubo_robot_namespace::ToolSerialBaudRate &baud,
                                        aubo_robot_namespace::ToolSerialStopBitNum &stop,
                                        aubo_robot_namespace::ToolSerialCheck &check,
                                        aubo_robot_namespace::ToolSerialCheckCmd &check_cmd);


public:  //固件升级
    int  robotServiceUpdateRobotBoardFirmware(aubo_robot_namespace::update_board_firmware_cmd cmd, const void *data, uint16 length);

    int  robotServiceGetBoardFirmwareUpdateResultService(bool &value);

public:

    int  robotServiceGetRobotEthernetDeviceName(std::string &ethernetDeviceName);

    //获取服务器版本信息
    int  robotServiceGetServerVersionInfo(std::string &versionInfo);

public:
    /**
     * @brief 设置关节碰撞补偿（范围0.00~0.51度）
     * @param jointOffset
     * @return
     */
    int robotServiceSetRobotJointOffset(aubo_robot_namespace::RobotJointOffset &jointOffset);


public:  //传送带跟踪

    int robotServiceSetConveyorEncoderReset(void);

    /**
     * @brief 启动传送带
     * @return
     */
    int robotServiceSetConveyorStartup(void);

    /**
     * @brief 停止传送带
     * @return
     */
    int robotServiceSetConveyorStop(void);

    /**
     * @brief 设置传送带方向
     * @param dir
     * @return
     */
    int robotServiceSetConveyorDir(int dir);


    /**
     * @brief 设置手眼标定结果关系
     * @param robotCameraCalib
     */
    int robotServiceSetRobotCameraCalib(const aubo_robot_namespace::RobotCameraCalib &robotCameraCalib);


    /**
     * @brief 设置传送带线速度
     * @param conveyorVelc (米/秒）
     */
    int robotServiceSetConveyorVelc(const double conveyorVelc);


    /**
     * @brief 设置编码器距离关系
     * @param encoderValPerMeter 编码器距离关系（编码器脉冲个数/米)
     */
    int robotServiceSetEncoderValPerMeter(const uint32_t &encoderValPerMeter);


    /**
     * @brief 设置传送带起始窗口上限
     * @param startWindowUpstream　单位：米
     */
    int robotServiceSetStartWindowUpstream(double startWindowUpstream);


    /**
     * @brief 设置传送带起始窗口下限
     * @param startWindowDownstream 单位：米
     */
    int robotServiceSetStartWindowDownstream(double startWindowDownstream);

    /**
     * @brief 设置传送带跟踪轨迹下限 单位：米
     * @param trackDownstream
     */
    int robotServiceSetConveyorTrackDownstream(double trackDownstream);


    int robotServiceAppendObject2ConveyorTrackQueue(const aubo_robot_namespace::Pos &objectPos, const aubo_robot_namespace::Ori &objectOri, uint32_t timestamp);


    int robotServiceEnableConveyorTrack();


    int robotServiceGetConveyorEncoderVal(int &value);

    //设置传送带跟踪的最大速度
    int robotServiceSetRobotConveyorTrackMaxVelc(double robotConveyorTrackMaxVelc);

    //设置传送带跟踪的最大加速度
    int robotServiceSetRobotConveyorTrackMaxAcc(double robotConveyorTrackMaxAcc);

    //设置传送带跟踪的系统延时时间
    int robotServiceSetRobotConveyorSystemDelay(double robotConveyorSystemDelay);

    //设置机械臂工具
    int robotServiceSetRobotTool(const aubo_robot_namespace::ToolInEndDesc &robotTool);

public:
    int robotServiceSetWeaveMoveParameters(const aubo_robot_namespace::WeaveMove &weaveMove);


public:
    int robotServiceSetRobotRecognitionParam(const aubo_robot_namespace::RobotRecongnitionParam &param);

    int robotServiceGetRobotRecognitionParam(int type, aubo_robot_namespace::RobotRecongnitionParam &param);

    int robotServiceSetSeamTrackingParameters(const aubo_robot_namespace::SeamTracking &seamTrack);

    int robotServiceGetSeamTrackingParameters(aubo_robot_namespace::SeamTracking &seamTrack);


public:
    int  robotServiceGetJointInitData(aubo_robot_namespace::JointInitData jointInitDataArray[], int size);

    int  robotServiceGetJointCommonData(aubo_robot_namespace::JointCommonData jointCommonDataArray[], int size);

    int  robotServiceSetJointParam_CurrentIP(int jointID, uint16 P);

    int  robotServiceSetJointParam_CurrentII(int jointID, uint16 I);

    int  robotServiceSetJointParam_CurrentID(int jointID, uint16 D);

    int  robotServiceSetJointParam_SpeedP(int jointID, uint16 P);

    int  robotServiceSetJointParam_SpeedI(int jointID, uint16 I);

    int  robotServiceSetJointParam_SpeedD(int jointID, uint16 D);

    int  robotServiceSetJointParam_SpeedDS(int jointID, uint16 DS);

    int  robotServiceSetJointParam_PosP(int jointID, uint16 P);

    int  robotServiceSetJointParam_PosI(int jointID, uint16 I);

    int  robotServiceSetJointParam_PosD(int jointID, uint16 D);

    int  robotServiceSetJointParam_PosDS(int jointID, uint16 DS);

    int  robotServiceJointSaveDataFlash(int jointID);

    int  robotServiceSetRobotBaseParameters(const aubo_robot_namespace::RobotBaseParameters &baseParameters);

    int  robotServiceNodeWriteData(int node_id, int start_addr, uint16 *data, int size);
    int  robotServiceNodeReadData(int node_id, int start_addr, uint16 *data, int size);
    int  robotServiceGetScrewerStatus(aubo_robot_namespace::ScrewerStatus &screwerStatus);


public:  //脚本管理

    int robotServiceScriptRun(const char *scriptPath, const char *scriptLabel);
    int robotServiceRegisterPercentageEvent(double percent,const char *scriptPath);
    int robotServiceScriptRunSetSpeedLimitPercent(const double speedLimit);
    int robotServiceScriptRunGetSpeedLimitPercent(double &speedLimitPercent);
public: //关节驱动升级
    int startUpdateJointFirmware(int jointId, const char *updateFilePath);
    int getUpdateJointFirmwareResult(bool &isFinished, bool &isSucceed);
    int setUpdateJointFirmwareFinished(int jointId);

    // 获取 movep 当前进度
    int getMovepSequenceNumber(int &num);

    int getCollisionCurrentThreshold(aubo_robot_namespace::CollisionCurrent &current);

public:  //调速模式
    //设置调速模式配置
    int robotServiceSetRegulateSpeedModeParam(const aubo_robot_namespace::RegulateSpeedModeParamConfig_t &regulateSpeedModeConfig);

    int  robotServiceGetRobotBaseParameters(aubo_robot_namespace::RobotBaseParameters &baseParameters);
    //获取调速模式配置
    int robotServiceGetRegulateSpeedModeParam(aubo_robot_namespace::RegulateSpeedModeParamConfig_t &regulateSpeedModeConfig);

    int  robotServiceSetRobotJointsParameter(const aubo_robot_namespace::RobotJointsParameter &jointsParameter);
    //使能/失能调速模式
    int robotServiceEnableRegulateSpeedMode(bool enbaleFlag);

    int  robotServiceGetRobotJointsParameter(aubo_robot_namespace::RobotJointsParameter &jointsParameter);
public: //力控模式
    //获取力控参数
    int robotServiceGetForceControlModeAdmittancePatam(aubo_robot_namespace::AdmittancePatam_t &admittancePatam);

    int  robotServiceRefreshRobotArmParamter();
    //设置力控参数
    int robotServiceSetForceControlModeAdmittancePatam(const aubo_robot_namespace::AdmittancePatam_t &admittancePatam);

public:
    //获取"主动探寻力"参数
    int robotServiceGetForceControlModeExploreForceParam(double &forceLimit, double &distLimit);

    //int  robotServiceGetForceSensorData(WrenchParam &data);
    //设置"主动探寻力"参数
    int robotServiceSetForceControlModeExploreForceParam(double forceLimit, double distLimit);

    //int  robotServiceCalibToolAndSensor(aubo_robot_namespace::JointParam JointParamGroup[3], WrenchParam wrenchParamGroup[3], FtSensorCalResult &result);
    //使能/失能力控模式
    int robotServicEnableForceControlModeService(bool enbaleFlag);

    int  robotServiceEnableForceControlPlan(bool enableFlag);
    //获取实时力数据
    int robotServiceGetRealtimeForceData(double forceData[6]);

    int  robotServiceSetForceDeviation(double data[6]);
public:
    /**
     * @brief parseFileAsRoadpointCollection
     *        将一个轨迹文件(位置+姿态)转换为路点容器，进行平滑处理和限制条件检查
     * @param filePath              轨迹文件路径      输入参数
     * @param referPointJointAngle  逆解参考点的关节角 输入参数
     * @param toolInEndDesc         末端工具的信息    输入参数
     * @param wayPointVector        路点集合         输出参数
     * @return
     */
    int parseFileAsRoadpointCollection(const char *filePath, aubo_robot_namespace::POSITION_ORIENTATION_TYPE poseType,
                                       const double *referPointJointAngle, const aubo_robot_namespace::ToolInEndDesc &toolInEndDesc, std::vector<aubo_robot_namespace::wayPoint_S> &wayPointVector);

    int  robotServiceSetForceMaxValue(double data[6]);
    /**
     * @brief parsePoseListeAsRoadpointCollection
     *        将位姿集合(位置+四元数)转换为路点容器， 进行平滑处理和限制条件检查
     * @param referPointJointAngle 逆解参考点的关节角 输入参数
     * @param toolInEndDesc        末端工具的信息    输入参数
     * @param toolEndPoseVector    位姿集合         输入参数
     * @param wayPointVector       路点集合         输出参数
     * @return
     */
    int parsePoseListeAsRoadpointCollection( const double *referPointJointAngle, const aubo_robot_namespace::ToolInEndDesc &toolInEndDesc,
                                             const std::vector<aubo_robot_namespace::PositionAndQuaternion> &toolEndPoseVector, std::vector<aubo_robot_namespace::wayPoint_S> &wayPointVector);

    int  robotServiceSetForceControlStiffness(double data[6]);

    int  robotServiceSetForceControlDamp(double data[6]);
    //解析路点文件并缓存结果
    int parseRoadPointFileAndCacheResult(const char *filePath, const double *referPointJointAngle, aubo_robot_namespace::ToolInEndDesc &toolInEndDesc, aubo_robot_namespace::wayPoint_S &firstWayPoint);

    int  robotServiceSetForceControlMass(double data[6]);
    //运行缓存轨迹（parseRoadPointFileAndCacheResult 结果）
    int moveCacheTrack();

    int  robotServiceForceControlCalibrationZero();


private:
    int HandlePosesFromFile(const char *filePath, const double *referPointJointAngle,
                            aubo_robot_namespace::ToolInEndDesc &toolInEndDesc, std::vector<FlangeAndToolInfo> &wayPointVector);

    int hanweiRoadPointHandle(const char *filePath, const double *referPointJointAngle, aubo_robot_namespace::ToolInEndDesc &toolInEndDesc,
                              std::vector<FlangeAndToolInfo> &flangeAndToolInfoVector, std::vector<int> &split_start_index);

    int moveHanweiTrack(const char *filePath, double *referPointJointAngle, aubo_robot_namespace::ToolInEndDesc &toolInEndDesc);

public:
    int HandlePosesFromFile(const char *filePath, const double *referPointJointAngle,
                            aubo_robot_namespace::ToolInEndDesc &toolInEndDesc, std::vector<aubo_robot_namespace::wayPoint_S> &wayPointVector);

    //针对瀚维的轨迹处理
    int hanweiRoadPointHandle(const char *filePath, const double *referPointJointAngle, aubo_robot_namespace::ToolInEndDesc &toolInEndDesc, aubo_robot_namespace::wayPoint_S &firstWayPoint);

    //针对瀚维使用
    int moveHanweiTrack();

public:
    //获取SDK版本
    std::string getVersion();

public:
    /**
     * @brief  nc轨迹的相关函数
     * @param Set_UserCoord     用户坐标系     输入参数
     * @param Set_Tool                工具                 输入参数
     * @param Set_FilePath          文件路径         输入参数
     * @param Set_Io                    Io口                输入参数
     * @param HighOrLowLevel   要设置的状态(打开:1; 关闭:0)       输入参数
     * @param Set_LineSpeed     线速度             输入参数
     * @param NC_PosList           路点集合         输出参数
     * @return
     */
    /********************nc给外部调用，设置相关参数/获取数据*********************************/
        /**************必须设置的属性start,*****************/
        //设置用户坐标系
        bool NC_Set_UserCoord(aubo_robot_namespace::CoordCalibrateByJointAngleAndTool Set_UserCoord);
        //设置工具
        bool NC_Set_Tool(aubo_robot_namespace::ToolInEndDesc Set_Tool);
        //设置文件路径
        bool NC_Set_FilePath(const std::string& Set_FilePath);
        //设置io相关属性;若is_modbus设为true,则代表io_type设置为aubo_robot_namespace::ModbusIOType::ModbusDO
        bool Nc_Set_Io(aubo_robot_namespace::RobotIoType IoType,const std::string Set_Io, int HighOrLowLevel,bool is_modbus = false);
        /**************必须设置的属性end*****************/

        //设置线速度 单位为mm
        bool NC_Set_LineSpeed(double Set_LineSpeed,double Set_Acc=50);
        //设置交融半径
        bool Nc_set_ArrivalAheadBlendDistance(double dis);
        //设置缩放系数. ps:不会直接改变生成的点或者轨迹，需要调用者自行调用相应函数生成
        bool Nc_Set_ScaleFactor(double ScaleFactor);
        //设置循环次数以及 循环间隔(单位为s)不设置的话分别默认为1次 2秒
        bool Nc_Set_CyclesAndIntervalTime(int cycles,int IntervalTime);

        //获取点的集合. 这里的点是基于用户坐标系的
        //注意:在调用此函数之前, 确保已经设置用户坐标系\工具\文件路径
        bool NC_Get_Points(std::list<aubo_robot_namespace::Nc_Points>& NC_PosList);
        //获取初始点一般为坐标原点
        bool NC_Get_InitPoint(aubo_robot_namespace::Nc_Points & NC_Point);
        //以回调的形式获取point集合，确保在此之前已经设置用户坐标系\工具\文件路径,并注册好回调函数
        bool NC_Get_Points_byCallBack();
        //获取当前缩放系数
        double Nc_get_ScaleFactor();
        //获取点的集合的size.ps:点位解析未完成时 返回0
        int Nc_Get_PointCount();

        bool Nc_Get_FileType(aubo_robot_namespace::NC_Import_File_Type &fileType);

        //开始运动 默认:阻塞执行\不用轨迹评估
        //block为真时,意味着此函数会阻塞执行,调用者也会被阻塞
        //type\interval 是轨迹评估用的参数
        bool Nc_start(bool block = true, aubo_robot_namespace::MoveModeType type = aubo_robot_namespace::MoveModeType::MOVE_GROUP, int interval = 0 );
        //发送运动指令 (暂停 停止 继续) (此函数还有bug 暂时先不对外开放)
        bool Nc_motion_control(aubo_robot_namespace::Nc_Move_Cmd cmd);

        //注册nc状态回调函数"robotServiceRegisterNcStatusCallback"依照sdk代码组织习惯放在了本文件第256行
        //注册nc_GetPoint回调函数"robotServiceRegisterNcGetPointCallback"依照sdk代码组织习惯放在了本文件第264行
        //注册nc_GetIkError回调函数robotServiceRegisterNcGetIkErorCallback依照sdk代码组织习惯放在了本文件第272行
    /**************************************************************************************/


private:   /**SDK内部使用 开发者不需要关心**/

    RobotControlServices             *m_robotBaseService;

    RobotIoService                   *m_robotIoService;

    RobotMoveService                 *m_robotMoveService;

    RobotConveyorTrack               *m_robotConveyorTrack;

    robotOtherService                *m_robotOtherService;

    ForceControl                     *m_forceControlService;

    HanWeiServices                   *m_hanWeiServiceHandle;

    static RobotLogPrint             *S_RobotLogPrintPtr;

    static Nc_Move                             *m_NcMove;

private:

    void                              *m_realTimeJointStatusCallbackArg;
    RealTimeJointStatusCallback        m_realTimeJointStatusCallback;
    pthread_mutex_t                    m_realTimeJointStatusCallbackChangeMutex;

    void                              *m_realTimeRoadPointCallbackArg;
    RealTimeRoadPointCallback          m_realTimeRoadPointCallback;
    pthread_mutex_t                    m_realTimeRoadPointCallbackChangeMutex;

    void                              *m_robotEventCallbackArg;
    RobotEventCallback                 m_robotEventCallback;
    pthread_mutex_t                    m_robotEventCallbackChangeMutex;

    void                              *m_robotEndSpeedCallbackArg;
    RealTimeEndSpeedCallback           m_robotEndSpeedCallback;
    pthread_mutex_t                    m_robotEndSpeedCallbackChangeMutex;

    void                                *m_movepProgressNotifyCallbackArg;
    RealTimeMovepStepNumNotifyCallback   m_movepProgressNotifyCallback;
    pthread_mutex_t                      m_movepProgressNotifyMutex;

    void                              *m_robotTcpEndSpeedCallbackArg;
    RealTimeEndSpeedCallback           m_robotTcpEndSpeedCallback;
    pthread_mutex_t                    m_robotTcpEndSpeedCallbackChangeMutex;

    void                              *m_plannerResultCallbackArg;
    PlannerResultCallback              m_plannerResultCallback;
    pthread_mutex_t                    m_plannerResultCallbackChangeMutex;

    void                              *m_analyseResultCallbackArg;
    AnalyseResultCallback              m_analyseResultCallback;
    pthread_mutex_t                    m_analyseResultCallbackChangeMutex;

    void                              *m_ncstatusCallbackArg;
    NcStatusCallback             	   m_ncstatusCallback;
    pthread_mutex_t                    m_ncstatusCallbackChangeMutex;
    static void* 					   m_static_ncstatusCbArg;

    void                              *m_ncgetpointCallbackArg;
    NcGetPointCallback             	   m_ncgetpointCallback;
    pthread_mutex_t                    m_ncgetpointCallbackChangeMutex;
    static void* 					   m_static_ncgetpointCbArg;

    void                              *m_ncGetIkErorCallbackArg;
    NcGetIkErorCallback                m_ncGetIkErorCallback;
    pthread_mutex_t                    m_ncGetIkErorCallbackChangeMutex;
    static void* 					   m_static_ncGetIkErorCbArg;
};

#endif // SERVICEINTERFACE_H