# QUNICS
QUNICS is un*x-like independent operating system. 
<hr>
<img width="1600" height="650" alt="Anatinus ve QUNICS" src="https://github.com/user-attachments/assets/942b0d27-63db-44d8-a15b-1924a7e18f97" />

## Screenshots
<img width="822" height="449" alt="resim" src="https://github.com/user-attachments/assets/0745882c-824d-4c89-afeb-bc059fb07380" />

<br>

Yukarıdaki ekran görüntüsü, userlandin olmaması nedeniyle ve elfloaderin hazırlanmamış olması nedeniyle kernel-boot'un ötesine geçememesini gösteren bir ekran görüntüsüdür. 
Bu, işletim sistemi çekirdeğinin rahatlıkla boot edilebildiğini gösterir. Bu aşamada QUNICS için çalışan bir kernel diyebiliriz. Ancak QUNICS'i kullanan bir host sistemi ne yazık ki henüz yok. 
Qunics için bağımsız bir userlandi olan, GRUB uyumlu ancak kendine has bootloaderi olan Qyzyl Operating System (kısaca QOS veya QyzylOS)'u geliştirmeye ileri zamanlarda başlayacağız.

## DevNote
- Hedefimiz bir userland ve elfloader uyumu sağlamaktır. QUNICS, POSIX standartları ile uyumlu olmaya çalışmayı hedefler
- QOS/QyzylOS, QUNICS'in stabil bir versiyonu çıktıktan sonra geliştirilmeye başlayacak. İleride GNU araçlarıyla da uyumlu olacak bir `Qyzgyl GNU/QUNICS` planımız da var.

- Mevcut QUNICS kerneli, ext2 dosya sistemini deneysel olarak okuyabilir. İleride QUNICS File System (kısaca QFS) adını verdiğimiz bir dosya sistemini oluşturacağım.
- QyzylOS, 2026'nın sonlarına doğru beta olarak çıkış yapacaktır
- QUNICS için işletim sistemi-bağımsız, TempleOS benzeri olan HQWM pencere yöneticimizi entegre edeceğiz. (Bu yazının yazıldığı `10/12/2025 | 2:30 AM` itibariyle HQWM çalışıyor olsa da deneysel olduğundan gizli bir repo altında tutuluyor. Yakınd kaynak kodları GPL-v3 lisansı altında paylaşılacaktır.)

<hr>

## Build iso from source
```bash
git clone https://github.com/KairaBegudiri/qunics
cd qunics
make run
```
