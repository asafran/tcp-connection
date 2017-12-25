// 29 11 2017
#ifndef     TCPDATA_H
#define     TCPDATA_H

#include    <QtGlobal>
#include    <QMetaType>

/*!
 *  \struct tcp_state_t
 *  \brief Состояние клиента
 */
//------------------------------------------------------------------------------
//      Состояние клиента
//------------------------------------------------------------------------------
#pragma pack(push, 1)

struct tcp_state_t
{
    /// Счетчик переданных пакетов данных
    uint64_t    send_count;
    /// Счетчик принятых пакетов данных
    uint64_t    recv_count;

    tcp_state_t()
    {
        send_count = recv_count = 0;
    }
};

#pragma pack(pop)

Q_DECLARE_METATYPE(tcp_state_t)

/*!
 *  \struct tcp_config_t
 *  \brief Конфигурация клиента
 */
//------------------------------------------------------------------------------
//      Конфигурация клиента
//------------------------------------------------------------------------------
struct tcp_config_t
{
    /// Таймаут между попытками соедиения
    int     cmd;
    /// Имя клиента (сигнатура для идентификации на сервере)
    QString name;
    /// Адрес сервера
    QString host_addr;
    /// Порт, на котором слушает сревер
    quint16 port;
    int     ms_timeout;

    tcp_config_t()
    {
        cmd = 0;
        name = "";
        host_addr = "127.0.0.1";
        port = 1992;
        ms_timeout = 1000;
    }
};

#endif // TCPDATA_H
