#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "bibliotecas/redblack.c"

void telaInicial(){
	printf("\n1-Cadastrar usuario: \n");
	printf("2-Realizar login: \n");
}
void signup(){
	printf("-------------MAXIMO DE 20 CARACTERES-------------\n");
	printf("--LETRAS MAISCULAS E MINUSCULAS NAO SE DIFEREM--\n");
	printf("Informe o Usuario e a Senha: ");
}
void signin(){
	printf("Informe o Usuario e a Senha: ");
}

int main(){

	//declaração de variaveis para o código
	int i = 0;
	arvore_vermelho_preto*t = new_arvore_vermelho_preto();
	FILE *file;
	char line[100];
	int intencao;
	char *vari;
	char usuario[20], senha[20], palavra[20], bancoUsuario[20], bancoSenha[20];
	int cont = 0;
	FILE *arq;
	Criptografia senhaUsuario;
	no_arvore*noSenha;
	no_arvore*noArvore;
	//abrindo o arquivo do banco de palavras para popular a arvore
	if ((file = fopen("arquivos/palavras.txt", "r")) == NULL)	{
		printf("Error! opening file");
		exit(1);
	}

	clock_t begin = clock();

	//populando a arvore red-black
	while ((fgets(line, 100, file)) != NULL)	{
		Criptografia crip;
		crip.palavraReal = strdup(strtok(line, "\n"));
		crip.palavraCriptografada = strtok(line, "\n");
		noArvore = new_no_arvore(crip);
		insert(t, noArvore);
	}
	fclose(file);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC/1000;
	printf("%lf\n",time_spent);

	//aplicação da criptografia aplicada no arquivo redblack.h
	//linhas 138 a 152 é o momento em q a criptografia foi realizada
	//nas linhas 126 130 133 é definido o valor da criptografia
	//levando em conta quantidade de nó que passou
	//quantas vezes foi maior ou menor que o nó
	telaInicial();
	scanf("%d", &intencao);
	
	//este if serve para receber um usuario, informar a senha enviar 
	//a senha para a arvore que ira criptografar, a senha 
	//criptografada sera armazenada em um arquivo de texto junto com o usuario
	if (intencao == 1){
		signup();
		scanf("%s", &usuario);
		scanf("%s", &senha);

		senhaUsuario.palavraReal = strdup(senha);
		senhaUsuario.palavraCriptografada = senha;
		noSenha = new_no_arvore(senhaUsuario);
		insert(t, noSenha);
		
		strcat(usuario, ",");
		strcat(usuario, senhaUsuario.palavraCriptografada);
		strcat(usuario, "\n");
		if ((arq = fopen("banco.txt", "a")) == NULL){
			printf("Error! opening file");
			exit(1);
		}
		fprintf(arq, "%s", usuario);
	}else if (intencao == 2){
		//neste if serve para conectar, usando a comparação das senhas criptografadas
		//como a arvore é estatica, acrescentando apenas na execução e não armazenando, 
		signin();
		scanf("%s", &usuario);
		scanf("%s", &senha);
		if ((arq = fopen("banco.txt", "r")) == NULL){
			printf("Error! opening file");
			exit(1);
		}

		//aqui  o arquivo é percorrido para encontrar os usuarios ja cadastrados
		//e testar se ele existe ou se a senha esta correta, aplicando
		//a criptografia utilizada
		while ((fgets(line, 100, arq)) != NULL){
			cont = 0;
			for (int i = 0; i < strlen(line); i++){
				if (line[i] == ','){
					strcpy(bancoUsuario, palavra);
					strcpy(palavra, " ");
					printf("%s\n", bancoUsuario);
					cont = 0;
				}
				else if (line[i] == '\n'){
					strcpy(bancoSenha, palavra);
					strcpy(palavra, "");
					printf("%s\n", bancoSenha);
					cont = 0;
					if (strcmp(bancoUsuario, usuario) == 0){
						break;
					}
				}
				else{
					palavra[cont] = line[i];
					cont += 1;
				}
			}
			if (strcmp(bancoUsuario, usuario) == 0){
				break;
			}
		}
		if (strcmp(bancoUsuario, usuario) != 0){
			printf("USUARIO NAO ENCONTRADO");
		}
		printf("%s  %s\n", bancoUsuario, bancoSenha);
		senhaUsuario.palavraReal = strdup(senha);
		senhaUsuario.palavraCriptografada = senha;
		noSenha = new_no_arvore(senhaUsuario);
		insert(t, noSenha);
		if (strcmp(senhaUsuario.palavraCriptografada, bancoSenha) == 0){
			printf("Senha CORRETA! Usuario logado!");
		}
		else{
			printf("Senha INCORRETA!!!");

		}
	}
	fclose(arq);
	printf("Senha informada criptografada: %s\n",senhaUsuario.palavraCriptografada);
	//é uma aplicação simples mas da pra ter uma noção de arvore red-black
	//e contextualizar o conteudo visto em aula
	return 0;
}