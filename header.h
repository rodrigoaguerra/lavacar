#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <locale.h>


/* STRUCTS SYSTEM */

typedef struct no_dia{
    char    data[15];
    double   entrada;
    double     saida;
    double resultado;
} noDia;


typedef struct cliente{
    unsigned int             id;
    char              nome[100];
    char           telefone[10];
    char               data[11];

} Cliente;

typedef struct ins_gastos{
    //info services
    int        id_ins;
    double      qntdP;
    double      qntdM;
    double      qntdG;

} InsGast;

typedef struct servico{

    //info services
    int           serId;
    char      nome[100];
    double       valorP;
    double       valorM;
    double       valorG;
    char    descri[555];
    InsGast  gastos[10];

} Servico;

typedef struct insumo{
    //info insumo
    int        insId;
    double     valor;
    double     quant;
    char   nome[100];
    char     tipo[8];
    char descri[555];

} Insumo;
typedef struct usuario{

    //info insumo
    int         userId;
    char     nome[100];
    char  telefone[10];
    char        rg[10];
    char     ende[555];
    char    entrada[8];
    char      saida[8];
    char pagamento[10];
    char      data[11];

} Usuario;

typedef struct veiculo{
    //info data
    char     data[11];
    char   entrada[6];
    char     saida[6];

    //info veiculo
    int        cli_id;
    char      cor[25];
    char     placa[9];
    char   modelo[55];
    char  tamanho[10];
    int  servicos[10];
    char  descri[555];

} Veiculo;


typedef struct arvore{
    Veiculo info;
    struct arvore *esq;
    struct arvore *dir;
} Arvore;

typedef struct nodeInsumo
{
    Insumo info;
    struct nodeInsumo* next;
    struct nodeInsumo* prev;
} ListaInsumo;

typedef struct nodeServico
{
    Servico info;
    struct nodeServico* next;
    struct nodeServico* prev;
} ListaServico;

typedef struct nodeCliente
{
    Cliente info;
    struct nodeCliente* next;
    struct nodeCliente* prev;
} ListaCliente;

typedef struct nodeUsuario{
    Usuario info;
    struct nodeUsuario* next;
    struct nodeUsuario* prev;
} ListaUsuario;

typedef struct nodeFila {
    Veiculo info;
    struct nodeFila* next;
    struct nodeFila* prev;
} Fila;

/* STRUCTS INTERFACES */
typedef struct interface{
    //windows entrada de caixa
    GtkFileFilter           *filterFile;
    GtkFileChooserDialog    *getfile;
    GtkWidget               *true_or_false;
    GtkLabel                *mensagem_tf;
    GtkWidget               *entryCaixa;
    GtkWidget               *passWord;
    GtkWidget               *passWord1;
    GtkWidget               *passWord2;
    GtkWidget               *dataFila;
    GtkWidget               *dataFilaMes;
    GtkWidget               *dataFilaAno;
    GtkWidget               *wsaida;
    GtkTreeView             *treeview_desp;
    GtkTreeModel            *treemodel_despesa;
    GtkLabel                *label_despesa;

    //window
    GtkWidget               *index;
    GtkTreeView             *treeview_index;
    GtkTreeModel            *treemodel_index;
    GtkLabel                *labelTimmer2;
    GtkTreeIter             iterVeiSmall[35];
    GtkTreeIter             iterVeiMedium[35];
    GtkTreeIter             iterVeiBig[35];


    //window timmer
    GtkWidget               *window_timmer;
    GtkImage                *image;
    GtkLabel                *labelTimmer;
    GtkLabel                *labelTimmer1;

    //window-person
    GtkTreeView             *treeview_cli;
    GtkTreeModel            *treemodel_cli;

    //window-insumos
    GtkTreeView             *treeview_ins;
    GtkTreeModel            *treemodel_ins;

    //window-user
    GtkTreeView             *treeview_usu;
    GtkTreeModel            *treemodel_usu;

    //window-services
    GtkTreeView             *treeview_ser;
    GtkTreeModel            *treemodel_ser;
    GtkTreeView             *treeview_insser;
    GtkTreeModel            *treemodel_insser;

    //window-vehicles
    GtkTreeView             *treeview_vei;
    GtkTreeModel            *treemodel_vei;
    GtkTreeView             *treeview_veicli;
    GtkTreeView             *treeview_alt_veicli;

    //assistant
    GtkAssistant            *insertVehicle;
    GtkTreeModel            *treemodel_insert_v;
    GtkTreeView             *treeview_insert_v;

    //Diagnostic
    GtkEntryBuffer         *extintor;
    GtkEntryBuffer         *oleo;
    GtkEntryBuffer         *trocaOleo;

    //Error
    GtkMessageDialog       *dialog;

    //Diagnostic
    GtkAssistant           *diagnost;


} InterfaceSystem;

typedef struct assistants{
    GtkEntryBuffer   *bufferName;
    GtkEntryBuffer   *bufferPhone;
    GtkEntryBuffer   *bufferInput;
    GtkEntryBuffer   *bufferOutput;
    GtkEntryBuffer   *bufferPlaca;
    GtkEntryBuffer   *bufferModelo;
    GtkEntryBuffer   *bufferCor;
    GtkEntryBuffer   *bufferRg;
    GtkEntryBuffer   *bufferEnd;
    GtkEntryBuffer   *bufferValor;
    GtkEntryBuffer   *bufferValorP;
    GtkEntryBuffer   *bufferValorM;
    GtkEntryBuffer   *bufferValorG;
    GtkEntryBuffer   *bufferQuant;
    GtkTextBuffer    *bufferDescri;
    GtkComboBox      *tamanho;
    GtkComboBox      *alt_tamanho;
    GtkComboBox      *tipo;
    GtkComboBox      *tipo_alt;
} AssistantSystem;

//needed for list coluns of tree
enum{
  COLUMN_USER_ID,
  COLUMN_USER_NOME,
  COLUMN_USER_TELFONE,
  COLUMN_USER_RG,
  COLUMN_USER_END,
  COLUMN_USER_DATA,
  COLUMN_USER_PAG,
  COLUMN_USER_ENT,
  COLUMN_USER_SAI,
  COLUMN_USER_EDIT,
  NUM_USER_COLUMNS
};

enum{
  COLUMN_ITEM_ID,
  COLUMN_ITEM_NOME,
  COLUMN_ITEM_TELFONE,
  COLUMN_ITEM_DATA,
  COLUMN_ITEM_XCLI,
  NUM_ITEM_COLUMNS
};

enum{
    COLUMN_INSUMOS_ID,
    COLUMN_INSUMOS_NOME,
    COLUMN_INSUMOS_VALOR,
    COLUMN_INSUMOS_QUANT,
    COLUMN_INSUMOS_DESCRI,
    COLUMN_INSUMOS_TIPO,
    NUM_INSUMOS_COLUMNS
};

enum
{
    COLUMN_INSSER_USA,
    COLUMN_INSSER_NOME,
    COLUMN_INSSER_QUANTP,
    COLUMN_INSSER_QUANTM,
    COLUMN_INSSER_QUANTG,
    COLUMN_INSSER_IDINS,
    COLUMN_INSSER_TIPO,
    NUM_INSSER_COLUMNS
};

enum
{
    COLUMN_SERV_ID,
    COLUMN_SERV_NOME,
    COLUMN_SERV_QUANTP,
    COLUMN_SERV_QUANTM,
    COLUMN_SERV_QUANTG,
    COLUMN_SERV_DESCRI,
    COLUMN_SERV_X,
    NUM_SERV_COLUMNS
};

enum{
  COLUMN_ITEM_N,
  COLUMN_ITEM_ENTRADA,
  COLUMN_ITEM_SAIDA,
  COLUMN_ITEM_VEICULO,
  COLUMN_ITEM_PROPREITARIO,
  COLUMN_ITEM_N_OS,
  COLUMN_ITEM_I,
  COLUMN_ITEM_P,
  COLUMN_ITEM_E,
  COLUMN_ITEM_VENDEDOR,
  COLUMN_ITEM_OBS,
  COLUMN_ITEM_PROCESSO,
  COLUMN_ITEM_IDVEHICLES,
  COLUMN_ITEM_PULSE,
  COLUMN_ITEM_ACTIVE,
  COLUMN_ITEM_VALOR,
  COLUMN_ITEM_GORJETA,
  COLUMN_ITEM_SUPERVISOR,
  COLUMN_ITEM_EDITAR,
  NUM_COLUMNS_VEHICLES
};

enum{
  COLUMN_VEHICLE_PLACA,
  COLUMN_VEHICLE_MODELO,
  COLUMN_VEHICLE_PROPRIETARIO,
  COLUMN_VEHICLE_ENTRADA,
  COLUMN_VEHICLE_SAIDA,
  COLUMN_VEHICLE_COR,
  COLUMN_VEHICLE_TAMANHO,
  COLUMN_VEHICLE_CLI_ID,
  NUM_VEHICLES_COLUMNS
};

enum{
  INSERT_VEHICLE_PLACA,
  INSERT_VEHICLE_MODELO,
  INSERT_VEHICLE_PROPRIETARIO,
  INSERT_VEHICLE_COR,
  INSERT_VEHICLE_TAMANHO,
  NUM_VEHICLES_INSERT
};

enum{
   COLUMN_DESP_NUMBER,
   COLUMN_DESP_DESCRI,
   COLUMN_DESP_VALOR,
   COLUMN_DESP_EDITAR,
   NUM_DESP_INSERT
};

/* Declaração De Funções System */
//time
void get_mes(char* data);
void get_year(char* data);
void data_arq(char* data);
void pega_data(char* data);
void pega_dataehora(char* data);

//files
void read_arqvs(void);
void save_arqvs(void);
//read date
ListaInsumo* readInsumos(gchar* arq_name, ListaInsumo* in);
ListaUsuario* readFuncion(gchar* arq_name, ListaUsuario* us);
ListaServico* readSevices(gchar* arq_name, ListaServico* ser);
ListaCliente* readClient(gchar *arq_name, ListaCliente* lista);
Arvore* readVehicles(gchar *arq_name, Arvore* a);
//~void readInsumos(void);
//~void readVehicles(void);

//save date
void saveInsumos(void);
void saveClient(void);
void saveServices(void);
void saveFuncion(void);
void save_veicle(Arvore *a, FILE* arq_vehicle);
void save_relatorio_dia(void);
void save_relat_ins(gchar* date_arq);

//out date
void relatorioDiaInsumos(gchar* date_arq);
void relatorioMesInsumos(gchar* date_arq);
void relatorioAnoInsumos(gchar* date_arq);

void relatorioDiaFuncionario(gchar* date_arq);
void relatorioMesFuncionario(gchar* date_arq);
void relatorioAnoFuncionario(gchar* date_arq);


//working with tree
int verifica_arv_vazia(Arvore* a);
Arvore* arv_libera (Arvore* a) ;
Arvore* inserir (Arvore *a, Veiculo v);
Arvore* buscar (Arvore *a, const char* v);
Arvore* remover(Arvore *a, Veiculo v);
void delete_veh_cli(Arvore *a, int id_clien);

//working with list
/*list insumos*/
ListaInsumo* criar_list_ins(void);
ListaInsumo* inserirInsumo(ListaInsumo* lista, Insumo elem);
void imprimir_insumos (ListaInsumo* lista);
ListaInsumo* procurar_insumos (ListaInsumo* lista, int elem);
ListaInsumo* removerInsumo (ListaInsumo *lista, int elem);
void liberarInsumos (ListaInsumo *lista);

/*list services*/
ListaServico* criar(void);
ListaServico* inserirList (ListaServico* lista, Servico elem);
void imprimir (ListaServico *lista);
void imprimir_para_frente (ListaServico *lista);
void imprime_anteriores(ListaServico *lista);
ListaServico* procurar (ListaServico* lista, int elem);
ListaServico* removerList (ListaServico *lista, int elem);
void liberar (ListaServico *lista);

/*list person*/
ListaCliente* criar_list_cli(void);
ListaCliente* inserirlistcli (ListaCliente* lista, Cliente elem);
void imprimirlistcli (ListaCliente* lista);
void imprimir_para_frentelistcli (ListaCliente* lista);
void imprime_anterioreslistcli (ListaCliente* lista);
ListaCliente* procurarlistcli  (ListaCliente* lista, int elem);
ListaCliente* removerlistcli   (ListaCliente* lista, int elem);
void liberarlistcli (ListaCliente* lista);

/*list user*/
ListaUsuario* criar_list_usu(void);
ListaUsuario* inserirlistusu (ListaUsuario* lista, Usuario elem);
void imprimirlistusu (ListaUsuario* lista);
void imprimir_para_frentelistusu (ListaUsuario* lista);
void imprime_anterioreslistusu   (ListaUsuario* lista);
ListaUsuario* procurarlistusu    (ListaUsuario* lista, int elem);
ListaUsuario* removerlistusu     (ListaUsuario* lista, int elem);
void liberarlistusu (ListaUsuario* lista);

/*Fila*/
Fila* criarFila (void);
Fila* enqueueFila (Fila *fila, Veiculo elem);
Fila* dequeueFila (Fila *fila);
Fila* procurar_Ele (char* elem);
Fila* remover_daFila(Fila *fila, char* elem);
Veiculo frontFila (Fila *fila);
int emptyFila (Fila *fila);
void imprimirFila(void);

//animação
void create_waittime();
gboolean processo_timeout (gpointer data);
gboolean timmer_timeout (gpointer data);
gint timeout_banner (gpointer data);
gboolean timeout_small_cars (gpointer data);
gboolean timeout_medium_cars (gpointer data);
gboolean timeout_big_cars (gpointer data);
gboolean load_pixbufs ();

/* Declaração De Funções CallBacks */
//caixa
G_MODULE_EXPORT void  entradadecaixa(GtkEntryBuffer *buffer);
G_MODULE_EXPORT void  inserirDespesa(GtkTreeModel *model);
G_MODULE_EXPORT void  excluirDespesa(void);
//windows
G_MODULE_EXPORT void  show_widget(GtkWidget* win);
G_MODULE_EXPORT void  close_widget(GtkWidget* win);

//inputs
G_MODULE_EXPORT void  valida_char(GtkEntryBuffer *buffer);
G_MODULE_EXPORT void  valida_char_esp(GtkEntryBuffer *buffer);
G_MODULE_EXPORT void  valida_num(GtkEntryBuffer *buffer);
G_MODULE_EXPORT void  valida_data(GtkEntryBuffer *buffer);
G_MODULE_EXPORT void  valida_valor(GtkEntryBuffer *buffer);
G_MODULE_EXPORT void  valida_descri(GtkTextBuffer *text);
G_MODULE_EXPORT void  ver_numPhone(GtkEntryBuffer *buffer);
G_MODULE_EXPORT void  valida_end(GtkEntryBuffer *buffer);
G_MODULE_EXPORT void  ver_hours(GtkEntryBuffer *buffer);
G_MODULE_EXPORT void  ver_plac(GtkEntryBuffer *buffer);
G_MODULE_EXPORT void  valida_date_a(GtkEntryBuffer* buffer);
G_MODULE_EXPORT void  valida_date_m(GtkEntryBuffer* buffer);

//assistant
G_MODULE_EXPORT void  search_vehicle(GtkEntry* entryVeh);
G_MODULE_EXPORT void  num_func(GtkEntry* entryFun);
G_MODULE_EXPORT void  applySearchInsertVehicle(GtkAssistant* assistant);
G_MODULE_EXPORT void  prepareAssistantVehicles(GtkAssistant *assistant);
G_MODULE_EXPORT void  apply_insert_vehicle(GtkAssistant *assistant);
G_MODULE_EXPORT void  changes_vehicle (GtkAssistant *assistant);
G_MODULE_EXPORT void  edit_vehicle(GtkAssistant *assistant);
G_MODULE_EXPORT void  delete_vehicle(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void  prepareAssistantInsumos(GtkAssistant *assistant);
G_MODULE_EXPORT void  applyAssistantInsumos(GtkAssistant* assistant);
G_MODULE_EXPORT void  open_assistant_alt(GtkAssistant* assistant);
G_MODULE_EXPORT void  applyAssistIns_Alt(GtkAssistant *assistant);
G_MODULE_EXPORT void  delete_insumos(void);
G_MODULE_EXPORT void  applyAssistantServices(GtkAssistant* assistant);
G_MODULE_EXPORT void  open_assistantSer_Alt(GtkAssistant* assistant);
G_MODULE_EXPORT void  applyAssistSer_Alt(GtkAssistant *assistant);
G_MODULE_EXPORT void  delete_services(void);
G_MODULE_EXPORT void  closed_assistant(GtkWidget* assistant);
G_MODULE_EXPORT void  applyAssistantClientes(GtkAssistant *assistant);
G_MODULE_EXPORT void  open_assistantCli_Alt(GtkAssistant* assistant);
G_MODULE_EXPORT void  apply_assistantCli_Alt(GtkAssistant* assistant);
G_MODULE_EXPORT void  delete_client(void);
G_MODULE_EXPORT void  applyAssistantUsuario(GtkAssistant *assistant);
G_MODULE_EXPORT void  open_assistantUsu_Alt(GtkAssistant* assistant);
G_MODULE_EXPORT void  apply_assistantUsu_Alt(GtkAssistant* assistant);
G_MODULE_EXPORT void  delete_user(void);

//tree editing
G_MODULE_EXPORT void fixed_toggled_USA(GtkCellRendererToggle *cell,gchar *path_str,gpointer data);
G_MODULE_EXPORT void fixed_toggled_X(GtkCellRendererToggle *cell,gchar *path_str,gpointer data);
G_MODULE_EXPORT void fixed_toggled_Client(GtkCellRendererToggle *cell,gchar *path_str,gpointer data);

G_MODULE_EXPORT void fixed_toggled_I(GtkCellRendererToggle *cell,gchar *path_str,gpointer data);
G_MODULE_EXPORT void fixed_toggled_E(GtkCellRendererToggle *cell,gchar *path_str,gpointer data);
G_MODULE_EXPORT void fixed_toggled_P(GtkCellRendererToggle *cell,gchar *path_str,gpointer data);
G_MODULE_EXPORT void cell_edited_Vendedor  (GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data);
G_MODULE_EXPORT void cell_edited_Obs       (GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data);
G_MODULE_EXPORT void cell_edited_Gorjeta   (GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data);
G_MODULE_EXPORT void cell_edited_Supervisor(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data);
G_MODULE_EXPORT void cell_edited_saidas(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data);
G_MODULE_EXPORT void cell_edited_Valor(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data);

G_MODULE_EXPORT void cell_edited_QtdInsP(GtkCellRendererText *cell, const gchar *path_string, const gchar  *new_text, gpointer  data);
G_MODULE_EXPORT void cell_edited_QtdInsM(GtkCellRendererText *cell, const gchar *path_string, const gchar  *new_text, gpointer  data);
G_MODULE_EXPORT void cell_edited_QtdInsG(GtkCellRendererText *cell, const gchar *path_string, const gchar  *new_text, gpointer  data);

G_MODULE_EXPORT void cell_edited_entF(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data);
G_MODULE_EXPORT void cell_edited_saiF(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data);
G_MODULE_EXPORT void cell_edited_pagF(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data);


G_MODULE_EXPORT void btn_diagnostic_vehicle(GtkWidget* win);
G_MODULE_EXPORT void done_editing(GtkEntryBuffer* entry);
G_MODULE_EXPORT void start_vehicle(void);
G_MODULE_EXPORT void zera_tempo(void);
G_MODULE_EXPORT void btn_delete_vehicletree(void);
G_MODULE_EXPORT void diagnostic(GtkWidget *widget);
G_MODULE_EXPORT void valid_password_d(GtkEntryBuffer* password);
G_MODULE_EXPORT void valid_password_m(GtkEntryBuffer* password);
G_MODULE_EXPORT void valid_password_a(GtkEntryBuffer* password);
G_MODULE_EXPORT void btn_save_tree(void);
G_MODULE_EXPORT void relatorioMes(void);
G_MODULE_EXPORT void relatorioAno(void);
G_MODULE_EXPORT void question_message (const gchar *title, const gchar *message);
G_MODULE_EXPORT void true_resp(void);
G_MODULE_EXPORT void false_resp(void);
G_MODULE_EXPORT void get_file_clientes(void);
G_MODULE_EXPORT void get_file_veiculos(void);
G_MODULE_EXPORT void get_file_servicos(void);
G_MODULE_EXPORT void get_file_insumos(void);
G_MODULE_EXPORT void salve_backup_funcionarios(void);

G_MODULE_EXPORT void salve_backup_clientes(void);
G_MODULE_EXPORT void salve_backup_veiculos(void);
G_MODULE_EXPORT void salve_backup_servicos(void);
G_MODULE_EXPORT void salve_backup_insumos(void);
G_MODULE_EXPORT void salve_backup_funcionarios(void);

G_MODULE_EXPORT void load_file(GtkWidget *widget);
G_MODULE_EXPORT void get_date_queue(GtkEntryBuffer* entry);
G_MODULE_EXPORT void get_date_mes(GtkEntryBuffer* entry);
G_MODULE_EXPORT void get_date_ano(GtkEntryBuffer* entry);

gboolean valida_date(const gchar* date);
gboolean valida_date_mes(const gchar* date_mes);
gboolean valida_date_ano(const gchar* date_ano);

void message_of_error (const gchar *message);
void error_message (const gchar *message);
void message_of_info (const gchar *message);

// get name widget
const gchar* get_name_widget(GtkWidget *widget);

gboolean init_app (InterfaceSystem *interface);
int cria_n_os(int id_nos);
int hours_int(char* saif);

/* Variáveis Globais */
//variable structs of interface
InterfaceSystem      *interface;
AssistantSystem      *iassistant;

//variable of animation
static guint timebanner = 0;
static guint timeout = 0;
static guint timeoutSmall = 0;
static guint timeoutMedium = 0;
static guint timeoutBig = 0;
static guint timmer  = 0;


/* Images */
static const char *image_names[] = {
  "images/Lavagem1.jpg",
  "images/Lavagem2.jpg",
  "images/Lavagem3.jpg",
};

#define N_IMAGES G_N_ELEMENTS (image_names)

static GdkPixbuf *images[N_IMAGES];

//variable of time
char        *stringTime;//string of time
char        *stringwaitTime;//string of time
struct tm waitinfo;

//variable of system
int num_treevehicles;
int num_vehi_aten;
int small_cars;
int medium_cars;
int big_cars;
int quant_fun;
int num_desp;
double gastcominsumos;
int insumosDia[35];
int quant_ins;
int loadFile;
noDia resultado_dia;
const gchar *date_d;
const gchar *date_a;
const gchar *date_m;


ListaInsumo          *insumos;//need tad for save insumos
ListaServico         *services;//need tad foervices
ListaCliente         *clientes;//need tad for save cr save slientes
ListaUsuario         *funcionarios;//need tad for save user
Arvore               *vehicles;//need tad for save vehicles
Arvore               *atendidos;//need tad for save vehicles tree
Fila                 *vehiclesEqueue;//need tad for save vehicles queue
