#include <bits/stdc++.h>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

double calcula_tempo(const struct rusage *b, const struct rusage *a);
void sortArray(int start, int end, int masterArray[], int tempArray[]);
void mergeArray(int start, int split, int end, int masterArray[], int tempArray[]);
void bruteCount(int masterArray[]);

long long INVERSIONS_SORT = 0;
long long INVERSIONS_BRUTE = 0;
int size;


int main() {

  std::cout << "Informe o tamanho do vetor:" << '\n';
  cin >> size;

  int masterArray[size];
  int tempArray[size];
  struct rusage tempo_inicial, tempo_final;

  if (size < 1000000) {
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < size; i++) {
      masterArray[i] = rand()%1000;
    }
  }

  if (size <= 20) {
    cout << "Vetor = ";
    for (size_t i = 0; i < size; i++) {
      cout << masterArray[i] << " ";
    }
  }

  getrusage(RUSAGE_SELF, &tempo_inicial);
    bruteCount(masterArray);
  getrusage(RUSAGE_SELF, &tempo_final);
  double tempo = calcula_tempo(&tempo_inicial, &tempo_final);

  getrusage(RUSAGE_SELF, &tempo_inicial);
    sortArray(0, size - 1, masterArray, tempArray);
  getrusage(RUSAGE_SELF, &tempo_final);
  double tempo2 = calcula_tempo(&tempo_inicial, &tempo_final);
  cout << endl;


  if (size <= 20){
    cout << "Vetor ordenado: ";
    for (size_t i = 0; i < size; i++) {
      cout << masterArray[i] << " ";
    }
  }
  cout << endl;
  cout << "\nNúmero de inversões por força bruta: " << INVERSIONS_BRUTE << endl;
  cout << "Tempo por força bruta: " << tempo << endl;
  cout << endl;
  cout << "\nNúmero de inversões pelo merge sort: " << INVERSIONS_SORT << endl;
  cout << "Tempo pelo merge sort: " << tempo2 << endl;

}

//Função recursiva para separar o vetor em subvetores
void sortArray(int start, int end, int masterArray[], int tempArray[]) {
  int split = (start + end) / 2;

  if (start < end) {
    sortArray(start, split, masterArray, tempArray);
    sortArray(split + 1, end, masterArray, tempArray);
    mergeArray(start, split, end, masterArray, tempArray);
  }


}

//Função para dar o merge nos dois vetores na ordem correta, contando o número de inversões
void mergeArray(int start, int split, int end, int masterArray[], int tempArray[]) {
  int leftCount = start; //Contador para o vetor esquerdo
  int rightCount = split+1; //Contador para o vertor direito
  int tempCount = start; //Contador para o vetor temporário

  while ((leftCount <= split) && (rightCount <= end)) { //Quando ainda existem valores nos dois vetores
    if (masterArray[leftCount] <= masterArray[rightCount]) { //Se o valor da esquerda for menor
      tempArray[tempCount] = masterArray[leftCount];
      leftCount++;
    }
    else {
      tempArray[tempCount] = masterArray[rightCount];  //ISe o valor da direita foi menor
      INVERSIONS_SORT = INVERSIONS_SORT + (split + 1 - leftCount);
      rightCount++;
    }
    tempCount++;
  }

  //Limpa quando terminou de varrer um dos vetores
  if (leftCount > split) {
    for (int i = rightCount; i <= end; i++) {
      tempArray[tempCount] = masterArray[i];
      tempCount++;
    }
  }
  else {
    for (int i = leftCount; i <= split; i++) {
      tempArray[tempCount] = masterArray[i];
      tempCount++;
    }
  }

  //Copia o vetor temporario para o vetor principal
  for (int i = start; i <= end; i++)
    masterArray[i] = tempArray[i];

}


//Conta o número de inversões por força bruta
void bruteCount(int masterArray[]) {

  for (int i = 0; i < size-1; i++)
    for (int j = i + 1; j < size; j++)
      if (masterArray[i] > masterArray[j])
        INVERSIONS_BRUTE++;
}

//Função para calcular o tempo gasto
double calcula_tempo(const struct rusage *b, const struct rusage *a) {
    if (b == NULL || a == NULL)
        return 0;
    else
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                 (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                 (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
}
