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
 *    ����
 *-----------*/
#include "../generated/gui_guider.h"
#include "../generated/events_init.h"
 
lv_ui guider_ui;

#define LV_DEMO_TASK_PRIO    3        /*�������ȼ�*/
#define LV_DEMO_TASK_SIZE    1024*5    /*�����ջ��С*/
TaskHandle_t lv_demo_Task_Handler;    /*������*/
void lv_demo_task(void* arguements); /*������*/	

#define ADC_TASK_PRIO      2       /* �������ȼ� */
#define ADC_TASK_SIZE      512    /* �����ջ��С��word�� */
TaskHandle_t adc_Task_Handler;    /*������*/
void adc_task(void* parameters); // ����������

#define W25QXX_TASK_PRIO  4       // �������ȼ�
#define W25QXX_TASK_SIZE  256    // �����ջ��С
TaskHandle_t w25qxx_Task_Handler; // ������
void w25qxx_task(void* parameters); // ����������

#define MUSIC_TASK_PRIO  5       // �������ȼ�
#define MUSIC_TASK_SIZE  1024    // �����ջ��С
TaskHandle_t music_Task_Handler; // ������
void music_task(void* parameters); // ����������





#define CELL_SIZE   40  // ÿ�����ӵ����ش�С
#define MAZE_W      7  // �Թ���ȣ���������
#define MAZE_H      9   // �Թ��߶ȣ���������
/*====================================*/
/* �Թ���ͼ��1=ǽ��0=�յ� */
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


#define TEST_ADDR  0x000000   // ���Ե�ַ��һ��ѡһ����ȫ�ĵ�ַ�������ƻ����ݣ�
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

//    // д��������
//    W25QXX_Write(txBuf, TEST_ADDR, sizeof(txBuf));

//    // ��������
//    W25QXX_Read(rxBuf, TEST_ADDR, sizeof(rxBuf));

//    printf("Read  Data: ");
//    for(int i=0; i<sizeof(rxBuf); i++)
//    {
//        printf("%02X ", rxBuf[i]);
//    }
//    printf("\r\n");

//    // �Ƚ�
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
        music_task,           // ������
        "music_task",         // ������
        MUSIC_TASK_SIZE,      // ջ��ȣ�word��
        NULL,                 // ����
        MUSIC_TASK_PRIO,      // ���ȼ�
        &music_Task_Handler   // ������
    ) ; 
	
	xTaskCreate(
        lv_demo_task,         // ������
        "start_task",        // ������
        LV_DEMO_TASK_SIZE,              // ջ��ȣ���λ��word�������ֽڣ�
        NULL,             // �������
        LV_DEMO_TASK_PRIO, // ���ȼ�
        &lv_demo_Task_Handler // ������
    );
	
	xTaskCreate(
        adc_task,         // ������
        "adc_task",        // ������
        ADC_TASK_SIZE,              // ջ��ȣ���λ��word�������ֽڣ�
        NULL,             // �������
        ADC_TASK_PRIO, // ���ȼ�
        &adc_Task_Handler // ������
    );
	
	xTaskCreate(
        w25qxx_task,         // ������
        "w25qxx_task",        // ������
        W25QXX_TASK_SIZE,              // ջ��ȣ���λ��word�������ֽڣ�
        NULL,             // �������
        W25QXX_TASK_PRIO, // ���ȼ�
        &w25qxx_Task_Handler // ������
    );
}

QueueHandle_t uartCmdQueueHandle;
QueueHandle_t mouseCmdQueueHandle;
SemaphoreHandle_t xI2SSemaphore;



void music_task(void* parameters)
{

	xI2SSemaphore = xSemaphoreCreateBinary();
	WAV_SetVolume(0.5f);
	WAV_PlayFile("0:/1.wav",&hi2s2);  // ���� SD ���ϵ� 1.WAV
	for(;;)
	{
		
		if(xSemaphoreTake(xI2SSemaphore, portMAX_DELAY) == pdTRUE)
        {
			update_volume(); 
            wav_proc();
        }
	}

}


/*adc�ɼ���ѹ*/

#define ADC_BUF_LEN            15      /* DMA ���������ȣ�������һ�£� */
#define BACKLIGHT_ACTIVE_HIGH  0       /* ������Ч��ƽ: 1=����Ч, 0=����Ч */
#define DIM_IIR_ALPHA_NUM      1U      /* IIR�˲�: ��ֵȨ�صķ��� (1/8) */
#define DIM_IIR_ALPHA_DEN      8U


static uint16_t AdcBuf[ADC_BUF_LEN];     /* DMA������ */
static volatile uint16_t g_adc_avg = 0;  /* DMA�ص�������ƽ��ֵ */
static volatile BaseType_t g_adc_ready = pdFALSE;

/* ==== С���ߺ��� ==== */
static inline uint16_t clamp_u16(uint32_t x, uint16_t lo, uint16_t hi) {
    if (x < lo) return lo;
    if (x > hi) return hi;
    return (uint16_t)x;
}

/* ����ӳ��: ADC(0..4095) -> ռ��(0..100)��ʹ���������⸡�� */
static inline uint16_t adc_to_duty(uint16_t adc)
{
    /* �������룺(adc * 100) / 4095 */
    uint32_t duty = ( (uint32_t)adc * 100U + (4095U/2U) ) / 4095U;
    duty = clamp_u16(duty, 0, 100U);  /* �� ARR=100 ���� */
    /* ���⼫�Դ��� */
    if (!BACKLIGHT_ACTIVE_HIGH) {
        duty = 100U - duty;
    }
    duty +=5;
    return (uint16_t)duty;
}

/* ==== DMA �ص������������ʱ����ƽ����֪ͨ���� ==== */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance != hadc1.Instance) return;

    uint32_t sum = 0;
    for (uint32_t i = 0; i < ADC_BUF_LEN; i++) sum += AdcBuf[i];
    g_adc_avg = (uint16_t)(sum / ADC_BUF_LEN);

    /* ֪ͨ������������ FromISR �汾�� */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    g_adc_ready = pdTRUE;
    if (adc_Task_Handler) {
        vTaskNotifyGiveFromISR(adc_Task_Handler, &xHigherPriorityTaskWoken);
    }
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)AdcBuf, ADC_BUF_LEN);
}


/* ==== ��ѡ���ѵ�ѹֵ����������ڵ��Դ�ӡ��==== */
static inline float adc_to_voltage(uint16_t adc)
{
    return (3.3f * adc) / (float)4095U;
}




/* ==== ���������������貢���� ADC ���� PWM ==== */

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

        /* ֻ�������Ƿ��������ݣ�����ȡ���� */
        if (mouseCmdNew == pdTRUE) {
		lastMouseTick = now;       // ����������ʱ��
		bright_state = BRIGHT_NORMAL;
		mouseCmdNew = pdFALSE;     // ���ñ�־
		}	

        /* Ĭ���� ADC �������� */
        if (g_adc_ready) {
            g_adc_ready = pdFALSE;
            duty_now = adc_to_duty(g_adc_avg);
        }

        /* ״̬������ʱ�߼� */
        switch (bright_state) {
            case BRIGHT_NORMAL:
                if ((now - lastMouseTick) > pdMS_TO_TICKS(10000)) {
                    bright_state = BRIGHT_10;
                    lastMouseTick = now;  // ��ʱ 10 ��
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

        /* IIR �˲� */
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
 *    ����
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
    // Ĭ�� -1 ��ʾ���ڸ�����
    *row = -1;
    *col = -1;

    // �ж��Ƿ����Թ���Χ��
    if (x < MARGIN || x >= MARGIN + CELL_W * COLS) return;
    if (y < MARGIN || y >= MARGIN + CELL_H * ROWS) return;

    // �������У�����ȡ����
    *col = (x - MARGIN) / CELL_W;
    *row = (y - MARGIN) / CELL_H;
}




/*����*/

#ifdef DEBUG_COLLISION 
static lv_obj_t *tank_bbox = NULL;  // ��ײ����ʾ����
#endif
#ifdef DEBUG_COLLISION
void debug_collision_init(void)
{
    if (!tank_bbox) {
        tank_bbox = lv_line_create(lv_scr_act());

        static lv_style_t style;
        lv_style_init(&style);
        lv_style_set_line_color(&style, lv_color_hex(0xFF0000)); // ��ɫ
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

    // �ĸ����㣨��ת���Σ�
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
    pts[4] = pts[0]; // �պϾ���

    lv_line_set_points(tank_bbox, pts, 5);
}
#endif

/**********************************̹��***********************************/


int tank_Cstep = 4;   // �ƶ��ٶ�
int tank_Cangle = 6;  // ÿ����ת�ĽǶ�
static lv_obj_t *tank_img[2];
static double tank_x[2], tank_y[2], tank_angle[2];
static int LOCAL_TANK_ID[2] = {-1, -1};

lv_timer_t *tank_move_timer;

static double tank1_x = 40;
static double tank1_y = 50;
static double tank1_angle = 0;



#define MAX_TANKS 8
int  BULLET_SPAWN_GRACE_MS=320;   // �ӵ������ɵ����˻���ʱ��

typedef struct {
    lv_obj_t *img;     // ��ѡ����Ӧ�� LVGL ͼƬ����
    double x, y;       // ��������
    double angle;      // �Ƕȣ��ȣ�
    double l, w;       // ����ߴ磺l=horiz=tank_l, w=vert=tank_w
    bool   alive;      // �Ƿ��ڳ�/�ɱ�����
    int    team;       // ��Ӫ����ѡ�����ڶ������ˣ�
} Tank;

static Tank g_tanks[MAX_TANKS];
static int  g_tank_count = 0;

//static int LOCAL_TANK_ID = -1;


void lv_obj_set_pos_center(lv_obj_t * img,lv_coord_t w,lv_coord_t h, lv_coord_t x, lv_coord_t y)
{
    if(img == NULL) return;

    /* �������Ͻ����� */
    lv_coord_t left = x - w / 2;
    lv_coord_t top  = y - h / 2;

    lv_obj_set_pos(img, left, top);
}



// ע��һ��̹�ˣ������� id����������ʧ�ܷ��� -1
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

// ����̹��״̬���������ڸ����ƶ�����ã�
static inline void tank_set_state(int id, double x, double y, double angle_deg)
{
    if (id < 0 || id >= g_tank_count || !g_tanks[id].alive) return;
    g_tanks[id].x = x;
    g_tanks[id].y = y;
    g_tanks[id].angle = angle_deg;
}

// ������Ҫ���Ƴ�/����
static inline void tank_kill(int id) {
    if (id < 0 || id >= g_tank_count) return;
    g_tanks[id].alive = false;
}

// ���ߣ��㵽�߶ε�ƽ�����루���豸�ã�
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

/************* ��ת���ι��ߺ����� *************/

/* ������ת̹�˵��ĸ����㣨��˳ʱ�룩������(x,y)���Ƕ�angle(��)���ߴ� w=horiz=tank_l, h=vert=tank_w */
static void get_tank_corners(double x, double y, double angle,
                             double w, double h, double out[4][2])
{
    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad), sinA = sin(rad);
    double hw = w * 0.5, hh = h * 0.5;

    // �������꣨������ģ������ϡ����ϡ����¡����£�˳ʱ�룩
    double local[4][2] = {
        {-hw, -hh}, { hw, -hh}, { hw,  hh}, {-hw,  hh}
    };

    for (int i = 0; i < 4; i++) {
        double lx = local[i][0], ly = local[i][1];
        out[i][0] = x + lx * cosA - ly * sinA;
        out[i][1] = y + lx * sinA + ly * cosA;
    }
}

/* �������(������n)ͶӰ��������(ax,ay)�ϣ���[min,max] */
static void project_polygon(const double (*poly)[2], int n,
                            double ax, double ay,
                            double *min_out, double *max_out)
{
    // �ɲ���һ����������һ�������һ��
    double len2 = ax*ax + ay*ay;
    if (len2 > 1e-12) { // ��һ�������⼫С��Ӱ����ֵ�ȶ�
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

/* �����Ƿ��ص� */
static inline bool interval_overlap(double minA, double maxA,
                                    double minB, double maxB)
{
    return !(maxA < minB || maxB < minA);
}

/* ��ת����(tank_poly) vs ��������(rx1,ry1,rx2,ry2) ��SAT��� */
static bool rect_vs_rect(const double tank_poly[4][2],
                         double rx1, double ry1,
                         double rx2, double ry2)
{
    // 4��ǽ�ǵ㣨����룩
    double wall_poly[4][2] = {
        {rx1, ry1}, {rx2, ry1}, {rx2, ry2}, {rx1, ry2}
    };

    // ��Ҫ���Եķ����᣺
    // 1) ̹�������ߵķ���
    // 2) ǽ����������(1,0)��(0,1)���㹻����ǽ�߷��ߣ�
    double axes[6][2];
    int axis_cnt = 0;

    for (int i = 0; i < 4; i++) {
        int j = (i + 1) & 3;
        double dx = tank_poly[j][0] - tank_poly[i][0];
        double dy = tank_poly[j][1] - tank_poly[i][1];
        // �ߵķ��� (-dy, dx)
        axes[axis_cnt][0] = -dy;
        axes[axis_cnt][1] =  dx;
        axis_cnt++;
    }
    axes[axis_cnt][0] = 1; axes[axis_cnt][1] = 0; axis_cnt++;
    axes[axis_cnt][0] = 0; axes[axis_cnt][1] = 1; axis_cnt++;

    // SAT����һ���ϲ��ص� => ���ཻ
    for (int i = 0; i < axis_cnt; i++) {
        double ax = axes[i][0], ay = axes[i][1];
        // ���������ᣬ������ֵ����
        if (ax*ax + ay*ay < 1e-12) continue;

        double minA, maxA, minB, maxB;
        project_polygon(tank_poly, 4, ax, ay, &minA, &maxA);
        project_polygon(wall_poly, 4, ax, ay, &minB, &maxB);

        if (!interval_overlap(minA, maxA, minB, maxB)) {
            return false; // ���� -> ����ײ
        }
    }
    return true; // ��������ص� -> ��ײ
}

/************* ���Ǹ���+����ǽ��� *************/

/* ֻ���̹�ˡ�ʵ�ʸ��ǡ��ĸ��Ӽ������ǽ������ȫ������֧����ת */
static bool check_collision(double x, double y, double angle)
{
    // ����̹���Ľ�
    double tank_poly[4][2];
    get_tank_corners(x, y, angle, tank_l, tank_w, tank_poly);

    // AABB ��Χ�� -> ת�ɸ��ӷ�Χ
    double min_x = tank_poly[0][0], max_x = tank_poly[0][0];
    double min_y = tank_poly[0][1], max_y = tank_poly[0][1];
    for (int i = 1; i < 4; i++) {
        if (tank_poly[i][0] < min_x) min_x = tank_poly[i][0];
        if (tank_poly[i][0] > max_x) max_x = tank_poly[i][0];
        if (tank_poly[i][1] < min_y) min_y = tank_poly[i][1];
        if (tank_poly[i][1] > max_y) max_y = tank_poly[i][1];
    }

    // ת��������������ȡ����
    int min_col = (int)((min_x - MARGIN) / CELL_W);
    int max_col = (int)((max_x - MARGIN) / CELL_W);
    int min_row = (int)((min_y - MARGIN) / CELL_H);
    int max_row = (int)((max_y - MARGIN) / CELL_H);

    // �߽�ü�
    if (max_col < 0 || max_row < 0 || min_col >= COLS || min_row >= ROWS) {
        // ��ȫ���Թ���࣬��Ϊ��ײ
        return true;
    }
    if (min_col < 0) min_col = 0;
    if (min_row < 0) min_row = 0;
    if (max_col >= COLS) max_col = COLS - 1;
    if (max_row >= ROWS) max_row = ROWS - 1;

    // �������Ƿ�Χ�ڵĸ��ӣ����ø�������ǽ
    for (int r = min_row; r <= max_row; r++) {
        for (int c = min_col; c <= max_col; c++) {

            // �ϱ�ǽ��ˮƽ�� (r, c..c+1)
            if (maze_map[r*2][c*2+1]) {
                double wy1 = MARGIN + CELL_H * r-LINE_WIDTH/2;
                double wy2 = wy1 + LINE_WIDTH;
                double wx1 = MARGIN + CELL_W * c;
                double wx2 = wx1 + CELL_W;
                if (rect_vs_rect(tank_poly, wx1, wy1, wx2, wy2)) return true;
            }

            // �±�ǽ��ˮƽ�� (r+1, c..c+1)
            if (maze_map[(r+1)*2][c*2+1]) {
                double wy1 = MARGIN + CELL_H * (r + 1)-LINE_WIDTH/2;
                double wy2 = wy1 + LINE_WIDTH;
                double wx1 = MARGIN + CELL_W * c;
                double wx2 = wx1 + CELL_W;
                if (rect_vs_rect(tank_poly, wx1, wy1, wx2, wy2)) return true;
            }

            // ���ǽ����ֱ�� (r..r+1, c)
            if (maze_map[r*2+1][c*2]) {
                double wx1 = MARGIN + CELL_W * c-LINE_WIDTH/2;
                double wx2 = wx1 + LINE_WIDTH;
                double wy1 = MARGIN + CELL_H * r;
                double wy2 = wy1 + CELL_H;
                if (rect_vs_rect(tank_poly, wx1, wy1, wx2, wy2)) return true;
            }

            // �ұ�ǽ����ֱ�� (r..r+1, c+1)
            if (maze_map[r*2+1][c*2+2]) {
                double wx1 = MARGIN + CELL_W * (c + 1)-LINE_WIDTH/2;
                double wx2 = wx1 + LINE_WIDTH;
                double wy1 = MARGIN + CELL_H * r;
                double wy2 = wy1 + CELL_H;
                if (rect_vs_rect(tank_poly, wx1, wy1, wx2, wy2)) return true;
            }
        }
    }

    return false; // ûײ��
}
//static bool screen2_loaded = false;
/* ��ȡ���ƺ�������꣬������ͼ��λ�úͽǶ� */
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

/* ================= ��ʱ���ص� ================= */
void tank_move_timer_cb(lv_timer_t *timer)
{
    lv_obj_t *game = timer->user_data;

    if (lv_obj_is_valid(game)) {
        tank_update_xy(game);   // ����̹��λ��
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
    // --- ̹��1 ---
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

    // --- ̹��2 ---
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

/******************************�Թ�**********************************/

static lv_obj_t * create_line(lv_obj_t * parent, int x1, int y1, int x2, int y2, int thickness)
{
    /* ���������� */
    lv_point_t * pts = lv_mem_alloc(sizeof(lv_point_t) * 2);
    pts[0].x = x1;
    pts[0].y = y1;
    pts[1].x = x2;
    pts[1].y = y2;

    /* �����߶��� */
    lv_obj_t * line = lv_line_create(parent);
    lv_line_set_points(line, pts, 2);
    lv_obj_add_style(line, &style_wall, 0);
    lv_obj_set_style_line_width(line, thickness, LV_PART_MAIN);

//    lv_mem_free(pts);  // ��ȫ�ͷ�
    /* ���� lv_obj_t*�������������/��ʾ */
    return line;
}



typedef struct {
    int x, y;
    int px, py; // ���ڵ�
} Edge;

// ������Һ���
extern RNG_HandleTypeDef hrng; // �ѳ�ʼ���� RNG

// ��Ӳ�� RNG ��ȡ�����
int hw_rand(int max) {
    uint32_t value = 0;
    HAL_RNG_GenerateRandomNumber(&hrng, &value);
    return value % max; // ���� 0 ~ max-1
}


// �����Թ�
void prim_maze() {
    for (int y = 0; y < MAZE_H; y++)
        for (int x = 0; x < MAZE_W; x++)
            maze_map[y][x] = 1; // ȫ����ǽ

    // ������ (��������)
    int sx = hw_rand(MAZE_W/2) * 2 + 1;
    int sy = hw_rand(MAZE_H/2) * 2 + 1;
    maze_map[sy][sx] = 0;

    Edge edges[MAZE_H * MAZE_W];
    int edge_count = 0;

    int dx[4] = {2, -2, 0, 0};
    int dy[4] = {0, 0, 2, -2};

    // ��ӳ�ʼ��
    for (int d = 0; d < 4; d++) {
        int nx = sx + dx[d];
        int ny = sy + dy[d];
        if (nx > 0 && nx < MAZE_W && ny > 0 && ny < MAZE_H) {
            edges[edge_count++] = (Edge){nx, ny, sx, sy};
        }
    }

    while (edge_count > 0) {
        int idx = hw_rand(edge_count); // ��Ӳ�� RNG ���ѡ���
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



/**********************************�ӵ�**********************************/
#define MAX_BULLETS 10
#define BULLET_RADIUS 3
float BULLET_SPEED=250.0f;      // ��λ������/�루�ɰ��������
#define BULLET_LIFETIME_MS 15000  // �ӵ�����ʱ�䣬����
#define TIMER_PERIOD_MS 20       // ��ʱ������ ms (~60 FPS)

typedef struct {
    lv_obj_t *obj;
    float x, y;
    float vx, vy;
    uint32_t start_time;
    bool active;

    int prev_row;
    int prev_col;

    int owner_id;   // ������������̹�� id��-1 ��ʾδ֪��
    int owner_team; // ��������������Ӫ�����ڶ������˵ȣ�
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

// Բ(�ӵ�) vs ��ת����(�Ľ�)�� SAT ���
static bool circle_vs_rotrect_SAT(double cx, double cy, double r,
                                  const double rect_poly[4][2])
{
    // 1) �����߷���
    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) & 3;
        double dx = rect_poly[j][0] - rect_poly[i][0];
        double dy = rect_poly[j][1] - rect_poly[i][1];
        double ax = -dy, ay = dx; // �߷���

        double minR, maxR, minC, maxC;
        project_polygon(rect_poly, 4, ax, ay, &minR, &maxR);
        project_circle  (cx, cy, r,   ax, ay, &minC, &maxC);
        if (!interval_overlap(minR, maxR, minC, maxC)) return false;
    }

    // 2) �����᣺Բ��ָ������ľ��ζ��㡱������
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

    return true; // ����������ص� -> �ཻ
}



extern uint8_t event_key;
extern bool click_event;
int hit_id=-1;


// ���лص���������������Ѫ/��ը/�÷ֵ�
void on_bullet_hit_tank(Bullet *b, int tank_id)
{
    (void)b;
    // ʾ�������ٸ�̹��
//    tank_kill(tank_id);
	if(doublecheck>0)
	{
	click_event=true;
	event_key=10;
	doublecheck-=1;
	}
    // ��ӡ������Ϣ
	hit_id=tank_id;
    printf("�ӵ�����̹�� %d\n", tank_id);

    // TODO: ���ű�ը/��Ѫ/UI ��
}

// �����ӵ� vs ����̹�˵���ײ
static bool bullet_check_collision(Bullet *b)
{
    // �ӵ�Բ����
    double cx = b->x;
    double cy = b->y;
    double r  = BULLET_RADIUS;

    uint32_t now = lv_tick_get();
	
    for (int id = 0; id < g_tank_count; ++id) {
        Tank *t = &g_tanks[id];
        if (!t->alive) continue;

//        // ����ѡ����������
//        if (b->owner_team >= 0 && t->team >= 0 && b->owner_team == t->team) {
//            // ������Ҫ���š����ѿ��ˡ���ɾ���˶�
//            continue;
//        }

//        // ����ѡ���������˻���
        if (b->owner_id == id && now - b->start_time < BULLET_SPAWN_GRACE_MS) {
            continue;
        }

        // ���� AABB �ų�����̹���ĽǼ��� AABB������Բ�� AABB ��������
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
            continue; // AABB ���ཻ -> һ������
        }

        // ��ȷ��Բ vs ��ת���ε� SAT
        if (circle_vs_rotrect_SAT(cx, cy, r, poly)) {
            on_bullet_hit_tank(b, id); // ���������¼�����ѡ��
            return true;               // ֪ͨ���ɾ���ӵ�
        }
    }

    return false;
}


// ���� 0 = ûǽ, 1 = ��ֱǽ (����ǽ), 2 = ˮƽǽ (����ǽ)
static int wall_between(int row1, int col1, int row2, int col2)
{
    if (abs(row1 - row2) + abs(col1 - col2) != 1) {
        return 0; // �������ڸ���
    }

    // ˮƽ�����ƶ�
    if (row1 == row2) {
        int row = row1;
        if (col2 > col1) {
            // ���� �� �����ǽ
            if (maze_map[2*row+1][2*col1+2]) return 1;
        } else {
            // ���� �� �����ǽ
            if (maze_map[2*row+1][2*col1]) return 1;
        }
    }

    // ��ֱ�����ƶ�
    if (col1 == col2) {
        int col = col1;
        if (row2 > row1) {
            // ���� �� �����ǽ
            if (maze_map[2*row1+2][2*col+1]) return 2;
        } else {
            // ���� �� �����ǽ
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
                // �������ǰ��λ��
        float old_x = bullets[i].x;
        float old_y = bullets[i].y;

        // ���ٶȸ���λ��
        bullets[i].x += bullets[i].vx * dt;
        bullets[i].y += bullets[i].vy * dt;

        // ���º����ڸ���
        int new_row, new_col;
        get_cell_from_xy((int)bullets[i].x, (int)bullets[i].y, &new_row, &new_col);

        // ����Ƿ�����
        if (old_row >= 0 && old_col >= 0 &&
            new_row >= 0 && new_col >= 0 &&
            (old_row != new_row || old_col != new_col)) {

            int wall_type = wall_between(old_row, old_col, new_row, new_col);
            if (wall_type == 1) {
                // ����ǽ �� ����λ�ã�����תX
                bullets[i].x = old_x;   // �ص���һ����ȫλ��
                bullets[i].vx = -bullets[i].vx;
            } else if (wall_type == 2) {
                // ����ǽ �� ����λ�ã�����תY
                bullets[i].y = old_y;
                bullets[i].vy = -bullets[i].vy;
            }
        }


        lv_obj_set_pos(bullets[i].obj,
                       (int)roundf(bullets[i].x - BULLET_RADIUS),
                       (int)roundf(bullets[i].y - BULLET_RADIUS));

        // ������飨������
        if (bullets[i].x < BULLET_RADIUS+MARGIN || bullets[i].x > scr_w - BULLET_RADIUS-MARGIN) bullets[i].vx = -bullets[i].vx;
        if (bullets[i].y < BULLET_RADIUS+MARGIN || bullets[i].y > scr_h - BULLET_RADIUS-MARGIN) bullets[i].vy = -bullets[i].vy;

        if (bullet_check_collision(&bullets[i])) {
            lv_obj_del(bullets[i].obj);
            bullets[i].active = false;
            continue;
        }
    }
}


/* ��ʱ���ص������������ӵ� */
static void bullet_update_cb(lv_timer_t *timer)
{
	lv_obj_t *game = timer->user_data;
	if (lv_obj_is_valid(game)) 
	{
		bullet_update_one();
	}
}

/* ��ʼ���ӵ�ϵͳ������һ�� */
void bullet_system_init(lv_obj_t *parent)
{
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
		bullets[i].obj = NULL; /* ��ʼ��Ϊ�գ�������ָ�� */
    }
//	static bool bullet_timer_enabled = false;
//    if (!bullet_timer_enabled) {
		lv_timer_create(bullet_update_cb, TIMER_PERIOD_MS, parent);
//		bullet_timer_enabled=true;
//	}
}

/*
 * �����ӵ����Ƕ�ʹ�û����ƣ�
 * parent: �ӵ�Ҫ��ӵ��ĸ�����ͨ���� lv_scr_act()��
 * x, y  : ������㣨�������꣩
 * angle : ����Ƕȣ����ȣ���0 = �ң�+PI/2 = ��
 * ���� true ��ʾ����ɹ��������Ļ������ 5 ���ӵ��򷵻� false
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
