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
  
