// SPDX-License-Identifier: GPL-3.0-only

pragma solidity ^0.8.30;

import {Base_TestV1, IHorseStore} from "./Base_TestV1.t.sol";
import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";

contract HorseStoreHuff is Base_TestV1 {
    string public constant HORSE_STORE_HUFF_LOCATION = "horseStoreV1/HorseStore"; // it assumes all the searching files are in `src` folder, and only looking for `.huff` files, that's the reason we're not giving extension here
    function setUp() public override{
        horseStore = IHorseStore(HuffDeployer.config().deploy(HORSE_STORE_HUFF_LOCATION));
    }
}