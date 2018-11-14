
#define F_CPU 16000000UL
#include <util/delay.h>

/*******************************************************************************
LCD.h
*******************************************************************************/
class LCD
{
    public:
        LCD();

        void Initialize();

        void Instruction(unsigned char data);

    private: // Fields
        union
        {
            struct
            {
                unsigned char lowNibble  : 4;
                unsigned char highNibble : 4;
            };
            unsigned char fullByte;
        }LCDWord;

    private: // Methods
        void PulseE();

};


/*******************************************************************************
LCD.cpp
*******************************************************************************/

/***************************************
Public methods:
***************************************/
LCD::LCD()
{
}

void LCD::Initialize()
{
    DDRB |= 0b00001111; // Our 4 bits set to output
    DDRD |= 0b11000000; // Set E and RS to output

    PORTB &= 0b11110000; // Our 4 bits off
    PORTD &= 0b00111111; // RS and E off

    _delay_ms(15);

    LCDWord.lowNibble = 0b0011;
    PORTB |=          LCDWord.lowNibble;
    PORTB &= (0xF0 | LCDWord.lowNibble);
    PulseE();
    _delay_ms(5);

    PulseE();
    _delay_us(110);

    PulseE();
    _delay_us(110);

    LCDWord.lowNibble =                     0b0010;
    PORTB            |=          LCDWord.lowNibble;
    PORTB            &= (0xF0 | LCDWord.lowNibble);
    PulseE();
    _delay_us(100);

    Instruction(0b00101000); // 2-line mode
    _delay_us(50);

    Instruction(0b00001111); // Activate Display

    Instruction(0b00000001); // Clear Display
    _delay_ms(2);
}

void LCD::Instruction(unsigned char data)
{
    LCDWord.lowNibble  =        0x0F & data;
    LCDWord.highNibble = (0xF0 & data) >> 4;

    PORTB |=          LCDWord.highNibble;
    PORTB &= (0xF0 | LCDWord.highNibble);
    PulseE();

    PORTB |=          LCDWord.lowNibble;
    PORTB &= (0xF0 | LCDWord.lowNibble);
    PulseE();

    _delay_us(50);
}

/***************************************
Private methods:
***************************************/
void LCD::PulseE()
{
    PORTD |= 0b10000000; // E on
    _delay_us(1);
    PORTD &= 0b01111111; // E off
}

/*******************************************************************************
Program start:
*******************************************************************************/

// Global lcd object:
LCD lcd;

void setup()
{
    lcd.Initialize();
    PORTD |= (1 << PD6); // set RS
    lcd.Instruction('N');
}

void loop()
{

}
