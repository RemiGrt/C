
#ifndef __ADC_H
#define __ADC_H

#define ADC_VALUE_MAX      (0xFFF)

extern uint16_t AD_last;
extern uint8_t  AD_done;
extern uint16_t AD_ExpliciteValue;
extern void     ADC_Init_PA6    (void);
extern void     ADC_StartCnv(void);
extern void     ADC_StopCnv (void);
extern uint16_t ADC_GetCnv  (void);
extern int ADC_ReadyVerif(void);
extern float TensionExpliciteValue (void);
#endif
