/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "w25qxx.h"
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"
#include "usart.h"

static void screen_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
// 
        break;
    }
    default:
        break;
    }
}

void screen1_async_cb(void *param)
{
	lv_event_send(guider_ui.screen_1_ta_1, LV_EVENT_CANCEL, guider_ui.g_kb_top_layer);
	ui_load_scr_animation(&guider_ui, &guider_ui.home, guider_ui.home_del, &guider_ui.screen_1_del, setup_scr_home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
}
extern char pd[33];
static void screen_1_ta_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {

		const char* input_password=lv_textarea_get_text(guider_ui.screen_1_ta_1);
		if(strcmp(input_password,pd)==0)lv_async_call(screen1_async_cb,NULL);	
        break;
    }
    default:
        break;
    }
}

void events_init_screen_1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_1, screen_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_ta_1, screen_1_ta_1_event_handler, LV_EVENT_ALL, ui);
}


static void home_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.character, guider_ui.character_del, &guider_ui.home_del, setup_scr_character, LV_SCR_LOAD_ANIM_FADE_ON, 200, 20, false, true);
        break;
    }
    default:
        break;
    }
}

static void home_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.settings, guider_ui.settings_del, &guider_ui.home_del, setup_scr_settings, LV_SCR_LOAD_ANIM_FADE_ON, 200, 20, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_home (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->home_btn_2, home_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_btn_3, home_btn_3_event_handler, LV_EVENT_ALL, ui);
}

extern lv_ui guider_ui;
extern int chose_id;
static void character_img_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		if(chose_id==1)
		{
			chose_id*=-1;
			lv_obj_set_pos(guider_ui.character_img_1,152,122);
			lv_obj_set_pos(guider_ui.character_img_2,43,122);
		}
		else
		{
			chose_id*=-1;
			lv_obj_set_pos(guider_ui.character_img_1,43,122);
			lv_obj_set_pos(guider_ui.character_img_2,152,122);
		}
        break;
    }
    default:
        break;
    }
}

static void character_img_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		
		if(chose_id==1)
		{
			chose_id*=-1;
			lv_obj_set_pos(guider_ui.character_img_1,152,122);
			lv_obj_set_pos(guider_ui.character_img_2,43,122);
		}
		else
		{
			chose_id*=-1;
			lv_obj_set_pos(guider_ui.character_img_1,43,122);
			lv_obj_set_pos(guider_ui.character_img_2,152,122);
		}
        break;
    }
    default:
        break;
    }
}

static void character_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.game, guider_ui.game_del, &guider_ui.character_del, setup_scr_game, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void character_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home, guider_ui.home_del, &guider_ui.character_del, setup_scr_home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_character (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->character_img_1, character_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->character_img_2, character_img_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->character_btn_1, character_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->character_btn_3, character_btn_3_event_handler, LV_EVENT_ALL, ui);
}

static void game_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home, guider_ui.home_del, &guider_ui.game_del, setup_scr_home, LV_SCR_LOAD_ANIM_NONE, 200, 20, false, true);
        break;
    }
    default:
        break;
    }
}

static void game_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home, guider_ui.home_del, &guider_ui.game_del, setup_scr_home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 20, false, true);
        break;
    }
    default:
        break;
    }
}

static void game_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.game1, guider_ui.game1_del, &guider_ui.game_del, setup_scr_game1, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void game_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.game2, guider_ui.game2_del, &guider_ui.game_del, setup_scr_game2, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void game_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.game3, guider_ui.game3_del, &guider_ui.game_del, setup_scr_game3, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void game_btn_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.game4, guider_ui.game4_del, &guider_ui.game_del, setup_scr_game4, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void game_btn_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.game5, guider_ui.game5_del, &guider_ui.game_del, setup_scr_game5, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_game (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->game, game_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->game_btn_1, game_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->game_btn_2, game_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->game_btn_3, game_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->game_btn_4, game_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->game_btn_5, game_btn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->game_btn_6, game_btn_6_event_handler, LV_EVENT_ALL, ui);
}

static void settings_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home, guider_ui.home_del, &guider_ui.settings_del, setup_scr_home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 20, false, true);
        break;
    }
    default:
        break;
    }
}

static void settings_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		uint8_t point[5]={0};
		W25QXX_RTOS(WRITE, 0x000000, point, sizeof(point));
        break;
    }
    default:
        break;
    }
}

static void settings_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		

        break;
    }
    default:
        break;
    }
}

static void settings_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		char cmd[] = "{\"cmd\":\"get_time\"}\n";
        HAL_UART_Transmit(&huart6, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
        break;
    }
    default:
        break;
    }
}

void events_init_settings (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->settings_btn_1, settings_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->settings_btn_4, settings_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->settings_btn_3, settings_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->settings_btn_2, settings_btn_2_event_handler, LV_EVENT_ALL, ui);
}

extern uint8_t event_key;
extern lv_timer_t *tank_move_timer;
extern lv_timer_t *bullet_timer;

void game1_async_cb(void *param) {
    // 这里安全删除定时器和切屏
    if(bullet_timer) 
    {
    lv_timer_del(bullet_timer);
    bullet_timer = NULL;
    }
    if(tank_move_timer) 
    {
    lv_timer_del(tank_move_timer);
    tank_move_timer = NULL;
    }
    if(lv_obj_is_valid(guider_ui.game1)) {  // 确认对象存在
        ui_load_scr_animation(&guider_ui, &guider_ui.end, guider_ui.end_del, &guider_ui.game1_del, setup_scr_end, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
    }
}


static void game1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_KEY:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.pause, guider_ui.pause_del, &guider_ui.game1_del, setup_scr_pause, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false, true);
        break;
    }
    case LV_EVENT_CLICKED:
    {
		if(event_key==10)
		lv_async_call(game1_async_cb,NULL);
//        ui_load_scr_animation(&guider_ui, &guider_ui.end, guider_ui.end_del, &guider_ui.game1_del, setup_scr_end, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		event_key = 0;
        break;
    }
    default:
        break;
    }
}

void events_init_game1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->game1, game1_event_handler, LV_EVENT_ALL, ui);
}

void game2_async_cb(void *param) {
    // 这里安全删除定时器和切屏
    if(bullet_timer) 
    {
    lv_timer_del(bullet_timer);
    bullet_timer = NULL;
    }
    if(tank_move_timer) 
    {
    lv_timer_del(tank_move_timer);
    tank_move_timer = NULL;
    }
    if(lv_obj_is_valid(guider_ui.game2)) {  // 确认对象存在
        ui_load_scr_animation(&guider_ui, &guider_ui.end, guider_ui.end_del, &guider_ui.game2_del, setup_scr_end, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
    }
}


static void game2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		if(event_key==10)
		lv_async_call(game2_async_cb,NULL);
		event_key = 0;
//        ui_load_scr_animation(&guider_ui, &guider_ui.pause, guider_ui.pause_del, &guider_ui.game2_del, setup_scr_pause, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_game2 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->game2, game2_event_handler, LV_EVENT_ALL, ui);
}

void game3_async_cb(void *param) {
    // 这里安全删除定时器和切屏
    if(bullet_timer) 
    {
    lv_timer_del(bullet_timer);
    bullet_timer = NULL;
    }
    if(tank_move_timer) 
    {
    lv_timer_del(tank_move_timer);
    tank_move_timer = NULL;
    }
    if(lv_obj_is_valid(guider_ui.game3)) {  // 确认对象存在
        ui_load_scr_animation(&guider_ui, &guider_ui.end, guider_ui.end_del, &guider_ui.game3_del, setup_scr_end, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
    }
}

static void game3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		if(event_key==10)
		lv_async_call(game3_async_cb,NULL);
		event_key = 0;
//        ui_load_scr_animation(&guider_ui, &guider_ui.pause, guider_ui.pause_del, &guider_ui.game3_del, setup_scr_pause, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false, true);
        break;
    }

    default:
        break;
    }
}

void events_init_game3 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->game3, game3_event_handler, LV_EVENT_ALL, ui);
}

void game4_async_cb(void *param) {
    // 这里安全删除定时器和切屏
    if(bullet_timer) 
    {
    lv_timer_del(bullet_timer);
    bullet_timer = NULL;
    }
    if(tank_move_timer) 
    {
    lv_timer_del(tank_move_timer);
    tank_move_timer = NULL;
    }
    if(lv_obj_is_valid(guider_ui.game4)) {  // 确认对象存在
        ui_load_scr_animation(&guider_ui, &guider_ui.end, guider_ui.end_del, &guider_ui.game4_del, setup_scr_end, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
    }
}

static void game4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		if(event_key==10)
		lv_async_call(game4_async_cb,NULL);
		event_key = 0;
//        ui_load_scr_animation(&guider_ui, &guider_ui.pause, guider_ui.pause_del, &guider_ui.game4_del, setup_scr_pause, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false, true);
        break;
    }

    default:
        break;
    }
}

void events_init_game4 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->game4, game4_event_handler, LV_EVENT_ALL, ui);
}

void game5_async_cb(void *param) {
    // 这里安全删除定时器和切屏
    if(bullet_timer) 
    {
    lv_timer_del(bullet_timer);
    bullet_timer = NULL;
    }
    if(tank_move_timer) 
    {
    lv_timer_del(tank_move_timer);
    tank_move_timer = NULL;
    }
    if(lv_obj_is_valid(guider_ui.game5)) {  // 确认对象存在
        ui_load_scr_animation(&guider_ui, &guider_ui.end, guider_ui.end_del, &guider_ui.game5_del, setup_scr_end, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
    }
}

static void game5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		if(event_key==10)
		lv_async_call(game5_async_cb,NULL);
		event_key = 0;
//        ui_load_scr_animation(&guider_ui, &guider_ui.pause, guider_ui.pause_del, &guider_ui.game5_del, setup_scr_pause, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false, true);
        break;
    }

    default:
        break;
    }
}

void events_init_game5 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->game5, game5_event_handler, LV_EVENT_ALL, ui);
}

static void pause_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        if (1) {
            ui_load_scr_animation(&guider_ui, &guider_ui.game1, guider_ui.game1_del, &guider_ui.pause_del, setup_scr_game1, LV_SCR_LOAD_ANIM_MOVE_TOP, 400, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

void events_init_pause (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->pause, pause_event_handler, LV_EVENT_ALL, ui);
}

static void end_label_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_label_set_text(guider_ui.end_label_3, "1");
        break;
    }
    default:
        break;
    }
}

static void end_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home, guider_ui.home_del, &guider_ui.end_del, setup_scr_home, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_end (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->end_label_3, end_label_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->end_btn_2, end_btn_2_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
