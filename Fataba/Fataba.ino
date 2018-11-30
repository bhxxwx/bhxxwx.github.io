/*
For the FUTABA M11BT222A VFD display

Build by WangXiang

2018-11-30

接线示意图：

 1. VCC (+5V)
 2. GND
 3. NC
 4. EN
 5. DIN
 6. GND
 7. /SCL
 8. /STB

 */
#include <inttypes.h >
#include <Wire.h>
#include "DS3231.h"
#include <dht11.h>
RTClib RTC;
#define EN_PIN 5
#define DIN_PIN 6
#define CLK_PIN 7
#define STB_PIN 8
dht11 DHT11;
#define DHT11PIN 4
#define DODELAY __asm__("nop\n\t" \
                        "nop\n\t")

unsigned char M11BT222A_16seg_digit[] =
    {
        0x46, 0x31, // '0'
        0x10, 0x84, // '1'
        0x45, 0xD1, // '2'
        0x43, 0xD1, // '3'
        0x03, 0xF0, // '4'
        0x43, 0xE1, // '5'
        0x47, 0xE1, // '6'
        0x10, 0x89, //0x02, 0x11, // '7'
        0x47, 0xF1, // '8'
        0x43, 0xF1  // '9'
};

unsigned char M11BT222A_8seg_digit[] =
    {
        0x77, 0x12, 0x6B, 0x5B, 0x1E, 0x5D, 0x7D, 0x13, 0x7F, 0x5F};

unsigned char M11BT222A_8seg_pos[] =
    {
        0x00, 0x06, 0x07, 0x03, 0x04, 0x01};

unsigned char RoundTab[] = {0x01, 0x02, 0x04, 0x8, 0x10, 0x20, 0x40, 0x80}; //转盘one
unsigned char Fpoints[] = {0x01, 0x02, 0x04, 0x8, 0x04, 0x02, 0x01, 0x9};   //点
unsigned char SecdTab[] = {0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x81}; //转盘two

unsigned char MiDigi[] = {12, 9, 6, 3, 0};

unsigned char BOXUP[] = {0x01, 0x03, 0x02, 0x05, 0x015, 0x04, 0x07, 0x06, 0x08, 0x09, 0x10, 0x20, 0x90, 0x80};
unsigned char BOXDOWN[] = {0x01, 0x03, 0x02, 0x05, 0x015, 0x04, 0x07, 0x06, 0x08, 0x09, 0x10, 0x20, 0x90, 0x80};

uint16_t MiTab[] = {
    0x3146, 0x1002, 0xd145, 0xd143, 0xf003, 0xe143, 0xe147, 0x1102, //0,1,2,3,4,5,6,7
    0xf147, 0xf143, 0x0000, 0xc001, 0x8808, 0xf107, 0xd552, 0x2144, //8,9, ,-,/,A,B,C
    0x9552, 0xe145, 0xe105, 0x6146, 0xf007, 0x8550, 0x1046, 0xa825, //D,E,F,G,H,I,J,K
    0x2044, 0xba06, 0xb226, 0x3146, 0xf105, 0x3166, 0xf125, 0xe143, //L,M,N,O,P,Q,R,S
    0x8510, 0x3046, 0xa80c, 0xb02e, 0x8a28, 0x8a10, 0x8948, 0xc411, //T,U,V,W,X,Y,Z,+
    0x8000, 0x0040, 0x0220, 0xA101, 0xEA2B, 0x0808                  //.,_,\,¡æ,%,
};

#define ON 19
#define OFF 20

#define NUL 1
//底层驱动，指令代码
//#define FASTIO
#ifndef FASTIO
#define PTDinHigh digitalWrite(DIN_PIN, HIGH)
#define PTDinLow digitalWrite(DIN_PIN, LOW)
// !!!CLK and STB are INVERTED in the hardware!!! //
#define PTClkLow digitalWrite(CLK_PIN, HIGH)
#define PTClkHigh digitalWrite(CLK_PIN, LOW)
#define PTStbLow digitalWrite(STB_PIN, HIGH)
#define PTStbHigh digitalWrite(STB_PIN, LOW)
#endif

#define CMD1_DMSC_08_20 0x00
#define CMD1_DMSC_09_19 0x08
#define CMD1_DMSC_10_18 0x09
#define CMD1_DMSC_11_17 0x0A
#define CMD1_DMSC_12_16 0x0B
#define CMD1_DMSC_13_15 0x0C
#define CMD1_DMSC_14_14 0x0D
#define CMD1_DMSC_15_13 0x0E
#define CMD1_DMSC_16_12 0x0F

#define CMD2_DSC_WDDM_INC (0x40 | 0x00)
#define CMD2_DSC_WDDM_FIX (0x40 | 0x04)
#define CMD2_DSC_WDLP (0x40 | 0x01)
#define CMD2_DSC_RKD (0x40 | 0x02)
#define CMD2_DSC_RSD (0x40 | 0x03)

#define CMD3_ASC 0xC0

#define CMD3_DCC_01_16 (0x88 | 0)
#define CMD3_DCC_02_16 (0x88 | 1)
#define CMD3_DCC_04_16 (0x88 | 2)
#define CMD3_DCC_10_16 (0x88 | 3)
#define CMD3_DCC_11_16 (0x88 | 4)
#define CMD3_DCC_12_16 (0x88 | 5)
#define CMD3_DCC_13_16 (0x88 | 6)
#define CMD3_DCC_14_16 (0x88 | 7)
#define CMD3_DCC_OFF 0x80

uint16_t MiNEW[5] = {0, 0, 0, 0, 0};
uint16_t MiRAM[5] = {0, 0, 0, 0, 0};

static int choosemenu = 1; //中断计数

static byte p = 0, r = 0;                 //用于NETWORK转盘，圆盘单次执行计数
static int state[6] = {0, 1, 0, 0, 0, 0}; //用于程序切换

void pt6331_Init(unsigned char dispMode, unsigned char dispCtrl);

void pt6331_Write(unsigned char dat);
void pt6331_Cmd(unsigned char cmd);
void pt6331_SetMem(unsigned char dat);
void pt6331_WriteDigit(unsigned char digit, unsigned char s1, unsigned char s2, unsigned char s3);
void pt6331_WriteDisplayRam(unsigned char addr, unsigned char *data, unsigned char len);

void diaplayNumber(int seg, int number, unsigned char point);
void diaplayDisk1(int rounds, int speed);
void diaplayDisk2(int rounds, int speed);
void displayNet(int rounds, int speed);
void displayNEK();
void displayMU();
void displayUSB();
void displayCH();
void displayMi(unsigned char addr, uint16_t data);
void PT6311_MiStr(byte *ch);
void displayMCH(char ch[5]);
void diaplayRandom(int speed);
void diaplayRandomMi();
void show();
void MixNM();
void displayAUTO();
void displayTITLE();
void displayEPG();
void displayTRANS();
void displayMAIL();
void displayRATE();
void displayCHP();
void displayTRK();
void displayBOXUP(unsigned char locat);
void displayBOXDOWN(unsigned char locat);
void displayRanBOX();
void gettime(int ti[14]);
void displayNETround();
void displayROUNDstep();
void showREC(byte choose);
void showTIME();
void showTEMPER();
void showHUM();
void AutoMod();
void temper();
void humidity();
void datas();
void CHOOSE();
void getdate();
void tworoundstep();
void adc11();
void adc12();
void adc13();
void adc14();
void adc15();

void adc11()
{
    int temp;
    unsigned char lig[4];
    lig[0] = Fpoints[0] | Fpoints[1] | 0x00 | 0x40 | 0x10;
    lig[1] = Fpoints[0] | Fpoints[1] | Fpoints[2] | 0x00 | 0x40 | 0x10;
    lig[2] = Fpoints[0] | Fpoints[1] | Fpoints[2] | Fpoints[3] | 0x00 | 0x40 | 0x10;
    lig[4] = Fpoints[0] | 0x00 | 0x40 | 0x10;
    temp = analogRead(A1);
    if (500 < temp)
        pt6331_WriteDisplayRam(25, &lig[4], 1);
    if (temp <= 300)
        pt6331_WriteDisplayRam(25, &lig[2], 1);
    if (300 < temp && temp <= 400)
        pt6331_WriteDisplayRam(25, &lig[1], 1);
    if (400 < temp && temp <= 500)
        pt6331_WriteDisplayRam(25, &lig[0], 1);
    //Serial.println(temp);
}

void adc12()
{
    int temp;
    unsigned char lig[4];
    lig[0] = Fpoints[0] | Fpoints[1] | 0x00 | 0x80 | 0x10;
    lig[1] = lig[0] | Fpoints[2] | 0x00 | 0x80 | 0x10;
    lig[2] = lig[1] | Fpoints[3] | 0x00 | 0x80 | 0x10;
    lig[4] = Fpoints[0] | 0x00 | 0x80 | 0x10;
    temp = analogRead(A1);
    if (500 < temp)
        pt6331_WriteDisplayRam(25, &lig[4], 1);
    if (temp <= 300)
        pt6331_WriteDisplayRam(25, &lig[2], 1);
    if (300 < temp && temp <= 400)
        pt6331_WriteDisplayRam(25, &lig[1], 1);
    if (400 < temp && temp <= 500)
        pt6331_WriteDisplayRam(25, &lig[0], 1);
}

void adc13()
{
    int temp;
    unsigned char lig[4];
    lig[0] = Fpoints[0] | Fpoints[1] | 0x00 | 0x20 | 0x80;
    lig[1] = Fpoints[0] | Fpoints[1] | Fpoints[2] | 0x00 | 0x20 | 0x80;
    lig[2] = Fpoints[0] | Fpoints[1] | Fpoints[2] | Fpoints[3] | 0x00 | 0x20 | 0x80;
    lig[4] = Fpoints[0] | 0x00 | 0x20 | 0x80;
    temp = analogRead(A1);
    if (500 < temp)
        pt6331_WriteDisplayRam(25, &lig[4], 1);
    if (temp <= 300)
        pt6331_WriteDisplayRam(25, &lig[2], 1);
    if (300 < temp && temp <= 400)
        pt6331_WriteDisplayRam(25, &lig[1], 1);
    if (400 < temp && temp <= 500)
        pt6331_WriteDisplayRam(25, &lig[0], 1);
}

void adc14()
{
    int temp;
    unsigned char lig[4];
    lig[0] = Fpoints[0] | Fpoints[1] | 0x00 | 0x40 | 0x80;
    lig[1] = Fpoints[0] | Fpoints[1] | Fpoints[2] | 0x00 | 0x40 | 0x80;
    lig[2] = Fpoints[0] | Fpoints[1] | Fpoints[2] | Fpoints[3] | 0x00 | 0x40 | 0x80;
    lig[4] = Fpoints[0] | 0x00 | 0x40 | 0x80;
    temp = analogRead(A1);
    if (500 < temp)
        pt6331_WriteDisplayRam(25, &lig[4], 1);
    if (temp <= 300)
        pt6331_WriteDisplayRam(25, &lig[2], 1);
    if (300 < temp && temp <= 400)
        pt6331_WriteDisplayRam(25, &lig[1], 1);
    if (400 < temp && temp <= 500)
        pt6331_WriteDisplayRam(25, &lig[0], 1);
}

void adc15()
{
    int temp;
    unsigned char lig[4];
    lig[0] = Fpoints[0] | Fpoints[1] | 0x00 | 0x10 | 0x20;
    lig[1] = Fpoints[0] | Fpoints[1] | Fpoints[2] | 0x00 | 0x10 | 0x20;
    lig[2] = Fpoints[0] | Fpoints[1] | Fpoints[2] | Fpoints[3] | 0x00 | 0x10 | 0x20;
    lig[4] = Fpoints[0] | 0x00 | 0x10 | 0x20;
    temp = analogRead(A1);
    if (500 < temp)
        pt6331_WriteDisplayRam(25, &lig[4], 1);
    if (temp <= 300)
        pt6331_WriteDisplayRam(25, &lig[2], 1);
    if (300 < temp && temp <= 400)
        pt6331_WriteDisplayRam(25, &lig[1], 1);
    if (400 < temp && temp <= 500)
        pt6331_WriteDisplayRam(25, &lig[0], 1);
}

void tworoundstep()
{
    pt6331_WriteDisplayRam(24, &SecdTab[r], 1);
    r++;
    if (r == 8)
        r = 0;
}

void getdate()
{
    DateTime now = RTC.now();
    int h, m, s;
    h = now.year() - 2000;
    m = now.month();
    s = now.day();
    Serial.println(h);
    diaplayNumber(0, h / 10, ON);
    diaplayNumber(1, h % 10, ON);
    diaplayNumber(2, m / 10, ON);
    diaplayNumber(3, m % 10, ON);
    diaplayNumber(4, s / 10, ON);
    diaplayNumber(5, s % 10, ON);
}

void CHOOSE() //中断程序选择函数
{
    for (int i = 0; i < 30000;)
    {
        i++;
    }
    choosemenu++;
    if (choosemenu > 5)
        choosemenu = 1;
    switch (choosemenu)
    {
    case 1:
    {
        state[0] = 0;
        state[1] = 1;
        state[2] = 0;
        state[3] = 0;
        state[4] = 0;
        state[5] = 0;
    }
    break;
    case 2:
    {
        state[0] = 0;
        state[1] = 0;
        state[2] = 1;
        state[3] = 0;
        state[4] = 0;
        state[5] = 0;
    }
    break;
    case 3:
    {
        state[0] = 0;
        state[1] = 0;
        state[2] = 0;
        state[3] = 1;
        state[4] = 0;
        state[5] = 0;
    }
    break;
    case 4:
    {
        state[0] = 0;
        state[1] = 0;
        state[2] = 0;
        state[3] = 0;
        state[4] = 1;
        state[5] = 0;
    }
    break;
    case 5:
    {
        state[0] = 0;
        state[1] = 0;
        state[2] = 0;
        state[3] = 0;
        state[4] = 0;
        state[5] = 1;
    }
    break;
    }
}

void temper() //温度显示程序
{
    MixNM();
    displayUSB();
    displayMCH("TEMPE");
    diaplayNumber(0, 0, ON);
    diaplayNumber(1, 0, ON);
    diaplayNumber(2, 0, ON);
    diaplayNumber(3, 0, ON);
    diaplayNumber(4, 0, ON);
    diaplayNumber(5, 0, ON);
    displayTRANS();
    //displayCH();
    displayTITLE();
    //showREC(13);
    while (state[3])
    {
        if (millis() % 1000 == 0)
        {
            showTEMPER();
            //showHUM();
            adc13();
            displayNETround();
            //displayROUNDstep();
            tworoundstep();
            displayRanBOX();
        }
    }
}

void humidity() //湿度显示程序
{
    MixNM();
    displayUSB();
    displayMCH("HUMID");
    diaplayNumber(0, 0, ON);
    diaplayNumber(1, 0, ON);
    diaplayNumber(2, 0, ON);
    diaplayNumber(3, 0, ON);
    diaplayNumber(4, 0, ON);
    diaplayNumber(5, 0, ON);
    displayMAIL();
    //displayCH();
    displayTITLE();
    //showREC(14);
    while (state[4])
    {
        if (millis() % 1000 == 0)
        {
            //showTIME();
            showHUM();
            adc14();
            displayNETround();
            //displayROUNDstep();
            tworoundstep();
            displayRanBOX();
        }
    }
}

void datas() //日期显示程序
{
    MixNM();
    displayUSB();
    displayMCH("DATE");
    diaplayNumber(0, 0, ON);
    diaplayNumber(1, 0, ON);
    diaplayNumber(2, 0, ON);
    diaplayNumber(3, 0, ON);
    diaplayNumber(4, 0, ON);
    diaplayNumber(5, 0, ON);
    displayRATE();
    //displayCH();
    displayTITLE();
    //showREC(15);
    while (state[5])
    {
        if (millis() % 1000 == 0)
        {
            getdate();
            adc15();
            //showHUM();
            displayNETround();
            displayROUNDstep();
            displayRanBOX();
        }
        if (millis() % 5000 == 0)
        {
            //diaplayRandomMi();
            DS3231 Clock;
            //DateTime now = RTC.now();
            char week[5] = {'D', 'O', 'W', '_'}; //day of week
            week[4] = 48 + Clock.getDoW();
            displayMCH(&week[0]);
            displayRATE();
            displayTRK();
        }
    }
}

void AutoMod() //自动模式
{
    char au[5];
    MixNM();
    displayUSB();
    displayMCH("AUTO");
    diaplayNumber(0, 0, ON);
    diaplayNumber(1, 0, ON);
    diaplayNumber(2, 0, ON);
    diaplayNumber(3, 0, ON);
    diaplayNumber(4, 0, ON);
    diaplayNumber(5, 0, ON);
    displayAUTO();
    displayCH();
    displayTITLE();
    //showREC(11);
    while (state[1])
    {
        if (millis() % 1000 == 0)
        {
            adc11();
            //showREC(11);
            showTIME();
            displayNETround();
            displayROUNDstep();
            displayRanBOX();
        }
        if (millis() % 10000 == 0)
        {
            int chk = DHT11.read(DHT11PIN);
            int te, hu;
            showREC(111);
            MixNM();
            te = (int)DHT11.humidity;
            hu = (int)DHT11.temperature;
            au[0] = 48 + te / 10;
            au[1] = 48 + te % 10;
            au[2] = '_';
            au[3] = 48 + hu / 10;
            au[4] = 48 + hu % 10;
            displayMCH(&au[0]);
            displayCH();
            displayCHP();
            displayTRK();
        }
    }
}

void showHUM() //显示湿度
{
    int chk = DHT11.read(DHT11PIN);
    int h;
    h = (int)DHT11.humidity;
    //diaplayNumber(0, now.hour() / 10, ON);
    //diaplayNumber(1, now.hour() % 10, ON);
    diaplayNumber(2, h / 10, ON);
    diaplayNumber(3, h % 10, ON);
}

void showTEMPER() //显示温度
{
    int chk = DHT11.read(DHT11PIN);
    int t;
    t = (int)DHT11.temperature;
    //diaplayNumber(0, now.hour() / 10, ON);
    //diaplayNumber(1, now.hour() % 10, ON);
    diaplayNumber(2, t / 10, ON);
    diaplayNumber(3, t % 10, ON);
}
void showTIME() //显示时间
{
    DateTime now = RTC.now();
    int h, m, s;
    h = now.hour();
    m = now.minute();
    s = now.second();
    diaplayNumber(0, h / 10, ON);
    diaplayNumber(1, h % 10, ON);
    diaplayNumber(2, m / 10, ON);
    diaplayNumber(3, m % 10, ON);
    diaplayNumber(4, s / 10, ON);
    diaplayNumber(5, s % 10, ON);
}
void showREC(byte choose)
{
    unsigned char data = 0X00;
    switch (choose)
    {
    case 1:
        data = 0x00 | 0x20;
        break; //   REC-RIGHT
    case 2:
        data = 0x00 | 0x40;
        break; //   HDD
    case 3:
        data = 0x00 | 0x40 | 0x20;
        break; //   HDD&REC-RIGHT
    case 4:
        data = 0x00 | 0x80;
        break; //   REC-LEFT
    case 5:
        data = 0x00 | 0x10; //DVD
    case 11:
        data = 0x00 | 0x40 | 0x20;
        break;
    case 111:
        data = 0x00 | 0x40 | 0x10;
        break;
    case 12:
        data = 0x00 | 0x80 | 0x10;
        break;
    case 13:
        data = 0x00 | 0x20 | 0x80;
        break;
    case 14:
        data = 0x00 | 0x40 | 0x80;
        break;
    case 15:
        data = 0x00 | 0x10 | 0x20;
        break;
    }
    pt6331_WriteDisplayRam(25, &data, 1);
}
void displayROUNDstep() //圆盘单步执行
{
    pt6331_WriteDisplayRam(24, &RoundTab[r], 1);
    r++;
    if (r == 8)
        r = 0;
}
void displayNETround() //NETWORK转盘显示单步执行
{
    unsigned char n1, n2;
    n1 = (0x01 << p) | 0x80;
    n2 = (0x01 << p);
    pt6331_WriteDisplayRam(30, &n1, 1);
    pt6331_WriteDisplayRam(31, &n2, 1);
    p++;
    if (p == 7)
        p = 0;
}
void gettime(int ti[11]) //获取当前时间
{
    DateTime now = RTC.now();
    ti[0] = (now.year() - 2000) / 10;
    ti[1] = (now.year() - 2000) % 10;
    ti[2] = now.month() / 10;
    ti[3] = now.month() % 10;
    ti[4] = now.hour() / 10;
    ti[5] = now.hour() % 10;
    ti[6] = now.minute() / 10;
    ti[7] = now.minute() % 10;
    ti[8] = now.second() / 10;
    ti[9] = now.second() % 10;
}
void displayRanBOX() //矩阵方块乱序显示
{
    unsigned char x, y;
    x = random(0, 15);
    y = random(0, 15);
    pt6331_WriteDisplayRam(28, &BOXUP[x], 1);
    pt6331_WriteDisplayRam(27, &BOXDOWN[y], 1);
}
void displayBOXUP(unsigned char locat) //矩阵方块上半部分
{
    pt6331_WriteDisplayRam(28, &locat, 1);
}
void displayBOXDOWN(unsigned char locat) //矩阵方块下半部分
{
    pt6331_WriteDisplayRam(27, &locat, 1);
}
void displayCHP()
{
    unsigned char n = 0x01;
    pt6331_WriteDisplayRam(8, &n, 1);
}
void displayTRK()
{
    unsigned char n = 0x01;
    pt6331_WriteDisplayRam(5, &n, 1);
}
void displayEPG()
{
    unsigned char n = 0x01;
    pt6331_WriteDisplayRam(23, &n, 1);
}
void displayTRANS()
{
    unsigned char n = 0x01;
    pt6331_WriteDisplayRam(17, &n, 1);
}
void displayMAIL()
{
    unsigned char n = 0x01;
    pt6331_WriteDisplayRam(32, &n, 1);
}
void displayRATE()
{
    unsigned char n = 0x01;
    pt6331_WriteDisplayRam(11, &n, 1);
}
void displayTITLE()
{
    unsigned char n3;
    n3 = 0x01;
    pt6331_WriteDisplayRam(14, &n3, 1);
}
void displayAUTO()
{
    unsigned char n = 0x01;
    pt6331_WriteDisplayRam(20, &n, 1);
}
void MixNM() //米字与数字乱序显示，间隔30ms，耗时240ms
{
    int ran0, ran1, ran2, ran3, ran4, ran5;
    int Mran0, Mran1, Mran2, Mran3, Mran4;
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        Mran0 = random(13, 39);
        Mran1 = random(13, 39);
        Mran2 = random(13, 39);
        Mran3 = random(13, 39);
        Mran4 = random(13, 39);

        displayMi(4, MiTab[ran0]);
        displayMi(3, MiTab[ran1]);
        displayMi(2, MiTab[ran2]);
        displayMi(1, MiTab[ran3]);
        displayMi(0, MiTab[ran4]);

        ran0 = random(1, 10);
        ran1 = random(1, 10);
        ran2 = random(1, 10);
        ran3 = random(1, 10);
        ran4 = random(1, 10);
        ran5 = random(1, 10);
        diaplayNumber(0, ran0, ON);
        diaplayNumber(1, ran1, ON);
        diaplayNumber(2, ran2, ON);
        diaplayNumber(3, ran3, ON);
        diaplayNumber(4, ran4, ON);
        diaplayNumber(5, ran5, ON);
        delay(30);
    }
}
void show() //示例程序->时间显示程序
{
    unsigned long times;
    MixNM();
    displayUSB();
    displayMCH("CLOCK");
    diaplayNumber(0, 0, ON);
    diaplayNumber(1, 0, ON);
    diaplayNumber(2, 0, ON);
    diaplayNumber(3, 0, ON);
    diaplayNumber(4, 0, ON);
    diaplayNumber(5, 0, ON);
    displayEPG();
    displayCH();
    displayTITLE();
    //showREC(12);
    while (state[2])
    {
        times = millis();
        if (times % 1000 == 0)
        {
            showTIME();
            adc12();
            //showHUM();
            displayNETround();
            displayROUNDstep();
            displayRanBOX();
            //adc();
        }
    }
}
void diaplayRandomMi() //米字乱序显示字母，耗时290ms
{
    int ran0, ran1, ran2, ran3, ran4;
    int i = 0, q;
    for (i = 0; i < 8; i++)
    {
        ran0 = random(13, 39);
        ran1 = random(13, 39);
        ran2 = random(13, 39);
        ran3 = random(13, 39);
        ran4 = random(13, 39);
        displayMi(4, MiTab[ran0]);
        displayMi(3, MiTab[ran1]);
        displayMi(2, MiTab[ran2]);
        displayMi(1, MiTab[ran3]);
        displayMi(0, MiTab[ran4]);
        delay(30);
    }
    delay(50);
}

void diaplayRandomNumber(int speed) //数字乱序显示，耗时6*(speed+20)ms
{
    int ran0, ran1, ran2, ran3, ran4, ran5;
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        ran0 = random(1, 10);
        ran1 = random(1, 10);
        ran2 = random(1, 10);
        ran3 = random(1, 10);
        ran4 = random(1, 10);
        ran5 = random(1, 10);
        diaplayNumber(0, ran0, ON);
        diaplayNumber(1, ran1, ON);
        diaplayNumber(2, ran2, ON);
        diaplayNumber(3, ran3, ON);
        diaplayNumber(4, ran4, ON);
        diaplayNumber(5, ran5, ON);
        delay(speed + 20);
    }
    ran0 = random(0, 10);
    ran1 = random(0, 10);
    ran2 = random(0, 10);
    ran3 = random(0, 10);
    ran4 = random(0, 10);
    ran5 = random(0, 10);
    diaplayNumber(0, ran0, ON);
    diaplayNumber(1, ran1, ON);
    diaplayNumber(2, ran2, ON);
    diaplayNumber(3, ran3, ON);
    diaplayNumber(4, ran4, ON);
    diaplayNumber(5, ran5, ON);
    delay(speed + 20);
}

void displayMCH(char ch[5]) //米字字符串显示
{
    int i, j = 0;
    PT6311_MiStr(&ch[0]);
    for (i = 4; i >= 0; i--)
    {
        displayMi(i, MiNEW[j]);
        j++;
    }
}

void PT6311_MiStr(byte *ch) //米字字符串显示字符处理函数
{
    byte i = 0;
    for (i = 0; i < 5; i++)
    {
        if (ch[i] >= 'A' && ch[i] <= 'Z')
            MiNEW[i] = MiTab[ch[i] - 52];
        else if (ch[i] >= '0' && ch[i] <= '9')
            MiNEW[i] = MiTab[ch[i] - 48];
        else if (ch[i] == '_')
            MiNEW[i] = MiTab[41];
        else
            MiNEW[i] = 0;
    }
}

void displayMi(unsigned char addr, uint16_t data) //米字显示,addr->位数选择,data->显示的数据
{
    unsigned char data1 = data >> 8;
    unsigned char data2 = data;
    pt6331_WriteDigit(addr, data1, data2, 20);
}

void displayCH() //CH
{
    unsigned char data = 0x01;
    pt6331_WriteDisplayRam(2, &data, 1);
}

void displayUSB() //USB
{
    unsigned char n;
    n = 0xFF;
    pt6331_WriteDisplayRam(29, &n, 1);
}

void displayNEK() //NETWORK
{
    unsigned char n;
    n = 0x80;
    pt6331_WriteDisplayRam(30, &n, 1);
}
void displayMU() //MUSIC
{
    unsigned char n;
    n = 0x80;
    pt6331_WriteDisplayRam(31, &n, 1);
}

void displayNet(int rounds, int speed) //NETWORK转盘显示,round->圈数,speed->速度
{
    int i = 0;
    for (; i < rounds; i++)
    {
        int p = 0;
        unsigned char n;
        for (; p < 7; p++)
        {
            n = (0x01 << p);
            pt6331_WriteDisplayRam(30, &n, 1);
            pt6331_WriteDisplayRam(31, &n, 1);
            delay(speed);
        }
    }
}

void diaplayDisk2(int rounds, int speed) //转盘2色块旋转,round->圈数,speed->速度
{
    int i = 0;
    for (; i < rounds; i++)
    {
        int p = 0;
        for (; p < 8; p++)
        {
            pt6331_WriteDisplayRam(24, &SecdTab[p], 1);
            delay(speed);
        }
    }
}

void diaplayDisk1(int rounds, int speed) //转盘单色块旋转,round->圈数,speed->速度
{
    int i = 0;
    for (; i < rounds; i++)
    {
        int p = 0;
        for (; p < 8; p++)
        {
            pt6331_WriteDisplayRam(24, &RoundTab[p], 1);
            pt6331_WriteDisplayRam(25, &Fpoints[p], 1);
            delay(speed);
        }
    }
}

void diaplayNumber(int seg, int number, unsigned char point) //显示数字，seg->位数选择,number->数字,point->是否显示小数点
{
    unsigned char swpoint;
    switch (point)
    {
    case 19:
    {
        swpoint = (M11BT222A_8seg_digit[number] | (0x80 & 0xff));
        pt6331_WriteDisplayRam(15 + M11BT222A_8seg_pos[seg], &swpoint, 1); // light up some segment
    }
    break;
    case 20:
        pt6331_WriteDisplayRam(15 + M11BT222A_8seg_pos[seg], &M11BT222A_8seg_digit[number], 1);
        break;
    case 1:
    {
        swpoint = (0x80 & 0xff);
        pt6331_WriteDisplayRam(15 + M11BT222A_8seg_pos[seg], &swpoint, 1);
    }
    }
}

void pt6331_Write(unsigned char dat)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        PTClkLow;
        if (dat & 0x01)
            PTDinHigh;
        else
            PTDinLow;
        dat >>= 1;
        //DODELAY;
        PTClkHigh;
        DODELAY;
    }
}

void pt6331_Cmd(unsigned char cmd)
{
    PTStbLow;
    //DODELAY;
    pt6331_Write(cmd);
    PTStbHigh;
    DODELAY;
}

void pt6331_SetMem(unsigned char dat)
{
    unsigned char i;
    pt6331_Cmd(CMD2_DSC_WDDM_INC);
    PTStbLow;
    pt6331_Write(CMD3_ASC);
    for (i = 0; i <= 0x2f; i++)
    {
        pt6331_Write(dat);
    }
    PTStbHigh;
    DODELAY;
}

void pt6331_WriteDigit(unsigned char digit, unsigned char s1, unsigned char s2, unsigned char s3)
{
    pt6331_Cmd(CMD2_DSC_WDDM_INC);
    PTStbLow;
    pt6331_Write(CMD3_ASC | (digit * 3));
    pt6331_Write(s1);        //SG1-SG4 SG5-SG8
    pt6331_Write(s2);        //SG9-SG12 SG13-SG16
    pt6331_Write(s3 & 0x0f); //SG17-SG20
    PTStbHigh;
    DODELAY;
}

void pt6331_WriteDisplayRam(unsigned char addr, unsigned char *data, unsigned char len)
{
    pt6331_Cmd(CMD2_DSC_WDDM_INC);
    PTStbLow;
    pt6331_Write(CMD3_ASC | addr);
    while (len--)
    {
        pt6331_Write(*data++);
    }
    PTStbHigh;
    DODELAY;
}

void pt6331_Init(unsigned char dispMode, unsigned char dispCtrl)
{
    PTStbHigh;
    PTClkHigh;
    PTDinHigh;
    DODELAY;
    pt6331_SetMem(0x00);
    pt6331_Cmd(dispMode);
    pt6331_Cmd(dispCtrl);
}

void setup()
{
    Serial.begin(9600);
    digitalPinToInterrupt(0);
    attachInterrupt(0, CHOOSE, RISING);
    Wire.begin();
    pinMode(DIN_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT);
    pinMode(STB_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, HIGH); // 使能
    delay(200);
    pt6331_Init(CMD1_DMSC_11_17, CMD3_DCC_04_16);
    pt6331_SetMem(0x00); // 清屏
}

void loop()
{
    AutoMod();
    pt6331_SetMem(0x00);
    show();
    pt6331_SetMem(0x00);
    temper();
    pt6331_SetMem(0x00);
    humidity();
    pt6331_SetMem(0x00);
    datas();
}