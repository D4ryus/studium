#! /bin/bash

MULTICAST_ADDRESS="224.0.0.1"
MULTICAST_PORT="1234"
EXECUTABLE="stdbuf -oL ./main $MULTICAST_ADDRESS $MULTICAST_PORT"
GREP="stdbuf -oL grep -v multicast"
tail_plist=""

mkfifo {P1,P2,P3,P4}

touch log.txt
echo "starting simulation." > log.txt
stdbuf -o0 tail -f log.txt &
pids=(`jobs -l % | sed 's/^[^ ]* \+//' | cut -d\  -f1`)
tail_plist="$tail_plist ${pids[0]}"
sleep 0.1
echo "starting P1" >> log.txt
stdbuf -oL tail -f P1 | $EXECUTABLE >> log.txt &
pids=(`jobs -l % | sed 's/^[^ ]* \+//' | cut -d\  -f1`)
tail_plist="$tail_plist ${pids[0]}"
sleep 0.1
echo "starting P2" >> log.txt
stdbuf -oL tail -f P2 | $EXECUTABLE | $GREP >> log.txt &
pids=(`jobs -l % | sed 's/^[^ ]* \+//' | cut -d\  -f1`)
tail_plist="$tail_plist ${pids[0]}"
sleep 0.1
echo "starting P3" >> log.txt
stdbuf -oL tail -f P3 | $EXECUTABLE | $GREP >> log.txt &
pids=(`jobs -l % | sed 's/^[^ ]* \+//' | cut -d\  -f1`)
tail_plist="$tail_plist ${pids[0]}"
sleep 0.1
echo "starting P4" >> log.txt
stdbuf -oL tail -f P4 | $EXECUTABLE | $GREP >> log.txt &
pids=(`jobs -l % | sed 's/^[^ ]* \+//' | cut -d\  -f1`)
tail_plist="$tail_plist ${pids[0]}"

sleep 1

echo "sending request from P1 (10 sec) tick 0.0" >> log.txt
echo "request 1 10000" >> P1
sleep 4.8
echo "sending request from P2 (2 sec)  tick 4.8" >> log.txt
echo "request 1 2000" >> P2
sleep 0.1
echo "sending request from P4 (3 sec)  tick 4.9" >> log.txt
echo "request 1 3000" >> P4
sleep 0.3
echo "sending request from P3 (5 sec)  tick 5.2" >> log.txt
echo "request 1 5000" >> P3
sleep 0.3
sleep 15
echo "quit" >> P1
echo "quit" >> P2
echo "quit" >> P3
echo "quit" >> P4

sleep 1
echo "finished"

kill $tail_plist
rm {P1,P2,P3,P4}
