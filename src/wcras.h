
/*
 *  Copyright (c) 2022 Diego Roux.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  Header for wcras.
 */

#ifndef WCRAS_H_
#define WCRAS_H_ 0

#include <cras_client.h>

#define TYPE_HEADPHONE  1
#define TYPE_SPEAKER    2

typedef struct cras_ionode_info cras_node;
typedef struct cras_iodev_info  cras_dev;
typedef struct cras_client      cras_ctx;

#define wcras_destroy(x) (cras_client_destroy(x))

int wcras_init(cras_ctx **ctx);
int wcras_get_output_node(cras_ctx *ctx, int type, cras_node *node);
int wcras_select_node(cras_ctx *ctx, int direction, cras_node *node);

#endif
