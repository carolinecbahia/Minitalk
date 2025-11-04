#!/usr/bin/env bash
# tests/run_multi_clients.sh
# Usage: ./tests/run_multi_clients.sh <PID> [N] [MODE] [MSG]
# MODE: sequential | stagger | parallel | jitter
# Example: ./tests/run_multi_clients.sh 12345 10 stagger "hello"

set -euo pipefail

PID=${1:-}
N=${2:-10}
MODE=${3:-stagger}
MSG=${4:-"hello-multi"}

if [ -z "$PID" ]; then
  echo "Usage: $0 <PID> [N] [MODE] [MSG]"
  echo "MODE: sequential | stagger | parallel | jitter"
  exit 1
fi

echo "Testing server PID=$PID with $N clients (mode=$MODE)"

long_msg() {
  # helper to build a ~100-char message if needed
  printf '%s' "$MSG"
}

case "$MODE" in
  sequential)
    for i in $(seq 1 "$N"); do
      ./client "$PID" "${MSG}-$i"
    done
    ;;

  stagger)
    for i in $(seq 1 "$N"); do
      ./client "$PID" "${MSG}-$i" &
      sleep 0.05
    done
    wait
    ;;

  parallel)
    for i in $(seq 1 "$N"); do
      ./client "$PID" "${MSG}-$i" &
    done
    wait
    ;;

  jitter)
    for i in $(seq 1 "$N"); do
      ./client "$PID" "${MSG}-$i" &
      # random sleep between 0 and 200ms
      sleep $(awk -v min=0 -v max=0.2 'BEGIN{srand(); printf "%.3f", min+rand()*(max-min)}')
    done
    wait
    ;;

  longmsg)
    # sends each client a 100-char message
    BASE=$(printf '%0.s0123456789' {1..10})
    for i in $(seq 1 "$N"); do
      ./client "$PID" "${BASE} from client-$i" &
    done
    wait
    ;;

  len)
    # Send messages of a single given length (4th arg)
    LEN=${4:-}
    if [ -z "$LEN" ]; then
      echo "Usage: $0 <PID> [N] len <LENGTH>"
      exit 2
    fi
    gen_msg() {
      local l=$1
      local s=""
      for ((k=0;k<l;k++)); do
        s+=$((k%10))
      done
      printf '%s' "$s"
    }
    MSG_STR=$(gen_msg "$LEN")
    echo "Sending $N clients with messages of length $LEN"
    for i in $(seq 1 "$N"); do
      ./client "$PID" "${MSG_STR} from client-$i" &
      sleep 0.05
    done
    wait
    ;;

  multi-len)
    # Run three rounds with lengths 10, 100 and 500
    gen_msg() {
      local l=$1
      local s=""
      for ((k=0;k<l;k++)); do
        s+=$((k%10))
      done
      printf '%s' "$s"
    }
    for LEN in 10 100 500; do
      MSG_STR=$(gen_msg "$LEN")
      echo "\n=== Round: length=$LEN (spawning $N clients) ==="
      for i in $(seq 1 "$N"); do
        ./client "$PID" "${MSG_STR} from client-$i" &
        sleep 0.05
      done
      wait
      echo "=== Finished round length=$LEN ===\n"
      # small pause between rounds
      sleep 0.5
    done
    ;;

  *)
    echo "Unknown mode: $MODE"
    exit 2
    ;;
esac

echo "All clients finished."
