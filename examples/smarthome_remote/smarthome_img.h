/*
 * ssd1306_img.h
 *
 *  Created on: Apr 24, 2018
 *      Author: kyle
 */

#ifndef __EXAMPLES_SSD1306_SEG_SSD1306_IMG_H
#define __EXAMPLES_SSD1306_SEG_SSD1306_IMG_H 1

static const unsigned char hkust_logo[]={
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xE0,0xF0,0xFC,0xFE,
    0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,
    0xFC,0xFC,0xF0,0xE0,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x80,0x80,0x80,0x80,
    0x80,0x80,0x83,0x83,0x83,0x83,
    0x83,0x83,0x03,0x03,0x83,0x83,
    0x83,0x83,0x83,0x81,0x80,0x80,
    0x80,0x80,0x80,0x80,0x00,0x00,
    0x02,0xFB,0xFB,0xFB,0x03,0xFB,
    0xFB,0x03,0x03,0x03,0x03,0x07,
    0xEF,0xEF,0x0F,0x0F,0xEF,0xEF,
    0x07,0x03,0x03,0x03,0x03,0xFB,
    0xFB,0x03,0xFB,0xFB,0xFB,0x00,
    0x00,0xFF,0xFF,0xFF,0x00,0xFF,
    0xFF,0x00,0x00,0x00,0x00,0x00,
    0xFF,0xFF,0x00,0x00,0xFF,0xFF,
    0x00,0x00,0x00,0x00,0x00,0xFF,
    0xFF,0x00,0xFF,0xFF,0xFF,0x00,
    0x00,0x1F,0x7F,0xFF,0xC0,0x1F,
    0x3F,0xF0,0xE0,0xC0,0x00,0x80,
    0xFF,0x7F,0x00,0x00,0x7F,0xFF,
    0x80,0x00,0xC0,0xE0,0x78,0x3F,
    0x8F,0xE0,0xFF,0x7F,0x0F,0x00,
    0x00,0x00,0x00,0x01,0x03,0x07,
    0x0E,0x44,0x71,0x78,0x7E,0x77,
    0x71,0x70,0x70,0x70,0x70,0x71,
    0x77,0x7E,0x78,0x71,0x44,0x0E,
    0x07,0x03,0x01,0x00,0x00,0x00,//hkust_small.bmp0,30x48
};

static const unsigned char light_off[]={
    0x00,0x00,0x00,0xC0,0x60,0x30,
    0x18,0x08,0x0C,0x04,0x06,0x06,
    0x02,0x02,0x02,0x02,0x02,0x06,
    0x06,0x04,0x0C,0x08,0x18,0x30,
    0x60,0xC0,0x00,0x00,0x00,0x00,
    0xFC,0x07,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x80,0xC0,0xE0,
    0xC0,0xC0,0xE0,0xE0,0x80,0xC0,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x01,0x07,0xFC,0x00,0x00,0x0F,
    0x38,0xE0,0x80,0x00,0x00,0x00,
    0x00,0x00,0xFF,0xF1,0x03,0x03,
    0x02,0x03,0x01,0xF1,0xFF,0x00,
    0x00,0x00,0x00,0x00,0x80,0xE0,
    0x38,0x0F,0x00,0x00,0x00,0x00,
    0x00,0x03,0x0E,0xF8,0x80,0x00,
    0x00,0x00,0xFF,0xC0,0x00,0x00,
    0x00,0xE0,0xFF,0x00,0x00,0x00,
    0x80,0xF8,0x0E,0x03,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xFF,0xFF,0x5A,0x5A,
    0x5A,0x5B,0x5B,0x5A,0x5A,0x5A,
    0x5B,0x5B,0x5A,0x5A,0x4A,0xFF,
    0xFF,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x07,0x0F,0x1B,0x13,0x13,
    0x13,0x33,0x73,0x53,0x73,0x33,
    0x13,0x13,0x13,0x1B,0x0F,0x07,
    0x00,0x00,0x00,0x00,0x00,0x00,//light_bulb.bmp, 29x48
};

static const unsigned char light_on[]={
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x40,0xC0,0x00,0x00,0x00,0x00,
    0x00,0x1C,0x70,0x00,0x00,0x00,
    0x00,0x00,0x3E,0x00,0x00,0x00,
    0x00,0x00,0x70,0x1C,0x00,0x00,
    0x00,0x00,0x80,0xC0,0x40,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x20,0x20,0x60,0x40,0x40,
    0x00,0x01,0x02,0x80,0xC0,0x20,
    0x10,0x08,0x0C,0x04,0x04,0x06,
    0x06,0x06,0x06,0x06,0x04,0x04,
    0x0C,0x18,0x10,0x60,0xC0,0x80,
    0x02,0x01,0x00,0x40,0x40,0x60,
    0x20,0x20,0x00,0x00,0x00,0x10,
    0x10,0x10,0x10,0x10,0x00,0x00,
    0x00,0xFC,0x87,0x00,0x00,0x00,
    0x00,0x00,0x20,0xF0,0x70,0x70,
    0x70,0x78,0x70,0xF0,0x10,0x00,
    0x00,0x00,0x00,0x00,0xC7,0xFC,
    0x00,0x00,0x00,0x10,0x10,0x10,
    0x10,0x10,0x00,0x00,0x00,0x10,
    0x18,0x08,0x0C,0x04,0x00,0x00,
    0x80,0x83,0x0C,0x30,0xE0,0x00,
    0x00,0x00,0xFF,0xE0,0x00,0x00,
    0x00,0xF0,0x7F,0x00,0x00,0x00,
    0xE0,0x38,0x0E,0x83,0x80,0x00,
    0x00,0x04,0x0C,0x08,0x18,0x10,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x04,0x06,0x03,0x01,
    0x00,0x00,0x00,0x01,0xFF,0x58,
    0x58,0x58,0x5F,0x58,0x58,0x58,
    0x5F,0x58,0x58,0x58,0xFF,0x01,
    0x00,0x00,0x00,0x01,0x03,0x06,
    0x04,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x1F,0x35,0x35,
    0x35,0x35,0x75,0x75,0x75,0x35,
    0x35,0x35,0x35,0x1F,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,//light_bulb_on.bmp0, 41x48
};

static const unsigned char rfid[]={
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x80,
    0x40,0x40,0x20,0x20,0x10,0x10,
    0x08,0x08,0x08,0x04,0x04,0x04,
    0x04,0x02,0x02,0x02,0x02,0x02,
    0x02,0x02,0x02,0x02,0x02,0x02,
    0x02,0x02,0x02,0x02,0x02,0x02,
    0x04,0x04,0x04,0x04,0x04,0x08,
    0x08,0x10,0x10,0x10,0x20,0x20,
    0x40,0x80,0x80,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x80,
    0x40,0x30,0x08,0x04,0x02,0x03,
    0x01,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x80,0x80,
    0x00,0x00,0x00,0x60,0xF0,0xF0,
    0xC0,0x00,0x00,0x0C,0x1E,0xFE,
    0xF8,0xE0,0x00,0x00,0x00,0x00,
    0x00,0x00,0x80,0x40,0x20,0x40,
    0x40,0x40,0x40,0x40,0x80,0x81,
    0x82,0x84,0x08,0x10,0x20,0xC0,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0xF8,
    0x06,0x01,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x3C,0xFC,0xF8,0xE0,0x00,0x03,
    0x07,0xFF,0xFE,0xF8,0x00,0x00,
    0x00,0x07,0xFF,0xFF,0xF8,0x00,
    0x00,0x00,0x0F,0xFF,0xFF,0xF0,
    0x00,0x00,0x00,0xE0,0x1F,0x00,
    0x00,0x78,0xCC,0x84,0x04,0x08,
    0x08,0x10,0x10,0x3C,0x67,0x44,
    0x84,0x85,0x07,0x04,0x04,0x08,
    0x18,0x30,0x40,0x80,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0F,0x70,0x80,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x78,0x7F,0x3F,0x0F,
    0x00,0x80,0xC0,0xFE,0xFF,0x3F,
    0x00,0x00,0x00,0xC0,0xFF,0xFF,
    0x3F,0x00,0x00,0x00,0xE0,0xFF,
    0xFF,0x0F,0x00,0x00,0x00,0x00,
    0x01,0x01,0x01,0x00,0x02,0x03,
    0x3F,0x26,0xC4,0x88,0x98,0x30,
    0x20,0x40,0x80,0x00,0x01,0x01,
    0x02,0x00,0x00,0x00,0x00,0x01,
    0x02,0x0C,0x10,0x60,0x80,0x00,
    0x00,0x00,0x00,0x00,0x00,0x01,
    0x06,0x08,0x10,0x20,0x40,0x80,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0x03,0x03,
    0x00,0x00,0x00,0x08,0x1E,0x1F,
    0x07,0x01,0x00,0x40,0xF0,0xFE,
    0x3F,0x0F,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x03,0x04,0x84,
    0x48,0x09,0x10,0x10,0x11,0x03,
    0x0C,0x30,0x40,0x40,0x80,0x80,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x02,0x0C,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x01,0x01,0x02,0x02,
    0x06,0x04,0x08,0x08,0x10,0x10,
    0x10,0x20,0x20,0x20,0x20,0x40,
    0x40,0x40,0x40,0x40,0x40,0x40,
    0x40,0x40,0x40,0x40,0x40,0x40,
    0x40,0x40,0x40,0x40,0x40,0x20,
    0x20,0x20,0x10,0x10,0x10,0x08,
    0x08,0x08,0x04,0x04,0x02,0x01,
    0x01,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,//rfid.bmp,80x48
};

#endif /* __EXAMPLES_SSD1306_SEG_SSD1306_IMG_H */