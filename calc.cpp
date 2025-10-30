	#include <iostream>
	#include <fstream>
	#include <string>
	#include <iomanip>
	#include <cstdlib> 
	
	using namespace std;
	
	struct Karyawan {
	    string nama;
	    int umur;
	    string nik;
	    string jabatan;
	};
	
	const int MAKS_KARYAWAN = 100;
	
	void tampilkanData(Karyawan daftar[], int jumlah) {
	    cout << "NIK";
	    cout << "Nama";
	    cout << "Umur";
	    cout << "Jabatan" << endl;
	
	    for (int i = 0; i < jumlah; i++) {
	        cout << daftar[i].nik << " " << daftar[i].nama << " "<< daftar[i].umur << " "<< daftar[i].jabatan << endl;
	       
	             
	    }
	}
	
	void simpanData(Karyawan daftar[], int jumlah) {
	    ofstream file("data_karyawan.txt");
	    if (!file) {
	        cerr << "Gagal menyimpan data ke file.\n";
	        return;
	    }
	
	    for (int i = 0; i < jumlah; i++) {
	        file << daftar[i].nik << ";";
	        file << daftar[i].nama << ";";
	        file << daftar[i].umur << ";";
	        file << daftar[i].jabatan << "\n";
	    }
	
	    file.close();
	}
	
	int muatData(Karyawan daftar[]) {
    ifstream file("data_karyawan.txt");

	
	    if (!file.is_open()) {
	        cerr << "File data_karyawan.txt tidak ditemukan! Program tidak dapat memuat data.\n";
	        return 0;
	    }
	
	
	    string line;
	    int jumlah = 0;
	
	    while (getline(file, line) && jumlah < MAKS_KARYAWAN) {
	        if (line.empty()) continue;
	
	        size_t pos1 = line.find(';');
	        size_t pos2 = line.find(';', pos1 + 1);
	        size_t pos3 = line.find(';', pos2 + 1);
	
	        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
	            continue;
	
	        daftar[jumlah].nik = line.substr(0, pos1);
	        daftar[jumlah].nama = line.substr(pos1 + 1, pos2 - pos1 - 1);
	        
	        // Ganti stoi() -> atoi()
	        string umurStr = line.substr(pos2 + 1, pos3 - pos2 - 1);
	        daftar[jumlah].umur = atoi(umurStr.c_str());
	        
	        daftar[jumlah].jabatan = line.substr(pos3 + 1);
	        jumlah++;
	    }
	
	    file.close();
	    return jumlah;
	}
	
	void tambahKaryawan(Karyawan daftar[], int &jumlah) {
	    if (jumlah >= MAKS_KARYAWAN) {
	        cout << "Data penuh! Tidak dapat menambah karyawan lagi.\n";
	        return;
	    }
	
	    Karyawan k;
	    cout << "Masukkan NIK: ";
	    cin >> k.nik;
	    cout << "Masukkan Nama: ";
	    cin.ignore();
	    getline(cin, k.nama);
	    cout << "Masukkan Umur: ";
	    cin >> k.umur;
	    cout << "Masukkan Jabatan: ";
	    cin.ignore();
	    getline(cin, k.jabatan);
	
	    daftar[jumlah++] = k;
	    simpanData(daftar, jumlah);
	    cout << "Data karyawan berhasil ditambahkan.\n";
	}
	
	void editKaryawan(Karyawan daftar[], int jumlah) {
	    string nik;
	    cout << "Masukkan NIK karyawan yang akan diedit: ";
	    cin >> nik;
	
	    bool ditemukan = false;
	    for (int i = 0; i < jumlah; i++) {
	        if (daftar[i].nik == nik) {
	            ditemukan = true;
	            cout << "\nData lama:\n";
	            cout << "Nama: " << daftar[i].nama << "\n";
	            cout << "Umur: " << daftar[i].umur << "\n";
	            cout << "Jabatan: " << daftar[i].jabatan << "\n\n";
	
	            cout << "Masukkan data baru.\n";
	            cout << "Nama: ";
	            cin.ignore();
	            getline(cin, daftar[i].nama);
	            cout << "Umur: ";
	            cin >> daftar[i].umur;
	            cout << "Jabatan: ";
	            cin.ignore();
	            getline(cin, daftar[i].jabatan);
	
	            simpanData(daftar, jumlah);
	            cout << "Data berhasil diperbarui.\n";
	            break;
	        }
	    }
	    if (!ditemukan) cout << "NIK tidak ditemukan.\n";
	}
	
	void hapusKaryawan(Karyawan daftar[], int &jumlah) {
	    string nik;
	    cout << "Masukkan NIK karyawan yang akan dihapus: ";
	    cin >> nik;
	
	    bool ditemukan = false;
	    for (int i = 0; i < jumlah; i++) {
	        if (daftar[i].nik == nik) {
	            for (int j = i; j < jumlah - 1; j++) {
	                daftar[j] = daftar[j + 1];
	            }
	            jumlah--;
	            simpanData(daftar, jumlah);
	            cout << "Data karyawan berhasil dihapus.\n";
	            ditemukan = true;
	            break;
	        }
	    }
	    if (!ditemukan) cout << "NIK tidak ditemukan.\n";
	}
	
	int main() {
	    Karyawan daftar[MAKS_KARYAWAN];
	    int jumlah = muatData(daftar);
	    int pilihan;
	
	    do {
	        cout << "MENU DATA KARYAWAN \n";
	        cout << "ketik 1 untuk Tampilkan semua data\n";
	        cout << "ketik 2 untuk Tambah karyawan baru\n";
	        cout << "ketik 3 untuk Edit data karyawan\n";
	        cout << "ketik 4 untuk Hapus karyawan\n";
	        cout << "ketik 5 untuk Keluar\n";
	        cout << "Ketika uy: ";
	        cin >> pilihan;
	
	        switch (pilihan) {
	            case 1: tampilkanData(daftar, jumlah); break;
	            case 2: tambahKaryawan(daftar, jumlah); break;
	            case 3: editKaryawan(daftar, jumlah); break;
	            case 4: hapusKaryawan(daftar, jumlah); break;
	            case 5: cout << "Keluar"; break;
	            default: cout << "Pilihan tidak valid.\n";
	        }
	    } while (pilihan != 5);
	
	    return 0;
	}


