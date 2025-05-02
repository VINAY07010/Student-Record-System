## 📚 Student Record System (C++)

A simple **console-based student management system** built in C++.  
This project demonstrates file handling, object-oriented programming, and data operations like **add**, **view**, **search**, **update**, **delete**, **sort**, and **export**.

---

### 🧰 Features

| Feature               | Description                                               |
|------------------------|-----------------------------------------------------------|
| ➕ Add Student          | Add a new student's roll number, name, and marks          |
| 📄 View All Students    | Display all stored student records                        |
| 🔍 Search by Roll No    | Find and display a student by their roll number           |
| 📝 Update Record        | Modify a student's name or marks                          |
| ❌ Delete Record        | Remove a student record based on roll number              |
| ✅ Input Validation     | Ensures valid data (e.g. non-negative marks, name not empty)|
| 📂 Export to TXT        | Export all records to a readable `students.txt` file      |
| 📊 Sort Records         | Sort students by roll number, name, or marks              |

---

### 🛠️ Technologies Used
- **C++**
- **File Handling** (binary and text)
- **OOP (Class)**
- **Vector & Algorithm (for sorting)**

---

### 🚀 How to Run

1. **Compile the program** (make sure `g++` is installed):
   ```bash
   g++ main.cpp -o student-record
