// lcd_8bit_mode.c

/*
#include <avr/io.h>
#include <util/delay.h>

//function declaration
void cmd(char x); 
void data(char y);

int main(void)
{
	DDRC=0X07;			//define PC0,PC1,PC2 as output lines (for RS,RS,EN Pins of LCD)
	DDRD=0XFF;			//define as output lines (data of LCD transmit via these lines)
	
	cmd(0X38);			//to initialize LCD in 2 lines, 5X7 dots and 8bit mode.
	//cmd(0X0F);			//Command for LCD ON Cursor ON,blinking
	//cmd(0X0E);			//Command for LCD ON Cursor ON,not blinking	
	cmd(0X0C);			//Command for LCD ON Cursor OFF

	while(1)
	{
		//cmd(0X01);			//Command to clear current screen
		cmd(0X02);			//Command to return home
		
		//cmd(0x04);
		cmd(0X86);			//Command to define the position of charaCter on LCD(8 means first row)
		data('A');			//Send 'A' character to LCD
		data('B');			//Send 'B' character to LCD
		data('C');			//Send 'B' character to LCD	
					
		cmd(0XC6);			//Command to define the position of character on LCD(C means second row)
		data('A');			//Send 'A' character to LCD
		data('B');			//Send 'B' character to LCD
		data('C');			//Send 'B' character to LCD
		
		_delay_ms(1000);	//1 Seconds delay	
	}
}

void cmd(char x)
{
	PORTD=x;			//Transmit command to LCD
	
	PORTC=0b0000100;	//Enable pin high, Rs=0 (cmd mode)
	_delay_ms(5);		//delay
	PORTC=0b0000000;	//Enable pin low, Rs=0 (cmd mode)
}

void data (char y)
{
	PORTD=y;			//Transmit command to LCD
	
	PORTC=0b0000101;	//Enable pin high, Rs=1 (data mode)
	_delay_ms(5);		//delay
	PORTC=0b0000001;	//Enable pin low, Rs=1 (data mode)
}


*/











// lcd_8bit_mode_string.c

#include <avr/io.h>
#include <util/delay.h>

//function declaration
void cmd(char x);
void data(char y);
//void string(char y[]);
void string(char *y);

int main(void)
{
	DDRC=0X07;			//define PC0,PC1,PC2 as output lines (for RS,RS,EN Pins of LCD)
	DDRD=0XFF;			//define as output lines (data of LCD transmit via these lines)
	
	cmd(0X38);			//command to select 8bit mode
	cmd(0X0E);			//command for LED ON,CURSOR ON, NO blinking
	//cmd(0X0C);			//command for LED ON,CURSOR OFF
	cmd(0X01);			//command for clear screen
	while(1)
	{
		cmd(0X01);					//command for clear screen
		//cmd(0X02);					//command for return home 
		cmd(0X80);					//command for position on LCD
		string("  LCD INTERFACING");	//String to be transmitted
		cmd(0XC0);					//command for position on LCD
		string("  BY  5VOLTZ");		//String to be transmitted
		_delay_ms(1000);
	}
}


void cmd(char x)
{
	PORTD=x;			//Transmit command to LCD
	
	PORTC=0b0000100;	//Enable pin high, Rs=0 (cmd mode)
	_delay_ms(5);		//delay
	PORTC=0b0000000;	//Enable pin low, Rs=0 (cmd mode)
}

void data (char y)
{
	PORTD=y;			//Transmit command to LCD
	
	PORTC=0b0000101;	//Enable pin high, Rs=1 (data mode)
	_delay_ms(5);		//delay
	PORTC=0b0000001;	//Enable pin low, Rs=1 (data mode)
}

void string (char y[])// y[]={'L',C,D, }
{
	int i;
	for (i=0;y[i]!='\0';i++)
	{
		data(y[i]);
	}
}

/*
void string (char *y)
{
	int i;
	for (i=0;*y!='\0';i++)
	{
		data(*y);
		y++;
	}
}*/














/*
// lcd_8bit_mode_button_press_count.c

#include <avr/io.h>
#include <util/delay.h>

//function declaration
void cmd(char x);
void data(char y);
//void string(char *y);

unsigned int press_count,button_status;
unsigned char press_count_str[5];

int main(void)
{
	DDRC=0X07;			//define PC0,PC1,PC2 as output lines (for RS,RS,EN Pins of LCD)
	DDRD=0XFF;			//define as output lines (data of LCD transmit via these lines)
	
	cmd(0X38);			//command to select 8bit mode
	cmd(0X0C);			//command for LED ON,CURSOR OFF
	cmd(0X01);			//command for clear screen
	while(1)
	{
		button_status=PINC & 0b0100000;
		if (button_status==0b0100000)
		{
			_delay_ms(250);
			press_count++;
		}
		itoa(press_count,press_count_str,10); //convert integer to string
		
		cmd(0X01);					//command for return home 
		cmd(0X80);					//command for position on LCD
		string("Press Counter");	//String to be transmitted
		cmd(0XC0);					//command for position on LCD
		string("Press No = ");		//String to be transmitted
		string(press_count_str);	//String to be transmitted
			
	}
}

void cmd(char x)
{
	PORTD=x;			//Transmit command to LCD
	
	PORTC=0b0000100;	//Enable pin high, Rs=0 (cmd mode)
	_delay_ms(5);		//delay
	PORTC=0b0000000;	//Enable pin low, Rs=0 (cmd mode)
}

void data (char y)
{
	PORTD=y;			//Transmit command to LCD
	
	PORTC=0b0000101;	//Enable pin high, Rs=1 (data mode)
	_delay_ms(5);		//delay
	PORTC=0b0000001;	//Enable pin low, Rs=1 (data mode)
}


void string (char *y)
{
	int i;
	for (i=0;*y!='\0';i++)
	{
		data(*y);
		y++;
	}
}
*/










/*

// lcd_8bit_mode_string_scrolling_text.c

#include <avr/io.h>
#include <util/delay.h>


//function declaration
void cmd(char x);
void data(char y);
void string(char *y);

int main(void)
{
	DDRC=0X07;			//define PC0,PC1,PC2 as output lines (for RS,RS,EN Pins of LCD)
	DDRD=0XFF;			//define as output lines (data of LCD transmit via these lines)
	
	cmd(0X38);			//command to select 8bit mode
	cmd(0X0C);			//command for LED ON,CURSOR OFF
	cmd(0X01);			//command for clear screen
	while(1)
	{
		for (unsigned int i=0;i<16;i++) //for scrolling right
		{
			cmd(0X02);					//command for return home 	
			unsigned int j=0;
			while(j<i)					//to print blank 
			{
				cmd(0X80+j);
				data(' ');
				j++;
			}
			cmd(0X80+i);					//command for position on LCD
			string("LCD INTERFACING");		//String to be transmitted
			_delay_ms(10);
		}
	}
}


void cmd(char x)
{
	PORTD=x;			//Transmit command to LCD
	
	PORTC=0b0000100;	//Enable pin high, Rs=0 (cmd mode)
	_delay_ms(5);		//delay
	PORTC=0b0000000;	//Enable pin low, Rs=0 (cmd mode)
}

void data (char y)
{
	PORTD=y;			//Transmit command to LCD
	
	PORTC=0b0000101;	//Enable pin high, Rs=1 (data mode)
	_delay_ms(5);		//delay
	PORTC=0b0000001;	//Enable pin low, Rs=1 (data mode)
}

void string (char *y)
{
	int i;
	for (i=0;*y!='\0';i++)
	{
		data(*y);
		y++;
	}
}
*/
