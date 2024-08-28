#include "print_uart.h"
#include "misc.h"
#include <stdio.h>
#include <stdarg.h>
#include "stm32f4xx_hal.h"
#include "peripheral_init.h"


void put_char_uart(uint8_t data)
{

	HAL_UART_Transmit(&huart5, &data, 1, 1000);

	return;
}

uint8_t get_char_uart()
{
	uint8_t data;

	while(HAL_UART_Receive(&huart5, &data, 1, 1000));

	return data;
}

void print_string_uart(uint8_t * str)
{
	uint16_t k = 0;

	while (str[k] != '\0')
    {
		put_char_uart(str[k]);
        if (str[k] == '\n')
        	put_char_uart('\r');
        k++;

        if (k == MAX_PRINT_STRING_SIZE)
            break;
    }

	return;
}






void print_uart(char *str, ... )
{
    uint8_t rstr[40];
    uint16_t k = 0;
    uint16_t arg_type;

    uint32_t utmp32;
    uint32_t * p_uint32;
    float ftmp;
    char * p_char;
    va_list vl;

    va_start(vl, str);
    while(str[k] != 0x00)
    {
        if(str[k] == '%')
        {
            if(str[k+1] != 0x00)
            {
                switch(str[k+1])
                {

                    case('f'):
                    {// float
                        ftmp = va_arg(vl, double);

                        int intPart = (int)ftmp;
                        float decimalPart = ftmp - intPart;
                        int decimalLength = 4;
                        int decimalMultiplier = 1;
                        for (int i = 0; i < decimalLength; ++i) {
                            decimalMultiplier *= 10;
                            decimalPart *= 10;
                        }
                        int decPart = (int)decimalPart;

                        // Print integer part
                        sprintf((char *)rstr, "%d.", intPart);
                        print_string_uart(rstr);

                        // Print decimal part
                        sprintf((char *)rstr, "%d", decPart);
                        print_string_uart(rstr);

                        arg_type = (PRINT_ARG_TYPE_FLOAT);
                        break;
                    }

                }
                k++;
            }
        }
        else
        {
            put_char_uart(str[k]);
            if (str[k] == '\n')
                put_char_uart('\r');
        }
        k++;
    }

    va_end(vl);
    return;
}

