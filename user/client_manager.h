#ifndef CLIENT_MANAGER_H

#include "ets_sys.h"
#include "osapi.h"
#include "c_types.h"
#include "mem.h"
#include "ip_addr.h"
#include "espconn.h"

typedef struct _clientList clientList;

struct _clientList {
    clientList *next;
    struct espconn *esp_conn;
};

clientList* cm_create_clientList();
void cm_add_connection(clientList *head, struct espconn *conn);
bool cm_remove_connection(clientList *head, struct espconn *conn);

#endif
