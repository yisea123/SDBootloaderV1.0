#ifndef __DRIVE_OUTPUT_H
#define __DRIVE_OUTPUT_H


#define OUTPUT0 		GPIO_Pin_0
#define OUTPUT1 		GPIO_Pin_1
#define OUTPUT2 		GPIO_Pin_2
#define OUTPUT3 		GPIO_Pin_3
#define OUTPUT4 		GPIO_Pin_4
#define OUTPUT5 		GPIO_Pin_5
#define OUTPUT6 		GPIO_Pin_6
#define OUTPUT7 		GPIO_Pin_7
#define OUTPUT8 		GPIO_Pin_8
#define OUTPUT9 		GPIO_Pin_9
#define OUTPUT10 		GPIO_Pin_10
#define OUTPUT11 		GPIO_Pin_11
#define OUTPUT12		GPIO_Pin_12
#define OUTPUT13		GPIO_Pin_13
#define OUTPUT14		GPIO_Pin_14
#define OUTPUT15		GPIO_Pin_15

#define OUTPUT_PIN_MAP 				OUTPUT0 | OUTPUT1 | OUTPUT2 | OUTPUT3 | \
									OUTPUT4 | OUTPUT5 | OUTPUT6 | OUTPUT7 | \
									OUTPUT8 | OUTPUT9 | OUTPUT10 | OUTPUT11 | \
									OUTPUT12 | OUTPUT13 | OUTPUT14 | OUTPUT15
									
	
#define DOOR_0 PFout(0)		
#define DOOR_1 PFout(1)	
#define DOOR_2 PFout(2)	
#define DOOR_3 PFout(3)	
#define DOOR_4 PFout(4)	
#define DOOR_5 PFout(5)	
#define DOOR_6 PFout(6)	
#define DOOR_7 PFout(7)	
#define DOOR_8 PFout(8)	
#define DOOR_9 PFout(9)		
#define DOOR_10 PFout(10)	
#define DOOR_11 PFout(11)	

#define COUNT_COMPLETE 	PFout(12)	
#define VIBRATE_SWITCH 	PFout(13)
#define PRE_COUNT_FLAG 	PFout(14)
#define REJECT_FLAG 	PFout(15)


void drive_io_init (void);




#endif

 
