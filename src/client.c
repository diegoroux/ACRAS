
/*
 *  Copyright (c) 2022 Diego Roux.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  A program to automatically switch audio outputs.
 */

#include <cras_client.h>
#include <syslog.h>
#include <signal.h>
#include <getopt.h>
#include <errno.h>
#include <stdio.h>

#include "wcras.h"
#include "acpi.h"

#define VERSION_STRING  "0.1.0"

cras_ctx *ctx;
int acpi;

// Do a clean exit.
static void clean_exit(int status)
{
    wcras_destroy(ctx);
    acpi_listener_destroy(acpi);
    closelog();
    exit(status);
}

/*  systemd will try to kill us with SIGTERM. So we'll catch the signal and
 *  do clean exit. */
static void sigterm(int signum)
{
    clean_exit(0);
}

//  Fills node info for headphones and speaker.
static void get_nodes(cras_node *headphones, cras_node *speaker)
{
    int ret;

    ret = wcras_get_output_node(ctx, TYPE_HEADPHONE, headphones);

    if (ret <= 0) {
        ret = (ret == 0 ? ENXIO : -ret);
        syslog(LOG_ERR, "Unable to get headphones info: %s", strerror(ret));
        clean_exit(ret);
    }

    ret = wcras_get_output_node(ctx, TYPE_SPEAKER, speaker);

    if (ret <= 0) {
        ret = (ret == 0 ? ENXIO : -ret);
        syslog(LOG_ERR, "Unable to get speaker info: %s", strerror(ret));
        clean_exit(ret);
    }

    return;
}

static void set_output_node(cras_node *output)
{
    int ret;

    ret = wcras_select_node(ctx, CRAS_STREAM_OUTPUT, output);

    if (ret < 0) {
        syslog(LOG_ERR, "Unable to set output to %s: %s", output->name,
                strerror(-ret));
        clean_exit(-ret);
    }

    return;
}

static void parse_opt(int argc, const char **argv)
{
    struct option loptions[] = {
        {"version", no_argument, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };
    char c = 0;

    while (1) {

        c = getopt_long(argc, (char **)argv, "v", loptions, NULL);

        if (c == -1)
            break;

        switch (c) {
            case 'v':
                printf("acras v"VERSION_STRING"\n");
                exit(0);
            default:
                exit(1);
        }

    }

    return;
}

int main(int argc, const char **argv)
{
    cras_node headphones, speaker;
    struct sigaction action;
    int status, ret;

    // Parse argv.
    parse_opt(argc, argv);

    // Register handler for SIGTERM.
    memset(&action, 0x00, sizeof(struct sigaction));
    action.sa_handler = sigterm;
    sigaction(SIGTERM, &action, NULL);

    openlog("acras", LOG_PID, LOG_USER);

    ret = wcras_init(&ctx);

    if (ret < 0) {
        syslog(LOG_ERR, "Unable to create cras_client: %s", strerror(-ret));
        clean_exit(-ret);
    }

    // Get headphones and speaker info.
    get_nodes(&headphones, &speaker);

    // Set default output (speaker).
    set_output_node(&speaker);

    acpi = acpi_listener_create();

    if (acpi < 0) {
        syslog(LOG_ERR, "Unable to create ACPI listener: %s", strerror(-acpi));
        clean_exit(-acpi);
    }

    // Now we listen for ACPI events.
    while (1) {
        status = acpi_listen(acpi);

        if (status < 0) {
            syslog(LOG_ERR, "While listening for ACPI events: error: %s",
                    strerror(-status));
            clean_exit(-status);
        }

        if (status == UNPLUGGED) {
            set_output_node(&speaker);
        } else if (status == PLUGGED) {
            set_output_node(&headphones);
        }

    }

    return 0;
}
