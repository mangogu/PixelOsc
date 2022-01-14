#ifndef __BTNFUNC_H
#define __BTNFUNC_H

#define BACK				0
#define FORWARD			1
#define IMPORT			2
#define SAVE				3
#define INIT				4

char* MasterSrcRecall(uint8_t key,char* setting);
uint8_t shiftContext(uint8_t key, uint8_t curIndex, uint8_t num);

#endif
