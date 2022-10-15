/*setup pulse counter for ESP32
* 
* auther : Kazuki Ito
* date   : 2020/04/17
* ------------------------------------------------
*/

#include "Arduino.h"
#include "driver/pcnt.h"

#define PCNT_H_LIM_VAL  32767
#define PCNT_L_LIM_VAL -32767

void counter_setup_x4(pcnt_unit_t PCNT_UNIT, int ENCODER_A_PIN, int ENCODER_B_PIN)
{
    //for mecanum robot setting (INC count)
    pinMode( ENCODER_A_PIN, INPUT );
    pinMode( ENCODER_B_PIN, INPUT );
    
    pcnt_config_t ENCORDER_A_CONF; 
        ENCORDER_A_CONF.unit            = PCNT_UNIT;
        ENCORDER_A_CONF.channel         = PCNT_CHANNEL_0;
        ENCORDER_A_CONF.pulse_gpio_num  = ENCODER_A_PIN;
        ENCORDER_A_CONF.ctrl_gpio_num   = ENCODER_B_PIN;
        ENCORDER_A_CONF.lctrl_mode      = PCNT_MODE_REVERSE;
        ENCORDER_A_CONF.hctrl_mode      = PCNT_MODE_KEEP;
        ENCORDER_A_CONF.pos_mode        = PCNT_COUNT_INC;
        ENCORDER_A_CONF.neg_mode        = PCNT_COUNT_DEC;
        ENCORDER_A_CONF.counter_h_lim   = PCNT_H_LIM_VAL;
        ENCORDER_A_CONF.counter_l_lim   = PCNT_L_LIM_VAL;
    
    pcnt_config_t ENCORDER_B_CONF;
        ENCORDER_B_CONF.unit            = PCNT_UNIT;
        ENCORDER_B_CONF.channel         = PCNT_CHANNEL_1;
        ENCORDER_B_CONF.pulse_gpio_num  = ENCODER_B_PIN;
        ENCORDER_B_CONF.ctrl_gpio_num   = ENCODER_A_PIN;
        ENCORDER_B_CONF.lctrl_mode      = PCNT_MODE_KEEP;
        ENCORDER_B_CONF.hctrl_mode      = PCNT_MODE_REVERSE;
        ENCORDER_B_CONF.pos_mode        = PCNT_COUNT_INC;
        ENCORDER_B_CONF.neg_mode        = PCNT_COUNT_DEC;
        ENCORDER_B_CONF.counter_h_lim   = PCNT_H_LIM_VAL;
        ENCORDER_B_CONF.counter_l_lim   = PCNT_L_LIM_VAL;

  /* Initialize PCNT unit */
  pcnt_unit_config(&ENCORDER_A_CONF);
  pcnt_unit_config(&ENCORDER_B_CONF);
  //pcnt_event_enable(PCNT_UNIT, PCNT_EVT_H_LIM);
  //pcnt_event_enable(PCNT_UNIT, PCNT_EVT_L_LIM);
  pcnt_counter_pause(PCNT_UNIT);
  pcnt_counter_clear(PCNT_UNIT);
  pcnt_counter_resume(PCNT_UNIT);
  
}

void counter_setup_x1(pcnt_unit_t PCNT_UNIT, int ENCODER_A_PIN, int ENCODER_B_PIN)
{
    pinMode( ENCODER_A_PIN, INPUT );
    pinMode( ENCODER_B_PIN, INPUT );
    
    pcnt_config_t ENCORDER_CONF;
        ENCORDER_CONF.unit           = PCNT_UNIT;
        ENCORDER_CONF.pulse_gpio_num = ENCODER_A_PIN;
        ENCORDER_CONF.ctrl_gpio_num  = ENCODER_B_PIN;
        ENCORDER_CONF.channel        = PCNT_CHANNEL_0;
        ENCORDER_CONF.pos_mode       = PCNT_COUNT_DEC;
        ENCORDER_CONF.neg_mode       = PCNT_COUNT_INC;
        ENCORDER_CONF.lctrl_mode     = PCNT_MODE_REVERSE;
        ENCORDER_CONF.hctrl_mode     = PCNT_MODE_KEEP;
        ENCORDER_CONF.counter_h_lim  = PCNT_H_LIM_VAL;//max 32767;
        ENCORDER_CONF.counter_l_lim  = PCNT_L_LIM_VAL;//min -32768;

  /* Initialize PCNT unit */
  pcnt_unit_config(&ENCORDER_CONF);
  pcnt_counter_pause(PCNT_UNIT);
  pcnt_counter_clear(PCNT_UNIT);
  pcnt_counter_resume(PCNT_UNIT);

}
