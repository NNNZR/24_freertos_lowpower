/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *screen_1_ta_1;
	lv_obj_t *home;
	bool home_del;
	lv_obj_t *home_btn_2;
	lv_obj_t *home_btn_2_label;
	lv_obj_t *home_btn_3;
	lv_obj_t *home_btn_3_label;
	lv_obj_t *home_digital_clock_1;
	lv_obj_t *home_img_1;
	lv_obj_t *character;
	bool character_del;
	lv_obj_t *character_label_1;
	lv_obj_t *character_label_3;
	lv_obj_t *character_img_1;
	lv_obj_t *character_img_2;
	lv_obj_t *character_btn_1;
	lv_obj_t *character_btn_1_label;
	lv_obj_t *character_btn_3;
	lv_obj_t *character_btn_3_label;
	lv_obj_t *character_label_4;
	lv_obj_t *game;
	bool game_del;
	lv_obj_t *game_btn_1;
	lv_obj_t *game_btn_1_label;
	lv_obj_t *game_btn_2;
	lv_obj_t *game_btn_2_label;
	lv_obj_t *game_btn_3;
	lv_obj_t *game_btn_3_label;
	lv_obj_t *game_btn_4;
	lv_obj_t *game_btn_4_label;
	lv_obj_t *game_btn_5;
	lv_obj_t *game_btn_5_label;
	lv_obj_t *game_btn_6;
	lv_obj_t *game_btn_6_label;
	lv_obj_t *settings;
	bool settings_del;
	lv_obj_t *settings_btn_1;
	lv_obj_t *settings_btn_1_label;
	lv_obj_t *settings_btn_4;
	lv_obj_t *settings_btn_4_label;
	lv_obj_t *settings_btn_3;
	lv_obj_t *settings_btn_3_label;
	lv_obj_t *settings_btn_2;
	lv_obj_t *settings_btn_2_label;
	lv_obj_t *settings_label_4;
	lv_obj_t *settings_label_3;
	lv_obj_t *settings_label_2;
	lv_obj_t *settings_label_1;
	lv_obj_t *settings_label_5;
	lv_obj_t *game1;
	bool game1_del;
	lv_obj_t *game1_line_72;
	lv_obj_t *game1_line_71;
	lv_obj_t *game1_line_63;
	lv_obj_t *game1_line_62;
	lv_obj_t *game1_line_61;
	lv_obj_t *game1_line_52;
	lv_obj_t *game1_line_51;
	lv_obj_t *game1_line_43;
	lv_obj_t *game1_line_42;
	lv_obj_t *game1_line_41;
	lv_obj_t *game1_line_32;
	lv_obj_t *game1_line_31;
	lv_obj_t *game1_line_23;
	lv_obj_t *game1_line_22;
	lv_obj_t *game1_line_21;
	lv_obj_t *game1_line_12;
	lv_obj_t *game1_line_11;
	lv_obj_t *game1_line_04;
	lv_obj_t *game1_line_03;
	lv_obj_t *game1_line_02;
	lv_obj_t *game1_line_01;
	lv_obj_t *game2;
	bool game2_del;
	lv_obj_t *game2_line_72;
	lv_obj_t *game2_line_71;
	lv_obj_t *game2_line_63;
	lv_obj_t *game2_line_62;
	lv_obj_t *game2_line_61;
	lv_obj_t *game2_line_52;
	lv_obj_t *game2_line_51;
	lv_obj_t *game2_line_43;
	lv_obj_t *game2_line_42;
	lv_obj_t *game2_line_41;
	lv_obj_t *game2_line_32;
	lv_obj_t *game2_line_31;
	lv_obj_t *game2_line_23;
	lv_obj_t *game2_line_22;
	lv_obj_t *game2_line_21;
	lv_obj_t *game2_line_12;
	lv_obj_t *game2_line_11;
	lv_obj_t *game2_line_04;
	lv_obj_t *game2_line_03;
	lv_obj_t *game2_line_02;
	lv_obj_t *game2_line_01;
	lv_obj_t *game3;
	bool game3_del;
	lv_obj_t *game3_line_93;
	lv_obj_t *game3_line_92;
	lv_obj_t *game3_line_91;
	lv_obj_t *game3_line_84;
	lv_obj_t *game3_line_83;
	lv_obj_t *game3_line_82;
	lv_obj_t *game3_line_81;
	lv_obj_t *game3_line_73;
	lv_obj_t *game3_line_72;
	lv_obj_t *game3_line_71;
	lv_obj_t *game3_line_64;
	lv_obj_t *game3_line_63;
	lv_obj_t *game3_line_62;
	lv_obj_t *game3_line_61;
	lv_obj_t *game3_line_53;
	lv_obj_t *game3_line_52;
	lv_obj_t *game3_line_51;
	lv_obj_t *game3_line_44;
	lv_obj_t *game3_line_43;
	lv_obj_t *game3_line_42;
	lv_obj_t *game3_line_41;
	lv_obj_t *game3_line_33;
	lv_obj_t *game3_line_32;
	lv_obj_t *game3_line_31;
	lv_obj_t *game3_line_24;
	lv_obj_t *game3_line_23;
	lv_obj_t *game3_line_22;
	lv_obj_t *game3_line_21;
	lv_obj_t *game3_line_13;
	lv_obj_t *game3_line_12;
	lv_obj_t *game3_line_11;
	lv_obj_t *game3_line_04;
	lv_obj_t *game3_line_03;
	lv_obj_t *game3_line_02;
	lv_obj_t *game3_line_01;
	lv_obj_t *game4;
	bool game4_del;
	lv_obj_t *game4_line_93;
	lv_obj_t *game4_line_92;
	lv_obj_t *game4_line_91;
	lv_obj_t *game4_line_84;
	lv_obj_t *game4_line_83;
	lv_obj_t *game4_line_82;
	lv_obj_t *game4_line_81;
	lv_obj_t *game4_line_73;
	lv_obj_t *game4_line_72;
	lv_obj_t *game4_line_71;
	lv_obj_t *game4_line_64;
	lv_obj_t *game4_line_63;
	lv_obj_t *game4_line_62;
	lv_obj_t *game4_line_61;
	lv_obj_t *game4_line_53;
	lv_obj_t *game4_line_52;
	lv_obj_t *game4_line_51;
	lv_obj_t *game4_line_44;
	lv_obj_t *game4_line_43;
	lv_obj_t *game4_line_42;
	lv_obj_t *game4_line_41;
	lv_obj_t *game4_line_33;
	lv_obj_t *game4_line_32;
	lv_obj_t *game4_line_31;
	lv_obj_t *game4_line_24;
	lv_obj_t *game4_line_23;
	lv_obj_t *game4_line_22;
	lv_obj_t *game4_line_21;
	lv_obj_t *game4_line_13;
	lv_obj_t *game4_line_12;
	lv_obj_t *game4_line_11;
	lv_obj_t *game4_line_04;
	lv_obj_t *game4_line_03;
	lv_obj_t *game4_line_02;
	lv_obj_t *game4_line_01;
	lv_obj_t *game5;
	bool game5_del;
	lv_obj_t *game5_line_155;
	lv_obj_t *game5_line_154;
	lv_obj_t *game5_line_153;
	lv_obj_t *game5_line_152;
	lv_obj_t *game5_line_151;
	lv_obj_t *game5_line_146;
	lv_obj_t *game5_line_145;
	lv_obj_t *game5_line_144;
	lv_obj_t *game5_line_143;
	lv_obj_t *game5_line_142;
	lv_obj_t *game5_line_141;
	lv_obj_t *game5_line_135;
	lv_obj_t *game5_line_134;
	lv_obj_t *game5_line_133;
	lv_obj_t *game5_line_132;
	lv_obj_t *game5_line_131;
	lv_obj_t *game5_line_126;
	lv_obj_t *game5_line_125;
	lv_obj_t *game5_line_124;
	lv_obj_t *game5_line_123;
	lv_obj_t *game5_line_122;
	lv_obj_t *game5_line_121;
	lv_obj_t *game5_line_115;
	lv_obj_t *game5_line_114;
	lv_obj_t *game5_line_113;
	lv_obj_t *game5_line_112;
	lv_obj_t *game5_line_111;
	lv_obj_t *game5_line_106;
	lv_obj_t *game5_line_105;
	lv_obj_t *game5_line_104;
	lv_obj_t *game5_line_103;
	lv_obj_t *game5_line_102;
	lv_obj_t *game5_line_101;
	lv_obj_t *game5_line_95;
	lv_obj_t *game5_line_94;
	lv_obj_t *game5_line_93;
	lv_obj_t *game5_line_92;
	lv_obj_t *game5_line_91;
	lv_obj_t *game5_line_86;
	lv_obj_t *game5_line_85;
	lv_obj_t *game5_line_84;
	lv_obj_t *game5_line_83;
	lv_obj_t *game5_line_82;
	lv_obj_t *game5_line_81;
	lv_obj_t *game5_line_75;
	lv_obj_t *game5_line_74;
	lv_obj_t *game5_line_73;
	lv_obj_t *game5_line_72;
	lv_obj_t *game5_line_71;
	lv_obj_t *game5_line_66;
	lv_obj_t *game5_line_65;
	lv_obj_t *game5_line_64;
	lv_obj_t *game5_line_63;
	lv_obj_t *game5_line_62;
	lv_obj_t *game5_line_61;
	lv_obj_t *game5_line_55;
	lv_obj_t *game5_line_54;
	lv_obj_t *game5_line_53;
	lv_obj_t *game5_line_52;
	lv_obj_t *game5_line_51;
	lv_obj_t *game5_line_46;
	lv_obj_t *game5_line_45;
	lv_obj_t *game5_line_44;
	lv_obj_t *game5_line_43;
	lv_obj_t *game5_line_42;
	lv_obj_t *game5_line_41;
	lv_obj_t *game5_line_35;
	lv_obj_t *game5_line_34;
	lv_obj_t *game5_line_33;
	lv_obj_t *game5_line_32;
	lv_obj_t *game5_line_31;
	lv_obj_t *game5_line_26;
	lv_obj_t *game5_line_25;
	lv_obj_t *game5_line_24;
	lv_obj_t *game5_line_23;
	lv_obj_t *game5_line_22;
	lv_obj_t *game5_line_21;
	lv_obj_t *game5_line_15;
	lv_obj_t *game5_line_14;
	lv_obj_t *game5_line_13;
	lv_obj_t *game5_line_12;
	lv_obj_t *game5_line_11;
	lv_obj_t *game5_line_04;
	lv_obj_t *game5_line_03;
	lv_obj_t *game5_line_02;
	lv_obj_t *game5_line_01;
	lv_obj_t *pause;
	bool pause_del;
	lv_obj_t *pause_label_4;
	lv_obj_t *pause_img_2;
	lv_obj_t *pause_label_3;
	lv_obj_t *pause_label_2;
	lv_obj_t *pause_img_1;
	lv_obj_t *pause_label_1;
	lv_obj_t *end;
	bool end_del;
	lv_obj_t *end_img_2;
	lv_obj_t *end_label_2;
	lv_obj_t *end_img_1;
	lv_obj_t *end_label_1;
	lv_obj_t *end_label_4;
	lv_obj_t *end_label_3;
	lv_obj_t *end_btn_2;
	lv_obj_t *end_btn_2_label;
	lv_obj_t *g_kb_top_layer;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_1(lv_ui *ui);
void setup_scr_home(lv_ui *ui);
void setup_scr_character(lv_ui *ui);
void setup_scr_game(lv_ui *ui);
void setup_scr_settings(lv_ui *ui);
void setup_scr_game1(lv_ui *ui);
void setup_scr_game2(lv_ui *ui);
void setup_scr_game3(lv_ui *ui);
void setup_scr_game4(lv_ui *ui);
void setup_scr_game5(lv_ui *ui);
void setup_scr_pause(lv_ui *ui);
void setup_scr_end(lv_ui *ui);
LV_IMG_DECLARE(_start_alpha_134x73);
LV_IMG_DECLARE(_tankgreen4026_alpha_40x26);
LV_IMG_DECLARE(_tankred_alpha_40x26);
LV_IMG_DECLARE(_tankred_alpha_40x26);
LV_IMG_DECLARE(_tankgreen4026_alpha_40x26);
LV_IMG_DECLARE(_tankred_alpha_40x26);
LV_IMG_DECLARE(_tankgreen4026_alpha_40x26);

LV_FONT_DECLARE(lv_font_montserratMedium_14)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_18)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_Antonio_Regular_17)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)


#ifdef __cplusplus
}
#endif
#endif
