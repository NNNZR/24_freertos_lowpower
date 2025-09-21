/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

#define MARGIN 7
#define COLS 3
#define ROWS 4
#define CELL_W ((240 - 2*MARGIN) / COLS) // 73
#define CELL_H ((320 - 2*MARGIN) / ROWS) // 75
#define LINE_WIDTH 6

extern void maze_draw(lv_obj_t * game);
extern void prim_maze(void);
extern void tank_init(lv_obj_t * game);
extern void bullet_system_init(lv_obj_t *parent);

extern uint8_t event_key;

/*====================================*/
/* ÃÔ¹¬µØÍ¼£º1=Ç½£¬0=¿ÕµØ */
extern int maze_map[9][7];
extern int tank_Cstep;
extern int tank_Cangle;
extern float BULLET_SPEED;
extern int  BULLET_SPAWN_GRACE_MS;

extern lv_obj_t * mouse_cursor;
void setup_scr_game1(lv_ui *ui)
{
	tank_Cstep=3;
	tank_Cangle=5;
	BULLET_SPEED=100.0f;
	BULLET_SPAWN_GRACE_MS=300;
	event_key = 0;
	
	lv_obj_add_flag(mouse_cursor, LV_OBJ_FLAG_HIDDEN);
	
    //Write codes game1
    ui->game1 = lv_obj_create(NULL);
    lv_obj_set_size(ui->game1, 240, 320);
    lv_obj_set_scrollbar_mode(ui->game1, LV_SCROLLBAR_MODE_OFF);

    //Write style for game1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->game1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	prim_maze();
	
	if(maze_map[7][4])
	{
    //Write codes game1_line_72
    ui->game1_line_72 = lv_line_create(ui->game1);
    static lv_point_t game1_line_72[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game1_line_72, game1_line_72, 2);
    lv_obj_set_pos(ui->game1_line_72, MARGIN + CELL_W * 2, MARGIN + CELL_H * 3);
//    lv_obj_set_size(ui->game1_line_72, 10, 63);

    //Write style for game1_line_72, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_72, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_72, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_72, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_72, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
	
	if(maze_map[7][2])
	{
    //Write codes game1_line_71
    ui->game1_line_71 = lv_line_create(ui->game1);
    static lv_point_t game1_line_71[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game1_line_71, game1_line_71, 2);
    lv_obj_set_pos(ui->game1_line_71, MARGIN + CELL_W * 1, MARGIN + CELL_H * 3);
//    lv_obj_set_size(ui->game1_line_71, 63, 60);

    //Write style for game1_line_71, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_71, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_71, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_71, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_71, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    
    }
	
    
    if(maze_map[6][5])
	{
    //Write codes game1_line_63
    ui->game1_line_63 = lv_line_create(ui->game1);
    static lv_point_t game1_line_63[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game1_line_63, game1_line_63, 2);
    lv_obj_set_pos(ui->game1_line_63, MARGIN + CELL_W * 2, MARGIN + CELL_H * 3);
//    lv_obj_set_size(ui->game1_line_63, 69, 1);

    //Write style for game1_line_63, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_63, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_63, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_63, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_63, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    
    }
	
    if(maze_map[6][3])
    {
    //Write codes game1_line_62
    ui->game1_line_62 = lv_line_create(ui->game1);
    static lv_point_t game1_line_62[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game1_line_62, game1_line_62, 2);
    lv_obj_set_pos(ui->game1_line_62, MARGIN + CELL_W * 1, MARGIN + CELL_H * 3);
//    lv_obj_set_size(ui->game1_line_62, 63, 60);

    //Write style for game1_line_62, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_62, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_62, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_62, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_62, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
    
     if(maze_map[6][1]){
    //Write codes game1_line_61
    ui->game1_line_61 = lv_line_create(ui->game1);
    static lv_point_t game1_line_61[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game1_line_61, game1_line_61, 2);
    lv_obj_set_pos(ui->game1_line_61, MARGIN, MARGIN + CELL_H * 3);
//    lv_obj_set_size(ui->game1_line_61, 63, 60);

    //Write style for game1_line_61, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_61, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_61, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_61, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_61, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    }
     
    if(maze_map[5][4])
    {
    //Write codes game1_line_52
    ui->game1_line_52 = lv_line_create(ui->game1);
    static lv_point_t game1_line_52[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game1_line_52, game1_line_52, 2);
    lv_obj_set_pos(ui->game1_line_52, MARGIN + CELL_W*2, MARGIN + CELL_H*2);
//    lv_obj_set_size(ui->game1_line_52, 5, 60);

    //Write style for game1_line_52, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_52, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_52, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_52, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_52, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
    
	if(maze_map[5][2]){
    //Write codes game1_line_51
    ui->game1_line_51 = lv_line_create(ui->game1);
    static lv_point_t game1_line_51[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game1_line_51, game1_line_51, 2);
    lv_obj_set_pos(ui->game1_line_51, MARGIN + CELL_W*1, MARGIN + CELL_H*2);
//    lv_obj_set_size(ui->game1_line_51, 24, 58);

    //Write style for game1_line_51, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_51, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_51, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_51, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_51, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
	
	if(maze_map[4][5]){
    //Write codes game1_line_43
    ui->game1_line_43 = lv_line_create(ui->game1);
    static lv_point_t game1_line_43[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game1_line_43, game1_line_43, 2);
    lv_obj_set_pos(ui->game1_line_43, MARGIN + CELL_W*2, MARGIN + CELL_H*2);
//    lv_obj_set_size(ui->game1_line_43, 59, 1);

    //Write style for game1_line_43, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_43, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_43, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_43, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_43, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	
      }if(maze_map[4][3]){
    //Write codes game1_line_42
    ui->game1_line_42 = lv_line_create(ui->game1);
    static lv_point_t game1_line_42[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game1_line_42, game1_line_42, 2);
    lv_obj_set_pos(ui->game1_line_42, MARGIN + CELL_W*1, MARGIN + CELL_H*2);
//    lv_obj_set_size(ui->game1_line_42, 61, 22);

    //Write style for game1_line_42, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_42, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_42, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_42, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_42, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[4][1]){
    //Write codes game1_line_41
    ui->game1_line_41 = lv_line_create(ui->game1);
    static lv_point_t game1_line_41[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game1_line_41, game1_line_41, 2);
    lv_obj_set_pos(ui->game1_line_41, MARGIN, MARGIN + CELL_H*2);
//    lv_obj_set_size(ui->game1_line_41, 63, 60);

    //Write style for game1_line_41, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_41, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_41, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_41, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_41, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[3][4]){
    //Write codes game1_line_32
    ui->game1_line_32 = lv_line_create(ui->game1);
    static lv_point_t game1_line_32[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game1_line_32, game1_line_32, 2);
    lv_obj_set_pos(ui->game1_line_32, MARGIN + CELL_W*2, MARGIN + CELL_H*1);
//    lv_obj_set_size(ui->game1_line_32, 63, 60);

    //Write style for game1_line_32, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_32, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_32, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_32, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_32, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[3][2]){
    //Write codes game1_line_31
    ui->game1_line_31 = lv_line_create(ui->game1);
    static lv_point_t game1_line_31[] =  {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game1_line_31, game1_line_31, 2);
    lv_obj_set_pos(ui->game1_line_31, MARGIN + CELL_W*1, MARGIN + CELL_H*1);
//    lv_obj_set_size(ui->game1_line_31, 63, 60);

    //Write style for game1_line_31, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_31, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_31, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_31, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_31, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[2][5]){
    //Write codes game1_line_23
    ui->game1_line_23 = lv_line_create(ui->game1);
    static lv_point_t game1_line_23[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game1_line_23, game1_line_23, 2);
    lv_obj_set_pos(ui->game1_line_23, MARGIN + CELL_W*2, MARGIN + CELL_H*1);
//    lv_obj_set_size(ui->game1_line_23, 65, 10);

    //Write style for game1_line_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_23, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_23, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_23, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[2][3]){
    //Write codes game1_line_22
    ui->game1_line_22 = lv_line_create(ui->game1);
    static lv_point_t game1_line_22[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game1_line_22, game1_line_22, 2);
    lv_obj_set_pos(ui->game1_line_22, MARGIN + CELL_W*1, MARGIN + CELL_H*1);
//    lv_obj_set_size(ui->game1_line_22, 68, 13);

    //Write style for game1_line_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_22, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_22, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_22, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[2][1]){
    //Write codes game1_line_21
    ui->game1_line_21 = lv_line_create(ui->game1);
    static lv_point_t game1_line_21[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game1_line_21, game1_line_21, 2);
    lv_obj_set_pos(ui->game1_line_21, MARGIN, MARGIN + CELL_H*1);
//    lv_obj_set_size(ui->game1_line_21, 63, 9);

    //Write style for game1_line_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_21, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_21, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_21, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[1][4]){
    //Write codes game1_line_12
    ui->game1_line_12 = lv_line_create(ui->game1);
    static lv_point_t game1_line_12[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game1_line_12, game1_line_12, 2);
    lv_obj_set_pos(ui->game1_line_12, MARGIN + CELL_W*2, MARGIN + CELL_H*0);
//    lv_obj_set_size(ui->game1_line_12, 22, 62);

    //Write style for game1_line_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_12, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_12, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[1][2]){
    //Write codes game1_line_11
    ui->game1_line_11 = lv_line_create(ui->game1);
    static lv_point_t game1_line_11[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game1_line_11, game1_line_11, 2);
    lv_obj_set_pos(ui->game1_line_11, MARGIN + CELL_W*1, MARGIN + CELL_H*0);
//    lv_obj_set_size(ui->game1_line_11, 27, 57);

    //Write style for game1_line_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_11, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->game1_line_11, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}
    //Write codes game1_line_04
    ui->game1_line_04 = lv_line_create(ui->game1);
    static lv_point_t game1_line_04[] = {{0, 0},{CELL_W * COLS, 0}};
	lv_line_set_points(ui->game1_line_04, game1_line_04, 2);
	lv_obj_set_pos(ui->game1_line_04, MARGIN, MARGIN + CELL_H * ROWS);
//    lv_obj_set_size(ui->game1_line_04, 207, 3);

    //Write style for game1_line_04, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_04, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_04, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_04, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_04, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes game1_line_03
    ui->game1_line_03 = lv_line_create(ui->game1);
    static lv_point_t game1_line_03[] = {{0, 0},{0, CELL_H * ROWS}};
    lv_line_set_points(ui->game1_line_03, game1_line_03, 2);
    lv_obj_set_pos(ui->game1_line_03, MARGIN + CELL_W * COLS, MARGIN);
//    lv_obj_set_size(ui->game1_line_03, 10, 276);

    //Write style for game1_line_03, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_03, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_03, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_03, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_03, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes game1_line_02
    ui->game1_line_02 = lv_line_create(ui->game1);
    static lv_point_t game1_line_02[] = {{0, 0},{0, CELL_H * ROWS}};
    lv_line_set_points(ui->game1_line_02, game1_line_02, 2);
    lv_obj_set_pos(ui->game1_line_02, MARGIN, MARGIN);
//    lv_obj_set_size(ui->game1_line_02, 5, 281);

    //Write style for game1_line_02, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_02, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_02, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_02, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_02, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes game1_line_01
    ui->game1_line_01 = lv_line_create(ui->game1);
    static lv_point_t game1_line_01[] = {{0, 0},{CELL_W * COLS, 0},};
    lv_line_set_points(ui->game1_line_01, game1_line_01, 2);
    lv_obj_set_pos(ui->game1_line_01, MARGIN, MARGIN);
//    lv_obj_set_size(ui->game1_line_01, MARGIN, LINE_WIDTH);

    //Write style for game1_line_01, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game1_line_01, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game1_line_01, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game1_line_01, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game1_line_01, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of game1.
        tank_init(ui->game1);
		bullet_system_init(ui->game1);

    //Update current screen layout.
    lv_obj_update_layout(ui->game1);

    //Init events for screen.
    events_init_game1(ui);
}
