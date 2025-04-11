# Tucil2_13523116
Quadtree Image Compression

oleh : Fityatul Haq Rosyidi - 13523116

Program ini dimaksudkan untuk memenuhi Tugas Kecil 2 Mata Kuliah Strategi Algoritma 2024/2025. 

Program ini melakukan Kompresi Gambar menggunakan algoritma Divide and Conquer dalam bentuk struktur Quadtree. setiap node pada Quadtree memiliki nilai variansi warna yang dihitung berdasarkan 4 metode yang dapat dipilih : 
  - Variance
  - Mean Absolute Value (MAD)
  - Max Pixel Difference
  - Entropy

Program ditulis dengan bahasa C, dapat dijalankan pada Operating System Windows melalui terminal cmd dan powershell

## Requirements
pastikan Compiler C (gcc) terinstall di device anda

## How to use
1. clone repo ini di lokal anda
2. buka terminal cmd/powershell, navigasi ke lokasi anda menyimpan repo ini
3. masuk ke folder src
4. pastikan lokasi anda sudah benar, kemudian compile dengan command

```console
gcc -o out .\main.c .\utils.c .\quadtree.c .\io_utils.c
```

4. setelah itu, run dengan command

pada cmd
```console
out.exe
```

pada powershell
```console
.\out.exe
```

5. jika program berhasil dijalankan, tampilannya akan seperti berikut

<div align="center">
  <img src="https://github.com/user-attachments/assets/a2ac6c76-2b9c-4191-8d0d-bc1a3b0c8650" alt="Contoh Gambar" width="300"/>
</div>


<br>
Jika ada kendala ketika dalam menjalankan program ini, silakan kontak penulis di alamat email berikut : 

<br>13523116@mahasiswa.itb.ac.id
<br>13523116@std.stei.itb.ac.id
<br>fityatulhaqrosyidi25@gmail.com
