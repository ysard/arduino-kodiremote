// An Infrared Remote receiver that emulates a USB keyboard,
// to be used as a remote receiver for Kodi Open Source Home Theater Software

// Original work: By Andre Miller - www.andremiller.net - 2016-11-16
// Updated: By Ysard - 2019-2021

// For Arduino Pro Micro
// Requirements:
// - IRRemote v2.x
//  See this link to upgrade from 2.x
//  https://github.com/Arduino-IRremote/Arduino-IRremote#converting-your-program-to-the-31-version
//
//  See the custom lightened IRremote.h:
//  - The sending functions of all protocols are deactivated to keep only the receiving ones
//  - Only the NEC protocol is enabled
// - KeyboardAzertyFr v1.0.1
// Hardware connections:
//     IR Receiver on Pins GND, VCC and A2

// Hint: Test keyboard events on GNU/Linux:
// xev -event keyboard

/// User configuration ////////////////////////////////////////////////////////

// Uncomment this line to run in test mode.
// In test mode the hex codes of buttons pressed on your remote will be printed to the serial console
// #define TESTMODE

// Configure targeted keyboard layout
#define FR_LAYOUT

// Choose remote brand
//#include "LG.h"
#include "Grandin.h"

/*
 * Specify which protocol(s) should be used for decoding.
 * If no protocol is defined, all protocols are active.
 */
#define DECODE_NEC
#define INT_SIZE    32
#include <IRremote.hpp>

/// Internal configuration ////////////////////////////////////////////////////
#ifdef FR_LAYOUT
    #include "KeyboardAzertyFr.h"
    #define Keyboard    KeyboardAzertyFr
#else
    #include "Keyboard.h"
#endif

// IR receiver pin
#define RECV_PIN    A2
// The RX LED has a defined Arduino pin
#define RXLED       17
// Avoid considering as a repetition, successive presses that are not fast enough
// so that the 0xFFFFF release code is not sent by the remote control
// (which is the case when presses are very fast).
// We compute the time elapsed since the key press, and refuse any 0xFFFFF
// code until MIN_MS_BETWEEN_2_PRESS ms.
#define MIN_MS_BETWEEN_2_PRESS  750
// Avoid considering as a repetition, a 0xFFFFF code sent for too long since a previous repetition.
// In this case it means that the press code has just been missed.
// Normal mode: 300ms minimum between repetititions
// Debug mode: ~107ms minimum between repetititions
// We compute elapsed time between 2 repetititions, and refuse any 0xFFFFF
// code if it is greater than MAX_MS_BETWEEN_2_REPS;
// (~2.3 times 107ms => allow 1 missing rep in a serie but still lesser than elapsed
// time between 2 quick manual presses on 2 different buttons)
#define MAX_MS_BETWEEN_2_REPS   300

///////////////////////////////////////////////////////////////////////////////
unsigned long lastPressTime = 0;
unsigned long previousCode;
unsigned long repetitionTime = 0;
bool          isPreviousRepeatable = false;


void setup()
{
    // Init & Start the receiver
    IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);

    pinMode(RXLED, OUTPUT); // Set RX LED as an output

    #ifdef TESTMODE
    // In test, start the serial and wait for serial console to connect
    Serial.begin(9600); // Status message will be sent to PC at 9600 bauds
    while (!Serial) {   // Wait for serial to be connected. Required on Leonardo with integrated USB
    }
    Serial.println("Begin test mode");

    //  Keyboard.println("abcdefghijklmnopqrstuvwxyz1234567890-=");
    //  Keyboard.println("~[]\\;'`,./");
    //  Keyboard.println("&é\"(è_çà)^^$*ù²:!<>°");
    //  Keyboard.println("+¨£µ%");
    //  Keyboard.println("§~#");
    //  Keyboard.println("{[|\\@]}¤");
    #endif

    // Flash RX LED
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(RXLED, LOW);  // ON
        delay(500);
        digitalWrite(RXLED, HIGH); // OFF
    }
}


void loop()
{
    if (!IrReceiver.decode()) { // Grab an IR code
        return;
    }

    #ifdef TESTMODE
    // In test mode, print the HEX code on the serial monitor
    Serial.print(results.decode_type, HEX);
    Serial.print(" - ");
    Serial.println(results.value, HEX);
    #endif

    // Press a key on the simulated keyboard
    // Change the decode type to your remote type (see test mode)
    // 0x03: NEC
    if (IrReceiver.decodedIRData.protocol == NEC) {
          // Detect repetitions (IrReceiver.decodedIRData.decodedRawData == 0)
          // See https://github.com/Arduino-IRremote/Arduino-IRremote/blob/a63162a0e0c5f6bf77b1b65cac1554e3f70fe7f8/src/IRReceive.hpp#L1014
          if (IrReceiver.decodedIRData.flags & (IRDATA_FLAGS_IS_AUTO_REPEAT | IRDATA_FLAGS_IS_REPEAT)) {
              // Potential repetition code ?
              if (!isPreviousRepeatable) {
                  goto end;
              }

              uint32_t gap = (uint32_t) IrReceiver.decodedIRData.rawDataPtr->rawbuf[0] * MICROS_PER_TICK;

              if (gap > 300000) { // MAX_MS_BETWEEN_2_REPS * 1000
                  // Elapsed time between 2 repetititions too long
                  // Avoid repetitions received with missed primary code.
                  // Disable this serie of repetitions by ignoring the next 0xFFFFF codes
                  isPreviousRepeatable = false;

                  #ifdef TESTMODE
                  Serial.println("bad rep, missing press");
                  #endif
              } else if (gap > 80000) {
                  // Elapsed time since the key press is acceptable
                  // Avoid repetitions that are emitted to soon
                  // Note: If not using timer since the first press, think about the fact that the first gap is ~39ms, then the next gaps are ~95ms.
                  // Alternative condition: currentTime - lastPressTime > MIN_MS_BETWEEN_2_PRESS
                  // TL;DR: The timer allows to wait more than 95ms since the first press.
                  sendKeystrokes(previousCode);
              }

            // TODO: delete millis calls everywhere ?
            // Repeat previous key press
            unsigned long currentTime = millis();

            #ifdef TESTMODE
            // Elapsed since the key press
            Serial.print(currentTime);
            Serial.print(" - ");
            Serial.print(lastPressTime);
            Serial.print(" = ");
            Serial.println(currentTime - lastPressTime);
            // Elapsed time between 2 repetititions
            Serial.println(currentTime - repetitionTime);
            #endif

            // Set new repetition time for the next one
            repetitionTime = currentTime;
        } else {
            // Simple key press
            sendKeystrokes(IrReceiver.decodedIRData.decodedRawData);
            // Keep the code for potential following repetitions
            previousCode = IrReceiver.decodedIRData.decodedRawData;
            // Store the timestamp of this accepted code
            lastPressTime  = millis();
            repetitionTime = lastPressTime;
        }
    }

end:
    // Ready to receive the next value
    IrReceiver.resume();
}

uint32_t reverseBits(uint32_t n)
{
    int8_t pos = INT_SIZE - 1;     // maintient le décalage

    // Store reversed bits of the given value `n`. All bits are initialized to 0.
    uint32_t reverse = 0;

    // Until all bits are processed
    while (pos >= 0 && n)
    {
        // If the current bit is 1, put this bit in the result at the correct position
        if (n & 1) {
            reverse = reverse | (1ul << pos);
        }

        n >>= 1;                // Delete the current bit (right shift of 1/divide by 2)
        pos--;                  // Update pos to the next one
    }
    return reverse;
}

void sendKeystrokes(unsigned long &irCode)
{
    uint32_t reverseIrCode = reverseBits(irCode);
    // Change the values to match your remote (see test mode)
    #ifdef TESTMODE
    Serial.print("sendKeystrokes: ");
    Serial.print(irCode, HEX);
    Serial.print(" - Reverse code: ");
    Serial.println(reverseIrCode, HEX);
    #endif

    // Non repeatable keys
    switch (reverseIrCode) {
      //case 0x2FD48B7 : Keyboard.write(); break; // poweroff
      case INFO : Keyboard.write('i'); break; // info > info
      case MUTE : Keyboard.write(KEY_F8); break; // mute > mute
      case ONE : Keyboard.write('1'); break; // 1
      case TWO : Keyboard.write('2'); break; // 2
      case THREE : Keyboard.write('3'); break; // 3
      case FOUR : Keyboard.write('4'); break; // 4
      case FIVE : Keyboard.write('5'); break; // 5
      case SIX : Keyboard.write('6'); break; // 6
      case SEVEN : Keyboard.write('7'); break; // 7
      case EIGHT : Keyboard.write('8'); break; // 8
      case NINE : Keyboard.write('9'); break; // 9
      case ZERO : Keyboard.write('0'); break; // 0
      //case SOURCE : Keyboard.write(); break; // source
      case NEXT_LANGUAGE : Keyboard.press(KEY_LEFT_CTRL); // audio > AudioNextLanguage
        Keyboard.press('a');
        Keyboard.releaseAll();
        break;
      //case MENU : Keyboard.write('c'); break; // menu
      case ZOOM : Keyboard.write('z'); break; // screen size > Zoom/aspect ratio
      //case LOOP : Keyboard.write(); break; // loop

      case SELECT : Keyboard.write(KEY_RETURN); break; // enter > select

      case SKIP_NEXT : Keyboard.write(KEY_PAGE_UP); break; // ch + > page up (skip to next)
      case SKIP_PREVIOUS : Keyboard.write(KEY_PAGE_DOWN); break; // ch - > page down (skip to previous)
      //case LIST : Keyboard.write(); break; // list
      case SLEEP : Keyboard.write('s'); break; // sleep
      //case EPG : Keyboard.write(); break; // EPG
      //case FAVORITES : Keyboard.write(); break; // favorites
      case REWIND : Keyboard.write('r'); break; // red (rewind) > rewind
      case FAST_FORWARD : Keyboard.write('f'); break; // green (fast forward) > fast forward
      case JUMP_BACKWARD : Keyboard.write('\''); break; // yellow (previous) > small seek step backwards 7 seconds //ù
      case JUMP_FORWARD : Keyboard.write('1'); // blue (next) > jump forward 10 seconds.
        Keyboard.write('0');
        Keyboard.write(KEY_RIGHT_ARROW);
        break;
      case PAUSE_PLAY : Keyboard.write(' '); break; // ? (play/pause) > pause/play
      case STOP : Keyboard.write('x'); break; // still (stop) > stop
      case NEXT_SUBTITLE : Keyboard.write('l'); break; // subtitle > next subtitle
      //case RADIO : Keyboard.write(); break; // radio
      //case 0x2FDEA15 : Keyboard.write(); break; // ?
      //case 0x2FDBA45 : Keyboard.write(); break; // dmp
      case MENU : Keyboard.write('c'); break; // index > contextual menu
      case SCREENSHOT : Keyboard.press(KEY_LEFT_CTRL); // record > screenshot
        Keyboard.press('s');
        Keyboard.releaseAll();
        break;
      default: break; // not implemented
    }

    // Repeatable keys
    isPreviousRepeatable = true;

    switch (reverseIrCode) {
      case BACK : Keyboard.write(KEY_BACKSPACE); return;
      case EXIT : Keyboard.write(KEY_ESC); return;
      case UP : Keyboard.write(KEY_UP_ARROW); return; // up
      case DOWN : Keyboard.write(KEY_DOWN_ARROW); return; // down
      case LEFT : Keyboard.write(KEY_LEFT_ARROW); return; // left > left (seek backward)
      case RIGHT : Keyboard.write(KEY_RIGHT_ARROW); return; // right > right (seek forward)
      case VOL_UP : Keyboard.write('+'); return; // vol + > vol up
      case VOL_DOWN : Keyboard.write('-'); return; // vol - > vol down
      default: break;
    }

    // Repeatable key not found (previous switch didn't exit the function)
    isPreviousRepeatable = false;
}
