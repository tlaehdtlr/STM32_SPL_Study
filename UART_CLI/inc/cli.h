#ifndef __CLI_H
#define __CLI_H

/**
 * @brief
 * command line interface
*/

#include "stm32f0xx_conf.h"
// void cli_
// void cli_init(void);

void shell_process_command_interactive(uint8_t cmd_ch);

#endif /* __CLI_H */