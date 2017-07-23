#ifndef __APP_TIMER_HAL_BURTC_H__
#define __APP_TIMER_HAL_BURTC_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include "string.h"

#include "ecode.h"

#ifdef __cplusplus
extern "C" {
#endif


//���⺯���ӿ�
void hal_burtc_over_flow_irq_process(void);
Ecode_t hal_burtc_init(void);
Ecode_t hal_burtc_deinit(void);


#ifdef __cplusplus
}
#endif

#endif