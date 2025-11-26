
#ifndef __S_CURVE_GENERATOR_H_
#define __S_CURVE_GENERATOR_H_
#include"MotionDefine.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double* t;
    double* q;
    double* v;
    double* a;
    double* j;
    int path_num;
    double T;
} trajectory_segment;

typedef struct 
{
    double q;
    double v;
    double a;
    double j;
    double r_t;
} STMotionFrame;


/**
* @brief      释放轨迹点对应的内存
* @author     蒋宇航
*/
void free_trajectory_segment(trajectory_segment* traj);

/**
* @brief      两点间s速度曲线（也称七段式轨迹）实现（考虑对称约束）
*             加加速->匀加速->减加速->匀速->加减速->匀减速->减减速
* @author     蒋宇航
* @version    1.0
* @param[in]  q0       - 起始位置
* @param[in]  q1       - 目标位置
* @param[in]  v0       - 起始速度
* @param[in]  v1       - 目标速度
* @param[in]  v_max    - 允许的最大速度
* @param[in]  a_max    - 允许的最大加速度
* @param[in]  j_max    - 允许的最大加加速度
* @param[in]  t_start  - 起始时间
* @param[in]  dt       - 控制周期
* @return     [t, q, v, a, j, path_num, T]  - (时间序列->位置->速度->加速度->加加速度->规划所得轨迹点个数->规划总时间)
*/
trajectory_segment s_curve_generator(double q0, double q1, double v0, double v1, double v_max, double a_max, double j_max, double t_start, double dt);

/**
* @brief      多点间实现S型加减速规划
* @author     蒋宇航
* @version    1.0
* @param[in]  q_points(1xN) - 位置向量
* @param[in]  v_points(1xN) - 速度向量
* @param[in]  v_max         - 允许的最大速度
* @param[in]  a_max         - 允许的最大加速度
* @param[in]  j_max         - 允许的最大加加速度
* @param[in]  start_time    - 起始时间
* @param[in]  dt            - 控制周期
* @param[in]  N             - 对应多点间实现S型加减速规划中的给定输入点个数，即q_points、v_points数组大小
* @return     [t, q, v, a, j, path_num, T]  - (时间序列->位置->速度->加速度->加加速度->规划所得轨迹点个数->规划总时间)
*/
trajectory_segment multi_s_curve_generator(double* q_points, double *v_points, double v_max, double a_max, double j_max, double start_time, double dt, int N);

/**
* @brief      过任意给定路径点的S型加减速规划(仅需要指定起始速度、终止速度，自动计算中间速度)
* @author     蒋宇航
* @version    1.0
* @param[in]  q_points(1xN) - 位置向量
* @param[in]  v_start       - 起始速度
* @param[in]  v_end         - 终止速度
* @param[in]  v_max         - 允许的最大速度
* @param[in]  a_max         - 允许的最大加速度
* @param[in]  j_max         - 允许的最大加加速度
* @param[in]  start_time    - 起始时间
* @param[in]  dt            - 控制周期
* @param[in]  N             - 对应q_points数组大小
* @return     [t, q, v, a, j, path_num, T]  - (时间序列->位置->速度->加速度->加加速度->规划所得轨迹点个数->规划总时间)
*/
trajectory_segment multi_s_curve_generator_based_on_path(double* q_points, double v_start, double v_end, double v_max, double a_max, double j_max, double start_time, double dt, int N);

/**
* @brief      两点间s速度曲线（也称七段式轨迹）实现（考虑对称约束）
*             加加速->匀加速->减加速->匀速->加减速->匀减速->减减速
* @author     蒋宇航
* @version    1.0
* @param[in]  q0       - 起始位置
* @param[in]  q1       - 目标位置
* @param[in]  v0       - 起始速度
* @param[in]  v1       - 目标速度
* @param[in]  v_max    - 允许的最大速度
* @param[in]  a_max    - 允许的最大加速度
* @param[in]  j_max    - 允许的最大加加速度
* @param[in]  t_start  - 起始时间
* @param[in]  dt       - 控制周期
* @param[in]  FrameTime- 当前时间
* @return     [t, q, v, a, j, path_num, T]  - (时间序列->位置->速度->加速度->加加速度->规划所得轨迹点个数->规划总时间)
*/
STMotionFrame s_curve_generator_RT(double q0, double q1, double v0, double v1, double v_max, double a_max, double j_max, double t_start, double dt,double FrameTime);


int Trapezoid_plan(ST_PlanParams stsetParam, ST_PlanParams& stActParam, ST_PlanData& trackData);
int Trapezoid_Inter(ST_PlanParams stActParam, ST_PlanData trackData, double t, ST_InterParams& stData);

int S_curve_plan(ST_PlanParams stsetParam, ST_PlanParams& stActParam, ST_PlanData& trackData);
int S_curve_Inter(ST_PlanParams stActParam, ST_PlanData trackData, double t, ST_InterParams& stData);

int FifteenSeg_plan(ST_PlanParams stsetParam, ST_PlanParams& stActParam, ST_PlanData& trackData);
int FifteenSeg_Inter(ST_PlanParams stActParam, ST_PlanData trackData, double t, ST_InterParams& stData);
/**
 * @brief 停止规划
 * 周期调用
 * 本函数用于执行运动过程中被中断进行停止规划，默认降到速度为0。
 * 根据是否有加加速度决定T型降速还是7段S降速
 * @param q0      [in]   当前位置
 * @param v0      [in]   当前速度
 * @param a0      [in]   当前加速度
 * @param A_max   [in]   最大减速度
 * @param J_max   [in]   最大加加速度
 * @param t       [in]   采样时间
 * @param T       [out]  停止总时间
 * @param stData  [out]  输出运动数据
 *
 * @return err   0，计算正常输出
 * @note 调用方必须检查返回值，以确保结果有效。
 */

int stopmotion(double q0, double v0, double a0, double A_max, double J_max, double t,double& T,ST_InterParams& stData);
#endif
