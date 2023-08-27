#!/bin/bash

# Run OAI nrUE1 in end-to-end SA mode
#cd openairinterface5g/
source oaienv
cd cmake_targets/ran_build/build

#RFSIMULATOR=127.0.0.1 ./nr-uesoftmodem --noS1 --rfsim --phy-test --uicc0.imsi 001010000057573 --numerology 1 -r 106 --band 78 -C 3619200000 2>&1

RFSIMULATOR=127.0.0.1 ./nr-uesoftmodem --rfsim --phy-test --rrc_config_path . --noS1 --nokrnmod 1
