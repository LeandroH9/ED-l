#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menu.c"
#include "controller.c"


int main(){
    FILE *orientado, *naoOrientado, *log;
    int optionType, optionModel, option, op, exit = 0, close = 0;

    orientado = fopen("txt/digrafo.txt", "r+");
    naoOrientado = fopen("txt/nao_orientado.txt", "r+");
    log = fopen("txt/log_de_processamento.txt", "w+");

    if(orientado != NULL && naoOrientado != NULL){
        do {
            close = exit = 0;
            optionType = firstMenu(log);
            optionModel = secondMenu(log);

            if(optionModel == 3) continue;

            optionType == 1 ? createGraph(log, orientado, optionModel) : createGraph(log, naoOrientado, optionModel);

            fflush(log);
            do{
                option = mainMenu(log);
                switch(option){
                    case 1: system("cls");
                            optionModel == 1 ? viewGraphMatrix(log): viewGraphList(log);
                            break;

                    case 2: op = menuGraphSearch(log);
                            system("cls");
                            switch(op){
                                case 1: optionModel == 1 ? DFSMatrix(log): DFSList(log);
                                        break;
                                case 2: optionModel == 1 ? BFSMatrix(log): BFSList(log);
                                        break;
                            }
                            break;

                    case 3: op = menuUpdateGraph(log);
                            system("cls");
                            switch(op){
                                case 1: optionModel == 1 ? insertVertexMatrix(log): insertVertexList(log);
                                        break;
                                case 2: optionModel == 1 ? insertArqOrEdgesMatrix(log, optionType): insertArqOrEdgesList(log);
                                        break;
                                case 3: // EM MANUTENCAO -> optionModel == 1 ? removeVertexMatrix(log): removeVertexList(log);
                                        break;
                                case 4: optionModel == 1 ? removeArqOrEdgesMatrix(log, optionType): removeArqOrEdgesList(log, optionType);
                                        break;
                            }
                            break;
                    case 4: op = menuVerificationOfProperties(log);
                            system("cls");
                            switch(op){
                                case 1: optionModel == 1 ? grauVertexMatrix(log, optionType): grauVertexList(log, optionType);
                                        break;
                                case 2: optionModel == 1 ? orderAndSizeMatrix(log): orderAndSizeList(log);
                                        break;
                                case 3: optionModel == 1 ? listVertexAndEdgesOrArcMatrix(log, optionType) : listVertexAndEdgesOrArcList(log, optionType);
                                        break;
                                case 4: optionModel == 1 ? checkLacesMatrix(log) : checkLacesList(log);
                                        break;
                                case 5: optionModel == 1 ? checkMultipleEdgesMatrix(log, optionType) : checkMultipleEdgesList(log, optionType);
                                        break;
                            }
                            break;

                    case 5: //EM MANUTENCAO
                            break;

                    case 6: op = exitProgram(log);
                            system("cls");
                            if(op == 1) {
                                exit = 1;
                                close = 0;
                            }
                            else {
                                exit = 1;
                                close = 1;
                            }
                            break;
                }
                puts("\n");
                fflush(log);
                system("pause");
            } while(!exit);
        } while (!close);
    }

    fclose(orientado);
    fclose(naoOrientado);
    fclose(log);
    return(0);
}

