

/*
 *
 * newbasic3x5
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : newbasic3x5.h
 * Date                : 23.04.2011
 * Font size in bytes  : 1830
 * Font width          : 10
 * Font height         : 6
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef NEWBASIC3X5_H
#define NEWBASIC3X5_H

#define NEWBASIC3X5_WIDTH 3
#define NEWBASIC3X5_HEIGHT 6

static uint8_t newbasic3x5[] PROGMEM = {
    0x0, 0x0, // size
    0x03, // width
    0x06, // height
    0x20, // first char
    0x60, // char count
    
    /* char widths
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    */
    // font data
    0x00, 0x00, 0x00, // 32
    0x00, 0x5C, 0x00, // 33
    0x0C, 0x00, 0x0C, // 34
    0x7C, 0x28, 0x7C, // 35
    0x28, 0x7C, 0x28, // 36
    0x24, 0x10, 0x48, // 37
    0x30, 0x5C, 0x6C, // 38
    0x00, 0x0C, 0x00, // 39
    0x38, 0x44, 0x00, // 40
    0x00, 0x44, 0x38, // 41
    0x08, 0x14, 0x08, // 42
    0x10, 0x38, 0x10, // 43
    0x00, 0x60, 0x00, // 44
    0x10, 0x10, 0x10, // 45
    0x00, 0x40, 0x00, // 46
    0x60, 0x10, 0x0C, // 47
    0x7C, 0x44, 0x7C, // 48
    0x48, 0x7C, 0x40, // 49
    0x74, 0x54, 0x5C, // 50
    0x44, 0x54, 0x7C, // 51
    0x1C, 0x10, 0x7C, // 52
    0x5C, 0x54, 0x74, // 53
    0x7C, 0x54, 0x74, // 54
    0x64, 0x14, 0x1C, // 55
    0x7C, 0x54, 0x7C, // 56
    0x5C, 0x54, 0x7C, // 57
    0x00, 0x28, 0x00, // 58
    0x00, 0x68, 0x00, // 59
    0x10, 0x28, 0x44, // 60
    0x28, 0x28, 0x28, // 61
    0x44, 0x28, 0x10, // 62
    0x04, 0x54, 0x1C, // 63
    0x38, 0x5C, 0x58, // 64
    0x78, 0x14, 0x78, // 65
    0x7C, 0x54, 0x28, // 66
    0x38, 0x44, 0x28, // 67
    0x7C, 0x44, 0x38, // 68
    0x7C, 0x54, 0x44, // 69
    0x7C, 0x14, 0x04, // 70
    0x38, 0x44, 0x74, // 71
    0x7C, 0x10, 0x7C, // 72
    0x44, 0x7C, 0x44, // 73
    0x20, 0x40, 0x3C, // 74
    0x7C, 0x10, 0x6C, // 75
    0x7C, 0x40, 0x40, // 76
    0x7C, 0x08, 0x7C, // 77
    0x7C, 0x18, 0x7C, // 78
    0x38, 0x44, 0x38, // 79
    0x7C, 0x14, 0x08, // 80
    0x38, 0x44, 0x78, // 81
    0x7C, 0x14, 0x68, // 82
    0x48, 0x54, 0x24, // 83
    0x04, 0x7C, 0x04, // 84
    0x7C, 0x40, 0x7C, // 85
    0x3C, 0x40, 0x3C, // 86
    0x7C, 0x30, 0x7C, // 87
    0x6C, 0x10, 0x6C, // 88
    0x0C, 0x70, 0x0C, // 89
    0x64, 0x54, 0x4C, // 90
    0x7C, 0x44, 0x00, // 91
    0x0C, 0x10, 0x60, // 92
    0x44, 0x7C, 0x00, // 93
    0x08, 0x04, 0x08, // 94
    0x80, 0x80, 0x80, // 95
    0x04, 0x00, 0x00, // 96
    0x70, 0x70, 0x70, // 97
    0x7C, 0x50, 0x70, // 98
    0x70, 0x50, 0x50, // 99
    0x70, 0x50, 0x7C, // 100
    0x30, 0x70, 0x10, // 101
    0x7C, 0x14, 0x00, // 102
    0x90, 0xF0, 0x40, // 103
    0x7C, 0x10, 0x70, // 104
    0x74, 0x00, 0x00, // 105
    0xE0, 0x00, 0x00, // 106
    0x7C, 0x30, 0x48, // 107
    0x7C, 0x00, 0x00, // 108
    0x70, 0x70, 0x70, // 109
    0x70, 0x10, 0x70, // 110
    0x70, 0x50, 0x70, // 111
    0x00, 0x00, 0x00, // 112
    0x00, 0x00, 0x00, // 113
    0x30, 0x00, 0x00, // 114
    0x50, 0x70, 0x00, // 115
    0x30, 0x50, 0x40, // 116
    0x70, 0x40, 0x70, // 117
    0x30, 0x70, 0x00, // 118
    0x30, 0x10, 0x30, // 119
    0x50, 0x70, 0x00, // 120
    0x00, 0x00, 0x00, // 121
    0x40, 0x70, 0x00, // 122
    0x10, 0x6C, 0x44, // 123
    0x00, 0x7C, 0x00, // 124
    0x44, 0x6C, 0x10, // 125
    0x10, 0x08, 0x10, // 126
    0x78, 0x48, 0x48 // 127
    
};

#endif
