
/*
 *  Copyright (c) 2022 Diego Roux.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  This code is a wrapper for the libcras API.
 */

#include <cras_client.h>

#include "wcras.h"

#define MAX_DEVS    1
#define MAX_NODES   10

// Create and connect cras_client.
int wcras_init(cras_ctx **ctx)
{
    int ret;

    ret = cras_client_create(ctx);

    if (ret)
        return ret;

    ret = cras_client_connect_timeout(*ctx, 1500);

    if (ret) {
        cras_client_destroy(*ctx);
        return ret;
    }

    ret = cras_client_run_thread(*ctx);

    if (ret) {
        cras_client_destroy(*ctx);
        return ret;
    }

    ret = cras_client_connected_wait(*ctx);

    if (ret) {
        cras_client_destroy(*ctx);
        return ret;
    }

    return ret;
}

/*  Get info of a specific node type.
 *  Returns 1 on success, 0 when the node was not found
 *  or a negative errno on failure. */
int wcras_get_output_node(cras_ctx *ctx, int type, cras_node *node)
{
    size_t num_devs, num_nodes;
    cras_node nodes[MAX_NODES];
    cras_dev devs[MAX_DEVS];
    int ret;

    num_devs = 0;
    num_nodes = MAX_NODES;

    ret = cras_client_get_output_devices(ctx, devs, nodes,
                                        &num_devs, &num_nodes);

    if (ret)
        return ret;

    for (int i = 0; i < num_nodes; i++) {

        if (type == TYPE_HEADPHONE) {
            if (strcmp("HEADPHONE", nodes[i].type) == 0) {
                memcpy(node, &nodes[i], sizeof(cras_node));
                return 1;
            }
        } else if (type == TYPE_SPEAKER) {
            if (strcmp("INTERNAL_SPEAKER", nodes[i].type) == 0) {
                memcpy(node, &nodes[i], sizeof(cras_node));
                return 1;
            }
        }

    }

    return 0;
}

// Set current input/output.
int wcras_select_node(cras_ctx *ctx, int direction, cras_node *node)
{
    cras_node_id_t node_id;

    node_id = ((uint64_t)node->iodev_idx << 32) | node->ionode_idx;

    return cras_client_select_node(ctx, direction, node_id);
}
