#!/usr/bin/env bash

# run_multi_clients.sh
# Uso: ./run_multi_clients.sh <SERVER_PID> [NUM_CLIENTS] [CLIENT_BINARY]
# - SERVER_PID: PID do processo do servidor (iniciado em outro terminal)
# - NUM_CLIENTS: opcional, número de clientes concorrentes (padrão: 4)
# - CLIENT_BINARY: opcional, caminho para o binário cliente (padrão: ./client)

set -u

# Cores para facilitar a leitura
GREEN="\033[0;32m"
YELLOW="\033[1;33m"
RED="\033[0;31m"
NC="\033[0m" # Sem Cor

if [ "$#" -lt 1 ]; then
    echo -e "${RED}Erro: Nenhum PID fornecido.${NC}"
    echo -e "Uso: ${YELLOW}./run_multi_clients.sh <PID_DO_SERVIDOR> [NUM_CLIENTS] [CLIENT_BINARY]${NC}"
    echo "Exemplo: ./run_multi_clients.sh 12345 8 ./client"
    echo "Inicie o servidor em outro terminal: ./server &  # pegue o PID com 'echo $!'"
    exit 1
fi

SERVER_PID=$1
NUM_CLIENTS=${2:-4}
CLIENT_BIN=${3:-./client}

if ! [[ "$NUM_CLIENTS" =~ ^[0-9]+$ ]] || [ "$NUM_CLIENTS" -le 0 ]; then
    echo -e "${RED}Erro: NUM_CLIENTS precisa ser um inteiro positivo.${NC}"
    exit 1
fi

# Verifica se o PID existe
if ! kill -0 "$SERVER_PID" 2>/dev/null; then
    echo -e "${RED}Erro: nenhum processo com PID ${SERVER_PID} encontrado.${NC}"
    exit 1
fi

# Tenta detectar se o PID parece ser o servidor deste projeto (opcional)
if [ -r "/proc/${SERVER_PID}/cmdline" ]; then
    cmdline=$(tr '\0' ' ' < /proc/${SERVER_PID}/cmdline)
    if [[ "$cmdline" != *server* && "$cmdline" != *server_bonus* ]]; then
        echo -e "${YELLOW}Aviso: o processo ${SERVER_PID} não parece ser 'server' (cmd: ${cmdline}). Continuando...${NC}"
    fi
fi

# Verifica o binário do cliente
if [ ! -x "$CLIENT_BIN" ]; then
    echo -e "${RED}Erro: binário cliente não encontrado ou não executável: ${CLIENT_BIN}${NC}"
    echo "Compile com 'make' no diretório do projeto. Arquivos principais: 'server' e 'client' (ou 'server_bonus'/'client_bonus')."
    exit 1
fi

echo -e "${GREEN}Iniciando teste: servidor PID=${SERVER_PID}, clientes=${NUM_CLIENTS}, binário='${CLIENT_BIN}'${NC}"

# Mensagens de teste (serão ciclicamente atribuídas aos clientes)
MESSAGES=(
    "Olá!"
    "Teste de string média."
    "Mensagem longa: $(printf '%0.sMuito ' {1..20})fim."
    "Unicode: 🚀✨ 42!"
)

PIDS=()

# Garantir que sinais limpem os filhos
cleanup() {
    echo -e "\n${YELLOW}Limpando clientes em segundo plano...${NC}"
    for p in "${PIDS[@]:-}"; do
        if kill -0 "$p" 2>/dev/null; then
            kill "$p" 2>/dev/null || true
        fi
    done
    wait
    exit 0
}
trap cleanup INT TERM

echo -e "${YELLOW}Lançando ${NUM_CLIENTS} clientes simultâneos...${NC}"

for i in $(seq 1 "$NUM_CLIENTS"); do
    msg_index=$(( (i-1) % ${#MESSAGES[@]} ))
    msg="${MESSAGES[$msg_index]}"
    echo -e "[cliente $i] enviando mensagem: '${msg}'"
    # lança em background e guarda PID
    "$CLIENT_BIN" "$SERVER_PID" "$msg" &
	sleep 0.01
    p=$!
    PIDS+=($p)
    echo -e "[cliente $i] PID=$p"
done

# Aguardar término e coletar status
EXIT_OK=0
for idx in "${!PIDS[@]}"; do
    p=${PIDS[$idx]}
    if wait "$p"; then
        echo -e "${GREEN}[cliente $((idx+1))] PID=$p finalizou com sucesso.${NC}"
    else
        echo -e "${RED}[cliente $((idx+1))] PID=$p terminou com erro.${NC}"
        EXIT_OK=1
    fi
done

if [ "$EXIT_OK" -eq 0 ]; then
    echo -e "${GREEN}Todos os clientes finalizaram com sucesso.${NC}"
else
    echo -e "${RED}Alguns clientes retornaram erro. Verifique o servidor e os logs.${NC}"
fi

echo "Verifique o terminal do servidor para confirmar o recebimento das mensagens."

exit $EXIT_OK