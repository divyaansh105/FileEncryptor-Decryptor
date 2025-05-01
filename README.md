# FileEncryptor-Decrytor

A multi-threaded file encryption and decryption utility that leverages **C++17** features like **threads**, **shared memory**, and **semaphores** to perform concurrent file processing. It includes a Python script to generate test files for experimentation.

---

## 🔐 Features

- Parallel file encryption and decryption
- Utilizes C++17 threading for performance
- Demonstrates shared memory and semaphore synchronization
- Python integration for test data generation

---

## 🛠️ Requirements

- **C++17** compiler (e.g., g++ 7+, MSVC 2017+)
- **Python 3.x**
- **Cmake**

---

## 🚀 Getting Started

### 1. Generate Test Files

```bash
# Create a folder for test files
mkdir test

# Run the Python script to generate sample files
python3 makeDirectory.py
```
### 2. Build the Project

```bash

If a `Makefile` is provided, you can build the project using:

make
```

### 3. Run the Program
```bash
./encrypt_decrypt.exe
```

## Snapshots 
1. Before 
  ![image](https://github.com/user-attachments/assets/9490516b-5e8c-48f5-aa78-11a835943efe)

2. After Encryption
    ![image](https://github.com/user-attachments/assets/5382be55-a431-46bc-b3b4-e32d42cb2bae)

3. Decrypting the Encrypted File
    ![image](https://github.com/user-attachments/assets/4c877ce1-ecb1-48e4-8cc4-0b51427bd8da)



