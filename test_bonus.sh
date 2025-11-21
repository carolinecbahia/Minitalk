#!/bin/bash

# --- Configurações Visuais ---
GREEN="\033[0;32m"
BLUE="\033[0;34m"
YELLOW="\033[1;33m"
RED="\033[0;31m"
NC="\033[0m"
BOLD="\033[1m"

echo -e "${BLUE}${BOLD}=== INICIANDO TESTES DE BÔNUS MINITALK ===${NC}\n"

# --- 1. Verificação dos Executáveis Bônus ---
# O subject exige nomes diferentes para os bônus
if [ ! -f ./server_bonus ] || [ ! -f ./client_bonus ]; then
    echo -e "${RED}[ERRO] Executáveis bônus não encontrados.${NC}"
    echo "O subject exige 'server_bonus' e 'client_bonus'."
    echo "Execute: make bonus"
    exit 1
fi

# --- 2. Iniciar Server Bônus ---
echo -e "${YELLOW}[INFO] Iniciando server_bonus em background...${NC}"
./server_bonus > server_log.txt &
SERVER_PID=$!
sleep 1 # Espera o servidor iniciar

echo -e "${GREEN}[OK] Servidor rodando no PID: $SERVER_PID${NC}\n"

# --- 3. Teste de Unicode (Emoji e Acentos) ---
MSG_UNICODE="Teste Bônus: Acentuação (ç, ã, ó) e Emojis: 🚀🔥💀"
echo -e "${YELLOW}[TESTE 1] Enviando Unicode...${NC}"
echo "Enviando: \"$MSG_UNICODE\""

# Captura a saída do CLIENTE para verificar se ele recebe a confirmação
CLIENT_OUTPUT=$(./client_bonus $SERVER_PID "$MSG_UNICODE")

echo -e "Saída do Cliente: $CLIENT_OUTPUT"

# Verifica se o cliente recebeu o sinal de volta (procura a palavra "Sucesso" ou similar que você colocou no printf)
if echo "$CLIENT_OUTPUT" | grep -q -E "Sucesso|Success|Recebido|Confirmed"; then
    echo -e "${GREEN}[PASS] O Cliente confirmou o recebimento!${NC}"
else
    echo -e "${RED}[FAIL] O Cliente não imprimiu mensagem de sucesso (SIGUSR2 não recebido?).${NC}"
fi
echo "------------------------------------------------"

# --- 4. Teste de Mensagem Longa (Estabilidade) ---
# Gera uma string de 1000 caracteres
MSG_LONG=$(printf 'A%.0s' {1..1000})
echo -e "${YELLOW}[TESTE 2] Enviando string longa (1000 chars)...${NC}"

./client_bonus $SERVER_PID "InicioLonga-$MSG_LONG-FimLonga" > /dev/null

# Verifica o log do servidor para ver se chegou
# (Usamos grep no arquivo de log para não poluir o terminal)
sleep 2 # Tempo para transmissão
if grep -q "InicioLonga" server_log.txt && grep -q "FimLonga" server_log.txt; then
     echo -e "${GREEN}[PASS] Servidor recebeu a string longa completa.${NC}"
else
     echo -e "${RED}[FAIL] String longa corrompida ou incompleta.${NC}"
fi
echo "------------------------------------------------"

# --- 5. Teste de Sinais de Controle (Mensagem Vazia) ---
echo -e "${YELLOW}[TESTE 3] Enviando string vazia...${NC}"
./client_bonus $SERVER_PID ""
echo -e "${GREEN}[PASS] Cliente rodou sem travar.${NC}"

# --- Finalização ---
echo -e "\n${BLUE}${BOLD}=== RESULTADO FINAL NO SERVIDOR ===${NC}"
echo "Conteúdo recebido pelo server_bonus:"
cat server_log.txt

# Limpeza
kill $SERVER_PID
rm server_log.txt

echo -e "\n${GREEN}Testes concluídos.${NC}"