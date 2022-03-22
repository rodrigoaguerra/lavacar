#include "header.h"

void relatorioAnoInsumos(gchar* date_arq){
      FILE* arqA;
      char strName_html[55];
      strcpy(strName_html, "relatorios-ins-ano\\relatorio-");
      strcat(strName_html, date_arq);
      strcat(strName_html, ".html\0");
      arqA = fopen(strName_html, "w");

      //printf("%s", strName_html);
      fprintf(arqA , "<html> \n"),
      fprintf(arqA , " <head> \n"),
      fprintf(arqA , "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
      fprintf(arqA , "  <title>Relatorio De Insumos Do Ano</title> \n"),
      fprintf(arqA , " </head> \n"),
      fprintf(arqA , " <body> \n"),
      fprintf(arqA , "  <table border=\"1\" align=center width=\"1200\"> \n");
      fprintf(arqA , "   <tr>\n");
      fprintf(arqA , "\t \t \t <th>DATA.: %s</th>\n", date_arq);
      fprintf(arqA , "   </tr>\n");
      if (arqA == 0){
         printf("Erro na abertura do arquivo %s .html \n", strName_html);
      }else{
           FILE* arq;
           char snum[5];
           char strName[55];
           int mes;
           double totalgastoM = 0;
           double totalgastoA = 0;
           for(mes = 1; mes < 13; mes++){
              strcpy(strName, "relatorios-ins-mes\\relatorio-mes-");
              if(mes < 10){
                strcat(strName, "0");
              }
              // convert 123 to string [buf]
              itoa(mes, snum, 10);
              strcat(strName, snum);
              strcat(strName, "-");
              strcat(strName, date_arq);
              strcat(strName, ".ogid\0");
              arq = fopen(strName, "rb");
              Insumo ins;
              totalgastoM = 0;
              if (arq == 0){
                 printf("Erro na abertura do arquivo %s.ogid \n", strName);
                 fprintf(arqA , "   <tr>\n");
                 fprintf(arqA , "\t \t \t <th colspan=\"2\">O Mes %d nao foi fechado !</th>\n", mes);
                 fprintf(arqA , "   </tr>\n");
              }else{
                fprintf(arqA , "   <tr>\n");
                fprintf(arqA , "\t \t \t <th>Mes.: %d </th> \n", mes);
                char data[15];
                while(!feof(arq)){
                       if(fread(&data, 15 * sizeof(char), 1, arq) == 1);
                       if(fread(&ins, sizeof(Insumo), 1, arq) == 1){
                              totalgastoM += ins.valor;
                              totalgastoA += ins.valor;
                        }
                 }
                 fprintf(arqA , "\t \t \t <th>Total Gasto Com Insumos no Mes.:  %.2lf</th>\n", totalgastoM);
                 fprintf(arqA , "   </tr>\n");
               }
               fclose(arq);
             }
             fprintf(arqA , "   <tr>\n");
             fprintf(arqA , "\t \t \t <th>Total Gasto Com Insumos.: </th> <td align=\"center\" >%.2lf</td>\n", totalgastoA);
             fprintf(arqA , "   </tr>\n");
           }

      fprintf(arqA , "  </table> \n");
      fprintf(arqA , " </body> \n");
      fprintf(arqA , "</html> \n");
      fclose(arqA);
}

void relatorioMesInsumos(gchar* date_arq){
      FILE* arqA;
      char strName_html[55];
      strcpy(strName_html, "relatorios-ins-mes\\relatorio-");
      strcat(strName_html, date_arq);
      strcat(strName_html, ".html\0");
      arqA = fopen(strName_html, "w");
      double totalgasto = 0;
      //printf("%s", strName_html);
      fprintf(arqA , "<html> \n"),
      fprintf(arqA , " <head> \n"),
      fprintf(arqA , "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
      fprintf(arqA , "  <title>Relatorio De Insumos Do Mes</title> \n"),
      fprintf(arqA , " </head> \n"),
      fprintf(arqA , " <body> \n"),
      fprintf(arqA , "  <table border=\"1\" align=center width=\"1200\"> \n");
      fprintf(arqA , "   <tr>\n");
      fprintf(arqA , "\t \t \t <th>DATA.: </th> <td align=\"center\" >%s</td>\n", date_arq);
      fprintf(arqA , "   </tr>\n");
      if (arqA == 0){
         printf("Erro na abertura do arquivo %s .html \n", strName_html);
      }else{
           FILE* arq;
           char strName[45];
           strcpy(strName, "relatorios-ins-mes\\relatorio-mes-");
           strcat(strName, date_arq);
           strcat(strName, ".ogid\0");
           arq = fopen(strName, "rb");
           Insumo ins;
           if (arq == 0){
            printf("Erro na abertura do arquivo %s.ogid \n", strName);
           }else{
            char data[15];
            while(!feof(arq)){
                   fprintf(arqA , "   <tr>\n");
                   if(fread(&data, 15 * sizeof(char), 1, arq) == 1){
                       fprintf(arqA , "\t \t \t <th>Data.: </th> <td align=\"center\" >%s</td>\n", data);
                   }
                   if(fread(&ins, sizeof(Insumo), 1, arq) == 1){
                          fprintf(arqA , "\t \t \t <th>Nome.: </th> <td align=\"center\" >%s</td>\n", ins.nome);
                          fprintf(arqA , "\t \t \t <th>Valor.: </th> <td align=\"center\" >%.2lf</td>\n", ins.valor);
                          fprintf(arqA , "\t \t \t <th>Quantidade.: </th> <td align=\"center\" >%.2lf</td>\n", ins.quant);
                          fprintf(arqA , "\t \t \t <th>Tipo.: </th> <td align=\"center\" >%s</td>\n", ins.tipo);
                          totalgasto += ins.valor;
                    }
                   fprintf(arqA , "   </tr>\n");
             }
             fclose(arq);
           }
           fprintf(arqA , "   <tr>\n");
           fprintf(arqA , "\t \t \t <th>Total Gasto Com Insumos.: </th> <td align=\"center\" >%.2lf</td>\n", totalgasto);
           fprintf(arqA , "   </tr>\n");
      }
      fprintf(arqA , "  </table> \n");
      fprintf(arqA , " </body> \n");
      fprintf(arqA , "</html> \n");
      fclose(arqA);
}


void relatorioDiaInsumos(gchar* date_arq){
      FILE* arqA;
      char strName_html[55];
      strcpy(strName_html, "relatorios-ins-dia\\relatorio-");
      strcat(strName_html, date_arq);
      strcat(strName_html, ".html\0");
      arqA = fopen(strName_html, "w");
      //printf("%s", strName_html);
      fprintf(arqA , "<html> \n"),
      fprintf(arqA , " <head> \n"),
      fprintf(arqA , "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
      fprintf(arqA , "  <title>Relatorio De Insumos Do Dia</title> \n"),
      fprintf(arqA , " </head> \n"),
      fprintf(arqA , " <body> \n"),
      fprintf(arqA , "  <table border=\"1\" align=center width=\"1200\"> \n");
      fprintf(arqA , "   <tr>\n");
      fprintf(arqA , "\t \t \t <th>DATA.: </th> <td align=\"center\" >%s</td>\n", date_arq);
      fprintf(arqA , "   </tr>\n");
      if (arqA == 0){
         printf("Erro na abertura do arquivo .html \n");
      }else{
         int i;
         for (i=0; i < quant_ins; i++){
           int id_ins = insumosDia[i];
           //printf("\n%d", id_ins);
           ListaInsumo* no = procurar_insumos(insumos, id_ins);
           fprintf(arqA , "   <tr>\n");
           fprintf(arqA , "\t \t \t <th>Nome.: </th> <td align=\"center\" >%s</td>\n", no->info.nome);
           fprintf(arqA , "\t \t \t <th>Valor.: </th> <td align=\"center\" >%.2lf</td>\n", no->info.valor);
           fprintf(arqA , "\t \t \t <th>Quantidade.: </th> <td align=\"center\" >%.2lf</td>\n", no->info.quant);
           fprintf(arqA , "\t \t \t <th>Tipo.: </th> <td align=\"center\" >%s</td>\n", no->info.tipo);
           fprintf(arqA , "   </tr>\n");
         }
           fprintf(arqA , "   <tr>\n");
           fprintf(arqA , "\t \t \t <th>Total Gasto Com Insumos.: </th> <td align=\"center\" >%.2lf</td>\n", gastcominsumos);
           fprintf(arqA , "   </tr>\n");
      }
      fprintf(arqA , "  </table> \n");
      fprintf(arqA , " </body> \n");
      fprintf(arqA , "</html> \n");
      fclose(arqA);
      save_relat_ins(date_arq);
}

void relatorioAnoFuncionario(gchar* date_arq){
      int mes;
      /*double tent, tsai, ttotal;
      tent = 0;
      tsai = 0;
      ttotal = 0;*/
      //mes string
      char snum[5];
      char strName[55];
      FILE *arqA;
      strcpy(strName, "relatorios-func-ano\\relatorio-ano-");
      //get_year(stringTime);
      strcat(strName, date_arq);
      strcat(strName, ".html\0");
      arqA = fopen(strName, "w");
      //printf("%s", strName);
      fprintf(arqA , "<html> \n"),
      fprintf(arqA , " <head> \n"),
      fprintf(arqA , "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
      fprintf(arqA , "  <title>Relat&#243;rio Do Ano De Funcion&#225;rios </title> \n"),
      fprintf(arqA , " </head> \n"),
      fprintf(arqA , " <body> \n"),
      fprintf(arqA , "  <table border=\"1\" align=center width=\"1200\"> \n");
      fprintf(arqA , "   <tr>\n");
      //pega_data(stringTime);
      fprintf(arqA , "\t \t \t <th>DATA.: </th> <td align=\"center\" >%s</td>\n", date_arq);
      fprintf(arqA , "   </tr>\n");
      if (arqA == 0){
         printf("Erro na abertura do arquivo .html \n");
      }else{
        //printf("Arquivo %s aberto \n", strName);
        gint us_idf;
        gchar *namef, *telf, *rgf, *endf, *dataf, *entf, *saif, *pagf;
        Usuario person;
        GtkTreeIter iter;
        int total_H_mes = 0;
        double total_P_mes = 0;
        if(gtk_tree_model_get_iter_first (interface->treemodel_usu, &iter)){
                gtk_tree_model_get (interface->treemodel_usu, &iter,
                                         COLUMN_USER_ID,      &us_idf,
                                         COLUMN_USER_NOME,    &namef,
                                         COLUMN_USER_TELFONE, &telf,
                                         COLUMN_USER_RG,      &rgf,
                                         COLUMN_USER_END,     &endf,
                                         COLUMN_USER_ENT,     &entf,
                                         COLUMN_USER_SAI,     &saif,
                                         COLUMN_USER_PAG,     &pagf,
                                         COLUMN_USER_DATA,    &dataf, -1);
            person.userId = us_idf;
            strcpy(person.nome, namef);
            strcpy(person.telefone, telf);
            strcpy(person.rg, rgf);
            strcpy(person.ende, endf);
            strcpy(person.entrada, entf);
            strcpy(person.saida, saif);
            strcpy(person.pagamento, pagf);
            strcpy(person.data, dataf);
            Usuario p;
            //int jf = 0;
            FILE* arq;
            total_H_mes = 0;
            total_P_mes = 0;
            for(mes = 1; mes < 13; mes++){
              strcpy(strName, "relatorios-func-mes\\relatorio-mes-");
              if(mes < 10){
                strcat(strName, "0");
              }

              // convert 123 to string [buf]
              itoa(mes, snum, 10);
              strcat(strName, snum);
              strcat(strName, "-");
              //get_year(stringTime);
              strcat(strName, date_arq);
              strcat(strName, ".ogid\0");
              arq = fopen(strName, "rb");
              //printf("%s", strName);
              char *ptr;
              if (arq == 0){
                  printf("Erro na abertura do arquivo %s \n", strName);
              }else{
                while(!feof(arq)){
                    if(fread(&p, sizeof(Usuario), 1, arq) == 1){
                       if(strcmp(p.rg, rgf) == 0){
                         int entr = hours_int(p.entrada);
                         int said = hours_int(p.saida);
                         int total_hours = said - entr;
                         total_H_mes += total_hours;
                         total_P_mes += strtod( p.pagamento, &ptr);
                       }
                    }
                  }
               }
               //printf("nome.: %s \n arq.: %s\n", namef, strName);
               fclose(arq);
            }
            fprintf(arqA , "   <tr>\n");
            fprintf(arqA , "\t \t \t <th>Nome.: </th> <td align=\"center\" >%s</td>\n", namef);
            fprintf(arqA , "\t \t \t <th>Rg.: </th> <td align=\"center\" > %s </td>\n", rgf);
            fprintf(arqA , "\t \t \t <th>Total Horas no Ano.: </th> <td align=\"center\" >%d</td>\n", total_H_mes);
            fprintf(arqA , "\t \t \t <th>Total Pago  no Ano.: </th> <td align=\"center\" > %.2lf </td>\n", total_P_mes);
            fprintf(arqA , "   </tr>\n");
            while(gtk_tree_model_iter_next (interface->treemodel_usu, &iter) == TRUE){
                   gtk_tree_model_get (interface->treemodel_usu, &iter,
                                             COLUMN_USER_ID,      &us_idf,
                                             COLUMN_USER_NOME,    &namef,
                                             COLUMN_USER_TELFONE, &telf,
                                             COLUMN_USER_RG,      &rgf,
                                             COLUMN_USER_END,     &endf,
                                             COLUMN_USER_ENT,     &entf,
                                             COLUMN_USER_SAI,     &saif,
                                             COLUMN_USER_PAG,     &pagf,
                                             COLUMN_USER_DATA,    &dataf, -1);
                person.userId = us_idf;
                strcpy(person.nome, namef);
                strcpy(person.telefone, telf);
                strcpy(person.rg, rgf);
                strcpy(person.ende, endf);
                strcpy(person.entrada, entf);
                strcpy(person.saida, saif);
                strcpy(person.pagamento, pagf);
                strcpy(person.data, dataf);
                total_H_mes = 0;
                total_P_mes = 0;
                for(mes = 1; mes < 13; mes++){
                  strcpy(strName, "relatorios-func-mes\\relatorio-mes-");
                  if(mes < 10){
                    strcat(strName, "0");
                  }
                  // convert 123 to string [buf]
                  itoa(mes, snum, 10);
                  strcat(strName, snum);
                  strcat(strName, "-");
                  //get_year(stringTime);
                  strcat(strName, date_arq);
                  strcat(strName, ".ogid\0");
                  arq = fopen(strName, "rb");
                  char *ptr;
                  if (arq == 0){
                      printf("Erro na abertura do arquivo %s \n", strName);
                  }else{
                      while(!feof(arq)){
                          if(fread(&p, sizeof(Usuario), 1, arq) == 1){
                              if(strcmp(p.rg, rgf) == 0){
                                int entr = hours_int(p.entrada);
                                int said = hours_int(p.saida);
                                int total_hours = said - entr;
                                total_H_mes += total_hours;
                                total_P_mes += strtod( p.pagamento, &ptr);
                                }
                            }
                        }
                  }
                  //printf("nome.: %s \n arq.: %s\n", namef, strName);
                  fclose(arq);
                }
                fprintf(arqA , "   <tr>\n");
                fprintf(arqA , "\t \t \t <th>Nome.: </th> <td align=\"center\" >%s</td>\n", namef);
                fprintf(arqA , "\t \t \t <th>Rg.: </th> <td align=\"center\" > %s </td>\n", rgf);
                fprintf(arqA , "\t \t \t <th>Total Horas no Ano.: </th> <td align=\"center\" >%d</td>\n", total_H_mes);
                fprintf(arqA , "\t \t \t <th>Total Pago  no Ano.: </th> <td align=\"center\" > %.2lf </td>\n", total_P_mes);
                fprintf(arqA , "   </tr>\n");
            }
        }
      }
      fprintf(arqA , "  </table> \n");
      fprintf(arqA , " </body> \n");
      fprintf(arqA , "</html> \n");
      fclose(arqA);
}

void relatorioMesFuncionario(gchar* date_arq){
      gint us_idf;
      gchar *namef, *telf, *rgf, *endf, *dataf, *entf, *saif, *pagf;
      Usuario person;
      GtkTreeIter iter;
      FILE* arqF;
      char strName_html[55];
      strcpy(strName_html, "relatorios-func-mes\\relatorio-");
      //get_mes(stringTime);
      strcat(strName_html, date_arq);
      strcat(strName_html, ".html\0");
      arqF = fopen(strName_html, "w");
      fprintf(arqF, "<html> \n"),
      fprintf(arqF, " <head> \n"),
      fprintf(arqF, "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
      fprintf(arqF, "  <title>Relat&#243;rio Do M&ecirc;s De Funcion&#225;rios </title> \n"),
      fprintf(arqF, " </head> \n"),
      fprintf(arqF, " <body> \n"),
      fprintf(arqF, "  <table border=\"1\" align=\"center\" width=\"1200\"> \n"),
      fprintf(arqF, "   <tr>\n");
      fprintf(arqF, "\t \t \t <th>Data .:</th>\n <th>%s</th> \n", date_arq),
      fprintf(arqF, "   </tr>\n");
      if(gtk_tree_model_get_iter_first (interface->treemodel_usu, &iter)){
                gtk_tree_model_get (interface->treemodel_usu, &iter,
                                         COLUMN_USER_ID,      &us_idf,
                                         COLUMN_USER_NOME,    &namef,
                                         COLUMN_USER_TELFONE, &telf,
                                         COLUMN_USER_RG,      &rgf,
                                         COLUMN_USER_END,     &endf,
                                         COLUMN_USER_ENT,     &entf,
                                         COLUMN_USER_SAI,     &saif,
                                         COLUMN_USER_PAG,     &pagf,
                                         COLUMN_USER_DATA,    &dataf, -1);
            person.userId = us_idf;
            strcpy(person.nome, namef);
            strcpy(person.telefone, telf);
            strcpy(person.rg, rgf);
            strcpy(person.ende, endf);
            strcpy(person.entrada, entf);
            strcpy(person.saida, saif);
            strcpy(person.pagamento, pagf);
            strcpy(person.data, dataf);
            Usuario p;
            //int jf = 0;
            FILE* arq;
            char strName[55];
            strcpy(strName, "relatorios-func-mes\\relatorio-mes-");
            strcat(strName, date_arq);
            strcat(strName, ".ogid\0");
            arq = fopen(strName, "rb");
            int total_H_mes = 0;
            double total_P_mes = 0;
            char *ptr;
            if (arq == 0){
                printf("Erro na abertura do arquivo %s \n", strName);
            }else{
                while(!feof(arq)){
                    if(fread(&p, sizeof(Usuario), 1, arq) == 1){
                       if(strcmp(p.rg, rgf) == 0){
                         fprintf(arqF, "   <tr>\n");
                         fprintf(arqF, "\t \t \t <th>Data    .:</th>\n <td>%s</td> \n", p.data),
                         fprintf(arqF, "\t \t \t <th>Entrada .:</td>\n <td>%s</td> \n", p.entrada),
                         fprintf(arqF, "\t \t \t <th>Saida   .:</td>\n <td>%s</td> \n", p.saida);
                         int entr = hours_int(p.entrada);
                         int said = hours_int(p.saida);
                         int total_hours = said - entr;
                         total_H_mes += total_hours;
                         total_P_mes += strtod( p.pagamento, &ptr);
                         fprintf(arqF, "\t \t \t <th>Total Horas .:</th>\n <td>%d</td> \n", total_hours),
                         fprintf(arqF, "\t \t \t <th>Pago    .:</th>\n <td>%s</td> \n", p.pagamento),
                         fprintf(arqF, "   </tr>\n");
                       }
                    }
                }
            }
            fprintf(arqF, "   <tr>\n");
            fprintf(arqF, "\t \t \t <th>Nome .:</th>\n <td>%s</td> \n", namef),
            fprintf(arqF, "\t \t \t <th>RG .:</th>\n <td>%s</td> \n", rgf),
            fprintf(arqF, "\t \t \t <th>Total Horas No Mes .:</th>\n <td>%d</td> \n", total_H_mes),
            fprintf(arqF, "\t \t \t <th>Total Pago  No Mes .:</th>\n <td>%.2lf</td> \n", total_P_mes),
            fprintf(arqF, "   </tr>\n");
            fclose(arq);
            while(gtk_tree_model_iter_next (interface->treemodel_usu, &iter) == TRUE){
                   gtk_tree_model_get (interface->treemodel_usu, &iter,
                                             COLUMN_USER_ID,      &us_idf,
                                             COLUMN_USER_NOME,    &namef,
                                             COLUMN_USER_TELFONE, &telf,
                                             COLUMN_USER_RG,      &rgf,
                                             COLUMN_USER_END,     &endf,
                                             COLUMN_USER_ENT,     &entf,
                                             COLUMN_USER_SAI,     &saif,
                                             COLUMN_USER_PAG,     &pagf,
                                             COLUMN_USER_DATA,    &dataf, -1);
                person.userId = us_idf;
                strcpy(person.nome, namef);
                strcpy(person.telefone, telf);
                strcpy(person.rg, rgf);
                strcpy(person.ende, endf);
                strcpy(person.entrada, entf);
                strcpy(person.saida, saif);
                strcpy(person.pagamento, pagf);
                strcpy(person.data, dataf);
                arq = fopen(strName, "rb");
                total_H_mes = 0;
                total_P_mes = 0;
                if (arq == 0){
                    printf("Erro na abertura do arquivo .html \n");
                }else{
                    while(!feof(arq)){
                        if(fread(&p, sizeof(Usuario), 1, arq) == 1){
                            if(strcmp(p.rg, rgf) == 0){
                             fprintf(arqF, "   <tr>\n");
                             fprintf(arqF, "\t \t \t <th>Data    .:</th>\n <td>%s</td> \n", p.data),
                             fprintf(arqF, "\t \t \t <th>Entrada .:</td>\n <td>%s</td> \n", p.entrada),
                             fprintf(arqF, "\t \t \t <th>Saida   .:</td>\n <td>%s</td> \n", p.saida);
                             int entr = hours_int(p.entrada);
                             int said = hours_int(p.saida);
                             int total_hours = said - entr;
                             total_H_mes += total_hours;
                             total_P_mes += strtod( p.pagamento, &ptr);
                             fprintf(arqF, "\t \t \t <th>Total Horas .:</th>\n <td>%d</td> \n", total_hours),
                             fprintf(arqF, "\t \t \t <th>Pago  .:</th>\n <td>%s</td> \n", p.pagamento),
                             fprintf(arqF, "   </tr>\n");
                            }
                        }
                    }
                }
              fprintf(arqF, "   <tr>\n");
              fprintf(arqF, "\t \t \t <th>Nome .:</th>\n <td>%s</td> \n", namef),
              fprintf(arqF, "\t \t \t <th>RG .:</th>\n <td>%s</td> \n", rgf),
              fprintf(arqF, "\t \t \t <th>Total Horas No Mes .:</th>\n <td>%d</td> \n", total_H_mes),
              fprintf(arqF, "\t \t \t <th>Total Pago  No Mes .:</th>\n <td>%.2lf</td> \n", total_P_mes),
              fprintf(arqF, "   </tr>\n");
              fclose(arq);
            }
        }
        fprintf(arqF, " </table> \n"),
        fprintf(arqF, " </body> \n"),
        fprintf(arqF, "</html> \n"),
        fclose(arqF);
}

void relatorioDiaFuncionario(gchar* date_arq){
        gint us_idf;
        gchar *namef, *telf, *rgf, *endf, *dataf, *entf, *saif, *pagf;
        Usuario person;
        GtkTreeIter iter;
        FILE* arqF;
        char strName_html[55];
        strcpy(strName_html, "relatorios-func-dia\\relatorio-");
        //data_arq(stringTime);
        strcat(strName_html, date_arq);
        strcat(strName_html, ".html\0");
        arqF = fopen(strName_html, "w");
        fprintf(arqF, "<html> \n"),
        fprintf(arqF, " <head> \n"),
        fprintf(arqF, "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
        fprintf(arqF, "  <title>Relat&#243;rio Do Dia De Funcion&#225;rios</title> \n"),
        fprintf(arqF, " </head> \n"),
        fprintf(arqF, " <body> \n"),
        fprintf(arqF, "  <table border=\"1\" align=\"center\" width=\"1200\"> \n"),
        fprintf(arqF, "   <tr>\n");
        //pega_dataehora(stringTime);
        fprintf(arqF, "\t \t \t <th>Data .:</th>\n <th>%s</th> \n", date_arq),
        fprintf(arqF, "   </tr>\n");
        if(gtk_tree_model_get_iter_first (interface->treemodel_usu, &iter)){
                gtk_tree_model_get (interface->treemodel_usu, &iter,
                                         COLUMN_USER_ID,      &us_idf,
                                         COLUMN_USER_NOME,    &namef,
                                         COLUMN_USER_TELFONE, &telf,
                                         COLUMN_USER_RG,      &rgf,
                                         COLUMN_USER_END,     &endf,
                                         COLUMN_USER_ENT,     &entf,
                                         COLUMN_USER_SAI,     &saif,
                                         COLUMN_USER_PAG,     &pagf,
                                         COLUMN_USER_DATA,    &dataf, -1);
            person.userId = us_idf;
            strcpy(person.nome, namef);
            strcpy(person.telefone, telf);
            strcpy(person.rg, rgf);
            strcpy(person.ende, endf);
            strcpy(person.entrada, entf);
            strcpy(person.saida, saif);
            strcpy(person.pagamento, pagf);
            strcpy(person.data, dataf);
            Usuario p;
            int jf = 0;
            FILE* arq;
            char strName[55];
            strcpy(strName, "relatorios-func-mes\\relatorio-mes-");
            //get_mes(stringTime);
            //subtrair dia da strind date_arq
            strcat(strName, &date_arq[3]);
            strcat(strName, ".ogid\0");
            //printf("%s\n", strName);
            arq = fopen(strName, "a+b");
            while(!feof(arq)){
                if(fread(&p, sizeof(Usuario), 1, arq) == 1){
                   if(strcmp(p.rg, rgf) == 0){
                    if(strcmp(person.data, p.data) == 0){
                        jf++;
                    }
                   }
                }
            }
            if(jf == 0){
               if((fwrite(&person, sizeof(Usuario), 1, arq) == 1)){
                        fprintf(arqF, "   <tr>\n");
                        fprintf(arqF, "\t \t \t <th>Nome .:</th>\n <td>%s</td> \n", namef),
                        fprintf(arqF, "\t \t \t <th>RG .:</th>\n <td>%s</td> \n", rgf),
                        fprintf(arqF, "\t \t \t <th>Entrada .:</td>\n <th>%s</td> \n", entf),
                        fprintf(arqF, "\t \t \t <th>Saida   .:</td>\n <th>%s</td> \n", saif);
                        int entr = hours_int(entf);
                        int said = hours_int(saif);
                        int total_hours = said - entr;
                        fprintf(arqF, "\t \t \t <th>Total Horas .:</th>\n <td>%d</td> \n", total_hours),
                        fprintf(arqF, "\t \t \t <th>Pago    .:</th>\n <td>%s</td> \n", pagf),
                        fprintf(arqF, "   </tr>\n");
                }
            }
            jf = 0;
            fclose(arq);
            while(gtk_tree_model_iter_next (interface->treemodel_usu, &iter) == TRUE){
                   gtk_tree_model_get (interface->treemodel_usu, &iter,
                                             COLUMN_USER_ID,      &us_idf,
                                             COLUMN_USER_NOME,    &namef,
                                             COLUMN_USER_TELFONE, &telf,
                                             COLUMN_USER_RG,      &rgf,
                                             COLUMN_USER_END,     &endf,
                                             COLUMN_USER_ENT,     &entf,
                                             COLUMN_USER_SAI,     &saif,
                                             COLUMN_USER_PAG,     &pagf,
                                             COLUMN_USER_DATA,    &dataf, -1);
                person.userId = us_idf;
                strcpy(person.nome, namef);
                strcpy(person.telefone, telf);
                strcpy(person.rg, rgf);
                strcpy(person.ende, endf);
                strcpy(person.entrada, entf);
                strcpy(person.saida, saif);
                strcpy(person.pagamento, pagf);
                strcpy(person.data, dataf);
                arq = fopen(strName, "a+b");
                while(!feof(arq)){
                    if(fread(&p, sizeof(Usuario), 1, arq) == 1){
                        if(strcmp(p.rg, rgf) == 0){
                         if(strcmp(person.data, p.data) == 0){
                            jf++;
                         }
                        }
                    }
                }
                if(jf == 0){
                    if((fwrite(&person, sizeof(Usuario), 1, arq) == 1)){
                        fprintf(arqF, "   <tr>\n");
                        fprintf(arqF, "\t \t \t <th>Nome .:</th>\n <td>%s</td> \n", namef),
                        fprintf(arqF, "\t \t \t <th>RG .:</th>\n <td>%s</td> \n", rgf),
                        fprintf(arqF, "\t \t \t <th>Entrada .:</td>\n <th>%s</td> \n", entf),
                        fprintf(arqF, "\t \t \t <th>Saida   .:</td>\n <th>%s</td> \n", saif);
                        int entr = hours_int(entf);
                        int said = hours_int(saif);
                        int total_hours = said - entr;
                        fprintf(arqF, "\t \t \t <th>Total Horas .:</th>\n <td>%d</td> \n", total_hours),
                        fprintf(arqF, "\t \t \t <th>Pago    .:</th>\n <td>%s</td> \n", pagf),
                        fprintf(arqF, "   </tr>\n");
                    }
                }
                fclose(arq);
            }
        }
        fprintf(arqF, " </table> \n"),
        fprintf(arqF, " </body> \n"),
        fprintf(arqF, "</html> \n"),
        fclose(arqF);
}

gboolean valida_date_ano(const gchar* date_ano){
    int i;
    for(i = 0; i < 4; i++){
        //number
        if(!(date_ano[i] >= '0' && date_ano[i] <= '9'))
             return FALSE;
    }
    return TRUE;
}

void get_date_ano(GtkEntryBuffer* entry){
     date_a = gtk_entry_buffer_get_text(entry);
     //printf("%s", date_a);
     close_widget(interface->dataFilaAno);
     if(valida_date_ano(date_a)){
         double tent, tsai, ttotal;
         tent = 0;
         tsai = 0;
         ttotal = 0;
         //mes string
         char mnum[5];
         char dnum[5];
         char strName_html[45];
         char strName[45];
         FILE* arqM, *arqA;
         strcpy(strName_html, "relatorios-ano\\relatorio-ano-");
         strcat(strName_html, date_a);
         strcat(strName_html, ".html\0");
         arqA = fopen(strName_html, "w");
         fprintf(arqA , "<html> \n"),
         fprintf(arqA , " <head> \n"),
         fprintf(arqA , "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
         fprintf(arqA , "  <title>Relat&#243;rio Do Ano</title> \n"),
         fprintf(arqA , " </head> \n"),
         fprintf(arqA , " <body> \n"),
         fprintf(arqA , "  <table border=\"1\" align=center width=\"1200\"> \n");
         if (arqA == 0){
            printf("Erro na abertura do arquivo .html \n");
         }else{
           int dia, meses;
           for(meses = 1; meses < 13; meses++){
                noDia mes;
                mes.entrada = 0;
                mes.saida = 0;
                mes.resultado = 0;
                for(dia=1; dia < 32; dia++){
                       strcpy(strName, "relatorios-dia\\relatorio-");
                       if(dia < 10){
                          strcat(strName, "0");
                       }
                       itoa(dia, dnum, 10);
                       strcat(strName, dnum);
                       strcat(strName, "-");
                       if(meses < 10){
                          strcat(strName, "0");
                       }
                       itoa(meses, mnum, 10);
                       strcat(strName, mnum);
                       strcat(strName, "-");
                       strcat(strName, date_a);
                       strcat(strName, ".ogid\0");
                       printf("\n %s", strName);
                       arqM = fopen(strName, "rb");
                       noDia dia;
                       if(fread(&dia, sizeof(noDia), 1, arqM) == 1){
                            mes.entrada = dia.entrada;
                            mes.saida = dia.saida;
                            mes.resultado = dia.resultado;
                            tent += dia.entrada;
                            tsai += dia.saida;
                            ttotal += dia.resultado;
                       }
                }
                fprintf(arqA, "   <tr>\n");
                fprintf(arqA, "\t \t \t <th colspan=\"3\" align=center> Data.:  %d </th>\n", meses);
                fprintf(arqA, "\t \t \t <th colspan=\"3\" align=center> Abertura   De Caixa.:  %.2lf </th>\n", mes.entrada );
                fprintf(arqA, "\t \t \t <th colspan=\"3\" align=center> Sa&iacute;das     De Caixa.:  %.2lf </th>\n", mes.saida );
                fprintf(arqA, "\t \t \t <th colspan=\"3\" align=center> Fechamento Do Caixa.:  %.2lf </th>\n", mes.resultado );
                fprintf(arqA, "  </tr>\n");
                fclose(arqM);
            }
         }
         fprintf(arqA , "   <tr>\n");
         fprintf(arqA , "\t \t \t <th colspan=\"3\" align=center> Ano.:  %s </th>\n", date_a);
         fprintf(arqA , "\t \t \t <th colspan=\"3\" align=center> Fechamento De Entradas.:  %.2lf </th>\n", tent);
         fprintf(arqA , "\t \t \t <th colspan=\"3\" align=center> Fechamento De Sa&iacute;das.:  %.2lf </th>\n", tsai);
         fprintf(arqA , "\t \t \t <th colspan=\"3\" align=center> Fechamento De Caixa Do Ano.:  %.2lf </th>\n", ttotal);
         fprintf(arqA , "   </tr>\n");
         fprintf(arqA , "  </table> \n");
         fprintf(arqA , " </body> \n");
         fprintf(arqA , "</html> \n");
         fclose(arqA);

         relatorioAnoFuncionario(date_a);
         relatorioAnoInsumos(date_a);
         gtk_entry_buffer_set_text(entry,"",0);
     }else{
        message_of_error("O Ano foi lancado em branco ditige um ano para continuar!");
        gtk_entry_buffer_set_text(entry,"",0);
        close_widget(interface->dataFilaAno);
     }
}

gboolean valida_date_mes(const gchar* date_mes){
    int i;
    for(i = 0; i < 7; i++){
        if( i != 2 ){
           //number
           if(!(date_mes[i] >= '0' && date_mes[i] <= '9'))
              return FALSE;
        }else if(i == 2){
           if(!(date_mes[i] == '-'))
              return FALSE;
        }

    }
    return TRUE;
}

void get_date_mes(GtkEntryBuffer* entry){
    date_m = gtk_entry_buffer_get_text(entry);
    //printf("%s", date_m);
    close_widget(interface->dataFilaMes);
    if(valida_date_mes(date_m)){
        //printf("%s", date_m);
        int dia;
        char* snum[5];
        FILE* arq;
        char strName[45];
        FILE* arq_html;
        char strName_html[45];
        strcpy(strName_html, "relatorios-mes\\relatorio-mes-");
        strcat(strName_html, date_m);
        strcat(strName_html, ".html\0");
        arq_html = fopen(strName_html, "w");
        fprintf(arq_html, "<html> \n"),
        fprintf(arq_html, " <head> \n"),
        fprintf(arq_html, "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
        fprintf(arq_html, "  <title>Relat&#243;rio Do M&ecirc;s </title> \n"),
        fprintf(arq_html, " </head> \n"),
        fprintf(arq_html, " <body> \n"),
        fprintf(arq_html, "  <table border=\"1\" align=center width=\"1200\"> \n");
        fprintf(arq_html, "   <tr>\n");
        fprintf(arq_html, "   <td>\n");
        fprintf(arq_html, "   <td>\n");
        fprintf(arq_html, "   </tr>\n");
        double tent, tsaida,ttotal;
        tent = 0;
        tsaida = 0;
        ttotal = 0;
        for(dia=1; dia < 32; dia++){
           strcpy(strName, "relatorios-dia\\relatorio-");
           if(dia < 10){
              strcat(strName, "0");
           }
           itoa(dia, snum, 10);
           strcat(strName, snum);
           strcat(strName, "-");
           strcat(strName, date_m);
           strcat(strName, ".ogid\0");
           //printf("\n %s", strName);
           arq = fopen(strName, "rb");
            if (arq == 0){
                fprintf(arq_html, "   <tr>\n");
                fprintf(arq_html, "\t \t \t <th colspan=\"12\" align=center> Dia Nao Foi Fechado !</th>\n");
                fprintf(arq_html, "  </tr>\n");
            }else{
                //printf(" abriu.\n");
                noDia dia;
                   if(fread(&dia, sizeof(noDia), 1, arq) == 1){
                        fprintf(arq_html, "   <tr>\n");
                        fprintf(arq_html, "\t \t \t <th colspan=\"3\" align=center> Data.:  %s </th>\n", dia.data);
                        fprintf(arq_html, "\t \t \t <th colspan=\"3\" align=center> Abertura   De Caixa.:  %.2lf </th>\n", dia.entrada );
                        fprintf(arq_html, "\t \t \t <th colspan=\"3\" align=center> Sa&iacute;das     De Caixa.:  %.2lf </th>\n", dia.saida );
                        fprintf(arq_html, "\t \t \t <th colspan=\"3\" align=center> Fechamento Do Caixa.:  %.2lf </th>\n", dia.resultado );
                        fprintf(arq_html, "  </tr>\n");
                        tent += dia.entrada;
                        tsaida += dia.saida;
                        ttotal += dia.resultado;
                   }
                }

            }
            fprintf(arq_html, "   <tr>\n");
            fprintf(arq_html, "\t \t \t <th colspan=\"4\" align=center> Fechamento De Entrada Do M&ecirc;s.:  %.2lf </th>\n", tent);
            fprintf(arq_html, "\t \t \t <th colspan=\"4\" align=center> Fechamento De Saida Do M&ecirc;s.:  %.2lf </th>\n", tsaida);
            fprintf(arq_html, "\t \t \t <th colspan=\"4\" align=center> Fechamento Do Caixa Do M&ecirc;s.:  %.2lf </th>\n", ttotal);
            fprintf(arq_html, "   </tr>\n");
            fprintf(arq_html, "  </table> \n");
            fprintf(arq_html, " </body> \n");
            fprintf(arq_html, "</html> \n");
            relatorioMesFuncionario(date_m);
            relatorioMesInsumos(date_m);
            // ao final do uso, o arquivo deve ser fechado
            fclose(arq);
            fclose(arq_html);
            gtk_entry_buffer_set_text(entry,"",0);
    }else{
        message_of_error("O mes foi lancado em branco ditige um mes para continuar!");
        gtk_entry_buffer_set_text(entry,"",0);
        close_widget(interface->dataFilaMes);
    }
}
void diagnostic(GtkWidget *win){
     GtkTreeIter iter;
     GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_index);
     if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
        gchar *id_vehi, *prop, *obs, *valor, *mode, *vend, *super, *gor;
        gint nos;
        gtk_tree_model_get (interface->treemodel_index, &iter,
                            COLUMN_ITEM_IDVEHICLES , &id_vehi,
                            COLUMN_ITEM_VEICULO, &mode,
                            COLUMN_ITEM_PROPREITARIO, &prop,
                            COLUMN_ITEM_N_OS, &nos,
                            COLUMN_ITEM_VALOR, &valor,
                            COLUMN_ITEM_VENDEDOR, &vend,
                            COLUMN_ITEM_SUPERVISOR, &super,
                            COLUMN_ITEM_GORJETA, &gor,
                            COLUMN_ITEM_OBS, &obs, -1);

        Arvore *no = buscar(vehicles, id_vehi);
        Veiculo veiculos = no->info;
        ListaServico *serv;

        //int i = 0;
        FILE* arq;
        char strName[45];
        strcpy(strName, "diagn\\diagnostico-");
        data_arq(stringTime);
        strcat(strName, stringTime);
        strcat(strName, "-");
        strcat(strName, id_vehi);
        strcat(strName, ".html\0");
        arq = fopen(strName, "w");

        if (arq == 0){
            printf("Erro na abertura do arquivo");
        }else{
            fprintf(arq, "<html> \n"),
            fprintf(arq, " <head> \n"),
            fprintf(arq, "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
            fprintf(arq, "  <title>Diagn&#243;stico do Ve&#237;culo</title> \n"),
            fprintf(arq, " </head> \n"),
            fprintf(arq, " <body> \n"),
            fprintf(arq, "  <table border=\"1\" align=center width=800> \n"),
            fprintf(arq, "   <tr>\n"),
            fprintf(arq, "\t \t \t <td colspan=\"1\" align=center><img src=\"../images/logo-site-lavacar.png\" width=\"100\" /></td> \n"),
            fprintf(arq, "\t \t \t <th colspan=\"2\"><h1>Diagn&#243;stico do Ve&#237;culo</h1></th> \n"),
            fprintf(arq, "   </tr>\n"),
            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t<th rowspan=\"7\"><h2>N&#186;OS: %d</h2></th>\n", nos),
            fprintf(arq, "\t \t<th>Propriet&#225;rio.:</th> <td align=center>%s<br /></td> \n", prop),
            fprintf(arq, "  </tr>\n"),
            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t<th>Placa.:</th> <td  align=center>%s<br /></td>\n", id_vehi),
            fprintf(arq, "  </tr>\n"),
            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t <th>Modelo.:</th>  <td align=center>%s<br /></td> \n", mode),
            fprintf(arq, "  </tr>\n"),
            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t<th>Valor Total.:</th> <td align=center>%s<br /></td> \n", valor),
            fprintf(arq, "  </tr>\n"),
            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t<th>Atendente.:</th> <td  align=center>%s<br /></td> \n", vend),
            fprintf(arq, "  </tr>\n"),
            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t<th>Supervisor.:</th> <td  align=center>%s<br /></td> \n", super),
            fprintf(arq, "  </tr>\n"),
            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t<th>Gorjeta.:</th> <td  align=center>%s<br /></td> \n", gor),
            fprintf(arq, "  </tr>\n"),
            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t<th>O extintor vence em:</th> <td colspan=\"2\" align=center>%s<br /></td> \n", gtk_entry_buffer_get_text(interface->extintor));
            fprintf(arq, "  </tr>\n"),
            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t<th>Km Atual de &#243;leo:</th> <td colspan=\"2\" align=center>%s<br /></td> \n", gtk_entry_buffer_get_text(interface->trocaOleo));
            fprintf(arq, "  </tr>\n");
            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t<th>Km para a pr&#243;xima troca de &#243;leo:</th> <td colspan=\"2\" align=center>%s<br /></td> \n", gtk_entry_buffer_get_text(interface->oleo));
            fprintf(arq, "  </tr>\n");

            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t<th>Observa&#231;&#245;es:</th> <td colspan=\"2\">%s<br /></td> \n", obs),
            fprintf(arq, "  </tr>\n"),

            fprintf(arq, "  <tr>\n"),
            fprintf(arq, "\t \t \t <td colspan=\"1\" align=center><img src=\"../images/services.png\" width=\"100\" /></td> \n"),
            fprintf(arq, "\t \t \t<th colspan=\"2\"><br /> <h1>Servi&#231;os Prestados</h1> <br /></th>\n");
            fprintf(arq, "  </tr>\n");
            int i = 0;

            while(veiculos.servicos[i] != 0 && i < 10){
                   serv = procurar(services, veiculos.servicos[i]);

                   fprintf(arq, "  <tr>\n"),
                   fprintf(arq, "\t \t<th aling=left>Nome:</th> <td colspan=\"2\" align=center> %d. %s<br /></td> \n", i+1, serv->info.nome);
                   fprintf(arq, "  </tr>\n");

                   if(strcmp(veiculos.tamanho, "Pequeno") == 0){
                        fprintf(arq, "  <tr>\n"),
                        fprintf(arq, "\t \t<th aling=left>Valor:</th> <td colspan=\"2\" align=center>%.2lf<br /></td> \n", serv->info.valorP);
                        fprintf(arq, "  </tr>\n");
                   }else if(strcmp(veiculos.tamanho, "Medio") == 0){
                        fprintf(arq, "  <tr>\n"),
                        fprintf(arq, "\t \t<th aling=left>Valor:</th> <td colspan=\"2\" align=center>%.2lf<br /></td> \n", serv->info.valorM);
                        fprintf(arq, "  </tr>\n");
                   }else{
                        fprintf(arq, "  <tr>\n"),
                        fprintf(arq, "\t \t<th aling=left>Valor:</th> <td colspan=\"2\" align=center>%.2lf<br /></td> \n", serv->info.valorG);
                        fprintf(arq, "  </tr>\n");
                   }

                   fprintf(arq, "  <tr>\n"),
                   fprintf(arq,"\t \t<th aling=left>Descri&#231;&#227;o:</th> <td colspan=\"2\" align=center>%s<br /></td> \n", serv->info.descri);
                   fprintf(arq, "  </tr>\n"),
                   i++;
             }

             fprintf(arq, "  <tr>\n"),
             fprintf(arq, "\t \t \t <td colspan=\"1\" align=center><img src=\"../images/services.png\" width=\"100\" /></td> \n"),
             fprintf(arq, "\t \t \t<th colspan=\"2\"><br /> <h1>Servi&#231;os Sugeridos</h1> <br /></th>\n");
             fprintf(arq, "  </tr>\n");

             gboolean tf;
             gint serv_id;
             GtkTreeIter iters;
             if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL (interface->treemodel_ser), &iters)){
                gtk_tree_model_get(interface->treemodel_ser,  &iters,
                                      COLUMN_SERV_X,   &tf,
                                      COLUMN_SERV_ID,  &serv_id, -1);
               if(tf  == 1){
                   ListaServico *ser = services; //var. para percorrer a lista
                   while(ser->info.serId != serv_id && ser != NULL){
                             ser = ser->next;
                   }
                   if(ser != NULL){
                     fprintf(arq, "  <tr>\n"),
                     fprintf(arq, "\t \t<th aling=left>Nome: </th> <th colspan=\"2\" aling=left> %s </th>  \n",  ser->info.nome);
                     fprintf(arq, "  </tr>\n"),
                     fprintf(arq, "  <tr>\n"),
                     fprintf(arq,"\t \t <th aling=left>Descri&#231;&#227;o:</th> <th colspan=\"2\" aling=left> %s </th>\n", ser->info.descri);
                     fprintf(arq, "  </tr>\n");
                   }
                 i++;
                }
             }
             while(gtk_tree_model_iter_next (interface->treemodel_ser, &iters) == TRUE){
                gtk_tree_model_get(interface->treemodel_ser,  &iters,
                                      COLUMN_SERV_X,   &tf,
                                      COLUMN_SERV_ID,  &serv_id, -1);
                if(tf  == 1){
                   ListaServico *ser = services; //var. para percorrer a lista
                   while(ser->info.serId != serv_id && ser != NULL){
                             ser = ser->next;
                   }
                   if(ser != NULL){
                     fprintf(arq, "  <tr>\n"),
                     fprintf(arq, "\t \t<th aling=left>Nome: </th> <th colspan=\"2\" aling=left> %s </th>  \n",  ser->info.nome);
                     fprintf(arq, "  </tr>\n"),
                     fprintf(arq, "  <tr>\n"),
                     fprintf(arq,"\t \t <th aling=left>Descri&#231;&#227;o:</th> <th colspan=\"2\" aling=left> %s </th>\n", ser->info.descri);
                     fprintf(arq, "  </tr>\n");
                   }
                 i++;
                }
            }
            fprintf(arq, "  </table>\n");
            fprintf(arq, " </body>\n");
            fprintf(arq, "</html>");
        }

        free(id_vehi);
        free(prop);
        free(obs);
        free(valor);
        free(mode);
        free(vend);
        free(super);
        free(gor);
        fclose(arq);
     }

     gtk_entry_buffer_set_text(interface->extintor,  "", 0);
     gtk_entry_buffer_set_text(interface->oleo,    "", 0);
     gtk_entry_buffer_set_text(interface->trocaOleo,    "", 0);
}



gboolean valida_date(const gchar* date){
    int i;
    for(i = 0; i < 10; i++){
        if( i != 2 && i != 5 ){
           //number
           if(!(date[i] >= '0' && date[i] <= '9'))
              return FALSE;
        }else if( i == 2 || i == 5 ){
           if(!(date[i] == '-'))
              return FALSE;
        }
    }
    return TRUE;
}

void get_date_queue(GtkEntryBuffer* entry){
     date_d = gtk_entry_buffer_get_text(entry);
     close_widget(interface->dataFila);
     if(valida_date(date_d)){
         //printf("\n date is .: %s", date_d);
         FILE* arqR;
         char strName[45];
         strcpy(strName, "relatorios-dia\\relatorio-");
         strcat(strName, date_d);
         strcat(strName, ".html\0");
         //printf("\n date is .: %s", strName);
         arqR = fopen(strName, "w");
         if (arqR != 0){
             GtkTreeIter iter;
             gboolean tf;
             char *ptr;
             gdouble cart, dinh, lucr;
             cart = 0;
             dinh = 0;
             lucr = 0;
             gchar *id_vehi, *entr, *sai, *prop, *obs, *valor, *mode, *vend, *super, *gor;
             gint n, nos;
             if(gtk_tree_model_get_iter_first (interface->treemodel_index, &iter)){
                if (arqR == 0){
                    printf("Erro na abertura do arquivo\n");
                }else{
                    fprintf(arqR, "<html> \n"),
                    fprintf(arqR, " <head> \n"),
                    fprintf(arqR, "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
                    fprintf(arqR, "  <title>Relat&#243;rio Do Dia</title> \n"),
                    fprintf(arqR, " </head> \n"),
                    fprintf(arqR, " <body> \n"),
                    fprintf(arqR, "  <table border=\"1\" align=\"center\" width=\"1200\"> \n"),
                    fprintf(arqR, "   <tr>\n");
                    fprintf(arqR, "\t \t \t <th>Data .:</th>\n <th>%s</th> \n", date_d),
                    fprintf(arqR, "   </tr>\n");
                    fprintf(arqR, "   <tr>\n"),
                    fprintf(arqR, "\t \t \t <th>N&#186;.:</th>\n <th>Entrada.:</th>\n <th>Sa&#237;da.:</th>\n <th>Placa.:</th>\n"),
                    fprintf(arqR, "\t \t \t <th>Modelo.:</th>\n <th>Propriet&#225;rio.:</th>\n <th>N&#186;.OS.:</th>\n <th>Valor.:</th>\n"),
                    fprintf(arqR, "\t \t \t <th>Vendedor.:</th>\n <th>Supervisor.:</th>\n <th>Gorjeta.:</th>\n <th>Obs.:</th>\n"),
                    fprintf(arqR, "   </tr>\n");

                    gtk_tree_model_get (interface->treemodel_index, &iter,
                                        COLUMN_ITEM_N, &n,
                                        COLUMN_ITEM_IDVEHICLES , &id_vehi,
                                        COLUMN_ITEM_VEICULO, &mode,
                                        COLUMN_ITEM_ENTRADA, &entr,
                                        COLUMN_ITEM_SAIDA,   &sai,
                                        COLUMN_ITEM_PROPREITARIO, &prop,
                                        COLUMN_ITEM_N_OS, &nos,
                                        COLUMN_ITEM_VALOR, &valor,
                                        COLUMN_SERV_X,   &tf,
                                        COLUMN_ITEM_VENDEDOR, &vend,
                                        COLUMN_ITEM_SUPERVISOR, &super,
                                        COLUMN_ITEM_GORJETA, &gor,
                                        COLUMN_ITEM_OBS, &obs, -1);

                    fprintf(arqR, "   <tr>\n");
                    fprintf(arqR, "\t \t \t <td align=\"center\">%d</td>\n <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n",
                            n, entr, sai, id_vehi);
                    fprintf(arqR, "\t \t \t <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n <td align=\"center\">%d</td>\n <td align=\"center\">%s</td>\n",
                            mode, prop,  nos, valor);
                    fprintf(arqR, "\t \t \t <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n",
                            vend, super, gor, obs);
                    fprintf(arqR, "   </tr>\n");

                    if( tf == TRUE){
                        cart = strtod(valor, &ptr);
                    }else{
                        dinh = strtod(valor, &ptr);
                    }
                        lucr = strtod(valor, &ptr);

                    while(gtk_tree_model_iter_next (interface->treemodel_index, &iter) == TRUE){
                          gtk_tree_model_get (interface->treemodel_index, &iter,
                                        COLUMN_ITEM_N, &n,
                                        COLUMN_ITEM_IDVEHICLES , &id_vehi,
                                        COLUMN_ITEM_VEICULO, &mode,
                                        COLUMN_ITEM_ENTRADA, &entr,
                                        COLUMN_ITEM_SAIDA,   &sai,
                                        COLUMN_ITEM_PROPREITARIO, &prop,
                                        COLUMN_ITEM_N_OS, &nos,
                                        COLUMN_ITEM_VALOR, &valor,
                                        COLUMN_SERV_X,   &tf,
                                        COLUMN_ITEM_VENDEDOR, &vend,
                                        COLUMN_ITEM_SUPERVISOR, &super,
                                        COLUMN_ITEM_GORJETA, &gor,
                                        COLUMN_ITEM_OBS, &obs, -1);

                            fprintf(arqR, "   <tr>\n");
                            fprintf(arqR, "\t \t \t <td align=\"center\">%d</td>\n <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n",
                                    n, entr, sai, id_vehi);
                            fprintf(arqR, "\t \t \t <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n <td align=\"center\">%d</td>\n <td align=\"center\">%s</td>\n",
                                    mode, prop,  nos, valor);
                            fprintf(arqR, "\t \t \t <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n <td align=\"center\">%s</td>\n",
                                    vend, super, gor, obs);
                            fprintf(arqR, "   </tr>\n");
                              if( tf == TRUE){
                                  cart += strtod(valor, &ptr);
                              }else{
                                  dinh += strtod(valor, &ptr);
                              }
                                  lucr += strtod(valor, &ptr);

                    }
                            fprintf(arqR, "   <tr>\n"),
                            fprintf(arqR, "\t \t \t <td colspan=\"3\" align=\"center\" > total pago com cartao.:</td>\n <td align=\"center\">%.2lf</td>\n <td colspan=\"3\" align=\"center\">total pago com dinheiro.:</td>\n <td align=\"center\">%.2lf</td>\n <td colspan=\"3\" align=\"center\">total.:</td>\n <td align=\"center\">%.2lf</td>\n",
                                    cart, dinh, lucr);
                            fprintf(arqR, "</tr>\n");
                    fprintf(arqR, "  </table>\n"),

                    fprintf(arqR, "\t  <br />\n"),

                    fprintf(arqR, "  <table border=\"0\" align=\"center\" width=\"1200\"> \n"),
                    fprintf(arqR, "\t  <tr>\n"),

                    fprintf(arqR, "\t  <td>\n"),

                    //1tabela
                    fprintf(arqR, "  <table border=\"1\" align=\"center\" width=\"800\">\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t<th colspan=\"1\"> N.: </th> <th colspan=\"5\"> Saidas </th> <th colspan=\"4\"> Valor </th>\n");
                    fprintf(arqR, "\t  </tr>\n");

                    if(gtk_tree_model_get_iter_first (interface->treemodel_despesa, &iter)){
                        gtk_tree_model_get (interface->treemodel_despesa, &iter,
                                        COLUMN_DESP_NUMBER, &n,
                                        COLUMN_DESP_DESCRI, &sai,
                                        COLUMN_DESP_VALOR,  &valor, -1);
                        fprintf(arqR, "\t  <tr>\n"),
                        fprintf(arqR, "\t \t \t <td colspan=\"1\" align=\"center\" > %d </td> <td colspan=\"5\" align=\"center\" > %s </td> <td colspan=\"4\" align=\"center\"> %s </td>\n", n, sai, valor);
                        fprintf(arqR, "\t  </tr>\n");
                        while(gtk_tree_model_iter_next (interface->treemodel_despesa, &iter) == TRUE){
                              gtk_tree_model_get (interface->treemodel_despesa, &iter,
                                        COLUMN_DESP_NUMBER, &n,
                                        COLUMN_DESP_DESCRI, &sai,
                                        COLUMN_DESP_VALOR,  &valor, -1);
                        fprintf(arqR, "\t  <tr>\n"),
                        fprintf(arqR, "\t \t \t <td colspan=\"1\" align=\"center\"> %d </td> <td colspan=\"5\" align=\"center\"> %s </td> <td colspan=\"4\" align=\"center\"> %s </td>\n", n, sai, valor);
                        fprintf(arqR, "\t  </tr>\n");
                        }
                    }
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t<th colspan=\"6\"> Total de Despesas </th> <th colspan=\"4\" align=\"center\"> %.2lf </th>\n", resultado_dia.saida);
                    fprintf(arqR, "\t  </tr>\n");
                    fprintf(arqR, "  </table>\n"),

                    fprintf(arqR, "\t  </td>\n"),

                    fprintf(arqR, "\t  <td>\n"),

                    //3 tabela
                    fprintf(arqR, "  <table border=\"1\" align=\"center\" width=\"300\">\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"6\"> Movimento </th>\n");
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"3\" align=center> Entrada.: </th>\n <td colspan=\"3\" align=center>%.2lf</td>\n ", (resultado_dia.entrada + lucr));
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"3\" align=center> Saida.: </th>\n <td colspan=\"3\" align=center>%.2lf</td>\n ", resultado_dia.saida);
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"3\" align=center> Resultado.: </th>\n <td colspan=\"3\" align=center>%.2lf</td>\n ", ((resultado_dia.entrada + lucr) - resultado_dia.saida));
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "  </table>\n"),

                    fprintf(arqR, "\t  <br />\n"),

                    fprintf(arqR, "  <table align=\"center\" width=\"300\">\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"6\"> Gerente.:______________________ </th>\n");
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "  </table>\n"),

                    fprintf(arqR, "\t  <br />\n"),

                    fprintf(arqR, "  <table border=\"1\" align=\"center\" width=\"300\">\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"6\" align=center> Abertura De Caixa.:  %.2lf</th>\n", resultado_dia.entrada );
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"6\" align=center> Fechamento De Caixa.: %.2lf</th>\n",((resultado_dia.entrada + lucr) - resultado_dia.saida));
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "  </table>\n"),

                    fprintf(arqR, "\t  </td>\n"),
                    fprintf(arqR, "\t  </tr>\n"),


                    fprintf(arqR, "  </table>\n"),
                    fprintf(arqR, " </body>\n"),
                    fprintf(arqR, "</html>");

                    resultado_dia.resultado = (( resultado_dia.entrada + lucr) - resultado_dia.saida);
                    save_relatorio_dia();
                }
             }else{
                if (arqR == 0){
                    printf("Erro na abertura do arquivo\n");
                }else{
                    fprintf(arqR, "<html> \n"),
                    fprintf(arqR, " <head> \n"),
                    fprintf(arqR, "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \n"),
                    fprintf(arqR, "  <title>Relat&#243;rio</title> \n"),
                    fprintf(arqR, " </head> \n"),
                    fprintf(arqR, " <body> \n"),
                    fprintf(arqR, "  <table border=\"1\" align=\"center\" width=\"1200\"> \n"),
                    fprintf(arqR, "   <tr>\n");
                    fprintf(arqR, "\t \t \t <th>Data .:</th>\n <th>%s</th> \n", date_d),
                    fprintf(arqR, "   </tr>\n");
                    //printf("\n date is .: %s", date_d);

                    fprintf(arqR, "   <tr>\n"),
                    fprintf(arqR, "\t \t \t <th>N&#186;.:</th>\n <th>Entrada.:</th>\n <th>Sa&#237;da.:</th>\n <th>Placa.:</th>\n"),
                    fprintf(arqR, "\t \t \t <th>Modelo.:</th>\n <th>Propriet&#225;rio.:</th>\n <th>N&#186;.OS.:</th>\n <th>Valor.:</th>\n"),
                    fprintf(arqR, "\t \t \t <th>Vendedor.:</th>\n <th>Supervisor.:</th>\n <th>Gorjeta.:</th>\n <th>Obs.:</th>\n"),
                    fprintf(arqR, "   </tr>\n");

                    fprintf(arqR, "   <tr>\n"),
                    fprintf(arqR, "\t \t \t <td colspan=\"3\" align=\"center\" > total pago com cartao.:</td>\n <td align=\"center\">%.2lf</td>\n <td colspan=\"3\" align=\"center\">total pago com dinheiro.:</td>\n <td align=\"center\">%.2lf</td>\n <td colspan=\"3\" align=\"center\">total.:</td>\n <td align=\"center\">%.2lf</td>\n",
                                    cart, dinh, lucr);
                    fprintf(arqR, "</tr>\n");
                    fprintf(arqR, "  </table>\n"),

                    fprintf(arqR, "\t  <br />\n"),

                    fprintf(arqR, "  <table border=\"0\" align=\"center\" width=\"1200\"> \n"),
                    fprintf(arqR, "\t  <tr>\n"),

                    fprintf(arqR, "\t  <td>\n"),

                    //1tabela
                    fprintf(arqR, "  <table border=\"1\" align=\"center\" width=\"800\">\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t<th colspan=\"1\"> N.: </th> <th colspan=\"5\"> Saidas </th> <th colspan=\"4\"> Valor </th>\n");
                    fprintf(arqR, "\t  </tr>\n");

                    if(gtk_tree_model_get_iter_first (interface->treemodel_despesa, &iter)){
                        gtk_tree_model_get (interface->treemodel_despesa, &iter,
                                        COLUMN_DESP_NUMBER, &n,
                                        COLUMN_DESP_DESCRI, &sai,
                                        COLUMN_DESP_VALOR,  &valor, -1);
                        fprintf(arqR, "\t  <tr>\n"),
                        fprintf(arqR, "\t \t \t <td colspan=\"1\" align=\"center\" > %d </td> <td colspan=\"5\" align=\"center\" > %s </td> <td colspan=\"4\" align=\"center\"> %s </td>\n", n, sai, valor);
                        fprintf(arqR, "\t  </tr>\n");
                        while(gtk_tree_model_iter_next (interface->treemodel_despesa, &iter) == TRUE){
                              gtk_tree_model_get (interface->treemodel_despesa, &iter,
                                        COLUMN_DESP_NUMBER, &n,
                                        COLUMN_DESP_DESCRI, &sai,
                                        COLUMN_DESP_VALOR,  &valor, -1);
                        fprintf(arqR, "\t  <tr>\n"),
                        fprintf(arqR, "\t \t \t <td colspan=\"1\" align=\"center\"> %d </td> <td colspan=\"5\" align=\"center\"> %s </td> <td colspan=\"4\" align=\"center\"> %s </td>\n", n, sai, valor);
                        fprintf(arqR, "\t  </tr>\n");
                        }
                    }
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t<th colspan=\"6\"> Total de Despesas </th> <th colspan=\"4\" align=\"center\"> %.2lf </th>\n", resultado_dia.saida);
                    fprintf(arqR, "\t  </tr>\n");
                    fprintf(arqR, "  </table>\n"),

                    fprintf(arqR, "\t  </td>\n"),

                    fprintf(arqR, "\t  <td>\n"),

                    //3 tabela
                    fprintf(arqR, "  <table border=\"1\" align=\"center\" width=\"300\">\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"6\"> Movimento </th>\n");
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"3\" align=center> Entrada.: </th>\n <td colspan=\"3\" align=center>%.2lf</td>\n ", (resultado_dia.entrada + lucr));
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"3\" align=center> Saida.: </th>\n <td colspan=\"3\" align=center>%.2lf</td>\n ", resultado_dia.saida);
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"3\" align=center> Resultado.: </th>\n <td colspan=\"3\" align=center>%.2lf</td>\n ", ((resultado_dia.entrada + lucr) - resultado_dia.saida));
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "  </table>\n"),

                    fprintf(arqR, "\t  <br />\n"),

                    fprintf(arqR, "  <table align=\"center\" width=\"300\">\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"6\"> Gerente.:______________________ </th>\n");
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "  </table>\n"),

                    fprintf(arqR, "\t  <br />\n"),

                    fprintf(arqR, "  <table border=\"1\" align=\"center\" width=\"300\">\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"6\" align=center> Abertura De Caixa.:  %.2lf</th>\n", resultado_dia.entrada );
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "\t  <tr>\n"),
                    fprintf(arqR, "\t \t \t <th colspan=\"6\" align=center> Fechamento De Caixa.: %.2lf</th>\n",((resultado_dia.entrada + lucr) - resultado_dia.saida));
                    fprintf(arqR, "\t  </tr>\n"),
                    fprintf(arqR, "  </table>\n"),

                    fprintf(arqR, "\t  </td>\n"),
                    fprintf(arqR, "\t  </tr>\n"),


                    fprintf(arqR, "  </table>\n"),
                    fprintf(arqR, " </body>\n"),
                    fprintf(arqR, "</html>");
                    resultado_dia.resultado = ((resultado_dia.entrada + lucr) - resultado_dia.saida);
                    //printf("\n date is .: %s", date_d);
                    save_relatorio_dia();
               }
            }
           relatorioDiaFuncionario(date_d);
           relatorioDiaInsumos(date_d);
         }else{
              message_of_error("Nao foi possivel criar um arquivo.html da data lancada!");
         }
         fclose(arqR);
         gtk_entry_buffer_set_text(entry,"",0);
     }else{
        message_of_error("A data foi lancada em branco ditige uma data para continuar!");
        gtk_entry_buffer_set_text(entry,"",0);
        close_widget(interface->dataFila);
     }
}
