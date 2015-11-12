#include "client_manager.h"

clientList* cm_create_clientList() {
    // allocate node and zero it. A zeroed node will signal end of list
    clientList* r = (clientList*)os_malloc(sizeof(clientList));
    os_memset(r, 0, sizeof(clientList));
    return r;
}

void cm_add_connection(clientList *head, struct espconn *conn) {
    // allocate new list item and copy head into it
    clientList *newNode = (clientList*)os_malloc(sizeof(clientList));
    os_memcpy((void *)newNode, (void *)head, sizeof(clientList));

    // fill head with new data
    head->next = newNode;
    head->esp_conn = conn;
}

bool cm_remove_connection(clientList *head, struct espconn *conn) {
    // find node
    clientList *prev = 0;
    while (head) {
        if (head->esp_conn == conn) {
            // found, check if first node
            if (prev == 0) {
                clientList *next = head->next;
                // check if only node (this should only happen if there are
                // zero connections)
                if (next == 0) {
                    head->next = 0;
                    head->esp_conn = 0;
                }
                else {
                    head->next = next->next;
                    head->esp_conn = next->esp_conn;
                    os_free(next);
                }
            }
            else {
                prev->next = head->next;
                os_free(head);
            }
            return true;
        }
        prev = head;
        head = head->next;
    }
    return false;
}



