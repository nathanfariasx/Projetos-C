#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------João Vitor Braga
// ------------Nathan Farias


int c;//pra o codigo de buffer


// struturas..........
struct aluno {
  int id;
  char nome[50];
  char cpf[16];
  char telefone[17];
  char email[50];
};//ok
typedef struct aluno aluno;

struct professor {
  int id;
  char nome[50];
  char cpf[16];
  char telefone[17];
  char email[50];
};//ok
typedef struct professor prof;

struct turma { 
  int id_turma;
  char tipo_aula;
  int dia_semana;
  char horario[6];
  int id_prof;
  int num_max;
  int num_min; 
  char faixa_etaria[5];
};//ok
typedef struct turma turma;

struct inscricao{
  int i_idaluno;
  int i_idturma;
};//ok
typedef struct inscricao inscricao;


// fim das struturas<<<<<<<

int lerOpcao(int a) { // pede e retorna o valor referente as opções
  int x;
  printf("Digite a opção: ");
  scanf("%d",&x);
  return x;
};//ok

void jumpLine() { // pular linha
  printf("\n\n");
};//ok
/*canceçar_ins()     ---->    função que é chamada dentro ta função fechar_turma() , ela cancela a inscrição dos alunos que estao em turmas que estao sendo canceladas na função em ela é chamada.
recebe como parametro: id (id da turma) , arquivo_inscricao (ponteiro do tipo char que aponta para um texto que é o nome do arquivo)
*/
void cancelar_ins(int id,char *arquivo_inscricao,char *arquivo_inscricao_cancelada,char *arquivo_aux_2){
  
  FILE *ins_1;//arquivo inscrição
  FILE *ins_2;//arquivo inscricao cancelada
  FILE *aux;//arquivo aux/temporario
  int id_1=0;//recebe id aluno
  int id_2=0;//receber id turma
  
  aux = fopen(arquivo_aux_2,"w");//abertura
  ins_1 =fopen(arquivo_inscricao,"rb");//abertura
  ins_2 =fopen(arquivo_inscricao_cancelada,"a");//abertura
 
  while(fscanf(ins_1,"%d %d",&id_1,&id_2)!= EOF){//leitura e salvamento de dados do arquivo inscricao nas variaveis id_1 e  id_2
      if(id_2 == id){//verifica se o id que esta no arquivo é == ao id passado como parametro , se for salvara no arquivo de inscriçãoe canceladas 
        fprintf(ins_2,"%d %d\n",id_1,id_2);//salvando no arquivo de aulas canceladas
       }else{//se o di nao for igual ao id (parametro)
        fprintf(aux,"%d %d\n",id_1,id_2);//salva no arquivo aux/temporario
      }
   } 
  //fechando arquivos
  fclose(ins_1);
  fclose(ins_2);
  fclose(aux);
  
  remove(arquivo_inscricao);//removendo antigo arquivo
  rename(arquivo_aux_2,arquivo_inscricao);//renomeando arquivo temporario
  //o arquivo temporario aonde estao as inscriçãoes da turma que nao foi cancelada se torna o novo arquivo_incricao
 
};//ok




/*obterMax() --->função que obtem o numero max que a turma tem */
int obterMax(int id,char *arquivo_turma){
  FILE *arq;
  arq = fopen(arquivo_turma,"r");
  int max_achei=0;//salva o valor do numero max de alunos 
  int id_turma=0;//variaveis de salvamento
  int dia_sema=0;//variaveis de salvamento
  int id_prof=0;//variaveis de salvamento
  int min=0;//variaveis de salvamento
  int max=0;//variaveis de salvamento
  char tipo;//variaveis de salvamento
  char hora[6];//variaveis de salvamento
  char faixa[5];//variaveis de salvamento
  while(fscanf(arq,"%d %d %d %d %d %c %s %s",&id_turma,&dia_sema,&id_prof,&min,&max,&tipo,hora,faixa)!=EOF){
    if(id_turma == id){//verifica se o id é == ao id passado como parametro, se for ...
      max_achei = max;//salva o numero maximo da turma representada nessa linha 
       }//if
}//while
  fclose(arq);//fecha arquivo
  return max_achei;//retorna o numero maximo
};//ok



/*obterMin() --->função que abtem o numero minimo de alunos que a truma tem */
int obterMin(int id_turma,char *arquivo_turma){
  FILE *arq;
  arq = fopen(arquivo_turma,"r");
  int min_achei=0;
  int id=0;
  int dia_sema=0;
  int id_prof=0;
  int min=0;
  int max=0;
  char tipo;
  char hora[6];
  char faixa[5];
  while(fscanf(arq,"%d %d %d %d %d %c %s %s",&id,&dia_sema,&id_prof,&min,&max,&tipo,hora,faixa)!=EOF){
    if(id == id_turma){
      min_achei = min;
       
    }
}
  fclose(arq);
  return min_achei;
};//ok



/*obter_num_inscritos() ----> função que retorna o numero de inscritos do id turma que foi passado como parametro*/
int obter_num_inscritos(int id_turma,char *arquivo_inscricao){
  FILE *arq_inscr;//arquivo inscrição
  arq_inscr = fopen(arquivo_inscricao,"rb");//abertura
  int cont=0;//contadora de inscritos
  int id_1=0,id_2=0;//variaveis para receber valor do arquivo
  while(fscanf(arq_inscr,"%d %d",&id_1,&id_2)!= EOF){//salvamento nas variaveis
     if(id_2 == id_turma){//verifica se o id é == ao id passado como parametro,se for ...
       cont++;//incrementa +1
     }//if
   }//while
 fclose(arq_inscr);//fecha arquivo
  return cont;//retorna cont(numero de inscritos)
};//ok



/*retorna o numero de inscritos*/
int contadora(int id_turma,char *arquivo_inscricao){
  int id_1=0,id_2=0,cont1=0;//variaveis para receber valor do arquivo
  FILE *arq3;//arquivo inscrição
  arq3 = fopen(arquivo_inscricao,"r");//abertura
  while(fscanf(arq3,"%d %d",&id_1,&id_2)!= EOF){//salvamento nas variaveis
      if(id_2 == id_turma){//verifica se o id é == ao id passado como parametro,se for ...
       cont1++;//incrementa +1
       }//if
  }//while
fclose(arq3);
return cont1;
};//ok



//Solicita um numero de alunos X. Fechar quaisquer turmas que estejam abaixo de X alunos e gera um arquivo r_aulasCanceladas.csv
void fechar_turma(char *arquivo_turma,char *arquivo_inscricao,char *arquivo_turma_c,char *arquivo_aux_tc,char *arquivo_incri_cancelada,char *arquivo_aux_2){

 FILE *arq_1;//arquivo inscricao
 FILE *arq_2;//arquivo turma
 FILE *arq_3;//arquivo turma cancelada
 FILE *arq_4;//arquivo_aux

  arq_1 = fopen(arquivo_inscricao,"r");
  arq_2 = fopen(arquivo_turma,"r");
  arq_3 = fopen(arquivo_turma_c,"a");
  arq_4 = fopen(arquivo_aux_tc,"w");
 
  int nun_inscritos=0;//variveis de salvamento de retorno de func
  int numMin=0;//variveis de salvamento de retorno de func
  int id_turma=0;//variveis de salvamento
  int dia_sema=0;//variveis de salvamento
  int id_prof=0;//variveis de salvamento
  int min=0;//variveis de salvamento
  int max=0;//variveis de salvamento
  char tipo;//variveis de salvamento
  char hora[6];//variveis de salvamento
  char faixa[5];//variveis de salvamento
  while(fscanf(arq_2,"%d %d %d %d %d %c %s %s",&id_turma,&dia_sema,&id_prof,&min,&max,&tipo,hora,faixa)!=EOF){
      nun_inscritos = obter_num_inscritos(id_turma,arquivo_inscricao);//chama função obter_num_inscritos
      numMin = obterMin(id_turma,arquivo_turma);//chama função para obter o minimo
      if (nun_inscritos < numMin){//se for menor que o numero colocado como minimo
       fprintf(arq_3,"%d %d %d %d %d %c %s %s\n",id_turma,dia_sema,id_prof,min,max,tipo,hora,faixa);//salva no arquivo turmas canceladas
        printf("Turmas apagadas com sucesso ! ");
          cancelar_ins(id_turma,arquivo_inscricao,arquivo_incri_cancelada,arquivo_aux_2);//chama a função para tambem cancelar as inscrições de acordo com as aulas canceladas
      }else{//se nao for menor ....
        fprintf(arq_4,"%d %d %d %d %d %c %s %s\n",id_turma,dia_sema,id_prof,min,max,tipo,hora,faixa);//salva no arquivo aux/temporario
     }//else
   } //while
//fechando arquivos
fclose(arq_1);
fclose(arq_2);
fclose(arq_3);
fclose(arq_4); 
  
remove(arquivo_turma);//removendo o arquivo antigo que contem inscrições invalidas
rename(arquivo_aux_tc,arquivo_turma);//renomeando o arquivo aux que contem todas as inscrições que nao foram canceladas
};//ok



/*confirmar_turmas() -----> confirmas as turmas que tem como numero de inscritos um  numero que esta entre min e o max das turmas*/
void confirmar_turmas(char *arquivo_confirma, char *arquivo_turma,char *arquivo_inscricao,char *arquivo_prof){
   
  FILE *aula_c,*arq_turma,*arq_ins,*arq_prof;//arquivos        aulas confirmadas   //  arquivo turma    // arquivo inscrição
  aula_c = fopen(arquivo_confirma,"a");//abertura
  arq_turma = fopen(arquivo_turma,"r");//abertura
  arq_ins = fopen(arquivo_inscricao,"r");//abertura
  arq_prof= fopen(arquivo_prof,"r");
  int id=0;
  int cont =0;
  int dia_sema=0;//variveis de salvamento
  int id_prof=0;//variveis de salvamento
  int min=0;//variveis de salvamento
  int max=0;//variveis de salvamento
  char tipo;//variveis de salvamento
  char hora[6];//variveis de salvamento
  char faixa[5];//variveis de salvamento
  int num_max=0;//variveis de salvamento
  int num_min=0;//variveis de salvamento
  char nome[50];
  int id_prof1=0;
  char nome_prof[50];
  char cpf[16],telefone[17],email[50];
  while(fscanf(arq_turma,"%d %d %d %d %d %c %s %s",&id,&dia_sema,&id_prof,&min,&max,&tipo,hora,faixa)!=EOF){//salvamento de variaveis 
    char linha_professor[400];
          fgets(linha_professor, sizeof(linha_professor), arq_prof);
          {
            int id_professor;
            char professor_cpf[15];
            sscanf(linha_professor, "%d,%[^,],%[^,],%[^,],%[^,]", &id_prof, nome,cpf,telefone,email);
        cont = contadora(id,arquivo_inscricao);//chamando a função que retorna o numero de inscritos
     if(cont >= min && cont <= max){//se estiver entre o min e o max 
      fprintf(aula_c,"%d %d %s %d %d %c %s %s\n",id,dia_sema,nome,min,max,tipo,hora,faixa);//salva no arquivo aulas confirmadas
     }//if
  }//while
fclose(aula_c);//fecha arquivo
fclose(arq_prof);
}
};//ok


//mostra turmas disponiveis depois do usuario tentar se inscreverem uma turma que ja esta lotada
void mostrar_turmas(int id_turma ,char *arquivo_turma){
  int max=0;//variveis de salvamento
  int min=0;//variveis de salvamento
  int id=0;//variveis de salvamento
  int id_prof=0;//variveis de salvamento
  int dia_sema=0;//variveis de salvamento
  char hora[6],faixa[5],tipo;//variveis de salvamento
  char tipo_achei;
  
  FILE *arq2;//arquivo de turma
  arq2 = fopen(arquivo_turma,"r");
  
      while(fscanf(arq2,"%d %d %d %d %d %c %s %s",&id,&dia_sema,&id_prof,&min,&max,&tipo,hora,faixa)!=EOF){ 
        if(id == id_turma){
          tipo_achei = tipo;//acha o tipo fa aula
        }
        if(tipo== tipo_achei){//se for igual ao tipo da aula ....
           if(id_turma != id){//e diferente do id da aula que o usuario digitou para se inscrever
          printf("\n\nID turma : %d | dia da semana : %d  | professor : %d | horario : %s | faixa etaria %s\n\n",id,dia_sema,id_prof,hora,faixa);
          printf("---------------------------------------------------------------------------------------------");
           }
        }
     }
  fclose(arq2);
} //ok


//verifica se o numero de inscritos na turma é maior que seu limite  se estiver retorna 2
int  ver_limite(int cont,int id_turma,char *arquivo_turma){
  
  int saida=0;
  int max=0;
  int min=0;
  int id=0,b=0,i=0;
  char f[6],g[5],h;
  FILE *arq2;
  arq2 = fopen(arquivo_turma,"r");
  
      while(fscanf(arq2,"%d %d %d %d %d %c %s %s",&id,&b,&i,&min,&max,&h,f,g)!=EOF){
        if(id == id_turma){ 
          
          if( cont > max){
            saida = 2;
           }
        }
      }
  fclose(arq2);
  return  saida;
};//ok



//verifica se  o aluno ja é cadastrado na turma que ele digitou caso for ...retorna 1 . e conta o numero de inscritos
int verificaEconta(int id,int id_turma,char *arquivo_inscricao,char *arquivo_turma){
  int id_turma2 = id_turma;
  
  int id_1=0,id_2=0,cont1=0,saida=0,cont2=0;
  FILE *arq3;
  arq3 = fopen(arquivo_inscricao,"r");
  while(fscanf(arq3,"%d %d",&id_1,&id_2)!= EOF){
      if(id_1 == id && id_2 == id_turma){
        saida = 1;
       break;
      }else if(id_1 != id && id_2 == id_turma){
        cont1++;
        cont2 = cont1;
      }
  }
fclose(arq3);
  if(saida == 1){
    return saida;
  }else{
     int aux= ver_limite(cont2,id_turma2,arquivo_turma);
    return aux;
  }
};//ok


//verifica se o id ja existe no arquivo passado como parametro
int verifica_existe(int id,char *arquivo){
  int id_ja_no_aquivo=0;
  int saida =0;
  char nome[50],cpf[16],tele[17],email[50];
  
   FILE *arq;
   arq = fopen(arquivo,"r");
  
   while(fscanf(arq,"%d %s %s %s %s",&id_ja_no_aquivo,nome,cpf,tele,email)!= EOF){
    if(id_ja_no_aquivo == id){
       saida = 1;
     }
   }
  fclose(arq);
  return saida;
};//ok


//cancela a inscrição pedida
void cancelar_inscricao(inscricao *ins,char *arquivo_inscricao,char *arquivo_inscrição_cancelada,char *arquivo_aux){
  int id_aluno=0,id_turma=0;
  FILE *ins_1;
  FILE *ins_2;
  FILE *aux;
  int id_1=0;
  int id_2=0;
  
  aux = fopen(arquivo_aux,"w");
  ins_1 =fopen(arquivo_inscricao,"rb");

  printf("\n\n\n-----------Cancelar Inscrição---------\n\n\n");
  printf("digite o ID do aluno :  ");
  scanf("%d",&id_aluno);
 // jumpline();
  printf("\n\n\ndigite o ID da turma : ");
  scanf("%d",&id_turma);
  //jumpline();
  FILE *arq_aux; 
  char atribui[2];
  ins_2 =fopen(arquivo_inscrição_cancelada,"a");
   while(fscanf(ins_1,"%d %d",&id_1,&id_2)!= EOF){
      if(id_1 == id_aluno && id_2 == id_turma){
        fprintf(ins_2,"%d %d\n",id_1,id_2);
        
    }else if(id_1 != id_aluno){
        fprintf(aux,"%d %d\n",id_1,id_2);
    }
  } 
  fclose(ins_1);
  fclose(ins_2);
  fclose(aux);
   remove(arquivo_inscricao);
      rename(arquivo_aux,arquivo_inscricao);

};//ok

//void cadastro_aluno() -> função que pede o id do aluno e chama a func(verifica_aluno) que caso que se retornar 1 o aluno não é cadastrado caso retorne 0 o aluno é cadastrado.
void cadastro_aluno(aluno *aluno1,char *arquivo_aluno){
        FILE *arq_aluno;
        arq_aluno = fopen(arquivo_aluno,"a");
        if(arq_aluno== NULL){
          printf("Erro 1!");
        }
        int id=0;
        printf("\n\n\n-------------->Cadastro Aluno<----------");
        jumpLine();    
        printf("digite seu ID : ");
        scanf("%d",&id);
     
        if(verifica_existe(id,arquivo_aluno)==1){
          printf("\n\n\nAluno já cadastrado !!\n\n\n");
        }else{
           aluno1->id=id;
           printf("Digite seu nome:  ");
           while ((c = getchar()) != '\n' && c != EOF);
           gets(aluno1->nome);
           jumpLine();
           printf("Digite seu CPF:  ");
           gets(aluno1->cpf);
           jumpLine();
           printf("Digite seu telefone:  ");
           gets(aluno1->telefone);
           jumpLine();
           printf("Digite seu email:  ");
           gets(aluno1->email);
           fprintf(arq_aluno,"%d %s %s %s %s",aluno1->id, aluno1->nome,aluno1->cpf,aluno1->telefone, aluno1->email);
           fprintf(arq_aluno, "\n");
           fclose(arq_aluno);
        }
};//ok


//cadastro de professores
void cadastro_professor(prof *prof1,char *arquivo_professor){
   printf("\n\n\n-------------->Cadastro Professor <----------");
      jumpLine();
      FILE *arq1;
      arq1 = fopen(arquivo_professor,"a");
      if(arq1 == NULL){
      printf("Erro 1!");
     }
      int id_prof=0;
      printf("Digite o ID: ");
      scanf("%d", &id_prof);
      if(verifica_existe(id_prof,arquivo_professor)==1){
         printf("\n\n\nprofessor ja cadastrado !\n\n\n");
      }else{
         jumpLine();
         prof1->id = id_prof;
         printf("Digite o nome:  ");
         while ((c = getchar()) != '\n' && c != EOF);
         gets(prof1->nome);
         jumpLine();
         printf("Digite seu CPF:  ");
         //while ((c = getchar()) != '\n' && c != EOF);
         gets(prof1->cpf);
         jumpLine();
         printf("Digite seu telefone:  ");
         gets(prof1->telefone);
         jumpLine();
         printf("Digite seu email:  ");
         gets(prof1->email);
         jumpLine();
         fprintf(arq1,"%d %s %s %s %s", prof1->id,prof1->nome, prof1->cpf, prof1->telefone,prof1->email);
         fprintf(arq1, "\n");
         fclose(arq1);
      } 
};//ok

//cadastro de turma
void cadastro_turma(turma *turma1,char *arquivo_turma){
      FILE *arq2;
       
      arq2 = fopen(arquivo_turma,"a");
      if(arq2 == NULL){
       printf("Erro 2!");
      }
  
      printf("-------------->Cadastro Turma <----------");
      jumpLine();
      printf("Digite o ID da turma: ");
      scanf("%d",&turma1->id_turma);
      jumpLine();
      
      printf("Digite o dia da semana: ");
      scanf("%d",&turma1->dia_semana);
      jumpLine();
      
      printf("Digite o ID/CPF do professor: ");
      scanf("%d",&turma1->id_prof);
      jumpLine(); 
      
      printf("Digite o número minímo: ");
      scanf("%d",&turma1->num_min);
      jumpLine();
      
      printf("Digite o número máximo: ");
      scanf("%d",&turma1->num_max);
      jumpLine();
      
      printf("Digite o tipo da aula: "); 
      scanf(" %c",&turma1->tipo_aula);
      jumpLine();
    
      printf("Digite o horario da turma: ");
      while ((c = getchar()) != '\n' && c != EOF);
      gets(turma1->horario);
      jumpLine();
      
      printf("Digite a faixa-etária: "); 
      gets(turma1->faixa_etaria);
      fprintf(arq2,"%d %d %d %d %d %c %s %s" ,turma1->id_turma,turma1->dia_semana,turma1->id_prof,turma1->num_min,turma1->num_max,turma1->tipo_aula,turma1->horario,turma1->faixa_etaria);
      fprintf(arq2,"\n");
      fclose(arq2);  
};//ok


//cadastro aluno 
void inscrever_aluno(inscricao *ins,char *arquivo_inscricao,char *arquivo_turma){
     FILE *arq3;
      
     int id_inscricao=0;
     int id_turma=0;
      printf("-------------->Inscrever Aluno <----------");
      jumpLine();
      jumpLine();
      printf("Digite o ID do aluno:");
      scanf("%d",&id_inscricao);
      jumpLine();
      printf("Digite o ID da turma:");
      scanf("%d",&id_turma);
      if(verificaEconta(id_inscricao,id_turma,arquivo_inscricao,arquivo_turma)==1){
        printf("\n\n\nAluno ja inscrito na turma !\n\n\n");
      }else if(verificaEconta(id_inscricao,id_turma,arquivo_inscricao,arquivo_turma)==2){
        printf("Turma lotada !!! \n ---abaixo turmas disponiveis\n\n\n\n");
        mostrar_turmas(id_turma,arquivo_turma);
      }else{ 
        arq3 = fopen(arquivo_inscricao,"a"); 
      if(arq3 == NULL){
        printf("Erro 3!");
      }
        ins->i_idaluno=id_inscricao;
        ins->i_idturma=id_turma;
        fprintf(arq3,"%d %d\n",ins->i_idaluno,ins->i_idturma);
        fclose(arq3); 
      }
       
  jumpLine();
}//ok

int main() { //---------------------------------------------------MAIN
  // variaveis>>>>>
  int opcao=1;
  int i = 0,j=0,k=0,t=0;
  int aluno_aux=0;
//<<<<<<<<<<<<<<<<

//>>>>>>>arquivos 
 char *arquivo_cadastro_aluno = "alunos1.csv";//aquivo_aluno
 char *arquivo_cadastro_professor = "professores.csv";//arquivo professores
 char *arquivo_cadastro_turma = "aulas.csv";//arquvo turma
 char *arquivo_inscricao="inscricoes.csv";//arquivo inscrição
 char *arquivo_inscricao_cancelada="relatorio_incri_canceladas.csv";//aulas canceladas
 char *arquivo_aux="arquivo_aux.csv";//arquivo aul na parte de fechar turmas
 char *arquivo_turmas_canceladas="r_aulasCancelada.csv"; 
 char *arquivo_aux_turma="arq_aux_tc.csv";
 char *arquivo_confirma="aulas_confirmadas.csv";
 char *arquivo_aux_2="arquivo_aux_2.csv";
  //<<<<<<<<<<
  // declaração de structs>>>>
  inscricao ins;
  aluno aluno1;
  prof prof1;
  turma turma1;
  
  //<<<<<<
  printf("\n-------Cadastrar aluno     -> 1");
  printf("\n-------Cadastrar professor -> 2");
  printf("\n-------Cadastrar turma     -> 3");
  printf("\n-------Inscrever aluno     -> 4");
  printf("\n-------Cancelar inscrição  -> 5");
  printf("\n-------Fechar turmas       -> 6");
  printf("\n-------Confirmar turmas    -> 7");
  printf("\n-------Fechar programa     -> 8");
  
  while (opcao > 0 && opcao < 9) {

    printf("\n\n-------------------------Academia superação-----------------------\n\n");
    opcao =lerOpcao(opcao);
    
    switch (opcao) {
      case 1: // 1- Cadastra aluno  
        cadastro_aluno(&aluno1,arquivo_cadastro_aluno);
      break;
     case 2: // 2-  Cadastrar professor
       cadastro_professor(&prof1,arquivo_cadastro_professor);
      break;
     case 3: // 3- Cadastrar turma
       cadastro_turma(&turma1,arquivo_cadastro_turma);
      break;
     case 4: // 4- Inscrever aluno
      inscrever_aluno(&ins,arquivo_inscricao,arquivo_cadastro_turma);
      break;
    case 5: // 5- Cancelar inscrição
      cancelar_inscricao(&ins,arquivo_inscricao,arquivo_inscricao_cancelada,arquivo_aux);
      break;
    case 6: // 6- Fechar turmas
        fechar_turma(arquivo_cadastro_turma,arquivo_inscricao,arquivo_turmas_canceladas,arquivo_aux_turma,arquivo_inscricao_cancelada,arquivo_aux_2);
      break;
    case 7: // 7- Confirmar turmas
     confirmar_turmas(arquivo_confirma,arquivo_cadastro_turma,arquivo_inscricao,arquivo_cadastro_professor);
      break;
    case 8:// 8- Fechar o programa
      printf("-------OBRIGADO POR UTILIZAR NOSSO SISTEMA!-------");
       exit(0);
    break;
   default:
      printf("Opção inválida, tente novamente.\n");
      break;
    } // swith
   
  } // while
 return 0;
} //main
