#include "includes.h"

#define BOTH_EMPTY (UART_LS_TEMT | UART_LS_THRE)

#define WAIT_FOR_XMITR \
        do { \
                lsr = REG8(UART_BASE + UART_LS_REG); \
        } while ((lsr & BOTH_EMPTY) != BOTH_EMPTY)

#define WAIT_FOR_THRE \
        do { \
                lsr = REG8(UART_BASE + UART_LS_REG); \
        } while ((lsr & UART_LS_THRE) != UART_LS_THRE)

#define TASK_STK_SIZE 512	//256

OS_STK TaskStartStk[TASK_STK_SIZE];

char Info[100] = "\nPlay Rock-Scissor-Paper with Computer!\n  @Author: 1952100 Ray\n  @Mail: rayhuc@163.com\n";

void uart_init(void)
{
	INT32U divisor;

	/* Set baud rate */

	divisor = (INT32U) IN_CLK/(16 * UART_BAUD_RATE);

	REG8(UART_BASE + UART_LC_REG) = 0x80;
	REG8(UART_BASE + UART_DLB1_REG) = divisor & 0x000000ff;
	REG8(UART_BASE + UART_DLB2_REG) = (divisor >> 8) & 0x000000ff;
	REG8(UART_BASE + UART_LC_REG) = 0x00;
	
	
	/* Disable all interrupts */
	
	REG8(UART_BASE + UART_IE_REG) = 0x00;
	

	/* Set 8 bit char, 1 stop bit, no parity */
	
	REG8(UART_BASE + UART_LC_REG) = UART_LC_WLEN8 | (UART_LC_ONE_STOP | UART_LC_NO_PARITY);
	

	// uart_print_str("UART initialize done ! \n");
	return;
}

void uart_putc(char c)
{
	unsigned char lsr;
	WAIT_FOR_THRE;
	REG8(UART_BASE + UART_TH_REG) = c;
	if(c == '\n') {
		WAIT_FOR_THRE;
		REG8(UART_BASE + UART_TH_REG) = '\r';
	}
	WAIT_FOR_XMITR;  
}

void uart_print_str(char* str)
{
	INT32U i=0;
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL()
	
	while(str[i]!=0)
	{
		uart_putc(str[i]);
		i++;
	}
	
	OS_EXIT_CRITICAL()
}

void gpio_init()
{
	REG32(GPIO_BASE + GPIO_OE_REG) = 0xffffffff;
	REG32(GPIO_BASE + GPIO_INTE_REG) = 0x00000000;
	gpio_out(0x0f0f0f0f);
	// uart_print_str("GPIO initialize done ! \n");
    return;
}

void gpio_out(INT32U number)
{
	REG32(GPIO_BASE + GPIO_OUT_REG) = number;
}

INT32U gpio_in()
{
	INT32U temp = 0;

    temp = REG32(GPIO_BASE + GPIO_IN_REG);

	return temp;
}

/*******************************************
   
    ÉèÖÃcompareŒÄŽæÆ÷£¬²¢ÇÒÊ¹ÄÜÊ±ÖÓÖÐ¶Ï    

********************************************/
void OSInitTick(void)
{
    INT32U compare = (INT32U)(IN_CLK / OS_TICKS_PER_SEC);
    
    asm volatile("mtc0   %0,$9"   : :"r"(0x0)); 
    asm volatile("mtc0   %0,$11"   : :"r"(compare));  
    asm volatile("mtc0   %0,$12"   : :"r"(0x10000401));
    //uart_print_str("OSInitTick Done!!!\n");
    
    return; 
}

void  TaskStart (void *pdata)
{
    INT32U count = 0;
    pdata = pdata;            /* Prevent compiler warning                 */
	OSInitTick();	      	/* don't put this function in main()*/

	// Program START       
    for (;;) {
		// 输出游戏规则和说明->存到 Info[] 里, GBK编码
    	if(count <= 100) {
        	uart_putc(Info[count]);
        	uart_putc(Info[count+1]);
        }
        // 玩游戏
        else {
            INT32U data;
            data = gpio_in();
            INT32U ready = data << 31;
            INT32U choice = data >> 1;

            if(ready) { //用户开始->按下N17
                //闪灯提示
                uart_print_str("\n");
                gpio_out(0x80000000);

                //获得用户输入
                INT32U u_stone = choice & 0x00000004;
                INT32U u_scissor = choice & 0x00000002;
                INT32U u_paper = choice & 0x00000001;

                //输出用户选择
                INT32U gamer = 0;
                if(u_stone) {
                    gamer = 2;
                    uart_print_str("- Play:\n   (You)Rock vs ");
                }
                else if(u_scissor) {
                    gamer = 0;
                    uart_print_str("- Play:\n   (You)Scissor vs ");
                }
                else {
                    gamer = 1;
                    uart_print_str("- Play:\n   (You)Paper vs ");
                }

                //电脑选择
                INT32U computer = 0;
                INT32U c_stone = (count & 0x00000004)>>1;
                INT32U c_scissor = (count & 0x00000002)>>1;
                if(c_scissor) {
                    computer = 1;
                    uart_print_str("Scissor(Computer)\n");
                }
                else if(c_stone) {
                    computer = 2;
                    uart_print_str("Rock(Computer)\n");
                }
                else {
                    computer = 0;
                    uart_print_str("Paper(Computer)\n");
                }

                //输出结果
                INT32U result = gamer + computer;
                if (result == 2) {
                    uart_print_str("   @ Computer Won.\n");
                }
                else if (result == 3) {
                    uart_print_str("   @ You Won!!!\n");
                }
                else if (result == 0) {
                    uart_print_str("   @ You Won!!!\n");
                }
                else {
                    uart_print_str("   @ Tied.\n");
                }

            }
            else {
                gpio_out(0x00010000);
            }
        }

    	count = count + 2;
        OSTimeDly(10);
    }
}

void main()
{
	OSInit();
  
  	uart_init();
  
  	gpio_init();	
  
  	OSTaskCreate(TaskStart, 
	    (void *)0, 
	    &TaskStartStk[TASK_STK_SIZE - 1], 
	    0);
  
  	OSStart();
}