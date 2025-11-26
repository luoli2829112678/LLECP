#include "../LLSMC/SoftMotion/motion_algorithm/motion_planning/motion_planning.h"
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <locale.h>
static FILE *g_csv = NULL;

static void csv_close(void) {
    if (g_csv) fclose(g_csv);
}

static void csv_init(const char *path) {
    setlocale(LC_NUMERIC, "C");                 // 保证小数点为'.'
    g_csv = fopen(path, "w");                   // 覆盖写；若想追加用 "a"
    if (!g_csv) {
        perror("fopen csv");
        return;
    }
    setvbuf(g_csv, NULL, _IOLBF, 0);            // 行缓冲，换行即写盘
    fprintf(g_csv, "t,q,v,a,j,compute_us\n");   // 表头
    atexit(csv_close);                          // 程序退出自动关闭
}
static inline uint64_t now_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts); // 单调时钟，不受系统时间调整影响
    return (uint64_t)ts.tv_sec * 1000000ULL + ts.tv_nsec / 1000ULL;
}
int main() {

    csv_init("s_plan.csv");
    printf("S速度验证 Begin\n");
    double t_start, q0, q1, v0, v1, v_max, a_max, j_max, dt;
    t_start = 0;
    q0 = 0;
    q1 = 100;
    v0 = 0;
    v1 = 0;
    v_max = 50;
    a_max = 200;
    j_max = 3000;
    dt = 0.001;
    trajectory_segment res;
    //res = s_curve_generator(q0, q1, v0, v1, v_max, a_max, j_max, t_start, dt);
    STMotionFrame st{0,0,0,0,0};
    double tf = 0;
    do
    {
        uint64_t s = now_us();
        st = s_curve_generator_RT(q0, q1, v0, v1, v_max, a_max, j_max, t_start, dt,tf);
        uint64_t e = now_us();
        printf("S速度规划当前路径, 当前时刻:[%.4f], 位置:[%.4f], 速度:[%.4f], 加速度:[%.4f], 加加速度:[%.4f], 计算用时:[%llu µs]\n", tf, st.q, st.v, st.a, st.j,(unsigned long long)(e - s));
        if (g_csv) {
        fprintf(g_csv, "%.4f,%.4f,%.4f,%.4f,%.4f,%llu\n",
                tf, st.q, st.v, st.a, st.j, (unsigned long long)(e - s));
}
        tf = tf + dt;
    } while (st.r_t>dt);
    
    
    /*
    for (int i = 0; i < res.path_num; i++) {
        printf("S速度规划当前路径序号:[%d], 当前时刻:[%.4f], 位置:[%.4f], 速度:[%.4f], 加速度:[%.4f], 加加速度:[%.4f]\n", i + 1, res.t[i], res.q[i], res.v[i], res.a[i], res.j[i]);
    }
    free_trajectory_segment(&res);
    /*
    printf("S速度验证 End\n");
    printf("多点间实现S型加减速规划 Begin\n");
    double q_points[] = {6, 4, 6, 11, 20};
    double v_points[] = {0, 3, 2, 4, 0};
    int N = 5;
    res = multi_s_curve_generator(q_points, v_points, v_max, a_max, j_max, t_start, dt, N);
    for (int i = 0; i < res.path_num; i++) {
        printf("多点间实现S型加减速规划当前路径序号:[%d], 当前时刻:[%.4f], 位置:[%.4f], 速度:[%.4f], 加速度:[%.4f], 加加速度:[%.4f]\n", i + 1, res.t[i], res.q[i], res.v[i], res.a[i], res.j[i]);
    }
    free_trajectory_segment(&res);
    printf("多点间实现S型加减速规划 End\n");
    printf("过任意给定路径点的S型加减速规划 Begin\n");
    double v_start = 0, v_end = 0;
    res = multi_s_curve_generator_based_on_path(q_points, v_start, v_end, v_max, a_max, j_max, t_start, dt, N);
    for (int i = 0; i < res.path_num; i++) {
        printf("过任意给定路径点的S型加减速规划当前路径序号:[%d], 当前时刻:[%.4f], 位置:[%.4f], 速度:[%.4f], 加速度:[%.4f], 加加速度:[%.4f]\n", i + 1, res.t[i], res.q[i], res.v[i], res.a[i], res.j[i]);
    }
    free_trajectory_segment(&res);
    printf("过任意给定路径点的S型加减速规划 End\n");*/
    return 0;
}