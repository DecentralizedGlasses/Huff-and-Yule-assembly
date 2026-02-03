// 0x6080604052348015600e575f5ffd5b506101298061001c5f395ff3fe6080604052348015600e575f5ffd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c01714604c575b5f5ffd5b604a60048036038101906046919060a9565b6066565b005b6052606f565b604051605d919060dc565b60405180910390f35b805f8190555050565b5f5f54905090565b5f5ffd5b5f819050919050565b608b81607b565b81146094575f5ffd5b50565b5f8135905060a3816084565b92915050565b5f6020828403121560bb5760ba6077565b5b5f60c6848285016097565b91505092915050565b60d681607b565b82525050565b5f60208201905060ed5f83018460cf565b9291505056fea26469706673582212202b51d3739e2c40de430c2c3b0eb4466ef4d04a7731f9897efb26033e9b9d4d1d64736f6c634300081e0033

// Every byte code we have three parts
// 1. Contract creation byte code
// 2. Runtime Bytecode
// 3. Metadata

PUSH1 0x80  // [0x80]
PUSH1 0x40  // [0x40, 0x80]
MSTORE      // []  free memory pointer.   Stores the value of 0x80, offset by 0x40 into memory
// the above separated section is almost seen in every contract you work with and represents the first part of `Contract Creation Code`
// These opcodes represent free memory pointer

// what this chunk do
// check if a value is being sent with our constructor/contract creation 
// reverts if value is being sent
// jumps over revert to continue the logic if no value is sent
CALLVALUE   // [msg.value]
DUP1        // [msg.value, msg.value]
ISZERO      // [msg.value == 0, msg.value]
PUSH1 0x0e  // [0x0e, ,msg.value == 0, msg.value]
JUMPI       // [msg.value]
PUSH0       // [0x00, msg.value]
PUSH0       // [0x00, 0x00, msg.value]
REVERT      // [msg.value]

// jump dest if msg.value == 0
JUMPDEST        // [msg.value]
POP             // []
PUSH2 0x0129    // [0x0129]
DUP1            // [0x0129, 0x0129]
PUSH2 0x001c    // [0x001c, 0x0129, 0x0129]
PUSH0           // [0x00, 0x001c, 0x0129, 0x0129]
CODECOPY        // [0x0129]            Memory: [runtime code]
PUSH0           // [0x00, 0x0129]
RETURN          // []
INVALID         // []


// 2. Runtime code
// Entry point for all calls
// free memory pointer
PUSH1 0x80
PUSH1 0x40
MSTORE


// checking msg.value if given reverting
CALLVALUE           // [msg.value]
DUP1                // [msg.value, msg.value]
ISZERO              // [msg.value == 0, msg.value]
PUSH1 0x0e          // [0x0e, msg.value ==0 msg.value]
JUMPI               // [msg.value]
PUSH0               // [0x00, msg.value]
PUSH0               // [0x00, 0x00, msg.value]
REVERT              // [msg.value]

// if msg.value == 0 ,start here!
// continue!
// this checks the calldata size of a function selector
JUMPDEST            // [msg.value]
POP                 // []
PUSH1 0x04          // [0x04]  
CALLDATASIZE        // [calldatasize, 0x04]
LT                  // [calldatasize < 0x04]
PUSH1 0x30          // [0x30, calldatasize < 0x04]
JUMPI               // []
// if calldatasize < 0x04 --> calldata_jump

// function dispatching in solidity
PUSH0               // [0x00]
CALLDATALOAD        // [32 bytes of calldata]
PUSH1 0xe0          // [0xe0, 32 bytes calldata]
SHR                 // [calldata[0:4]]   //function_selector

// Dispatching for setNumberOfHorses
DUP1                // [calldata[0:4], calldata[0:4]]
PUSH4 0xcdfead2e    // [0xcdfead2e, calldata[0:4], calldata[0:4]]
EQ                  // [0xcdfead2e == caldata[0:4] , calldata[0:4]]
PUSH1 0x34          // [0x34, 0xcdfead2e == caldata[0:4] , calldata[0:4] ]
JUMPI               // [calldata[0:4]]
// if func_selector == 0xcdfead2e -> set_number_of_horses

// function dispatching for readNumberOfHorses
DUP1                // [calldata[0:4], calldata[0:4]]
PUSH4 0xe026c017    // [0xe026c017, calldata[0:4], calldata[0:4]]
EQ                  // [0xe026c017 == calldata[0:4], calldata[0:4]]
PUSH1 0x4c          // [0x4c, 0xe026c017 == calldata[0:4], calldata[0:4]]
JUMPI               // [calldata[0:4]] // [func_selector]
// if func_selector == 0xe026c017 --> get_number_of_horses

// calldata_jump
// Revert Jumpdest
JUMPDEST            // []
PUSH0               // [0x00]
PUSH0               // [0x00, 0x00]
REVERT              // []

// update horse number jump dest 1
// setup jumping program counters in the stack
JUMPDEST            // [func_selector]
PUSH1 0x4a          // [0x4a, func_selector]
PUSH1 0x04          // [0x04, 0x4a, func_selector]
DUP1                // [0x04, 0x04, 0x4a, func_selector]
CALLDATASIZE        // [ calldatasize, 0x04, 0x04, 0x4a, func_selector]
SUB                 // [calldatasize - 0x04, 0x04, 0x4a, func_selector]
DUP2                // [0x04, calldatasize - 0x04, 0x04, 0x4a, func_selector]
ADD                 // [0x04 + (calldatasize - 0x04), 0x04, 0x4a, func_selector] 
SWAP1               // [0x04, 0x04 + (calldatasize - 0x04), 0x4a, func_selector]
PUSH1 0x46          // [0x46, 0x04, 0x04 + (calldatasize - 0x04), 0x4a, func_selector]
SWAP2               // [0x04 + (calldatasize - 0x04), 0x04, 0x46, 0x4a, func_selector]
SWAP1               // [0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
PUSH1 0xa9          // [0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
JUMP

JUMPDEST
PUSH1 0x66
JUMP

// jump dest 5
JUMPDEST            // [func_selector]
STOP                // [func_selector]


JUMPDEST
PUSH1 0x52
PUSH1 0x6f
JUMP
JUMPDEST
PUSH1 0x40
MLOAD
PUSH1 0x5d
SWAP2
SWAP1
PUSH1 0xdc
JUMP
JUMPDEST
PUSH1 0x40
MLOAD
DUP1
SWAP2
SUB
SWAP1
RETURN

//Jump dest 4
// we can finally run an sstore to save our value ot storage:
// 1. Function Dispatch
// 2. Checked msg.value
// 3. Checked that calldata is long enough 
// 4. Received the number to use from the calldata
JUMPDEST
DUP1
PUSH0
DUP2
SWAP1
SSTORE
POP
POP
JUMP
// jump dest 5

// readMNumberOfHorses jump des 1
// the only jump dest
JUMPDEST
PUSH0
PUSH0
SLOAD
SWAP1
POP
SWAP1
JUMP


JUMPDEST
PUSH0
PUSH0
REVERT
JUMPDEST
PUSH0
DUP2
SWAP1
POP
SWAP2
SWAP1
POP
JUMP


JUMPDEST
PUSH1 0x8b
DUP2
PUSH1 0x7b
JUMP
JUMPDEST
DUP2
EQ
PUSH1 0x94


JUMPI
PUSH0
PUSH0
REVERT

JUMPDEST
POP
JUMP

// updateHorseNumber jump dest 3
// Grab the calldata for updating the horse number
// Delete some stuff in the stack
JUMPDEST
PUSH0
DUP2
CALLDATALOAD
SWAP1
POP
PUSH1 0xa3
DUP2
PUSH1 0x84
JUMP
// jump to jumpdest 4

JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP

// updateNumberOfHorses jump dest 2
// check to see if there is a value to update the horse number to 
// 4 bytes for function selector, 32 bytes for horse number
JUMPDEST            // [0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
PUSH0               // [0x00, 0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
PUSH1 0x20          // [0x20, 0x00, 0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
DUP3                // [0xa9, 0x20, 0x00, 0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
DUP5                // [0x04, 0xa9, 0x20, 0x00, 0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
SUB                 // [0x04 - 0xa9, 0x20, 0x00, 0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
// is there more call data than just the function selector?
SLT                 // [0x04 - 0xa9 < 0x20, 0x00, 0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
ISZERO              // [more_call_data_than_selector?, 0x00, 0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
PUSH1 0xbb          // [0xbb, more_call_data_than_selector?, 0x00, 0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
JUMPI               // [0, 0xa9, 0x04, 0x04 + (calldatasize - 0x04), 0x46, 0x4a, func_selector]
// we are going to jump dest 3 if there is more calldata than:
// function selector + 0x20

// revert if the
PUSH1 0xba
PUSH1 0x77
JUMP
JUMPDEST
JUMPDEST
PUSH0
PUSH1 0xc6
DUP5
DUP3
DUP6
ADD
PUSH1 0x97
JUMP
JUMPDEST
SWAP2
POP
POP
SWAP3
SWAP2
POP
POP
JUMP
JUMPDEST
PUSH1 0xd6
DUP2
PUSH1 0x7b
JUMP
JUMPDEST
DUP3
MSTORE
POP
POP
JUMP
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
ADD
SWAP1
POP
PUSH1 0xed
PUSH0
DUP4
ADD
DUP5
PUSH1 0xcf
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP
INVALID

LOG2
PUSH5 0x6970667358
INVALID

SLT
KECCAK256
INVALID
MLOAD
INVALID
PUSH20 0x9e2c40de430c2c3b0eb4466ef4d04a7731f9897e
INVALID
INVALID
SUB
RETURNDATACOPY
SWAP12
SWAP14
INVALID
SAR
PUSH5 0x736f6c6343
STOP
ADDMOD
INVALID
STOP
CALLER