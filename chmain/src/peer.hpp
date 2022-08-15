#ifndef CH_PEER_HPP
#define CH_PEER_HPP

#include <cstddef>
#include <cstdint>

struct _ENetAddress;
typedef _ENetAddress ENetAddress;

struct _ENetPacket;
typedef _ENetPacket ENetPacket;

struct _ENetPeer;
typedef _ENetPeer ENetPeer;

struct _ENetHost;
typedef _ENetHost ENetHost;

namespace ch
{
    class peer
    {
    public:
        peer(
            ENetHost *host,
            const ENetAddress *address,
            std::size_t channel_count,
            std::uint32_t data);
        ~peer();

        int send(ENetPacket *packet) const;

        void disconnect() const;

        bool is_successfully_disconnected() const;
        void set_successfully_disconnected();

    private:
        ENetPeer *enet_peer;
        bool successfully_disconnected = false;
    };
}

#endif