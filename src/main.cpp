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
boolean strCompleted;

/* Private function prototypes -----------------------------------------------*/
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

  pinMode(MANLESS_IN_TO_ESP_STOP, INPUT);
  pinMode(MANLESS_IN_TO_ESP_DOWN, INPUT);
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
}

/* Infinite loop */
void loop() {
  /* handling inputs */
  Serial.printf("LOOP_TO_ESP_IN         : %d\r\n",  digitalRead(LOOP_TO_ESP_IN));
  Serial.printf("LOOP_TO_ESP_LOOP2      : %d\r\n",  digitalRead(LOOP_TO_ESP_LOOP2));
  Serial.printf("LOOP_TO_ESP_LOOP1_OUT  : %d\r\n",  digitalRead(LOOP_TO_ESP_LOOP1_OUT));
  Serial.printf("BARRIER_TO_ESP_LS1     : %d\r\n",  digitalRead(BARRIER_TO_ESP_LS1));
  Serial.printf("BARRIER_TO_ESP_LS2     : %d\r\n",  digitalRead(BARRIER_TO_ESP_LS2));
  Serial.printf("MANLESS_IN_TO_ESP_STOP : %d\r\n",  digitalRead(MANLESS_IN_TO_ESP_STOP));
  Serial.printf("MANLESS_IN_TO_ESP_DOWN : %d\r\n",  digitalRead(MANLESS_IN_TO_ESP_DOWN));
  Serial.printf("MANLESS_IN_TO_ESP_UP   : %d\r\n",  digitalRead(MANLESS_IN_TO_ESP_UP));
  Serial.printf("MANLESS_OUT_TO_ESP_STOP: %d\r\n",  digitalRead(MANLESS_OUT_TO_ESP_STOP));
  Serial.printf("MANLESS_OUT_TO_ESP_DOWN: %d\r\n",  digitalRead(MANLESS_OUT_TO_ESP_DOWN));
  Serial.printf("MANLESS_OUT_TO_ESP_UP  : %d\r\n",  digitalRead(MANLESS_OUT_TO_ESP_UP));
  Serial.println();

  /* handling outputs */
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\n') {
      strCompleted = true;
    } else {
      str += c;
    }
  }

  if (strCompleted) {
    processCommand(str);
    str = "";
  }

  delay(1000);
}


/**
  * @brief Fungsi untuk parsing dan eksekusi perintah
  * @param String command
  * @retval None
  */
void processCommand(String command) {
  command.trim();  // hapus spasi/enter

  // Eksekusi perintah
  if (command.equalsIgnoreCase("ESP_TO_BARRIER_UP")) {
    digitalWrite(ESP_TO_BARRIER_UP, !digitalRead(ESP_TO_BARRIER_UP));
  } 
  else if (command.equalsIgnoreCase("ESP_TO_BARRIER_DOWN")) {
    digitalWrite(ESP_TO_BARRIER_DOWN, !digitalRead(ESP_TO_BARRIER_DOWN));
  }
  else if (command.equalsIgnoreCase("ESP_TO_BARRIER_STOP")) {
    digitalWrite(ESP_TO_BARRIER_STOP, !digitalRead(ESP_TO_BARRIER_STOP));
  }
  else if (command.equalsIgnoreCase("ESP_TO_MANLESS_IN_LS1")) {
    digitalWrite(ESP_TO_MANLESS_IN_LS1, !digitalRead(ESP_TO_MANLESS_IN_LS1));
  }
  else if (command.equalsIgnoreCase("ESP_TO_MANLESS_IN_LS2")) {
    digitalWrite(ESP_TO_MANLESS_IN_LS2, !digitalRead(ESP_TO_MANLESS_IN_LS2));
  }
  else if (command.equalsIgnoreCase("ESP_TO_MANLESS_IN_LOOP1")) {
    digitalWrite(ESP_TO_MANLESS_IN_LOOP1, !digitalRead(ESP_TO_MANLESS_IN_LOOP1));
  }
  else if (command.equalsIgnoreCase("ESP_TO_MANLESS_IN_LOOP2")) {
    digitalWrite(ESP_TO_MANLESS_IN_LOOP2, !digitalRead(ESP_TO_MANLESS_IN_LOOP2));
  }
  else if (command.equalsIgnoreCase("ESP_TO_MANLESS_OUT_LS1")) {
    digitalWrite(ESP_TO_MANLESS_OUT_LS1, !digitalRead(ESP_TO_MANLESS_OUT_LS1));
  }
  else if (command.equalsIgnoreCase("ESP_TO_MANLESS_OUT_LS2")) {
    digitalWrite(ESP_TO_MANLESS_OUT_LS2, !digitalRead(ESP_TO_MANLESS_OUT_LS2));
  }
  else if (command.equalsIgnoreCase("ESP_TO_MANLESS_OUT_LOOP1")) {
    digitalWrite(ESP_TO_MANLESS_OUT_LOOP1, !digitalRead(ESP_TO_MANLESS_OUT_LOOP1));
  }
  else if (command.equalsIgnoreCase("ESP_TO_MANLESS_OUT_LOOP2")) {
    digitalWrite(ESP_TO_MANLESS_OUT_LOOP2, !digitalRead(ESP_TO_MANLESS_OUT_LOOP2));
  }
  else {
    Serial.println("Perintah tidak dikenal!");
  }
}