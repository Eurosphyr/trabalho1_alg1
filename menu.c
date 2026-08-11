#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

void gotoxy(int x, int y);
int setColor(char color);
void escreveTexto(int x, int y, char texto[], int cor);
void desenhaMenu(int op);
void iniciaArray(struct Projeto *projetos);
void cadastrarProjeto(struct Projeto *projetos);
void cadastrarNotas(struct Projeto *projetos);
void verProjetos(struct Projeto *projetos);
double mediaGeral(struct Projeto *projetos, int numProjetos);
void menorQueSeteEmUma(struct Projeto *projetos);
void mostraClassificados(struct Projeto *projetos);
void sair();

struct Projeto
{
    int existe;
    double codigo;
    double percentual;
    double nota1;
    double nota2;
    double media;
};

int main()
{
    struct Projeto projetos[30];
    int op = 1;
    char t;

    setColor(15);

    iniciaArray(projetos);
    desenhaMenu(op);
    do
    {
        t = getch();

        if (t <= 0)
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
            switch (op)
            {
            case 1:
                // Cadastrar o código e o percentual de cumprimento das etapas dos projetos
                cadastrarProjeto(projetos);
                break;
            case 2:
                // Cadastrar as notas dos projetos, indicando se a nota corresponde à primeira ou à segunda avaliação
                cadastrarNotas(projetos);
                break;
            case 3:
                // Exibir todos os projetos, com código, notas e percentual de cumprimento
                verProjetos(projetos);
                break;
            case 4:
                // Calcular e exibir a média geral dos projetos
                mediaGeral(projetos, 30);
                break;
            case 5:
                // Exibir a maior e a menor nota final
                maiorEmenorMedia(projetos);
                break;
            case 6:
                // Contar quantos projetos ficaram acima da média geral
                break;
            case 7:
                // Exibir as notas finais em ordem crescente, acompanhadas dos respectivos códigos
                break;
            case 8:
                // Mostrar os códigos dos projetos que receberam nota menor que 7,0 em pelo menos uma avaliação
                break;
            case 9:
                // Mostrar os projetos classificados para a exposição final, exibindo código, nota final e percentual de cumprimento
                break;
            case 10:
                sair();
                break;
            }
    } while (t != 27);
}

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int setColor(char color)
{
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    return SetConsoleTextAttribute(h, color);
}

void escreveTexto(int x, int y, char texto[], int cor)
{
    setColor(cor);
    gotoxy(y, x);
    printf("%s", texto);
}

void iniciaArray(struct Projeto *projetos)
{
    int i;
    for (i = 0; i < 30; i++)
    {
        projetos[i].existe = 0;
    }
}

void desenhaMenu(int op)
{
    char vet[][20] = {"Cadastrar novo projeto", "Cadastrar notas", "Ver projetos", "Ver media geral dos projetos", "Ver maior e menor nota final", "Ver numero de projetos acima da media", "Exibir medias em ordem crescente", "Ver projetos com pelo menos uma nota maior que 7", "Mostrar projetos classificados", "Sair"};
    int i;
    system("cls");
    for (i = 0; i < 11; i++)
        escreveTexto(3 + i, 10, vet[i], 10);
    escreveTexto(2 + op, 10, vet[op - 1], 5);
}

// 1. Cadastrar o código e o percentual de cumprimento das etapas dos projetos
void cadastrarProjeto(struct Projeto *projetos)
{
    for (int i = 0; i < 30; i++)
    {
        double cod;
        int jaCadastrado = 0;
        if (projetos[i].existe == 0)
        {
            projetos[i].existe = 1;

            do
            {
                printf("Digite o codigo do projeto: ");
                scanf("%lf", &cod);
                int j = 0;
                for (; j < 30; j++)
                {
                    if (cod == projetos[j].codigo)
                    {
                        jaCadastrado = 1;
                    }
                    else
                    {
                        jaCadastrado = 0;
                    }
                }
            } while (jaCadastrado == 1);

            printf("Digite o percentual de cumprimento das etapas: ");
            scanf("%lf", &projetos[i].percentual);
            break;
        }
    }
    struct Projeto projeto;
    printf("Digite o codigo do projeto: ");
    scanf("%lf", &projeto.codigo);
    printf("Digite o percentual de cumprimento das etapas: ");
    scanf("%lf", &projeto.percentual);
    projetos[0] = projeto;
}
// 2. Cadastrar as notas dos projetos, indicando se a nota corresponde à primeira ou à segunda avaliação
void cadastrarNotas(struct Projeto *projetos)
{
    int i;
    int cod;
    printf("Digite o codigo do projeto: ");
    scanf("%d", &cod);
    for (i = 0; i < 30; i++)
    {
        if (projetos[i].existe == 1 && projetos[i].codigo == cod)
        {
            printf("Digite a nota 1 do projeto %lf: ", projetos[i].codigo);
            scanf("%lf", &projetos[i].nota1);
            printf("Digite a nota 2 do projeto %lf: ", projetos[i].codigo);
            scanf("%lf", &projetos[i].nota2);
        }
    }
    printf("Notas cadastradas com sucesso!\n");
}

// 3. Exibir todos os projetos, com código, notas e percentual de cumprimento
void verProjetos(struct Projeto *projetos)
{
    int i, count = 0;
    for (i = 0; i < 30; i++)
    {
        if (projetos[i].existe == 1)
        {
            printf("Projeto %d:\n", i + 1);
            printf("Codigo: %lf\n", projetos[i].codigo);
            printf("Percentual de cumprimento: %lf\n", projetos[i].percentual);
            printf("Nota 1: %lf\n", projetos[i].nota1);
            printf("Nota 2: %lf\n", projetos[i].nota2);
            printf("\n");
            count++;
        }
    }

    if (count == 0)
        printf("Sem projetos cadastrados!");
}
// 4. Calcular e exibir a média geral dos projetos

double mediaGeral(struct Projeto *projetos, int numProjetos)
{
    int i;
    double soma = 0.0;
    for (i = 0; i < numProjetos; i++)
    {
        soma += projetos[i].nota1 + projetos[i].nota2;
    }
    double media_geral = soma / (numProjetos * 2);
    printf("Media geral dos projetos: %lf\n", media_geral);
    return media_geral;
}

// 5. Exibir a maior e a menor nota final
void maiorEmenorMedia(struct Projeto *projetos)
{
    int i;
    double maior = 0, menor = 0;
    for (i = 0; i < 29; i++)
    {
        if (projetos[i].existe == 1)
        {
            if (i == 0)
            {
                maior = projetos[i].media;
                menor = projetos[i].media;
            }

            if (projetos[i + 1].existe == 1)
            {
                if (maior < projetos[i + 1].media)
                {
                    maior = projetos[i + 1].media;
                }
                if (menor > projetos[i + 1].media)
                {
                    menor = projetos[i + 1].media;
                }
            }
        }
    }
}

// 6. Contar quantos projetos ficaram acima da média geral
void contarProjetosAcimaMedia(struct Projeto *projetos)
{
    int i, count = 0;
    for (i = 0; i < 30; i++)
    {
        if (projetos[i].existe == 1 && projetos[i].media > mediaGeral(projetos, 30))
        {
            count++;
        }
    }
    printf("Numero de projetos acima da media geral: %d\n", count);
}

// 7. Exibir as notas finais em ordem crescente, acompanhadas dos respectivos códigos (qsort)
int compareNotas(const void *a, const void *b)
{
    struct Projeto *projetoA = (struct Projeto *)a;
    struct Projeto *projetoB = (struct Projeto *)b;

    if (projetoA->media < projetoB->media)
        return -1;
    else if (projetoA->media > projetoB->media)
        return 1;
    else
        return 0;

}

void exibirNotasCrescente(struct Projeto *projetos)
{
    qsort(projetos, 30, sizeof(struct Projeto), compareNotas);
}

// 8. Mostrar os códigos dos projetos que receberam nota menor que 7,0 em pelo menos uma avaliação
void menorQueSeteEmUma(struct Projeto *projetos)
{
    int i = 0;
    double codigos[30];

    for (; i < 30; i++)
    {
        if (projetos[i].existe == 1 && (projetos[i].nota1 < 7 || projetos[i].nota2 < 7))
        {
            escreveTexto(5, 5 + i, (char)projetos[i].codigo, 10);
        }
    }
}

// 9. Mostrar os projetos classificados para a exposição final, exibindo código, nota final e percentual de cumprimento
void mostraClassificados(struct Projeto *projetos)
{
    int i = 0;
    double codigos[30];

    for (; i < 30; i++)
    {
        if (projetos[i].existe == 1)
        {
            escreveTexto(5, 5 + i, (char)projetos[i].codigo, 10);
        }
    }
}

// 10. Sair
void sair()
{
    escreveTexto(5, 5, "Obrigado por usar nossas solucoes\n\tSee u soon!", 10);
}