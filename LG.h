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
#define R_INFO            0x20DF55AA
#define R_MUTE            0x20DF906F
#define R_ONE             0x20DF8877
#define R_TWO             0x20DF48B7
#define R_THREE           0x20DFC837
#define R_FOUR            0x20DF28D7
#define R_FIVE            0x20DFA857
#define R_SIX             0x20DF6897
#define R_SEVEN           0x20DFE817
#define R_EIGHT           0x20DF18E7
#define R_NINE            0x20DF9867
#define R_ZERO            0x20DF08F7
//#define R_SOURCE          0x20DFD02F
#define R_AUDIO           0x20DF8976
//#define R_MENU            0x20DFA25D
#define R_SCREEN_SIZE     0x20DF9E61
//#define R_LOOP
#define R_OK              0x20DF22DD
#define R_CHANNEL_UP      0x20DF00FF
#define R_CHANNEL_DOWN    0x20DF807F
//#define R_LIST            0x20DFCA35
#define R_SLEEP           0x20DF10EF
//#define R_FAVORITES       0x20DF7887
//#define R_GUIDE           0x20DFD52A
//#define R_TEXT            0x20DF04FB
//#define R_TOPT            0x20DF847B
//#define R_SETTINGS        0x20DFC23D
//#define R_AVMODE          0x20DF0CF3
#define R_REWIND          0x20DFF10E
#define R_FORWARD         0x20DF718E
#define R_RED             0x20DF4EB1
#define R_GREEN           0x20DF8E71
#define R_YELLOW          0x20DFC639
#define R_BLUE            0x20DF8679
#define R_PLAY_PAUSE      0x20DF0DF2
#define R_STOP            0x20DF8D72
#define R_SUBTITLE        0x20DF9C63
//#define R_RADIO           0x20DF0FF0
#define R_RECORD          0x20DFBD42
#define R_BACK            0x20DF14EB
//#define R_REPEAT
#define R_EXIT            0x20DFDA25
#define R_UP              0x20DF02FD
#define R_DOWN            0x20DF827D
#define R_LEFT            0x20DFE01F
#define R_RIGHT           0x20DF609F
#define R_VOL_UP          0x20DF40BF
#define R_VOL_DOWN        0x20DFC03F

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
#define SELECT            R_OK
#define SKIP_NEXT         R_CHANNEL_UP
#define SKIP_PREVIOUS     R_CHANNEL_DOWN
#define SLEEP             R_SLEEP
#define REWIND            R_REWIND
#define FAST_FORWARD      R_FORWARD
#define JUMP_BACKWARD     R_YELLOW
#define JUMP_FORWARD      R_BLUE
#define PAUSE_PLAY        R_PLAY_PAUSE
#define STOP              R_STOP
#define NEXT_SUBTITLE     R_SUBTITLE
//#define RADIO             R_RADIO
//#define MENU              R_MENU
#define MENU              R_RED
#define SCREENSHOT        R_RECORD

// Repeatable keys
#define BACK              R_BACK
#define EXIT              R_EXIT
#define UP                R_UP
#define DOWN              R_DOWN
#define LEFT              R_LEFT
#define RIGHT             R_RIGHT
#define VOL_UP            R_VOL_UP
#define VOL_DOWN          R_VOL_DOWN
