# ft_irc


### OSI MODELİ

OSI (Open Systems Interconnection) modeli, ağ iletişimini yedi katmana ayıran kavramsal bir çerçevedir. Bu katmanlar, en alttaki fiziksel katmandan en üstteki uygulama katmanına kadar sıralanır. İşte OSI modelinin 7 katmanı:

Fiziksel Katman (Physical Layer):
Verinin fiziksel ortamda iletilmesini sağlar. Kablolar, fiberler, elektrik sinyalleri gibi fiziksel bileşenlerle ilgilenir.

Veri Bağlantı Katmanı (Data Link Layer):
Fiziksel katman üzerinde güvenilir veri iletimini sağlar. MAC adresleri kullanılır ve çerçeveleme (framing) işlemi burada gerçekleşir.

Ağ Katmanı (Network Layer):
Veri paketlerinin yönlendirilmesini (routing) sağlar. IP adresleri bu katmanda kullanılır.

Taşıma Katmanı (Transport Layer):
Veri akışının kontrolünü ve güvenilirliğini sağlar. TCP ve UDP protokolleri bu katmanda çalışır.

Oturum Katmanı (Session Layer):
İki cihaz arasındaki oturumları (sessions) yönetir, başlatır, sürdürür ve sonlandırır.

Sunum Katmanı (Presentation Layer):
Veriyi uygulama katmanı için anlaşılır hale getirir. Veri sıkıştırma ve şifreleme işlemleri burada gerçekleşir.

Uygulama Katmanı (Application Layer):
Kullanıcı uygulamalarının ağ hizmetlerine erişimini sağlar. HTTP, FTP, SMTP gibi protokoller bu katmanda çalışır.

## External functs.

### socket();
```bash
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```
  Socket, iletişim için bir endpoint(uç nokta) oluşturur ve bu endpoint'e başvuran bir file descriptor (dosya tanımlayıcısı) döndürür.
  Başarılı bir çağrı tarafından döndürülen file descriptor, işlem için o anda açık olmayan en düşük numaralı file descriptor olacaktır.

### close();
```bash
#include <unistd.h>
int close(int fd);
```
close() işlevi bir dosya tanımlayıcısını kapatır, böylece artık herhangi bir dosyaya atıfta bulunmaz ve yeniden kullanılabilir. 

### setsockopt();
```bash
#include <sys/socket.h>
int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
```
   setsockopt() işlevi, option_name bağımsız değişkeniyle belirtilen seçeneği, level bağımsız değişkeniyle belirtilen protokol düzeyinde,
socket bağımsız değişkeniyle belirtilen dosya tanımlayıcısıyla ilişkili soket için option_value bağımsız değişkeninin işaret ettiği değere ayarlar.

### getsockname();
```bash
#include <sys/socket.h>
int getsockname(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
```
  getsockname(), sockfd soketinin bağlı olduğu geçerli adresi addr tarafından işaret edilen buffer'a döndürür.
addrlen argümanı, addr tarafından işaret edilen alan miktarını (bayt cinsinden) belirtecek şekilde başlatılmalıdır.
  Dönüşte soket adresinin gerçek boyutunu içerir.
  Sağlanan buffer çok küçükse, döndürülen adres kesilir; bu durumda addrlen, çağrıya sağlanandan daha büyük bir değer döndürür.

### getprotobyname();
```bash
#include <netdb.h>
struct protoent *getprotobyname(const char *name);
```
  Bu fonksiyon protokoller hakkında bilgi alacaktır.
  Bu bilgilerin, sıralı veya rastgele erişilebilen bir veritabanında saklandığı kabul edilir. Bu veritabanının uygulanması belirtilmemiştir.
  getprotobyname() işlevi veritabanını baştan itibaren arar ve name ile belirtilen protokol adının p_name üyesiyle eşleştiği ilk girişi bulur,
gerektiğinde veritabanına bir bağlantı açar ve kapatır.

### gethostbyname();
```bash
#include <netdb.h>
struct hostent *gethostbyname(const char *name);
```
  gethostbyname() işlevi, verilen hostname için hostent türünde bir yapı döndürür.  Burada name ya bir hostname ya da standart nokta gösteriminde bir IPv4 adresidir.
  İsim bir IPv4 adresi ise, herhangi bir arama yapılmaz ve gethostbyname() sadece ismi h_name alanına ve struct in_addr eşdeğerini dönen hostent yapısının h_addr_list[0] alanına kopyalar.
  İsim nokta ile bitmiyorsa ve HOSTALIASES ortam değişkeni ayarlanmışsa, isim için ilk olarak HOSTALIASES tarafından işaret edilen takma ad dosyası aranır.

### bind();
```bash
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```
Bir soket oluşturulduğunda, bir isimle var olur bind(), addr tarafından belirtilen adresi sockfd dosya tanımlayıcısı tarafından belirtilen sokete atar.
addrlen, addr tarafından işaret edilen adres yapısının boyutunu bayt cinsinden belirtir. Geleneksel olarak bu işlem “sokete isim atama” olarak adlandırılır.

### connect();
```bash
 #include <sys/socket.h>
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```
connect() sistem çağrısı, sockfd dosya tanımlayıcısı tarafından belirtilen soketi addr tarafından belirtilen adrese bağlar.
addrlen argümanı addr'nin boyutunu belirtir. addr içindeki adresin biçimi sockfd soketinin adres alanı tarafından belirlenir.

### listen();
```bash
#include <sys/socket.h>
int listen(int sockfd, int backlog);
```
listen(), sockfd tarafından belirtilen soketi pasif bir soket olarak, yani accept() kullanılarak gelen bağlantı isteklerini kabul etmek için kullanılacak bir soket olarak işaretler.
sockfd bağımsız değişkeni, SOCK_STREAM veya SOCK_SEQPACKET türünde bir sokete başvuran bir dosya tanımlayıcısıdır.

### accept();
```bash
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *_Nullable restrict addr, socklen_t *_Nullable restrict addrlen);
```
accept() sistem çağrısı, bağlantı tabanlı soket türleri (SOCK_STREAM, SOCK_SEQPACKET) ile kullanılır.
Dinleme soketi, sockfd için bekleyen bağlantılar kuyruğundaki ilk bağlantı isteğini çıkarır, yeni bir bağlı soket oluşturur ve bu sokete başvuran yeni bir dosya tanımlayıcısı döndürür.
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
Bu işlevler 16 bit ve 32 bit büyüklükleri ağ bayt sırası ve ana bilgisayar bayt sırası arasında dönüştürmelidir.
Bazı uygulamalarda bu işlevler makro olarak tanımlanır.
htonl() işlevi, işaretsiz tamsayı hostlong'u ana bilgisayar bayt sırasından ağ bayt sırasına dönüştürür.
htons() işlevi, işaretsiz kısa tamsayı hostshort'u ana bilgisayar bayt sırasından ağ bayt sırasına dönüştürür.
ntohl() işlevi, işaretsiz tamsayı netlong'u ağ bayt sırasından ana bilgisayar bayt sırasına dönüştürür.
ntohs() işlevi, işaretsiz kısa tamsayı netshort'u ağ bayt sırasından ana bilgisayar bayt sırasına dönüştürür.

### inet-ntop();
```bash
#include <arpa/inet.h>
const char *inet_ntop(int af, const void *restrict src, char dst[restrict .size], socklen_t size);
```
Bu işlev, af adres ailesindeki src ağ adresi yapısını bir karakter dizesine dönüştürür.
Elde edilen dize, boş olmayan bir işaretçi olması gereken dst tarafından işaret edilen buffer'a kopyalanır.
Çağıran, size argümanında bu buffer'da bulunan bayt sayısını belirtir.

### fcntl();
```bash
#include <fcntl.h>
int fcntl(int fd, int op, ... /* arg */ );
```
fcntl(), açık dosya tanımlayıcısı fd üzerinde aşağıda açıklanan işlemlerden birini gerçekleştirir. İşlem op tarafından belirlenir.
fcntl() isteğe bağlı üçüncü bir bağımsız değişken alabilir.
Bu argümanın gerekli olup olmadığı op tarafından belirlenir.
Gerekli argüman türü her op adından sonra parantez içinde belirtilir(çoğu durumda, gerekli tür int'tir ve arg adını kullanarak argümanı tanımlarız) veya argüman gerekli değilse void belirtilir.

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

select(), bir programın birden fazla dosya tanımlayıcısını izlemesine ve dosya tanımlayıcılarından biri veya daha fazlası bazı I/O işlemleri için “hazır” hale gelene kadar beklemesine olanak tanır (örneğin, giriş mümkündür).
Birden fazla dosya tanımlayıcısını (file descriptor) eş zamanlı olarak izler.
Okuma, yazma veya istisnai durum olaylarını bekler.
Çoklu I/O işlemlerini tek bir thread'de yönetebilir.
Zaman aşımı mekanizması sayesinde bloke olmayan I/O işlemleri gerçekleştirilebilir.
