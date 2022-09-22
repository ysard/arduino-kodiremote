/**
 * arduino-kodiremote is an USB Infrared Remote receiver for Kodi
 * using an Arduino Pro Micro (Leonardo).
 *
 * Copyright (C) 2019-2022 Ysard <ysard@users.noreply.github.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
// Remote definitions
#define R_INFO            0x2FD6897
#define R_MUTE            0x2FD08F7
#define R_ONE             0x2FD807F
#define R_TWO             0x2FD40BF
#define R_THREE           0x2FDC03F
#define R_FOUR            0x2FD20DF
#define R_FIVE            0x2FDA05F
#define R_SIX             0x2FD609F
#define R_SEVEN           0x2FDE01F
#define R_EIGHT           0x2FD10EF
#define R_NINE            0x2FD906F
#define R_ZERO            0x2FD00FF
//#define R_SOURCE          0x2FD28D7
#define R_AUDIO           0x2FD4AB5
//#define R_MENU            0x2FDDA25
#define R_SCREEN_SIZE     0x2FDA25D
#define R_LOOP            0x2FD02FD
#define R_OK              0x2FD50AF
#define R_CHANNEL_UP      0x2FDD827
#define R_CHANNEL_DOWN    0x2FDF807
//#define R_LIST            0x2FD18E7
#define R_SLEEP           0x2FDB04F
//#define R_EPG             0x2FD926D
//#define R_FAVORITES       0x2FD42BD
#define R_RED             0x2FD12ED
#define R_GREEN           0x2FDF20D
#define R_YELLOW          0x2FD0AF5
#define R_BLUE            0x2FDD22D
#define R_PLAY_PAUSE      0x2FDE817
#define R_STOP            0x2FDAA55
#define R_SUBTITLE        0x2FD2AD5
//#define R_RADIO           0x2FDCA35
//#define R_                0x2FDEA15 // ?
//#define R_DMP             0x2FDBA45 // ?
#define R_INDEX           0x2FD7A85
#define R_RECORD          0x2FD6A95
#define R_REPEAT          0x2FD02FD
#define R_EXIT            0x2FD22DD
#define R_UP              0x2FD9867
#define R_DOWN            0x2FDB847
#define R_LEFT            0x2FD629D
#define R_RIGHT           0x2FDE21D
#define R_VOL_UP          0x2FD58A7
#define R_VOL_DOWN        0x2FD7887

// Mappings Remote > Kodi
// Non repeatable keys
#define INFO              R_INFO
#define MUTE              R_MUTE
#define ONE               R_ONE
#define TWO               R_TWO
#define THREE             R_THREE
#define FOUR              R_FOUR
#define FIVE              R_FIVE
#define SIX               R_SIX
#define SEVEN             R_SEVEN
#define EIGHT             R_EIGHT
#define NINE              R_NINE
#define ZERO              R_ZERO
#define NEXT_LANGUAGE     R_AUDIO
#define ZOOM              R_SCREEN_SIZE
//#define LOOP              R_LOOP
#define SELECT            R_OK
#define SKIP_NEXT         R_CHANNEL_UP
#define SKIP_PREVIOUS     R_CHANNEL_DOWN
#define SLEEP             R_SLEEP
#define REWIND            R_RED
#define FAST_FORWARD      R_GREEN
#define JUMP_BACKWARD     R_YELLOW
#define JUMP_FORWARD      R_BLUE
#define PAUSE_PLAY        R_PLAY_PAUSE
#define STOP              R_STOP
#define NEXT_SUBTITLE     R_SUBTITLE
//#define MENU              R_MENU
#define MENU              R_INDEX
#define SCREENSHOT        R_RECORD

// Repeatable keys
#define BACK              R_REPEAT
#define EXIT              R_EXIT
#define UP                R_UP
#define DOWN              R_DOWN
#define LEFT              R_LEFT
#define RIGHT             R_RIGHT
#define VOL_UP            R_VOL_UP
#define VOL_DOWN          R_VOL_DOWN
