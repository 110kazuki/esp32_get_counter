/* ------------------------------------------------
 * [ESP_get_encoder]
 *            
 * Auther : Kazuki Ito
 * 
 * -------------------------------------------------
 * [Pin out]
 *                 ● 3.3V          GND ●
 *                 ● Enable         23 ● 
 *                 ● 36(VP)         22 ● 
 *                 ● 39(VN)      1(TX) ●
 *                 ● 34(AD)      3(RX) ●
 *                 ● 35(AD)         21 ● 
 *                 ● 32(AD)        GND ●
 *                 ● 33(AD)         19 ● 
 *                 ● 25(AD)         18 ● 
 *                 ● 26(AD)          5 ● 
 *                 ● 27(AD)         17 ● 
 *                 ● 14(AD)         16 ● 
 *                 ● 12(AD)      4(AD) ● 
 *                 ● GND         0(AD) ● 
 *                 ● 13(AD)      2(AD) ● 
 *                 ● 9(D2)      15(AD) ● 
 *                 ● 10(D3)      8(D1) ●
 *                 ● 11(CMD)     7(D0) ●
 *                 ● 5V        31(CLK) ●
 *                         [USB]
 * 
-------------------------------------------------*/

#include "driver/pcnt.h"
#include "driver/gpio.h"
#include "driver/timer.h"
#include "driver/periph_ctrl.h"
#include "soc/timer_group_struct.h"
#include "esp_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "counter_setup.hpp"

#define ENCODER_SIGNAL_A 36
#define ENCODER_SIGNAL_B 39

//pulse counter
  long    master_count = 0;
  int16_t cycle_count  = 0;

//mecanical property
  int     Encoder_ppr    = 7; //pulse per revolution
  double  Gear_rario     = 1000;
  int     Multiplication = 4;
  double  OneT_pulse;
  double  pi = 3.1415;

//time
  long    time_rec = 0;

//motor
  double velocity = 0;

int16_t get_count( pcnt_unit_t PCNT_UNIT_X ){
  int16_t count;
    pcnt_get_counter_value(PCNT_UNIT_X, &count);
    pcnt_counter_clear(PCNT_UNIT_X);
    return count;
}

void setup()
{
  Serial.begin(115200);
  //encorder
  counter_setup_x4( PCNT_UNIT_0, ENCODER_SIGNAL_A, ENCODER_SIGNAL_B );

  //pulse
  OneT_pulse = Multiplication * Encoder_ppr * Gear_rario;
}

void loop()
{
    //get count
    cycle_count = get_count( PCNT_UNIT_0 );
    master_count = master_count + cycle_count;

    //velocity
    velocity = ( (cycle_count / OneT_pulse) * 2 * pi ) / ((millis() - time_rec )/1000.0); //[rad/s]
    time_rec = millis();

    Serial.printf("cycle count : %d , total : %ld, velocity : %0.4f\n", cycle_count, master_count, velocity );
    delay(10);
}
