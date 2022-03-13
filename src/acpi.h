
/*
 *  Copyright (c) 2022 Diego Roux.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  Header for acpi.
 */

#ifndef _ACPI_H_
#define _ACPI_H_ 0

#define UNPLUGGED   0
#define PLUGGED     1

#include <unistd.h>

#define acpi_listener_destroy(x) (close(x))

int acpi_listener_create(void);
int acpi_listen(int sock);

#endif
