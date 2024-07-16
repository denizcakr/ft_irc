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



