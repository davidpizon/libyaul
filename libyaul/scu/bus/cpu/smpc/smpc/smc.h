/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#ifndef _SMPC_SMC_H_
#define _SMPC_SMC_H_

#include <sys/cdefs.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern uint8_t smpc_smc_cdoff_call(void);
extern uint8_t smpc_smc_cdon_call(void);
extern uint8_t smpc_smc_ckchg320_call(void);
extern uint8_t smpc_smc_ckchg352_call(void);
extern uint8_t smpc_smc_intback_call(uint8_t, uint8_t);
extern uint8_t smpc_smc_mshon_call(void);
extern uint8_t smpc_smc_nmireq_call(void);
extern uint8_t smpc_smc_resdisa_call(void);
extern uint8_t smpc_smc_resenab_call(void);
extern uint8_t smpc_smc_setsmem_call(void);
extern uint8_t smpc_smc_sndoff_call(void);
extern uint8_t smpc_smc_sndon_call(void);
extern uint8_t smpc_smc_sshoff_call(void);
extern uint8_t smpc_smc_sshon_call(void);
extern void smpc_smc_sysres_call(void) __noreturn;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_SMPC_SMC_H_ */
