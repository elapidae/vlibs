#ifndef VHOSTADDRESS_H
#define VHOSTADDRESS_H

#include <string>
#include <netinet/in.h>

class VHostAddress
{
public:
    VHostAddress();
    VHostAddress( const std::string &addr, uint16_t port );

    bool set_addr( const std::string &addr );
    std::string get_addr() const;

    void set_port( uint16_t port );

    uint32_t inet_ip()   const;
    uint16_t inet_port() const;

    uint32_t host_ip()   const;
    uint16_t get_port() const;

    std::string str() const;

    sockaddr_in _addr;
private:
};



#endif // VHOSTADDRESS_H
