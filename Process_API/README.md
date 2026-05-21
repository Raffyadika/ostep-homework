# Kenapa Banyak Variant `exec()`?

Jawaban singkatnya: **fleksibilitas untuk berbagai situasi pemrograman.**

---

## 1. Soal Argumen: `l` vs `v`

**`l` (list)** — kalau argumen sudah diketahui saat nulis kode:

```c
execl("/bin/ls", "ls", "-l", "-a", NULL); // langsung tulis
```

**`v` (vector)** — kalau argumen baru diketahui saat program jalan (dinamis):

```c
char *args[] = {strdup(input), flag, NULL}; // dari user input / loop
execv("/bin/ls", args);
```

> Bayangkan bikin shell — kita tidak tahu argumen apa yang user ketik sebelumnya, jadi harus pakai array.

---

## 2. Soal Path: `p` atau tidak

**Tanpa `p`** — harus tahu lokasi persis programnya:

```c
execl("/usr/bin/python3", ...); // harus tahu full path
```

**Dengan `p`** — cukup nama programnya, OS yang cari:

```c
execlp("python3", ...); // OS cari sendiri di $PATH
```

> Lebih praktis kalau lokasi program bisa beda-beda di tiap sistem.

---

## 3. Soal Environment: `e` atau tidak

**Tanpa `e`** — pakai environment variable yang diwarisi dari parent:

```c
execvp("ls", args); // pakai PATH, HOME, dll dari parent
```

**Dengan `e`** — set environment sendiri:

```c
char *env[] = {"PATH=/bin", "HOME=/tmp", NULL};
execvpe("ls", args, env); // environment terisolasi
```

> Berguna untuk **keamanan** atau **isolasi proses** — misalnya menjalankan program tanpa mewarisi variabel sensitif dari parent.

---