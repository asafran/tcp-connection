// 29 11 2017

#ifndef		TCPCLIENT_H
#define 	TCPCLIENT_H

#include	<QtGlobal>
#include    <QObject>
//#include    <QTcpSocket>
#include    <QDataStream>
//#include    <QMetaType>

class QTimer;
class QTcpSocket;

#include    "tcp-client-structs.h"

#if defined(TCPCONNECTION_LIB)
# define TCPCLIENT_EXPORT Q_DECL_EXPORT
#else
# define TCPCLIENT_EXPORT Q_DECL_IMPORT
#endif


/*!
 *  \class TcpClient
 *  \brief Класс, обслуживающий клиентское TCP/IP-соединение
 */
//-----------------------------------------------------------------------------
//	Класс, обслуживающий клиентское TCP/IP-соединение
//-----------------------------------------------------------------------------
class TCPCLIENT_EXPORT TcpClient Q_DECL_FINAL : public QObject
{
    Q_OBJECT

public:
    /// Конструктор и деструктор
    explicit TcpClient();
    ~TcpClient();

    /// Инициализация клиента
    void init(tcp_config_t tcp_config);

    /// Проверка соединения
    bool isConnected() const;

    /// Запуск клиента
    void start();

    ///
    const tcp_config_t getConfig() const;


public slots:
    /// Cоединение с сервером
    void connectToServer();

    /// Передача данных серверу
    void sendToServer(QByteArray send_data);

    ///
    void connectArrayPtr(QByteArray* &arrPtr);


signals:
    ///
    void connectedToServer();

    ///
    void disconnectedFromServer();

    ///
    void authorized();


public slots:
    /// Прием данных от сервера
    void receive();

    /// Обработка факта соединения с сервером
    void onConnect();

    /// Обработка факта разрыва соединения с сервером
    void onDisconnect();


protected:
    /// Клиентский сокет
    QTcpSocket      *socket;

    /// Входящий поток данных
    QDataStream     in;

    /// Текущее состояние клиента
    tcp_state_t     tcp_state;

    /// Конфигурация клиента
    tcp_config_t    tcp_config;

    /// Данные, принятые от сервера
    QByteArray      incomingData_;


private:
    ///
    QTimer* timerConnector_;


private slots:
    ///
    void onTimerConnector();

};

#endif