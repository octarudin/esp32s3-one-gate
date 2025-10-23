/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEFINES_H
#define __DEFINES_H

/* Private defines -----------------------------------------------------------*/
// 48  Loop to Esp Input In
// 47  Loop to Esp Input loop 2
// 21  Loop to Esp Input Loop 1 Out
#define LOOP_TO_ESP_IN          48
#define LOOP_TO_ESP_LOOP2       47
#define LOOP_TO_ESP_LOOP1_OUT   21

// 36  Barrier to Esp Input LS 1
// 37  Barrier to Esp Input LS 2
#define BARRIER_TO_ESP_LS1      36
#define BARRIER_TO_ESP_LS2      37

// 39  Esp to Barrier Output Up
// 40  Esp to Barrier Output Down
// 41  Esp to Barrier Output Stop
#define ESP_TO_BARRIER_UP       39
#define ESP_TO_BARRIER_DOWN     40
#define ESP_TO_BARRIER_STOP     41

// 1    Manless to Esp Input Stop
// 2    Manless to Esp Input Down 
// 42   Manless to Esp Up
#define MANLESS_IN_TO_ESP_IN_STOP   1
#define MANLESS_IN_TO_ESP_IN_DOWN   2
#define MANLESS_IN_TO_ESP_UP        42

// 41  Manless to Esp Stop -> 8
// 40  Manless to Esp Down -> 3
// 39  Manless to Esp Up -> 46
#define MANLESS_OUT_TO_ESP_STOP     8
#define MANLESS_OUT_TO_ESP_DOWN     3
#define MANLESS_OUT_TO_ESP_UP       46

// Output
// 4 Esp to manless
// 5 Esp to manless
// 6 Esp to manless
// 7 Esp to manless
// 15 Esp to manless
// 16 Esp to manless
// 17 Esp to manless
// 18 Esp to manless
#define ESP_TO_MANLESS_IN_LS1 4
#define ESP_TO_MANLESS_IN_LS2 5
#define ESP_TO_MANLESS_IN_LOOP1 6
#define ESP_TO_MANLESS_IN_LOOP2 7

#define ESP_TO_MANLESS_OUT_LS1 15
#define ESP_TO_MANLESS_OUT_LS2 16
#define ESP_TO_MANLESS_OUT_LOOP1 17
#define ESP_TO_MANLESS_OUT_LOOP2 18

#endif /* __DEFINES_H */
