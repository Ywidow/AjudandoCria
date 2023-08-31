/* 
  Coe cria, uma dica! 
  
  - Presta atenção no enunciado do exercício. Não sei se o professor exigiu que havia necessidade de utilizar template,
  mas no enunciado dessa questão falava que apenas iria receber um vetor do tipo inteiro. Para você aprender é muito bom
  fazer coisas a mais, mas caso isso aconteça em uma apresentação de trabalho você pode perder ponto por causa disso.

  - Tenta prestar mais atenção na nomeação das suas variáveis. Quesitos de legebilidade do código são muito requisitados, tanto na facul
  quanto em entrevistas. O padrão para variáves é o camelcase.

  - Tente correlacionar funções, ao invés de ter que chamar uma função por vez dentro do main.

  - Seu código tava com uma lógica boa, mas faltou saber implementar. Caso precise de mais ajuda da um toque tmj.
*/


#include <iostream>
#include <time.h>
#define TAM 20

using namespace std;

void ShowArray(int array[TAM], string infoText = ""){
  if(infoText != ""){
    cout << infoText << endl;
  }
  
  for (int i = 0; i < TAM; i++){
    if(i == 0){
      cout << "[" << array[i] << "\t";
    }
    else if(i == TAM - 1){
      cout << array[i] << "]";
    }
    else{
      cout << array[i] << "\t";
    }
  }

  cout << endl << endl;
}

void BubbleSort(int array[TAM]){
  for(int i = 0; i < TAM - 1; i++){
    for(int j = 0; j < TAM - i - 1; j++){
      if(array[j] > array[j + 1]){
          int temp = array[j];
          array[j] = array[j + 1];
          array[j + 1] = temp;
      }
    }
  }

  ShowArray(array, "Array Ordenado: ");
}

void VerificaMinMax(int array[TAM]){

  int min, max, repeatedNumber, repeatedNumberPosition;
  int maxIndex, minIndex;
  bool haveRepeatedNumber = false;

  for (int i = 0; i < TAM; i++){ //Atribuição de minimo e máximo.
    if(i == 0){
      min = array[0];
      minIndex = i;

      max = array[0];
      maxIndex = i;
    }

    if(min > array[i]){
      min = array[i];
      minIndex = i;
    }

    if(max < array[i]){
      max = array[i];
      maxIndex = i;
    }
  }

  for(int i = 0; i < TAM; i++){
    for(int j = 0; j < TAM; j++){
      if(array[i] == array[j] && i != j && !haveRepeatedNumber){
        repeatedNumber = array[i];
        repeatedNumberPosition = j;
        haveRepeatedNumber = true;
      }
    }
  }

  if(haveRepeatedNumber){
    cout << "O maior número encontrado no vetor foi: " << max << " e esta localizado no index: " << maxIndex << endl;
    cout << "O menor número encontrado no vetor foi: " << min << " e esta localizado no index: " << minIndex << endl;

    cout << endl << "No vetor há pelo menos um número repetido!" << endl;
    cout << "Número Repetido: " << repeatedNumber << ", Index: " << repeatedNumberPosition << endl << endl;

    BubbleSort(array);

    return;
  }

  cout << "O maior número encontrado no vetor foi: " << max << " e esta localizado no index: " << maxIndex << endl;
  cout << "O menor número encontrado no vetor foi: " << min << " e esta localizado no index: " << minIndex << endl << endl;

  cout << endl << "No vetor não há um número repetido!" << endl;

  BubbleSort(array);

  return;
}

void Preenche(int array[TAM]) {
  srand(time(NULL));

  for (int i = 0; i < TAM; i++) {
    array[i] = rand() % (TAM * 5) + 1;
  }

  ShowArray(array, "Array Original: ");
}

int main(){
  setlocale(LC_ALL, "portuguese");

  system("cls");

  int array[TAM] = {};

  Preenche(array);
  VerificaMinMax(array);

  cout << endl << endl;

  system("pause");
  system("cls");

  return 0;
}