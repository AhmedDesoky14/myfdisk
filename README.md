# myfdisk

`myfdisk` is a C program designed to display the partitions on a Linux machine. Similar to the `fdisk` program in Linux, it shows key information about the partitions, such as their size, number of sectors, start sector, and end sector. The program supports showing both MBR (Master Boot Record) primary partitions and EBR (Extended Boot Record) logical partitions.

---

## Acknowledgment

This project was developed as part of the **STMicroelectronics Internship Program**, **Linux System Programming**, supervised by **Eng. Reda Maher**.

---

## Features

- **Displays Partition Information**:
  - Size of each partition.
  - Number of sectors in each partition.
  - Start and end sectors of each partition.

- **Supports MBR Primary Partitions**: The program can detect and display primary partitions in the MBR partitioning scheme.

- **Supports EBR Extended Logical Partitions**: It can also detect and display logical partitions in the extended partition scheme.

- **System-Level Interaction**: It interacts with the disk's partition table to gather relevant data, making it a useful tool for understanding disk partitions.

---

## Project Outcomes

- Learn about disk partitioning schemes like MBR and EBR.
- Understand how to interact with low-level system data on Linux systems.
- Gain experience with working with disk-related system calls and handling binary data.
- Improve skills in string manipulation, memory handling, and parsing structured data.
- Explore how partitioning information is stored and retrieved from storage devices.

---

## How to Build

1. Clone the repository:
   ```bash
   git clone https://github.com/AhmedDesoky14/myfdisk
   cd myfdisk
   ```
2. Compile the program:
   ```bash
   make myfdisk
   make install
   ```

---

## Usage

Run the program in the terminal

```bash
myfdisk
```

---

## Contact 

For questions or suggestions, please contact me, Ahmed Desoky at "ahmed0201150@gmail.com".
