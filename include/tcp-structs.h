//29 11 2017
#ifndef TCPSTRUCTS_H
#define TCPSTRUCTS_H

#include "a-tcp-namespace.h"

#include <stddef.h>
#include <stdint.h>
#include <QByteArray>


constexpr size_t TCP_BUFFER_SIZE = 1024;

#pragma pack(push, 1)
struct tcp_cmd_t_old
{
    ATcp::TcpCommand command;
    size_t           data_size;
    uint8_t          buffer[TCP_BUFFER_SIZE]; // попробовать перевести на вектор !!!

    tcp_cmd_t_old()
        : command(ATcp::tcZERO)
        , data_size(0)
    {

    }

    QByteArray toByteAray()
    {
        QByteArray buf(sizeof *this, Qt::Uninitialized);
        memcpy(buf.data(), this, sizeof *this);
        return buf;
    }
};
#pragma pack(pop)

struct tcp_cmd_t
{
    ATcp::TcpCommand command;
    size_t           bufferSize;
    QByteArray       buffer;

    static const size_t INFO_SIZE = sizeof(command) + sizeof(bufferSize);

    tcp_cmd_t()
        : command(ATcp::tcZERO)
        , bufferSize(0u)
    {

    }

    void setData(const char* _dat, size_t _len)
    {
        buffer = std::move(QByteArray(_dat, _len));
        bufferSize = buffer.size();
    }

    template<typename T>
    void setData(T _dat)
    {
        buffer.resize(sizeof(T));
        memcpy(buffer.data(), &_dat, sizeof(T));
        bufferSize = sizeof(T);
    }

    QByteArray toByteArray()
    {
        QByteArray buf(sizeof(ATcp::TcpCommand) + sizeof(size_t) + bufferSize,
                       Qt::Uninitialized);

        ptrdiff_t offset = 0u;
        memcpy(buf.data(), &command, sizeof command);
        offset += sizeof command;
        memcpy(buf.data() + offset, &bufferSize, sizeof bufferSize);
        offset += sizeof bufferSize;
        memcpy(buf.data() + offset, buffer.data(), bufferSize);

        return buf;
    }

    static bool chechBufferSize(QByteArray &_arr)
    {
        return static_cast<size_t>(_arr.size()) >= INFO_SIZE;
    }

    static ATcp::TcpCommand extractCommand(QByteArray &_arr)
    {
        ATcp::TcpCommand tmp = ATcp::tcZERO;
        memcpy(&tmp, _arr.data(), sizeof(ATcp::TcpCommand));
        return tmp;
    }

    static size_t extractBufferSize(QByteArray &_arr)
    {
        size_t tmp = 0u;
        memcpy(&tmp, _arr.data() + sizeof(ATcp::TcpCommand), sizeof(size_t));
        return tmp;
    }
};

#endif // TCPSTRUCTS_H