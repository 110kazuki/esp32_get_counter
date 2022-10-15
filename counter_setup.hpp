/*setup pulse counter for ESP32
* 
* auther : Kazuki Ito
* date   : 2020/04/17
* ------------------------------------------------
*/

#pragma once
#ifndef INCLUDE_GUARD_HOGE_HPP
#define INCLUDE_GUARD_HOGE_HPP

#include "driver/pcnt.h"

  void counter_setup_x4(pcnt_unit_t PCNT_UNIT, int ENCODER_A_PIN, int ENCODER_B_PIN);
  
  void counter_setup_x1(pcnt_unit_t PCNT_UNIT, int ENCODER_A_PIN, int ENCODER_B_PIN);

#endif
