#pragma once

#include "unistd.h" // unix standard library fonksiyonlari
#include "iostream" // I/O islemleri
#include "sys/socket.h" // socket programlama fonksiyonlari
#include "arpa/inet.h" // internet adres islemleri
#include "sys/types.h" // cesitli veri tipleri
#include "string.h" // c string fonksiyonlari
#include "vector" // vector container
#include "sys/select.h" // select() fonksiyonu


int createSocket(int portNo); // belirtilen port numarasi uzerinde bir sunucu soketi (server socket) olusturacak olan fonksiyon

class client
{
    public:
        std::vector<std::string> messageBox; //client'in gonderdigi veya aldigi mesajlari tutan vector container'i
        int cliFd; // client fd'si
        int port; // client'in bagli oldugu port numarasi
        std::string ipAddr; //client'in ip adresi
};


class server
{
    public:
        std::vector<client> clients; // bagli olan clientlari tutacak olan vector
        int serverFd; // server fd'si
        int findMaxFd(); // server'in ve bagli olan clientlarin fdleri arasinda max degeru bulan fonk.
};

/*

temel olarak TCP server ve client yapisini kurmak icin olusturulan classlardir
createSocket() -> fonksiyon, belirli bir port uzerinde dinleyen bir server socket olusturur.

*/