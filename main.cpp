#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include <stdlib.h>

class I2CPreInit : public I2C
{
public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
        frequency(400000);
        start();
    };
};

I2CPreInit gI2C(p28,p27);
Adafruit_SSD1306_I2c oled(gI2C,p9);

void setRowColumn(int row, int col) {
    // Col is 5px wide, row is 8 px wide 
    oled.setTextCursor( (col * 5), (row * 8) ); 
}

void draw_radargrid() {
    
    // Display the radar grid
    oled.drawCircle(63, 127, 90, 1);
    oled.drawCircle(63, 127, 125, 1);
    
}

void draw_directionbox() {
    // This draws the direction box on the top right corner of display
    oled.drawRect(99,0,27,10,1);
    setRowColumn(0,19);
    oled.printf("%d N",134);    
}

void generate_obstacle() {
    // This function generates a random obstacle for the radar and displays it
    int obstacle_x, obstacle_y;
    
    obstacle_x = rand() % 127 + 20; // random number between 20 and 100;
    obstacle_y = rand() % 63 + 10; // random number between 20 and 100;
    
    oled.fillCircle(obstacle_x, obstacle_y, 4, 1);
    
}

void sweep() {
    // This function does the radar sweep operation and displays the output on screen
    int x = 0, y = 63;
    int xcenter = 63, ycenter = 63;
    
    while(y>=0) {
        oled.clearDisplay();
        draw_radargrid();
        if (y%15 == 0) // randomly generate obstacle to display
            generate_obstacle();
        draw_directionbox();
        oled.drawLine(xcenter,ycenter,x,y,1);
        y--;
        oled.display();
    }
    
    y = 0; x = 1;
    while(x<=127) {
        oled.clearDisplay();
        draw_radargrid();
        if(x%15 == 0) // randomly generate obstacle to display
            generate_obstacle();
        draw_directionbox();
        oled.drawLine(xcenter,ycenter,x,y,1);
        x++;
        oled.display();
    }
    x = 127; y = 1;
    while(y<63) {
        oled.clearDisplay();
        draw_radargrid();
        if(y%15 == 0) // randomly generate obstacle to display
            generate_obstacle();
        draw_directionbox();
        oled.drawLine(xcenter,ycenter,x,y,1);
        y++;
        oled.display();
    }
}

int main() {
    // Continuously sweep the radar screen
    while(1) {
        sweep();
    }    
}