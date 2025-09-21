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


extern int maze_map[9][7];
extern uint8_t event_key;

extern int tank_Cstep;
extern int tank_Cangle;
extern float BULLET_SPEED;
extern int  BULLET_SPAWN_GRACE_MS;  


extern lv_obj_t * mouse_cursor;
void setup_scr_game2(lv_ui *ui)
{
	lv_obj_add_flag(mouse_cursor, LV_OBJ_FLAG_HIDDEN);
	tank_Cstep=3;
	tank_Cangle=5;
	BULLET_SPEED=150.0f;
	BULLET_SPAWN_GRACE_MS=200;	
	
	event_key = 0;
	prim_maze();

	
    //Write codes game2
    ui->game2 = lv_obj_create(NULL);
    lv_obj_set_size(ui->game2, 240, 320);
    lv_obj_set_scrollbar_mode(ui->game2, LV_SCROLLBAR_MODE_OFF);


    //Write style for game2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->game2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	if(maze_map[7][4])
	{
    //Write codes game2_line_72
    ui->game2_line_72 = lv_line_create(ui->game2);
    static lv_point_t game2_line_72[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game2_line_72, game2_line_72, 2);
    lv_obj_set_pos(ui->game2_line_72, MARGIN + CELL_W * 2, MARGIN + CELL_H * 3);
//    lv_obj_set_size(ui->game2_line_72, 4, 60);

    //Write style for game2_line_72, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_72, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_72, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_72, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_72, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
	if(maze_map[7][2])
	{
    //Write codes game2_line_71
    ui->game2_line_71 = lv_line_create(ui->game2);
    static lv_point_t game2_line_71[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game2_line_71, game2_line_71, 2);
    lv_obj_set_pos(ui->game2_line_71, MARGIN + CELL_W * 1, MARGIN + CELL_H * 3);
//    lv_obj_set_size(ui->game2_line_71, 6, 62);

    //Write style for game2_line_71, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_71, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_71, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_71, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_71, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
    if(maze_map[6][5])
	{
    //Write codes game2_line_63
    ui->game2_line_63 = lv_line_create(ui->game2);
    static lv_point_t game2_line_63[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game2_line_63, game2_line_63, 2);
    lv_obj_set_pos(ui->game2_line_63, MARGIN + CELL_W * 2, MARGIN + CELL_H * 3);
//    lv_obj_set_size(ui->game2_line_63, 62, 12);

    //Write style for game2_line_63, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_63, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_63, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_63, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_63, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
    if(maze_map[6][3])
    {	
    //Write codes game2_line_62
    ui->game2_line_62 = lv_line_create(ui->game2);
    static lv_point_t game2_line_62[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game2_line_62, game2_line_62, 2);
    lv_obj_set_pos(ui->game2_line_62, MARGIN + CELL_W * 1, MARGIN + CELL_H * 3);
//    lv_obj_set_size(ui->game2_line_62, 60, 6);

    //Write style for game2_line_62, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_62, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_62, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_62, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_62, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
     if(maze_map[6][1])
	{
    //Write codes game2_line_61
    ui->game2_line_61 = lv_line_create(ui->game2);
    static lv_point_t game2_line_61[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game2_line_61, game2_line_61, 2);
    lv_obj_set_pos(ui->game2_line_61, MARGIN, MARGIN + CELL_H * 3);
//    lv_obj_set_size(ui->game2_line_61, 63, 13);

    //Write style for game2_line_61, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_61, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_61, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_61, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_61, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
    if(maze_map[5][4])
    {
    //Write codes game2_line_52
    ui->game2_line_52 = lv_line_create(ui->game2);
    static lv_point_t game2_line_52[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game2_line_52, game2_line_52, 2);
    lv_obj_set_pos(ui->game2_line_52, MARGIN + CELL_W*2, MARGIN + CELL_H*2);
//    lv_obj_set_size(ui->game2_line_52, 5, 63);

    //Write style for game2_line_52, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_52, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_52, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_52, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_52, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
	if(maze_map[5][2])
	{
    //Write codes game2_line_51
    ui->game2_line_51 = lv_line_create(ui->game2);
    static lv_point_t game2_line_51[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game2_line_51, game2_line_51, 2);
    lv_obj_set_pos(ui->game2_line_51, MARGIN + CELL_W*1, MARGIN + CELL_H*2);
//    lv_obj_set_size(ui->game2_line_51, 7, 62);

    //Write style for game2_line_51, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_51, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_51, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_51, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_51, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
	
	if(maze_map[4][5]){
    //Write codes game2_line_43
    ui->game2_line_43 = lv_line_create(ui->game2);
    static lv_point_t game2_line_43[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game2_line_43, game2_line_43, 2);
    lv_obj_set_pos(ui->game2_line_43, MARGIN + CELL_W*2, MARGIN + CELL_H*2);
//    lv_obj_set_size(ui->game2_line_43, 63, 4);

    //Write style for game2_line_43, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_43, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_43, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_43, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_43, true, LV_PART_MAIN|LV_STATE_DEFAULT);
 }if(maze_map[4][3]){
    //Write codes game2_line_42
    ui->game2_line_42 = lv_line_create(ui->game2);
    static lv_point_t game2_line_42[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game2_line_42, game2_line_42, 2);
    lv_obj_set_pos(ui->game2_line_42, MARGIN + CELL_W*1, MARGIN + CELL_H*2);
//    lv_obj_set_size(ui->game2_line_42, 63, 60);

    //Write style for game2_line_42, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_42, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_42, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_42, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_42, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[4][1]){
    //Write codes game2_line_41
    ui->game2_line_41 = lv_line_create(ui->game2);
    static lv_point_t game2_line_41[] ={{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game2_line_41, game2_line_41, 2);
    lv_obj_set_pos(ui->game2_line_41, MARGIN, MARGIN + CELL_H*2);
//    lv_obj_set_size(ui->game2_line_41, 63, 60);

    //Write style for game2_line_41, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_41, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_41, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_41, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_41, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[3][4]){
    //Write codes game2_line_32
    ui->game2_line_32 = lv_line_create(ui->game2);
    static lv_point_t game2_line_32[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game2_line_32, game2_line_32, 2);
    lv_obj_set_pos(ui->game2_line_32, MARGIN + CELL_W*2, MARGIN + CELL_H*1);
//    lv_obj_set_size(ui->game2_line_32, 63, 60);

    //Write style for game2_line_32, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_32, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_32, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_32, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_32, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[3][2]){
    //Write codes game2_line_31
    ui->game2_line_31 = lv_line_create(ui->game2);
    static lv_point_t game2_line_31[] =  {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game2_line_31, game2_line_31, 2);
    lv_obj_set_pos(ui->game2_line_31, MARGIN + CELL_W*1, MARGIN + CELL_H*1);
//    lv_obj_set_size(ui->game2_line_31, 3, 65);

    //Write style for game2_line_31, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_31, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_31, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_31, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_31, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[2][5]){
    //Write codes game2_line_23
    ui->game2_line_23 = lv_line_create(ui->game2);
    static lv_point_t game2_line_23[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game2_line_23, game2_line_23, 2);
    lv_obj_set_pos(ui->game2_line_23, MARGIN + CELL_W*2, MARGIN + CELL_H*1);
//    lv_obj_set_size(ui->game2_line_23, 69, 9);

    //Write style for game2_line_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_23, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_23, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_23, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[2][3]){
    //Write codes game2_line_22
    ui->game2_line_22 = lv_line_create(ui->game2);
    static lv_point_t game2_line_22[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game2_line_22, game2_line_22, 2);
    lv_obj_set_pos(ui->game2_line_22, MARGIN + CELL_W*1, MARGIN + CELL_H*1);
//    lv_obj_set_size(ui->game2_line_22, 61, 15);

    //Write style for game2_line_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_22, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_22, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_22, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[2][1]){
    //Write codes game2_line_21
    ui->game2_line_21 = lv_line_create(ui->game2);
    static lv_point_t game2_line_21[] = {{0, 0},{CELL_W, 0}};
    lv_line_set_points(ui->game2_line_21, game2_line_21, 2);
    lv_obj_set_pos(ui->game2_line_21, MARGIN, MARGIN + CELL_H*1);
//    lv_obj_set_size(ui->game2_line_21, 63, 9);

    //Write style for game2_line_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_21, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_21, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_21, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[1][4]){
    //Write codes game2_line_12
    ui->game2_line_12 = lv_line_create(ui->game2);
    static lv_point_t game2_line_12[] =  {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game2_line_12, game2_line_12, 2);
    lv_obj_set_pos(ui->game2_line_12, MARGIN + CELL_W*2, MARGIN + CELL_H*0);
//    lv_obj_set_size(ui->game2_line_12, 5, 54);

    //Write style for game2_line_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_12, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_12, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}if(maze_map[1][2]){
    //Write codes game2_line_11
    ui->game2_line_11 = lv_line_create(ui->game2);
    static lv_point_t game2_line_11[] = {{0, 0},{0, CELL_H}};
    lv_line_set_points(ui->game2_line_11, game2_line_11, 2);
    lv_obj_set_pos(ui->game2_line_11, MARGIN + CELL_W*1, MARGIN + CELL_H*0);
//    lv_obj_set_size(ui->game2_line_11, 5, 52);

    //Write style for game2_line_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_11, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_11, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);
}
    //Write codes game2_line_04
    ui->game2_line_04 = lv_line_create(ui->game2);
    static lv_point_t game2_line_04[] = {{0, 0},{CELL_W * COLS, 0}};
    lv_line_set_points(ui->game2_line_04, game2_line_04, 2);
    lv_obj_set_pos(ui->game2_line_04, MARGIN, MARGIN + CELL_H * ROWS);
//    lv_obj_set_size(ui->game2_line_04, 201, 15);

    //Write style for game2_line_04, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_04, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_04, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_04, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_04, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes game2_line_03
    ui->game2_line_03 = lv_line_create(ui->game2);
    static lv_point_t game2_line_03[] ={{0, 0},{0, CELL_H * ROWS}};
    lv_line_set_points(ui->game2_line_03, game2_line_03, 2);
    lv_obj_set_pos(ui->game2_line_03, MARGIN + CELL_W * COLS, MARGIN);
//    lv_obj_set_size(ui->game2_line_03, 10, 276);

    //Write style for game2_line_03, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_03, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_03, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_03, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_03, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes game2_line_02
    ui->game2_line_02 = lv_line_create(ui->game2);
    static lv_point_t game2_line_02[] = {{0, 0},{0, CELL_H * ROWS}};
    lv_line_set_points(ui->game2_line_02, game2_line_02, 2);
    lv_obj_set_pos(ui->game2_line_02, MARGIN, MARGIN);
//    lv_obj_set_size(ui->game2_line_02, 5, 281);

    //Write style for game2_line_02, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_02, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_02, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_02, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_02, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes game2_line_01
    ui->game2_line_01 = lv_line_create(ui->game2);
    static lv_point_t game2_line_01[] = {{0, 0},{CELL_W * COLS, 0},};
    lv_line_set_points(ui->game2_line_01, game2_line_01, 2);
    lv_obj_set_pos(ui->game2_line_01, MARGIN, MARGIN);
////    lv_obj_set_size(ui->game2_line_01, 205, 1);

    //Write style for game2_line_01, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->game2_line_01, LINE_WIDTH, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->game2_line_01, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->game2_line_01, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->game2_line_01, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of game2.
		tank_init(ui->game2);
		bullet_system_init(ui->game2);

    //Update current screen layout.
    lv_obj_update_layout(ui->game2);

    //Init events for screen.
    events_init_game2(ui);
}
