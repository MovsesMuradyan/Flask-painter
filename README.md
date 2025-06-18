# 🎨 Flask-Painter  
*Because your BMPs deserve a second life—as ASCII art!*

---

## 🧠 Project Overview

**Flask-Painter** is a two-part project that combines the power of C and the magic of Flask to turn boring old BMP files into glorious ASCII art.

One part is a fast, no-nonsense command-line tool written in C. The other is a web interface for those who prefer clicking buttons over writing commands. Together, they bring art to the terminal *and* the browser.

---

## I. C Command-Line Tool: *ASCII-fy All the Things!*

This tool was born after I finished my C lectures and thought, “Why not make a program that turns images into text?” (Because obviously, that’s what normal people do.)

### 💡 What It Does:
- Accepts 24-bit BMP files (must have that sweet `BM` signature).
- Converts the image into ASCII using characters like `@`, `#`, `%`, `*`, and more.
- Offers two output options:

#### 1️⃣ Terminal Output:
Prints the ASCII art directly to your terminal. Great for one-time viewing, impressing your classmates.

- The first method Usage
```  ./painter -i ( input bmp file ) ```
- The second method Usage
```  ./painter -i ( input bmp file ) -o ( output txt file )```

---

## II. 🌐 Flask Web Interface: A Simple and Accessible UI

To complement the command-line tool, I developed a web interface using **Flask**, along with **HTML** and **CSS**, to make the program more accessible to a wider audience.

### 💡 What It Does:
- Provides a clean and user-friendly interface for uploading BMP files.
- Sends the image to the backend, where the C program processes it into ASCII art.
- Once complete, the user is prompted to download the ASCII-formatted `.txt` file.

### ✅ Benefits:
- No need to use the terminal or install additional tools.
- Multiple users can access and use the tool via a web browser.
- Designed to be straightforward and easy to use for all skill levels.

