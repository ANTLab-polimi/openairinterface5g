# Run OAI gNB
#cd openairinterface5g/
source oaienv
rootf=$(pwd)
cd cmake_targets/ran_build/build/


RFSIMULATOR=server ./nr-softmodem -O $rootf/gnb_rfsim.conf --noS1 --nokrnmod 1 --parallel-config PARALLEL_SINGLE_THREAD --rfsim --phy-test --telnetsrv --rfsimulator.options chanmod --rfsimulator.modelname AWGN -s 2
