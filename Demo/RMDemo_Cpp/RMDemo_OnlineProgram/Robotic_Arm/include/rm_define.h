#ifndef RM_DEFINE_H
#define RM_DEFINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#define ARM_DOF 7
#define  M_PI		 3.14159265358979323846
#define  SDK_VERSION (char*)"1.0.0"

/**
 * @brief 线程模式
 * @ingroup Init_Class
 */
typedef enum {
    RM_SINGLE_MODE_E,       ///< 单线程模式，单线程非阻塞等待数据返回
    RM_DUAL_MODE_E,     ///< 双线程模式，增加接收线程监测队列中的数据
    RM_TRIPLE_MODE_E,       ///< 三线程模式，在双线程模式基础上增加线程监测UDP接口数据
}rm_thread_mode_e;

/**
 * @brief 机械臂型号
 * @ingroup Algo
 */
typedef enum{
    RM_MODEL_RM_65_E,       ///< RM_65
    RM_MODEL_RM_75_E,       ///< RM_75
    RM_MODEL_RM_63_I_E,     ///< RML_63(已弃用)
    RM_MODEL_RM_63_II_E,        ///< RML_63
    RM_MODEL_RM_63_III_E,       ///< RML_63(已弃用)
    RM_MODEL_ECO_65_E,      ///< ECO_65
    RM_MODEL_ECO_62_E,      ///< ECO_62
    RM_MODEL_GEN_72_E       ///< GEN_72
}rm_robot_arm_model_e;

/**
 * @brief 机械臂末端力传感器版本
 * @ingroup Algo
 */
typedef enum{
    RM_MODEL_RM_B_E,    ///< 标准版
    RM_MODEL_RM_ZF_E,   ///< 一维力版
    RM_MODEL_RM_SF_E,   ///< 六维力版
}rm_force_type_e;

/**
 * @brief 事件类型
 * @ingroup Init_Class
 */
typedef enum 
{
    RM_NONE_EVENT_E,    ///< 无事件
    RM_CURRENT_TRAJECTORY_STATE_E,      ///< 当前轨迹到位
    RM_PROGRAM_RUN_FINISH_E,        ///< 在线编程运行结束
} rm_event_type_e;

/**
 * @brief 事件信息
 * @ingroup Init_Class
 */
typedef struct 
{
    int handle_id;       ///< 返回消息的机械臂id
    rm_event_type_e event_type;     ///< 事件类型，包含无事件、当前轨迹到位、在线编程运行结束
    bool trajectory_state;      ///< 当前轨迹到位状态
    int device;     ///< 到位设备，0：关节 1：夹爪 2：灵巧手 3：升降机构 4：扩展关节 其他：保留
    int trajectory_connect;     ///< 是否连接下一条轨迹，0：全部到位，1：连接下一条轨迹
    int program_id;     ///< 运行结束的在线编程程序id
}rm_event_push_data_t;

/**
 * @brief 机械臂当前规划类型
 * 
 */
typedef enum 
{
    RM_NO_PLANNING_E,     ///< 无规划
    RM_JOINT_SPACE_PLANNING_E,        ///< 关节空间规划
    RM_CARTESIAN_LINEAR_PLANNING_E,   ///< 笛卡尔空间直线规划
    RM_CARTESIAN_ARC_PLANNING_E,      ///< 笛卡尔空间圆弧规划
    RM_SPLINE_CURVE_MOTION_PLANNING_E,      ///< 样条曲线运动规划
    RM_TRAJECTORY_REPLAY_PLANNING_E,  ///< 示教轨迹复现规划
}rm_arm_current_trajectory_e;


/**
 * @brief 机械臂主动上报接口配置
 * @ingroup UdpConfig
 */
typedef struct {
    int cycle;      ///< 广播周期，5ms的倍数
    bool enable;     ///< 使能，是否主动上报
    int port;       ///< 广播的端口号
    int force_coordinate;       ///< 系统外受力数据的坐标系，0为传感器坐标系 1为当前工作坐标系 2为当前工具坐标系（力传感器版本支持）
    char ip[28];       ///< 自定义的上报目标IP地址
} rm_realtime_push_config_t;

/**
 * @brief 四元数
 * 
 */
typedef struct
{
	float w;
	float x;
	float y;
	float z;
} rm_quat_t;

/**
 * @brief 位置坐标
 * 
 */
typedef struct
{
	float x; //* unit: m
	float y;
	float z;
} rm_position_t;

/**
 * @brief 欧拉角
 * 
 */
typedef struct
{
	float rx; //* unit: rad
	float ry;
	float rz;
} rm_euler_t;
/**
 * @brief 机械臂位置姿态结构体
 * @ingroup Algo
 */
typedef struct 
{
    rm_position_t position;     ///< 位置，单位：m
    rm_quat_t quaternion;       ///< 四元数
    rm_euler_t euler;           ///< 欧拉角，单位：rad
}rm_pose_t;

/**
 * @brief 坐标系名称
 * 不超过10个字符
 * @ingroup ToolCoordinateConfig
 * @ingroup WorkCoordinateConfig
 */
typedef struct 
{
    char name[12];
}rm_frame_name_t;


/**
 * @brief 坐标系
 * @ingroup Algo
 * @ingroup ToolCoordinateConfig
 * @ingroup WorkCoordinateConfig
 */
typedef struct 
{
    char frame_name[12];    ///< 坐标系名称
    rm_pose_t pose;         ///< 坐标系位姿
    float payload;      ///< 坐标系末端负载重量，单位：kg
    float x;    ///< 坐标系末端负载质心位置，单位：m
    float y;    ///< 坐标系末端负载质心位置，单位：m
    float z;    ///< 坐标系末端负载质心位置，单位：m
}rm_frame_t;

typedef struct{
    char build_time[20];    ///< 编译时间
    char version[10];       ///< 版本号
}rm_ctrl_version_t;

typedef struct{
    char model_version[5];      ///< 动力学模型版本号
}rm_dynamic_version_t;

typedef struct{
    char build_time[20];    ///<编译时间
    char version[10];       ///< 版本号
}rm_planinfo_t;

typedef struct {
    char version[20];   ///< 算法库版本号
}rm_algorithm_version_t;

/**
 * @brief  机械臂软件信息
 * 
 */
typedef struct
{
    char product_version[10];           ///< 机械臂型号
    rm_algorithm_version_t algorithm_info;      ///< 算法库信息
    rm_ctrl_version_t ctrl_info;        ///< ctrl 层软件信息
    rm_dynamic_version_t dynamic_info;      ///< 动力学版本
    rm_planinfo_t plan_info;        ///< plan 层软件信息
}rm_arm_software_version_t;

/**
 * @brief  机械臂当前状态
 * 
*/
typedef struct 
{
    rm_pose_t pose;         ///< 机械臂当前位姿
    float joint[ARM_DOF];   ///< 机械臂当前关节角度
    uint8_t arm_err;        ///< 机械臂错误代码
    uint8_t sys_err;        ///< 控制器错误代码
}rm_current_arm_state_t;

/**
 * @brief  机械臂关节状态参数
 * 
*/
typedef struct
{
    float joint_current[ARM_DOF];               ///< 关节电流，单位mA，精度：0.001mA
    bool joint_en_flag[ARM_DOF];                ///< 当前关节使能状态 ，1为上使能，0为掉使能
    uint16_t joint_err_code[ARM_DOF];           ///< 当前关节错误码
    float joint_position[ARM_DOF];              ///< 关节角度，单位°，精度：0.001°
    float joint_temperature[ARM_DOF];       ///< 当前关节温度，精度0.001℃
    float joint_voltage[ARM_DOF];       ///< 当前关节电压，精度0.001V
}rm_joint_status_t;

/**
 * @brief 位置示教方向
 * 
 */
typedef enum
{
    RM_X_DIR_E,        ///< 位置示教，x轴方向
    RM_Y_DIR_E,        ///< 位置示教，y轴方向
    RM_Z_DIR_E,        ///< 位置示教，z轴方向
}rm_pos_teach_type_e;

/**
 * @brief 姿态示教方向
 * 
 */
typedef enum
{
    RM_RX_ROTATE_E,        ///< 姿态示教，绕x轴旋转
    RM_RY_ROTATE_E,        ///< 姿态示教，绕y轴旋转
    RM_RZ_ROTATE_E,        ///< 姿态示教，绕z轴旋转
}rm_ort_teach_type_e;

/**
 * @brief 无线网络信息结构体
 * 
 */
typedef struct{
    int channel;               ///< 如果是 AP 模式，则存在此字段，标识 wifi 热点的物理信道号
    char ip[16];               ///< IP 地址
    char mac[18];              ///< MAC 地址
    char mask[16];             ///< 子网掩码
    char mode[5];              ///< ap 代表热点模式，sta 代表联网模式，off 代表未开启无线模式
    char password[16];         ///< 密码
    char ssid[32];             ///< 网络名称 (SSID)
}rm_wifi_net_t;

/**
 * @brief  机械臂所有状态参数
 * 
*/
typedef struct
{
    float joint_current[ARM_DOF];           ///< 关节电流，单位mA
    int joint_en_flag[ARM_DOF];            ///< 关节使能状态
    float joint_temperature[ARM_DOF];       ///< 关节温度,单位℃
    float joint_voltage[ARM_DOF];           ///< 关节电压，单位V
    int joint_err_code[ARM_DOF];            ///< 关节错误码
    int sys_err;                            ///< 机械臂错误代码
}rm_arm_all_state_t;

/**
 * @brief 夹爪状态
 * 
 */
typedef struct
{
    int enable_state;      ///< 夹爪使能标志，0 表示未使能，1 表示使能
    int status;            ///< 夹爪在线状态，0 表示离线， 1表示在线
    int error;              ///< 夹爪错误信息，低8位表示夹爪内部的错误信息bit5-7 保留bit4 内部通bit3 驱动器bit2 过流 bit1 过温bit0 堵转
    int mode;               ///< 当前工作状态：1 夹爪张开到最大且空闲，2 夹爪闭合到最小且空闲，3 夹爪停止且空闲，4 夹爪正在闭合，5 夹爪正在张开，6 夹爪闭合过程中遇到力控停止
    int current_force;      ///< 夹爪当前的压力，单位g
    int temperature;        ///< 当前温度，单位℃
    int actpos;             ///< 夹爪开口度
}rm_gripper_state_t;

/**
 * @brief  六维力传感器数据结构体
 * 
*/
typedef struct {
    float force_data[6];         ///< 当前力传感器原始数据，力的单位为N；力矩单位为Nm。
    float zero_force_data[6];        ///< 当前力传感器系统外受力数据，力的单位为N；力矩单位为Nm。
    float work_zero_force_data[6];     ///< 当前工作坐标系下系统外受力原始数据，力的单位为N；力矩单位为Nm。
    float tool_zero_force_data[6];     ///< 当前工具坐标系下系统外受力原始数据，力的单位为N；力矩单位为Nm。
} rm_force_data_t;

/**
 * @brief  一维力传感器数据结构体
 * 
*/
typedef struct {
    float Fz;         ///< 原始数据
    float zero_Fz;        ///< 传感器坐标系下系统外受力数据，力的单位为N；力矩单位为Nm。
    float work_zero_Fz;     ///< 当前工作坐标系下系统外受力原始数据，力的单位为N；力矩单位为Nm。
    float tool_zero_Fz;     ///< 当前工具坐标系下系统外受力原始数据，力的单位为N；力矩单位为Nm。
} rm_fz_data_t;

/**
 * @brief  外设数据读写参数结构体
 * 
*/
typedef struct {
    int port;       ///< 通讯端口，0-控制器RS485端口，1-末端接口板RS485接口，3-控制器ModbusTCP设备
    int address;    ///< 数据起始地址
    int device;     ///< 外设设备地址
    int num;        ///< 要读的数据的数量
} rm_peripheral_read_write_params_t;

/**
 * @brief  升降机构、扩展关节状态结构体
 * 
*/
typedef struct {
    int pos;        ///< 扩展关节角度，单位度，精度 0.001°(若为升降机构高度，则单位：mm，精度：1mm，范围：0 ~2300)
    int current;        ///< 驱动电流，单位：mA，精度：1mA
    int err_flag;       ///< 驱动错误代码，错误代码类型参考关节错误代码
    int mode;       ///< 当前状态，0-空闲，1-正方向速度运动，2-正方向位置运动，3-负方向速度运动，4-负方向位置运动
} rm_expand_state_t;

/**
 * @brief 文件下发
 * @ingroup OnlineProgramming
 */
typedef struct {
    char project_path[300];      ///< 下发文件路径文件名
    int project_path_len;   ///< 名称长度
    int plan_speed;     ///< 规划速度比例系数
    int only_save;      ///< 0-运行文件，1-仅保存文件，不运行
    int save_id;        ///< 保存到控制器中的编号
    int step_flag;      ///< 设置单步运行方式模式，1-设置单步模式 0-设置正常运动模式
    int auto_start;     ///< 设置默认在线编程文件，1-设置默认  0-设置非默认
    // int err_line;       ///< 若运行失败，该参数返回有问题的工程行数，err_line 为 0，则代表校验数据长度不对
} rm_send_project_t;

/**
 * @brief 在线编程存储信息
 * @ingroup OnlineProgramming
 */
typedef struct  {
    int id;     ///< 在线编程文件id
    int size;   ///< 文件大小
    int speed;  ///< 默认运行速度
    char trajectory_name[32];   ///< 文件名称
}rm_trajectory_data_t;
/**
 * @brief 查询在线编程列表
 * @ingroup OnlineProgramming
 */
typedef struct
{
    int page_num;       // 页码
    int page_size;       // 每页大小
    int list_size;   //返回总数量
    char vague_search[32];  // 模糊搜索
    rm_trajectory_data_t trajectory_list[100];   // 符合的在线编程列表
}rm_program_trajectorys_t;

/**
 * @brief 在线编程运行状态
 * @ingroup OnlineProgramming
 */
typedef struct
{
    int run_state;  ///< 运行状态 0 未开始 1运行中 2暂停中
    int id;         ///< 运行轨迹编号
    int edit_id;    ///< 上次编辑的在线编程编号 id
    int plan_num;   ///< 运行行数
    int total_loop;     ///< 循环指令数量
    int step_mode;      ///< 单步模式，1 为单步模式，0 为非单步模式
    int plan_speed;     ///< 全局规划速度比例 1-100
    int loop_num[100];        ///< 循环行数
    int loop_cont[100];       ///< 对应循环次数
}rm_program_run_state_t;

/**
 * @brief 全局路点存储信息
 * @ingroup OnlineProgramming
 */
typedef struct
{
    char point_name[20];    ///< 路点名称
    float joint[ARM_DOF];   ///< 关节角度
    rm_pose_t pose;     ///< 位姿信息
    char work_frame[12];    ///< 工作坐标系名称
    char tool_frame[12];    ///< 工具坐标系名称
    char time[50];      ///<  路点新增或修改时间
}rm_waypoint_t;
/**
 * @brief 全局路点列表
 * @ingroup OnlineProgramming
 */
typedef struct{
    int page_num;       ///< 页码
    int page_size;      ///< 每页大小
    int total_size;     ///< 列表长度
    char vague_search[32];  ///< 模糊搜索 
    int list_len;       ///<返回符合的全局路点列表长度
    rm_waypoint_t points_list[100];   ///< 返回符合的全局路点列表
}rm_waypoint_list_t;

/**
 * @brief 几何模型长方体参数
 * @ingroup Electronic_Fence
 */
typedef struct{
    float x_min_limit;      ///< 长方体基于世界坐标系 X 方向最小位置，单位 m
    float x_max_limit;      ///< 长方体基于世界坐标系 X 方向最大位置，单位 m
    float y_min_limit;      ///< 长方体基于世界坐标系 Y 方向最小位置，单位 m
    float y_max_limit;      ///< 长方体基于世界坐标系 Y 方向最大位置，单位 m
    float z_min_limit;      ///< 长方体基于世界坐标系 Z 方向最小位置，单位 m
    float z_max_limit;      ///< 长方体基于世界坐标系 Z 方向最大位置，单位 m
}rm_fence_config_cube_t;
/**
 * @brief 几何模型点面矢量平面参数
 * @ingroup Electronic_Fence
 */
typedef struct{
    float x1, y1, z1;       ///< 点面矢量平面三点法中的第一个点坐标，单位 m
    float x2, y2, z2;       ///< 点面矢量平面三点法中的第二个点坐标，单位 m
    float x3, y3, z3;       ///< 点面矢量平面三点法中的第三个点坐标，单位 m
}rm_fence_config_plane_t;
/**
 * @brief 几何模型球体参数
 * @ingroup Electronic_Fence
 */
typedef struct{
    float x;        ///< 表示球心在世界坐标系 X 轴的坐标，单位 m
    float y;        ///< 表示球心在世界坐标系 Y 轴的坐标，单位 m
    float z;        ///< 表示球心在世界坐标系 Z 轴的坐标，单位 m
    float radius;       ///< 表示半径，单位 m
}rm_fence_config_sphere_t;
/**
 * @brief 几何模型参数
 * @ingroup Electronic_Fence
 */
typedef struct{
    int form;       ///< 形状，1 表示长方体，2 表示点面矢量平面，3 表示球体
    char name[12];  ///< 电子围栏名称，不超过 10 个字节，支持字母、数字、下划线
    rm_fence_config_cube_t cube;    ///< 长方体参数
    rm_fence_config_plane_t plan;    ///< 点面矢量平面参数
    rm_fence_config_sphere_t sphere;    ///< 球体参数
}rm_fence_config_t;

/**
 * @brief 几何模型名称结构体
 * @ingroup Electronic_Fence
 */
typedef struct
{
    char name[12];    ///< 几何模型名称,不超过10个字符
}rm_fence_names_t;

/**
 * @brief 几何模型参数列表
 * @ingroup Electronic_Fence
 */
typedef struct
{
    rm_fence_config_t config[10];    
}rm_fence_config_list_t;
/**
 * @brief 包络球参数
 * 
 */
typedef struct{
    char name[12];            ///< 工具包络球体的名称，1-10 个字节，支持字母数字下划线
	float radius;           ///< 工具包络球体的半径，单位 m
    float x;        ///< 工具包络球体球心基于末端法兰坐标系的 X 轴坐标，单位 m
    float y;        ///< 工具包络球体球心基于末端法兰坐标系的 Y 轴坐标，单位 m
    float z;        ///< 工具包络球体球心基于末端法兰坐标系的 Z 轴坐标，单位 m
}rm_envelopes_ball_t;
/**
 * @brief 包络球参数集合
 * 
 */
typedef struct{
	rm_envelopes_ball_t balls[5];///< 包络参数列表，每个工具最多支持 5 个包络球，可以没有包络
    int size;   ///< 包络球数量
    char tool_name[12];///< 控制器中已存在的工具坐标系名称，如果不存在该字段，则为临时设置当前包络参数
}rm_envelope_balls_list_t;

/**
 * @brief 电子围栏/虚拟墙使能状态参数
 * 
 */
typedef struct
{
    bool enable_state;  ///< 电子围栏/虚拟墙使能状态，true 代表使能，false 代表禁使能
    int in_out_side;    ///< 0-机器人在电子围栏/虚拟墙内部，1-机器人在电子围栏外部
    int effective_region;   ///< 0-电子围栏针对整臂区域生效，1-虚拟墙针对末端生效
}rm_electronic_fence_enable_t;


/**
 * @brief  （UDP主动上报机械臂信息）力传感器数据结构体
 * 
*/
typedef struct {
    float force[6];         ///< 当前力传感器原始数据，0.001N或0.001Nm
    float zero_force[6];        ///< 当前力传感器系统外受力数据，0.001N或0.001Nm
    int coordinate;         ///< 系统外受力数据的坐标系，0为传感器坐标系 1为当前工作坐标系 2为当前工具坐标系
} rm_force_sensor_t;

/**
 * @brief  udp主动上报机械臂信息
 * 
*/
typedef struct 
{
    int errCode;        ///< 数据解析错误码，-3为数据解析错误，代表推送的数据不完整或格式不正确
    char arm_ip[16];       ///< 推送数据的机械臂的IP地址
    uint16_t arm_err;       ///< 机械臂错误码
    rm_joint_status_t joint_status;     ///< 关节状态
    rm_force_sensor_t force_sensor;       ///< 力数据（六维力或一维力版本支持）
    uint16_t sys_err;       ///< 系统错误码
    rm_pose_t waypoint;         ///< 当前路点信息
}rm_realtime_arm_joint_state_t; 

/**
 * @brief 逆解参数
 * @ingroup Algo
 */
typedef struct {
    float q_in[ARM_DOF];    ///< 上一时刻关节角度，单位°
    rm_pose_t q_pose;      ///< 目标位姿
    uint8_t flag;           ///< 姿态参数类别：0-四元数；1-欧拉角
} rm_inverse_kinematics_params_t;
/**
 * @brief 旋转矩阵
 * @ingroup Algo
 */
typedef struct
{
    short irow;
    short iline;
    float data[4][4];
} rm_matrix_t;
/**
 * @brief 机械臂事件回调函数
 * @ingroup Init_Class
 */
typedef void (*rm_event_callback_ptr)(rm_event_push_data_t data);
/**
 * @brief UDP机械臂状态主动上报回调函数
 * @ingroup Init_Class
 */
typedef void (*rm_realtime_arm_state_callback_ptr)(rm_realtime_arm_joint_state_t data);

/**
 * @brief 机械臂基本信息
 * @ingroup Init_Class
 */
typedef struct
{
    int arm_dof;    ///< 机械臂自由度
    rm_robot_arm_model_e arm_model;              ///< 机械臂型号
    rm_force_type_e force_type;                  ///< 末端力传感器版本
}rm_robot_info_t;

/**
 * @brief 机械臂控制句柄
 * @ingroup Init_Class
 */
typedef struct {
    int id;         ///< 句柄id，连接成功id大于0，连接失败返回-1
}rm_robot_handle;

#ifdef __cplusplus
}
#endif

#endif