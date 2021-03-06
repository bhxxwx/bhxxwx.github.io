/*
 * IIC.c
 *
 *  Created on: 2018年7月12日
 *      Author: Wang Xiang
 *
 *  MSP430F5529类Arduino库文件
 */
#include <IIC.h>
#include <msp430.h>
//字库
unsigned char F8X16[95][16]=
{
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xCC,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00},/*"!",1*/
{0x00,0x00,0x08,0x00,0x30,0x00,0x60,0x00,0x08,0x00,0x30,0x00,0x60,0x00,0x00,0x00},/*""",2*/
{0x02,0x20,0x03,0xFC,0x1E,0x20,0x02,0x20,0x03,0xFC,0x1E,0x20,0x02,0x20,0x00,0x00},/*"#",3*/
{0x00,0x00,0x0E,0x18,0x11,0x04,0x3F,0xFF,0x10,0x84,0x0C,0x78,0x00,0x00,0x00,0x00},/*"$",4*/
{0x0F,0x00,0x10,0x84,0x0F,0x38,0x00,0xC0,0x07,0x78,0x18,0x84,0x00,0x78,0x00,0x00},/*"%",5*/
{0x00,0x78,0x0F,0x84,0x10,0xC4,0x11,0x24,0x0E,0x98,0x00,0xE4,0x00,0x84,0x00,0x08},/*"&",6*/
{0x08,0x00,0x68,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xE0,0x18,0x18,0x20,0x04,0x40,0x02,0x00,0x00},/*"(",8*/
{0x00,0x00,0x40,0x02,0x20,0x04,0x18,0x18,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},/*")",9*/
{0x02,0x40,0x02,0x40,0x01,0x80,0x0F,0xF0,0x01,0x80,0x02,0x40,0x02,0x40,0x00,0x00},/*"*",10*/
};
//字库
unsigned int F6x8[][6]=
{
 {0x00,0x00,0x05,0x03,0x00,0x00},
 { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, //sp0
     { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 }, // !1
     { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 }, // "2
     { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 }, // #3
     { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, // $4
     { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 }, // %5
     { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 }, // &6
     { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 }, // '7
     { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 }, // (8
     { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 }, // )9
     { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 }, // *10
     { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 }, // +11
     { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 }, // ,12
     { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 }, // -13
     { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 }, // .14
     { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 }, // /15
     { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 016
     { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 117
     { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 }, // 218
     { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 }, // 319
     { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 420
     { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 }, // 521
     { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 }, // 622
     { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 }, // 723
     { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 }, // 824
     { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E }, // 925
     { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 }, // :26
     { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 }, // ;27
     { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 }, // <28
     { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 }, // =29
     { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 }, // >30
     { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 }, // ?31
     { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E }, // @32
     { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C }, // A33
     { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 }, // B34
     { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 }, // C35
     { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C }, // D36
     { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 }, // E37
     { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 }, // F38
     { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A }, // G39
     { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F }, // H40
     { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 }, // I41
     { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 }, // J42
     { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 }, // K43
     { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 }, // L44
     { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F }, // M45
     { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F }, // N46
     { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E }, // O47
     { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 }, // P48
     { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E }, // Q49
     { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 }, // R50
     { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 }, // S51
     { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 }, // T52
     { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F }, // U53
     { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F }, // V54
     { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F }, // W55
     { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 }, // X56
     { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 }, // Y57
     { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 }, // Z58
     { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 }, // [59
     { 0x00, 0x02, 0x04, 0x08, 0x10, 0x20 }, // \60
     { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 }, // ]61
     { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 }, // ^62
     { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 }, // _63
     { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 }, // '64
     { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 }, // a65
     { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 }, // b66
     { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 }, // c67
     { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F }, // d68
     { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 }, // e69
     { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 }, // f70
     { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C }, // g71
     { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 }, // h72
     { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 }, // i73
     { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 }, // j74
     { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 }, // k75
     { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 }, // l76
     { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 }, // m77
     { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 }, // n78
     { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 }, // o79
     { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 }, // p80
     { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC }, // q81
     { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 }, // r82
     { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 }, // s83
     { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 }, // t84
     { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C }, // u85
     { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C }, // v86
     { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C }, // w87
     { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 }, // x88
     { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C }, // y89
     { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 }, // z90
     { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 } // horiz lines91
};



void IIC_delayus(unsigned int i)
{
  unsigned int j,k;
  for(k=0;k<i;k++)
    for(j=0;j<4;i++);
}


//IIC初始化函数
void IIC_ioinit()
{
  P6DIR|=BIT1|BIT2|BIT3|BIT4; //配置IIC IO口为输出方向
  P6REN|=BIT3|BIT4; //配置IIC IO口使能上拉电阻
  P6OUT&=~BIT1;//6.1 拉高
  P6OUT|=BIT2;//6.2 拉低
}


//开始一个IIC通信
void IIC_start()
{
    //产生信号上升沿
   SCL_HIGH;//SCL拉高
   SDA_HIGH;//SDA拉高
//接下来产生SDA信号下降沿，注意，这里SDA一定比SCL先拉低
   //IIC_delayus(2);
   SDA_LOW;//SDA拉低
   //IIC_delayus(2);
   SCL_LOW;//SCL拉低
//主机开始读写信号产生完毕
}


//停止IIC通信
void IIC_stop()
{
     SCL_LOW;
     SDA_LOW;
     //IIC_delayus(2);
//接下来产生SDA信号上升沿，注意，这里SCL一定比SDA先拉高
     SCL_HIGH;
     SDA_HIGH;
     //IIC_delayus(2);
}


//IIC发送一个byte
void IIC_writebyte(unsigned char IIC_byte)
{
   unsigned char i;
//一个字节8bit因此，循环从0开始到7共8次写数据
   for(i=0;i<8;i++)
   {
      if(IIC_byte&0x80)  //如果写满8字节且不为0
        SDA_HIGH;//拉高SDA信号
      else//没有写满8字节
        SDA_LOW;//写入0
      SCL_HIGH;//拉高SCL结束一bit的写
      SCL_LOW;//拉低SCL使得SDA可写
      IIC_byte<<=1;   //IIC_byte左移一位，故名思意了
//假设IIC_byte数据为字符c 那么它的二进制就是01100011写入寄存器就是
//第一遍循环11000110
//第二遍循环10001100
//第三遍循环00011000
//第四遍循环00110000
//第五遍循环01100000
//第六遍循环11000000
//第七遍循环10000000
//第八遍循环00000000 全为0拉高SDA
   }
   SDA_HIGH;//恢复拉高SDA
   SCL_HIGH;//恢复拉高SCL
   SCL_LOW;//拉低SCL等待SDA电平变动
}


void IIC_writecmd(unsigned char IIC_command)
{
   IIC_start();
   IIC_writebyte(0x78);   //Slave address,SA0=0 从机寄存器地址
   IIC_writebyte(0x00);   //发送指令写指令
   IIC_writebyte(IIC_command);//写入指令
   IIC_stop();//结束IIC通信
}


void IIC_writedata(unsigned char IIC_data)
{
    IIC_start();
    IIC_writebyte(0x78);   //IIC写从机起始地址
    IIC_writebyte(0x40);   //write data写数据
    IIC_writebyte(IIC_data);//写入字符数据
    IIC_stop();
}


/**************************LCD 设置坐标*******************************/
void LCD_Set_Pos(unsigned char x, unsigned char y)
{
//OLED寄存器指令集查看OLED芯片手册
    IIC_writecmd(0xb0+y);
    IIC_writecmd(((x&0xf0)>>4)|0x10);
    IIC_writecmd((x&0x0f)|0x01);
}


/***************************LCD复位************************************/
void LCD_CLS(void)
{
  unsigned char y,x;
  for(y=0;y<8;y++)
  {
    IIC_writecmd(0xb0+y);
    IIC_writecmd(0x01);
    IIC_writecmd(0x10);
    for(x=0;x<X_WIDTH;x++)
    IIC_writedata(0);
   }
}


/***************************LCD初始化************************************/
void LCD_Init(void)
{
  IIC_ioinit();
  IIC_writecmd(0xAE);   //display off
  IIC_writecmd(0x20); //Set Memory Addressing Mode
  IIC_writecmd(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
  IIC_writecmd(0xb0); //Set Page Start Address for Page Addressing Mode,0-7
  IIC_writecmd(0xc8); //Set COM Output Scan Direction
  IIC_writecmd(0x00);//---set low column address
  IIC_writecmd(0x10);//---set high column address
  IIC_writecmd(0x40);//--set start line address
  IIC_writecmd(0x81);//--set contrast control register
  IIC_writecmd(0x7f);
  IIC_writecmd(0xa1);//--set segment re-map 0 to 127
  IIC_writecmd(0xa6);//--set normal display
  IIC_writecmd(0xa8);//--set multiplex ratio(1 to 64)
  IIC_writecmd(0x3F);//
  IIC_writecmd(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
  IIC_writecmd(0xd3);//-set display offset
  IIC_writecmd(0x00);//-not offset
  IIC_writecmd(0xd5);//--set display clock divide ratio/oscillator frequency
  IIC_writecmd(0xf0);//--set divide ratio
  IIC_writecmd(0xd9);//--set pre-charge period
  IIC_writecmd(0x22); //
  IIC_writecmd(0xda);//--set com pins hardware configuration
  IIC_writecmd(0x12);
  IIC_writecmd(0xdb);//--set vcomh
  IIC_writecmd(0x20);//0x20,0.77xVcc
  IIC_writecmd(0x8d);//--set DC-DC enable
  IIC_writecmd(0x14);//
  IIC_writecmd(0xaf);//--turn on oled panel
  LCD_CLS();
  LCD_Set_Pos(0,0);
}


//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/12


void LCD_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size)
{
  unsigned char c=0,i=0;
  c=chr-' ';//得到偏移后的值
  if(x>Max_Column-1)//如果，字符坐标大于行最大像素值写到下一行开始位置
  {
     x=0;
     y=y+2;
  }
  if(Char_Size ==16)//如果字符刚好等于16字符
  {
     LCD_Set_Pos(x,y);
     for(i=0;i<8;i++)
     IIC_writedata(F8X16[c*16+i]);
     LCD_Set_Pos(x,y+1);
     for(i=0;i<8;i++)
     IIC_writedata(F8X16[c*16+i+8]);
   }

   else //否则写到下一行
   {
     LCD_Set_Pos(x,y);
     for(i=0;i<6;i++)
     IIC_writedata(F6x8[c][i]);

   }

}


/*
void LCD_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char size)
{
    unsigned char temp,t,t1;
    unsigned char y0=y;
    unsigned char csize=(size/8+((size%8)?1:0))*(size/2);//字符对应点阵字节数
    chr=chr-' ';//得到在字库码表中的位置索引

    for(t=0;t<16;t++)
    {
        if(size==16)
            temp=asc2_1608[chr][t]; // 1608字体
        else
            return;                 // 未匹配到字库-放弃

        //画点

        for(t1=0;t1<8;t1++)
                {
                    if(temp&0x80)
                    {
                        LCD_Set_Pos(x,y);
                        IIC_writedata(0x00);
                    }
                    else
                    {
                        LCD_Set_Pos(x,y);
                        IIC_writedata(0x80);
                    }

                    temp<<=1;
                    y++;

                    //判断是否画到了最底部 - 如1206,到达底部后,当前字节未画完,换新列继续画
                    if((y-y0)==size)
                    {
                        y=y0;
                        x++;
                        break;
                    }

                }

        }


 }

*/

//显示一个字符号串
void LCD_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char Char_Size)
{
   unsigned char j=0;
   while (chr[j]!='\0')//遍历字符串，x+8相当于每个字符间隔8个坐标 循环调用显示字符函数，直到字符串为空
   {
     LCD_ShowChar(x,y,chr[j],Char_Size);
     x+=8;
     if(x>128)
     {
       x=0;
       y+=2;
     }
     j++;
   }
}

//m^n函数
unsigned long oled_pow(unsigned char m,unsigned char n)
{
    unsigned long result=1;
    while(n--)result*=m;
    return result;
}



//显示一个数字将数字取模获取每一位的数字，以字符的形式显示
//当输入数字为9876时坐标为0,0时
//取得每一位数
//第一遍循环 9876%10=987 余6 6+'0'='6' 坐标 x=0 y=0
//第二遍循环 987%10=98 余7 7+'0'='7‘ 坐标 x=0+8=8 y=0
//第三遍循环 98%10=9 余6 6+'0'='7' 坐标 x=8+8=16 y=0
//第四遍循环 9%10=0 余9 9+'0'='9' 坐标 x=16+8=24 y=0
//其他以此类推
void LCD_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size2)
{
    unsigned char t,temp;
    //unsigned char enshow=0;
    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        LCD_ShowChar(x+(size2/2)*t,y,temp+'0',size2);

    }
}



