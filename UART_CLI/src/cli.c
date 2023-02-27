/**
 * @brief
 * command line interface
*/

#include "cli.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CMD_BUF_MAX     256
#define SHELL_PROMPT    "\r\n>>> "
static char     l_p_cli_rx_buf[CMD_BUF_MAX];
static uint16_t l_w_rx_idx;

typedef struct
{
    char *cmd;                                          // Command
    void (*cmd_func)(uint8_t argc, void **argv);        // Function for command processing
    char *cmd_usage;                                    // Command usage
} cli_cmd_t;


static void sim_test(uint8_t argc, void **argv)
{
    char *command = argv[0];
    char *arg1 = argv[0 + strlen(command)];
    char *arg2 = argv[0 + strlen(command) + strlen(arg1)];
    char *arg3 = argv[0 + strlen(command) + strlen(arg1) + strlen(arg2)];

    if (argc == 1)
    {
        printf("sim argc 1 \r\n");

        return;
    }
    if (strcmp(arg1, "argu") == 0)
    {
        if (argc == 2)
        {
            printf("1st argument : %s \r\n", arg1);
        }
        else if (argc == 3)
        {
            printf("2nd argument : %s \r\n", arg2);
        }
        else if (argc == 4)
        {
            printf("3rd argument : %s \r\n", arg3);
        }
        else
        {
            printf("many arguments... \r\n");
        }
    }
}

const cli_cmd_t l_cli_cmds_t[] =
{
    {
        "sim", sim_test,
        "usage) argu [arg2] [arg3]\r\n \
                "
    },
    {
        (void *)0, (void *)0, (void *)0
    }
};

static uint8_t shell_get_command_index(char *cmd_str)
{
    int i = 0;

    for (i = 0; l_cli_cmds_t[i].cmd_func != 0; i++)
    {
        if (strcmp(cmd_str, l_cli_cmds_t[i].cmd) == 0)
        {
            break;
        }
    }

    return i;
}

static void shell_run_command(void)
{
    void *argv[128] = {0};
    int i = 0, idx = 0, argc = 0;
    char *cmd, *arg1;
    uint8_t cmd_idx;

    char *ptr = strtok(l_p_cli_rx_buf, " \r");

    while (ptr != NULL)
    {
        for (i = 0; i < strlen(ptr); i++)
            argv[idx++] = &ptr[i];

        ptr = strtok(NULL, " \r");
        argc++;
    }

    cmd = argv[0];
    arg1 = argv[0 + strlen(cmd)];

    cmd_idx = shell_get_command_index(cmd);

    if (l_cli_cmds_t[cmd_idx].cmd_func == 0)
    {
        printf("\r\nNo command found");
        return;
    }

    printf("\r\n");

    if (strcmp(arg1, "help") == 0)
    {
        printf("\r\n%-7s : %s", l_cli_cmds_t[cmd_idx].cmd, l_cli_cmds_t[cmd_idx].cmd_usage);
    }
    else
    {
        l_cli_cmds_t[cmd_idx].cmd_func(argc, argv);
    }

    /* clear command buffer */
    memset(l_p_cli_rx_buf, 0, sizeof(l_p_cli_rx_buf));
}

void shell_process_command_interactive(uint8_t cmd_ch)
{
    /* check cmd buffer full */
    if (l_w_rx_idx >= CMD_BUF_MAX)
    {
        l_w_rx_idx = 0;
        return;
    }

    /* check if valid character */
    if ((cmd_ch >= ' ') && (cmd_ch <= '~'))
    {
        l_p_cli_rx_buf[l_w_rx_idx++] = cmd_ch;

        printf("%c", cmd_ch);
    }

    /* delete if back space is pressed */
    if ((cmd_ch == '\b') && (l_w_rx_idx > 0))
    {
        l_w_rx_idx--;

        printf("\b\x1B[K");
    }

    /* display command if tab is pressed */
    if ((cmd_ch == '\t') && (l_w_rx_idx == 0))
    {
        unsigned char inc = 0;

        printf("\r\n");
        printf("commands :\r\n");

        for (inc = 0; l_cli_cmds_t[inc].cmd != 0; inc++)
        {
            printf(" %-10s", l_cli_cmds_t[inc].cmd);

            if ((inc + 1) % 5 == 0)
            {
                printf("\r\n");
            }
        }

        printf("\r\n");

        printf(SHELL_PROMPT);
    }

    /* do parsing command if input is enter key */
    if ((cmd_ch == '\r') || (cmd_ch == '\n'))
    {
        l_p_cli_rx_buf[l_w_rx_idx++] = cmd_ch;

        if (l_w_rx_idx > 1)
        {
            shell_run_command();
        }

        l_w_rx_idx = 0;

        printf(SHELL_PROMPT);
    }
}
