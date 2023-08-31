/* 
  Coe cria, uma dica! 
  
  - Presta aten��o no enunciado do exerc�cio. N�o sei se o professor exigiu que havia necessidade de utilizar template,
  mas no enunciado dessa quest�o falava que apenas iria receber um vetor do tipo inteiro. Para voc� aprender � muito bom
  fazer coisas a mais, mas caso isso aconte�a em uma apresenta��o de trabalho voc� pode perder ponto por causa disso.

  - Tenta prestar mais aten��o na nomea��o das suas vari�veis. Quesitos de legebilidade do c�digo s�o muito requisitados, tanto na facul
  quanto em entrevistas. O padr�o para vari�ves � o camelcase.

  - Tente correlacionar fun��es, ao inv�s de ter que chamar uma fun��o por vez dentro do main.

  - Seu c�digo tava com uma l�gica boa, mas faltou saber implementar. Caso precise de mais ajuda da um toque tmj.
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

  for (int i = 0; i < TAM; i++){ //Atribui��o de minimo e m�ximo.
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
    cout << "O maior n�mero encontrado no vetor foi: " << max << " e esta localizado no index: " << maxIndex << endl;
    cout << "O menor n�mero encontrado no vetor foi: " << min << " e esta localizado no index: " << minIndex << endl;

    cout << endl << "No vetor h� pelo menos um n�mero repetido!" << endl;
    cout << "N�mero Repetido: " << repeatedNumber << ", Index: " << repeatedNumberPosition << endl << endl;

    BubbleSort(array);

    return;
  }

  cout << "O maior n�mero encontrado no vetor foi: " << max << " e esta localizado no index: " << maxIndex << endl;
  cout << "O menor n�mero encontrado no vetor foi: " << min << " e esta localizado no index: " << minIndex << endl << endl;

  cout << endl << "No vetor n�o h� um n�mero repetido!" << endl;

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