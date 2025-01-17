#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>
#include "timers.h"
/*
       ##  #     # ####      ###      ###   ##
      #  # #     # #   #     #  #        # #  #
      ####  #   #  ####      #  # # #  ##    #
      #  #   # #   # #       #  #  #     #  #
      #  #    #    #  #      ###  # # ###  ####
*/

#define DEFAULT_32PIN_PINOUT

// Arduino pin macros
#define PIN_PA0 (0)
#define PIN_PA1 (1)
#define PIN_PA2 (2)
#define PIN_PA3 (3)
#define PIN_PA4 (4)
#define PIN_PA5 (5)
#define PIN_PA6 (6)
#define PIN_PA7 (7)
#define PIN_PC0 (8)
#define PIN_PC1 (9)
#define PIN_PC2 (10)
#define PIN_PC3 (11)
#define PIN_PD0 (12)
/* On DB32, PD0 is not a pin - everything else NOT_A_PIN's pin 12, but we can
 * still add an offset to it to get pin number for other pins on the port,
 * after finding it with digitalPinToPinZero() for determination of pin
 * numbers at runtime. This way if you get the number of a port, and
 * need to determine the pin number of bit 3 of that port so you can call
 * turnOffPWM() on it - PIN_PD0+3 is a 15, PIN_PD3. Calling I/O functions
 * will still fail with PIN_PD0, but fail harmlessly, because everything
 * (bit_mask, bit_position, etc) resolves to NOT_A_PIN */
#define PIN_PD1 (13)
#define PIN_PD2 (14)
#define PIN_PD3 (15)
#define PIN_PD4 (16)
#define PIN_PD5 (17)
#define PIN_PD6 (18)
#define PIN_PD7 (19)
#define PIN_PF0 (20)
#define PIN_PF1 (21)
#define PIN_PF2 (22)
#define PIN_PF3 (23)
#define PIN_PF4 (24)
#define PIN_PF5 (25)
#define PIN_PF6 (26)

#define PINS_COUNT                     27
#define NUM_DIGITAL_PINS               PINS_COUNT
#define NUM_ANALOG_INPUTS              12
#define NUM_RESERVED_PINS              0
#define NUM_INTERNALLY_USED_PINS       0
#define NUM_I2C_PINS                   4 // (SDA / SCL)
#define NUM_SPI_PINS                   6 // (MISO / MOSI / SCK)
#define NUM_TOTAL_FREE_PINS            (NUM_DIGITAL_PINS)
#define NUM_TOTAL_PINS                 (NUM_DIGITAL_PINS)
//#define ANALOG_INPUT_OFFSET          12 //See comments in 64-pin variant.
#if !defined(LED_BUILTIN)
  #define LED_BUILTIN                  PIN_PA7
#endif
#define EXTERNAL_NUM_INTERRUPTS        47


#define digitalPinToAnalogInput(p)        (((p) > PIN_PC3 && (p) < PIN_PF0) ? ((p) - PIN_PD0) : ((p) < PIN_PF6 ? ((p) - 4) : NOT_A_PIN))
#define analogChannelToDigitalPin(p)      ((p) < 8 ? ((p) + PIN_PD0) : (((p) > 15 && (p) < 22) ? ((p) - 16 + PIN_PF0) : NOT_A_PIN))
#define analogInputToDigitalPin(p)                        analogChannelToDigitalPin((p) & 0x7F)
#define digitalOrAnalogPinToDigital(p)    (((p) & 0x80) ? analogChannelToDigitalPin((p) & 0x7f) : (((p)<=NUM_DIGITAL_PINS) ? (p) : NOT_A_PIN))
#define portToDigitalPinZero(port)        ((port) == 0 ? 0 : ((port)== 2 ? 8 : ((port)== 3 ? 12 : ((port)== 5 ? 20 : NOT_A_PIN))))

// PWM pins

#if defined(MILLIS_USE_TIMERB0)
  #define digitalPinHasPWMTCB(p) (((p) == PIN_PA3) || ((p) == PIN_PC0)
#elif defined(MILLIS_USE_TIMERB1)
  #define digitalPinHasPWMTCB(p) (((p) == PIN_PA2) || ((p) == PIN_PC0)
#elif defined(MILLIS_USE_TIMERB2)
  #define digitalPinHasPWMTCB(p) (((p) == PIN_PA2) || ((p) == PIN_PA3)
#else //no TCB's are used for millis
  #define digitalPinHasPWMTCB(p) (((p) == PIN_PA2) || ((p) == PIN_PA3) || ((p) == PIN_PC0)
#endif

// Timer pin mapping
#define TCA0_PINS PORTMUX_TCA0_PORTD_gc // TCA0 output on PD[0:5]
#define TCB0_PINS 0x00                  // TCB0 output on PA2 instead of PF4
#define TCB1_PINS 0x00                  // TCB1 output on PA3 instead of PF5
#define TCB2_PINS 0x00                  // TCB2 output on PC0 instead of PB4
#define TCD0_PINS 0x00                  // TCD0 output on PA4~PA7


#define PIN_TCA0_WO0_INIT PIN_PD0
#define PIN_TCD0_WOA_INIT PIN_PA4

#define USE_TIMERD0_PWM
#define NO_GLITCH_TIMERD0


#define digitalPinHasPWM(p)               (digitalPinHasPWMTCB(p) || ((p) >= PIN_PA4 && (p) <= PIN_PA7) || ((p) >= PD0 && (p) < PIN_PD6))

/*
      ####   ###  ####  ##### #   # #   # #   #
      #   # #   # #   #   #   ## ## #   #  # #
      ####  #   # ####    #   # # # #   #   #
      #     #   # # #     #   #   # #   #  # #
      #      ###  #  #    #   #   #  ###  #   #
*/

#define SPI_INTERFACES_COUNT   1 /* See SPI.h */

// SPI 0
#define SPI_MUX                PORTMUX_SPI0_DEFAULT_gc
#define PIN_SPI_MISO           PIN_PA5
#define PIN_SPI_SCK            PIN_PA6
#define PIN_SPI_MOSI           PIN_PA4
#define PIN_SPI_SS             PIN_PA7


// SPI 1
#define SPI1_MUX                PORTMUX_SPI1_DEFAULT_gc
#define PIN_SPI1_MISO           PIN_PC0
#define PIN_SPI1_SCK            PIN_PC1
#define PIN_SPI1_MOSI           PIN_PC2
#define PIN_SPI1_SS             PIN_PC3


// TWI 0
#define PIN_WIRE_SDA           PIN_PA2
#define PIN_WIRE_SCL           PIN_PA3
#define PIN_WIRE_SDA_PINSWAP_1 PIN_PA2
#define PIN_WIRE_SCL_PINSWAP_1 PIN_PA3
#define PIN_WIRE_SDA_PINSWAP_2 PIN_PC2
#define PIN_WIRE_SCL_PINSWAP_2 PIN_PC3


// TWI 1
#define PIN_WIRE1_SDA           PIN_PF2
#define PIN_WIRE1_SCL           PIN_PF3
#define PIN_WIRE1_SDA_PINSWAP_1 PIN_PF2
#define PIN_WIRE1_SCL_PINSWAP_1 PIN_PF3

#define NUM_HWSERIAL_PORTS              3

// USART 0
#define HWSERIAL0                       &USART0
#define HWSERIAL0_DRE_VECTOR            USART0_DRE_vect
#define HWSERIAL0_DRE_VECTOR_NUM        USART0_DRE_vect_num
#define HWSERIAL0_RXC_VECTOR            USART0_RXC_vect
#define HWSERIAL0_MUX                   PORTMUX_USART0_DEFAULT_gc
#define HWSERIAL0_MUX_PINSWAP_1         PORTMUX_USART0_ALT1_gc
#define HWSERIAL0_MUX_PINSWAP_NONE      PORTMUX_USART0_NONE_gc
#define PIN_HWSERIAL0_TX                PIN_PA0
#define PIN_HWSERIAL0_RX                PIN_PA1
#define PIN_HWSERIAL0_XCK               PIN_PA2
#define PIN_HWSERIAL0_XDIR              PIN_PA3
#define PIN_HWSERIAL0_TX_PINSWAP_1      PIN_PA4
#define PIN_HWSERIAL0_RX_PINSWAP_1      PIN_PA5
#define PIN_HWSERIAL0_XCK_PINSWAP_1     PIN_PA6
#define PIN_HWSERIAL0_XDIR_PINSWAP_1    PIN_PA7

// USART1
#define HWSERIAL1                       &USART1
#define HWSERIAL1_DRE_VECTOR            USART1_DRE_vect
#define HWSERIAL1_DRE_VECTOR_NUM        USART1_DRE_vect_num
#define HWSERIAL1_RXC_VECTOR            USART1_RXC_vect
#define HWSERIAL1_MUX                   PORTMUX_USART1_DEFAULT_gc
#define HWSERIAL1_MUX_PINSWAP_1         NOT_A_MUX
#define HWSERIAL1_MUX_PINSWAP_NONE      PORTMUX_USART1_NONE_gc
#define PIN_HWSERIAL1_TX                PIN_PC0
#define PIN_HWSERIAL1_RX                PIN_PC1
#define PIN_HWSERIAL1_XCK               PIN_PC2
#define PIN_HWSERIAL1_XDIR              PIN_PC3
#define PIN_HWSERIAL1_TX_PINSWAP_1      NOT_A_PIN
#define PIN_HWSERIAL1_RX_PINSWAP_1      NOT_A_PIN
#define PIN_HWSERIAL1_XCK_PINSWAP_1     NOT_A_PIN
#define PIN_HWSERIAL1_XDIR_PINSWAP_1    NOT_A_PIN

// USART 2
#define HWSERIAL2                       &USART2
#define HWSERIAL2_DRE_VECTOR            USART2_DRE_vect
#define HWSERIAL2_DRE_VECTOR_NUM        USART2_DRE_vect_num
#define HWSERIAL2_RXC_VECTOR            USART2_RXC_vect
#define HWSERIAL2_MUX                   PORTMUX_USART2_DEFAULT_gc
#define HWSERIAL2_MUX_PINSWAP_1         PORTMUX_USART2_ALT1_gc
#define HWSERIAL2_MUX_PINSWAP_NONE      PORTMUX_USART2_NONE_gc
#define PIN_HWSERIAL2_TX                PIN_PF0
#define PIN_HWSERIAL2_RX                PIN_PF1
#define PIN_HWSERIAL2_XCK               PIN_PF2
#define PIN_HWSERIAL2_XDIR              PIN_PF3
#define PIN_HWSERIAL2_TX_PINSWAP_1      PIN_PF4
#define PIN_HWSERIAL2_RX_PINSWAP_1      PIN_PF5
#define PIN_HWSERIAL2_XCK_PINSWAP_1     NOT_A_PIN
#define PIN_HWSERIAL2_XDIR_PINSWAP_1    NOT_A_PIN

/*
       ##  #   #  ##  #     ###   ###      ####  ### #   #  ###
      #  # ##  # #  # #    #   # #         #   #  #  ##  # #
      #### # # # #### #    #   # #  ##     ####   #  # # #  ###
      #  # #  ## #  # #    #   # #   #     #      #  #  ##     #
      #  # #   # #  # ####  ###   ###      #     ### #   #  ###
*/

#ifndef MVIO
  // 32-pin parts with MVIO don't have an A0 or a PD0, as that physical pin is used for VDDIO2
  #define PIN_A0   PIN_PD0
#else
  #define PIN_A0   NOT_A_PIN
#endif
#define PIN_A1   PIN_PD1
#define PIN_A2   PIN_PD2
#define PIN_A3   PIN_PD3
#define PIN_A4   PIN_PD4
#define PIN_A5   PIN_PD5
#define PIN_A6   PIN_PD6
#define PIN_A7   PIN_PD7
#define PIN_A16  PIN_PF0
#define PIN_A17  PIN_PF1
#define PIN_A18  PIN_PF2
#define PIN_A19  PIN_PF3
#define PIN_A20  PIN_PF4
#define PIN_A21  PIN_PF5


#ifndef MVIO
  static const uint8_t A0  = PIN_A0;
#else
  static const uint8_t A0  = NOT_A_PIN;
#endif
static const uint8_t A1  = PIN_A1;
static const uint8_t A2  = PIN_A2;
static const uint8_t A3  = PIN_A3;
static const uint8_t A4  = PIN_A4;
static const uint8_t A5  = PIN_A5;
static const uint8_t A6  = PIN_A6;
static const uint8_t A7  = PIN_A7;
static const uint8_t A16 = PIN_A16;
static const uint8_t A17 = PIN_A17;
static const uint8_t A18 = PIN_A18;
static const uint8_t A19 = PIN_A19;
static const uint8_t A20 = PIN_A20;
static const uint8_t A21 = PIN_A21;
/* AINn = (0x80 | n)
 * can be turned into digital pins with analogInputToDigitalPin(), but do not
 * directly work in digital I/O (this can be changed, but I'd rather not have
 * to, as it slows down every non-compiletime-known call to digital I/O. Just
 * because these parts can be clocked higher doesn't mean we should bog them
 * down until they run slower. */
#define  AIN0  ADC_CH(0)
#define  AIN1  ADC_CH(1)
#define  AIN2  ADC_CH(2)
#define  AIN3  ADC_CH(3)
#define  AIN4  ADC_CH(4)
#define  AIN5  ADC_CH(5)
#define  AIN6  ADC_CH(6)
#define  AIN7  ADC_CH(7)
#define AIN16 ADC_CH(16)
#define AIN17 ADC_CH(17)
#define AIN18 ADC_CH(18)
#define AIN19 ADC_CH(19)
#define AIN20 ADC_CH(20)
#define AIN21 ADC_CH(21)

/*
            ####  ### #   #      ##  ####  ####   ##  #   #  ###
            #   #  #  ##  #     #  # #   # #   # #  #  # #  #
            ####   #  # # #     #### ####  ####  ####   #    ###
            #      #  #  ##     #  # # #   # #   #  #   #       #
            #     ### #   #     #  # #  #  #  #  #  #   #    ###
*/
#ifdef ARDUINO_MAIN

const uint8_t digital_pin_to_port[] = {
  PA, //  0 PA0/USART0_Tx/CLKIN
  PA, //  1 PA1/USART0_Rx
  PA, //  2 PA2/SDA
  PA, //  3 PA3/SCL
  PA, //  4 PA4/MOSI
  PA, //  5 PA5/MISO
  PA, //  6 PA6/SCK
  PA, //  7 PA7/SS/CLKOUT/LED_BUILTIN
  PC, //  8 PC0/USART1_Tx
  PC, //  9 PC1/USART1_Rx
  PC, // 10 PC2
  PC, // 11 PC3
  PD, // 12 PD0/AIN0
  PD, // 13 PD1/AIN1
  PD, // 14 PD2/AIN2
  PD, // 15 PD3/AIN3
  PD, // 16 PD4/AIN4
  PD, // 17 PD5/AIN5
  PD, // 18 PD6/AIN6
  PD, // 19 PD7/AIN7/AREF
  PF, // 20 PF0/AIN16/USART2_Tx/TOSC1
  PF, // 21 PF1/AIN17/USART2_Rx/TOSC2
  PF, // 22 PF2/AIN18
  PF, // 23 PF3/AIN19
  PF, // 24 PF4/AIN20/TCB0 PWM
  PF, // 25 PF5/AIN21/TCB1 PWM
  PF  // 26 PF6 RESET
};

/* Use this for accessing PINnCTRL register */
const uint8_t digital_pin_to_bit_position[] = {
  PIN0_bp, //  0 PIN_bp0/USART0_Tx/CLKIN
  PIN1_bp, //  1 PA1/USART0_Rx
  PIN2_bp, //  2 PA2/SDA
  PIN3_bp, //  3 PA3/SCL
  PIN4_bp, //  4 PA4/MOSI
  PIN5_bp, //  5 PA5/MISO
  PIN6_bp, //  6 PA6/SCK
  PIN7_bp, //  7 PA7/SS/CLKOUT
  PIN0_bp, //  8 PC0/USART1_Tx
  PIN1_bp, //  9 PC1/USART1_Rx
  PIN2_bp, // 10 PC2
  PIN3_bp, // 11 PC3
  #ifndef MVIO
  PIN0_bp, // 12 PD0/AIN0
  #else
  NOT_A_PIN,
  #endif
  PIN1_bp, // 13 PD1/AIN1
  PIN2_bp, // 14 PD2/AIN2
  PIN3_bp, // 15 PD3/AIN3
  PIN4_bp, // 16 PD4/AIN4
  PIN5_bp, // 17 PD5/AIN5
  PIN6_bp, // 18 PD6/AIN6
  PIN7_bp, // 19 PD7/AIN7/AREF
  PIN0_bp, // 20 PF0/USART2_Tx/TOSC1
  PIN1_bp, // 21 PF1/USART2_Rx/TOSC2
  PIN2_bp, // 22 PF2/AIN12
  PIN3_bp, // 23 PF3/AIN13
  PIN4_bp, // 24 PF4/AIN14/TCB0 PWM
  PIN5_bp, // 25 PF5/AIN15/TCB1 PWM
  PIN6_bp  // 26 PF6 RESET
};

/* Use this for accessing PINnCTRL register */
const uint8_t digital_pin_to_bit_mask[] = {
  PIN0_bm, //  0 PA0/USART0_Tx/CLKIN
  PIN1_bm, //  1 PA1/USART0_Rx
  PIN2_bm, //  2 PA2/SDA
  PIN3_bm, //  3 PA3/SCL
  PIN4_bm, //  4 PA4/MOSI
  PIN5_bm, //  5 PA5/MISO
  PIN6_bm, //  6 PA6/SCK
  PIN7_bm, //  7 PA7/SS/CLKOUT
  PIN0_bm, //  8 PC0/USART1_Tx
  PIN1_bm, //  9 PC1/USART1_Rx
  PIN2_bm, // 10 PC2
  PIN3_bm, // 11 PC3
  #ifndef MVIO
  PIN0_bm, // 12 PD0/AIN0
  #else
  NOT_A_PIN,
  #endif
  PIN1_bm, // 13 PD1/AIN1
  PIN2_bm, // 14 PD2/AIN2
  PIN3_bm, // 15 PD3/AIN3
  PIN4_bm, // 16 PD4/AIN4
  PIN5_bm, // 17 PD5/AIN5
  PIN6_bm, // 18 PD6/AIN6
  PIN7_bm, // 19 PD7/AIN7/AREF
  PIN0_bm, // 20 PF0/USART2_Tx/TOSC1
  PIN1_bm, // 21 PF1/USART2_Rx/TOSC2
  PIN2_bm, // 22 PF2/AIN12
  PIN3_bm, // 23 PF3/AIN13
  PIN4_bm, // 24 PF4/AIN14/TCB0 PWM
  PIN5_bm, // 25 PF5/AIN15/TCB1 PWM
  PIN6_bm  // 26 PF6 RESET
};

const uint8_t digital_pin_to_timer[] = {
  NOT_ON_TIMER, //  0 PA0/USART0_Tx/CLKIN
  NOT_ON_TIMER, //  1 PA1/USART0_Rx
  TIMERB0,      //  2 PA2/SDA
  TIMERB1,      //  3 PA3/SCL
  TIMERD0,      //  4 PA4/MOSI      WOA
  TIMERD0,      //  5 PA5/MISO      WOB
  TIMERD0,      //  6 PA6/SCK       WOC mirrors WOA
  TIMERD0,      //  7 PA7/SS/CLKOUT WOD mirrors WOB
  TIMERB2,      //  8 PC0/USART1_Tx
  NOT_ON_TIMER, //  9 PC1/USART1_Rx
  NOT_ON_TIMER, // 10 PC2
  NOT_ON_TIMER, // 11 PC3
  #ifndef MVIO
  NOT_ON_TIMER, // 12 PD0/AIN0
  #else
  NOT_ON_TIMER,
  #endif
  NOT_ON_TIMER, // 13 PD1/AIN1
  NOT_ON_TIMER, // 14 PD2/AIN2
  NOT_ON_TIMER, // 15 PD3/AIN3
  NOT_ON_TIMER, // 16 PD4/AIN4
  NOT_ON_TIMER, // 17 PD5/AIN5
  DACOUT,       // 18 PD6/AIN6
  NOT_ON_TIMER, // 19 PD7/AIN7/AREF
  NOT_ON_TIMER, // 20 PF0/USART2_Tx/TOSC1
  NOT_ON_TIMER, // 21 PF1/USART2_Rx/TOSC2
  NOT_ON_TIMER, // 22 PF2/AIN12
  NOT_ON_TIMER, // 23 PF3/AIN13
  NOT_ON_TIMER, // 24 PF4/AIN14
  NOT_ON_TIMER, // 25 PF5/AIN15
  NOT_ON_TIMER  // 26 PF6 RESET
};

#endif

#endif
