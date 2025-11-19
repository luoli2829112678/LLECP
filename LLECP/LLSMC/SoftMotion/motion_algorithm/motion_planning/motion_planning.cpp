#include"motion_planning.h"

// 用于控制内存申请，设置允许的最大路径点个数
#define MAX_PATH_NUM_ALLOWED 100000
#define ITERATIVESTEPS 0.00001

void free_trajectory_segment(trajectory_segment* traj) {
    if (traj->t != NULL) {
        free(traj->t);
        traj->t = NULL;
    }

    if (traj->q != NULL) {
        free(traj->q);
        traj->q = NULL;
    }

    if (traj->v != NULL) {
        free(traj->v);
        traj->v = NULL;
    }

    if (traj->a != NULL) {
        free(traj->a);
        traj->a = NULL;
    }

    if (traj->j != NULL) {
        free(traj->j);
        traj->j = NULL;
    }
}

STMotionFrame s_curve_generator_RT(double q0, double q1, double v0, double v1, double v_max, double a_max, double j_max, double t_start, double dt,double FrameTime)
{
    double v_min, a_min, j_min, v_max_origin, v_min_origin, a_max_origin, a_min_origin, j_max_origin, j_min_origin, v_m;
    int direction, n;
    double T_1, T_2, T_3, T_4, T_5, T_6, T_7, T_j1, T_j2, T_j, T_a, T_v, T_d;
    double t1, t2, t3, t4, t5, t6, t7;
    double delta, step, cur_t;
    STMotionFrame stMotionFrame;
    double cur_start_time, last_v, last_q;

    // 数据有效性判断
    if (abs(v0) > v_max) {
        printf("给定的起始速度超出可行速度范围！！！");
    }

    if (abs(v1) > v_max) {
        printf("给定的目标速度超出可行速度范围！！！");
    }

    v_min = -v_max;
    a_min = -a_max;
    j_min = -j_max;

    // 输入归一化处理
    v_max_origin = v_max;
    v_min_origin = v_min;
    a_max_origin = a_max;
    a_min_origin = a_min;
    j_max_origin = j_max;
    j_min_origin = j_min;

    direction = ((q1 - q0) > 0) ? 1 : -1;
    q0 = direction * q0;
    q1 = direction * q1;
    v0 = direction * v0;
    v1 = direction * v1;

    v_max = (direction + 1) / 2 * v_max_origin + (direction - 1) / 2 * v_min_origin;
    v_min = (direction + 1) / 2 * v_min_origin + (direction - 1) / 2 * v_max_origin;
    a_max = (direction + 1) / 2 * a_max_origin + (direction - 1) / 2 * a_min_origin;
    a_min = (direction + 1) / 2 * a_min_origin + (direction - 1) / 2 * a_max_origin;
    j_max = (direction + 1) / 2 * j_max_origin + (direction - 1) / 2 * j_min_origin;
    j_min = (direction + 1) / 2 * j_min_origin + (direction - 1) / 2 * j_max_origin;

    if ((v_max - v0) * j_max < a_max * a_max) {
        T_j1 = sqrt((v_max - v0) / j_max);
        T_a = 2 * T_j1;
    }
    else {
        T_j1 = a_max / j_max;
        T_a = T_j1 + (v_max - v0) / a_max;
    }

    if ((v_max - v1) * j_max < a_max * a_max) {
        T_j2 = sqrt((v_max - v1) / j_max);
        T_d = 2 * T_j2;
    }
    else {
        T_j2 = a_max / j_max;
        T_d = T_j2 + (v_max - v1) / a_max;
    }

    T_v = (q1 - q0) / v_max - T_a / 2 * (1 + v0 / v_max) - T_d / 2 * (1 + v1 / v_max);

    if (T_v >= 0) {
        // 最大速度可达
        v_m = v_max;
        //printf("最大可行速度可达, 最大速度: [%f]\n", v_m);
        T_1 = T_j1;
        T_2 = T_a - 2 * T_j1;
        T_3 = T_j1;
        T_4 = T_v;
        T_5 = T_j2;
        T_6 = T_d - 2 * T_j2;
        T_7 = T_j2;
    } else {
        // 最大速度不可达
        //printf("最大可行速度不可达\n");
        T_j1 = a_max / j_max;
        T_j2 = a_max / j_max;
        T_j = T_j1;
        delta = pow(a_max, 4) / (j_max * j_max) + 2 * (v0 * v0 + v1 * v1) + a_max * (4 * (q1 - q0) - 2 * a_max / j_max * (v0 + v1));
        T_a = (a_max * a_max / j_max - 2 * v0 + sqrt(delta)) / (2 * a_max);
        T_d = (a_max * a_max / j_max - 2 * v1 + sqrt(delta)) / (2 * a_max);
        T_v = 0;

        T_1 = T_j1;
        T_2 = T_a - 2 * T_j1;
        T_3 = T_j1;
        T_4 = T_v;
        T_5 = T_j2;
        T_6 = T_d - 2 * T_j2;
        T_7 = T_j2;

        if ((T_a >= 2 * T_j) && (T_d >= 2 * T_j)) {
            v_m = v0 + j_max * T_j1 * T_j1 + j_max * T_j1 * T_2;
            //printf("最大速度: [%f]\n", v_m);
        }
        else {
            //printf("递归计算可达到的最大加速度\n");          
            step = ITERATIVESTEPS;
            for (double i = 1 - step; i = i - step; i >= step) {
                double temp = i * a_max;
                T_j = temp / j_max;
                delta = pow(temp, 4) / (j_max * j_max) + 2 * (v0 * v0 + v1 * v1) + temp * (4 * (q1 - q0) - 2 * temp / j_max * (v0 + v1));
                T_a = (temp * temp / j_max - 2 * v0 + sqrt(delta)) / (2 * temp);
                T_d = (temp * temp / j_max - 2 * v1 + sqrt(delta)) / (2 * temp);
                if ((T_a >= 2 * T_j) && (T_d >= 2 * T_j)) {
                    T_1 = T_j;
                    T_2 = T_a - 2 * T_j;
                    T_3 = T_j;
                    T_4 = 0;
                    T_5 = T_j;
                    T_6 = T_d - 2 * T_j;
                    T_7 = T_j;

                    v_m = v0 + j_max * T_j * T_j + j_max * T_j * T_2;
                    //printf("最大加速度不可达, 最大速度: %f\n", v_m);
                    break;
                }
                else if ((T_a < 0) && (v0 > v1)) {
                    //printf("无加速段，仅单一减速段\n");
                    T_a = 0;
                    T_d = 2 * (q1 - q0) / (v1 + v0);
                    T_j2 = (j_max * (q1 - q0) - sqrt(j_max * (j_max * (q1 - q0) * (q1 - q0) + (v1 + v0) * (v1 + v0) * (v1 - v0)))) / (j_max * (v1 + v0));

                    T_1 = 0;
                    T_2 = 0;
                    T_3 = 0;
                    T_4 = 0;
                    T_5 = T_j2;
                    T_6 = T_d - 2 * T_j2;
                    T_7 = T_j2;

                    v_m = v0;
                    //printf("最大速度:[%f]\n", v_m);
                    break;
                }
                else if ((T_d < 0) && (v0 < v1)) {
                    //printf("无减速段，仅单一加速段\n");
                    T_d = 0;
                    T_a = 2 * (q1 - q0) / (v1 + v0);
                    T_j1 = (j_max * (q1 - q0) - sqrt(j_max * (j_max * (q1 - q0) * (q1 - q0) - (v1 + v0) * (v1 + v0) * (v1 - v0)))) / (j_max * (v1 + v0));

                    T_1 = T_j1;
                    T_2 = T_a - 2 * T_j1;
                    T_3 = T_j1;
                    T_4 = 0;
                    T_5 = 0;
                    T_6 = 0;
                    T_7 = 0;

                    v_m = v0 + j_max * T_j1 * T_j1 + j_max * T_j1 * T_2;
                    //printf("最大速度: [% f] \n", v_m);
                    break;
                }
            }
        }
    }

    // 总时间
    double T = T_a + T_v + T_d;

    // 时间点划分
    t1 = t_start + T_1;
    t2 = t1 + T_2;
    t3 = t2 + T_3;
    t4 = t3 + T_4;
    t5 = t4 + T_5;
    t6 = t5 + T_6;
    t7 = t6 + T_7;
    stMotionFrame.r_t = t7 - FrameTime;
    // 生成时间序列
    n = (int)(ceil((t7 - t_start) / dt)) + 1;
    last_v = v0;
    last_q = q0;
    cur_t = FrameTime;
    if ((cur_t <= t1) && (T_1 > 0)) {
        cur_start_time = t_start;
        last_v = v0;
        last_q = q0;
        // 加加速阶段
        stMotionFrame.j = j_max;
        stMotionFrame.a = j_max * (cur_t - cur_start_time);
        stMotionFrame.v = last_v + (j_max * (cur_t - cur_start_time) * (cur_t - cur_start_time)) / 2;
        stMotionFrame.q = last_q + ((cur_t - cur_start_time) * (j_max * cur_t * cur_t - 2 * j_max * cur_t * cur_start_time + j_max * cur_start_time * cur_start_time + 6 * last_v)) / 6;
    }
    else if ((cur_t <= t2) && (T_2 > 0)) {
        cur_start_time = t_start + T_1;
        last_v = v0 + (j_max * T_1 * T_1) / 2;
        last_q = q0 + ((T_1) * (j_max * (t_start + T_1) * (t_start + T_1) - 2 * j_max * (t_start + T_1) * t_start + j_max * t_start * t_start + 6 * v0)) / 6;
        // 匀加速阶段
        stMotionFrame.j = 0;
        stMotionFrame.a = j_max * T_1;
        stMotionFrame.v = last_v + T_1 * j_max * (cur_t - cur_start_time);
        stMotionFrame.q = last_q + ((cur_t - cur_start_time) * (2 * last_v + T_1 * cur_t * j_max - T_1 * cur_start_time * j_max)) / 2;
    }
    else if ((cur_t <= t3) && (T_3 > 0)) {
        cur_start_time = t_start + T_1 + T_2;
        last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0;
        last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + v0 * T_1 + v0 * T_2 + q0;
        // 减加速阶段
        stMotionFrame.j = -j_max;
        stMotionFrame.a = j_max * T_1 - j_max * (cur_t - cur_start_time);
        stMotionFrame.v = last_v + (j_max * (cur_t - cur_start_time) * (2 * T_1 - cur_t + cur_start_time)) / 2;
        stMotionFrame.q = last_q + ((cur_t - cur_start_time) * (-j_max * cur_t * cur_t + 2 * j_max * cur_t * cur_start_time + 3 * T_1 * j_max * cur_t - j_max * cur_start_time * cur_start_time - 3 * T_1 * j_max * cur_start_time + 6 * last_v)) / 6;
    }
    else if ((cur_t <= t4) && (T_4 > 0)) {
        cur_start_time = t_start + T_1 + T_2 + T_3;
        last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2;
        last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + (j_max * T_1 * T_3 * T_3) / 2 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 + v0 * T_3 + q0;
        // 匀速阶段
        stMotionFrame.j = 0;
        stMotionFrame.a = 0;
        stMotionFrame.v = last_v;
        stMotionFrame.q = last_q + last_v * (cur_t - cur_start_time);
    }
    else if ((cur_t <= t5) && (T_5 > 0)) {
        cur_start_time = t_start + T_1 + T_2 + T_3 + T_4;
        last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2;
        last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (T_4 * j_max * T_1 * T_1) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + T_4 * j_max * T_1 * T_2 + (j_max * T_1 * T_3 * T_3) / 2 + T_4 * j_max * T_1 * T_3 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 - (T_4 * j_max * T_3 * T_3) / 2 + v0 * T_3 + q0 + T_4 * v0;
        // 加减速阶段
        stMotionFrame.j = j_min;
        stMotionFrame.a = j_min * (cur_t - cur_start_time);
        stMotionFrame.v = last_v + (j_min * (cur_t - cur_start_time) * (cur_t - cur_start_time)) / 2;
        stMotionFrame.q = last_q + ((cur_t - cur_start_time) * (j_min * cur_t * cur_t - 2 * j_min * cur_t * cur_start_time + j_min * cur_start_time * cur_start_time + 6 * last_v)) / 6;
    }
    else if ((cur_t <= t6) && (T_6 > 0)) {
        cur_start_time = t_start + T_1 + T_2 + T_3 + T_4 + T_5;
        last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2 + (j_min * T_5 * T_5) / 2;
        last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (j_max * T_1 * T_1 * T_5) / 2 + (T_4 * j_max * T_1 * T_1) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + j_max * T_1 * T_2 * T_5 + T_4 * j_max * T_1 * T_2 + (j_max * T_1 * T_3 * T_3) / 2 + j_max * T_1 * T_3 * T_5 + T_4 * j_max * T_1 * T_3 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 - (j_max * T_3 * T_3 * T_5) / 2 - (T_4 * j_max * T_3 * T_3) / 2 + v0 * T_3 + (j_min * pow(T_5, 3)) / 6 + v0 * T_5 + q0 + T_4 * v0;
        // 匀减速阶段
        stMotionFrame.j = 0;
        stMotionFrame.a = j_min * T_5;
        stMotionFrame.v = last_v + T_5 * j_min * (cur_t - cur_start_time);
        stMotionFrame.q = last_q + ((cur_t - cur_start_time) * (2 * last_v + T_5 * cur_t * j_min - T_5 * cur_start_time * j_min)) / 2;
    }
    else if ((T_7 > 0)) {
        cur_start_time = t_start + T_1 + T_2 + T_3 + T_4 + T_5 + T_6;
        last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2 + (j_min * T_5 * T_5) / 2 + T_5 * j_min * T_6;
        last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (j_max * T_1 * T_1 * T_5) / 2 + (j_max * T_1 * T_1 * T_6) / 2 + (T_4 * j_max * T_1 * T_1) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + j_max * T_1 * T_2 * T_5 + j_max * T_1 * T_2 * T_6 + T_4 * j_max * T_1 * T_2 + (j_max * T_1 * T_3 * T_3) / 2 + j_max * T_1 * T_3 * T_5 + j_max * T_1 * T_3 * T_6 + T_4 * j_max * T_1 * T_3 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 - (j_max * T_3 * T_3 * T_5) / 2 - (j_max * T_3 * T_3 * T_6) / 2 - (T_4 * j_max * T_3 * T_3) / 2 + v0 * T_3 + (j_min * pow(T_5, 3)) / 6 + (j_min * T_5 * T_5 * T_6) / 2 + (j_min * T_5 * T_6 * T_6) / 2 + v0 * T_5 + v0 * T_6 + q0 + T_4 * v0;
        // 减减速阶段
        stMotionFrame.j = -j_min;
        stMotionFrame.a = j_min * T_5 - j_min * (cur_t - cur_start_time);
        stMotionFrame.v = last_v + (j_min * (cur_t - cur_start_time) * (2 * T_5 - cur_t + cur_start_time)) / 2;
        stMotionFrame.q = last_q + ((cur_t - cur_start_time) * (-j_min * cur_t * cur_t + 2 * j_min * cur_t * cur_start_time + 3 * T_5 * j_min * cur_t - j_min * cur_start_time * cur_start_time - 3 * T_5 * j_min * cur_start_time + 6 * last_v)) / 6;
    }
    stMotionFrame.j = direction * stMotionFrame.j;
    stMotionFrame.a = direction * stMotionFrame.a;
    stMotionFrame.v = direction * stMotionFrame.v;
    stMotionFrame.q = direction * stMotionFrame.q;
    return stMotionFrame;
}


trajectory_segment s_curve_generator(double q0, double q1, double v0, double v1, double v_max, double a_max, double j_max, double t_start, double dt) {
    double v_min, a_min, j_min, v_max_origin, v_min_origin, a_max_origin, a_min_origin, j_max_origin, j_min_origin, v_m;
    int direction, n;
    double T_1, T_2, T_3, T_4, T_5, T_6, T_7, T_j1, T_j2, T_j, T_a, T_v, T_d;
    double t1, t2, t3, t4, t5, t6, t7;
    double delta, step, cur_t;
    trajectory_segment res;
    double cur_start_time, last_v, last_q;

    // 数据有效性判断
    if (abs(v0) > v_max) {
        printf("给定的起始速度超出可行速度范围！！！");
    }

    if (abs(v1) > v_max) {
        printf("给定的目标速度超出可行速度范围！！！");
    }

    v_min = -v_max;
    a_min = -a_max;
    j_min = -j_max;

    // 输入归一化处理
    v_max_origin = v_max;
    v_min_origin = v_min;
    a_max_origin = a_max;
    a_min_origin = a_min;
    j_max_origin = j_max;
    j_min_origin = j_min;

    direction = ((q1 - q0) > 0) ? 1 : -1;
    q0 = direction * q0;
    q1 = direction * q1;
    v0 = direction * v0;
    v1 = direction * v1;

    v_max = (direction + 1) / 2 * v_max_origin + (direction - 1) / 2 * v_min_origin;
    v_min = (direction + 1) / 2 * v_min_origin + (direction - 1) / 2 * v_max_origin;
    a_max = (direction + 1) / 2 * a_max_origin + (direction - 1) / 2 * a_min_origin;
    a_min = (direction + 1) / 2 * a_min_origin + (direction - 1) / 2 * a_max_origin;
    j_max = (direction + 1) / 2 * j_max_origin + (direction - 1) / 2 * j_min_origin;
    j_min = (direction + 1) / 2 * j_min_origin + (direction - 1) / 2 * j_max_origin;

    /**
    * v_m:   运动过程中的最大速度
    * T_j1 : 加速段中加加速度恒定（j_max或j_min）恒定的时长
    * T_j2 : 减速段中加加速度恒定（j_max或j_min）恒定的时长
    * T_a :  加速阶段时长
    * T_v :  匀速阶段时长
    * T_d :  减速阶段时长
    * T :    轨迹总时长（T_a + T_v + T_d）
    */

    if ((v_max - v0) * j_max < a_max * a_max) {
        T_j1 = sqrt((v_max - v0) / j_max);
        T_a = 2 * T_j1;
    }
    else {
        T_j1 = a_max / j_max;
        T_a = T_j1 + (v_max - v0) / a_max;
    }

    if ((v_max - v1) * j_max < a_max * a_max) {
        T_j2 = sqrt((v_max - v1) / j_max);
        T_d = 2 * T_j2;
    }
    else {
        T_j2 = a_max / j_max;
        T_d = T_j2 + (v_max - v1) / a_max;
    }

    T_v = (q1 - q0) / v_max - T_a / 2 * (1 + v0 / v_max) - T_d / 2 * (1 + v1 / v_max);

    if (T_v >= 0) {
        // 最大速度可达
        v_m = v_max;
        printf("最大可行速度可达, 最大速度: [%f]\n", v_m);
        T_1 = T_j1;
        T_2 = T_a - 2 * T_j1;
        T_3 = T_j1;
        T_4 = T_v;
        T_5 = T_j2;
        T_6 = T_d - 2 * T_j2;
        T_7 = T_j2;
    } else {
        // 最大速度不可达
        printf("最大可行速度不可达\n");
        T_j1 = a_max / j_max;
        T_j2 = a_max / j_max;
        T_j = T_j1;
        delta = pow(a_max, 4) / (j_max * j_max) + 2 * (v0 * v0 + v1 * v1) + a_max * (4 * (q1 - q0) - 2 * a_max / j_max * (v0 + v1));
        T_a = (a_max * a_max / j_max - 2 * v0 + sqrt(delta)) / (2 * a_max);
        T_d = (a_max * a_max / j_max - 2 * v1 + sqrt(delta)) / (2 * a_max);
        T_v = 0;

        T_1 = T_j1;
        T_2 = T_a - 2 * T_j1;
        T_3 = T_j1;
        T_4 = T_v;
        T_5 = T_j2;
        T_6 = T_d - 2 * T_j2;
        T_7 = T_j2;

        if ((T_a >= 2 * T_j) && (T_d >= 2 * T_j)) {
            v_m = v0 + j_max * T_j1 * T_j1 + j_max * T_j1 * T_2;
            printf("最大速度: [%f]\n", v_m);
        }
        else {
            printf("递归计算可达到的最大加速度\n");
            step = ITERATIVESTEPS;
            for (double i = 1 - step; i = i - step; i >= step) {
                double temp = i * a_max;
                T_j = temp / j_max;
                delta = pow(temp, 4) / (j_max * j_max) + 2 * (v0 * v0 + v1 * v1) + temp * (4 * (q1 - q0) - 2 * temp / j_max * (v0 + v1));
                T_a = (temp * temp / j_max - 2 * v0 + sqrt(delta)) / (2 * temp);
                T_d = (temp * temp / j_max - 2 * v1 + sqrt(delta)) / (2 * temp);
                if ((T_a >= 2 * T_j) && (T_d >= 2 * T_j)) {
                    T_1 = T_j;
                    T_2 = T_a - 2 * T_j;
                    T_3 = T_j;
                    T_4 = 0;
                    T_5 = T_j;
                    T_6 = T_d - 2 * T_j;
                    T_7 = T_j;

                    v_m = v0 + j_max * T_j * T_j + j_max * T_j * T_2;
                    printf("最大加速度不可达, 最大速度: %f\n", v_m);
                    break;
                }
                else if ((T_a < 0) && (v0 > v1)) {
                    printf("无加速段，仅单一减速段\n");
                    T_a = 0;
                    T_d = 2 * (q1 - q0) / (v1 + v0);
                    T_j2 = (j_max * (q1 - q0) - sqrt(j_max * (j_max * (q1 - q0) * (q1 - q0) + (v1 + v0) * (v1 + v0) * (v1 - v0)))) / (j_max * (v1 + v0));

                    T_1 = 0;
                    T_2 = 0;
                    T_3 = 0;
                    T_4 = 0;
                    T_5 = T_j2;
                    T_6 = T_d - 2 * T_j2;
                    T_7 = T_j2;

                    v_m = v0;
                    printf("最大速度:[%f]\n", v_m);
                    break;
                }
                else if ((T_d < 0) && (v0 < v1)) {
                    printf("无减速段，仅单一加速段\n");
                    T_d = 0;
                    T_a = 2 * (q1 - q0) / (v1 + v0);
                    T_j1 = (j_max * (q1 - q0) - sqrt(j_max * (j_max * (q1 - q0) * (q1 - q0) - (v1 + v0) * (v1 + v0) * (v1 - v0)))) / (j_max * (v1 + v0));

                    T_1 = T_j1;
                    T_2 = T_a - 2 * T_j1;
                    T_3 = T_j1;
                    T_4 = 0;
                    T_5 = 0;
                    T_6 = 0;
                    T_7 = 0;

                    v_m = v0 + j_max * T_j1 * T_j1 + j_max * T_j1 * T_2;
                    printf("最大速度: [% f] \n", v_m);
                    break;
                }
            }
        }
    }

    // 总时间
    res.T = T_a + T_v + T_d;

    // 时间点划分
    t1 = t_start + T_1;
    t2 = t1 + T_2;
    t3 = t2 + T_3;
    t4 = t3 + T_4;
    t5 = t4 + T_5;
    t6 = t5 + T_6;
    t7 = t6 + T_7;

    // 生成时间序列
    n = (int)(ceil((t7 - t_start) / dt)) + 1;

    res.t = (double*)malloc(n * sizeof(double));
    if (res.t == NULL) {
        printf("内存申请失败\n");
        return res;
    }

    for (int i = 0; i < n; i++) {
        res.t[i] = t_start + i * dt;
    }

    // 初始化输出
    res.q = (double*)malloc(n * sizeof(double));
    res.v = (double*)malloc(n * sizeof(double));
    res.a = (double*)malloc(n * sizeof(double));
    res.j = (double*)malloc(n * sizeof(double));

    res.path_num = n;

    // cur_start_time:  当前阶段的起始时刻
    // last_v : 上一阶段的末速度，也即当前阶段的起始速度
    // last_q : 上一阶段的末位置，也即当前阶段的起始位置

    last_v = v0;
    last_q = q0;
    // 分段计算轨迹
    for (int i = 0; i < n; i++) {
        cur_t = res.t[i];
        if ((cur_t <= t1) && (T_1 > 0)) {
            cur_start_time = t_start;
            last_v = v0;
            last_q = q0;
            // 加加速阶段
            res.j[i] = j_max;
            res.a[i] = j_max * (cur_t - cur_start_time);
            res.v[i] = last_v + (j_max * (cur_t - cur_start_time) * (cur_t - cur_start_time)) / 2;
            res.q[i] = last_q + ((cur_t - cur_start_time) * (j_max * cur_t * cur_t - 2 * j_max * cur_t * cur_start_time + j_max * cur_start_time * cur_start_time + 6 * last_v)) / 6;
        }
        else if ((cur_t <= t2) && (T_2 > 0)) {
            cur_start_time = t_start + T_1;
            last_v = v0 + (j_max * T_1 * T_1) / 2;
            last_q = q0 + ((T_1) * (j_max * (t_start + T_1) * (t_start + T_1) - 2 * j_max * (t_start + T_1) * t_start + j_max * t_start * t_start + 6 * v0)) / 6;
            // 匀加速阶段
            res.j[i] = 0;
            res.a[i] = j_max * T_1;
            res.v[i] = last_v + T_1 * j_max * (cur_t - cur_start_time);
            res.q[i] = last_q + ((cur_t - cur_start_time) * (2 * last_v + T_1 * cur_t * j_max - T_1 * cur_start_time * j_max)) / 2;
        }
        else if ((cur_t <= t3) && (T_3 > 0)) {
            cur_start_time = t_start + T_1 + T_2;
            last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0;
            last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + v0 * T_1 + v0 * T_2 + q0;
            // 减加速阶段
            res.j[i] = -j_max;
            res.a[i] = j_max * T_1 - j_max * (cur_t - cur_start_time);
            res.v[i] = last_v + (j_max * (cur_t - cur_start_time) * (2 * T_1 - cur_t + cur_start_time)) / 2;
            res.q[i] = last_q + ((cur_t - cur_start_time) * (-j_max * cur_t * cur_t + 2 * j_max * cur_t * cur_start_time + 3 * T_1 * j_max * cur_t - j_max * cur_start_time * cur_start_time - 3 * T_1 * j_max * cur_start_time + 6 * last_v)) / 6;
        }
        else if ((cur_t <= t4) && (T_4 > 0)) {
            cur_start_time = t_start + T_1 + T_2 + T_3;
            last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2;
            last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + (j_max * T_1 * T_3 * T_3) / 2 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 + v0 * T_3 + q0;
            // 匀速阶段
            res.j[i] = 0;
            res.a[i] = 0;
            res.v[i] = last_v;
            res.q[i] = last_q + last_v * (cur_t - cur_start_time);
        }
        else if ((cur_t <= t5) && (T_5 > 0)) {
            cur_start_time = t_start + T_1 + T_2 + T_3 + T_4;
            last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2;
            last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (T_4 * j_max * T_1 * T_1) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + T_4 * j_max * T_1 * T_2 + (j_max * T_1 * T_3 * T_3) / 2 + T_4 * j_max * T_1 * T_3 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 - (T_4 * j_max * T_3 * T_3) / 2 + v0 * T_3 + q0 + T_4 * v0;
            // 加减速阶段
            res.j[i] = j_min;
            res.a[i] = j_min * (cur_t - cur_start_time);
            res.v[i] = last_v + (j_min * (cur_t - cur_start_time) * (cur_t - cur_start_time)) / 2;
            res.q[i] = last_q + ((cur_t - cur_start_time) * (j_min * cur_t * cur_t - 2 * j_min * cur_t * cur_start_time + j_min * cur_start_time * cur_start_time + 6 * last_v)) / 6;
        }
        else if ((cur_t <= t6) && (T_6 > 0)) {
            cur_start_time = t_start + T_1 + T_2 + T_3 + T_4 + T_5;
            last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2 + (j_min * T_5 * T_5) / 2;
            last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (j_max * T_1 * T_1 * T_5) / 2 + (T_4 * j_max * T_1 * T_1) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + j_max * T_1 * T_2 * T_5 + T_4 * j_max * T_1 * T_2 + (j_max * T_1 * T_3 * T_3) / 2 + j_max * T_1 * T_3 * T_5 + T_4 * j_max * T_1 * T_3 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 - (j_max * T_3 * T_3 * T_5) / 2 - (T_4 * j_max * T_3 * T_3) / 2 + v0 * T_3 + (j_min * pow(T_5, 3)) / 6 + v0 * T_5 + q0 + T_4 * v0;
            // 匀减速阶段
            res.j[i] = 0;
            res.a[i] = j_min * T_5;
            res.v[i] = last_v + T_5 * j_min * (cur_t - cur_start_time);
            res.q[i] = last_q + ((cur_t - cur_start_time) * (2 * last_v + T_5 * cur_t * j_min - T_5 * cur_start_time * j_min)) / 2;
        }
        else if ((T_7 > 0)) {
            cur_start_time = t_start + T_1 + T_2 + T_3 + T_4 + T_5 + T_6;
            last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2 + (j_min * T_5 * T_5) / 2 + T_5 * j_min * T_6;
            last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (j_max * T_1 * T_1 * T_5) / 2 + (j_max * T_1 * T_1 * T_6) / 2 + (T_4 * j_max * T_1 * T_1) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + j_max * T_1 * T_2 * T_5 + j_max * T_1 * T_2 * T_6 + T_4 * j_max * T_1 * T_2 + (j_max * T_1 * T_3 * T_3) / 2 + j_max * T_1 * T_3 * T_5 + j_max * T_1 * T_3 * T_6 + T_4 * j_max * T_1 * T_3 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 - (j_max * T_3 * T_3 * T_5) / 2 - (j_max * T_3 * T_3 * T_6) / 2 - (T_4 * j_max * T_3 * T_3) / 2 + v0 * T_3 + (j_min * pow(T_5, 3)) / 6 + (j_min * T_5 * T_5 * T_6) / 2 + (j_min * T_5 * T_6 * T_6) / 2 + v0 * T_5 + v0 * T_6 + q0 + T_4 * v0;
            // 减减速阶段
            res.j[i] = -j_min;
            res.a[i] = j_min * T_5 - j_min * (cur_t - cur_start_time);
            res.v[i] = last_v + (j_min * (cur_t - cur_start_time) * (2 * T_5 - cur_t + cur_start_time)) / 2;
            res.q[i] = last_q + ((cur_t - cur_start_time) * (-j_min * cur_t * cur_t + 2 * j_min * cur_t * cur_start_time + 3 * T_5 * j_min * cur_t - j_min * cur_start_time * cur_start_time - 3 * T_5 * j_min * cur_start_time + 6 * last_v)) / 6;
        }
    }

    printf("S速度规划各阶段时长:[%f, %f, %f, %f, %f, %f, %f]\n", T_1, T_2, T_3, T_4, T_5, T_6, T_7);
    printf("加速、匀速、减速时长:[%f, %f, %f], 总时长:[%f]\n", T_a, T_v, T_d, res.T);
    printf("路径点个数:[%d]\n", res.path_num);

    // 输出归一化处理
    for (int i = 0; i < n; i++) {
        res.q[i] = direction * res.q[i];
        res.v[i] = direction * res.v[i];
        res.a[i] = direction * res.a[i];
        res.j[i] = direction * res.j[i];
    }

    return res;
}

trajectory_segment multi_s_curve_generator(double* q_points, double* v_points, double v_max, double a_max, double j_max, double start_time, double dt, int N) {
    double cur_t_start = start_time;
    double q0, q1, v0, v1;
    trajectory_segment temp_res, res;
    int cur_path_num = 0, last_path_num = 0;
    double T = 0;

    temp_res.t = (double*)malloc(MAX_PATH_NUM_ALLOWED * sizeof(double));
    temp_res.q = (double*)malloc(MAX_PATH_NUM_ALLOWED * sizeof(double));
    temp_res.v = (double*)malloc(MAX_PATH_NUM_ALLOWED * sizeof(double));
    temp_res.a = (double*)malloc(MAX_PATH_NUM_ALLOWED * sizeof(double));
    temp_res.j = (double*)malloc(MAX_PATH_NUM_ALLOWED * sizeof(double));

    for (int i = 0; i < N - 1; i++) {
        q0 = q_points[i];
        q1 = q_points[i + 1];
        v0 = v_points[i];
        v1 = v_points[i + 1];

        trajectory_segment cur_trajectory_segment = s_curve_generator(q0, q1, v0, v1, v_max, a_max, j_max, cur_t_start, dt);
        cur_t_start = cur_t_start + cur_trajectory_segment.T;
        if (i == 0) {
            cur_path_num = cur_path_num + cur_trajectory_segment.path_num;
        }
        else {
            cur_path_num = cur_path_num + cur_trajectory_segment.path_num - 1;
        }

        T += cur_trajectory_segment.T;

        if (cur_path_num <= MAX_PATH_NUM_ALLOWED) {
            if (i == 0) {
                for (int j = 0; j < cur_trajectory_segment.path_num; j++) {
                    temp_res.t[j] = cur_trajectory_segment.t[j];
                    temp_res.q[j] = cur_trajectory_segment.q[j];
                    temp_res.v[j] = cur_trajectory_segment.v[j];
                    temp_res.a[j] = cur_trajectory_segment.a[j];
                    temp_res.j[j] = cur_trajectory_segment.j[j];
                }
            } else {
                for (int j = 0; j < cur_trajectory_segment.path_num; j++) {
                    temp_res.t[last_path_num - 1 + j] = cur_trajectory_segment.t[j];
                    temp_res.q[last_path_num - 1 + j] = cur_trajectory_segment.q[j];
                    temp_res.v[last_path_num - 1 + j] = cur_trajectory_segment.v[j];
                    temp_res.a[last_path_num - 1 + j] = cur_trajectory_segment.a[j];
                    temp_res.j[last_path_num - 1 + j] = cur_trajectory_segment.j[j];
                }
            }

            // 释放每段S速度规划申请的内存
            free_trajectory_segment(&cur_trajectory_segment);
        } else {
            free_trajectory_segment(&temp_res);
            // 释放每段S速度规划申请的内存
            free_trajectory_segment(&cur_trajectory_segment);
            return temp_res;
        }

        last_path_num = cur_path_num;
    }

    temp_res.path_num = cur_path_num;
    temp_res.T = T;

    res.path_num = cur_path_num;
    res.T = T;

    res.t = (double*)malloc(cur_path_num * sizeof(double));
    res.q = (double*)malloc(cur_path_num * sizeof(double));
    res.v = (double*)malloc(cur_path_num * sizeof(double));
    res.a = (double*)malloc(cur_path_num * sizeof(double));
    res.j = (double*)malloc(cur_path_num * sizeof(double));

    for (int i = 0; i < cur_path_num; i++) {
        res.t[i] = temp_res.t[i];
        res.q[i] = temp_res.q[i];
        res.v[i] = temp_res.v[i];
        res.a[i] = temp_res.a[i];
        res.j[i] = temp_res.j[i];
    }

    free_trajectory_segment(&temp_res);
    printf("多点间实现S型加减速规划, 规划后轨迹点个数:[%d], 轨迹总时长:[%f], 控制周期:[%f]\n", res.path_num, res.T, dt);

    return res;
}

trajectory_segment multi_s_curve_generator_based_on_path(double* q_points, double v_start, double v_end, double v_max, double a_max, double j_max, double start_time, double dt, int N) {
    double* v_points  = (double*)malloc(N * sizeof(double));

    v_points[0] = v_start;
    v_points[N - 1] = v_end;

    for (int i = 1; i < N - 1; i++) {
        v_points[i] = v_start + i / (N - 1) * (v_end - v_start);
    }

    trajectory_segment res = multi_s_curve_generator(q_points, v_points, v_max, a_max, j_max, start_time, dt, N);

    if (v_points != NULL) {
        free(v_points);
        v_points = NULL;
    }

    return res;
}


int Trapezoid_plan(ST_PlanParams stsetParam, ST_PlanParams& stActParam, ST_PlanData& trackData)
{
    double q0, q1, Vs, Ve, Vmax, Amax;
    double T_acc, T_flat, T_dec, T, d_acc, d_dec, A_tem, Vmax_new;
    int direction;
    int err;
    int planmode;
    int sign;
    sign = 1;

    q0 = stsetParam.q0;
    q1 = stsetParam.q1;
    Vs = stsetParam.v0;
    Ve = stsetParam.v1;
    Vmax = stsetParam.V_max;
    Amax = stsetParam.A_amax;
    if(stsetParam.enPlanmode == enPositionPlanningMode)
    {
        planmode = 1;
    }
    if(stsetParam.enPlanmode == enVelocityPlanningMode)
    {
        planmode = 2;
    }

    T_acc = 0;
    T_flat = 0;
    T_dec = 0;
    d_acc = 0;
    d_dec = 0;
    A_tem = 0;
    Vmax_new = 0;
    err = 0;
    if(planmode == 1)//位置模式
        {
        if (abs(Vmax) <= Zero || abs(Amax) <= Zero) {
            err = ERROR_INVALID_PARAMETERS;
            return err;
        }
        if ((Vmax<Vs && Vmax>Ve) || (Vmax > Vs && Vmax < Ve) || (Vmax < Vs && Vmax < Ve)) {
            if ((Vs - Ve) > Zero) {
                Vmax = Vs;
            }
            else {
                Vmax = Ve;
            }
        }
        direction = (q1 > q0) ? 1.0 : -1.0;
        Vs = direction * Vs;
        Ve = direction * Ve;
        q0 = direction * q0;
        q1 = direction * q1;
        // 计算中间参数
        T_acc = std::abs(Vmax - Vs) / Amax;
        T_dec = std::abs(Vmax - Ve) / Amax;
        T_flat = std::abs(q1 - q0) / Vmax - (T_acc / 2) * (1 + Vs / Vmax) - (T_dec / 2) * (1 + Ve / Vmax);
        d_acc = abs(Vmax * Vmax - Vs * Vs) / (2 * Amax);  // 加速阶段位移
        d_dec = abs(Vmax * Vmax - Ve * Ve) / (2 * Amax);  // 减速阶段位移

        // 判断是否有匀速段
        if (T_flat < 0) {
            if ((std::abs(q1 - q0) - d_acc) < Zero || (std::abs(q1 - q0) - d_dec < Zero)) {
                if ((Vs - Ve) > Zero) {
                    Vmax = Vs;
                    if(abs(Vs + Ve)<=Zero)
                    {
                        err = ERROR_DISPLACEMENT_TOO_SMALL;
                        return err;
                    }
                    T_dec = (2 * std::abs(q0 - q1)) / abs(Vs + Ve);
                    if (abs(T_dec) < Zero) {
                        err = ERROR_DISPLACEMENT_TOO_SMALL;
                        return err;
                    }
                    A_tem = (Vs - Ve) / T_dec;
                    // if (A_tem - Amax > -Zero) {
                    //     cout<<"A: "<<A_tem<<Amax<<endl;
                    //     err = ERROR_INVALID_PARAMETERS;
                    //     return err;
                    // }
                    Amax = A_tem;
                    T_acc = 0;
                    T_flat = 0;
                    if (abs(Amax) < Zero)
                    {
                        err = ERROR_DISPLACEMENT_TOO_SMALL;
                        return err;
                    }
                    T_dec = std::abs(Vmax - Ve) / Amax;
                }
                else if ((Vs - Ve) < Zero) {
                    Vmax = Ve;
                    if(abs(Vs + Ve)<Zero)
                    {
                        err = ERROR_INVALID_PARAMETERS;
                        return err;  
                    }
                    T_acc = (2 * std::abs(q0 - q1)) / abs(Vs + Ve);
                    if (abs(T_acc) <= Zero) {
                        err = ERROR_INVALID_PARAMETERS;
                        return err;
                    }
                    A_tem = (Ve - Vs) / T_acc;
                    if (A_tem - Amax > Zero) {
                        err = ERROR_DISPLACEMENT_TOO_SMALL;
                        return err;
                    }
                    Amax = A_tem;
                    if(abs(Amax)<Zero)
                    {
                        err = ERROR_DISPLACEMENT_TOO_SMALL;
                        return err;
                    }
                    T_acc = std::abs(Vmax - Vs) / Amax;
                    T_flat = 0;
                    T_dec = 0;
                }
                else {
                    Vmax_new = std::sqrt((2 * std::abs(q0 - q1) * Amax + Vs * Vs + Ve * Ve) / 2);
                    if (Vmax_new < Vs && Vmax_new < Ve && Vmax_new < Zero) {
                        if (Vs - Ve > Zero) {
                            Vmax = Vs;
                        }
                        else {
                            Vmax = Ve;
                        }
                    }
                    else if ((Vmax_new - Vmax) > Zero) {
                        err = ERROR_CALCULATION_01;
                        return err;
                    }
                    Vmax = Vmax_new;
                    T_acc = std::abs(Vmax - Vs) / Amax;
                    T_dec = std::abs(Vmax - Ve) / Amax;
                    d_acc = std::abs(Vmax * Vmax - Vs * Vs) / (2 * Amax);
                    d_dec = std::abs(Vmax * Vmax - Ve * Ve) / (2 * Amax);
                    T_flat = std::abs(q0 - q1) / Vmax - (T_acc / 2) * (1 + Vs / Vmax) - (T_dec / 2) * (1 + Ve / Vmax);
                    if (T_flat < Zero) {
                        err = ERROR_CALCULATION_02;
                        return err;
                    }
                }
            }
            else {
                Vmax_new = std::sqrt((2 * std::abs(q0 - q1) * Amax + Vs * Vs + Ve * Ve) / 2);
                if ((Vmax_new < Vs) && (Vmax_new < Ve) && (Vmax_new < Zero)) {
                    if (Vs - Ve > Zero) {
                        Vmax = Vs;
                    }
                    else {
                        Vmax = Ve;
                    }
                }
                else if ((Vmax_new - Vmax) > Zero) {
                    err = ERROR_CALCULATION_01;
                    return err;
                }
                Vmax = Vmax_new;
                T_acc = std::abs(Vmax - Vs) / Amax;
                T_dec = std::abs(Vmax - Ve) / Amax;
                d_acc = std::abs(Vmax * Vmax - Vs * Vs) / (2 * Amax);
                d_dec = std::abs(Vmax * Vmax - Ve * Ve) / (2 * Amax);
                T_flat = std::abs(q0 - q1) / Vmax - (T_acc / 2) * (1 + Vs / Vmax) - (T_dec / 2) * (1 + Ve / Vmax);
                if (T_flat < Zero) {
                    err = ERROR_CALCULATION_02;
                    return err;
                }
            }
        }
        else {
            if ((Vmax - Vs) < Zero || (Vmax - Ve) < Zero) {
                if (Vs - Ve > Zero) {
                    Vmax = Vs;
                }
                else {
                    Vmax = Ve;
                }
                T_acc = std::abs(Vmax - Vs) / Amax;
                T_dec = std::abs(Vmax - Ve) / Amax;
                T_flat = std::abs(q0 - q1) / Vmax - (T_acc / 2) * (1 + Vs / Vmax) - (T_dec / 2) * (1 + Ve / Vmax);
            }
        }
        // 总时间
        T = T_acc + T_flat + T_dec;

        stActParam.q0 = q0;
        stActParam.q1 = q1;
        stActParam.v0 = Vs;
        stActParam.v1 = Ve;
        stActParam.V_max = abs(Vmax);
        trackData.A_amax = sign*Amax;
        trackData.A_dmax = sign*Amax;
        trackData.Ta = T_acc;
        trackData.Tv = T_flat;
        trackData.Td = T_dec;
        trackData.T = T;
        trackData.direction = direction;
    }
    if(planmode == 2)//速度模式
    {
        if(Vmax<Zero)
        {
            direction = -1;
        }else
        {
            direction = 1;
        }
        Vs = direction * Vs;
        q0 = direction * q0;
        if ((Vs*Vmax<-Zero)||(abs(Vs)-abs(Vmax)<Zero))
        {
            sign = 1;
            Amax = stsetParam.A_amax;
        }else
        {
            sign = -1;
            Amax = stsetParam.A_dmax;
        }
        if(abs(Amax)<=Zero)
        {
            err = Denominator_is_zero;
            return err;
        }
        T_acc = abs(Vmax - Vs) / Amax;// 速度的加速时间
        // 总时间
        T = T_acc;

        stActParam.q0 = q0;
        stActParam.v0 = Vs;
        stActParam.V_max = abs(Vmax);
        trackData.A_amax = sign*Amax;
        trackData.Ta = T_acc;
        trackData.T = T;
        trackData.direction = direction;
    }


    return err;
}
int Trapezoid_Inter(ST_PlanParams stActParam, ST_PlanData trackData, double t, ST_InterParams& stData)
{
    double q0, q1, Vs, Ve, Vmax, A_amax, A_dmax;
    double T_acc, T_flat, T_dec, T, d_acc, d_dec, A_tem, Vmax_new;
    double  P, V, A;
    int direction;
    int err = 0;

    q0 = stActParam.q0;
    q1 = stActParam.q1;
    Vs = stActParam.v0;
    Ve = stActParam.v1;
    Vmax = stActParam.V_max;
    A_amax = trackData.A_amax;
    A_dmax = trackData.A_dmax;
    T_acc = trackData.Ta;
    T_flat = trackData.Tv;
    T_dec = trackData.Td;
    T = trackData.T;
    direction = trackData.direction;
    P = 0;
    V = 0;
    A = 0;

    // cout<<"stActParam.q0  "<<stActParam.q0
    //     <<"\t stActParam.q1  "<<stActParam.q1
    //     <<"\t stActParam.v0  "<<stActParam.v0
    //     <<"\t stActParam.v1  "<<stActParam.v1
    //     <<"\t stActParam.V_max  "<<stActParam.V_max
    //     <<"\t trackData.A_amax  "<<trackData.A_amax
    //     <<"\t trackData.A_dmax  "<<trackData.A_dmax
    //     <<"\t trackData.Ta  "<<trackData.Ta
    //     <<"\t trackData.Td  "<<trackData.Td
    //     <<"\t trackData.Tv  "<<trackData.Tv
    //     <<"\t trackData.T "<<trackData.T 
    //     <<"\t t "<<t
    //     <<endl;
    // 计算各阶段轨迹
    if (t <= T_acc) {
        // 加速阶段
        A = A_amax;
        V = Vs + A_amax * t;
        P = q0 + Vs * t + 0.5 * A_amax * t * t;
    }
    else if (t <= (T_acc + T_flat)) {
        // 匀速阶段
        A = 0;
        V = Vmax;
        P = (Vmax - Vs) / 2 * (2 * t - T_acc) + Vs * t + q0;
    }
    else if (t <= T) {
        // 减速阶段
        A = -A_dmax;
        V = Ve + A_dmax * (T - t);
        P = -Ve * (T - t) - 0.5 * A_dmax * (T - t) * (T - t) + q1;
    }
    else {
        err = ERROR_INVALID_PARAMETERS;
        return err;
    }
    
    stData.P = direction * P;
    stData.V = direction * V;
    stData.A = direction * A;

    return err;
}

int S_curve_plan(ST_PlanParams stsetParam, ST_PlanParams& stActParam, ST_PlanData& trackData)
{
    double q0, q1, v0, v1, v_max, a_max, j_max, v_min, a_min, j_min;
    double v_max_origin, v_min_origin, a_max_origin, a_min_origin, j_max_origin, j_min_origin, v_m;
    int direction, n;
    int err;
    double T_1, T_2, T_3, T_4, T_5, T_6, T_7, T_j1, T_j2, T_j, T_a, T_v, T_d, T;
    double delta, step;
    int sign;
    int planmode;

    sign = 1;
    q0 = stsetParam.q0;
    q1 = stsetParam.q1;
    v0 = stsetParam.v0;
    v1 = stsetParam.v1;
    v_max = stsetParam.V_max;
    v_min = -stsetParam.V_max;
    a_max = stsetParam.A_amax;
    a_min = -stsetParam.A_dmax;
    j_max = stsetParam.J_max;
    j_min = -stsetParam.J_max;
    if(stsetParam.enPlanmode == enPositionPlanningMode)
    {
        planmode = 1;
    }
    if(stsetParam.enPlanmode == enVelocityPlanningMode)
    {
        planmode = 2;
    }

    if (abs(stsetParam.V_max) <= Zero || abs(stsetParam.A_amax) <= Zero ||abs(stsetParam.A_dmax) <= Zero || abs(stsetParam.J_max) <= Zero )
    {
        err = Invalid_input_parameter;
        return err;
    }

    T_j1 = 0;
    T_j2 = 0;
    T_a = 0;
    T_d = 0;
    T_v = 0;
    err = 0;
    if(planmode == 1)
    {
        // 输入归一化处理
        v_max_origin = v_max;
        v_min_origin = v_min;
        a_max_origin = a_max;
        a_min_origin = a_min;
        j_max_origin = j_max;
        j_min_origin = j_min;

        direction = ((q1 - q0) > 0) ? 1 : -1;
        q0 = direction * q0;
        q1 = direction * q1;
        v0 = direction * v0;
        v1 = direction * v1;

        v_max = (direction + 1) / 2 * v_max_origin + (direction - 1) / 2 * v_min_origin;
        v_min = (direction + 1) / 2 * v_min_origin + (direction - 1) / 2 * v_max_origin;
        a_max = (direction + 1) / 2 * a_max_origin + (direction - 1) / 2 * a_min_origin;
        a_min = (direction + 1) / 2 * a_min_origin + (direction - 1) / 2 * a_max_origin;
        j_max = (direction + 1) / 2 * j_max_origin + (direction - 1) / 2 * j_min_origin;
        j_min = (direction + 1) / 2 * j_min_origin + (direction - 1) / 2 * j_max_origin;

        if ((v_max - v0) * j_max < a_max * a_max) {
            T_j1 = sqrt((v_max - v0) / j_max);
            T_a = 2 * T_j1;
        }
        else {
            T_j1 = a_max / j_max;
            T_a = T_j1 + (v_max - v0) / a_max;
        }

        if ((v_max - v1) * j_max < a_max * a_max) {
            T_j2 = sqrt((v_max - v1) / j_max);
            T_d = 2 * T_j2;
        }
        else {
            T_j2 = a_max / j_max;
            T_d = T_j2 + (v_max - v1) / a_max;
        }

        if (abs(v_max) <= Zero || abs(a_max) <= Zero || abs(j_max) <= Zero )
        {
            err = Invalid_input_parameter;
            return err;
        }
        T_v = (q1 - q0) / v_max - T_a / 2 * (1 + v0 / v_max) - T_d / 2 * (1 + v1 / v_max);

        if (T_v >= 0) {
            // 最大速度可达
            v_m = v_max;
            T_1 = T_j1;
            T_2 = T_a - 2 * T_j1;
            T_3 = T_j1;
            T_4 = T_v;
            T_5 = T_j2;
            T_6 = T_d - 2 * T_j2;
            T_7 = T_j2;
        }
        else {
            // 最大速度不可达
            T_j1 = a_max / j_max;
            T_j2 = a_max / j_max;
            T_j = T_j1;

            delta = pow(a_max, 4) / (j_max * j_max) + 2 * (v0 * v0 + v1 * v1) + a_max * (4 * (q1 - q0) - 2 * a_max / j_max * (v0 + v1));
            T_a = (a_max * a_max / j_max - 2 * v0 + sqrt(delta)) / (2 * a_max);
            T_d = (a_max * a_max / j_max - 2 * v1 + sqrt(delta)) / (2 * a_max);
            T_v = 0;

            T_1 = T_j1;
            T_2 = T_a - 2 * T_j1;
            T_3 = T_j1;
            T_4 = T_v;
            T_5 = T_j2;
            T_6 = T_d - 2 * T_j2;
            T_7 = T_j2;

            if ((T_a >= 2 * T_j) && (T_d >= 2 * T_j)) {
                v_m = v0 + j_max * pow(T_j1,2) + j_max * T_j1 * T_2;
                v_max = v_m;
            }
            else {
                step = ITERATIVESTEPS;
                for (double i = 1 - step; i = i - step; i >= step) {
                    double temp = i * a_max;
                    T_j = temp / j_max;
                    if(abs(temp)<=Zero)
                    {
                        err = ERROR_DISPLACEMENT_TOO_SMALL;
                        return err;
                    }
                    delta = pow(temp, 4) / (j_max * j_max) + 2 * (v0 * v0 + v1 * v1) + temp * (4 * (q1 - q0) - 2 * temp / j_max * (v0 + v1));
                    T_a = (temp * temp / j_max - 2 * v0 + sqrt(delta)) / (2 * temp);
                    T_d = (temp * temp / j_max - 2 * v1 + sqrt(delta)) / (2 * temp);
                    if ((T_a >= 2 * T_j) && (T_d >= 2 * T_j)) {
                        // a_max = temp;
                        // a_min = -a_max;
                        // v_m = v0 + (T_a - T_j1) * a_max;
                        // v_max = v_m;
                        T_1 = T_j;
                        T_2 = T_a - 2 * T_j;
                        T_3 = T_j;
                        T_4 = 0;
                        T_5 = T_j;
                        T_6 = T_d - 2 * T_j;
                        T_7 = T_j;
                        T_v = 0;    

                        v_m = v0 + j_max * pow(T_j,2) + j_max * T_j * T_2;
                        v_max = v_m;
                        break;
                    }
                    else if ((T_a < 0) && (v0 > v1)) {
                        T_a = 0;
                        T_v = 0;
                        if(abs(v1 + v0)<=Zero)
                        {
                            err = ERROR_DISPLACEMENT_TOO_SMALL;
                            return err;
                        }
                        T_d = 2 * (q1 - q0) / (v1 + v0);
                        if((j_max * (j_max * (q1 - q0) * (q1 - q0) + (v1 + v0) * (v1 + v0) * (v1 - v0)))<0)
                        {
                            T_j2 = 0.5 * T_d;
                        }else
                        {
                            T_j2 = (j_max * (q1 - q0) - sqrt(j_max * (j_max * (q1 - q0) * (q1 - q0) + (v1 + v0) * (v1 + v0) * (v1 - v0)))) / (j_max * (v1 + v0));
                        }

                        T_1 = 0;
                        T_2 = 0;
                        T_3 = 0;
                        T_4 = 0;
                        T_5 = T_j2;
                        T_6 = T_d - 2 * T_j2;
                        T_7 = T_j2;

                        v_m = v0;
                        v_max = v_m;
                        break;
                    }
                    else if ((T_d < 0) && (v0 < v1)) {
                        T_d = 0;
                        T_v = 0;
                        if(abs(v1 + v0)<=Zero)
                        {
                            err = ERROR_DISPLACEMENT_TOO_SMALL;
                            return err;
                        }
                        T_a = 2 * (q1 - q0) / (v1 + v0);
                        if ((j_max * (j_max * (q1 - q0) * (q1 - q0) - (v1 + v0) * (v1 + v0) * (v1 - v0)))<0)
                        {
                            T_j1 = 0.5 * T_a;
                        }else
                        {
                            T_j1 = (j_max * (q1 - q0) - sqrt(j_max * (j_max * (q1 - q0) * (q1 - q0) - (v1 + v0) * (v1 + v0) * (v1 - v0)))) / (j_max * (v1 + v0));
                        }
                        
                        T_1 = T_j1;
                        T_2 = T_a - 2 * T_j1;
                        T_3 = T_j1;
                        T_4 = 0;
                        T_5 = 0;
                        T_6 = 0;
                        T_7 = 0;

                        v_m = v1;
                        v_max = v_m;
                        break;
                    }
                }
            }
        }
        // 总时间
        T = T_a + T_v + T_d;
        stActParam.q0 = q0;
        stActParam.q1 = q1;
        stActParam.v0 = v0;
        stActParam.v1 = v1;
        stActParam.V_max = v_max;
        trackData.A_amax = T_1*j_max * sign;
        trackData.A_dmax = -T_5*j_max;
        trackData.J_amax = j_max * sign;
        trackData.J_dmax = -j_max;
        trackData.Tja = T_1;
        trackData.Tjd = T_5;
        trackData.Ta = T_a;
        trackData.Td = T_d;
        trackData.Tv = T_v;
        trackData.T = T;
        trackData.direction = direction;
    }
    if(planmode == 2)
    {
        if(v_max<Zero)
        {
            direction = -1;
        }else
        {
            direction = 1;
        }
        v0 = direction * v0;
        q0 = direction * q0;
        if ((v0*v_max<-Zero)||(abs(v0)-abs(v_max)<Zero))
        {
            sign = 1;
            a_max = stsetParam.A_amax;
            j_max = stsetParam.J_max;
            
        }else
        {
            sign = -1;
            a_max = stsetParam.A_dmax;
            j_max = stsetParam.J_max;
        }
        //S型规划
        if (abs(v_max - v0) * j_max < a_max * a_max) 
        {
            if(abs(j_max)<=Zero)
            {
                err = Denominator_is_zero;
                return err;
            }
            T_j1 = sqrt(abs(v_max - v0) / j_max);
            T_a = 2 * T_j1;
            a_max = T_j1 * j_max;
        }
        else 
        {
            if(abs(j_max)<=Zero||abs(a_max)<=Zero)
            {
                err = Denominator_is_zero;
                return err;
            }
            T_j1 = a_max / j_max;
            T_a = T_j1 + abs(v_max - v0) / a_max;
        } 
        // 总时间
        T = T_a ;
        stActParam.q0 = q0;
        stActParam.v0 = v0;
        stActParam.V_max = abs(v_max);
        trackData.A_amax = a_max * sign;
        trackData.J_amax = j_max * sign;
        trackData.Tja = T_1;
        trackData.Ta = T_a;
        trackData.T = T;
        trackData.direction = direction;
    }

    return err;
}
int S_curve_Inter(ST_PlanParams stActParam, ST_PlanData trackData, double t, ST_InterParams& stData)
{
    double q0, q1, v0, v1, v_max, a_max, j_max, v_min, a_min, j_min;
    double T_1, T_2, T_3, T_4, T_5, T_6, T_7, T_j1, T_j2, T_j, T_a, T_v, T_d;
    double t1, t2, t3, t4, t5, t6, t7, T;
    double  j, a, v, q;
    double cur_start_time, last_v, last_q, t_start;
    int direction;
    int err;

    q0 = stActParam.q0;
    q1 = stActParam.q1;
    v0 = stActParam.v0;
    v1 = stActParam.v1;
    v_max = stActParam.V_max;
    v_min = -stActParam.V_max;
    a_max = trackData.A_amax;
    a_min = trackData.A_dmax;
    j_max = trackData.J_amax;
    j_min = trackData.J_dmax;
    T_j1 = trackData.Tja;
    T_j2 = trackData.Tjd;
    T_a = trackData.Ta;
    T_d = trackData.Td;
    T_v = trackData.Tv;
    T = trackData.T;
    direction = trackData.direction;
    err = 0;
    t_start = 0;


    // 时间点划分
    T_1 = T_j1;
    T_2 = T_a - 2 * T_j1;
    T_3 = T_j1;
    T_4 = T_v;
    T_5 = T_j2;
    T_6 = T_d - 2 * T_j2;
    T_7 = T_j2;

    t1 = t_start + T_1;
    t2 = t1 + T_2;
    t3 = t2 + T_3;
    t4 = t3 + T_4;
    t5 = t4 + T_5;
    t6 = t5 + T_6;
    t7 = t6 + T_7;

    last_v = v0;
    last_q = q0;
    if ((t <= t1) && (T_1 > 0)) {
        cur_start_time = t_start;
        last_v = v0;
        last_q = q0;
        // 加加速阶段
        j = j_max;
        a = j_max * (t - cur_start_time);
        v = last_v + (j_max * (t - cur_start_time) * (t - cur_start_time)) / 2;
        q = last_q + ((t - cur_start_time) * (j_max * t * t - 2 * j_max * t * cur_start_time + j_max * cur_start_time * cur_start_time + 6 * last_v)) / 6;
    }
    else if ((t <= t2) && (T_2 > 0)) {
        cur_start_time = t_start + T_1;
        last_v = v0 + (j_max * T_1 * T_1) / 2;
        last_q = q0 + ((T_1) * (j_max * (t_start + T_1) * (t_start + T_1) - 2 * j_max * (t_start + T_1) * t_start + j_max * t_start * t_start + 6 * v0)) / 6;
        // 匀加速阶段
        j = 0;
        a = j_max * T_1;
        v = last_v + T_1 * j_max * (t - cur_start_time);
        q = last_q + ((t - cur_start_time) * (2 * last_v + T_1 * t * j_max - T_1 * cur_start_time * j_max)) / 2;
    }
    else if ((t <= t3) && (T_3 > 0)) {
        cur_start_time = t_start + T_1 + T_2;
        last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0;
        last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + v0 * T_1 + v0 * T_2 + q0;
        // 减加速阶段
        j = -j_max;
        a = j_max * T_1 - j_max * (t - cur_start_time);
        v = last_v + (j_max * (t - cur_start_time) * (2 * T_1 - t + cur_start_time)) / 2;
        q = last_q + ((t - cur_start_time) * (-j_max * t * t + 2 * j_max * t * cur_start_time + 3 * T_1 * j_max * t - j_max * cur_start_time * cur_start_time - 3 * T_1 * j_max * cur_start_time + 6 * last_v)) / 6;
    }
    else if ((t <= t4) && (T_4 > 0)) {
        cur_start_time = t_start + T_1 + T_2 + T_3;
        last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2;
        last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + (j_max * T_1 * T_3 * T_3) / 2 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 + v0 * T_3 + q0;
        // 匀速阶段
        j = 0;
        a = 0;
        v = last_v;
        q = last_q + last_v * (t - cur_start_time);
    }
    else if ((t <= t5) && (T_5 > 0)) {
        cur_start_time = t_start + T_1 + T_2 + T_3 + T_4;
        last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2;
        last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (T_4 * j_max * T_1 * T_1) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + T_4 * j_max * T_1 * T_2 + (j_max * T_1 * T_3 * T_3) / 2 + T_4 * j_max * T_1 * T_3 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 - (T_4 * j_max * T_3 * T_3) / 2 + v0 * T_3 + q0 + T_4 * v0;
        // 加减速阶段
        j = j_min;
        a = j_min * (t - cur_start_time);
        v = last_v + (j_min * (t - cur_start_time) * (t - cur_start_time)) / 2;
        q = last_q + ((t - cur_start_time) * (j_min * t * t - 2 * j_min * t * cur_start_time + j_min * cur_start_time * cur_start_time + 6 * last_v)) / 6;
    }
    else if ((t <= t6) && (T_6 > 0)) {
        cur_start_time = t_start + T_1 + T_2 + T_3 + T_4 + T_5;
        last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2 + (j_min * T_5 * T_5) / 2;
        last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (j_max * T_1 * T_1 * T_5) / 2 + (T_4 * j_max * T_1 * T_1) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + j_max * T_1 * T_2 * T_5 + T_4 * j_max * T_1 * T_2 + (j_max * T_1 * T_3 * T_3) / 2 + j_max * T_1 * T_3 * T_5 + T_4 * j_max * T_1 * T_3 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 - (j_max * T_3 * T_3 * T_5) / 2 - (T_4 * j_max * T_3 * T_3) / 2 + v0 * T_3 + (j_min * pow(T_5, 3)) / 6 + v0 * T_5 + q0 + T_4 * v0;
        // 匀减速阶段
        j = 0;
        a = j_min * T_5;
        v = last_v + T_5 * j_min * (t - cur_start_time);
        q = last_q + ((t - cur_start_time) * (2 * last_v + T_5 * t * j_min - T_5 * cur_start_time * j_min)) / 2;
    }
    else if ((T_7 > 0)) {
        cur_start_time = t_start + T_1 + T_2 + T_3 + T_4 + T_5 + T_6;
        last_v = (j_max * T_1 * T_1) / 2 + T_2 * j_max * T_1 + v0 + (j_max * T_3 * (2 * T_1 - T_3)) / 2 + (j_min * T_5 * T_5) / 2 + T_5 * j_min * T_6;
        last_q = (j_max * pow(T_1, 3)) / 6 + (j_max * T_1 * T_1 * T_2) / 2 + (j_max * T_1 * T_1 * T_3) / 2 + (j_max * T_1 * T_1 * T_5) / 2 + (j_max * T_1 * T_1 * T_6) / 2 + (T_4 * j_max * T_1 * T_1) / 2 + (j_max * T_1 * T_2 * T_2) / 2 + j_max * T_1 * T_2 * T_3 + j_max * T_1 * T_2 * T_5 + j_max * T_1 * T_2 * T_6 + T_4 * j_max * T_1 * T_2 + (j_max * T_1 * T_3 * T_3) / 2 + j_max * T_1 * T_3 * T_5 + j_max * T_1 * T_3 * T_6 + T_4 * j_max * T_1 * T_3 + v0 * T_1 + v0 * T_2 - (j_max * pow(T_3, 3)) / 6 - (j_max * T_3 * T_3 * T_5) / 2 - (j_max * T_3 * T_3 * T_6) / 2 - (T_4 * j_max * T_3 * T_3) / 2 + v0 * T_3 + (j_min * pow(T_5, 3)) / 6 + (j_min * T_5 * T_5 * T_6) / 2 + (j_min * T_5 * T_6 * T_6) / 2 + v0 * T_5 + v0 * T_6 + q0 + T_4 * v0;
        // 减减速阶段
        j = -j_min;
        a = j_min * T_5 - j_min * (t - cur_start_time);
        v = last_v + (j_min * (t - cur_start_time) * (2 * T_5 - t + cur_start_time)) / 2;
        q = last_q + ((t - cur_start_time) * (-j_min * t * t + 2 * j_min * t * cur_start_time + 3 * T_5 * j_min * t - j_min * cur_start_time * cur_start_time - 3 * T_5 * j_min * cur_start_time + 6 * last_v)) / 6;
    }

    stData.J = direction * j;
    stData.A = direction * a;
    stData.V = direction * v;
    stData.P = direction * q;
    return err;
}

int FifteenSeg_plan(ST_PlanParams stsetParam, ST_PlanParams& stActParam, ST_PlanData& trackData) {
    double q0, q1, v0, v1, V_max, A_amax, A_dmax, J_amax, J_dmax, S_max;
    double Tsa, Tsd, Tja, Tjd, Ta, Td, Tv, T;
    double S_juge, A_ajuge, A_djuge, V_adiff, V_ddiff, a_tem, v_newmax;
    bool plan;
    int err_count;
    int err;
    int sign;
    int planmode;
    int direction;

    sign = 1;
    // 初始化参数
    q0 = stsetParam.q0;
    q1 = stsetParam.q1;
    v0 = stsetParam.v0;
    v1 = stsetParam.v1;
    V_max = stsetParam.V_max;
    A_amax = stsetParam.A_amax;
    A_dmax = stsetParam.A_dmax;
    J_amax = stsetParam.J_max;
    J_dmax = stsetParam.J_max;
    S_max = stsetParam.S_max;
    plan = false;
    if(stsetParam.enPlanmode == enPositionPlanningMode)
    {
        stActParam.enPlanmode = enPositionPlanningMode;
        planmode = 1;
    }
    if(stsetParam.enPlanmode == enVelocityPlanningMode)
    {
        stActParam.enPlanmode = enVelocityPlanningMode;
        planmode = 2;
    }

    Tsa = 0;
    Tsd = 0;
    Tja = 0;
    Tjd = 0;
    Ta = 0;
    Td = 0;
    Tv = 0;
    err = 0;
    err_count = 0;
    if(planmode == 1)
    {
        // 判断速度
        if ((V_max < v0) || (V_max < v1)) {
            if (v0 - v1 > 0.0) {
                V_max = v0;
            }
            else {
                V_max = v1;
            }
        }
        if (abs(stsetParam.V_max) <= Zero || abs(stsetParam.A_amax) <= Zero || abs(stsetParam.A_dmax) <= Zero || abs(stsetParam.J_max) <= Zero || abs(stsetParam.S_max) <= Zero) {
            err = Invalid_input_parameter;
            return err;
        }
        // 判断位移
        S_juge = 1 / 2 * (sqrt(4 * (1 / stsetParam.J_max) * abs(v1 - v0)) + stsetParam.J_max / stsetParam.S_max) * abs(v1 + v0);
        if (abs(q1 - q0) < S_juge) {
            err = The_displacement_is_too_small_to_plan;
            return err;
        }
        direction = (q1 > q0) ? 1.0 : -1.0;
        v0 = direction * v0;
        v1 = direction * v1;
        q0 = direction * q0;
        q1 = direction * q1;
        // 中间参数计算
        Tsa = J_amax / S_max;// 加加速度一阶导的持续时间
        Tsd = J_dmax / S_max;// 加加速度一阶导的持续时间
        Tja = A_amax / J_amax + Tsa;// 加速度的加速时间
        Tjd = A_dmax / J_dmax + Tsd;// 加速度的加速时间
        Ta = Tja + abs(V_max - v0) / A_amax;// 速度的加速时间
        Td = Tjd + abs(V_max - v1) / A_dmax;// 速度的减速时间
        Tv = abs(q1 - q0) / V_max - (Ta / 2) * (1 + v0 / V_max) - (Td / 2) * (1 + v1 / V_max);// 速度的匀速时间
        T = Ta + Tv + Td;
        // 标准判等式
        A_ajuge = pow(J_amax, 2) / S_max;// 能不能达到j_max
        A_djuge = pow(J_dmax, 2) / S_max;// 能不能达到j_max
        V_adiff = pow(A_amax, 2) / J_amax + A_amax * J_amax / S_max;// 能不能达到a_max
        V_ddiff = pow(A_dmax, 2) / J_dmax + A_dmax * J_dmax / S_max;// 能不能达到a_max

        while (plan == false) {
            // 单段规划
            if (((V_max - v0) <= Zero) || ((V_max - v1) <= Zero) || (V_max <= Zero) || ((V_max - stsetParam.V_max) > Zero)) {
                // 减速段
                if ((v0 - v1) > Zero) {
                    J_amax = 0;
                    A_amax = 0;
                    V_max = v0;
                    if ((V_max - v1) < V_ddiff) {
                        a_tem = (-pow(J_dmax, 2) + sqrt(pow(J_dmax, 4) + 4 * S_max * (V_max - v1) * J_dmax * S_max)) / (2 * S_max);
                        if ((a_tem - stsetParam.A_dmax) > Zero) {
                            err = Error_in_calculating_the_acceleration_for_the_single_deceleration_segment;
                            return err;
                        }
                        A_dmax = a_tem;
                    }
                    if ((A_dmax - A_djuge) < Zero) {
                        J_dmax = sqrt(A_dmax * S_max);
                    }
                    if (abs(A_dmax) <= Zero || abs(J_dmax) <= Zero || abs(S_max) <= Zero || abs(V_max) <= Zero) {
                        err = Denominator_is_zero;
                        return err;
                    }
                    Tsa = 0;// 加加速度一阶导的持续时间
                    Tsd = J_dmax / S_max;// 加加速度一阶导的持续时间
                    Tja = 0;// 加速度的加速时间
                    Tjd = A_dmax / J_dmax + Tsd;// 加速度的加速时间
                    Ta = 0;// 速度的加速时间
                    Td = Tjd + abs(V_max - v1) / A_dmax;// 速度的减速时间
                    Tv = abs(q1 - q0) / V_max - (Ta / 2) * (1 + v0 / V_max) - (Td / 2) * (1 + v1 / V_max);// 速度的匀速时间
                    T = Ta + Tv + Td;
                    A_djuge = pow(A_dmax, 2) / S_max;// 能不能达到j_max
                    if (Tv < Zero) {
                        Tv = 0;
                        if (abs(v1 + v0) <= Zero) {
                            err = Denominator_is_zero;
                            return err;
                        }
                        Td = 2 * abs(q1 - q0) / abs(v1 + v0);
                        Tjd = 0.5 * Td;
                        if ((Td - Tjd) <= Zero) {
                            err = Denominator_is_zero;
                            return err;
                        }
                        a_tem = abs(V_max - v1) / (Td - Tjd);
                        if ((a_tem - stsetParam.A_dmax) > Zero) {
                            err = Error_in_calculating_the_acceleration_for_the_single_deceleration_segment;
                            return err;
                        }
                        A_dmax = a_tem;
                        if ((A_dmax - A_djuge) < Zero) {
                            J_dmax = sqrt(A_dmax * S_max);
                        }
                        if (abs(A_dmax) <=Zero  || abs(J_dmax) <= Zero || abs(S_max) <= Zero || abs(V_max) <= Zero) {
                            err = Denominator_is_zero;
                            return err;
                        }
                        Tsd = J_dmax / S_max;// 加加速度一阶导的持续时间
                        Td = Tjd + abs(V_max - v1) / A_dmax;// 速度的减速时间
                        Tv = abs(q1 - q0) / V_max - (Ta / 2) * (1 + v0 / V_max) - (Td / 2) * (1 + v1 / V_max);// 速度的匀速时间
                        T = Ta + Tv + Td;
                    }
                }
                // 加速段
                if ((v0 - v1) < Zero) {
                    J_dmax = 0;
                    A_dmax = 0;
                    V_max = v1;
                    if ((V_max - v0) < V_adiff) {
                        a_tem = (-pow(J_amax, 2) + sqrt(pow(J_amax, 4) + 4 * S_max * (V_max - v0) * J_amax * S_max)) / (2 * S_max);
                        if ((a_tem - stsetParam.A_amax) > Zero) {
                            err = Error_in_calculating_the_acceleration_for_the_single_deceleration_segment;
                            return err;
                        }
                        A_amax = a_tem;
                    }
                    if ((A_amax - A_ajuge) < Zero) {
                        J_amax = sqrt(A_amax * S_max);
                    }
                    if (abs(A_amax) <= Zero || abs(J_amax) <= Zero || abs(S_max) <= Zero || abs(V_max) <= Zero) {
                        err = Denominator_is_zero;
                        return err;
                    }
                    Tsa = J_amax / S_max;// 加加速度一阶导的持续时间
                    Tsd = 0;// 加加速度一阶导的持续时间
                    Tja = A_amax / J_amax + Tsa;// 加速度的加速时间
                    Tjd = 0;// 加速度的加速时间
                    Ta = Tja + abs(V_max - v0) / A_amax;// 速度的加速时间
                    Td = 0;// 速度的减速时间
                    Tv = abs(q1 - q0) / V_max - (Ta / 2) * (1 + v0 / V_max) - (Td / 2) * (1 + v1 / V_max);// 速度的匀速时间
                    T = Ta + Tv + Td;
                    A_ajuge = pow(J_amax, 2) / S_max;// 能不能达到j_max
                    if (Tv < Zero) {
                        Tv = 0;
                        if (abs(v1 + v0) <= Zero) {
                            err = Denominator_is_zero;
                            return err;
                        }
                        Ta = 2 * abs(q1 - q0) / abs(v1 + v0);
                        Tja = 0.5 * Ta;
                        if ((Ta - Tja) <= Zero) {
                            err = Denominator_is_zero;
                            return err;
                        }
                        a_tem = abs(V_max - v0) / (Ta - Tja);
                        if ((a_tem - stsetParam.A_amax) > Zero) {
                            err = Error_in_calculating_the_acceleration_for_the_single_aeceleration_segment;
                            return err;
                        }
                        A_amax = a_tem;
                        if ((A_amax - A_ajuge) < Zero) {
                            J_amax = sqrt(A_amax * S_max);
                        }
                        if (abs(A_amax) <= Zero || abs(J_amax) <= Zero || abs(S_max) <= Zero || abs(V_max) <= Zero) {
                            err = Denominator_is_zero;
                            return err;
                        }
                        Tsa = J_amax / S_max;// 加加速度一阶导的持续时间
                        Ta = Tja + abs(V_max - v0) / A_amax;// 速度的减速时间
                        Tv = abs(q1 - q0) / V_max - (Ta / 2) * (1 + v0 / V_max) - (Td / 2) * (1 + v1 / V_max);// 速度的匀速时间
                        T = Ta + Tv + Td;
                    }
                }
                plan = true;
            }
            else {
                // 有加速段，减速段
                if ((V_max - v0) < V_adiff) {
                    a_tem = (-pow(J_amax, 2) + sqrt(pow(J_amax, 4) + 4 * S_max * (V_max - v0) * J_amax * S_max)) / (2 * S_max);
                    if ((a_tem - stsetParam.A_amax) > Zero) {
                        err = Error_in_calculating_acceleration_in_the_aeceleration_section;
                        return err;
                    }
                    A_amax = a_tem;
                }
                if ((A_amax - A_ajuge) < Zero) {
                    J_amax = sqrt(A_amax * S_max);
                }
                if ((V_max - v1) < V_ddiff) {
                    a_tem = (-pow(J_dmax, 2) + sqrt(pow(J_dmax, 4) + 4 * S_max * (V_max - v1) * J_dmax * S_max)) / (2 * S_max);
                    if ((a_tem - stsetParam.A_dmax) > Zero) {
                        err = Error_in_calculating_acceleration_in_the_deceleration_section;
                        return err;
                    }
                    A_dmax = a_tem;
                }
                if ((A_dmax - A_djuge) < Zero) {
                    J_dmax = sqrt(A_dmax * S_max);
                }
                if (abs(V_max) <= Zero || abs(A_amax) <= Zero || abs(A_dmax) <= Zero || abs(J_amax) <= Zero || abs(J_dmax) <= Zero || abs(S_max) <= Zero) {
                    err = Invalid_input_parameter;
                    return err;
                }
                Tsa = J_amax / S_max;// 加加速度一阶导的持续时间
                Tsd = J_dmax / S_max;// 加加速度一阶导的持续时间
                Tja = A_amax / J_amax + Tsa;// 加速度的加速时间
                Tjd = A_dmax / J_dmax + Tsd;// 加速度的加速时间
                Ta = Tja + abs(V_max - v0) / A_amax;// 速度的加速时间
                Td = Tjd + abs(V_max - v1) / A_dmax;// 速度的减速时间
                Tv = abs(q1 - q0) / V_max - (Ta / 2) * (1 + v0 / V_max) - (Td / 2) * (1 + v1 / V_max);// 速度的匀速时间
                T = Ta + Tv + Td;
                A_ajuge = pow(J_amax, 2) / S_max;// 能不能达到j_max
                A_djuge = pow(J_dmax, 2) / S_max;// 能不能达到j_max
                V_adiff = pow(A_amax, 2) / J_amax + A_amax * J_amax / S_max;// 能不能达到a_max
                V_ddiff = pow(A_dmax, 2) / J_dmax + A_dmax * J_dmax / S_max;// 能不能达到a_max
                plan = true;
                while (Tv < 0) {
                    v_newmax = 0.9 * V_max;
                    V_max = v_newmax;
                    Ta = Tja + abs(V_max - v0) / A_amax;// 速度的加速时间
                    Td = Tjd + abs(V_max - v1) / A_dmax;// 速度的减速时间
                    Tv = abs(q1 - q0) / V_max - (Ta / 2) * (1 + v0 / V_max) - (Td / 2) * (1 + v1 / V_max);// 速度的匀速时间
                    T = Ta + Tv + Td;
                    plan = false;
                    if ((V_max - v0) <= Zero || ((V_max - v1) <= Zero) || (V_max <= Zero)) {
                        Tv = 0;
                    }
                }
                if (err_count > 2) {
                    err = Planning_error;
                    return err;
                }
                err_count = err_count + 1;
            }
        }
        // 安全保护
        if ((J_amax < 0) || ((J_amax - stsetParam.J_max) > 0) || (Tv < 0) || (J_dmax < 0) || ((J_dmax - stsetParam.J_max) > 0)
            || (A_amax < 0) || ((A_amax - stsetParam.A_amax) > 0) || (A_dmax < 0) || ((A_dmax - stsetParam.A_dmax) > 0)) {
            err = Planning_error;
            return err;
        }

        stActParam.q0 = q0;
        stActParam.q1 = q1;
        stActParam.v0 = v0;
        stActParam.v1 = v1;
        stActParam.V_max = V_max;
        stActParam.S_max = S_max;
        trackData.A_amax = A_amax;
        trackData.A_dmax = A_dmax;
        trackData.J_amax = J_amax;
        trackData.J_dmax = J_dmax;
        trackData.Tsa = Tsa;
        trackData.Tsd = Tsd;
        trackData.Tja = Tja;
        trackData.Tjd = Tjd;
        trackData.Ta = Ta;
        trackData.Td = Td;
        trackData.Tv = Tv;
        trackData.T = T;
        trackData.direction = direction;
    }
    if(planmode == 2)
    {
        if(V_max<Zero)
        {
            direction = -1;
        }else
        {
            direction = 1;
        }
        v0 = direction * v0;
        q0 = direction * q0;
        if ((v0*V_max<-Zero)||(abs(v0)-abs(V_max)<Zero))
        {
            sign = 1;
            A_amax = stsetParam.A_amax;
            J_amax = stsetParam.J_max;
            
        }else
        {
            sign = -1;
            A_amax = stsetParam.A_dmax;
            J_dmax = stsetParam.J_max;
        }
        if(abs(J_amax)<=Zero||abs(A_amax)<=Zero||abs(S_max)<=Zero)
        {
            err = Denominator_is_zero;
            return err;
        }
        //15段规划
        Tsa = J_amax / S_max;// 加加速度一阶导的持续时间
        Tja = A_amax / J_amax + Tsa;// 加速度的加速时间
        Ta = Tja + abs(V_max - v0) / A_amax;// 速度的加速时间
        // 标准判等式
        A_ajuge = pow(J_amax, 2) / S_max;// 能不能达到j_max
        V_adiff = pow(A_amax, 2) / J_amax + A_amax * J_amax / S_max;// 能不能达到a_max

        if (abs(V_max - v0) < V_adiff) {
            a_tem = (-pow(J_amax, 2) + sqrt(pow(J_amax, 4) + 4 * S_max * abs(V_max - v0) * J_amax * S_max)) / (2 * S_max);
            if ((a_tem - stsetParam.A_amax) > Zero) {
                err = Error_in_calculating_the_acceleration_for_the_single_deceleration_segment;
                return err;
            }
            A_amax = a_tem;
        }
        if ((A_amax - A_ajuge) < Zero) {
            J_amax = sqrt(A_amax * S_max);
        }   
        if(abs(J_amax)<=Zero||abs(A_amax)<=Zero||abs(S_max)<=Zero)
        {
            err = Denominator_is_zero;
            return err;
        }
        Tsa = J_amax / S_max;// 加加速度一阶导的持续时间
        Tja = A_amax / J_amax + Tsa;// 加速度的加速时间
        Ta = Tja + abs(V_max - v0) / A_amax;// 速度的加速时间       
        T = Ta;
        stActParam.q0 = q0;
        stActParam.v0 = v0;
        stActParam.V_max = abs(V_max);
        stActParam.S_max = sign * S_max;
        trackData.A_amax = sign * A_amax;
        trackData.J_amax = sign * J_amax;
        trackData.Tsa = Tsa;
        trackData.Tja = Tja;
        trackData.Ta = Ta;
        trackData.T = T;
        trackData.direction = direction;
    }

    return err;
}
int FifteenSeg_Inter(ST_PlanParams stActParam, ST_PlanData trackData, double t, ST_InterParams& stData) {
    double q0, q1, v0, v1, V_max, A_amax, A_dmax, J_amax, J_dmax, S_max;
    double Tsa, Tsd, Tja, Tjd, Ta, Td, Tv, T;
    double  P, V, A, J, S;
    int direction;
    int err;

    q0 = stActParam.q0;
    q1 = stActParam.q1;
    v0 = stActParam.v0;
    v1 = stActParam.v1;
    V_max = stActParam.V_max;
    S_max = stActParam.S_max;
    A_amax = trackData.A_amax;
    A_dmax = trackData.A_dmax;
    J_amax = trackData.J_amax;
    J_dmax = trackData.J_dmax;
    Tsa = trackData.Tsa;
    Tsd = trackData.Tsd;
    Tja = trackData.Tja;
    Tjd = trackData.Tjd;
    Ta = trackData.Ta;
    Td = trackData.Td;
    Tv = trackData.Tv;
    T = trackData.T;
    direction = trackData.direction;
    err = 0;

    P = 0;
    V = 0;
    A = 0;
    J = 0;
    S = 0;

    if ((0 <= t) && (t <= Tsa)) {
        // 加速段 - 第一部分
        S = S_max;
        J = S_max * t;
        A = 0.5 * S_max * pow(t, 2);
        V = (1.0 / 6.0) * S_max * pow(t, 3) + v0;
        P = (1.0 / 24.0) * S_max * pow(t, 4) + v0 * t + q0;
    }
    else if ((Tsa < t) && (t <= (Tja - Tsa))) {
        S = 0;
        J = J_amax;
        A = J_amax * t - 0.5 * J_amax * Tsa;
        V = (J_amax / 6.0) * pow(Tsa, 2) + 0.5 * J_amax * t * (t - Tsa) + v0;
        P = (J_amax / 24.0) * (2 * t - Tsa) * (2 * t * (t - Tsa) + pow(Tsa, 2)) + v0 * t + q0;
    }
    else if (((Tja - Tsa) < t) && (t <= Tja)) {
        S = -S_max;
        J = -S_max * (t - Tja);
        A = -0.5 * S_max * pow(t - Tja, 2) + A_amax;
        double temp = t - Tja + Tsa;
        V = (S_max / 6.0) * (7 * pow(Tsa, 3) - 9 * pow(Tsa, 2) * (t + Tsa) +
            3 * Tsa * pow(t + Tsa, 2) - pow(temp, 3)) + v0;
        P = (S_max / 24.0) * (-15 * pow(Tsa, 4) + 28 * pow(Tsa, 3) * (t + Tsa) -
            18 * pow(Tsa, 2) * pow(t + Tsa, 2) + 4 * Tsa * pow(t + Tsa, 3) -
            pow(temp, 4)) + v0 * t + q0;
    }
    else if ((Tja < t) && (t <= (Ta - Tja))) {
        S = 0;
        J = 0;
        A = A_amax;
        V = 0.5 * A_amax * (2 * t - Tja) + v0;
        P = (A_amax / 12.0) * (6 * pow(t, 2) - 6 * t * Tja + 2 * pow(Tja, 2) - Tja * Tsa + pow(Tsa, 2)) + v0 * t + q0;
    }
    else if (((Ta - Tja) < t) && (t <= (Ta - Tja + Tsa))) {
        S = -S_max;
        J = -S_max * (t - Ta + Tja);
        A = A_amax - 0.5 * S_max * pow(t - Ta + Tja, 2);
        double temp = t - Ta + Tja;
        V = -(S_max / 6.0) * pow(temp, 3) + 0.5 * A_amax * (2 * t - Tja) + v0;
        P = -(S_max / 24.0) * pow(temp, 4) +
            (A_amax / 12.0) * (6 * pow(t, 2) - 6 * t * Tja + 2 * pow(Tja, 2) - Tja * Tsa + pow(Tsa, 2)) + v0 * t + q0;
    }
    else if (((Ta - Tja + Tsa) < t) && (t <= (Ta - Tsa))) {
        S = 0;
        J = -J_amax;
        A = -0.5 * J_amax * (2 * t - 2 * Ta + Tsa);
        V = -(J_amax / 6.0) * (3 * pow(t - Ta, 2) - 6 * Ta * Tja + 6 * pow(Tja, 2) +
            3 * (t + Ta - 2 * Tja) * Tsa + pow(Tsa, 2)) + v0;
        P = -(J_amax / 24.0) * (4 * pow(t - Ta, 3) - 12 * (2 * t - Ta) * Ta * Tja +
            12 * (2 * t - Ta) * pow(Tja, 2) + 6 * (pow(t, 2) + 2 * t * (Ta - 2 * Tja) - Ta * (Ta - 2 * Tja)) * Tsa +
            4 * (t - Ta) * pow(Tsa, 2) + pow(Tsa, 3)) + v0 * t + q0;
    }
    else if (((Ta - Tsa) < t) && (t <= Ta)) {
        S = S_max;
        J = S_max * (t - Ta);
        A = 0.5 * S_max * pow(t - Ta, 2);
        V = (S_max / 6.0) * pow(t - Ta, 3) + A_amax * (Ta - Tja) + v0;
        P = (S_max / 24.0) * pow(t - Ta, 4) +
            0.5 * A_amax * (2 * t - Ta) * (Ta - Tja) + v0 * t + q0;
    }
    else if ((Ta < t) && (t <= (Ta + Tv))) {
        // 恒速段
        S = 0;
        J = 0;
        A = 0;
        V = V_max;
        P = 0.5 * (V_max - v0) * (2 * t - Ta) + v0 * t + q0;
    }
    else if (((Ta + Tv) < t) && (t <= (Ta + Tv + Tsd))) {
        // 减速段 - 第一部分
        S = -S_max;
        J = S_max * ((T - t) - Td);
        A = -0.5 * S_max * pow((T - t) - Td, 2);
        V = (S_max / 6.0) * pow((T - t) - Td, 3) + A_dmax * (Td - Tjd) + v1;
        P = -(S_max / 24.0) * pow((T - t) - Td, 4) - 0.5 * A_dmax * (2 * (T - t) - Td) * (Td - Tjd) - v1 * (T - t) + q1;
    }
    else if (((Ta + Tv + Tsd) < t) && (t <= (Ta + Tv + Tjd - Tsd))) {
        S = 0;
        J = -J_dmax;
        A = 0.5 * J_dmax * (2 * (T - t) - 2 * Td + Tsd);
        V = -(J_dmax / 6.0) * (3 * pow((T - t) - Td, 2) - 6 * Td * Tjd + 6 * pow(Tjd, 2) +
            3 * ((T - t) + Td - 2 * Tjd) * Tsd + pow(Tsd, 2)) + v1;
        P = (J_dmax / 24.0) * (4 * pow((T - t) - Td, 3) - 12 * (2 * (T - t) - Td) * Td * Tjd +
            12 * (2 * (T - t) - Td) * pow(Tjd, 2) + 6 * (pow(T - t, 2) + 2 * (T - t) * (Td - 2 * Tjd) - Td * (Td - 2 * Tjd)) * Tsd +
            4 * ((T - t) - Td) * pow(Tsd, 2) + pow(Tsd, 3)) - v1 * (T - t) + q1;
    }
    else if (((Ta + Tv + Tjd - Tsd) < t) && (t <= (Ta + Tv + Tjd))) {
        S = S_max;
        J = -S_max * ((T - t) - Td + Tjd);
        A = -A_dmax + 0.5 * S_max * pow((T - t) - Td + Tjd, 2);
        double temp = (T - t) - Td + Tjd;
        V = -(S_max / 6.0) * pow(temp, 3) + 0.5 * A_dmax * (2 * (T - t) - Tjd) + v1;
        P = (S_max / 24.0) * pow(temp, 4) -
            (A_dmax / 12.0) * (6 * pow(T - t, 2) - 6 * (T - t) * Tjd + 2 * pow(Tjd, 2) - Tjd * Tsd + pow(Tsd, 2)) -
            v1 * (T - t) + q1;
    }
    else if (((Ta + Tv + Tjd) < t) && (t <= (T - Tjd))) {
        S = 0;
        J = 0;
        A = -A_dmax;
        V = 0.5 * A_dmax * (2 * (T - t) - Tjd) + v1;
        P = -(A_dmax / 12.0) * (6 * pow(T - t, 2) - 6 * (T - t) * Tjd + 2 * pow(Tjd, 2) - Tjd * Tsd + pow(Tsd, 2)) -
            v1 * (T - t) + q1;
    }
    else if (((T - Tjd) < t) && (t <= (T - Tjd + Tsd))) {
        S = S_max;
        J = -S_max * ((T - t) - Tjd);
        A = 0.5 * S_max * pow((T - t) - Tjd, 2) - A_dmax;
        double temp1 = (T - t) + Tsd;
        double temp2 = (T - t) - Tjd + Tsd;
        V = (S_max / 6.0) * (7 * pow(Tsd, 3) - 9 * pow(Tsd, 2) * temp1 +
            3 * Tsd * pow(temp1, 2) - pow(temp2, 3)) + v1;
        P = -(S_max / 24.0) * (-15 * pow(Tsd, 4) + 28 * pow(Tsd, 3) * temp1 -
            18 * pow(Tsd, 2) * pow(temp1, 2) + 4 * Tsd * pow(temp1, 3) - pow(temp2, 4)) -
            v1 * (T - t) + q1;
    }
    else if (((T - Tjd + Tsd) < t) && (t <= (T - Tsd))) {
        S = 0;
        J = J_dmax;
        A = -J_dmax * (T - t) + 0.5 * J_dmax * Tsd;
        V = (J_dmax / 6.0) * pow(Tsd, 2) + 0.5 * J_dmax * (T - t) * ((T - t) - Tsd) + v1;
        P = -(J_dmax / 24.0) * (2 * (T - t) - Tsd) * (2 * (T - t) * ((T - t) - Tsd) + pow(Tsd, 2)) -
            v1 * (T - t) + q1;
    }
    else if (((T - Tsd) < t) && (t <= T)) {
        S = -S_max;
        J = S_max * (T - t);
        A = -0.5 * S_max * pow(T - t, 2);
        V = (S_max / 6.0) * pow(T - t, 3) + v1;
        P = -(S_max / 24.0) * pow(T - t, 4) - v1 * (T - t) + q1;
    }
    else {
        if(stActParam.enPlanmode == enPositionPlanningMode) //位置模式，超时时间，位置不动
        {
            S = 0;
            J = 0;
            A = 0;
            V = 0;
            P = q1;       
        }else if(stActParam.enPlanmode == enVelocityPlanningMode)                                   //速度模式，超时时间，匀速运动      
        {
            S = 0;
            J = 0;
            A = 0;
            V = V_max;
            P = (S_max / 24.0) * pow(T - Ta, 4) + 0.5 * A_amax * (2 * T - Ta) * (Ta - Tja) + v0 * t + q0  + V_max*(t-T);         
        }
    }

    stData.S = direction * S;
    stData.J = direction * J;
    stData.A = direction * A;
    stData.V = direction * V;
    stData.P = direction * P;

    return err;
}


int stopmotion(double q0, double v0, double a0, double a_max, double j_max, double t,double& T,ST_InterParams& stData)
{
    double J_amax, J_dmax, A_max, A_diff, a_tem;
    int direction;
    double Tsa = 0.0, Tsd = 0.0, Tsv = 0.0;
    T = 0.0;
    double V_tem1 = 0.0, V_tem2 = 0.0;
    double P_tem1 = 0.0, P_tem2 = 0.0;
    double P = 0.0, V = 0.0, A = 0.0, J = 0.0, S = 0.0;

    double v1 = 0.0; // 目标速度 = 0
    double a1 = 0.0; // 目标速度 = 0
    int err = 0;

    J_amax = j_max;
    J_dmax = j_max;
    A_max = a_max;

    // === 下面为 S 型规划 ===
    if ((j_max <= Zero)||a_max <= Zero) 
    {
        err = Invalid_input_parameter;
        return err;
    }

    A_diff = fabs(a0) * fabs(a0) / (2.0 * j_max);
    if (fabs(v0 - v1) < A_diff) 
    {
        err = The_displacement_is_too_small_to_plan;
        return err; 
    }

    // === 判断方向 ===
    direction = (v1 > v0) ? 1.0 : -1.0;
    q0 = direction * q0;
    v0 = direction * v0;
    v1 = direction * v1;
    a0 = direction * a0;
    a1 = direction * a1;

    // === 规划 ===
    if (fabs(A_max - a0) <= Zero) 
    {
        Tsa = 0.0;
        Tsd = fabs(A_max - a1) / J_dmax;
    } else if (fabs(A_max - a1) <= Zero) 
    {
        Tsd = 0.0;
        Tsa = fabs(A_max - a0) / J_amax;
    } else {
        Tsa = fabs(A_max - a0) / J_amax;
        Tsd = fabs(A_max - a1) / J_dmax;
    }
    Tsv = fabs(v1 - v0) / A_max - (Tsa / 2.0) * (1.0 + a0 / A_max) - (Tsd / 2.0) * (1.0 + a1 / A_max);
    if (Tsv < Zero) 
    {
        a_tem = sqrt((2.0 * J_amax * J_dmax * fabs(v0 - v1) + J_dmax * a0 * a0 + J_amax * a1 * a1) / (J_amax + J_dmax));
        A_max = a_tem;
        Tsa = fabs(A_max - a0) / J_amax;
        Tsd = fabs(A_max - a1) / J_dmax;
        Tsv = fabs(v1 - v0) / A_max - (Tsa / 2.0) * (1.0 + a0 / A_max) - (Tsd / 2.0) * (1.0 + a1 / A_max);
        if (Tsv < -Zero || (A_max - a_max) > Zero) 
        {
            A_max = a0;
            Tsa = 0.0;
            Tsd = fabs(A_max - a1) / J_dmax;
            Tsv = fabs(v1 - v0) / A_max - (Tsa / 2.0) * (1.0 + a0 / A_max) - (Tsd / 2.0) * (1.0 + a1 / A_max);
            if (Tsv < -Zero) 
            {
                err = The_displacement_is_too_small_to_plan;
                return err; 
            }
        }
    }

    T = Tsa + Tsv + Tsd;  // 总时间

    if (A_max < a0) {
        J_amax = -J_amax;
    }
    if (A_max < a1) {
        J_dmax = -J_dmax;
    }

    // === 计算每个节点的数据 ===
    V_tem1 = v0 + a0 * Tsa + 0.5 * J_amax * Tsa * Tsa;
    V_tem2 = V_tem1 + A_max * Tsv;
    P_tem1 = q0 + v0 * Tsa + 0.5 * a0 * Tsa * Tsa + (1.0 / 6.0) * J_amax * Tsa * Tsa * Tsa;
    P_tem2 = P_tem1 + V_tem1 * Tsv + 0.5 * A_max * Tsv * Tsv;

    // === 分段求运动学量 ===
    if (t <= 0.0) 
    {
        J = 0;
        A = a0;
        V = v0;
        P = q0;
    } else if (t <= Tsa) 
    {
        // 加加速度阶段
        J = J_amax;
        A = a0 + J_amax * t;
        V = v0 + a0 * t + 0.5 * J_amax * t * t;
        P = q0 + v0 * t + 0.5 * a0 * t * t + (1.0 / 6.0) * J_amax * t * t * t;
    } else if (t <= (Tsa + Tsv)) 
    {
        // 匀加速度阶段
        double dt = t - Tsa;
        J = 0.0;
        A = A_max;
        V = V_tem1 + A_max * dt;
        P = P_tem1 + V_tem1 * dt + 0.5 * A_max * dt * dt;
    } else if (t <= T) {
        // 减加速度阶段
        double dt = t - (Tsa + Tsv);
        J = -J_dmax;
        A = A_max - J_dmax * dt;
        V = V_tem2 + A_max * dt - 0.5 * J_dmax * dt * dt;
        P = P_tem2 + V_tem2 * dt + 0.5 * A_max * dt * dt - (1.0 / 6.0) * J_dmax * dt * dt * dt;
    } else {
        // 结束之后保持
        J = 0.0;
        A = a1;
        V = v1;
        P = P_tem2 + V_tem2 * Tsd + 0.5 * A_max * Tsd * Tsd - (1.0 / 6.0) * J_dmax * Tsd * Tsd * Tsd;
    }

    // 还原方向
    stData.J = direction * J;
    stData.A = direction * A;
    stData.V = direction * V;
    stData.P = direction * P;
    
    return err;
}