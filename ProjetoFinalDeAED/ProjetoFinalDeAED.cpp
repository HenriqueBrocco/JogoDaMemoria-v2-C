#include <iostream>
#include <fstream>
#include <string>
#include <speechapi_cxx.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>//Definição das bibliotecas

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;//Definição dos namespace

auto autenticacao = SpeechConfig::FromSubscription("b342362136af4a70863d908ba46047e2", "brazilsouth"); //Declaração da autenticação do recurso
auto requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //Declaração do objeto de requisição de texto em fala do recurso
auto audio_config = AudioConfig::FromDefaultMicrophoneInput(); //Declaração da entrada do microfone
auto requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); //Declaração do objeto de requesição de fala em texto do recurso

int sair = 0, vitoria = 0, play = -1, aux = -1, Acertos[16]; //Variaveis globais

void texto_em_fala(string Texto) //Função para converter texto em fala
{
    cout << Texto + "\n"; //Escreve o texto
    requisicao_textofala->SpeakTextAsync(Texto).get(); //Requisição da sintetização de texto em fala
}//Função para converter texto em fala
string fala_em_texto() {
    auto resultado = requisicao_falatexto->RecognizeOnceAsync().get(); //Requisição do reconhecimento de fala em texto
    cout << resultado->Text + "\n"; //Escreve o texto
    return resultado->Text; //Conversão do resultado do reconhecimento em texto
}//Função para converter texto em fala

typedef struct
{
    int Posicoes[16]; //Cria um veor com 16 posições para ser o tabuleiro
}Tabuleiro; //Criação do vetor do tabuleiro

void MostrarTabuleiro(int b, Tabuleiro primeiro, int play) //Função para desenhar o tabuleiro e atulizar quando necessário
{
    if (play == 0) //Condição para podermos ver as 2 jogadas feitas por rodada
    {
        aux = b; //Agrega o valor da jogada do usuário em auxiliar para que quando ele realize a segunda ainda tenhamos o numero informado
    }
    for (int i = 0; i < 16; i++) //Função para desenhar o tabuleiro
    {
        if (i == b || i == aux) //Atualiza o desenho de acordo com a jogada do usuário
        {
            cout << '\t' << "|   [" << primeiro.Posicoes[i] << "]   |"; //Desenha o campo que o jogador escolheu com o destaque de colchetes para saber que é o da jogada atual
        }
        else //Garante que onde não tenha a joga atualize o mapa corretamente
        {
            if (Acertos[i] == -1) //Atualiza com os campos ainda não selecionados
                cout << '\t' << "|_________|"; //Desenha o campo vazio
            else //Atualiza os campos que já foram acertados para manter o histórico
                cout << '\t' << "|    " << primeiro.Posicoes[i] << "    |"; //Desenha os campos acertados
        }
        if ((i + 1) % 4 == 0) //Faz a separação do tabuleiro para ficar 4x4
        {
            cout << '\n'; //Salta a linha
        }
    }
    if (primeiro.Posicoes[b] - primeiro.Posicoes[aux] == 8 || primeiro.Posicoes[b] - primeiro.Posicoes[aux] == -8) //Verifica se o par selecionado é correto
    {
        Acertos[b] = primeiro.Posicoes[b]; //Agrega o valor acertado e aposição ao vetor acertado, alterando o valor de -1
        Acertos[aux] = primeiro.Posicoes[aux]; //Agrega o valor acertado e aposição ao vetor acertado, alterando o valor de -1
    }
}

int Jogadas(string a) //Função para realizar as jogadas
{
    int posicao = -1; //Declara a variavel posição para auxiliar na hora de mostrar o tabuleiro, iniciada com -1 para evitar conflitos
    string jogada = a; //Iguala a variavel "a" para a "jogada"
    if (jogada == ("1.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 1 da matriz
    {
        posicao = 0; //Atribui o valor a variável posição
    }
    else if (jogada == ("2.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 2 da matriz
    {
        posicao = 1; //Atribui o valor a variável posição
    }
    else if (jogada == ("3.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 3 da matriz
    {
        posicao = 2; //Atribui o valor a variável posição
    }
    else if (jogada == ("4.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 4 da matriz
    {
        posicao = 3; //Atribui o valor a variável posição
    }
    else if (jogada == ("5.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 5 da matriz
    {
        posicao = 4; //Atribui o valor a variável posição
    }
    else if (jogada == ("6.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 6 da matriz
    {
        posicao = 5; //Atribui o valor a variável posição
    }
    else if (jogada == ("7.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 7 da matriz
    {
        posicao = 6; //Atribui o valor a variável posição
    }
    else if (jogada == ("8.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 8 da matriz
    {
        posicao = 7; //Atribui o valor a variável posição
    }
    else if (jogada == ("9.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 9 da matriz
    {
        posicao = 8; //Atribui o valor a variável posição
    }
    else if (jogada == ("10.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 10 da matriz
    {
        posicao = 9; //Atribui o valor a variável posição
    }
    else if (jogada == ("11.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 11 da matriz
    {
        posicao = 10; //Atribui o valor a variável posição
    }
    else if (jogada == ("12.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 12 da matriz
    {
        posicao = 11; //Atribui o valor a variável posição
    }
    else if (jogada == ("13.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 13 da matriz
    {
        posicao = 12; //Atribui o valor a variável posição
    }
    else if (jogada == ("14.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 14 da matriz
    {
        posicao = 13; //Atribui o valor a variável posição
    }
    else if (jogada == ("15.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 15 da matriz
    {
        posicao = 14; //Atribui o valor a variável posição
    }
    else if (jogada == ("16.")) //Caso o jogador tenha falado este número irá atualizar o valor da variavel posição para poder revelar a posição 16 da matriz
    {
        posicao = 15; //Atribui o valor a variável posição
    }
    else if (jogada == ("Sair.")) //Caso o jogar queira parar de jogar, basta falar sair e ele poderá sair
    {
        sair = 1; //Atribui o valor 1 a variável sair para o jogador poder sair do jogo
    }
    else
        texto_em_fala("Nao entendi, poderia repetir"); //Fala que não entendeu a frase dita

    return posicao; //Retorna o valor da variação posição para ela poder ser demonstrada no tabuleiro
}

void ConfereVitoria()
{
    int vic = 0; //Variavel auxiliar que verifica quantos -1 o vetor Acertos  ainda tem
    for (int i = 0; i < 16; i++) //Função para permitir a verificação de todo o vetor que estiver diferente de -1 com isso permite a contagem de acertos
    {
        if (Acertos[i] != -1) //Verifica se aquela posição já foi verificada
            vic = vic + 1; //Faz a soma para ver se todos os campos já foram acertados
    }
    if (vic == 16) //Verifica se todos os campos já foram preenchidos
        vitoria = 1; //Atualiza o valor da vitoria, para sair do while 
    else //Em caso de não ter ganhado ainda mostra quantos pares faltam
    {
        cout << "\nVoce fez " << vic << " acertos\n"; //Diz quantos acertos faltam
    }
}

int main()
{
    autenticacao = SpeechConfig::FromSubscription("b342362136af4a70863d908ba46047e2", "brazilsouth"); //Autenticação do recurso com a cheve e região informados pelo usuário 
    autenticacao->SetSpeechRecognitionLanguage("pt-BR"); //Configuração da autenticação para o reconhecimento de fala em português 
    autenticacao->SetSpeechSynthesisLanguage("pt-BR"); //Configuração da autenticação para a sintetização de fala em português 
    autenticacao->SetSpeechSynthesisVoiceName("pt-BR-HeloisaRUS"); //PT-BR-Heloisa  //Configuração da autenticação com uma voz específica 
    requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //Redefinição do objeto requisição_texto fala com as novas configurações 
    requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); //Redefinição do objeto requisição_fala texti com as novas configurações

    for (int i = 0; i < 16; i++) //Coloca todos os valores do vetor Acertos com -1
        Acertos[i] = -1; //Atribui o valor com -1

    texto_em_fala("\n\t\t\tDiferenca de 8\n\n \tBem-vindo ao Diferenca de 8 por voz, as regras sao as seguintes:\n \tO jogo possui 16 casas, voce deve encontrar os numeros que tem uma diferenca modular de 8 entre si.\nPor rodada tem-se uma chance de acertar, caso acerte, as casas ficarao aparecendo ate o final da sua partida.\nOs pares sao: 0-8 1-9 2-10 3-11 4-12 5-13 6-14 7-15\n Caso queira sair, basta dizer Sair duas vezes.\nSeu objetivo e acertar todos\n\tBoa sorte e bom jogo!!!\n\n"); //Explica as regras

    Tabuleiro primeiro; //Cria a variavel primeiro do tipo tabuleiro
    srand(time(NULL)); //Configura a função rand com o time para gerar números "aleatórios"

    for (int i = 0; i < 16; i++) //Função para poder randomizar os números de forma aleatória nas posições dos vetores e formar o que fica por "trás" do tabuleiro
    {
        primeiro.Posicoes[i] = rand() % 16; //Atribui os números dentro do vetor (aleatoriamente)
        for (int j = 0; j < i; j++) //Condição para verificar se existem números iguais alocados em diferentes posições
        {
            if (primeiro.Posicoes[j] == primeiro.Posicoes[i]) //Função para impedir que em duas posições diferentes tenha o mesmo valor
            {
                i--; //Caso o valor seja igual ele volta o valor do i para poder tentar acertar um novamente
            }
        }
    }
    MostrarTabuleiro(-1, primeiro, play); //Puxa a função de Mostrar o tabuleiro, para mostrar ele todo zerado, envia os valores de -1 que seria o da primeira jogada, o vetor com o resultado e o valor de play, para poder ser contabilizada as jogadas por rodada
    while (vitoria == 0 && sair == 0) //Cria um looping de jogo até a pessoa querer sair ou ganhar o jogo
    {
        for (int play = 0; play < 2; play++) //Criação do loop para controlar as jogadas por rodada
        {
            texto_em_fala("Qual lugar deseja virar?"); //Faz a mensagem entre aspas ser falada (Para jogar por voz)
            //cout << "\nQual lugar deseja virar?\n"; //Variação da mensagem para caso queira jogar na mão (Para jogar manualmente)
            //string jogada; //Cria a variavel jogada sendo uma string (Para jogar manualmente)
            //cin >> jogada; //Pega o valor digitado pelo usuario para poder ser o valor a ser revelado no tabuleiro (Para jogar manualmente)
            string jogada = fala_em_texto(); //Capta a mensagem falada, a transformando em texto e atribuindo ao valor da string jogada (Para jogar por voz)
            int posicao = Jogadas(jogada); //Atribui o valor posição com o retorno da função jogadas (tras a variavél posição para poder ser revelada no tabuleiro)
            MostrarTabuleiro(posicao, primeiro, play); //Atualiza o tabuleiro com a posição escolhida sendo revelada
        }
        ConfereVitoria(); //Chama a função checar vitoria apos cada rodada jogada
    }
    if (sair == 1) //Caso o usuario tenha escolhido sair, irá ter alterado a variavel sair, fazendo com que saia do loop do while e caia nessa condição encerrando o jogo
        cout << "\n \tVoce saiu! Obrigado por jogar!";
    else //Caso não tenha saido do loop com o sair, o usuário terá ganhado o jogo
        cout << "\n \tParabens, voce ganhou!!!"; //Mensagem parabenizando a vitoria
    return 0; //Define o retorno 0
}