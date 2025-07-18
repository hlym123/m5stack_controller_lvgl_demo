/******************************************************************************
 * M5Stack CoreS3 lvgl Demo 
 * @author: Enable
 * @date: 2025/07/17
 * 
 * 
 * 
 * 
 * 
 ******************************************************************************/
#include <stdio.h>
#include "bsp/esp-bsp.h"
#include "lvgl.h"
#include "esp_log.h"



static const char * TAG = "main";


LV_FONT_DECLARE(font_puhui_20_4);

static lv_obj_t *scr_main = nullptr;
static lv_obj_t *label_tip = nullptr;
static lv_obj_t *btn_a = nullptr;
static lv_obj_t *btn_b = nullptr;
static lv_obj_t *btn_c = nullptr;



void btn_event_cb(lv_event_t *e) 
{
    lv_obj_t *btn = (lv_obj_t *)lv_event_get_target(e);  
    lv_event_code_t code = (lv_event_code_t)lv_event_get_code(e);  

    if (code == LV_EVENT_CLICKED) {
        if (btn == btn_a) {
            lv_label_set_text(label_tip, "你按下了按键 A");
        } else if  (btn == btn_b) {
            lv_label_set_text(label_tip, "你按下了按键 B");
        } else if (btn == btn_c) {
            lv_label_set_text(label_tip, "你按下了按键 C");
        }  
    }
}
 
void ui_init()
{
    bsp_display_lock(0);

    scr_main = lv_scr_act();
    lv_obj_set_style_bg_color(scr_main, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(scr_main, LV_OPA_COVER, 0);  
    lv_obj_t* label = lv_label_create(scr_main);
    lv_obj_set_style_text_font(label, &font_puhui_20_4, 0);
    lv_label_set_text(label, "M5Stack CoreS3 lvgl 示例");
    lv_obj_set_style_text_color(label, lv_color_make(0x00, 0x00, 0xFF), 0);
    lv_obj_align(label, LV_ALIGN_TOP_MID, -10, 0);

    label_tip = lv_label_create(scr_main);
    lv_obj_set_style_text_font(label_tip, &font_puhui_20_4, 0);
    lv_label_set_text(label_tip, "Hello!");
    lv_obj_set_style_text_color(label_tip, lv_color_make(0x00, 0x00, 0xFF), 0);
    lv_obj_align(label_tip, LV_ALIGN_CENTER, 0, -20);

    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_bg_opa(&style_btn, LV_OPA_TRANSP);     
    lv_style_set_border_color(&style_btn, lv_color_make(0x00, 0x00, 0xFF));
    lv_style_set_border_width(&style_btn, 2);
    lv_style_set_radius(&style_btn, 10);                
    lv_style_set_pad_all(&style_btn, 10);   

    btn_a = lv_btn_create(scr_main);
    lv_obj_remove_style_all(btn_a);
    lv_obj_set_size(btn_a, 76, 50);
    lv_obj_align(btn_a, LV_ALIGN_CENTER, -100, 90);
    lv_obj_add_style(btn_a, &style_btn, 0);
    lv_obj_add_event_cb(btn_a, btn_event_cb, LV_EVENT_ALL, NULL);
    label = lv_label_create(btn_a);
    lv_label_set_text(label, "A");
    lv_obj_set_style_text_color(label, lv_color_make(0x00, 0x00, 0xFF), 0);
    lv_obj_center(label);

    btn_b = lv_btn_create(scr_main);
    lv_obj_remove_style_all(btn_b);
    lv_obj_set_size(btn_b, 76, 50);
    lv_obj_align(btn_b, LV_ALIGN_CENTER, 0, 90);
    lv_obj_add_style(btn_b, &style_btn, 0);
    lv_obj_add_event_cb(btn_b, btn_event_cb, LV_EVENT_ALL, NULL);
    label = lv_label_create(btn_b);
    lv_label_set_text(label, "B");
    lv_obj_set_style_text_color(label, lv_color_make(0x00, 0x00, 0xFF), 0);
    lv_obj_center(label);

    btn_c = lv_btn_create(scr_main);
    lv_obj_remove_style_all(btn_c);
    lv_obj_set_size(btn_c, 76, 50);
    lv_obj_align(btn_c, LV_ALIGN_CENTER, 100, 90);
    lv_obj_add_style(btn_c, &style_btn, 0);
    lv_obj_add_event_cb(btn_c, btn_event_cb, LV_EVENT_ALL, NULL);
    label = lv_label_create(btn_c);
    lv_label_set_text(label, "C");
    lv_obj_set_style_text_color(label, lv_color_make(0x00, 0x00, 0xFF), 0);
    lv_obj_center(label);

    bsp_display_unlock();
}


extern "C" void app_main(void)
{
    /* Initialize display and LVGL */
    static lv_disp_t *display = bsp_display_start();

    /* Set display brightness to 80% */
    bsp_display_brightness_set(80);

    ui_init();

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
