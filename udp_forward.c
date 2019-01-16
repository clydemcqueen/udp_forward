#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Listen on listen_ip:listen_port and forward packets to forward_ip:forward_port
// gcc -o udp_forward udp_forward.c

int main(int argc, char *argv[])
{
  if (argc != 5) {
    printf("Usage: %s listen_ip listen_port forward_ip forward_port\n", argv[0]);
    exit(1);
  }

  // Create UDP socket
  int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

  // Listen address
  struct sockaddr_in listen_addr;
  listen_addr.sin_family = AF_INET;
  listen_addr.sin_addr.s_addr = inet_addr(argv[1]);
  listen_addr.sin_port = htons((uint16_t) atoi(argv[2]));  // htons() flips the byte order

  // Bind socket to listen address
  if (bind(sock, (struct sockaddr *) &listen_addr, sizeof(listen_addr)) == -1) {
    printf("Cannot bind address %s:%s\n", argv[1], argv[2]);
    exit(1);
  }

  printf("Listening on %s:%s\n", argv[1], argv[2]);

  // Forward address
  struct sockaddr_in fwd_addr;
  fwd_addr.sin_family = AF_INET;
  fwd_addr.sin_addr.s_addr = inet_addr(argv[3]);
  fwd_addr.sin_port = htons((uint16_t) atoi(argv[4]));

  // Remember the first sender -- we'll send responses back to this address:port
  struct sockaddr_in sender_addr;
  sender_addr.sin_addr.s_addr = 0;  // 0 means we don't have a sender

  while (1) {
    char buf[65535];

    // Where the packet came from
    struct sockaddr_in from_addr;
    socklen_t from_addr_len = sizeof(from_addr);

    // Receive a packet
    ssize_t n = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *) &from_addr, &from_addr_len);
    if (n <= 0) {
      continue;
    }

    if (from_addr.sin_addr.s_addr == fwd_addr.sin_addr.s_addr && from_addr.sin_port == fwd_addr.sin_port) {
      // Packet came from forward_ip:forward_port, so this must be a response
      if (sender_addr.sin_addr.s_addr) {
        // Send it back
        sendto(sock, buf, (size_t) n, 0, (struct sockaddr *) &sender_addr, sizeof(sender_addr));
      }
    }
    else {
      // Forward this packet
      sendto(sock, buf, (size_t) n, 0, (struct sockaddr *) &fwd_addr, sizeof(fwd_addr));
      if (!sender_addr.sin_addr.s_addr) {
        // Save the sender
        sender_addr = from_addr;
      }
    }
  }
}
