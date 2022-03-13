
/*
 *  Copyright (c) 2022 Diego Roux.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  Parse ACPI events.
 */

#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

#include "acpi.h"

#define ACPI_SOCK "/run/acpid.socket"

// Establish a connection to ACPI_SOCK.
int acpi_listener_create(void)
{
    struct sockaddr_un addr;
    int sock, ret;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    if (sock < 0)
        return sock;

    memset(&addr, 0x00, sizeof(struct sockaddr_un));

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, ACPI_SOCK, 18);

    ret = connect(sock, (const struct sockaddr *)&addr,
                sizeof(struct sockaddr_un));

    if (ret < 0)
        return ret;

    return sock;
}

int acpi_listen(int sock)
{
    int ret, status;
    char buffer[65];

    while (1) {
        memset(buffer, 0x00, 65);

        ret = read(sock, buffer, 64);

        if (ret < 0)
            return ret;

        buffer[64] = '\0';

        // As of right now we only care about jack/headphone events.
        if (strncmp("jack/headphone", buffer, 14) == 0) {

            /* Events are structured in the following way:
             * 'jack/headphone HEADPHONE (un)plug' */
            switch (buffer[25]) {
                case 'u':
                    status = UNPLUGGED;
                    break;
                case 'p':
                    status = PLUGGED;
            }

        } else {
            continue;
        }

        return status;
    }
}
