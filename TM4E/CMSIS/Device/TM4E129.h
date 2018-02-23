/**************************************************************************//**
 * @file     TM4E129.h
 * @brief    CMSIS Device System Header File for
 *           Texas Instruments Tiva TM4E129 Device Series
 * @version  V10956
 * @date     05. June 2013
 *
 * @note
 *
 ******************************************************************************/

#ifndef TM4E129_H
#define TM4E129_H

#if defined(TM4E129BNCZAD)
  #include "TM4E129BNCZAD.h"
#elif defined(TM4E129SNCZAD)
  #include "TM4E129SNCZAD.h"
#elif defined(TM4E129XNCZAD)
  #include "TM4E129XNCZAD.h"
#else
#error "TM4E129.h: TM4E129 Device NOT specified"
#endif

#endif /* TM4E129_H */
