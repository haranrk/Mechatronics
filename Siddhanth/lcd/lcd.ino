#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 8, 12, 13);

void lcd_display(String text, int x=0, int y=0)
{
  lcd.clear();
  lcd.setCursor(x, y);
  lcd.print(text);
}

void setup() {
  lcd.begin(16,2);

}

void loop() {
  lcd_display("hello world");
  delay(1000);
  lcd_display("goodbye", 0, 1);
  delay(1000);
}
