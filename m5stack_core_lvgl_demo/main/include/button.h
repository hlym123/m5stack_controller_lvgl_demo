#ifndef _BUTTON_MGR_H_
#define _BUTTON_MGR_H_

#include "iot_button.h"
#include "button_gpio.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BUTTON_A = 0,
    BUTTON_B,
    BUTTON_C,
    BUTTON_ID_MAX,
} button_id_t;

typedef void (*button_cb_t)(void *arg, void *usr_data);

/**
 * @brief 初始化所有按键
 */
esp_err_t button_init(void);

/**
 * @brief 注册按键事件
 */
esp_err_t button_register_cb(button_id_t btn_id, button_event_t event, button_cb_t cb, void *usr_data);

/**
 * @brief 获取按键句柄
 */
button_handle_t button_get_handle(button_id_t btn_id);

#ifdef __cplusplus
}
#endif

#endif // _BUTTON_MGR_H_
