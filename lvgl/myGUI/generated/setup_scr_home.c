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
#include "lv_dclock.h"
#include "usart.h"

int home_digital_clock_1_min_value = 0;
int home_digital_clock_1_hour_value = 12;
int home_digital_clock_1_sec_value = 0;
char home_digital_clock_1_meridiem[] = "AM";
void setup_scr_home(lv_ui *ui)
{
	
	char cmd[] = "{\"cmd\":\"get_time\"}\n";
    HAL_UART_Transmit(&huart6, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
    //Write codes home
    ui->home = lv_obj_create(NULL);
    lv_obj_set_size(ui->home, 240, 320);
    lv_obj_set_scrollbar_mode(ui->home, LV_SCROLLBAR_MODE_OFF);

    //Write style for home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_btn_2
    ui->home_btn_2 = lv_btn_create(ui->home);
    ui->home_btn_2_label = lv_label_create(ui->home_btn_2);
    lv_label_set_text(ui->home_btn_2_label, "start");
    lv_label_set_long_mode(ui->home_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->home_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->home_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->home_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->home_btn_2, 70, 163);
    lv_obj_set_size(ui->home_btn_2, 100, 50);

    //Write style for home_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_btn_2, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_btn_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->home_btn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->home_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->home_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->home_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->home_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_btn_2, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_btn_2, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_btn_3
    ui->home_btn_3 = lv_btn_create(ui->home);
    ui->home_btn_3_label = lv_label_create(ui->home_btn_3);
    lv_label_set_text(ui->home_btn_3_label, "settings");
    lv_label_set_long_mode(ui->home_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->home_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->home_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->home_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->home_btn_3, 70, 239);
    lv_obj_set_size(ui->home_btn_3, 100, 50);

    //Write style for home_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_btn_3, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_btn_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->home_btn_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->home_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->home_btn_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->home_btn_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->home_btn_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_btn_3, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_btn_3, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_clock_1
    static bool home_digital_clock_1_timer_enabled = false;
    ui->home_digital_clock_1 = lv_dclock_create(ui->home, "0:00 AM");
    if (!home_digital_clock_1_timer_enabled) {
        lv_timer_create(home_digital_clock_1_timer, 1000, NULL);
        home_digital_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->home_digital_clock_1, 72, 3);
    lv_obj_set_size(ui->home_digital_clock_1, 95, 25);

    //Write style for home_digital_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->home_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_digital_clock_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_digital_clock_1, &lv_font_Antonio_Regular_17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_digital_clock_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_digital_clock_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_digital_clock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_digital_clock_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_digital_clock_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_digital_clock_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digital_clock_1, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_img_1
    ui->home_img_1 = lv_img_create(ui->home);
    lv_obj_add_flag(ui->home_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_img_1, &_start_alpha_134x73);
    lv_img_set_pivot(ui->home_img_1, 50,50);
    lv_img_set_angle(ui->home_img_1, 0);
    lv_obj_set_pos(ui->home_img_1, 53, 57);
    lv_obj_set_size(ui->home_img_1, 134, 73);

    //Write style for home_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of home.


    //Update current screen layout.
    lv_obj_update_layout(ui->home);

    //Init events for screen.
    events_init_home(ui);
}
