#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

/*
    estrutura da matriz:
    [
    [cod,percentual,nota1,nota2,media],
    ...
    ]
*/

void gotoxy(int x, int y);
int setColor(char color);
void escreveTexto(int x, int y, char texto[], int cor);
void desenhaMenu(int op);
void desenhaNenhumCadastrado();
void iniciaArray(double projetos[30][5]);
void cadastrarProjeto(double projetos[30][5]);
void cadastrarNotas(double projetos[30][5]);
void verProjetos(double projetos[30][5]);
double mediaGeral(double projetos[30][5]);
void maiorEmenorMedia(double projetos[30][5]);
void contarProjetosAcimaMedia(double projetos[30][5]);
void exibirNotasCrescente(double projetos[30][5]);
void menorQueSeteEmUma(double projetos[30][5]);
void mostraClassificados(double projetos[30][5]);
void sair();

int main()
{
    double projetos[30][5];
    int op = 1;
    char t;

    setColor(15);
    iniciaArray(projetos);
    desenhaMenu(op);

    do
    {
        t = getch();

        if (t <= 0 || t == -32)
        {
            t = getch();
            if (t == 80)
            {
                if (op != 10)
                    op++;
                else
                    op = 1;
                desenhaMenu(op);
            }
            else if (t == 72)
            {
                if (op != 1)
                    op--;
                else
                    op = 10;
                desenhaMenu(op);
            }
        }
        else if (t == 13)
        {
            system("cls");
            switch (op)
            {
            case 1:
                cadastrarProjeto(projetos);
                break;
            case 2:
                cadastrarNotas(projetos);
                break;
            case 3:
                verProjetos(projetos);
                break;
            case 4:
                mediaGeral(projetos);
                break;
            case 5:
                maiorEmenorMedia(projetos);
                break;
            case 6:
                contarProjetosAcimaMedia(projetos);
                break;
            case 7:
                exibirNotasCrescente(projetos);
                break;
            case 8:
                menorQueSeteEmUma(projetos);
                break;
            case 9:
                mostraClassificados(projetos);
                break;
            case 10:
                sair();
                return 0;
            }
            printf("\nPressione qualquer tecla para voltar ao menu...");
            getch();
            desenhaMenu(op);
        }
    } while (t != 27);
    return 0;
}

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int setColor(char color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    return SetConsoleTextAttribute(h, color);
}

void escreveTexto(int x, int y, char texto[], int cor)
{
    setColor(cor);
    gotoxy(y, x);
    printf("%s", texto);
}

void desenhaNenhumCadastrado()
{
    system("cls");
    escreveTexto(5,10,"Nenhum projeto cadastrado!", 15);
}

void iniciaArray(double projetos[30][5])
{
    int i;
    for (i = 0; i < 30; i++)
    {
        projetos[i][0] = -1;
        projetos[i][1] = 0;
        projetos[i][2] = 0;
        projetos[i][3] = 0;
        projetos[i][4] = 0;
    }
}

void desenhaMenu(int op)
{
    char vet[10][60] = {
        "1. Cadastrar novo projeto",
        "2. Cadastrar notas",
        "3. Ver projetos",
        "4. Ver media geral dos projetos",
        "5. Ver maior e menor nota final",
        "6. Ver numero de projetos acima da media",
        "7. Exibir medias em ordem crescente",
        "8. Ver projetos com pelo menos uma nota < 7",
        "9. Mostrar projetos classificados",
        "10. Sair"};

    system("cls");
    for (int i = 0; i < 10; i++)
    {
        if (i == op - 1)
            escreveTexto(3 + i, 10, vet[i], 11);
        else
            escreveTexto(3 + i, 10, vet[i], 15);
    }
}

// 1. Cadastrar o código e o percentual de cumprimento das etapas dos projetos
void cadastrarProjeto(double projetos[30][5])
{
    int i;
    int posLivre = -1;

    for (i = 0; i < 30; i++)
    {
        if (projetos[i][0] == -1)
        {
            posLivre = i;
            break;
        }
    }

    if (posLivre == -1)
    {
        printf("Capacidade maxima de projetos atingida (30/30)!\n");
        return;
    }

    double cod;
    int jaCadastrado;

    do
    {
        jaCadastrado = 0;
        
        printf("Digite o codigo do projeto: ");
        scanf("%lf", &cod);

        for (i = 0; i < 30; i++)
        {
            if(cod < 0)
            {
               printf("Codigo invalido!\n");
               break;
            }
            
            if (projetos[i][0] != -1 && projetos[i][0] == cod)
            {
                jaCadastrado = 1;
                printf("Projeto ja existente! Digite outro.\n");
                break;
            }
        }
    } while (jaCadastrado || cod < 0);

    projetos[posLivre][0] = cod;

    do
    {
        printf("Digite o percentual de cumprimento das etapas (0 a 100): ");
        scanf("%lf", &projetos[posLivre][1]);
        if (projetos[posLivre][1] < 0 || projetos[posLivre][1] > 100)
        {
            printf("Percentual invalido! Informe um valor entre 0 e 100.\n");
        }
    } while (projetos[posLivre][1] < 0 || projetos[posLivre][1] > 100);

    printf("\nProjeto %.0lf cadastrado com sucesso!\n", cod);
}

//  2. Cadastrar as notas dos projetos, indicando se a nota corresponde à primeira ou à segunda avaliação
void cadastrarNotas(double projetos[30][5])
{
    double cod, notaTemp;
    int achou = 0, opcaoNota, count = 0;

    if(projetos[0][0] == -1){
        desenhaNenhumCadastrado();
        return;
    }

    do
    {
        printf("Digite o codigo do projeto: ");
        scanf("%lf", &cod);

        for (int i = 0; i < 30; i++)
        {
            if(cod < 0)
            {
                printf("Codigo invalido!\n");
                break;
            }

            if (projetos[i][0] == cod)
            {
                achou = 1;
                
                do
                {
                    printf("\nQual avaliacao deseja cadastrar?\n");
                    printf("1 - Primeira avaliacao (Nota 1)\n");
                    printf("2 - Segunda avaliacao (Nota 2)\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaoNota);

                    if (opcaoNota == 1 || opcaoNota == 2)
                    {
                        // Validação de nota entre 0 e 10
                        do
                        {
                            printf("Digite a nota (0.0 a 10.0): ");
                            scanf("%lf", &notaTemp);
                            if (notaTemp < 0.0 || notaTemp > 10.0)
                            {
                                printf("Nota invalida! Deve estar entre 0.0 e 10.0.\n");
                            }
                        } while (notaTemp < 0.0 || notaTemp > 10.0);

                        if (opcaoNota == 1)
                        {
                            projetos[i][2] = notaTemp;
                            printf("Nota 1 cadastrada!\n");
                        }
                        else
                        {
                            projetos[i][3] = notaTemp;
                            printf("Nota 2 cadastrada!\n");
                        }

                        // Recalcula média se ambas as notas estiverem lançadas
                        projetos[i][4] = (projetos[i][2] + projetos[i][3]) / 2.0;
                        printf("Media final: %.2lf\n", projetos[i][4]);
                    }
                    else
                    {
                        printf("Opcao de avaliacao invalida!\n");
                    }
                }
                while(opcaoNota != 1 && opcaoNota != 2);
            }
        }

        if (!achou && cod >= 0)
        {
            printf("Projeto com o codigo %.0lf nao foi encontrado!\n", cod);
        }
    }
    while(!achou || cod < 0);
}

// 3. Exibir todos os projetos, com código, notas e percentual de cumprimento
void verProjetos(double projetos[30][5])
{
    if(projetos[0][0] == -1){
        desenhaNenhumCadastrado();
        return;
    }

    printf("--------LISTA DE PROJETOS--------\n\n");
    for (int i = 0; i < 30; i++)
    {
        if (projetos[i][0] != -1)
        {
            printf("Projeto [%.0lf]\n", projetos[i][0]);
            printf("  Codigo: %.0lf\n", projetos[i][0]);
            printf("  Cumprimento: %.2lf%%\n", projetos[i][1]);
            printf("  Nota 1: %.2lf\n", projetos[i][2]);
            printf("  Nota 2: %.2lf\n", projetos[i][3]);
            printf("  Media Final: %.2lf\n", projetos[i][4]);
            printf("\n");
        }
    }
}

// 4. Calcular e exibir a média geral dos projetos
double mediaGeral(double projetos[30][5])
{
    if(projetos[0][0] == -1){
        desenhaNenhumCadastrado();
        return 0.0;
    }

    double soma = 0.0;
    int count = 0;

    for (int i = 0; i < 30; i++)
    {
        if (projetos[i][0] != -1)
        {
            soma += projetos[i][4];
            count++;
        }
    }

    if (count == 0)
    {
        printf("Nao ha projetos cadastrados para calcular a media geral.\n");
        return 0.0;
    }

    double media_geral = soma / count;
    printf("Media geral dos %d projetos cadastrados: %.2lf\n", count, media_geral);
    return media_geral;
}

// 5. Exibir a maior e a menor nota final
void maiorEmenorMedia(double projetos[30][5])
{
    if(projetos[0][0] == -1){
        desenhaNenhumCadastrado();
        return;
    }

    double maior = 0, menor = 0, codMaior = 0, codMenor = 0;
    int i = 0, encontrou = 0;

    for (; i < 30; i++)
    {
        if (projetos[i][0] != -1)
        {
            if(i == 0)
            {
                maior = projetos[i][4];
                menor = projetos[i][4];
                codMaior = projetos[i][0];
                codMenor = projetos[i][0];
            }
            else
            {
                if (projetos[i][4] > maior)
                {
                    maior = projetos[i][4];
                    codMaior = projetos[i][0];
                }
                    
                if (projetos[i][4] < menor)
                {
                    menor = projetos[i][4];
                    codMenor = projetos[i][0];
                }
            }
            encontrou = 1;
        }
    }

    if (encontrou)
    {
        printf("Maior nota final (media): %.2lf | Codigo: %.0lf\n", maior, codMaior);
        printf("Menor nota final (media): %.2lf | Codigo: %.0lf\n", menor, codMenor);
    }
    else
    {
        printf("Nenhum projeto cadastrado.\n");
    }
}

// 6. Contar quantos projetos ficaram acima da média geral
void contarProjetosAcimaMedia(double projetos[30][5])
{
    if(projetos[0][0] == -1){
        desenhaNenhumCadastrado();
        return;
    }

    double soma = 0.0;
    int totalProjetos = 0;

    for (int i = 0; i < 30; i++)
    {
        if (projetos[i][0] != -1)
        {
            soma += projetos[i][4];
            totalProjetos++;
        }
    }

    if (totalProjetos == 0)
    {
        printf("Nenhum projeto cadastrado.\n");
        return;
    }

    double mGeral = soma / totalProjetos;
    int count = 0;

    for (int i = 0; i < 30; i++)
    {
        if (projetos[i][0] != -1 && projetos[i][4] > mGeral)
        {
            count++;
        }
    }

    printf("Media Geral Atual: %.2lf\n", mGeral);
    printf("Numero de projetos com media FINAL acima da media geral: %d\n", count);
}

// 7. Exibir as notas finais em ordem crescente, acompanhadas dos respectivos códigos
void exibirNotasCrescente(double projetos[30][5])
{
    if(projetos[0][0] == -1){
        desenhaNenhumCadastrado();
        return;
    }

    double temp[30][5];
    int count = 0;

    for (int i = 0; i < 30; i++)
    {
        if (projetos[i][0] != -1)
        {
            temp[count][0] = projetos[i][0];
            temp[count][1] = projetos[i][1];
            temp[count][2] = projetos[i][2];
            temp[count][3] = projetos[i][3];
            temp[count][4] = projetos[i][4];
            count++;
        }
    }

    for(int i = 0;i < count-1;i++)
    {
        for(int j = i+1;j < count;j++)
        {
            if(temp[i][4] > temp[j][4]){
                double aux[5];
                aux[0] = temp[i][0];
                aux[1] = temp[i][1];
                aux[2] = temp[i][2];
                aux[3] = temp[i][3];
                aux[4] = temp[i][4];
                
                temp[i][0] = temp[j][0];
                temp[i][1] = temp[j][1];
                temp[i][2] = temp[j][2];
                temp[i][3] = temp[j][3];
                temp[i][4] = temp[j][4];
                
                temp[j][0] = aux[0];
                temp[j][1] = aux[1];
                temp[j][2] = aux[2];
                temp[j][3] = aux[3];
                temp[j][4] = aux[4];
            }
        }
    }
    printf("-------MEDIAS FINAIS EM ORDEM CRESCENTE--------\n\n");
    for (int i = 0; i < count; i++)
    {
        printf("Codigo: %.0lf | Media Final: %.2lf\n", temp[i][0], temp[i][4]);
    }
}

// 8. Mostrar os códigos dos projetos que receberam nota menor que 7,0 em pelo menos uma avaliação
void menorQueSeteEmUma(double projetos[30][5])
{
    if(projetos[0][0] == -1){
        desenhaNenhumCadastrado();
        return;
    }

    printf("--------PROJETOS COM PELO MENOS UMA NOTA < 7.0--------\n\n");
    int encontrou = 0;
    for (int i = 0; i < 30; i++)
    {
        if (projetos[i][0] != -1 && (projetos[i][2] < 7.0 || projetos[i][3] < 7.0))
        {
            printf("Codigo: %.0lf (Nota1: %.2lf, Nota2: %.2lf)\n", projetos[i][0], projetos[i][2], projetos[i][3]);
            encontrou = 1;
        }
    }
    if (!encontrou)
        printf("Nenhum projeto encontrado nesta condicao.\n");
}

// 9. Mostrar os projetos classificados para a exposição final, exibindo código, nota final e percentual de cumprimento
void mostraClassificados(double projetos[30][5])
{
    if(projetos[0][0] == -1){
        desenhaNenhumCadastrado();
        return;
    }

    printf("-------PROJETOS CLASSIFICADOS--------\n\n");
    int encontrou = 0, classificado = 0;
    for (int i = 0; i < 30; i++)
    {
        if (projetos[i][0] != -1)
        {
            if(projetos[i][4] >= 7.0 && projetos[i][1] > 70.0)
            {
                printf("Codigo: %.0lf | Media: %.2lf | Cumprimento: %.2lf%%\n", projetos[i][0], projetos[i][4], projetos[i][1]);
                classificado = 1;
            }
            encontrou = 1;
        }
    }

    if(!classificado)
        printf("Nenhum projeto classificado!\n");
    if (!encontrou)
        printf("Nenhum projeto cadastrado.\n");
}

// 10. Sair
void sair()
{
    system("cls");
    escreveTexto(0,0,"Obrigado por usar nossas solucoes!\n\tSee u soon!",15);
}