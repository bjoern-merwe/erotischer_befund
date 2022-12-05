#include <SPI.h>
#include <SdFat.h>
#include <vs1053_SdFat.h>
#include <SoftwareSerial.h>
#include <Adafruit_Thermal.h>

#include "Config.h"
#include "Strings.h"

SdFat sd;
vs1053 mp3player;
SoftwareSerial printerSerial(PIN_RX, PIN_TX);
Adafruit_Thermal printer(&printerSerial);

char stringBuffer[50];
boolean seedSet = false;

void setup() {
  Serial.begin(BAUD);
  printerSerial.begin(BAUD);

  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_RELAIS, OUTPUT);

  if (!sd.begin(SD_SEL, SPI_FULL_SPEED)) {
    sd.initErrorHalt();
  }
  if (!sd.chdir("/")) {
    sd.errorHalt("sd.chdir");
  }

  mp3player.begin();
  mp3player.setVolume(VOLUME, VOLUME);

  printer.begin(VERSION);
}

void loop() {
  setRelais(false);
  delay(1000);
  setLed(true);
  waitForButton();
  setSeed();
  setLed(false);
  setRelais(true);
  befund();
}

void setSeed() {
  if (!seedSet) {
    randomSeed(micros());
    seedSet = true;
  }
}

void setLed(boolean on) {
  if (on) {
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }
}

void setRelais(boolean on) {
  if (on) {
    digitalWrite(PIN_RELAIS, LOW);
  } else {
    digitalWrite(PIN_RELAIS, HIGH);
  }
}

void waitForButton() {
  while (digitalRead(PIN_BUTTON) == LOW) {
    // wait
  }
}

void playSound(char* fileName) {
  mp3player.available();
  mp3player.playMP3(fileName);
  while (mp3player.isPlaying() != 0) {
    // wait
  }
  delay(100);
}

void befund() {
  printer.wake();
  printer.flush();
  printer.feed(2);
  printer.setDefault();
  printer.setLineHeight(24);
  printer.setSize('M');
  printer.justify('C');
  printer.underlineOn();
  strcpy_P(stringBuffer, (char*)pgm_read_word(&t_headline1));
  printer.println(stringBuffer);
  printer.setSize('S');
  printer.underlineOff();
  strcpy_P(stringBuffer, (char*)pgm_read_word(&t_headline2));
  printer.println(stringBuffer);
  printer.justify('L');
  printer.boldOn();
  printer.underlineOn();
  strcpy_P(stringBuffer, (char*)pgm_read_word(&t_diagnose));
  printer.println(stringBuffer);
  printer.underlineOff();
  printer.boldOff();
  float ges = rateGes();
  float geb = rateGeb();
  float fig = rateFig();
  float sch = rateSch();
  float ars = rateArs();
  float zwi = rateZwi();
  float schnitt = (ges + geb + fig + sch + ars + zwi) / 6.0;
  printer.boldOn();
  rateGesamtnote(round(schnitt));
  printer.boldOff();
  strcpy_P(stringBuffer, (char*)pgm_read_word(&t_divider));
  printer.println(stringBuffer);
  kommentar();
  strcpy_P(stringBuffer, (char*)pgm_read_word(&t_divider));
  printer.println(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&t_disclaimer));
  printer.println(stringBuffer);
  printer.boldOn();
  strcpy_P(stringBuffer, (char*)pgm_read_word(&t_servedby));
  printer.println(stringBuffer);
  printer.boldOff();
  printer.feed(2);
  printer.flush();
  printer.sleep();
}

void kommentar() {
  int number = random(0, 32);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_kommentar[number])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_kommentar[number])));
  printer.println(stringBuffer);
}

int rateGes() {
  int rating = random(1, 11);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&s_kges));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_ges[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

int rateGeb() {
  int rating = random(1, 11);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&s_kgeb));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_geb[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

int rateFig() {
  int rating = random(1, 11);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&s_kfig));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_fig[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

int rateSch() {
  int rating = random(1, 11);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&s_ksch));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_sch[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

int rateArs() {
  int rating = random(1, 11);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&s_kars));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_ars[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

int rateZwi() {
  int rating = random(1, 11);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&s_kzwi));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_zwi[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

void rateGesamtnote(int rating) {
  if (rating < 1) {
    rating = 1;
  } else   if (rating > 10) {
    rating = 10;
  }
  strcpy_P(stringBuffer, (char*)pgm_read_word(&s_kgesamt));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
}
