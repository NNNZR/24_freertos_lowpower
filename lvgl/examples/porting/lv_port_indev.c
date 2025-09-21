/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "lvgl.h"
#include "touch.h"
#include "key.h"
#include <stdio.h>
#include "math.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "../generated/gui_guider.h"
#include "../generated/events_init.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void touchpad_init(void);
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y);

static void mouse_init(void);
static void mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static bool mouse_is_pressed(void);
static void mouse_get_xy(lv_coord_t * x, lv_coord_t * y);

static void keypad_init(void);
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);

static void encoder_init(void);
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void encoder_handler(void);

static void button_init(void);
static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static int8_t button_get_pressed_id(void);
static bool button_is_pressed(uint8_t id);

/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;
lv_indev_t * indev_mouse;
lv_indev_t * indev_keypad;
lv_indev_t * indev_encoder;
lv_indev_t * indev_button;

static int32_t encoder_diff;
static lv_indev_state_t encoder_state;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
lv_obj_t * mouse_cursor;

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Touchpad
     *  - Mouse (with cursor support)
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *  - Button (external buttons to press points on the screen)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

    static lv_indev_drv_t indev_drv;
    static lv_indev_drv_t indev_drv2;

    /*------------------
     * Touchpad
     * -----------------*/

//    /*Initialize your touchpad if you have*/
//    touchpad_init();

//    /*Register a touchpad input device*/
//    lv_indev_drv_init(&indev_drv);
//    indev_drv.type = LV_INDEV_TYPE_POINTER;
//    indev_drv.read_cb = touchpad_read;
//    indev_touchpad = lv_indev_drv_register(&indev_drv);

//    /*------------------
//     * Mouse
//     * -----------------*/

    /*Initialize your mouse if you have*/
    mouse_init();

    /*Register a mouse input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = mouse_read;
    indev_mouse = lv_indev_drv_register(&indev_drv);

    /*Set cursor. For simplicity set a HOME symbol now.*/
    // 创建鼠标光标对象
     mouse_cursor = lv_img_create(lv_scr_act()); 
    lv_img_set_src(mouse_cursor, LV_SYMBOL_OK); 
    lv_indev_set_cursor(indev_mouse, mouse_cursor);
//    /*------------------
//     * Keypad
//     * -----------------*/

//    /*Initialize your keypad or keyboard if you have*/
//    keypad_init();

//    /*Register a keypad input device*/
//    lv_indev_drv_init(&indev_drv2);
//    indev_drv2.type = LV_INDEV_TYPE_KEYPAD;
//    indev_drv2.read_cb = keypad_read;
//    indev_keypad = lv_indev_drv_register(&indev_drv2);

    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_keypad, group);`*/

//    /*------------------
//     * Encoder
//     * -----------------*/

//    /*Initialize your encoder if you have*/
//    encoder_init();

//    /*Register a encoder input device*/
//    lv_indev_drv_init(&indev_drv);
//    indev_drv.type = LV_INDEV_TYPE_ENCODER;
//    indev_drv.read_cb = encoder_read;
//    indev_encoder = lv_indev_drv_register(&indev_drv);

//    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
//     *add objects to the group with `lv_group_add_obj(group, obj)`
//     *and assign this input device to group to navigate in it:
//     *`lv_indev_set_group(indev_encoder, group);`*/

//    /*------------------
//     * Button
//     * -----------------*/

//    /*Initialize your button if you have*/
//    button_init();

//    /*Register a button input device*/
//    lv_indev_drv_init(&indev_drv);
//    indev_drv.type = LV_INDEV_TYPE_BUTTON;
//    indev_drv.read_cb = button_read;
//    indev_button = lv_indev_drv_register(&indev_drv);

//    /*Assign buttons to points on the screen*/
//    static const lv_point_t btn_points[2] = {
//        {10, 10},   /*Button 0 -> x:10; y:10*/
//        {40, 100},  /*Button 1 -> x:40; y:100*/
//    };
//    lv_indev_set_button_points(indev_button, btn_points);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Touchpad
 * -----------------*/

/*Initialize your touchpad*/
static void touchpad_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;
    /*Save the pressed coordinates and the state*/
    if(touchpad_is_pressed()) {
        touchpad_get_xy(&last_x, &last_y);
        data->state = LV_INDEV_STATE_PR;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Set the last pressed coordinates*/
    data->point.x = last_x;
    data->point.y = last_y;
}

/*Return true is the touchpad is pressed*/
static bool touchpad_is_pressed(void)
{
    /*Your code comes here*/
    static uint8_t last_status = 0;
    uint8_t status = TP_Scan(0);
    
    if(status != last_status) {
        last_status = status;
    }
    
    return status & TP_PRESS_DOWN;
//    return false;
}

/*Get the x and y coordinates if the touchpad is pressed*/
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    /*Your code comes here*/
	static lv_coord_t last_x = 0;
	static lv_coord_t last_y = 0;
    
    // 直接使用 tp_dev 中的值，因为 TP_Scan 已经在 touchpad_is_pressed 中执行过了
    if(tp_dev.sta & TP_PRESS_DOWN)
    {
        *x = tp_dev.x;
        *y = tp_dev.y;
        last_x = *x;
        last_y = *y;
    }
    else
    {
        *x = last_x;
        *y = last_y;
    }
}

/*------------------
 * Mouse
 * -----------------*/

/*Initialize your mouse*/
static void mouse_init(void)
{
    /*Your code comes here*/
}

extern QueueHandle_t uartCmdQueueHandle;
char cmd[10]={0};  // 存放串口接收的命令
char act[10]={0};
/*Will be called by the library to read the mouse*/
static void mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{   
    if(xQueueReceive(uartCmdQueueHandle, cmd, 0)==pdFALSE)
    {
		memset(cmd, 0, sizeof(cmd));
    }
    /*Get the current x and y coordinates*/
    mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the mouse button is pressed or released*/
    if(mouse_is_pressed()) {
        data->state = LV_INDEV_STATE_PR;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }
    
}

bool click_event=false;
/*Return true is the mouse button is pressed*/
static bool mouse_is_pressed(void)
{
    /*Your code comes here*/
//    Key_Read();	
    if (strcmp(cmd, "RS\r\n") == 0||click_event==true) { 
		click_event=false;
        return true;   // 鼠标被按下
    } else {
        return false;  // 鼠标释放
    }
}

static float mouse_x = 120;
static float mouse_y = 160;
const int step = 3;
extern lv_ui guider_ui;
uint8_t event_key;
/* Get the x and y coordinates if the mouse is pressed */
static void mouse_get_xy(lv_coord_t * x, lv_coord_t * y)
{
//    Key_Read();

//    // 左键位 (KB5 → bit4)
//    if (Cont & (1 << 4)) mouse_x -= step;
//    // 右键位 (KB4 → bit3)
//    if (Cont & (1 << 3)) mouse_x += step;
//    // 上键位 (KB7 → bit6)
//    if (Cont & (1 << 6)) mouse_y -= step;
//    // 下键位 (KB6 → bit5)
//    if (Cont & (1 << 5)) mouse_y += step;



    if (strcmp(cmd, "RL\r\n") == 0) {
        // 左移
        mouse_x -= step;
    } else if (strcmp(cmd, "RR\r\n") == 0) {
        // 右移
        mouse_x += step;
    } else if (strcmp(cmd, "RF\r\n") == 0) {
        // 上移
        mouse_y -= step;
    } else if (strcmp(cmd, "RB\r\n") == 0) {
        // 下移
        mouse_y += step;
    }
     else if (strcmp(cmd, "RO\r\n") == 0) {
    // 检查对象是否存在再发送事件
	  event_key=10;
     }

    // 限制范围：x ∈ [0, 240], y ∈ [0, 320]
    if (mouse_x < 0)   mouse_x = 0;
    if (mouse_x > 240) mouse_x = 240;
    if (mouse_y < 0)   mouse_y = 0;
    if (mouse_y > 320) mouse_y = 320;

    // 返回最新坐标
    *x = (lv_coord_t)mouse_x;
    *y = (lv_coord_t)mouse_y;
}

/*------------------
 * Keypad
 * -----------------*/

/*Initialize your keypad*/
static void keypad_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the mouse*/
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;

    /*Get the current x and y coordinates*/
    mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PR;

        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
            case 1:
                act_key = LV_KEY_NEXT;
                break;
            case 2:
                act_key = LV_KEY_PREV;
                break;
            case 3:
                act_key = LV_KEY_LEFT;
                break;
            case 4:
                act_key = LV_KEY_RIGHT;
                break;
            case 5:
                act_key = LV_KEY_ENTER;
                break;
        }

        last_key = act_key;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
}

/*Get the currently being pressed key.  0 if no key is pressed*/
static uint32_t keypad_get_key(void)
{
    /*Your code comes here*/
	uint8_t key=event_key;
	event_key=0;
    return key;
}

/*------------------
 * Encoder
 * -----------------*/

/*Initialize your keypad*/
static void encoder_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the encoder*/
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{

    data->enc_diff = encoder_diff;
    data->state = encoder_state;
}

/*Call this function in an interrupt to process encoder events (turn, press)*/
static void encoder_handler(void)
{
    /*Your code comes here*/

    encoder_diff += 0;
    encoder_state = LV_INDEV_STATE_REL;
}

/*------------------
 * Button
 * -----------------*/

/*Initialize your buttons*/
static void button_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the button*/
static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{

    static uint8_t last_btn = 0;

    /*Get the pressed button's ID*/
    int8_t btn_act = button_get_pressed_id();

    if(btn_act >= 0) {
        data->state = LV_INDEV_STATE_PR;
        last_btn = btn_act;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Save the last pressed button's ID*/
    data->btn_id = last_btn;
}

/*Get ID  (0, 1, 2 ..) of the pressed button*/
static int8_t button_get_pressed_id(void)
{
    uint8_t i;

    /*Check to buttons see which is being pressed (assume there are 2 buttons)*/
    for(i = 0; i < 2; i++) {
        /*Return the pressed button's ID*/
        if(button_is_pressed(i)) {
            return i;
        }
    }

    /*No button pressed*/
    return -1;
}

/*Test if `id` button is pressed or not*/
static bool button_is_pressed(uint8_t id)
{

    /*Your code comes here*/

    return false;
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
