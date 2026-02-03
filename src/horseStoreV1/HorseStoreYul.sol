// SPDX-License-Identifier: GPL-3.0-only
pragma solidity ^0.8.20;

contract HorseStoreYul {
    uint256 numberOfHorses;

    constructor() payable {}

    function updateHorseNumber(uint256 newNumberOfHorses) external {
        // numberOfHorses = newNumberOfHorses;
        assembly {
            sstore(numberOfHorses.slot, newNumberOfHorses)  // .slot will put your integer slot to number 0, the value of to be stored in that position(newNumberOfHorses)
        }
    }

    function readNumberOfHorses() external view returns (uint256) {
        // return numberOfHorses;
        assembly{
            let num := sload(numberOfHorses.slot)
            mstore(0, num) // stores at zero position num value
            return(0, 0x20) // returns 0th position value in 32 bytes value  
        }
    }
}