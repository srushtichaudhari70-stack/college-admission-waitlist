# 🎓 College Admission Waiting List System

> A **Queue-based** Admission Management System — DS Mini Project

[![Live Demo](https://img.shields.io/badge/Live-Demo-blue?style=for-the-badge)](https://college-admission-waitlist.vercel.app)
![HTML](https://img.shields.io/badge/HTML-CSS-JS-orange?style=for-the-badge)
![C++](https://img.shields.io/badge/C++-17-blue?style=for-the-badge)

---

## 📌 About

A Data Structures mini project that simulates a **college admission waiting list** using a **Queue (FIFO)** data structure. Built in both **C++** (console) and a **Web App** (HTML/CSS/JS).

## 🧠 Data Structure Used

- **Queue** implemented as a **Linked List**
- `front` pointer → next to be processed
- `rear` pointer → last applicant who joined
- Separate linked list for admitted students

## ⚙️ Operations

| Operation | DS Concept | Time Complexity |
|-----------|-----------|----------------|
| Add Applicant | Enqueue (add at rear) | O(1) |
| Process Next | Dequeue (remove from front) | O(1) |
| View Next | Peek front | O(1) |
| Display All | Traverse | O(n) |
| Search by ID | Linear Search | O(n) |
| Clear Queue | Flush | O(n) |

## 🚀 How to Run

### Web App
Just open `index.html` in any browser — no server needed!

### C++ Console App
```bash
g++ admission.cpp -o admission -std=c++17
./admission
```

## 📁 Project Structure

```
├── index.html       # Web app (HTML + CSS + JS)
├── admission.cpp    # C++ console version
└── README.md
```

## 👩‍💻 Author

Made with ❤️ as a Data Structures Mini Project
