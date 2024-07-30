#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "define.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  lcd.setCursor(0, 0);
  lcd.print("WELCOME!");
  lcd.setCursor(4, 1);
  lcd.print("TO ARM ROBOT");
  delay(2000);
  lcd.clear();
  updateMenu(); // Tampilkan menu awal
}

void loop() {
  // Cek input dari tombol untuk navigasi menu
  if (digitalRead(downButton)) {
    delay(100); // Debounce
    while (digitalRead(downButton)); // Tunggu sampai tombol dilepas
    if (inSubmenu) {
      submenu++; // Pindah ke item submenu berikutnya
    } else {
      menu++; // Pindah ke item menu berikutnya
    }
    updateMenu();
  }
  if (digitalRead(upButton)) {
    delay(100); // Debounce
    while (digitalRead(upButton)); // Tunggu sampai tombol dilepas
    if (inSubmenu) {
      submenu--; // Pindah ke item submenu sebelumnya
    } else {
      menu--; // Pindah ke item menu sebelumnya
    }
    updateMenu();
  }
  if (digitalRead(selectButton)) {
    delay(100); // Debounce
    while (digitalRead(selectButton)); // Tunggu sampai tombol dilepas
    if (inSubmenu) {
      executeSubmenuAction(); // Eksekusi aksi submenu
      updateMenu();
    } else {
      enterSubmenu(); // Masuk ke submenu
    }
  }
}

void updateMenu() {
  if (inSubmenu) {
    // Cek batas submenu
    if (submenu < 1) submenu = 4;
    if (submenu > 4) submenu = 1;
    
    // Tampilkan submenu
    lcd.clear();
    switch (menu) {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print("Submenu 1.");
        lcd.print(submenu);
        break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print("Submenu 2.");
        lcd.print(submenu);
        break;
      case 3:
        lcd.setCursor(0, 0);
        lcd.print("Submenu 3.");
        lcd.print(submenu);
        break;
      case 4:
        lcd.setCursor(0, 0);
        lcd.print("Submenu 4.");
        lcd.print(submenu);
        break;
    }
    lcd.setCursor(0, 1);
    lcd.print(">Option ");
    lcd.print(submenu);
  } else {
    // Cek batas menu
    if (menu < 1) menu = 4;
    if (menu > 4) menu = 1;

    // Tampilkan menu utama
    lcd.clear();
    switch (menu) {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print(">MenuAuto");
        lcd.setCursor(0, 1);
        lcd.print(" MenuManual");
        break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print(" MenuAuto");
        lcd.setCursor(0, 1);
        lcd.print(">MenuManual");
        break;
      case 3:
        lcd.setCursor(0, 0);
        lcd.print(">CekServo");
        lcd.setCursor(0, 1);
        lcd.print(" Android");
        break;
      case 4:
        lcd.setCursor(0, 0);
        lcd.print(" CekServo");
        lcd.setCursor(0, 1);
        lcd.print(">Android");
        break;
    }
  }
}

void enterSubmenu() {
  inSubmenu = true; // Menandakan bahwa kita sekarang berada di submenu
  submenu = 1; // Mulai dari submenu pertama
  updateMenu();
}

void executeSubmenuAction() {
  // Eksekusi aksi sesuai submenu
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Executing:");
  lcd.setCursor(0, 1);
  lcd.print("Submenu ");
  lcd.print(menu);
  lcd.print(".");
  lcd.print(submenu);
  delay(1500); // Simulasi eksekusi aksi
  inSubmenu = false; // Kembali ke menu utama setelah eksekusi
}

void executeAction() {
  // Eksekusi aksi utama (jika diperlukan)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Executing #");
  lcd.print(menu);
  delay(1500);
}
