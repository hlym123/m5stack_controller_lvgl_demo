/******************************************************************************
 * M5Stack Core lvgl Demo 
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
#include "iot_button.h"
#include "button_gpio.h"
#include "esp_log.h"
#include "button.h"



static const char * TAG = "main";


LV_FONT_DECLARE(font_puhui_20_4);

typedef enum {
    BUTTON_EVENT_A,
    BUTTON_EVENT_B,
    BUTTON_EVENT_C
} button_event_id_t;

static QueueHandle_t btn_event_queue = NULL;

lv_obj_t *scr_main = nullptr;


static void on_btn_a_click(void *arg, void *usr_data)
{
    button_event_id_t ev = BUTTON_EVENT_A;
    xQueueSendFromISR(btn_event_queue, &ev, NULL);
}

static void on_btn_b_click(void *arg, void *usr_data)
{
    button_event_id_t ev = BUTTON_EVENT_B;
    xQueueSendFromISR(btn_event_queue, &ev, NULL);
}

static void on_btn_c_click(void *arg, void *usr_data)
{
    button_event_id_t ev = BUTTON_EVENT_C;
    xQueueSendFromISR(btn_event_queue, &ev, NULL);
}

 
static void button_event_task(void *arg)
{
    button_event_id_t evt;

    bsp_display_lock(0);
    lv_obj_t *label_tip = lv_label_create(scr_main);
    lv_obj_set_style_text_font(label_tip, &font_puhui_20_4, 0);
    lv_label_set_text(label_tip, "Hello!");
    lv_obj_set_style_text_color(label_tip, lv_color_make(0x00, 0x00, 0xFF), 0);
    lv_obj_align(label_tip, LV_ALIGN_CENTER, 0, 0);
    bsp_display_unlock();

    while (1) {
        if (xQueueReceive(btn_event_queue, &evt, portMAX_DELAY)) {
            bsp_display_lock(0);
            switch (evt) {
                case BUTTON_EVENT_A:
                    lv_label_set_text(label_tip, "你按下了按键 A");
                    break;
                case BUTTON_EVENT_B:
                    lv_label_set_text(label_tip, "你按下了按键 B");
                    break;
                case BUTTON_EVENT_C:
                    lv_label_set_text(label_tip, "你按下了按键 C");
                    break;
            }
            bsp_display_unlock();
        }
    }
}


extern "C" void app_main(void)
{
    /* Initialize display and LVGL */
    static lv_disp_t *display = bsp_display_start();

    /* Set display brightness to 100% */
    bsp_display_backlight_on();

    /* Add and show objects on display */
    bsp_display_lock(0);
    scr_main = lv_scr_act();
    lv_obj_set_style_bg_color(scr_main, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(scr_main, LV_OPA_COVER, 0);  
    lv_obj_t* label = lv_label_create(scr_main);
    lv_obj_set_style_text_font(label, &font_puhui_20_4, 0);
    lv_label_set_text(label, "M5Stack Core lvgl 示例");
    lv_obj_set_style_text_color(label, lv_color_make(0x00, 0x00, 0xFF), 0);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 3);
    bsp_display_unlock();

    button_init();
    button_register_cb(BUTTON_A, BUTTON_SINGLE_CLICK, on_btn_a_click, NULL);
    button_register_cb(BUTTON_B, BUTTON_SINGLE_CLICK, on_btn_b_click, NULL);
    button_register_cb(BUTTON_C, BUTTON_SINGLE_CLICK, on_btn_c_click, NULL);

    btn_event_queue = xQueueCreate(5, sizeof(button_event_id_t));
    assert(btn_event_queue);

    xTaskCreate(button_event_task, "button_event_task", 4096, NULL, 5, NULL);
 
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
