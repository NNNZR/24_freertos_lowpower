#include "lvgl_demo.h"
#include "tim.h"
#include "adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include "key.h"
#include "math.h"
#include "w25qxx.h"
#include "music.h"
#include "i2s.h"
#include "w25qxx.h"
#include "usart.h"
/*-------------
 *    任务
 *-----------*/
#include "../generated/gui_guider.h"
#include "../generated/events_init.h"
 
lv_ui guider_ui;

#define LV_DEMO_TASK_PRIO    3        /*任务优先级*/
#define LV_DEMO_TASK_SIZE    1024*5    /*任务堆栈大小*/
TaskHandle_t lv_demo_Task_Handler;    /*任务句柄*/
void lv_demo_task(void* arguements); /*任务函数*/	

#define ADC_TASK_PRIO      2       /* 任务优先级 */
#define ADC_TASK_SIZE      512    /* 任务堆栈大小（word） */
TaskHandle_t adc_Task_Handler;    /*任务句柄*/
void adc_task(void* parameters); // 任务函数声明

#define W25QXX_TASK_PRIO  4       // 任务优先级
#define W25QXX_TASK_SIZE  256    // 任务堆栈大小
TaskHandle_t w25qxx_Task_Handler; // 任务句柄
void w25qxx_task(void* parameters); // 任务函数声明

#define MUSIC_TASK_PRIO  5       // 任务优先级
#define MUSIC_TASK_SIZE  1024    // 任务堆栈大小
TaskHandle_t music_Task_Handler; // 任务句柄
void music_task(void* parameters); // 任务函数声明





#define CELL_SIZE   40  // 每个格子的像素大小
#define MAZE_W      7  // 迷宫宽度（格子数）
#define MAZE_H      9   // 迷宫高度（格子数）
/*====================================*/
/* 迷宫地图：1=墙，0=空地 */
int maze_map[MAZE_H][MAZE_W] = {
    {1,1,1,1,1,1,1},
    {1,0,1,0,1,0,1},
    {1,1,1,1,1,1,1},
    {1,0,1,0,1,0,1},
    {1,1,1,1,1,1,1},
    {1,0,1,0,1,0,1},
    {1,1,1,1,1,1,1},
    {1,0,1,0,1,0,1},
    {1,1,1,1,1,1,1}
};

//static int maze_map[MAZE_H][MAZE_W] = {
//    {1,1,1,1,1,1,1},
//    {1,0,0,0,0,0,1},
//    {1,1,1,0,1,1,1},
//    {1,0,0,0,0,0,1},
//    {1,1,1,0,1,1,1},
//    {1,0,0,0,0,0,1},
//    {1,1,1,0,1,1,1},
//    {1,0,0,0,0,0,1},
//    {1,1,1,1,1,1,1}
//};
void maze_draw(lv_obj_t * game);
void prim_maze(void);
void tank_init(lv_obj_t * game);
lv_style_t style_wall;
void bullet_system_init(lv_obj_t *parent);
bool bullet_create_ex(lv_obj_t *parent, float x, float y, float angle_deg,
                      int owner_id, int owner_team);
#define M_PI 3.14159265358


#define TEST_ADDR  0x000000   // 测试地址（一般选一个安全的地址，避免破坏数据）
/*=====================================*/
void lvgl_demo_init(void)
{
	

	W25QXX_Init();
//	W25QXX_Erase_Chip(); 
//	
//	
//	u8 txBuf[8] = {0x11,0x22,0x33,0x44,0x55,0xAA,0xBB,0xCC};
//    u8 rxBuf[8] = {0};

//    printf("Write Data: ");
//    for(int i=0; i<sizeof(txBuf); i++)
//    {
//        printf("%02X ", txBuf[i]);
//    }
//    printf("\r\n");

//    // 写测试数据
//    W25QXX_Write(txBuf, TEST_ADDR, sizeof(txBuf));

//    // 读回数据
//    W25QXX_Read(rxBuf, TEST_ADDR, sizeof(rxBuf));

//    printf("Read  Data: ");
//    for(int i=0; i<sizeof(rxBuf); i++)
//    {
//        printf("%02X ", rxBuf[i]);
//    }
//    printf("\r\n");

//    // 比较
//    if(memcmp(txBuf, rxBuf, sizeof(txBuf)) == 0)
//    {
//        printf("W25QXX Init OK, Flash R/W normal.\r\n");
//    }
//    else
//    {
//        printf("W25QXX Init Failed, R/W error!\r\n");
//    }
	
	w25qxxQueue = xQueueCreate(10, sizeof(W25QXX_Request));
	xTaskCreate(
        music_task,           // 任务函数
        "music_task",         // 任务名
        MUSIC_TASK_SIZE,      // 栈深度（word）
        NULL,                 // 参数
        MUSIC_TASK_PRIO,      // 优先级
        &music_Task_Handler   // 任务句柄
    ) ; 
	
	xTaskCreate(
        lv_demo_task,         // 任务函数
        "start_task",        // 任务名
        LV_DEMO_TASK_SIZE,              // 栈深度（单位：word，不是字节）
        NULL,             // 任务参数
        LV_DEMO_TASK_PRIO, // 优先级
        &lv_demo_Task_Handler // 任务句柄
    );
	
	xTaskCreate(
        adc_task,         // 任务函数
        "adc_task",        // 任务名
        ADC_TASK_SIZE,              // 栈深度（单位：word，不是字节）
        NULL,             // 任务参数
        ADC_TASK_PRIO, // 优先级
        &adc_Task_Handler // 任务句柄
    );
	
	xTaskCreate(
        w25qxx_task,         // 任务函数
        "w25qxx_task",        // 任务名
        W25QXX_TASK_SIZE,              // 栈深度（单位：word，不是字节）
        NULL,             // 任务参数
        W25QXX_TASK_PRIO, // 优先级
        &w25qxx_Task_Handler // 任务句柄
    );
}

QueueHandle_t uartCmdQueueHandle;
QueueHandle_t mouseCmdQueueHandle;
SemaphoreHandle_t xI2SSemaphore;



void music_task(void* parameters)
{

	xI2SSemaphore = xSemaphoreCreateBinary();
	WAV_SetVolume(0.5f);
	WAV_PlayFile("0:/1.wav",&hi2s2);  // 播放 SD 卡上的 1.WAV
	for(;;)
	{
		
		if(xSemaphoreTake(xI2SSemaphore, portMAX_DELAY) == pdTRUE)
        {
			update_volume(); 
            wav_proc();
        }
	}

}


/*adc采集电压*/

#define ADC_BUF_LEN            15      /* DMA 缓冲区长度（与题设一致） */
#define BACKLIGHT_ACTIVE_HIGH  0       /* 背光有效电平: 1=高有效, 0=低有效 */
#define DIM_IIR_ALPHA_NUM      1U      /* IIR滤波: 新值权重的分子 (1/8) */
#define DIM_IIR_ALPHA_DEN      8U


static uint16_t AdcBuf[ADC_BUF_LEN];     /* DMA缓冲区 */
static volatile uint16_t g_adc_avg = 0;  /* DMA回调里计算的平均值 */
static volatile BaseType_t g_adc_ready = pdFALSE;

/* ==== 小工具函数 ==== */
static inline uint16_t clamp_u16(uint32_t x, uint16_t lo, uint16_t hi) {
    if (x < lo) return lo;
    if (x > hi) return hi;
    return (uint16_t)x;
}

/* 线性映射: ADC(0..4095) -> 占空(0..100)；使用整数避免浮点 */
static inline uint16_t adc_to_duty(uint16_t adc)
{
    /* 四舍五入：(adc * 100) / 4095 */
    uint32_t duty = ( (uint32_t)adc * 100U + (4095U/2U) ) / 4095U;
    duty = clamp_u16(duty, 0, 100U);  /* 与 ARR=100 对齐 */
    /* 背光极性处理 */
    if (!BACKLIGHT_ACTIVE_HIGH) {
        duty = 100U - duty;
    }
    duty +=5;
    return (uint16_t)duty;
}

/* ==== DMA 回调：满传输完成时计算平均并通知任务 ==== */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance != hadc1.Instance) return;

    uint32_t sum = 0;
    for (uint32_t i = 0; i < ADC_BUF_LEN; i++) sum += AdcBuf[i];
    g_adc_avg = (uint16_t)(sum / ADC_BUF_LEN);

    /* 通知任务处理（无阻塞 FromISR 版本） */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    g_adc_ready = pdTRUE;
    if (adc_Task_Handler) {
        vTaskNotifyGiveFromISR(adc_Task_Handler, &xHigherPriorityTaskWoken);
    }
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)AdcBuf, ADC_BUF_LEN);
}


/* ==== 可选：把电压值算出来（用于调试打印）==== */
static inline float adc_to_voltage(uint16_t adc)
{
    return (3.3f * adc) / (float)4095U;
}




/* ==== 任务函数：启动外设并根据 ADC 控制 PWM ==== */

volatile BaseType_t mouseCmdNew = pdFALSE;

void adc_task(void *arguments)
{
    (void)arguments;

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)AdcBuf, ADC_BUF_LEN);

    uint16_t duty_now = 0;
    uint16_t duty_filt = 0;

    TickType_t lastMouseTick = xTaskGetTickCount();
    enum {BRIGHT_NORMAL, BRIGHT_10, BRIGHT_0} bright_state = BRIGHT_NORMAL;
	

	
    for (;;)
	{
		
        ulTaskNotifyTake(pdTRUE, 100);

        TickType_t now = xTaskGetTickCount();

        /* 只检测队列是否有新数据，不读取队列 */
        if (mouseCmdNew == pdTRUE) {
		lastMouseTick = now;       // 更新最后接收时间
		bright_state = BRIGHT_NORMAL;
		mouseCmdNew = pdFALSE;     // 重置标志
		}	

        /* 默认用 ADC 控制亮度 */
        if (g_adc_ready) {
            g_adc_ready = pdFALSE;
            duty_now = adc_to_duty(g_adc_avg);
        }

        /* 状态机处理超时逻辑 */
        switch (bright_state) {
            case BRIGHT_NORMAL:
                if ((now - lastMouseTick) > pdMS_TO_TICKS(10000)) {
                    bright_state = BRIGHT_10;
                    lastMouseTick = now;  // 计时 10 秒
                    duty_now = 10;
                }
                break;

            case BRIGHT_10:
                if ((now - lastMouseTick) > pdMS_TO_TICKS(5000)) {
                    bright_state = BRIGHT_0;
                    duty_now = 0;
                } else {
                    duty_now = 10;
                }
                break;

            case BRIGHT_0:
                duty_now = 0;
                break;
        }

        /* IIR 滤波 */
        duty_filt = (uint16_t)((duty_filt * (DIM_IIR_ALPHA_DEN - DIM_IIR_ALPHA_NUM)
                     + duty_now * DIM_IIR_ALPHA_NUM) / DIM_IIR_ALPHA_DEN);

        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty_filt);

        vTaskDelay(20);
    }
}



void w25qxx_task(void* params)
{
    W25QXX_Request req;
	
    for (;;)
    {
        if (xQueueReceive(w25qxxQueue, &req, portMAX_DELAY) == pdTRUE)
        {
            if (req.type == WRITE)
                W25QXX_Write(req.buf, req.addr, req.len);
            else
                W25QXX_Read(req.buf, req.addr, req.len);
        }
    }
}


uint8_t user_point[5]={0};
void lv_demo_task(void* arguements)
{
	
	uartCmdQueueHandle = xQueueCreate(5, 10); 
	mouseCmdQueueHandle = xQueueCreate(5, 10);	
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
     setup_ui(&guider_ui);
     events_init(&guider_ui);
	char cmd[] = "{\"cmd\":\"getTime\"}\n";
    HAL_UART_Transmit(&huart6, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
	for(;;)
	{
	 lv_timer_handler();
	  vTaskDelay(5);   
	}
}






/*-------------
 *    函数
 *-----------*/



void game1_event_init()
{
	

}

//#define DEBUG_COLLISION 0
#define MARGIN 7
#define COLS 3
#define ROWS 4
#define CELL_W ((240 - 2*MARGIN) / COLS) // 73
#define CELL_H ((320 - 2*MARGIN) / ROWS) // 75
#define LINE_WIDTH 6

uint16_t zoom=256;
lv_coord_t tank_l=40,tank_w=28;


void get_cell_from_xy(int x, int y, int *row, int *col)
{
    // 默认 -1 表示不在格子内
    *row = -1;
    *col = -1;

    // 判断是否在迷宫范围内
    if (x < MARGIN || x >= MARGIN + CELL_W * COLS) return;
    if (y < MARGIN || y >= MARGIN + CELL_H * ROWS) return;

    // 计算行列（向下取整）
    *col = (x - MARGIN) / CELL_W;
    *row = (y - MARGIN) / CELL_H;
}




/*调试*/

#ifdef DEBUG_COLLISION 
static lv_obj_t *tank_bbox = NULL;  // 碰撞箱显示对象
#endif
#ifdef DEBUG_COLLISION
void debug_collision_init(void)
{
    if (!tank_bbox) {
        tank_bbox = lv_line_create(lv_scr_act());

        static lv_style_t style;
        lv_style_init(&style);
        lv_style_set_line_color(&style, lv_color_hex(0xFF0000)); // 红色
        lv_style_set_line_width(&style, 2);

        lv_obj_add_style(tank_bbox, &style, 0);
    }
}
#endif
#ifdef DEBUG_COLLISION
void debug_collision_update(double x, double y, double angle)
{
    if (!tank_bbox) return;

    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad), sinA = sin(rad);
    double hw = tank_l * 0.5, hh = tank_w * 0.5;

    // 四个顶点（旋转矩形）
    double corners[4][2] = {
        { -hw, -hh },
        {  hw, -hh },
        {  hw,  hh },
        { -hw,  hh }
    };

    static lv_point_t pts[5];
    for (int i=0; i<4; i++) {
        double rx = corners[i][0]*cosA - corners[i][1]*sinA;
        double ry = corners[i][0]*sinA + corners[i][1]*cosA;
        pts[i].x = (lv_coord_t)(x + rx);
        pts[i].y = (lv_coord_t)(y + ry);
    }
    pts[4] = pts[0]; // 闭合矩形

    lv_line_set_points(tank_bbox, pts, 5);
}
#endif

/**********************************坦克***********************************/


int tank_Cstep = 4;   // 移动速度
int tank_Cangle = 6;  // 每次旋转的角度
static lv_obj_t *tank_img[2];
static double tank_x[2], tank_y[2], tank_angle[2];
static int LOCAL_TANK_ID[2] = {-1, -1};

lv_timer_t *tank_move_timer;

static double tank1_x = 40;
static double tank1_y = 50;
static double tank1_angle = 0;



#define MAX_TANKS 8
int  BULLET_SPAWN_GRACE_MS=320;   // 子弹刚生成的自伤豁免时间

typedef struct {
    lv_obj_t *img;     // 可选：对应的 LVGL 图片对象
    double x, y;       // 中心坐标
    double angle;      // 角度（度）
    double l, w;       // 车体尺寸：l=horiz=tank_l, w=vert=tank_w
    bool   alive;      // 是否在场/可被命中
    int    team;       // 阵营（可选，用于队友免伤）
} Tank;

static Tank g_tanks[MAX_TANKS];
static int  g_tank_count = 0;

//static int LOCAL_TANK_ID = -1;


void lv_obj_set_pos_center(lv_obj_t * img,lv_coord_t w,lv_coord_t h, lv_coord_t x, lv_coord_t y)
{
    if(img == NULL) return;

    /* 计算左上角坐标 */
    lv_coord_t left = x - w / 2;
    lv_coord_t top  = y - h / 2;

    lv_obj_set_pos(img, left, top);
}



// 注册一辆坦克，返回其 id（索引），失败返回 -1
static int tank_register(lv_obj_t *img, double x, double y,
                         double angle_deg, double l, double w, int team)
{
    for (int i = 0; i < MAX_TANKS; ++i) {
        if (!g_tanks[i].alive) {
            g_tanks[i].img   = img;
            g_tanks[i].x     = x;
            g_tanks[i].y     = y;
            g_tanks[i].angle = angle_deg;
            g_tanks[i].l     = l;
            g_tanks[i].w     = w;
            g_tanks[i].team  = team;
            g_tanks[i].alive = true;
            if (i >= g_tank_count) g_tank_count = i + 1;
            return i;
        }
    }
    return -1;
}

// 更新坦克状态（比如你在更新移动后调用）
static inline void tank_set_state(int id, double x, double y, double angle_deg)
{
    if (id < 0 || id >= g_tank_count || !g_tanks[id].alive) return;
    g_tanks[id].x = x;
    g_tanks[id].y = y;
    g_tanks[id].angle = angle_deg;
}

// 若有需要可移除/击毁
static inline void tank_kill(int id) {
    if (id < 0 || id >= g_tank_count) return;
    g_tanks[id].alive = false;
}

// 工具：点到线段的平方距离（如需备用）
static double dist2_point_seg(double px, double py,
                              double ax, double ay, double bx, double by)
{
    double vx = bx - ax, vy = by - ay;
    double wx = px - ax, wy = py - ay;
    double c1 = vx*wx + vy*wy;
    if (c1 <= 0) return wx*wx + wy*wy;
    double c2 = vx*vx + vy*vy;
    if (c2 <= c1) {
        double dx = px - bx, dy = py - by;
        return dx*dx + dy*dy;
    }
    double t = c1 / c2;
    double projx = ax + t*vx, projy = ay + t*vy;
    double dx = px - projx, dy = py - projy;
    return dx*dx + dy*dy;
}

/************* 旋转矩形工具函数们 *************/

/* 计算旋转坦克的四个顶点（按顺时针），中心(x,y)，角度angle(度)，尺寸 w=horiz=tank_l, h=vert=tank_w */
static void get_tank_corners(double x, double y, double angle,
                             double w, double h, double out[4][2])
{
    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad), sinA = sin(rad);
    double hw = w * 0.5, hh = h * 0.5;

    // 本地坐标（相对中心）：左上、右上、右下、左下（顺时针）
    double local[4][2] = {
        {-hw, -hh}, { hw, -hh}, { hw,  hh}, {-hw,  hh}
    };

    for (int i = 0; i < 4; i++) {
        double lx = local[i][0], ly = local[i][1];
        out[i][0] = x + lx * cosA - ly * sinA;
        out[i][1] = y + lx * sinA + ly * cosA;
    }
}

/* 将多边形(顶点数n)投影到给定轴(ax,ay)上，求[min,max] */
static void project_polygon(const double (*poly)[2], int n,
                            double ax, double ay,
                            double *min_out, double *max_out)
{
    // 可不归一化；若想稳一点可做归一化
    double len2 = ax*ax + ay*ay;
    if (len2 > 1e-12) { // 归一化，避免极小轴影响数值稳定
        double inv = 1.0 / sqrt(len2);
        ax *= inv; ay *= inv;
    }

    double p = poly[0][0]*ax + poly[0][1]*ay;
    double minv = p, maxv = p;

    for (int i = 1; i < n; i++) {
        p = poly[i][0]*ax + poly[i][1]*ay;
        if (p < minv) minv = p;
        if (p > maxv) maxv = p;
    }
    *min_out = minv; *max_out = maxv;
}

/* 区间是否重叠 */
static inline bool interval_overlap(double minA, double maxA,
                                    double minB, double maxB)
{
    return !(maxA < minB || maxB < minA);
}

/* 旋转矩形(tank_poly) vs 轴对齐矩形(rx1,ry1,rx2,ry2) 的SAT检测 */
static bool rect_vs_rect(const double tank_poly[4][2],
                         double rx1, double ry1,
                         double rx2, double ry2)
{
    // 4个墙角点（轴对齐）
    double wall_poly[4][2] = {
        {rx1, ry1}, {rx2, ry1}, {rx2, ry2}, {rx1, ry2}
    };

    // 需要测试的分离轴：
    // 1) 坦克四条边的法线
    // 2) 墙的两条主轴(1,0)与(0,1)（足够覆盖墙边法线）
    double axes[6][2];
    int axis_cnt = 0;

    for (int i = 0; i < 4; i++) {
        int j = (i + 1) & 3;
        double dx = tank_poly[j][0] - tank_poly[i][0];
        double dy = tank_poly[j][1] - tank_poly[i][1];
        // 边的法线 (-dy, dx)
        axes[axis_cnt][0] = -dy;
        axes[axis_cnt][1] =  dx;
        axis_cnt++;
    }
    axes[axis_cnt][0] = 1; axes[axis_cnt][1] = 0; axis_cnt++;
    axes[axis_cnt][0] = 0; axes[axis_cnt][1] = 1; axis_cnt++;

    // SAT：任一轴上不重叠 => 不相交
    for (int i = 0; i < axis_cnt; i++) {
        double ax = axes[i][0], ay = axes[i][1];
        // 跳过极短轴，避免数值问题
        if (ax*ax + ay*ay < 1e-12) continue;

        double minA, maxA, minB, maxB;
        project_polygon(tank_poly, 4, ax, ay, &minA, &maxA);
        project_polygon(wall_poly, 4, ax, ay, &minB, &maxB);

        if (!interval_overlap(minA, maxA, minB, maxB)) {
            return false; // 分离 -> 不碰撞
        }
    }
    return true; // 所有轴均重叠 -> 碰撞
}

/************* 覆盖格子+四面墙检测 *************/

/* 只检查坦克“实际覆盖”的格子集合里的墙，避免全遍历；支持旋转 */
static bool check_collision(double x, double y, double angle)
{
    // 计算坦克四角
    double tank_poly[4][2];
    get_tank_corners(x, y, angle, tank_l, tank_w, tank_poly);

    // AABB 包围盒 -> 转成格子范围
    double min_x = tank_poly[0][0], max_x = tank_poly[0][0];
    double min_y = tank_poly[0][1], max_y = tank_poly[0][1];
    for (int i = 1; i < 4; i++) {
        if (tank_poly[i][0] < min_x) min_x = tank_poly[i][0];
        if (tank_poly[i][0] > max_x) max_x = tank_poly[i][0];
        if (tank_poly[i][1] < min_y) min_y = tank_poly[i][1];
        if (tank_poly[i][1] > max_y) max_y = tank_poly[i][1];
    }

    // 转格子索引（向下取整）
    int min_col = (int)((min_x - MARGIN) / CELL_W);
    int max_col = (int)((max_x - MARGIN) / CELL_W);
    int min_row = (int)((min_y - MARGIN) / CELL_H);
    int max_row = (int)((max_y - MARGIN) / CELL_H);

    // 边界裁剪
    if (max_col < 0 || max_row < 0 || min_col >= COLS || min_row >= ROWS) {
        // 完全在迷宫外侧，视为碰撞
        return true;
    }
    if (min_col < 0) min_col = 0;
    if (min_row < 0) min_row = 0;
    if (max_col >= COLS) max_col = COLS - 1;
    if (max_row >= ROWS) max_row = ROWS - 1;

    // 遍历覆盖范围内的格子，检查该格子四面墙
    for (int r = min_row; r <= max_row; r++) {
        for (int c = min_col; c <= max_col; c++) {

            // 上边墙：水平条 (r, c..c+1)
            if (maze_map[r*2][c*2+1]) {
                double wy1 = MARGIN + CELL_H * r-LINE_WIDTH/2;
                double wy2 = wy1 + LINE_WIDTH;
                double wx1 = MARGIN + CELL_W * c;
                double wx2 = wx1 + CELL_W;
                if (rect_vs_rect(tank_poly, wx1, wy1, wx2, wy2)) return true;
            }

            // 下边墙：水平条 (r+1, c..c+1)
            if (maze_map[(r+1)*2][c*2+1]) {
                double wy1 = MARGIN + CELL_H * (r + 1)-LINE_WIDTH/2;
                double wy2 = wy1 + LINE_WIDTH;
                double wx1 = MARGIN + CELL_W * c;
                double wx2 = wx1 + CELL_W;
                if (rect_vs_rect(tank_poly, wx1, wy1, wx2, wy2)) return true;
            }

            // 左边墙：垂直条 (r..r+1, c)
            if (maze_map[r*2+1][c*2]) {
                double wx1 = MARGIN + CELL_W * c-LINE_WIDTH/2;
                double wx2 = wx1 + LINE_WIDTH;
                double wy1 = MARGIN + CELL_H * r;
                double wy2 = wy1 + CELL_H;
                if (rect_vs_rect(tank_poly, wx1, wy1, wx2, wy2)) return true;
            }

            // 右边墙：垂直条 (r..r+1, c+1)
            if (maze_map[r*2+1][c*2+2]) {
                double wx1 = MARGIN + CELL_W * (c + 1)-LINE_WIDTH/2;
                double wx2 = wx1 + LINE_WIDTH;
                double wy1 = MARGIN + CELL_H * r;
                double wy2 = wy1 + CELL_H;
                if (rect_vs_rect(tank_poly, wx1, wy1, wx2, wy2)) return true;
            }
        }
    }

    return false; // 没撞到
}
//static bool screen2_loaded = false;
/* 获取控制后的新坐标，并更新图像位置和角度 */
static void tank_update_xy(lv_obj_t *game)
{
#ifdef DEBUG_COLLISION
    debug_collision_update(tank_x[idx], tank_y[idx], tank_angle[idx]);
#endif
    
	double new_x1 = tank_x[1];
    double new_y1 = tank_y[1];
    double new_angle1 = tank_angle[1 ];
	
	double new_x0 = tank_x[0];
    double new_y0 = tank_y[0];
    double new_angle0 = tank_angle[0 ];

    char cmd[10];
    if (xQueueReceive(mouseCmdQueueHandle, cmd, 0) == pdPASS) {
        if (strcmp(cmd, "RR\r\n") == 0) {
            new_angle1 += tank_Cangle;
        } else if (strcmp(cmd, "RL\r\n") == 0) {
            new_angle1 -= tank_Cangle;
        } else if (strcmp(cmd, "RF\r\n") == 0) {
            new_x1 -= cos(tank_angle[1] * M_PI / 180.0f) * tank_Cstep;
            new_y1 -= sin(tank_angle[1] * M_PI / 180.0f) * tank_Cstep;
        } else if (strcmp(cmd, "RB\r\n") == 0) {
            new_x1 += cos(tank_angle[1] * M_PI / 180.0f) * tank_Cstep;
            new_y1 += sin(tank_angle[1] * M_PI / 180.0f) * tank_Cstep;
        }

        if (strcmp(cmd, "RS\r\n") == 0) {
            lv_coord_t real_l = tank_l * zoom / 512;
            float sx = tank_x[1] - (float)(real_l * cosf(tank_angle[1] * M_PI / 180.0f));
            float sy = tank_y[1] - (float)(real_l * sinf(tank_angle[1] * M_PI / 180.0f));
            bullet_create_ex(game, sx, sy, tank_angle[1] - 180, LOCAL_TANK_ID[1], /*owner_team=*/0);
        }
		
		if (strcmp(cmd, "LR\r\n") == 0) {
            new_angle0 += tank_Cangle;
        } else if (strcmp(cmd, "LL\r\n") == 0) {
            new_angle0 -= tank_Cangle;
        } else if (strcmp(cmd, "LF\r\n") == 0) {
            new_x0 -= cos(tank_angle[0] * M_PI / 180.0f) * tank_Cstep;
            new_y0 -= sin(tank_angle[0] * M_PI / 180.0f) * tank_Cstep;
        } else if (strcmp(cmd, "LB\r\n") == 0) {
            new_x0 += cos(tank_angle[0] * M_PI / 180.0f) * tank_Cstep;
            new_y0 += sin(tank_angle[0] * M_PI / 180.0f) * tank_Cstep;
        }

        if (strcmp(cmd, "LS\r\n") == 0) {
            lv_coord_t real_l = tank_l * zoom / 512;
            float sx = tank_x[0] - (float)(real_l * cosf(tank_angle[0] * M_PI / 180.0f));
            float sy = tank_y[0] - (float)(real_l * sinf(tank_angle[0] * M_PI / 180.0f));
            bullet_create_ex(game, sx, sy, tank_angle[0] - 180, LOCAL_TANK_ID[0], /*owner_team=*/0);
        }
    }

	if (!check_collision(new_x0, new_y0, new_angle0)) {
        tank_x[0] = new_x0;
        tank_y[0] = new_y0;
        tank_angle[0] = new_angle0;
    }
	
    if (!check_collision(new_x1, new_y1, new_angle1)) {
        tank_x[1] = new_x1;
        tank_y[1] = new_y1;
        tank_angle[1] = new_angle1;
    }

	if (tank_angle[0] >= 360) tank_angle[1] -= 360;
    if (tank_angle[0] < 0) tank_angle[1] += 360;
	
    if (tank_angle[1] >= 360) tank_angle[1] -= 360;
    if (tank_angle[1] < 0) tank_angle[1] += 360;

	lv_obj_set_pos_center(tank_img[0], tank_l, tank_w,
                          (lv_coord_t)tank_x[0], (lv_coord_t)tank_y[0]);
    lv_img_set_angle(tank_img[0], tank_angle[0] * 10);
	
    lv_obj_set_pos_center(tank_img[1], tank_l, tank_w,
                          (lv_coord_t)tank_x[1], (lv_coord_t)tank_y[1]);
    lv_img_set_angle(tank_img[1], tank_angle[1] * 10);

    if (!check_collision(new_x0, new_y0, new_angle0)) {
        if (LOCAL_TANK_ID[0] >= 0) {
            tank_set_state(LOCAL_TANK_ID[0], tank_x[0], tank_y[0], tank_angle[0]);
        }
    }
	if (!check_collision(new_x1, new_y1, new_angle1)) {
        if (LOCAL_TANK_ID[1] >= 0) {
            tank_set_state(LOCAL_TANK_ID[1], tank_x[1], tank_y[1], tank_angle[1]);
        }
    }
}

/* ================= 定时器回调 ================= */
void tank_move_timer_cb(lv_timer_t *timer)
{
    lv_obj_t *game = timer->user_data;

    if (lv_obj_is_valid(game)) {
        tank_update_xy(game);   // 更新坦克位置
    }
}


LV_IMG_DECLARE(tankgreen4026);
LV_IMG_DECLARE(_tankred_alpha_40x26);
int doublecheck=0;
int chose_id=1;
void tank_init(lv_obj_t *game)
{
#ifdef DEBUG_COLLISION
    debug_collision_init();
#endif
    // --- 坦克1 ---
    tank_img[0] = lv_img_create(game);
	if(chose_id==1)lv_img_set_src(tank_img[0], &tankgreen4026);
	else lv_img_set_src(tank_img[0], &_tankred_alpha_40x26);
    lv_obj_move_background(tank_img[0]);
    tank_x[0] = 40;
    tank_y[0] = 50;
    tank_angle[0] = 0;

    if (LOCAL_TANK_ID[0] < 0) {
        LOCAL_TANK_ID[0] = tank_register(tank_img[0], tank_x[0], tank_y[0],
                                         tank_angle[0], tank_l, tank_w, 0);
    }

    // --- 坦克2 ---
    tank_img[1] = lv_img_create(game);
	if(chose_id==1)lv_img_set_src(tank_img[1], &_tankred_alpha_40x26);
    else lv_img_set_src(tank_img[1], &tankgreen4026);
    lv_obj_move_background(tank_img[1]);
    tank_x[1] = 240-40;
    tank_y[1] = 320-50;
    tank_angle[1] = 180;

    if (LOCAL_TANK_ID[1] < 0) {
        LOCAL_TANK_ID[1] = tank_register(tank_img[1], tank_x[1], tank_y[1],
                                         tank_angle[1], tank_l, tank_w, 0);
    }
	 doublecheck=1;
		tank_move_timer = lv_timer_create(tank_move_timer_cb, 10, game);

}

/******************************迷宫**********************************/

static lv_obj_t * create_line(lv_obj_t * parent, int x1, int y1, int x2, int y2, int thickness)
{
    /* 分配两个点 */
    lv_point_t * pts = lv_mem_alloc(sizeof(lv_point_t) * 2);
    pts[0].x = x1;
    pts[0].y = y1;
    pts[1].x = x2;
    pts[1].y = y2;

    /* 创建线对象 */
    lv_obj_t * line = lv_line_create(parent);
    lv_line_set_points(line, pts, 2);
    lv_obj_add_style(line, &style_wall, 0);
    lv_obj_set_style_line_width(line, thickness, LV_PART_MAIN);

//    lv_mem_free(pts);  // 安全释放
    /* 返回 lv_obj_t*，方便后续隐藏/显示 */
    return line;
}



typedef struct {
    int x, y;
    int px, py; // 父节点
} Edge;

// 随机打乱函数
extern RNG_HandleTypeDef hrng; // 已初始化的 RNG

// 用硬件 RNG 获取随机数
int hw_rand(int max) {
    uint32_t value = 0;
    HAL_RNG_GenerateRandomNumber(&hrng, &value);
    return value % max; // 返回 0 ~ max-1
}


// 生成迷宫
void prim_maze() {
    for (int y = 0; y < MAZE_H; y++)
        for (int x = 0; x < MAZE_W; x++)
            maze_map[y][x] = 1; // 全部设墙

    // 随机起点 (奇数坐标)
    int sx = hw_rand(MAZE_W/2) * 2 + 1;
    int sy = hw_rand(MAZE_H/2) * 2 + 1;
    maze_map[sy][sx] = 0;

    Edge edges[MAZE_H * MAZE_W];
    int edge_count = 0;

    int dx[4] = {2, -2, 0, 0};
    int dy[4] = {0, 0, 2, -2};

    // 添加初始边
    for (int d = 0; d < 4; d++) {
        int nx = sx + dx[d];
        int ny = sy + dy[d];
        if (nx > 0 && nx < MAZE_W && ny > 0 && ny < MAZE_H) {
            edges[edge_count++] = (Edge){nx, ny, sx, sy};
        }
    }

    while (edge_count > 0) {
        int idx = hw_rand(edge_count); // 用硬件 RNG 随机选择边
        Edge e = edges[idx];
        edges[idx] = edges[--edge_count];

        if (maze_map[e.y][e.x] == 1) {
            maze_map[e.y][e.x] = 0;
            maze_map[(e.y + e.py)/2][(e.x + e.px)/2] = 0;

            for (int d = 0; d < 4; d++) {
                int nx = e.x + dx[d];
                int ny = e.y + dy[d];
                if (nx > 0 && nx < MAZE_W && ny > 0 && ny < MAZE_H && maze_map[ny][nx] == 1) {
                    edges[edge_count++] = (Edge){nx, ny, e.x, e.y};
                }
            }
        }
    }
}



/**********************************子弹**********************************/
#define MAX_BULLETS 10
#define BULLET_RADIUS 3
float BULLET_SPEED=250.0f;      // 单位：像素/秒（可按需调整）
#define BULLET_LIFETIME_MS 15000  // 子弹生存时间，毫秒
#define TIMER_PERIOD_MS 20       // 定时器周期 ms (~60 FPS)

typedef struct {
    lv_obj_t *obj;
    float x, y;
    float vx, vy;
    uint32_t start_time;
    bool active;

    int prev_row;
    int prev_col;

    int owner_id;   // 新增：发射者坦克 id（-1 表示未知）
    int owner_team; // 新增：发射者阵营（用于队友免伤等）
} Bullet;


static Bullet bullets[MAX_BULLETS];
 lv_timer_t *bullet_timer = NULL;



static inline void project_circle(double cx, double cy, double r,
                                  double ax, double ay,
                                  double *min_out, double *max_out)
{
    double len2 = ax*ax + ay*ay;
    if (len2 > 1e-12) {
        double inv = 1.0 / sqrt(len2);
        ax *= inv; ay *= inv;
    }
    double c = cx*ax + cy*ay;
    *min_out = c - r;
    *max_out = c + r;
}

// 圆(子弹) vs 旋转矩形(四角)的 SAT 检测
static bool circle_vs_rotrect_SAT(double cx, double cy, double r,
                                  const double rect_poly[4][2])
{
    // 1) 四条边法线
    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) & 3;
        double dx = rect_poly[j][0] - rect_poly[i][0];
        double dy = rect_poly[j][1] - rect_poly[i][1];
        double ax = -dy, ay = dx; // 边法线

        double minR, maxR, minC, maxC;
        project_polygon(rect_poly, 4, ax, ay, &minR, &maxR);
        project_circle  (cx, cy, r,   ax, ay, &minC, &maxC);
        if (!interval_overlap(minR, maxR, minC, maxC)) return false;
    }

    // 2) 额外轴：圆心指向“最近的矩形顶点”的向量
    int nearest = 0;
    double best_d2 = 1e300;
    for (int i = 0; i < 4; ++i) {
        double dx = rect_poly[i][0] - cx;
        double dy = rect_poly[i][1] - cy;
        double d2 = dx*dx + dy*dy;
        if (d2 < best_d2) { best_d2 = d2; nearest = i; }
    }
    double ax = cx - rect_poly[nearest][0];
    double ay = cy - rect_poly[nearest][1];
    if (ax*ax + ay*ay > 1e-12) {
        double minR, maxR, minC, maxC;
        project_polygon(rect_poly, 4, ax, ay, &minR, &maxR);
        project_circle  (cx, cy, r,   ax, ay, &minC, &maxC);
        if (!interval_overlap(minR, maxR, minC, maxC)) return false;
    }

    return true; // 所有轴均有重叠 -> 相交
}



extern uint8_t event_key;
extern bool click_event;
int hit_id=-1;


// 命中回调：可在这里做扣血/爆炸/得分等
void on_bullet_hit_tank(Bullet *b, int tank_id)
{
    (void)b;
    // 示例：击毁该坦克
//    tank_kill(tank_id);
	if(doublecheck>0)
	{
	click_event=true;
	event_key=10;
	doublecheck-=1;
	}
    // 打印命中信息
	hit_id=tank_id;
    printf("子弹命中坦克 %d\n", tank_id);

    // TODO: 播放爆炸/扣血/UI 等
}

// 计算子弹 vs 所有坦克的碰撞
static bool bullet_check_collision(Bullet *b)
{
    // 子弹圆数据
    double cx = b->x;
    double cy = b->y;
    double r  = BULLET_RADIUS;

    uint32_t now = lv_tick_get();
	
    for (int id = 0; id < g_tank_count; ++id) {
        Tank *t = &g_tanks[id];
        if (!t->alive) continue;

//        // （可选）队友免伤
//        if (b->owner_team >= 0 && t->team >= 0 && b->owner_team == t->team) {
//            // 可视需要开放“队友可伤”则删除此段
//            continue;
//        }

//        // （可选）短暂自伤豁免
        if (b->owner_id == id && now - b->start_time < BULLET_SPAWN_GRACE_MS) {
            continue;
        }

        // 快速 AABB 排除：用坦克四角计算 AABB，并与圆的 AABB 先做粗判
        double poly[4][2];
        get_tank_corners(t->x, t->y, t->angle, t->l, t->w, poly);

        double minx = poly[0][0], maxx = poly[0][0];
        double miny = poly[0][1], maxy = poly[0][1];
        for (int i = 1; i < 4; ++i) {
            if (poly[i][0] < minx) minx = poly[i][0];
            if (poly[i][0] > maxx) maxx = poly[i][0];
            if (poly[i][1] < miny) miny = poly[i][1];
            if (poly[i][1] > maxy) maxy = poly[i][1];
        }
        if (cx + r < minx || cx - r > maxx || cy + r < miny || cy - r > maxy) {
            continue; // AABB 不相交 -> 一定不碰
        }

        // 精确：圆 vs 旋转矩形的 SAT
        if (circle_vs_rotrect_SAT(cx, cy, r, poly)) {
            on_bullet_hit_tank(b, id); // 触发命中事件（可选）
            return true;               // 通知外层删除子弹
        }
    }

    return false;
}


// 返回 0 = 没墙, 1 = 垂直墙 (左右墙), 2 = 水平墙 (上下墙)
static int wall_between(int row1, int col1, int row2, int col2)
{
    if (abs(row1 - row2) + abs(col1 - col2) != 1) {
        return 0; // 不是相邻格子
    }

    // 水平方向移动
    if (row1 == row2) {
        int row = row1;
        if (col2 > col1) {
            // 往右 → 检查右墙
            if (maze_map[2*row+1][2*col1+2]) return 1;
        } else {
            // 往左 → 检查左墙
            if (maze_map[2*row+1][2*col1]) return 1;
        }
    }

    // 垂直方向移动
    if (col1 == col2) {
        int col = col1;
        if (row2 > row1) {
            // 往下 → 检查下墙
            if (maze_map[2*row1+2][2*col+1]) return 2;
        } else {
            // 往上 → 检查上墙
            if (maze_map[2*row1][2*col+1]) return 2;
        }
    }

    return 0;
}



static void bullet_update_one()
{
    uint32_t now = lv_tick_get();
    const float dt = TIMER_PERIOD_MS / 1000.0f;

    const int scr_w = lv_disp_get_hor_res(NULL);
    const int scr_h = lv_disp_get_ver_res(NULL);

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;

        if (now - bullets[i].start_time > BULLET_LIFETIME_MS) {
            lv_obj_del(bullets[i].obj);
            bullets[i].active = false;
            continue;
        }

        int old_row, old_col;
        get_cell_from_xy((int)bullets[i].x, (int)bullets[i].y, &old_row, &old_col);
                // 保存更新前的位置
        float old_x = bullets[i].x;
        float old_y = bullets[i].y;

        // 按速度更新位置
        bullets[i].x += bullets[i].vx * dt;
        bullets[i].y += bullets[i].vy * dt;

        // 更新后所在格子
        int new_row, new_col;
        get_cell_from_xy((int)bullets[i].x, (int)bullets[i].y, &new_row, &new_col);

        // 检查是否跨格子
        if (old_row >= 0 && old_col >= 0 &&
            new_row >= 0 && new_col >= 0 &&
            (old_row != new_row || old_col != new_col)) {

            int wall_type = wall_between(old_row, old_col, new_row, new_col);
            if (wall_type == 1) {
                // 左右墙 → 回退位置，并反转X
                bullets[i].x = old_x;   // 回到上一步安全位置
                bullets[i].vx = -bullets[i].vx;
            } else if (wall_type == 2) {
                // 上下墙 → 回退位置，并反转Y
                bullets[i].y = old_y;
                bullets[i].vy = -bullets[i].vy;
            }
        }


        lv_obj_set_pos(bullets[i].obj,
                       (int)roundf(bullets[i].x - BULLET_RADIUS),
                       (int)roundf(bullets[i].y - BULLET_RADIUS));

        // 出屏检查（反弹）
        if (bullets[i].x < BULLET_RADIUS+MARGIN || bullets[i].x > scr_w - BULLET_RADIUS-MARGIN) bullets[i].vx = -bullets[i].vx;
        if (bullets[i].y < BULLET_RADIUS+MARGIN || bullets[i].y > scr_h - BULLET_RADIUS-MARGIN) bullets[i].vy = -bullets[i].vy;

        if (bullet_check_collision(&bullets[i])) {
            lv_obj_del(bullets[i].obj);
            bullets[i].active = false;
            continue;
        }
    }
}


/* 定时器回调：遍历所有子弹 */
static void bullet_update_cb(lv_timer_t *timer)
{
	lv_obj_t *game = timer->user_data;
	if (lv_obj_is_valid(game)) 
	{
		bullet_update_one();
	}
}

/* 初始化子弹系统：调用一次 */
void bullet_system_init(lv_obj_t *parent)
{
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
		bullets[i].obj = NULL; /* 初始化为空，避免脏指针 */
    }
//	static bool bullet_timer_enabled = false;
//    if (!bullet_timer_enabled) {
		lv_timer_create(bullet_update_cb, TIMER_PERIOD_MS, parent);
//		bullet_timer_enabled=true;
//	}
}

/*
 * 发射子弹（角度使用弧度制）
 * parent: 子弹要添加到的父对象（通常传 lv_scr_act()）
 * x, y  : 发射起点（像素坐标）
 * angle : 发射角度（弧度），0 = 右，+PI/2 = 下
 * 返回 true 表示发射成功；如果屏幕上已有 5 个子弹则返回 false
 */
bool bullet_create_ex(lv_obj_t *parent, float x, float y, float angle_deg,
                      int owner_id, int owner_team)
{
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            double dir_x = cosf(angle_deg * M_PI / 180.0f);
            double dir_y = sinf(angle_deg * M_PI / 180.0f);

            bullets[i].vx = (float)(dir_x * BULLET_SPEED);
            bullets[i].vy = (float)(dir_y * BULLET_SPEED);

            lv_obj_t *b = lv_obj_create(parent);
            lv_obj_set_size(b, BULLET_RADIUS * 2, BULLET_RADIUS * 2);
            lv_obj_set_style_radius(b, BULLET_RADIUS, 0);
            lv_obj_set_style_border_width(b, 0, 0);
            lv_obj_set_style_bg_color(b, lv_color_make(0x00, 0x00, 0x00), 0);
            lv_obj_set_style_bg_opa(b, LV_OPA_COVER, 0);
            lv_obj_set_pos(b, (int)roundf(x - BULLET_RADIUS), (int)roundf(y - BULLET_RADIUS));

            bullets[i].obj        = b;
            bullets[i].x          = x;
            bullets[i].y          = y;
            bullets[i].start_time = lv_tick_get();
            bullets[i].active     = true;
            bullets[i].owner_id   = owner_id;
            bullets[i].owner_team = owner_team;
            bullets[i].prev_row   = bullets[i].prev_col = -1;
            return true;
        }
    }
    return false;
}


bool bullet_create(lv_obj_t *parent, float x, float y, float angle_deg)
{
    return bullet_create_ex(parent, x, y, angle_deg, -1, -1);
}
