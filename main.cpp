#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;


bool citesteMatriceDinFisier(const string& numeFisier,int**& matrice, int& dimensiune){
    
     ifstream input(numeFisier);

     if(!input.is_open()){
        cerr<<"Nu s-a putut deschide fisierul pentru citire";
        return false;
     }
    input>>dimensiune;

    
    matrice=new int*[dimensiune];
    for(int i=0;i<dimensiune;++i){
           matrice[i]=new int[dimensiune];
        }
    
    for(int i=0;i<dimensiune;++i){
        for(int j=0;j<dimensiune;j++){
            input>>matrice[i][j];
        }
    }

    input.close();
    return true;
     
}

void scrieSirInFisier(const string& numeFisier, const string& sir) {
    ofstream file(numeFisier);
    if (!file.is_open()) {
        cerr << "Nu s-a putut deschide fisierul pentru scriere" << endl;
        return;
    }
    file << sir;
    file.close();
}


void parcurgeSpirala(int**& matrice, int*& vector,int n){

   int startRow=0;
   int startCol=0;
   int endRow=n-1;
   int endCol=n-1;
   int index=0;

  while(startRow<=endRow && startCol<=endCol){

        while (startRow <= endRow && startCol <= endCol) {
        for (int col = startCol; col <= endCol; col++) {
            vector[index++] = matrice[startRow][col];
        }
        startRow++;

        for (int row = startRow; row <= endRow; row++) {
            vector[index++] = matrice[row][endCol];
        }
        endCol--;

        if (startRow <= endRow) {
            for (int col = endCol; col >= startCol; col--) {
                vector[index++] = matrice[endRow][col];
            }
            endRow--;
        }

        if (startCol <= endCol) {
            for (int row = endRow; row >= startRow; row--) {
                vector[index++] = matrice[row][startCol];
            }
            startCol++;
        }
    }
  }
}



    void Rot13(char *s){
        int n=strlen(s);
        for(int i=0;i<n;i++){
            if(s[i]>='a' && s[i]<='z'){
                
                s[i] = 'a' + (s[i] - 'a'+ 13) % 26;
            }
            if(s[i]>='A' && s[i]<='Z'){
                s[i] = 'A' +(s[i] - 'A' + 13) % 26;
            }

        }
    }
    
    void stergeElemente(char* s){
    int n=strlen(s);
    int j=0;
    for(int i=0;i<=n;i++){
        if(s[i]!='_'){
            
            s[j++]=s[i];
        
      }
    }
    s[j]='\0';
}
    
    void oglindire(char *s){
        int n=strlen(s);
        for(int i=0;i<n/2;i++){
        char temp=s[i];
        s[i]=s[n-1-i];
        s[n-1-i]=temp;
    }
 }

 void Atbash(char *s){
     int n = strlen(s);
    for (int i = 0; i < n; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = 'z' - (s[i] - 'a');
        }else if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = 'Z' - (s[i] - 'A');
        }else if(s[i]>='1' && s[i]<='9'){
             s[i]='9' - (s[i]-'0');
        }
    }
}

void Caesar(char *s, int shift){
     if (s == nullptr) return;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = ((s[i] - 'A' - shift + 26) % 26) + 'A'; 
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = ((s[i] - 'a' - shift + 26) % 26) + 'a'; 
        }
    }
}

void separator(char *s){
    const char* separator="|=|";
    char* tokens[100]; 
    int tokenCount = 0;

     char* token = strtok(s, separator);
    while (token != nullptr) {
        std::cout << token << std::endl;
        token = strtok(nullptr, separator);
    }
    for (int i = 0; i < tokenCount - 1; i++) {
        for (int j = 0; j < tokenCount - i - 1; j++) {
            if (tokens[j][0] > tokens[j + 1][0]) {
                std::swap(tokens[j], tokens[j + 1]);
            }
        }
    }
    for (int i = 0; i < tokenCount; i++) {
        std::cout << tokens[i] << std::endl;
    }
}

int main(){
    
    int dimensiune;
    int **matrice;
   

    if(citesteMatriceDinFisier("1.txt",matrice,dimensiune)){
    
      int *vectorSpirala=new int[dimensiune*dimensiune];

      parcurgeSpirala(matrice,vectorSpirala,dimensiune);
    
      char *caractere=new char[dimensiune*dimensiune];
        //convertim ASCII in caractere si le punem in vectorul caractere[]
        for (int i = 0; i < dimensiune*dimensiune; ++i) {
                 //populam vectorul caractere vectorul tradus in text
                 caractere[i]=static_cast<char>(vectorSpirala[i]);
        }

      Rot13(caractere);
      oglindire(caractere);
      Atbash(caractere);
      Caesar(caractere,11);
      stergeElemente(caractere);
      separator(caractere);

      scrieSirInFisier("./result.txt",caractere);


      for (int i = 0; i < dimensiune; i++) {
            delete[] matrice[i];
        }
        delete[] matrice;
    
    }

    return 0;

}
  