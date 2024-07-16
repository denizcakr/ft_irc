#include "server.hpp"


//tcp sunucusu olusturma ve max fd bulma islemleri

int createSocket(int portNo)
{
    int sockFd;
    sockaddr_in addr;


    sockFd = socket(AF_INET, SOCK_STREAM, 0);// ipv4, tcp* -> socket create >-< tcp/ip protokolunu kullanarak bir socket olusturur
    if (sockFd == -1)//socket olusmadiysa hata
    {
        std::cerr << "error" << std::endl;
        exit(1);
    }

    int opt = 1; //opsiyonel
    setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // SO_REUSEADDR-> 8080(port) duzgun kapat >-< 
    //setsockopt-> socket icin 'SO_REUSEADDR' secenegini ayarlar, boylece ayni adres ve port uzerinde yeniden kullanilabilir.

    memset(&addr, 0, sizeof(sockaddr_in)); // adres yapisini sifirlar
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 127.0.0.1 localhost >-< socketi herhangi bir ip adresinden gelen baglantilari kabul edecek sekilde ayarlar.
    addr.sin_family = AF_INET; // adres ailesini IPv4 (AF_INET) olarak ayarlar.
    addr.sin_port = htons(portNo);// portu veriyor -> port num. ag bayt sirasina(big-endian) cevirir.

    if (bind(sockFd, (sockaddr *)&addr, sizeof(addr)) == -1)//birlestir-> socketi belirtilen adrese ve porta baglar.
    {
        std::cerr << "bind err" << std::endl;
        close(sockFd);
        exit(1);
    }


    if (listen(sockFd, 1024) == -1) // server socket ready to listen
    {
        std::cerr << "listen err" << std::endl;
        close(sockFd);
        exit(1);
    }

    return (sockFd); // success olan socketin fdsi doner. 
}


int server::findMaxFd()
{
    int maxFd = this->serverFd;// basta max olarak server'in fdsini verir

    for(std::vector<client>::iterator begin = this->clients.begin(); begin != this->clients.end(); begin++) // tum bagli clientlarin fdsini kontrol eder
    {
        if (maxFd < (*begin).cliFd) // eger client'in fd'si , maxFd'den buyukse, maxFd nin degeri degisir
            maxFd = (*begin).cliFd;
    }
    return (maxFd); // 
}

/*

    findMaxFd() neden gerekli?
-> bir server uygulamasinda 'select()' fonk. kullanilarak socketler uzerinde coklu I/O islemleri gerceklestirilirken,
  max dosya tanimlayicisini bulmak icin kullanilir. bu select() fonk. dogru calismasi icin gereklidir.


*****   int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout); *****
- select() fonksiyonu, birden fazla fd'yi(orn:socket) izlemek ve hangilerinin I/O islemleri icin hazir oldugunu belirlemek icin kullanilir
- sunucu ve istemci calisirken, sunucunun ana soketi ve tum bagli istemcilerin soket dosya tanimlayacilarinin takip edilmesi gerek.
- select fonksiyonunu cagirirken, 'nfds' parametresi olrak en buyuk fd'nin bir fazlasini gecmeliyiz. bu noktada findMaxFd fonk kullanilir.
*/