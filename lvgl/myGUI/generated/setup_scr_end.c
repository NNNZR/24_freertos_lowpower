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
#include "w25qxx.h"
#include "usart.h"

extern int hit_id;
extern int chose_id;

extern lv_obj_t * mouse_cursor;
void setup_scr_end(lv_ui *ui)
{
	
	lv_obj_clear_flag(mouse_cursor, LV_OBJ_FLAG_HIDDEN);
	//read and send data
	uint8_t point[5];
	W25QXX_RTOS(READ, 0x000000, point, sizeof(point));
	if(hit_id==0){if(chose_id==1)point[0] += 1;else point[1] += 1;}
	else if(hit_id==1){if(chose_id==1)point[1] += 1;else point[0] += 1;}
	W25QXX_RTOS(WRITE, 0x000000, point, sizeof(point));
	char uart_buf[64];
	int len = snprintf(uart_buf, sizeof(uart_buf),"{\"user1\":%u,\"user2\":%u}\n",point[1], point[0]);
	HAL_UART_Transmit(&huart6, (uint8_t*)uart_buf, len, HAL_MAX_DELAY);
	
    //Write codes end
    ui->end = lv_obj_create(NULL);
    lv_obj_set_size(ui->end, 240, 320);
    lv_obj_set_scrollbar_mode(ui->end, LV_SCROLLBAR_MODE_OFF);

    //Write style for end, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->end, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes end_img_2
    ui->end_img_2 = lv_img_create(ui->end);
    lv_obj_add_flag(ui->end_img_2, LV_OBJ_FLAG_CLICKABLE);
    if(chose_id==1)lv_img_set_src(ui->end_img_2, &_tankred_alpha_40x26);
	else lv_img_set_src(ui->end_img_2, &_tankgreen4026_alpha_40x26);
    lv_img_set_pivot(ui->end_img_2, 50,50);
    lv_img_set_angle(ui->end_img_2, 0);
    lv_obj_set_pos(ui->end_img_2, 152, 122);
    lv_obj_set_size(ui->end_img_2, 40, 26);

    //Write style for end_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->end_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->end_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->end_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->end_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes end_label_2
    ui->end_label_2 = lv_label_create(ui->end);
    lv_label_set_text(ui->end_label_2, "Player2");
    lv_label_set_long_mode(ui->end_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->end_label_2, 126, 90);
    lv_obj_set_size(ui->end_label_2, 100, 32);

    //Write style for end_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->end_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->end_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->end_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->end_label_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->end_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->end_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->end_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->end_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->end_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->end_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->end_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->end_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->end_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->end_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes end_img_1
    ui->end_img_1 = lv_img_create(ui->end);
    lv_obj_add_flag(ui->end_img_1, LV_OBJ_FLAG_CLICKABLE);
    if(chose_id==1)lv_img_set_src(ui->end_img_1, &_tankgreen4026_alpha_40x26);
	else lv_img_set_src(ui->end_img_1, &_tankred_alpha_40x26);
    lv_img_set_pivot(ui->end_img_1, 50,50);
    lv_img_set_angle(ui->end_img_1, 0);
    lv_obj_set_pos(ui->end_img_1, 43, 122);
    lv_obj_set_size(ui->end_img_1, 40, 26);

    //Write style for end_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->end_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->end_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->end_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->end_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes end_label_1
    ui->end_label_1 = lv_label_create(ui->end);
    lv_label_set_text(ui->end_label_1, "Player1");
    lv_label_set_long_mode(ui->end_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->end_label_1, 14, 90);
    lv_obj_set_size(ui->end_label_1, 100, 32);

    //Write style for end_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->end_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->end_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->end_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->end_label_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->end_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->end_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->end_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->end_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->end_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->end_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->end_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->end_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->end_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->end_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes end_label_4
    ui->end_label_4 = lv_label_create(ui->end);
	if(hit_id==0)lv_label_set_text(ui->end_label_4, "1");
    else lv_label_set_text(ui->end_label_4, "0");
    lv_label_set_long_mode(ui->end_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->end_label_4, 126, 157);
    lv_obj_set_size(ui->end_label_4, 100, 32);

    //Write style for end_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->end_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->end_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->end_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->end_label_4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->end_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->end_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->end_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->end_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->end_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->end_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->end_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->end_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->end_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->end_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes end_label_3
    ui->end_label_3 = lv_label_create(ui->end);
	if(hit_id==1)lv_label_set_text(ui->end_label_3, "1");
    else lv_label_set_text(ui->end_label_3, "0");
    lv_label_set_long_mode(ui->end_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->end_label_3, 17, 157);
    lv_obj_set_size(ui->end_label_3, 100, 32);

    //Write style for end_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->end_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->end_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->end_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->end_label_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->end_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->end_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->end_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->end_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->end_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->end_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->end_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->end_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->end_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->end_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes end_btn_2
    ui->end_btn_2 = lv_btn_create(ui->end);
    ui->end_btn_2_label = lv_label_create(ui->end_btn_2);
    lv_label_set_text(ui->end_btn_2_label, "back");
    lv_label_set_long_mode(ui->end_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->end_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->end_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->end_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->end_btn_2, 70, 212);
    lv_obj_set_size(ui->end_btn_2, 102, 30);

    //Write style for end_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->end_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->end_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->end_btn_2, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->end_btn_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->end_btn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->end_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->end_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->end_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->end_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->end_btn_2, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->end_btn_2, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->end_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->end_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of end.


    //Update current screen layout.
    lv_obj_update_layout(ui->end);

    //Init events for screen.
    events_init_end(ui);
}
