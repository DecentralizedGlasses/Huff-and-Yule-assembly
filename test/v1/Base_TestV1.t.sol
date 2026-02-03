// SPDX-License-Identifier: GPL-3.0-only

pragma solidity ^0.8.30;

import {HorseStore} from "src/horseStoreV1/horseStore.sol";
import {IHorseStore} from "src/horseStoreV1/IHorseStore.sol";
import {Test, console2} from "forge-std/Test.sol";

abstract contract Base_TestV1 is Test {
    IHorseStore public horseStore;


    function setUp() public virtual{
        horseStore = IHorseStore(address(new HorseStore()));

    } 

    function testReadValue() public {
        uint256 initialValue = horseStore.readNumberOfHorses();
        assertEq(initialValue, 0);

    }

    function testWriteValue() public {
        uint256 newNumberOfHorses = 745;
        horseStore.updateHorseNumber(newNumberOfHorses);
        assertEq(horseStore.readNumberOfHorses(), newNumberOfHorses);
    }

    
}