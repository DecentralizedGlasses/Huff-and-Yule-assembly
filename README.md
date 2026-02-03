# Horse Store

1. write a basic simplestorage/horse store


Here is an updated **README.md** section you can paste into your repo that specifically explains how to run / compile **Yul** and **Huff** files.
You can merge this into the earlier README or replace the “Smart Contract” section.

---

````markdown
# 🐴 Horse Store

A decentralized prototype project exploring high-level Solidity as well as **low-level EVM languages** like **Yul** and **Huff**.  
This repository is mainly for learning, experimentation, and understanding gas-efficient contract design.

---

## 📦 Project Structure

| Folder | Purpose |
|--------|--------|
| `src/` | Main Solidity contracts / front-end logic |
| `test/` | Contract tests |
| `yul/` | Yul smart contracts |
| `huff/` | Huff smart contracts |
| `lib/` | External dependencies |
| `.github/` | CI workflows |

---

## ⚙️ Requirements

Make sure you have the following installed:

- **Node.js v18+**
- **Git**
- **Foundry** → https://book.getfoundry.sh/
- **Huff Compiler** → https://docs.huff.sh/get-started/installing/
- (Optional) **Hardhat**

---

## 🧩 Installation

```bash
git clone https://github.com/DecentralizedGlasses/horse-store.git
cd horse-store
npm install
````

---

## 🛠 Running Solidity Contracts (Foundry)

```bash
forge build
forge test
```

---

## 🧪 Running Yul Contracts

Yul contracts are low-level EVM contracts compiled with **Solc**.

### Compile Yul

```bash
solc --strict-assembly yul/HorseStore.yul --bin --optimize -o build/
```

This generates the bytecode inside the `build/` folder.

### Deploy Yul Contract (Local Anvil)

```bash
anvil
```

Then in another terminal:

```bash
cast send <PRIVATE_KEY> \
--create build/HorseStore.bin \
--rpc-url http://127.0.0.1:8545
```

---

## 🧪 Running Huff Contracts

Huff is an even lower-level language designed for **gas-optimized contracts**.

### Compile Huff

```bash
huffc huff/HorseStore.huff -b -o build/
```

This produces the `.bin` bytecode file.

### Deploy Huff Contract

```bash
anvil
```

Then:

```bash
cast send <PRIVATE_KEY> \
--create build/HorseStore.bin \
--rpc-url http://127.0.0.1:8545
```

---

## 📱 Running Frontend (If Included)

```bash
npm run dev
```

Visit `http://localhost:3000`

---

## 🧠 Why Yul & Huff?

* **Yul** → Intermediate low-level language used by Solidity compiler.
* **Huff** → Assembly-like language with extreme gas efficiency.
* Great for learning EVM internals, opcodes, and optimization.

---

## 🧪 Testing

```bash
forge test -vv
```

---

## 🤝 Contributing

Pull requests welcome — especially improvements to gas optimization or opcode efficiency.

---

## 📝 License

MIT

```

This gives clear **step-by-step commands** for:

• compiling Yul  
• compiling Huff  
• deploying locally  
• understanding why they exist  

It matches the learning / experimentation nature of your repo.
```
