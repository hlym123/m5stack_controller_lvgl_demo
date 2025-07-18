#include "button.h"
#include "esp_log.h"
#include "bsp/esp-bsp.h"


static const char *TAG = "button";

// 初始化按键引脚 
static const int button_gpio_nums[BUTTON_ID_MAX] = {BSP_BUTTON_LEFT, BSP_BUTTON_MIDDLE, BSP_BUTTON_RIGHT};
static button_handle_t button_handles[BUTTON_ID_MAX] = {NULL};


esp_err_t button_init(void)
{
    esp_err_t ret = ESP_OK;
    const button_config_t btn_cfg = {0};

    for (int i = 0; i < BUTTON_ID_MAX; i++) {
        const button_gpio_config_t gpio_cfg = {
            .gpio_num = button_gpio_nums[i],
            .active_level = 0,
        };
        
        ret = iot_button_new_gpio_device(&btn_cfg, &gpio_cfg, &button_handles[i]);
        if (ret != ESP_OK || button_handles[i] == NULL) {
            ESP_LOGE(TAG, "Failed to create button %d", i);
            return ESP_FAIL;
        }
    }
    return ESP_OK;
}

esp_err_t button_register_cb(button_id_t btn_id, button_event_t event, button_cb_t cb, void *usr_data)
{
    if (btn_id >= BUTTON_ID_MAX || button_handles[btn_id] == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return iot_button_register_cb(button_handles[btn_id], event, NULL, cb, usr_data);
}

button_handle_t button_get_handle(button_id_t btn_id)
{
    if (btn_id >= BUTTON_ID_MAX) return NULL;
    return button_handles[btn_id];
}

