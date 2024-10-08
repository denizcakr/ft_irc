# ft_irc

## GİRİŞ
 - Bu projeyi ve repoyu arkadaşlarım [@eymenhafsalbayrak](https://github.com/eymenhafsalbayrak) ve [@prettysavagex](https://github.com/prettysavagex) ile geliştirdik. Repoya eklemeler tamamlanmıştır. Kampüs kuralları gereği projede herhangi bir değişiklik yapmadan pushlamayınız.
---
## IRC nedir?
 - IRC (Internet Relay Chat), internet üzerinde metin tabanlı bir iletişim protokolüdür.
 - Genel veya özel olabilen gerçek zamanlı mesajlaşma imkanı sunar.
 - Kullanıcılar doğrudan mesaja ve grup kanallarına katılabilir.
 - IRC istemcileri kanallara katılmak için IRC sunucularına bağlanır.


Table of Contents
=================
* [ft_irc](#ft-irc)
* [TCP/IP](#tcp/ip)
* [External functs](#external-functs)
* [HexChat](#HexChat)
* [MiniSocket](#MiniSocket)

## TCP/IP
---
### TCP/IP Nedir?
---
 - TCP/IP (Transmission Control Protocol/Internet Protocol), iki ana protokolün (TCP ve IP) ve ilgili diğer protokollerin bir araya gelmesiyle oluşan bir protokol yığınıdır.
 - Ağlar arası iletişimi sağlayan standartlaştırılmış bir yöntemdir.
### TCP/IP Katmanları;
---
 - TCP/IP modeli genellikle 4 katmandan oluşur.
  - Uygulama Katmanı (Application Layer)
  - Taşıma Katmanı (Transport Layer)
  - İnternet Katmanı (Internet Layer)
  - Ağ Arayüz Katmanı (Network Interface Layer)
### Katmanların İncelenmesi;
---
 `Uygulama Katmanı;`
 - Kullanıcı uygulamalarıyla iletişime girer.
 - Protokoller; HTTP, FTP, SMTP, DNS, SSH, Telnet vb.
 - Veriyi kullanıcı için anlamlı formatta sunar.
---
 `Taşıma Katmanı;`
 - Uç noktalar arası iletişimi sağlar.
 - Ana protokoller: TCP (Transmission Control Protocol), UDP (User Datagram Protocol)
---
 `İnternet Katmanı;`
 - Paketlerin yönlendirilmesini sağlar.
 - Ana protokol: IP (Internet Protocol) - IPv4: 32-bit adres sistemi, IPv6: 128-bit adres sistemi-
 - Diğer protokoller: ICMP, ARP, IGMP
---
 `Ağ Arayüzü Katmanı;`
 - Fiziksel ağ bağlantısını yönetir.
 - Ethernet, Wi-Fi, PPP gibi teknolojileri kapsar.
 - Veriyi fiziksel ortama uygun biçimde kodlar ve iletir.
### TCP/IP Çalışma Prensibi;
---
 - Veri, uygulama katmanından başlayarak aşağı doğru iner.
 - Her katman, kendi başlığını (header) ekler.
 - Alıcı tarafta, veri yukarı doğru çıkarken her katman ilgili başlığı çıkarır.
### IP Adresleme;
---
 - Her cihaza benzersiz bir IP adresi atanır.
 - IPv4: 192.168.1.1 gibi noktalı ondalık gösterim.
 - IPv6: 2001:0db8:85a3:0000:0000:8a2e:0370:7334 gibi hexadecimal gösterim.
### TCP'nin Önemli Özellikleri;
---
 - Üç aşamalı el sıkışma (Three-way handshake).
 - Akış kontrolü ve tıkanıklık kontrolü.
 - Sıralı teslimat ve veri bütünlüğü kontrolü.

## External functs
---

### socket();
```bash
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```
 - Socket, iletişim için bir endpoint(uç nokta) oluşturur ve bu endpoint'e başvuran bir file descriptor (dosya tanımlayıcısı) döndürür.
 - Başarılı bir çağrı tarafından döndürülen file descriptor, işlem için o anda açık olmayan en düşük numaralı file descriptor olacaktır.

### close();
```bash
#include <unistd.h>
int close(int fd);
```
 - close() işlevi bir dosya tanımlayıcısını kapatır, böylece artık herhangi bir dosyaya atıfta bulunmaz ve yeniden kullanılabilir. 

### setsockopt();
```bash
#include <sys/socket.h>
int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
```
 - setsockopt() işlevi, option_name bağımsız değişkeniyle belirtilen seçeneği, level bağımsız değişkeniyle belirtilen protokol düzeyinde,
socket bağımsız değişkeniyle belirtilen dosya tanımlayıcısıyla ilişkili soket için option_value bağımsız değişkeninin işaret ettiği değere ayarlar.

### getsockname();
```bash
#include <sys/socket.h>
int getsockname(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
```
 - getsockname(), sockfd soketinin bağlı olduğu geçerli adresi addr tarafından işaret edilen buffer'a döndürür.
addrlen argümanı, addr tarafından işaret edilen alan miktarını (bayt cinsinden) belirtecek şekilde başlatılmalıdır.
 - Dönüşte soket adresinin gerçek boyutunu içerir.
 - Sağlanan buffer çok küçükse, döndürülen adres kesilir; bu durumda addrlen, çağrıya sağlanandan daha büyük bir değer döndürür.

### getprotobyname();
```bash
#include <netdb.h>
struct protoent *getprotobyname(const char *name);
```
 - Bu fonksiyon protokoller hakkında bilgi alacaktır.
 - Bu bilgilerin, sıralı veya rastgele erişilebilen bir veritabanında saklandığı kabul edilir. Bu veritabanının uygulanması belirtilmemiştir.
 - getprotobyname() işlevi veritabanını baştan itibaren arar ve name ile belirtilen protokol adının p_name üyesiyle eşleştiği ilk girişi bulur,
gerektiğinde veritabanına bir bağlantı açar ve kapatır.

### gethostbyname();
```bash
#include <netdb.h>
struct hostent *gethostbyname(const char *name);
```
 - gethostbyname() işlevi, verilen hostname için hostent türünde bir yapı döndürür.  Burada name ya bir hostname ya da standart nokta gösteriminde bir IPv4 adresidir.
 - İsim bir IPv4 adresi ise, herhangi bir arama yapılmaz ve gethostbyname() sadece ismi h_name alanına ve struct in_addr eşdeğerini dönen hostent yapısının h_addr_list[0] alanına kopyalar.
 - İsim nokta ile bitmiyorsa ve HOSTALIASES ortam değişkeni ayarlanmışsa, isim için ilk olarak HOSTALIASES tarafından işaret edilen takma ad dosyası aranır.

### bind();
```bash
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```
 - Bir soket oluşturulduğunda, bir isimle var olur bind(), addr tarafından belirtilen adresi sockfd dosya tanımlayıcısı tarafından belirtilen sokete atar.
 - addrlen, addr tarafından işaret edilen adres yapısının boyutunu bayt cinsinden belirtir. Geleneksel olarak bu işlem “sokete isim atama” olarak adlandırılır.

### connect();
```bash
 #include <sys/socket.h>
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```
 - connect() sistem çağrısı, sockfd dosya tanımlayıcısı tarafından belirtilen soketi addr tarafından belirtilen adrese bağlar.
 - addrlen argümanı addr'nin boyutunu belirtir. addr içindeki adresin biçimi sockfd soketinin adres alanı tarafından belirlenir.

### listen();
```bash
#include <sys/socket.h>
int listen(int sockfd, int backlog);
```
 - listen(), sockfd tarafından belirtilen soketi pasif bir soket olarak, yani accept() kullanılarak gelen bağlantı isteklerini kabul etmek için kullanılacak bir soket olarak işaretler.
 - sockfd bağımsız değişkeni, SOCK_STREAM veya SOCK_SEQPACKET türünde bir sokete başvuran bir dosya tanımlayıcısıdır.

### accept();
```bash
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *_Nullable restrict addr, socklen_t *_Nullable restrict addrlen);
```
 - accept() sistem çağrısı, bağlantı tabanlı soket türleri (SOCK_STREAM, SOCK_SEQPACKET) ile kullanılır.
 - Dinleme soketi, sockfd için bekleyen bağlantılar kuyruğundaki ilk bağlantı isteğini çıkarır, yeni bir bağlı soket oluşturur ve bu sokete başvuran yeni bir dosya tanımlayıcısı döndürür.
Yeni oluşturulan soket dinleme durumunda değildir. Orijinal sockfd soketi bu çağrıdan etkilenmez.
sockfd argümanı, socket() ile oluşturulmuş, bind() ile yerel bir adrese bağlanmış ve bir listen() işleminden sonra bağlantıları dinleyen bir sokettir.

### htonl() ve htons(), ntohl() ve ntohs();
```bash
#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```
 - Bu işlevler 16 bit ve 32 bit büyüklükleri ağ bayt sırası ve ana bilgisayar bayt sırası arasında dönüştürmelidir.
 - Bazı uygulamalarda bu işlevler makro olarak tanımlanır.

 - htonl() işlevi, işaretsiz tamsayı hostlong'u ana bilgisayar bayt sırasından ağ bayt sırasına dönüştürür.
 - htons() işlevi, işaretsiz kısa tamsayı hostshort'u ana bilgisayar bayt sırasından ağ bayt sırasına dönüştürür. (htons() işlevi, veriyi göndermeden önce göndericinin byte sıralamasını, alıcının byte sıralamasına dönüştürerek "endianness" uyuşmazlığını ortadan kaldırır)
 - ntohl() işlevi, işaretsiz tamsayı netlong'u ağ bayt sırasından ana bilgisayar bayt sırasına dönüştürür.
 - ntohs() işlevi, işaretsiz kısa tamsayı netshort'u ağ bayt sırasından ana bilgisayar bayt sırasına dönüştürür.

### inet-ntop();
```bash
#include <arpa/inet.h>
const char *inet_ntop(int af, const void *restrict src, char dst[restrict .size], socklen_t size);
```
 - Bu işlev, af adres ailesindeki src ağ adresi yapısını bir karakter dizesine dönüştürür.
 - Elde edilen dize, boş olmayan bir işaretçi olması gereken dst tarafından işaret edilen buffer'a kopyalanır.
 - Çağıran, size argümanında bu buffer'da bulunan bayt sayısını belirtir.

### fcntl();
```bash
#include <fcntl.h>
int fcntl(int fd, int op, ... /* arg */ );
```
 - fcntl(), açık dosya tanımlayıcısı fd üzerinde aşağıda açıklanan işlemlerden birini gerçekleştirir. İşlem op tarafından belirlenir.
 - fcntl() isteğe bağlı üçüncü bir bağımsız değişken alabilir.
 - Bu argümanın gerekli olup olmadığı op tarafından belirlenir.
 - Gerekli argüman türü her op adından sonra parantez içinde belirtilir(çoğu durumda, gerekli tür int'tir ve arg adını kullanarak argümanı tanımlarız) veya argüman gerekli değilse void belirtilir.

### select();
```bash
#include <sys/select.h>

typedef /* ... */ fd_set;

int select(int nfds, fd_set *_Nullable restrict readfds, fd_set *_Nullable restrict writefds, fd_set *_Nullable restrict exceptfds, struct timeval *_Nullable restrict timeout);
```
 - nfds: İzlenecek en yüksek dosya tanımlayıcı numarası + 1.
 - readfds: Okunabilir dosya tanımlayıcıları kümesi.
 - writefds: Yazılabilir dosya tanımlayıcıları kümesi.
 - exceptfds: İstisnai durum için izlenecek dosya tanımlayıcıları kümesi.
 - timeout: Bekleme süresi.

 - select(), bir programın birden fazla dosya tanımlayıcısını izlemesine ve dosya tanımlayıcılarından biri veya daha fazlası bazı I/O işlemleri için “hazır” hale gelene kadar beklemesine olanak tanır (örneğin, giriş mümkündür).
 - Birden fazla dosya tanımlayıcısını (file descriptor) eş zamanlı olarak izler.
 - Okuma, yazma veya istisnai durum olaylarını bekler.
 - Çoklu I/O işlemlerini tek bir thread'de yönetebilir.
 - Zaman aşımı mekanizması sayesinde bloke olmayan I/O işlemleri gerçekleştirilebilir.

## HexChat
---
 ### HexChat Nedir?
 - HexChat, açık kaynaklı bir IRC (Internet Relay Chat) istemcisidir. IRC, gerçek zamanlı metin tabanlı iletişim için kullanılan bir protokoldür. HexChat, bu protokolü kullanarak kullanıcıların çeşitli IRC sunucularına bağlanmasını ve sohbet etmesini sağlar.
---
`HexChat Özellikleri ve Arayüz`
   - HexChat, XChat'in bir çatallamasıdır (fork).
   - Çapraz platform desteği sunar (Windows, macOS, Linux).
   - Çoklu sunucu bağlantısı.
   - Kanal listesi ve yönetimi.
   - Özel mesajlaşma.
   - Dosya transferi.
   - Kullanıcı dostu arayüz.
   - Özelleştirilebilir temalar ve renkler.
   - Eklenti desteği (Python ve Perl).
   - SSL bağlantı desteği.
   - SASL kimlik doğrulama.
   - DCC (Direct Client-to-Client) desteği.
   - Otomatik komut çalıştırma.
   - Detaylı log tutma.
   - Sekmeli arayüz tasarımı.
   - Özelleştirilebilir araç çubukları.
   - Kanal kullanıcı listesi.
   - Şifreli bağlantılar (SSL/TLS).
   - Güvenli kimlik doğrulama yöntemleri.
   - IP maskeleme seçenekleri.
   - IPv6 desteği.
---

# MiniSocket

- Bu kısımda basit bir socket örneğini paylaşmak istedim. server.cpp ve client.cpp dosyalarını, "c++ server.cpp -o server" ve "c++ client.cpp -o client" şeklinde derleyip server'den client'e mesaj yollayabilirsiniz. exit yazarak programı kapatabilirsiniz. (programın çalışmaması durumunda server.cpp ve client.cpp dosyalarında bulunan port numarasını, iki dosyada aynı olacak şekilde değiştiriniz.)
---
 `Server.cpp`
```c
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPV4, SOCK_STREAM = TCP
    if (server_socket == -1)
    {
        std::cout << "!SOCKET ERROR!" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "- SOCKET CREATED SUCCESSFULLY -" << std::endl;
    }

    struct sockaddr_in server_address; // Sunucu adresi
    server_address.sin_family = AF_INET; // IPV4
    server_address.sin_addr.s_addr = INADDR_ANY; // Herhangi bir IP adresinden bağlanmayı kabul et
    server_address.sin_port = htons(4000); // Port numarası

    int bind_status = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (bind_status == -1)
    {
        std::cout << "!BIND ERROR!" << std::endl;
        close(server_socket);
        return -1;
    }
    else
    {
        std::cout << "- BIND SUCCESSFUL -" << std::endl;
    }

    int listen_status = listen(server_socket, 1); // Maksimum 1 bekleyen bağlantı
    if (listen_status == -1)
    {
        std::cout << "!LISTEN ERROR!" << std::endl;
        close(server_socket);
        return -1;
    }
    else
    {
        std::cout << "- LISTENING ON PORT 4000 -" << std::endl;
    }

    struct sockaddr_in client_address; // İstemci adresi
    socklen_t client_address_len = sizeof(client_address); // İstemci adresinin boyutu
    int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len); // İstemci bağlantısını kabul et
    if (client_socket == -1)
    {
        std::cout << "!ACCEPT ERROR!" << std::endl;
        close(server_socket);
        return -1;
    }
    else
    {
        std::cout << "- CONNECTION ACCEPTED -" << std::endl;
    }

    while (true)
    {
        // Terminalden mesaj al
        std::cout << "Enter message to send to client: ";
        std::string input_message; // Gönderilecek mesaj
        std::getline(std::cin, input_message); // Mesajı al

        if (input_message == "exit")
            break;

        int message_length = input_message.size(); // Mesaj uzunluğu
        send(client_socket, &message_length, sizeof(message_length), 0); // Mesaj uzunluğunu gönder

        // Mesajı gönder
        send(client_socket, input_message.c_str(), message_length, 0); 
    }

    close(client_socket); // İstemci soketini kapat
    close(server_socket); // Sunucu soketini kapat

    return 0;
}
```

---

 `Client.cpp`
 
```c
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int scket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPV4, SOCK_STREAM = TCP
    if (scket == -1)
        std::cout << "!SOCKET ERROR!" << std::endl;
    else
        std::cout << "- SOCKET WORKED SUCCESSFULLY -" << std::endl;

    struct sockaddr_in sockadd; // Server adresi
    sockadd.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server'ın IP adresi
    sockadd.sin_family = AF_INET; // IPV4
    sockadd.sin_port = htons(4000); // Port numarası

    int conn = connect(scket, (struct sockaddr*)&sockadd, sizeof(sockadd)); // Server'a bağlanma
    if (conn == -1)
        std::cout << "!CONNECTION ERROR!" << std::endl;
    else
        std::cout << "- CONNECTION SUCCESSFUL -" << std::endl;

    while (true)
    {
        int message_length; 
        int recv_status = recv(scket, &message_length, sizeof(message_length), 0); // Mesaj uzunluğunu al
        if (recv_status <= 0) // Eğer mesaj alınamazsa
            break;

        char message[message_length + 1];
        recv(scket, message, message_length, 0); // Mesajı al
        message[message_length] = '\0'; // Null karakter ekle

        std::cout << "Server: " << message << std::endl;
    }

    close(scket); // Soket kapat

    return 0;
}
```
