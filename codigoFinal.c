#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

// structs ===========================================

typedef struct{
	int horasVolun, codVolun, telefoneVolun;
	char nome[60], cpf[30];
}voluntario;

typedef struct{
	int qtdoarAlimento, qtdoarMedicamentos, qtdRoupa;
	char alimento[30], medicamento[30], roupa[30];
	float vMonetario; 
}doacao;

typedef struct{
    char nomeProjeto[20], nomeProduto[20];
    int qtdpessoas, dias, horasTotal, horasMax, horasMin, qtdProduto;
    float valorDoado;
}projeto;

typedef struct{
	char nomeEmpresa[30];
	int telefoneEmpresa, codEmpresa;
}empresa;

typedef struct{
	char nomeAtividade[30], local[30];
	int dia, mes, ano, qtdParticipantes;
}atividade;

typedef struct{
    char nome_certificado[60], cpf_certificado[20];
    int dia_certificado, mes_certificado, ano_certificado, horas_certificado;
}certificado;

// funcoes (menu) ===========================================

void menu(){
	printf("\n====MENU====\n");
	printf("1- Gerenciar voluntarios\n");
	printf("2- Gerenciar doacoes\n");
	printf("3- Gerenciar projetos\n");
	printf("4- Gerenciar empresas parceiras\n");
	printf("5- Gerenciar atividades\n");
	printf("6- Emitir relatorios\n");
	printf("\n7- Finalizar\n");
}

void menuVolun(){
    printf("\n1- Cadastrar voluntario\n");
    printf("2- Dispensar voluntario\n");
    printf("3- Lancar horas\n");
    printf("4- Exibir voluntarios\n");
    printf("\n5- Retornar\n");
}

void menuDoacao(){
    printf("\nInforme o tipo de doacao:\n");
    printf("\n1 - Valor monetario");
    printf("\n2 - Medicamento");
    printf("\n3 - Alimento");
    printf("\n4 - Agasalho\n");
    printf("\n5 - Retornar\n");
}

void menuProjeto(){
    printf("1 - Cadastrar projeto\n");
    printf("2 - Excluir projeto\n");
    printf("3 - Exibir projetos\n");
    printf("4 - Retornar\n\n");
}

void menuEmpresas(){
    printf("\n1 - Cadastrar empresa parceira");
    printf("\n2 - Remover empresa da parceria");
    printf("\n3 - Listar empresas\n\n");
    printf("\n4 - Retornar");
}

void menuAtividade(){
    printf("\n1 - Cadastrar atividade");
    printf("\n2 - Listar atividades\n\n");
    printf("\n3 - Retornar");
}

void menuRelatorio(){
    printf("\n1 - Relatorio de voluntarios");
    printf("\n2 - Relatorio de doacoes");
    printf("\n3 - Certificado de participacao");
    printf("\n4 - Retornar");
}

// voluntario ===========================================

void cadVolun(FILE *p){
	voluntario v;
	
	p=fopen("Voluntario.bin", "ab");
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
	char nomeBusca[30];
	p = fopen("Voluntario.bin", "rb");
	
	printf("\nDigite o nome do voluntario que quer excluir: ");
	fflush(stdin);
	gets(nomeBusca);
		
	if(stricmp(nomeBusca,'\0')!= 0){
		posArq = buscar_nome(p, nomeBusca);
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
					if(strcmp(nomeBusca, v.nome)!= 0)
						fwrite(&v, sizeof(voluntario),1,temp);
					
					fread(&v, sizeof(voluntario), 1, p);
				}
				
				fclose(p);
				fclose(temp);
				remove("Voluntario.bin");
				rename("auxiliar.bin", "Voluntario.bin");
				
			}
			else{
				fclose(p);
			}
		}
		
	getch();
	}
	fclose(p);
}

void lancHoras(FILE *p){

	system("cls");
	voluntario v;
	int posArq, nova_hora;
    char nomeBusca[30];
	
	p = fopen("Voluntario.bin", "rb+");
	
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		printf("\nDigite o nome do voluntario que quer alterar as horas lancadas: ");
        fflush(stdin);
        gets(nomeBusca);
		
        if(stricmp(nomeBusca,'\0')!= 0){
            posArq = buscar_nome(p, nomeBusca);
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
                printf("\nHoras alterada!\n");
            }
        }
	fclose(p);
    }
}

void exibirVolun(FILE *p){
    system("cls");
	voluntario v;
	p = fopen("Voluntario.bin","rb");
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

// doacao ===========================================

void doarValor(FILE *p){
	doacao d;
	p = fopen("Doacao.bin","ab");
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}
	else{
		printf("Digite o valor da doacao: \n");
        scanf("%f", &d.vMonetario);
		fwrite(&d, sizeof(doacao), 1, p);
	}
	system("cls");
	fclose(p);
}

void doarMedicamentos(FILE *p){
    system("cls");
	doacao d;
	p = fopen("Doacao.bin","ab");
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		printf("Digite o nome do medicamento: \n");
        fflush(stdin);
        gets(d.medicamento);
        printf("Quantidade do medicamento: \n");
        scanf("%d", &d.qtdoarMedicamentos);
        fwrite(&d, sizeof(doacao), 1, p);

	}
	system("cls");
	fclose(p);
}

void doarAlimento(FILE *p){
    system("cls");
	doacao d;
	p = fopen("Doacao.bin","ab");
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		printf("Digite o alimento doado: \n");
        fflush(stdin);
        gets(d.alimento);
        printf("Digite a quantidade de alimento doado: ");
        scanf("%d", &d.qtdoarAlimento);
        fwrite(&d, sizeof(doacao), 1, p);

	}
	system("cls");
	fclose(p);
}

void doarAgasalho(FILE *p){
    system("cls");
	doacao d;
	p = fopen("Doacao.bin","ab");
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		printf("Digite o tipo de roupa doada: \n");
        fflush(stdin);
        gets(d.roupa);
        printf("Digite a quantidade de roupa doada: ");
        scanf("%d", &d.qtdRoupa);
            
        fwrite(&d, sizeof(doacao), 1, p);

    }
    system("cls");
    fclose(p);
}

// projetos ===========================================

void cadProj(FILE *p){
    system("cls");
    projeto proj;
    int opcao;

    	p=fopen("Projeto.bin", "ab");
	if(p == NULL){
		printf("\nErro no arquivo");
	}
	else{

        printf("\nDigite o nome do projeto:");fflush(stdin);
        gets(proj.nomeProjeto);
        printf("Quantas pessoas vao participar do projeto?\n");fflush(stdin);
        scanf("%d", &proj.qtdpessoas);
        printf("Quantos dias vai durar o projeto?\n");fflush(stdin);
        scanf("%d", &proj.dias);
        printf("\nQual o total de horas para concluir o projeto:");fflush(stdin);
        scanf("%d", &proj.horasTotal);
        printf("\nMinimo de horas por dia:");fflush(stdin);
        scanf("%d", &proj.horasMin);
        printf("\nMaximo de horas por dia:");fflush(stdin);
        scanf("%d", &proj.horasMax);
        printf("\nInforme a opcao desejada:\n");
        printf("1 - Dinheiro\n");
        printf("2 - Produto fisico\n");
        printf("3 - Produto e dinheiro\n");
        printf("4 - Sair\n\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("\nInfome o valor usado no projeto:");fflush(stdin);
                scanf("%f", &proj.valorDoado);
                strcpy(proj.nomeProduto, "");
                proj.qtdProduto = 0;
                break;
            case 2:
                printf("\nInforme o nome do produto:");fflush(stdin);
                gets(proj.nomeProduto);
                printf("\nInforme a quantidade do produto");
                scanf("%d", &proj.qtdProduto);
                proj.valorDoado = 0;
                break;
            case 3:
                printf("\nInforme o nome do produto:");fflush(stdin);
                gets(proj.nomeProduto);
                printf("\nInfome o valor usado no projeto:");fflush(stdin);
                scanf("%f", &proj.valorDoado);
                printf("\nInforme a quantidade do produto");
                scanf("%d", &proj.qtdProduto);
                break;
            case 4:
                printf("\nSair\n\n");
            default: printf("\nOpcao invalida\n\n");
        }
        fwrite(&proj, sizeof(projeto), 1, p);
    }
    system("cls");
    fclose(p);
}

long int buscar_projeto(FILE *p, char projeto_busca[30]){
	
	projeto proj;
	rewind(p);
	fread(&proj, sizeof(projeto), 1, p);
	while(!feof(p) && stricmp(projeto_busca, proj.nomeProjeto)!=0){
		fread(&proj, sizeof(projeto), 1, p);
	}
	if(!feof(p)){
		return (ftell(p) - sizeof(projeto));
	}
	return -1;
}

void excProj(FILE *p){
	system("cls");
	projeto proj;
	int posArq;
	char projetoBusca[30];
	p = fopen("Projeto.bin", "rb");
	
	printf("\nDigite o nome do projeto que quer excluir: "); fflush(stdin);
	gets(projetoBusca);
		
	if(stricmp(projetoBusca,'\0')!= 0){
		posArq = buscar_projeto(p, projetoBusca);
		if(posArq == -1)
			printf("\nNao encontrado\n");
		else{
			fseek(p, posArq,0);
			fread(&proj, sizeof(projeto),1,p);
         	 printf("\nNome do projeto:%s",proj.nomeProjeto);
            printf("\nQuantas pessoas vao participar do projeto:%d",proj.qtdpessoas);
            printf("\nQuantos dias vai durar o projeto:%d", proj.dias);
            printf("\nQual o total de horas para concluir o projeto:%d", proj.horasTotal);
            printf("\nMinimo de horas por dia:%d", proj.horasMin);
            printf("\nMaximo de horas por dia:%d", proj.horasMax);
            printf("\nInforme o nome do produto:%s", proj.nomeProduto);
            printf("\nInfome o valor usado no projeto:%.2f", proj.valorDoado);
            printf("\nInforme a quantidade do produto:%d\n\n", proj.qtdProduto);

			printf("\nDeseja excluir? (s/n)\n");
			
			if(toupper(getche())=='S'){
				FILE *temp = fopen("auxiliar.bin", "wb");
				rewind(p);
				fread(&proj, sizeof(projeto),1,p);
				while(!feof(p)){
					if(strcmp(projetoBusca, proj.nomeProjeto)!= 0)
						fwrite(&proj, sizeof(projeto),1,temp);
					
					fread(&proj, sizeof(projeto), 1, p);
				}
				
				fclose(p);
				fclose(temp);
				remove("Projeto.bin");
				rename("auxiliar.bin", "Projeto.bin");
				printf("Projeto Excluido com sucesso!");
			}
			else{
				fclose(p);
			}
		}
	getch();
	}
	fclose(p);
}

void exibirProjeto(FILE *p){
     system("cls");
	 projeto proj;
	 p = fopen("Projeto.bin","rb");
	 if(p == NULL){
		printf("\nErro no arquivo :(");
    	}else{
		while(fread(&proj,sizeof(projeto),1,p)==1){
            printf("\nNome do projeto:%s",proj.nomeProjeto);
            printf("\nQuantas pessoas vao participar do projeto:%d",proj.qtdpessoas);
            printf("\nQuantos dias vai durar o projeto:%d", proj.dias);
            printf("\nQual o total de horas para concluir o projeto:%d", proj.horasTotal);
            printf("\nMinimo de horas por dia:%d", proj.horasMin);
            printf("\nMaximo de horas por dia:%d", proj.horasMax);
            printf("\nInforme o nome do produto:%s", proj.nomeProduto);
            printf("\nInfome o valor usado no projeto:%.2f", proj.valorDoado);
            printf("\nInforme a quantidade do produto:%d\n\n", proj.qtdProduto);	
		}
		fclose(p);
    }
}

// Empresas ===============================================

void cadEmp(FILE *p){
    system("cls");
    empresa e;
    int op;

    	p=fopen("Empresas.bin", "ab");
	if(p == NULL){
		printf("\nErro no arquivo");
	}
	else{

        printf("\nDigite o nome da empresa parceira:");fflush(stdin);
        gets(e.nomeEmpresa);
        printf("Codigo da empresa:\n");fflush(stdin);
        scanf("%d", &e.codEmpresa);
        printf("Telefone da empresa:\n");fflush(stdin);
        scanf("%d", &e.telefoneEmpresa);
        fwrite(&e, sizeof(empresa), 1, p);
    }
    system("cls");
    fclose(p);
}

long int buscar_empresa(FILE *p, char empresa_busca[30]){
	
	empresa e;
	rewind(p);
	fread(&e, sizeof(empresa), 1, p);
	while(!feof(p) && stricmp(empresa_busca, e.nomeEmpresa)!=0){
		fread(&e, sizeof(empresa), 1, p);
	}
	if(!feof(p)){
		return (ftell(p) - sizeof(empresa));
	}
	return -1;
}

void excEmp(FILE *p){
    system("cls");
	empresa e;
	int posArq;
	char empresaBusca[30];
	p = fopen("Empresas.bin", "rb");
	
	printf("\nDigite o nome do projeto que quer excluir: "); fflush(stdin);
	gets(empresaBusca);
		
	if(stricmp(empresaBusca,'\0')!= 0){
		posArq = buscar_empresa(p, empresaBusca);
		if(posArq == -1)
			printf("\nNao encontrado\n");
		else{
			fseek(p, posArq,0);
			fread(&e, sizeof(empresa),1,p);
         	printf("\nNome da empresa:%s",e.nomeEmpresa);
            printf("\nCodigo da empresa:%d",e.codEmpresa);
            printf("\nTelefone da empresa:%d", e.telefoneEmpresa);

			printf("\nDeseja excluir? (s/n)\n");
			
			if(toupper(getche())=='S'){
				FILE *temp = fopen("auxiliar.bin", "wb");
				rewind(p);
				fread(&e, sizeof(empresa),1,p);
				while(!feof(p)){
					if(strcmp(empresaBusca, e.nomeEmpresa)!= 0)
						fwrite(&e, sizeof(empresa),1,temp);
					
					fread(&e, sizeof(empresa), 1, p);
				}
				
				fclose(p);
				fclose(temp);
				remove("Empresas.bin");
				rename("auxiliar.bin", "Empresas.bin");
				printf("Projeto Excluido com sucesso!");
			}
			else{
				fclose(p);
			}
		}
	getch();
	}
	fclose(p);
}

void exibirEmpresa(FILE *p){
    system("cls");
	 empresa e;
	 p = fopen("Empresas.bin","rb");
	 if(p == NULL){
		printf("\nErro no arquivo :(");
    	}else{
		while(fread(&e,sizeof(empresa),1,p)==1){
            printf("\nNome da empresa:%s",e.nomeEmpresa);
            printf("\nCodigo da empresa:%d",e.codEmpresa);
            printf("\nTelefone da empresa:%d", e.telefoneEmpresa);
		}
		fclose(p);
    }
}

// ATIVIDADES ===============================================

void cadAtv(FILE *p){
    system("cls");
    atividade a;
    int op;

    	p=fopen("Atividade.bin", "ab");
	if(p == NULL){
		printf("\nErro no arquivo");
	}
	else{

        printf("\nDigite o nome da atividade:");fflush(stdin);
        gets(a.nomeAtividade);
        printf("Local da atividade:\n");fflush(stdin);
        scanf("%d", &a.local);
        printf("Dia da atividade:\n");fflush(stdin);
        scanf("%d", &a.dia);
        printf("Mes da atividade:\n");fflush(stdin);
        scanf("%d", &a.mes);
        printf("Ano da atividade:\n");fflush(stdin);
        scanf("%d", &a.ano);
        printf("Quantidade de participantes:\n");fflush(stdin);
        scanf("%d", &a.qtdParticipantes);
        fwrite(&a, sizeof(atividade), 1, p);
    }
    system("cls");
    fclose(p);
}

void exibirAtividade(FILE *p){
    system("cls");
	atividade a;
	p = fopen("Atividade.bin","rb");
	if(p == NULL){
		printf("\nErro no arquivo :(");
    	}else{
		while(fread(&a,sizeof(atividade),1,p)==1){
            printf("\nNome da atividade: %s",a.nomeAtividade);
            printf("\nData da atividade: %d/%d/%d",a.dia, a.mes, a.ano);
            printf("\nQuantidade de participantes na atividade: %d", a.qtdParticipantes);
		}
		fclose(p);
    }
}

// RELATORIOS ================================================

void relatorio_volun(FILE *p){
    system("cls");
	voluntario v;
	p = fopen("Voluntario.bin","rb");
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

void relatorio_doacao(FILE *p){
    system("cls");
	doacao d;
	p = fopen("Doacao.bin","rb");
	if(p == NULL){
		printf("\nErro no arquivo :(");
	}else{
		while(fread(&d,sizeof(doacao),1,p)==1){
			printf("====== DOACAO MONETARIA ======");
            printf("\nValor: %.2f\n", d.vMonetario);
			printf("====== DOACAO MEDICAMENTO ======");
            printf("\nMedicamento: %s\n", d.medicamento);
			printf("\nQuantidade: %d\n", d.qtdoarMedicamentos);
			printf("====== DOACAO ROUPAS ======");
            printf("\nRoupa: %s\n", d.roupa);
            printf("\nQuantidade: %d\n", d.qtdRoupa);
		    printf("====== DOACAO ALIMENTO ======");
            printf("\nAlimento: %s\n", d.alimento);
            printf("\nQuantidade: %d\n", d.qtdoarAlimento);
        }
		fclose(p);
	}
}

void relatorio_certificado(FILE *p){
    system("cls");
    certificado c;
    int op;

    	p=fopen("Certificado.bin", "ab");
	if(p == NULL){
		printf("\nErro no arquivo");
	}
	else{

        printf("\nDigite o nome do voluntario:");fflush(stdin);
        gets(c.nome_certificado);
        printf("\nDigite o CPF do voluntario:");fflush(stdin);
        gets(c.cpf_certificado);
        printf("Dia para colocar no certificado:\n");fflush(stdin);
        scanf("%d", &c.dia_certificado);
        printf("Mes para colocar no certificado:\n");fflush(stdin);
        scanf("%d", &c.mes_certificado);
        printf("Ano para colocar no certificado:\n");fflush(stdin);
        scanf("%d", &c.ano_certificado);
        printf("Digite a quantidade de horas ganhas:\n"),fflush(stdin);
        scanf("%d", &c.horas_certificado);

        printf("\nO voluntario %s, portador do CPF: %s, realizou atividade/trabalho voluntario na data %d/%d/%d. Com isso, recebeu um total de %d horas.\n",c.nome_certificado, c.cpf_certificado, c.dia_certificado, c.mes_certificado, c.ano_certificado, c.horas_certificado);
        fwrite(&c, sizeof(certificado), 1, p);
    }
    system("pause");
    fclose(p);
}

main()
{
	FILE *p;
	int opM, opSM;
	do{
		menu();
		scanf("%d", &opM);
		if(opM == 1){
			system("cls");
			menuVolun();
            scanf("%d", &opSM);

            while(opSM != 5){
                if(opSM == 1){
                    system("cls");
                    cadVolun(p);
                }

                if(opSM == 2){
                    system("cls");
                    excVolun(p);
                }

                if(opSM == 3){
                    system("cls");
                    lancHoras(p);
                }

                if(opSM == 4){
                    system("cls");
                    exibirVolun(p);
                }
                
                menuVolun();
	            scanf("%d", &opSM);
            }
		}
			
		if(opM == 2){
            system("cls");
            menuDoacao();
            scanf("%d", &opSM);

            while(opSM != 5){
                if(opSM == 1){
                    system("cls");
                    doarValor(p);
                }

                if(opSM == 2){
                    system("cls");
                    doarMedicamentos(p);
                }

                if(opSM == 3){
                    system("cls");
                    doarAlimento(p);
                }

                if(opSM == 4){
                    system("cls");
                    doarAgasalho(p);
                }

                menuDoacao();
                scanf("%d", &opSM);
            }
        }
		
		if(opM == 3){
            system("cls");
			menuProjeto();
            scanf("%d", &opSM);

            while(opSM != 4){
                if(opSM == 1){
                    system("cls");
                    cadProj(p);
                }

                if(opSM == 2){
                    system("cls");
                    excProj(p);
                }

                if(opSM == 3){
                    system("cls");
                    exibirProjeto(p);
                }

                menuProjeto();
                scanf("%d", &opSM);
            }
		}
		
		if(opM == 4){
            system("cls");
			menuEmpresas();
            scanf("%d", &opSM);

            while(opSM != 4){
                if(opSM == 1){
                    system("cls");
                    cadEmp(p);
                }

                if(opSM == 2){
                    system("cls");
                    excEmp(p);
                }

                if(opSM == 3){
                    system("cls");
                    exibirEmpresa(p);
                }
                menuEmpresas();
                scanf("%d", &opSM);
            }
		}
		
		if(opM == 5){
            system("cls");
			
			menuAtividade();
            scanf("%d", &opSM);

            while(opSM != 3){
                if(opSM == 1){
                    system("cls");
                    cadAtv(p);
                }

                if(opSM == 2){
                    system("cls");
                    exibirAtividade(p);
                }
            menuAtividade();
            scanf("%d", &opSM);
		    }
		}
		
		if(opM == 6){
            system("cls");
			menuRelatorio();
            scanf("%d", &opSM);

            while(opSM != 4){
                if(opSM == 1){
                    system("cls");
                    relatorio_volun(p);
                }

                if(opSM == 2){
                    system("cls");
                    relatorio_doacao(p);
                }
				
                if(opSM == 3){
                    system("cls");
                    relatorio_certificado(p);
                }
			    menuRelatorio();
                scanf("%d", &opSM);
            }
		}
	}while(opM != 7);

    printf("\nObrigada por acessar o programa!\n");
	system("pause");
}
