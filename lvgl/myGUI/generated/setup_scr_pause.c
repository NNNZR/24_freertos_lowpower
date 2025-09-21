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



void setup_scr_pause(lv_ui *ui)
{
    //Write codes pause
    ui->pause = lv_obj_create(NULL);
    lv_obj_set_size(ui->pause, 240, 320);
    lv_obj_set_scrollbar_mode(ui->pause, LV_SCROLLBAR_MODE_OFF);

    //Write style for pause, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->pause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pause_label_4
    ui->pause_label_4 = lv_label_create(ui->pause);
    lv_label_set_text(ui->pause_label_4, "0");
    lv_label_set_long_mode(ui->pause_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pause_label_4, 126, 157);
    lv_obj_set_size(ui->pause_label_4, 100, 32);

    //Write style for pause_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pause_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pause_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pause_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pause_label_4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pause_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pause_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pause_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pause_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pause_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pause_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pause_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pause_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pause_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pause_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pause_img_2
    ui->pause_img_2 = lv_img_create(ui->pause);
    lv_obj_add_flag(ui->pause_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->pause_img_2, &_tankred_alpha_40x26);
    lv_img_set_pivot(ui->pause_img_2, 50,50);
    lv_img_set_angle(ui->pause_img_2, 0);
    lv_obj_set_pos(ui->pause_img_2, 152, 122);
    lv_obj_set_size(ui->pause_img_2, 40, 26);

    //Write style for pause_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->pause_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pause_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pause_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pause_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pause_label_3
    ui->pause_label_3 = lv_label_create(ui->pause);
    lv_label_set_text(ui->pause_label_3, "Player2");
    lv_label_set_long_mode(ui->pause_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pause_label_3, 126, 90);
    lv_obj_set_size(ui->pause_label_3, 100, 32);

    //Write style for pause_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pause_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pause_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pause_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pause_label_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pause_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pause_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pause_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pause_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pause_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pause_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pause_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pause_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pause_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pause_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pause_label_2
    ui->pause_label_2 = lv_label_create(ui->pause);
    lv_label_set_text(ui->pause_label_2, "0");
    lv_label_set_long_mode(ui->pause_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pause_label_2, 17, 157);
    lv_obj_set_size(ui->pause_label_2, 100, 32);

    //Write style for pause_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pause_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pause_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pause_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pause_label_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pause_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pause_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pause_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pause_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pause_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pause_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pause_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pause_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pause_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pause_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pause_img_1
    ui->pause_img_1 = lv_img_create(ui->pause);
    lv_obj_add_flag(ui->pause_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->pause_img_1, &_tankgreen4026_alpha_40x26);
    lv_img_set_pivot(ui->pause_img_1, 50,50);
    lv_img_set_angle(ui->pause_img_1, 0);
    lv_obj_set_pos(ui->pause_img_1, 43, 122);
    lv_obj_set_size(ui->pause_img_1, 40, 26);

    //Write style for pause_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->pause_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pause_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pause_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pause_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pause_label_1
    ui->pause_label_1 = lv_label_create(ui->pause);
    lv_label_set_text(ui->pause_label_1, "Player1");
    lv_label_set_long_mode(ui->pause_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pause_label_1, 14, 90);
    lv_obj_set_size(ui->pause_label_1, 100, 32);

    //Write style for pause_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pause_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pause_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pause_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pause_label_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pause_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pause_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pause_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pause_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pause_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pause_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pause_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pause_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pause_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pause_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of pause.


    //Update current screen layout.
    lv_obj_update_layout(ui->pause);

    //Init events for screen.
    events_init_pause(ui);
}
