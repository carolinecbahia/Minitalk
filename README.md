# Minitalk

> A lightweight inter-process communication (IPC) program using Unix signals (SIGUSR1 and SIGUSR2). This project was developed as part of the **42 School** curriculum.

[![Language](https://img.shields.io/badge/language-C-blue.svg)]()
[![Grade](https://img.shields.io/badge/grade-125%2F100-brightgreen.svg)]()
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Architecture](#architecture)
- [Performance](#performance)
- [Testing](#testing)
- [Author](#author)

## 🎯 Overview

Minitalk is a minimal but complete implementation of a client-server communication system using Unix signals. It demonstrates deep understanding of process management, signal handling, and bit manipulation in C.

**Key Achievements:**
- ✅ Bidirectional communication between client and server using only signals
- ✅ Supports both mandatory and bonus features
- ✅ Efficient bit-by-bit character transmission
- ✅ Full error handling and validation
- ✅ Server confirmation of message receipt

## ✨ Features

### Mandatory Features
- **Server Program**: Listens for incoming signals and displays received messages
- **Client Program**: Sends messages to the server using SIGUSR1 and SIGUSR2 signals
- **Bit Encoding**: Transmits characters bit-by-bit using signal types
- **Process Communication**: Uses process IDs (PID) for targeted signal delivery

### Bonus Features
- **Server Confirmation**: Server sends acknowledgment after each bit received
- **Multiple Clients**: Server can handle multiple concurrent clients
- **Return Message**: Server can send messages back to the client

## 📦 Requirements

- **OS**: Linux / macOS
- **Compiler**: GCC / Clang with `-Wall -Wextra -Werror`
- **C Standard**: C99 or later
- **Make**: GNU Make 3.81 or later
- **Signal Support**: SIGUSR1, SIGUSR2

## 🚀 Installation

```bash
# Clone the repository
git clone https://github.com/carolinecbahia/Minitalk.git
cd Minitalk

# Build the mandatory version
make

# Build with bonus features
make bonus

# Clean build artifacts
make clean
```

## 💻 Usage

### Start the Server

```bash
# Terminal 1
./server
```

The server will display its PID, which you need to send messages to it.

### Send Messages from Client

```bash
# Terminal 2
./client <SERVER_PID> "Your message here"
```

### Example

```bash
# Terminal 1
$ ./server
5678

# Terminal 2
$ ./client 5678 "Hello World!"
Message received: Hello World!
```

### Bonus Features

```bash
# Build and run bonus version with server confirmation
make bonus
./server_bonus
./client_bonus 5678 "Message with acknowledgment"
```

### Return Codes

- ✅ Returns 0 on successful message delivery
- ❌ Returns 1 on error (invalid PID, signal delivery failure, etc.)

## 🏗️ Architecture

### Project Structure

```
Minitalk/
├── src/                    # Mandatory source files
│   ├── client.c           # Client implementation
│   ├── server.c           # Server implementation
│   ├── client_bonus.c     # Enhanced client with features
│   └── server_bonus.c     # Enhanced server with features
├── includes/
│   └── minitalk.h         # Header with common definitions
├── Libft/                 # Custom C library utilities
├── ft_printf/             # Custom printf implementation
├── Makefile               # Build configuration
└── README.md
```

### Key Components

**Server**: 
- Registers signal handlers for SIGUSR1 and SIGUSR2
- Accumulates incoming bits to reconstruct characters
- Displays received message
- (Bonus) Sends acknowledgment signals back to client

**Client**:
- Converts message characters to binary representation
- Sends each bit as either SIGUSR1 (0) or SIGUSR2 (1)
- Implements delays to ensure signal delivery
- (Bonus) Waits for server acknowledgment before sending next bit

### Algorithm / Approach

**Bit Transmission Protocol:**
1. Client converts each character to 8-bit binary representation
2. For each bit position (MSB to LSB):
   - Sends SIGUSR1 if bit is 0
   - Sends SIGUSR2 if bit is 1
3. Server receives signals and reconstructs the original bit pattern
4. Once 8 bits are received, the character is displayed

**Signal Handling:**
- Uses `sigaction()` for reliable signal handling
- Implements proper signal masking to avoid race conditions
- (Bonus) Uses signal-safe communication for confirmation

## 📊 Performance

### Characteristics

| Aspect | Value | Notes |
|--------|-------|-------|
| Message Length | Unlimited | Limited only by system resources |
| Transmission Speed | ~100-500 chars/sec | Depends on system load |
| Bit Rate | 1 bit/signal | 8 signals per character |
| Signal Latency | <1ms typical | May vary by system |

**Performance Notes**: 
- No CPU spinning; uses efficient signal handling
- Scalable to multiple simultaneous clients (bonus)
- Minimal memory footprint

## 🧪 Testing

### Run Tests

```bash
# Test with basic messages
./server &
SERVER_PID=$!
./client $SERVER_PID "Test message"
./client $SERVER_PID "123456"
./client $SERVER_PID "Special chars: !@#$%"

kill $SERVER_PID
```

### Test Coverage

- ✅ Basic ASCII characters (a-z, A-Z, 0-9)
- ✅ Special characters and symbols
- ✅ Empty strings handling
- ✅ Invalid PID detection
- ✅ Long messages
- ✅ Multiple sequential messages
- ✅ Concurrent clients (bonus)

### Expected Behavior

```
✅ Messages transmitted accurately without corruption
✅ Server continues running after each message
✅ Client exits after successful transmission
✅ Signal delivery success rate: 100% (local testing)
✅ No memory leaks (verified with valgrind)
```

## 🔧 Build Commands

```bash
make              # Compile mandatory version
make bonus        # Compile with bonus features
make clean        # Remove object files
make fclean       # Remove all generated files
make re           # Rebuild everything
```

## 📝 Implementation Details

### Key Functions

| Function | Purpose | Location |
|----------|---------|----------|
| `signal_handler()` | Processes incoming signals | server.c |
| `send_bit()` | Sends single bit via signal | client.c |
| `reconstruct_char()` | Converts bits back to character | server.c |
| `ft_atoi()` | Parses PID from command line | libft/ |

### Data Structures

- **Signal Handler**: Implements bitwise operations to decode transmitted bits
- **PID Management**: Stores process ID for targeted signal delivery
- **Bit Buffer**: Accumulates received bits until full character is formed

### Notable Challenges Solved

1. **Signal Race Conditions**: Used `sigaction()` and proper signal masking to ensure no signals are lost
2. **Bit Timing**: Implemented strategic delays to allow server time to process signals
3. **Bonus Acknowledgment**: Coordinated bidirectional signal flow without deadlocks

## 📚 Learning Outcomes

This project reinforced knowledge in:
- **Unix Signals**: SIGUSR1, SIGUSR2, signal handlers, mask operations
- **Process Management**: PID handling, process communication
- **Bit Manipulation**: Binary representation, bit shifting, masking operations
- **Low-Level IPC**: Alternative to pipes, sockets, and shared memory
- **Signal-Safe Programming**: Understanding race conditions and atomicity

## 🎓 About 42 School

The **42 School** is a coding school that emphasizes peer learning and practical programming skills. Projects are evaluated based on:
- **Mandatory Requirements**: Core IPC functionality
- **Bonus Features**: Server confirmation and multi-client support
- **Code Quality**: Norminette compliance (strict function length, line limits)

## 📄 License

This project is licensed under the MIT License - see [LICENSE](LICENSE) file for details.

## ✍️ Author

**Caroline Bahia**
- GitHub: [@carolinecbahia](https://github.com/carolinecbahia)
- 42 School: cbahia

---

**Project Grade**: 125/100 ⭐  
**Status**: Complete with bonus features  
**Repository**: [GitHub Minitalk](https://github.com/carolinecbahia/Minitalk)
