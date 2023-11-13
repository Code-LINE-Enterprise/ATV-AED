#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

typedef struct{
	int horasVolun, codVolun, telefoneVolun;
	char nome[60], cpf[30];
}voluntario;

typedef struct{
	int qtdAlimento, qtdMedicamento, qtdRoupa;
	char alimento[30], medicamento[30], roupa[30];
	float vMonetario; 
}doacao;

typedef struct{
    char nomeP[20], produto[100];
    int qtdpessoas, dias, horasTotal, horasMax, horasMin;
}projeto;

typedef struct{
	char nomeEmpresa[30];
	int telefoneEmpresa, codEmpresa;
}empresa;

typedef struct{
	char atividade[30], local[30];
	int dia, mes, ano, qtdParticipantes;
}atividade;

void menu(){
	printf("\n====MENU====\n");
	printf("1- Gerenciar voluntarios\n");
	printf("2- Gerenciar doacoes\n");
	printf("3- Gerenciar projetos\n");
	printf("4- Gerenciar empresas parceiras\n");
	printf("5- Gerenciar atividades\n");
	printf("6- Emitir relatorios\n");
	printf("7- Finalizar\n\n");
}

void cadVolun(FILE *p){
	voluntario v;
	
	p=fopen("arquivo.bin", "ab");
	if(p == NULL){
		printf("\nErro no arquivo");
	}
	else{
		printf("Nome do voluntario: \n");
		fflush(stdin);
		gets(v.nome);
		printf("CPF: \n");
		fflush(stdin);
		gets(v.cpf);
		printf("Codigo voluntario: \n");
		scanf("%d", &v.codVolun);
        printf("Telefone: \n");
        scanf("%d", &v.telefoneVolun);
        printf("Horas: \n");
        scanf("%d", &v.horasVolun);
        
		fwrite(&v, sizeof(voluntario), 1, p);
        }

	system("cls");
	fclose(p);
}

long int buscar_nome(FILE *p, char nome_busca[30]){
	
	voluntario v;
	rewind(p);
	fread(&v, sizeof(voluntario), 1, p);
	while(!feof(p) && stricmp(nome_busca, v.nome)!=0){
		fread(&v, sizeof(voluntario), 1, p);
	}
	if(!feof(p)){
		return (ftell(p) - sizeof(voluntario));
	}
	return -1;
}

void excVolun(FILE *p){
	system("cls");
	voluntario v;
	int posArq;
	char nomeB[30];
	p = fopen("arquivo.bin", "rb");
	
	printf("\nDigite o nome do voluntario que quer excluir: ");
	fflush(stdin);
	gets(nomeB);
		
	if(stricmp(nomeB,'\0')!= 0){
		posArq = buscar_nome(p, nomeB);
		if(posArq == -1)
			printf("\nNao encontrado");
		else{
			fseek(p, posArq,0);
			fread(&v, sizeof(voluntario),1,p);
			printf("\nCodigo: %d", v.codVolun);
			printf("\nNome do voluntario: %s", v.nome);
			printf("\nCPF: %s", v.cpf);
			printf("\nTelefone: %d", v.telefoneVolun);

			printf("\nDeseja excluir? (s/n)\n");
			
			if(toupper(getche())=='S'){
				FILE *temp = fopen("auxiliar.bin", "wb");
				rewind(p);
				fread(&v, sizeof(voluntario),1,p);
				while(!feof(p)){
					if(strcmp(nomeB, v.nome)!= 0)
						fwrite(&v, sizeof(voluntario),1,temp);
					
					fread(&v, sizeof(voluntario), 1, p);
				}
				
				fclose(p);
				fclose(temp);
				remove("arquivo.bin");
				rename("auxiliar.bin", "arquivo.bin");
				
			}
			else{
				fclose(p);
			}
		}
	}getch();
	fclose(p);
}

void lancHoras(FILE *p){

	system("cls");
	voluntario v;
	int posArq, nova_hora;
    char nomeB[30];
	
	p = fopen("arquivo.bin", "rb+");
	
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		printf("\nDigite o nome do voluntario que quer alterar as horas lancadas: ");
        fflush(stdin);
        gets(nomeB);
		
        if(stricmp(nomeB,'\0')!= 0){
            posArq = buscar_nome(p, nomeB);
            if(posArq == -1)
                printf("\nNao encontrado");
            else{
                fseek(p,posArq,0);
                fread(&v,sizeof(voluntario),1,p);
                
                printf("\nVoluntario encontrado!");
                printf("\nCodigo: %d", v.codVolun);
                printf("\nNome do voluntario: %s", v.nome);
                printf("\nCPF: %s", v.cpf);
                printf("\nTelefone: %d", v.telefoneVolun);
                printf("\nHoras: %d", v.horasVolun);
                
                printf("\n\n");
                printf("\nDigite a nova hora para o voluntario: ");
                scanf("%d", &v.horasVolun);
                fseek(p,posArq,0);
                fwrite(&v,sizeof(voluntario),1,p);
                printf("\nHoras alterada!");
            }
        }
	fclose(p);
    }
}

void geralVolun(FILE *p){
    system("cls");
	voluntario v;
	p = fopen("arquivo.bin","rb");
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		while(fread(&v,sizeof(voluntario),1,p)==1){
			printf("\nCodigo: %d", v.codVolun);
			printf("\nNome do voluntario: %s", v.nome);
			printf("\nCPF: %s", v.cpf);
			printf("\nTelefone: %d", v.telefoneVolun);
            printf("\nHoras: %d\n", v.horasVolun);
		}
		fclose(p);
	}
}

void dMonetario(FILE *p){
    system("cls");
	doacao d;
	p = fopen("arquivo.bin","rb");
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		while(fread(&d,sizeof(doacao),1,p)==1){
			printf("Digite o valor da doacao: \n");
            scanf("%f", &d.vMonetario);
		}
		fclose(p);
	}
}

void dMedicamento(FILE *p){
    system("cls");
	doacao d;
	p = fopen("arquivo.bin","rb");
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		while(fread(&d,sizeof(doacao),1,p)==1){
			printf("Digite o nome do medicamento: \n");
            fflush(stdin);
            gets(d.medicamento);
            printf("Quantidade do medicamento: \n");
            scanf("%d", &d.qtdMedicamento);
		}
		fclose(p);
	}
}

void dAlimento(FILE *p){
    system("cls");
	doacao d;
	p = fopen("arquivo.bin","rb");
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		while(fread(&d,sizeof(doacao),1,p)==1){
			printf("Digite o alimento doado: \n");
            fflush(stdin);
            gets(d.alimento);
            printf("Digite a quantidade de alimento doado: ");
            scanf("%d", &d.qtdAlimento);
		}
		fclose(p);
	}
}

void dAgasalho(FILE *p){
    system("cls");
	doacao d;
	p = fopen("arquivo.bin","rb");
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		while(fread(&d,sizeof(doacao),1,p)==1){
			printf("Digite o tipo de roupa doada: \n");
            fflush(stdin);
            gets(d.roupa);
            printf("Digite a quantidade de roupa doada: ");
            scanf("%d", &d.qtdRoupa);
		}
		fclose(p);
    }
}

void cadProj(FILE *p){

}

void excProj(FILE *p){

}

void geralProj(FILE *p){

}

main()
{
	FILE *p;
	int op;
	do{
		menu();
		scanf("%d", &op);
		if(op == 1){
			system("cls");
			printf("1- Cadastrar voluntario\n");
            printf("2- Dispensar voluntario\n");
            printf("3- Lancar horas\n");
            printf("4- Exibir voluntarios\n");
            printf("5- Retornar\n\n");
            scanf("%d", &op);

            while(op != 5){
                if(op == 1){
                    system("cls");
                    cadVolun(p);
                }

                if(op == 2){
                    system("cls");
                    excVolun(p);
                }

                if(op == 3){
                    system("cls");
                    lancHoras(p);
                }

                if(op == 4){
                    system("cls");
                    geralVolun(p);
                }
                
                printf("1- Cadastrar voluntario\n");
	            printf("2- Dispensar voluntario\n");
	            printf("3- Lancar horas\n");
	            printf("4- Exibir voluntarios\n");
	            printf("5- Retornar\n\n");
	            scanf("%d", &op);
            }
		}
			
		if(op == 2){
            system("cls");
			printf("\nInforme o tipo de doacao:\n");
            printf("\n1 - Valor monetario");
            printf("\n2 - Medicamento");
            printf("\n3 - Alimento");
            printf("\n4 - Agasalho\n\n");
            printf("\n5 - Retornar");
            scanf("%d", &op);

            while(op != 5){
                if(op == 1){
                    system("cls");
                    dMonetario(p);
                }

                if(op == 2){
                    system("cls");
                    dMedicamento(p);
                }

                if(op == 3){
                    system("cls");
                    dAlimento(p);
                }

                if(op == 4){
                    system("cls");
                    dAgasalho(p);
                }

                printf("\nInforme o tipo de doacao:\n");
                printf("\n1 - Valor monetario");
                printf("\n2 - Medicamento");
                printf("\n3 - Alimento");
                printf("\n4 - Agasalho\n\n");
                printf("\n5 - Retornar");
                scanf("%d", &op);
            }
        }
		
		if(op == 3){
            system("cls");
			printf("1 - Cadastrar projeto\n");
            printf("2 - Excluir projeto\n");
            printf("3 - Exibir projetos\n");
            printf("4 - Retornar\n\n");
            scanf("%d", &op);

            while(op != 4){
                if(op == 1){
                    system("cls");
                    cadProj(p);
                }

                if(op == 2){
                    system("cls");
                    excProj();
                }

                if(op == 3){
                    system("cls");
                    geralProj();
                }
            }
		}
		
		if(op == 4){
            system("cls");
			printf("\n1 - Cadastrar empresa parceira");
            printf("\n2 - Remover empresa da parceria");
            printf("\n3 - Listar empresas\n\n");
            printf("\n4 - Retornar");
            scanf("%d", &op);

            while(op != 4){
                if(op == 1){
                    system("cls");
                    cadEmp(p);
                }

                if(op == 2){
                    system("cls");
                    excEmp();
                }

                if(op == 3){
                    system("cls");
                    geralEmp();
                }

            }
		}
		
		if(op == 5){
            system("cls");
			printf("\n1 - Cadastrar atividade");
            printf("\n2 - Listar atividades\n\n");
            printf("\n3 - Retornar");
            scanf("%d", &op);

            while(op != 3){
                if(op == 1){
                    system("cls");
                    cadAtv(p);
                }

                if(op == 2){
                    system("cls");
                    geralAtv();
                }
            }
		}
		
		if(op == 6){
            system("cls");
			printf("\n1 - Relatorio de voluntarios");
            printf("\n2 - Relatorio de doacoes");
            printf("\n3 - Certificado de participacao");
            printf("\n4 - Retornar");
            scanf("%d", &op);

            while(op != 4){
                if(op == 1){
                    system("cls");
                    relatorio_volun(p);
                }

                if(op == 2){
                    system("cls");
                    relatorio_doacao();
                }

                if(op == 3){
                    system("cls");
                    certificado();
                }
            }
		}
	}while(op != 7);

    printf("\nObrigada por acessar o programa!\n");
	system("pause");
}