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
  printer.println("Erotischer Befund");
  printer.setSize('S');
  printer.underlineOff();
  printer.println("Zentrum fuer Hurologie\nJohanna Bank & Bjoern Merwe");
  printer.justify('L');
  printer.boldOn();
  printer.underlineOn();
  printer.println("Diagnose");
  printer.underlineOff();
  printer.boldOff();
  float gesicht = rateGesicht();
  float gebiss = rateGebiss();
  float figur = rateFigur();
  float schritt = rateSchritt();
  float arsch = rateArsch();
  float zwischenmenschlich = rateZwischenmenschlich();
  float schnitt = (gesicht + gebiss + figur + schritt + arsch + zwischenmenschlich) / 6.0;
  printer.boldOn();
  rateGesamtnote(round(schnitt));
  printer.boldOff();
  printer.println("------------------------------");
  kommentar();
  printer.println("------------------------------");
  printer.println("Vertrauliches Dokument, bitte\naufbewahren. Es bediente Sie");
  printer.boldOn();
  printer.println("Johanna Bank");
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

int rateGesicht() {
  int rating = random(1, 11);
  playSound("kategorie/gesicht.mp3");
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_ges[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

int rateGebiss() {
  int rating = random(1, 11);
  playSound("kategorie/gebiss.mp3");
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_geb[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

int rateFigur() {
  int rating = random(1, 11);
  playSound("kategorie/figur.mp3");
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_fig[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

int rateSchritt() {
  int rating = random(1, 11);
  playSound("kategorie/schritt.mp3");
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_sch[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

int rateArsch() {
  int rating = random(1, 11);
  playSound("kategorie/arsch.mp3");
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating_ars[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
  return rating;
}

int rateZwischenmenschlich() {
  int rating = random(1, 11);
  playSound("kategorie/zwischenmenschlich.mp3");
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
  playSound("kategorie/gesamtnote.mp3");
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(sound_rating[rating - 1])));
  playSound(stringBuffer);
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(text_rating[rating - 1])));
  printer.println(stringBuffer);
  delay(500);
}
