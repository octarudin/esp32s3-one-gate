/**
  ******************************************************************************
  * @file           : main.cpp
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 Aba Robotics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Private includes ----------------------------------------------------------*/
#include <Arduino.h>
#include "defines.h"

/* Private defines ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
String str;
hw_timer_t *timer = NULL;
const int TIMER_TIMEOUT_US = 10000;  // 10 ms (dalam mikrodetik)
volatile bool timerExpired = false;

/* Private function prototypes -----------------------------------------------*/
void IRAM_ATTR onTimer();
void resetTimer();
void processCommand(String command);

/**
  * @brief  The application entry point.
  * @retval int
  */
void setup() {
  /* Input declarations -----------------------------------------------------------*/
  pinMode(LOOP_TO_ESP_IN, INPUT);
  pinMode(LOOP_TO_ESP_LOOP2, INPUT);
  pinMode(LOOP_TO_ESP_LOOP1_OUT, INPUT);

  pinMode(BARRIER_TO_ESP_LS1, INPUT);
  pinMode(BARRIER_TO_ESP_LS2, INPUT);

  pinMode(MANLESS_IN_TO_ESP_IN_STOP, INPUT);
  pinMode(MANLESS_IN_TO_ESP_IN_DOWN, INPUT);
  pinMode(MANLESS_IN_TO_ESP_UP, INPUT);

  pinMode(MANLESS_OUT_TO_ESP_STOP, INPUT);
  pinMode(MANLESS_OUT_TO_ESP_DOWN, INPUT);
  pinMode(MANLESS_OUT_TO_ESP_UP, INPUT);

  /* Output declarations -----------------------------------------------------------*/
  pinMode(ESP_TO_BARRIER_UP, OUTPUT);
  pinMode(ESP_TO_BARRIER_DOWN, OUTPUT);
  pinMode(ESP_TO_BARRIER_STOP, OUTPUT);

  pinMode(ESP_TO_MANLESS_IN_LS1, OUTPUT);
  pinMode(ESP_TO_MANLESS_IN_LS2, OUTPUT);
  pinMode(ESP_TO_MANLESS_IN_LOOP1, OUTPUT);
  pinMode(ESP_TO_MANLESS_IN_LOOP2, OUTPUT);
  
  pinMode(ESP_TO_MANLESS_OUT_LS1, OUTPUT);
  pinMode(ESP_TO_MANLESS_OUT_LS2, OUTPUT);
  pinMode(ESP_TO_MANLESS_OUT_LOOP1, OUTPUT);
  pinMode(ESP_TO_MANLESS_OUT_LOOP2, OUTPUT);

  /* Initialize all configured peripherals */
  Serial.begin(115200);
  timer = timerBegin(0, 80, true);       // Timer 0, prescaler 80 → 1 tick = 1 µs
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, TIMER_TIMEOUT_US, false);  // Non-reload (once)
}

/* Infinite loop */
void loop() {
  /* handling inputs */
  if (digitalRead(LOOP_TO_ESP_IN)) Serial.println("LOOP_TO_ESP_IN");
  if (digitalRead(LOOP_TO_ESP_LOOP2)) Serial.println("LOOP_TO_ESP_LOOP2");
  if (digitalRead(LOOP_TO_ESP_LOOP1_OUT)) Serial.println("LOOP_TO_ESP_LOOP1_OUT");
  if (digitalRead(BARRIER_TO_ESP_LS1)) Serial.println("BARRIER_TO_ESP_LS1");
  if (digitalRead(BARRIER_TO_ESP_LS2)) Serial.println("BARRIER_TO_ESP_LS2");
  if (digitalRead(MANLESS_IN_TO_ESP_IN_STOP)) Serial.println("MANLESS_IN_TO_ESP_IN_STOP");
  if (digitalRead(MANLESS_IN_TO_ESP_IN_DOWN)) Serial.println("MANLESS_IN_TO_ESP_IN_DOWN");
  if (digitalRead(MANLESS_IN_TO_ESP_UP)) Serial.println("MANLESS_IN_TO_ESP_UP");  
  if (digitalRead(MANLESS_OUT_TO_ESP_STOP)) Serial.println("MANLESS_OUT_TO_ESP_STOP");
  if (digitalRead(MANLESS_OUT_TO_ESP_DOWN)) Serial.println("MANLESS_OUT_TO_ESP_DOWN");
  if (digitalRead(MANLESS_OUT_TO_ESP_UP)) Serial.println("MANLESS_OUT_TO_ESP_UP");

  /* handling outputs */
  while (Serial.available() > 0) {
    str += (char)Serial.read();
    timerAlarmEnable(timer);
    resetTimer();
  }

  if (timerExpired) {
    // Serial.println(str);
    processCommand(str);
    delay(100);
    str = "";
    timerAlarmDisable(timer);
    resetTimer();
  }

}

/**
  * @brief On timer callback
  * @param None
  * @retval None
  */
void IRAM_ATTR onTimer() {
  timerExpired = true;
}

/**
  * @brief Reset timer
  * @param None
  * @retval None
  */
void resetTimer() {
  timerWrite(timer, 0);   // Reset hitungan timer ke 0
  timerExpired = false;   // Pastikan flag tidak aktif
}

/**
  * @brief Fungsi untuk parsing dan eksekusi perintah
  * @param String command
  * @retval None
  */
void processCommand(String command) {
  command.trim();  // hapus spasi/enter

  // Pisahkan berdasarkan koma
  int commaIndex = command.indexOf(',');
  if (commaIndex == -1) {
    Serial.println("Format salah! Gunakan format: PERINTAH,ANGKA");
    return;
  }

  String cmd = command.substring(0, commaIndex);
  String valStr = command.substring(commaIndex + 1);
  int val = valStr.toInt();

  // Eksekusi perintah
  if (cmd.equalsIgnoreCase("ESP_TO_BARRIER_UP")) {
    digitalWrite(ESP_TO_BARRIER_UP, val);
  } 
  else if (cmd.equalsIgnoreCase("ESP_TO_BARRIER_DOWN")) {
    digitalWrite(ESP_TO_BARRIER_DOWN, val);
  }
  else if (cmd.equalsIgnoreCase("ESP_TO_BARRIER_STOP")) {
    digitalWrite(ESP_TO_BARRIER_STOP, val);
  }
  else if (cmd.equalsIgnoreCase("ESP_TO_MANLESS_IN_LS1")) {
    digitalWrite(ESP_TO_MANLESS_IN_LS1, val);
  }
  else if (cmd.equalsIgnoreCase("ESP_TO_MANLESS_IN_LS2")) {
    digitalWrite(ESP_TO_MANLESS_IN_LS2, val);
  }
  else if (cmd.equalsIgnoreCase("ESP_TO_MANLESS_IN_LOOP1")) {
    digitalWrite(ESP_TO_MANLESS_IN_LOOP1, val);
  }
  else if (cmd.equalsIgnoreCase("ESP_TO_MANLESS_IN_LOOP2")) {
    digitalWrite(ESP_TO_MANLESS_IN_LOOP2, val);
  }
  else if (cmd.equalsIgnoreCase("ESP_TO_MANLESS_OUT_LS1")) {
    digitalWrite(ESP_TO_MANLESS_OUT_LS1, val);
  }
  else if (cmd.equalsIgnoreCase("ESP_TO_MANLESS_OUT_LS2")) {
    digitalWrite(ESP_TO_MANLESS_OUT_LS2, val);
  }
  else if (cmd.equalsIgnoreCase("ESP_TO_MANLESS_OUT_LOOP1")) {
    digitalWrite(ESP_TO_MANLESS_OUT_LOOP1, val);
  }
  else if (cmd.equalsIgnoreCase("ESP_TO_MANLESS_OUT_LOOP2")) {
    digitalWrite(ESP_TO_MANLESS_OUT_LOOP2, val);
  }
  else {
    Serial.println("Perintah tidak dikenal!");
  }
}