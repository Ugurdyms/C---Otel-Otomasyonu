
#include <iostream>
#include <string>        // stringleri kullabilmek içim
#include <fstream>       // Dosya yazma için 
#include <time.h>        // Random sayı atması için
using namespace std;


class otel          // otel adında bir sınıf tanımladım 
{
	// sayac ve toplam ve diğerleri
	int sayac = 0, toplam = 0;

	// Yetişkin için 
	int YetişkinSayisi, KalinacakGun_Sayısı, Y_ücret;

	// cevap ve oda no
	int cevap, oda_numarası;

	// çocuk için
	int ÇocukSayisi, Ç_ücret, Çocuklar[10];

	// müşteri bilgileri
	string Müşteri_adı, Müşteri_soyadı;

	// rezervasyonlu ad karşılaştırma için oluşturuldu
	string Rezervasyonlu_ad;


public:              // public kısımda ise programda kullancağım fonksiyonları tanımladım 
	otel();
	void oda_işletmesi();
	void oda_rezervasyonu();
	void rezervasyon_bilgileri();
	void oda_boşaltma();
	void oda_guncelleme();
};

otel::otel()
{
	toplam = 0;
	sayac = 0;
	oda_işletmesi();            // oda işletmesini iki defa çağırdım 
}
void otel::oda_işletmesi()
{
	do
	{
		system("color 70");
		cout << "****** HOŞGELDİNİZ ******" << endl;
		cout << "1 ---> Rezervasyon yapma" << endl;
		cout << "2 ---> Rezervasyon bilgileri" << endl;
		cout << "3 ---> Oda boşaltma" << endl;
		cout << "4 ---> Rezervasyon güncelleme" << endl;
		cout << "5 ---> Çıkış" << endl;
		cout << endl << "İşlem yapmak istediğiniz seçeneği giriniz." << endl;
		
		cin >> cevap;

		system("cls");

		switch (cevap)
		{
		case 1: oda_rezervasyonu();
			break;
		case 2: rezervasyon_bilgileri();
			break;
		case 3: oda_boşaltma();
			break;
		case 4:oda_guncelleme();
			break;
		case 5:
			exit(1);

		default: cout << "Yanlış seçim yaptınız ! " << endl;
			break;
		}
		cout << endl;

	} while (cevap != 5);
}

void otel::oda_rezervasyonu()
{
	//// rezervasyon yapma kısmı ////
	cout << endl;

	cout << "   Rezervasyon sahibinin : " << endl;
	cout << endl;
	cout << "   Adı: ";
	cin >> Müşteri_adı;

	cout << "   Soyadı: ";
	cin >> Müşteri_soyadı;

	cout << endl;
	do
	{
		cout << "   Otelde kalacak yetişkin sayısını giriniz : ";                // Yetişkin sayısını istiyor 
		cin >> YetişkinSayisi;
		cout << endl;

		if (YetişkinSayisi == 0)
		{
			cout << "Lütfen doğru bir değer girin. " << endl;                     // Eğer yetişkin sayısını 0 girerse kullanıcı uyaracak
		}
	} while (YetişkinSayisi < 1 || YetişkinSayisi > 100);

	do
	{
		cout << "   Otelde kalacak çoçuk sayısını giriniz: ";    // otelde kalacak çoçuk sayısı isteme bölümü
		cin >> ÇocukSayisi;

		if (ÇocukSayisi == 0)
		{
			cout << "Lütfen doğru bir değer girin. " << endl;                     // Eğer çocuk sayısını 0 girerse kullanıcı uyaracak
		}
	} while (ÇocukSayisi < 1 || ÇocukSayisi > 100);

	cout << endl;
	cout << "   Kaç gün kalmak istiyorsunuz ? ";     // Müşterinin otelde kalacağı gün sayısı
	cin >> KalinacakGun_Sayısı;
	cout << endl;

	// Müşterinin ödeyeceği ücret hesaplama bölümü //


	Y_ücret = YetişkinSayisi * 100 * KalinacakGun_Sayısı;
	Ç_ücret = sayac * 20 * KalinacakGun_Sayısı;
	toplam = Y_ücret + Ç_ücret;

	system("cls");

	cout << endl;
	cout << "    Rezervasyonunuz " << Müşteri_adı << " adına yapılmıştır. " << endl;        // Rezervasyon bilgilerinde kullanılacak Müşteri adını göstermesi
	cout << endl;

	///// oda numarası verme  ///// 

	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		oda_numarası = rand() % 100 + 1;                // Random kendiliğinden 1-100 arası oda numarası verme.
	}


	ofstream ekle("musteri_bilgileri.txt", ios::app);           // dosyaya müşteri bilgileri yazdırma 

	ekle << endl << oda_numarası << "\t" << Müşteri_adı << "\t" << Müşteri_soyadı << "\t" << toplam;

	ekle.close();
}
void otel::rezervasyon_bilgileri()
{
	int bulma = 0;

	cout << "Rezervasyon kimin adına yapılmıştı : ";
	cin >> Rezervasyonlu_ad;

	ifstream oku("musteri_bilgileri.txt");

	while (!oku.eof())				// Rezervasyonu yaptıran kişinin adına kayıtlı bilgileri gösterir.
	{
		oku >> oda_numarası >> Müşteri_adı >> Müşteri_soyadı >> toplam;
		//if (kontrol_degisken != oda_numarası)
		//{
		if (Rezervasyonlu_ad == Müşteri_adı)
		{
			bulma = 1;
			cout << endl << "--- Oda no: " << oda_numarası; cout << endl;
			cout << "--- Ad    : " << Müşteri_adı; cout << endl;
			cout << "--- Soyad : " << Müşteri_soyadı; cout << endl;
			cout << "--- Ücret : " << toplam; cout << endl << endl;
		}
		//}
		//kontrol_degisken = oda_numarası;
	}
	if (bulma == 0)
	{
		cout << "Böyle bir kişi adına rezervasyon yapılmamıştır !" << endl;
	}

	oku.close();
}
void otel::oda_boşaltma()
{
	ifstream guncelle("musteri_bilgileri.txt");
	ofstream ekle("gecici.txt", ios::app);
	int k_odano, oda_kontrol = 0;
	cout << "Silmek istediğiniz oda numarasını giriniz=";
	cin >> k_odano;
	while (!guncelle.eof())
	{
		guncelle >> oda_numarası >> Müşteri_adı >> Müşteri_soyadı >> toplam;

		if (k_odano == oda_numarası)
		{
			oda_kontrol = 1;
			cout << "Odanız silindi.";
		}

		else
		{
			ekle << endl << oda_numarası << "\t" << Müşteri_adı << "\t" << Müşteri_soyadı << "\t" << toplam;
		}
	}
	if (oda_kontrol == 0)
	{
		cout << "Oda bulunamadı...";
	}

	guncelle.close();
	ekle.close();
	remove("musteri_bilgileri.txt");
	rename("gecici.txt", "musteri_bilgileri.txt");
}
void otel::oda_guncelleme()
{
	ifstream guncelle("musteri_bilgileri.txt");
	ofstream ekle("gecici.txt", ios::app);
	int k_odano, oda_kontrol = 0;
	cout << "Güncellemek istediğiniz oda numarasını giriniz=";
	cin >> k_odano;
	while (!guncelle.eof())
	{
		guncelle >> oda_numarası >> Müşteri_adı >> Müşteri_soyadı >> toplam;

		if (k_odano == oda_numarası)
		{
			oda_kontrol = 1;
			cout << "   Adı: ";
			cin >> Müşteri_adı;

			cout << "   Soyadı: ";
			cin >> Müşteri_soyadı;

			cout << endl;

			cout << "   Otelde kalacak yetişkin sayısını giriniz : ";                // Yetişkin sayısını istiyor 
			cin >> YetişkinSayisi;
			cout << endl;

			if (YetişkinSayisi == 0)
			{
				cout << "Lütfen doğru bir değer girin. " << endl;                     // Eğer yetişkin sayısını 0 girerse kullanıcı uyaracak
			}


			cout << "   Otelde kalacak çoçuk sayısını giriniz. ";    // otelde kalacak çoçuk sayısı isteme bölümü
			cin >> ÇocukSayisi;

			if (ÇocukSayisi == 0)
			{
				goto q;
			}

		q:
			cout << endl;
			cout << "   Kaç gün kalmak istiyorsunuz ? ";     // Müşterinin otelde kalacağı gün sayısı
			cin >> KalinacakGun_Sayısı;
			cout << endl;

			// Müşterinin ödeyeceği ücret hesaplama bölümü //


			Y_ücret = YetişkinSayisi * 100 * KalinacakGun_Sayısı;
			Ç_ücret = sayac * 20 * KalinacakGun_Sayısı;
			toplam = Y_ücret + Ç_ücret;

			ekle << endl << oda_numarası << "\t" << Müşteri_adı << "\t" << Müşteri_soyadı << "\t" << toplam;
		}

		else
		{
			ekle << endl << oda_numarası << "\t" << Müşteri_adı << "\t" << Müşteri_soyadı << "\t" << toplam;
		}
	}

	if (oda_kontrol == 0)
	{
		cout << "Oda bulunamadı...";
	}

	guncelle.close();
	ekle.close();
	remove("musteri_bilgileri.txt");
	rename("gecici.txt", "musteri_bilgileri.txt");

}

int main()
{
	setlocale(LC_ALL, "Turkish");                    // Türkçe karakter kullanma 
	otel a;                           // main bloğunda sadece otel sınıfında bir nesne oluşturdum.
	// program çalışırken main bloğunun içinde ilk olarak sınıf nesnesi görecek ve yapıcı fonk. devreye girecek. 
	system("pause");
	return 0;
}