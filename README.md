# Projekt 1 – Pomiar odczytu pliku (read vs mmap)

## Opis
Celem projektu jest porównanie dwóch sposobów odczytu plików w systemie Linux:
- za pomocą funkcji `read(2)`
- za pomocą mapowania pamięci `mmap(2)`

Program mierzy czas odczytu pliku (sekwencyjnie i losowo) oraz oblicza hash CRC64,
który pozwala zweryfikować poprawność odczytu.

---

## Kompilacja
Projekt wymaga systemu Linux z kompilatorem GCC.

Aby skompilować program:
```bash
make all
