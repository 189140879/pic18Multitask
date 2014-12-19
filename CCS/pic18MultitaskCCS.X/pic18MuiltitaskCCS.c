/*
 * File:   pic18MultitaskCCS.c
 * Author: JASPHER LOPEZ C
 * jlopezca@uni.pe
 * MIT License
 */


#include <18F4550.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set> extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES HSPLL,NOPROTECT,USBDIV,PLL5,CPUDIV1
#use delay(clock=48M,crystal=20M)

#use rs232(baud = 9600, xmit = PIN_C6, rcv = PIN_C7)

#byte PORTA = 0x80
#byte PORTB = 0x81
#byte PORTC = 0x82
#byte PORTD = 0x83
#byte PORTE = 0x84
#byte TRISA = 0x92
#byte TRISB = 0x93
#byte TRISC = 0x94
#byte TRISD = 0x95
#byte TRISE = 0x96


#byte TOSU = 0xFFF
#byte TOSH = 0xFFE
#byte TOSL = 0xFFD
#byte STKPTR = 0xFFC
#byte PCLATU = 0xFFB
#byte PCLATH = 0xFFA
#byte PCL = 0xFF9
#byte TMR0H = 0xFD7
#byte TMR0L = 0xFD6
#byte T0CON = 0xFD5
#byte T1CON = 0xFCD
#byte bsr = 0xFE0
#byte wreg = 0xFE8
#byte status = 0xFD8
#byte RCON = 0xFD0
#byte INTCON = 0xFF2

//Agregado (2 líneas):
#byte PIR1 = 0XF9E
#bit RCIF = PIR1.5

#byte ADCON0 = 0xFC2
#byte ADCON2 = 0xFC0
#byte ADRESL = 0xFC3
#byte ADRESH = 0xFC4
#bit ANALOGICO = ADCON0.3
#bit TMR0IE = INTCON.5
#bit TMR0IF = INTCON.2
#bit IPEN = RCON.7

#byte CCPR1L = 0xFBE
#byte CCP1CON = 0XFBD
#bit CCP5 = CCP1CON.5
#bit CCP4 = CCP1CON.4

#byte UCON=0xF6D
#bit USBEN=UCON.3

struct Process
{
    long StartAddress;
    long EndAddress;
    long CurrentAddress;
    int ProcessStatus;
    int RWREG;
    int RSTATUS;
    int RBSR;
    int Id;
} pList[8]; // Lista de procesos
int pStack[8]; // Pila de procesos
char cmd = 0x00; // Comando
char speed = '-';
int nCount = 0; // Numero de procesos
int pCount; // Total de procesos

void enableQuantum()
{
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_2); //10.9 ms overflow
    enable_interrupts(INT_TIMER1);
}

void disableQuantum()
{
    disable_interrupts(INT_TIMER1);
}

void Init_PWM()
{
    setup_ccp1(ccp_pwm);
    setup_timer_2(t2_div_by_16, 249, 10); //Para un periodo de 1.6ms
    CCPR1L = 0x00;
    CCP5 = 0x00;
    CCP4 = 0x00;
}



int processIdToSend = -1;
#INT_TIMER0

void Isr_TIMER0()
{

    output_toggle(PIN_C1);

    if (nCount > 0)
    {

        processIdToSend++;
        if (processIdToSend > pCount)
            processIdToSend = 0;
        printf("$%i %Lu %i;", pList[0].Id, pList[0].CurrentAddress, pList[0].ProcessStatus);
        printf("$%i %Lu %i;", pList[processIdToSend].Id, pList[processIdToSend].CurrentAddress, pList[processIdToSend].ProcessStatus);
    }
}


#INT_TIMER1

void Isr_QUANTUM()
{
    pList[pStack[0]].RSTATUS = status;
    pList[pStack[0]].RWREG = wreg;
    pList[pStack[0]].RBSR = bsr;

    disableQuantum();
    if (nCount > 0)
    {
        pList[pStack[0]].CurrentAddress = TOSL + (TOSH * 256) + (TOSU * 65536);
        int temp;
        temp = pStack[0];
        int k;
        for (k = 0; k < (nCount - 1); k++)
        {
            pStack[k] = pStack[k + 1];
        }
        pStack[nCount - 1] = temp;
    }

    goto_address(pList[0].StartAddress);
}

#INT_RDA

void Isr_Data()
{
    cmd = getc();
    if (cmd == '+' || cmd == '-')
    {
        speed = cmd;
        cmd = 0x0;
    }
    output_toggle(PIN_B7);
}

#ORG 0x1000, 0x1350

void Task1()
{

    long vk1, vl1;
    while (TRUE)
    {
        output_low(PIN_C0);
        output_low(PIN_D3);
        output_low(PIN_A2);
        output_low(PIN_A3);
        for (vk1 = 1; vk1 < 600; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_high(PIN_C0);

        for (vk1 = 1; vk1 < 600; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_high(PIN_D3);

        for (vk1 = 1; vk1 < 600; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_high(PIN_A2);

        for (vk1 = 1; vk1 < 600; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_high(PIN_A3);

        for (vk1 = 1; vk1 < 600; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_A3);

        for (vk1 = 1; vk1 < 600; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_A2);

        for (vk1 = 1; vk1 < 600; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D3);

        for (vk1 = 1; vk1 < 600; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }


    }

}


#ORG 0x1352, 0x2000

void Task2()
{
    long t21, t22;
    do
    {

        output_b(~103);
        for (t21 = 0; t21 < 600; ++t21)
        {
            for (t22 = 0; t22 < 500; ++t22)
            {
            }

        }
        output_b(~127);
        for (t21 = 0; t21 < 600; ++t21)
        {
            for (t22 = 0; t22 < 500; ++t22)
            {
            }

        }
        output_b(~7);
        for (t21 = 0; t21 < 600; ++t21)
        {
            for (t22 = 0; t22 < 500; ++t22)
            {
            }

        }
        output_b(~125);
        for (t21 = 0; t21 < 600; ++t21)
        {
            for (t22 = 0; t22 < 500; ++t22)
            {
            }

        }
        output_b(~109);
        for (t21 = 0; t21 < 600; ++t21)
        {
            for (t22 = 0; t22 < 500; ++t22)
            {
            }

        }
        output_b(~102);
        for (t21 = 0; t21 < 600; ++t21)
        {
            for (t22 = 0; t22 < 500; ++t22)
            {
            }

        }
        output_b(~79);
        for (t21 = 0; t21 < 600; ++t21)
        {
            for (t22 = 0; t22 < 500; ++t22)
            {
            }

        }
        output_b(~91);
        for (t21 = 0; t21 < 600; ++t21)
        {
            for (t22 = 0; t22 < 500; ++t22)
            {
            }

        }
        output_b(~6);
        for (t21 = 0; t21 < 600; ++t21)
        {
            for (t22 = 0; t22 < 500; ++t22)
            {
            }

        }
        output_b(~63);
        for (t21 = 0; t21 < 600; ++t21)
        {
            for (t22 = 0; t22 < 500; ++t22)
            {
            }

        }
    }
    while (TRUE);
}


#ORG 0x2010, 0x2500

void Task3()
{
    while (TRUE)
    {
        if (speed == '-')
        {
            CCPR1L = 0xAA; //
            CCP5 = 1;
            CCP4 = 0;
        }

        if (speed == '+')
        {
            CCPR1L = 0x55;
            CCP5 = 0;
            CCP4 = 1;
        }
    }
}



#ORG 0x2510, 0x3000
void Task4(void)
{
    long vk1, vl1;
    while (TRUE)
    {
        output_high(PIN_D1);
        output_high(PIN_D2);

        output_low(PIN_D4);
        output_low(PIN_D5);

        output_low(PIN_D6);
        output_low(PIN_D7);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D1);
        output_low(PIN_D2);

        output_high(PIN_D4);
        output_high(PIN_D5);
        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D4);
        output_low(PIN_D5);

        output_high(PIN_D6);
        output_high(PIN_D7);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }

        output_low(PIN_D6);
        output_low(PIN_D7);

        output_high(PIN_D1);
        output_high(PIN_D2);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D1);
        output_low(PIN_D2);

        output_high(PIN_D4);
        output_high(PIN_D5);
        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D4);
        output_low(PIN_D5);

        output_high(PIN_D6);
        output_high(PIN_D7);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }


        output_low(PIN_D1);
        output_low(PIN_D2);

        output_low(PIN_D4);
        output_low(PIN_D5);

        output_low(PIN_D6);
        output_low(PIN_D7);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_high(PIN_D1);
        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D1);
        output_high(PIN_D2);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D2);
        output_high(PIN_D4);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D4);
        output_high(PIN_D5);


        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D5);
        output_high(PIN_D6);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D6);
        output_high(PIN_D7);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }




        ///

        output_low(PIN_D7);
        output_high(PIN_D1);
        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D1);
        output_high(PIN_D2);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D2);
        output_high(PIN_D4);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D4);
        output_high(PIN_D5);


        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D5);
        output_high(PIN_D6);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
        output_low(PIN_D6);
        output_high(PIN_D7);

        for (vk1 = 1; vk1 < 300; ++vk1)
        {
            for (vl1 = 1; vl1 < 500; ++vl1)
            {
            }
        }
    }
}



#ORG 0x3010, 0x3500

void Task5(void)
{
    long l1, k1;
    while (TRUE)
    {

        output_low(PIN_E0);
        output_low(PIN_E1);
        output_low(PIN_E2);
        for (l1 = 1; l1 < 400; ++l1)
        {
            for (k1 = 1; k1 < 500; ++k1)
            {
            }
        }
        output_high(PIN_E0);
        for (l1 = 1; l1 < 400; ++l1)
        {
            for (k1 = 1; k1 < 500; ++k1)
            {
            }
        }
        output_high(PIN_E1);
        output_low(PIN_E0);
        for (l1 = 1; l1 < 400; ++l1)
        {
            for (k1 = 1; k1 < 500; ++k1)
            {
            }
        }
        output_high(PIN_E2);
        output_low(PIN_E1);
        for (l1 = 1; l1 < 400; ++l1)
        {
            for (k1 = 1; k1 < 500; ++k1)
            {
            }
        }
    }
}

void Init_PORTS()
{
    USBEN = 0;
    set_tris_a(0b11110010);
    set_tris_b(0x00);
    set_tris_c(0b11000000);
    set_tris_d(0x00);
    set_tris_e(0x00);

    output_a(0x00);
    output_b(0xFF);
    output_c(0x00);
    output_d(0x00);
    output_e(0x00);
    output_low(PIN_B7);
}

void Init_INTERRUPTS()
{
    enable_interrupts(GLOBAL);
    enable_interrupts(INT_RDA);
}

void Init_TIMERS()
{
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_128); //699 ms overflow
    enable_interrupts(INT_TIMER0);
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_2); //10.9 ms overflow
    disable_interrupts(INT_TIMER1);
}

void Init_PROCESSES() //invocado al inicializar
{
    pList[0].Id = 0;
    pList[1].Id = 1;
    pList[2].Id = 2;
    pList[3].Id = 3;
    pList[4].Id = 4;
    pList[5].Id = 5;

    pList[0].ProcessStatus = 2;
    pList[1].ProcessStatus = 0;
    pList[2].ProcessStatus = 0;
    pList[3].ProcessStatus = 0;
    pList[4].ProcessStatus = 0;
    pList[5].ProcessStatus = 0;

    pList[0].StartAddress = 0x4000;
    pList[0].CurrentAddress = 0x4000;
    pList[0].EndAddress = 0x4900;

    pList[1].StartAddress = 0x1000;
    pList[1].CurrentAddress = 0x1000;
    pList[1].EndAddress = 0x1150; //

    pList[2].StartAddress = 0x1352;
    pList[2].CurrentAddress = 0x1352;
    pList[2].EndAddress = 0x2000;

    pList[3].StartAddress = 0x2010;
    pList[3].CurrentAddress = 0x2010;
    pList[3].EndAddress = 0x2500;

    pList[4].StartAddress = 0x2510; //
    pList[4].CurrentAddress = 0x2510;
    pList[4].EndAddress = 0x3000;

    pList[5].StartAddress = 0x3010; //
    pList[5].CurrentAddress = 0x3010;
    pList[5].EndAddress = 0x3500;

    pCount = 6;

}

void Init_MCI()
{
    cmd = 0x0;
    Init_PORTS(); //puertos B, C y D a cero
    Init_PWM();
    Init_PROCESSES(); //Configuración de direcciones y estado
    Init_INTERRUPTS(); //Habilitación comunicación serial (a su cargo la variable proceso)
    Init_TIMERS(); //Configura el TMR0 (registro T0CON), sin habilitar las interrupciones
}

void main(void)
{
    Init_MCI();
    output_high(PIN_C1);
    goto_address(pList[0].StartAddress);
}

int IsLoaded(int pID)
{
    int i;
    for (i = 0; i < nCount; i++)
    {
        if (pStack[i] == pID)
        {
            return i;
        }
    }
    return -1;
}

void LoadProcess(int pID)
{
    // Añadir a la Pila de procesos
    pStack[nCount] = pID;
    // Set status: 1, Cargado.
    pList[pID].ProcessStatus = 1;
    // Notificar cambio
    //printf("L%i;", pID);
    printf("$%i %Lu %i;", pList[pID].Id, pList[pID].CurrentAddress, pList[pID].ProcessStatus);
    // Se incrementa el numero de procesos
    nCount++;
}

void UnLoadProcess(int pID, int index)
{
    // Se retira el proces0 de la Pila
    int i;
    for (i = index; i < nCount - 1; i++)
    {
        pStack[i] = pStack[i + 1];
    }
    // Set status: 1, Cargado.
    pList[pID].ProcessStatus = 0;
    // Reset
    pList[pID].CurrentAddress = pList[pID].StartAddress;
    // Notificar cambio

    // Apagar el sistema
    switch (pID)
    {
        case 0:

            break;
        case 1:
        {
            output_low(PIN_C0);
            output_low(PIN_D3);
            output_low(PIN_A2);
            output_low(PIN_A3);
            nCount--;
        }
            break;
        case 2:
        {
            output_b(0xff);
            nCount--;
        }
            break;
        case 3:
        {
            CCPR1L = 0x00;
            CCP5 = 0;
            CCP4 = 0;
            nCount--;
            break;
        }
        case 4:
        {
            output_low(PIN_D1);
            output_low(PIN_D2);
            output_low(PIN_D4);
            output_low(PIN_D5);
            output_low(PIN_D6);
            output_low(PIN_D7);
            nCount--;
        }
            break;
        case 5:
        {
            output_low(PIN_E0);
            output_low(PIN_E1);
            output_low(PIN_E2);
            nCount--;
        }
            break;
    }
    printf("$%i %Lu %i;", pList[pID].Id, pList[pID].CurrentAddress, pList[pID].ProcessStatus);


}

#ORG 0x4000, 0x4900

void OS()
{
    int command, process;

    while (TRUE)
    {
        output_toggle(PIN_D0);
        if (cmd != 0x00)
        {
            int gol;
            gol = 0;
            switch (cmd)
            {
                case '1':
                    gol = 1;
                    command = 1;
                    process = 1;
                    break;
                case '2':
                    gol = 1;
                    command = 1;
                    process = 2;
                    break;
                case '3':
                    gol = 1;
                    command = 1;
                    process = 3;
                    break;
                case '4':
                    gol = 1;
                    command = 1;
                    process = 4;
                    break;
                case '5':
                    gol = 1;
                    command = 1;
                    process = 5;
                    break;
                case 'A':
                    gol = 1;
                    command = 2;
                    process = 1;
                    break;
                case 'B':
                    gol = 1;
                    command = 2;
                    process = 2;
                    break;
                case 'C':
                    gol = 1;
                    command = 2;
                    process = 3;
                    break;
                case 'D':
                    gol = 1;
                    command = 2;
                    process = 4;
                    break;
                case 'E':
                    gol = 1;
                    command = 2;
                    process = 5;
                    break;
            }

            if (gol == 1)
            {
                switch (command)
                {
                    case 0:
                        cmd = 0x00;
                        break;
                        // Load
                    case 1:
                        cmd = 0x00;
                        // Proceso no cargado
                        if (IsLoaded(process) == -1)
                        {
                            LoadProcess(process);
                        }
                        break;
                        // UnLoad
                    case 2:
                        cmd = 0x00;
                        // Proceso cargado
                        int indexProcess = IsLoaded(process);
                        if (indexProcess != -1)
                        {
                            UnLoadProcess(process, indexProcess);
                        }
                        break;
                    case 3:
                        cmd = 0x00;
                        break;
                }
                cmd = 0x00;
            }
        }
        if (nCount > 0)
        {
            if (pList[pStack[0]].ProcessStatus == 1)
            {
                pList[pStack[0]].ProcessStatus = 2;
                enableQuantum();
                goto_address(pList[pStack[0]].StartAddress);

            }
            else if (pList[pStack[0]].ProcessStatus == 2)
            {
                status = pList[pStack[0]].RSTATUS;
                bsr = pList[pStack[0]].RBSR;
                wreg = pList[pStack[0]].RWREG;
                enableQuantum();
                goto_address(pList[pStack[0]].CurrentAddress);
            }
        }
    }
}



