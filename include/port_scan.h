#ifndef PORT_SCAN_H
#define PORT_SCAN_H

const char *get_service_name(int port);
int scan_port(const char *ip, int port);
void scan_ip(const char *ip, int start_port, int end_port);

#endif