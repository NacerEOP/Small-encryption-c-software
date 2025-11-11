
<img width="737" height="300" alt="image" src="https://github.com/user-attachments/assets/92fa85de-47fa-4089-b0b7-9be157c9d5f2" />

C++ Text File Encryption System

Description:
This is a lightweight C++ application to encrypt and decrypt .txt files using multiple security modes. It features a simple Windows GUI for easy user interaction and real-time status updates.

Features:

Encrypt and decrypt .txt files

Three encryption modes:

Level 1: Caesar cipher

Level 2: XOR encryption

Level 3: Combination of Caesar + XOR

Simple and intuitive GUI built with native Windows HWND API

Validates that only .txt files are processed

Lightweight, dependency-free C++ implementation

Getting Started:

Clone the repository to your local machine

Open the project in your preferred C++ IDE (Visual Studio, Code::Blocks, etc.)

Build and run the project

Use the GUI to select a .txt file, choose the security level, and click Encrypt or Decrypt

How it Works:

User selects a .txt file through the GUI

The program validates the file extension

The file content is read using the data_write class

The text is encrypted or decrypted using the Chiffrement class according to the selected mode

The result is written back to the same file

Status messages are displayed in the GUI

Dependencies:

Windows operating system

C++ compiler supporting C++11 or later

Use Cases:

Learning basic cryptography techniques

Practicing C++ Windows GUI programming

Simple text file encryption/decryption tool for personal use

License:
MIT License
