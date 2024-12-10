#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct car{
  int autonomy;
  struct car* next; //puntatore all'auto con autonomia minore
  struct car* prev; //puntatore all'auto con autonomia maggiore
} car;

typedef struct station{
  int distance; //distanza dall'inizio della strada
  struct station* next; //puntatore alla stazione dopo più vicina
  struct station* prev; //puntatore alla stazione prima più vicina
  struct station* left; //puntatore alla stazione nodo sx (inferiore)
  struct station* right; //puntatore alla stazione nodo dx (superiore)
  struct station* father; //puntatore al padre
  struct car* car_list;
} station;

typedef struct memory{
  int station_number;
  struct memory* next;
} memory;

/****************************************************************************************/

//Aggiunge le auto decrescentemente nella lista mentre la creo
void add_car(station* head, int car_autonomy){
  //head è il puntatore al nodo dell'albero in cui sto cercando la lista di auto

  car* index;
  car* new_car = (car*) malloc(sizeof(car));
  new_car -> autonomy = car_autonomy;

  if(head -> car_list == NULL){
    new_car -> next = NULL;
    new_car -> prev = NULL;
    head -> car_list = new_car;
    return;
  }

  else{
    //se c'è almeno 1 nodo nella car_list
    for(index = head -> car_list; new_car -> autonomy < index -> autonomy && index -> next != NULL; index = index -> next);
    //for serve per scorrere la lista di auto

    if(index == head -> car_list && (new_car -> autonomy > index -> autonomy || new_car -> autonomy == index -> autonomy)){
      new_car -> next = index;
      new_car -> prev = NULL;
      index -> prev = new_car;
      head -> car_list = new_car;
    }
    else if(new_car -> autonomy > index -> autonomy || new_car -> autonomy == index -> autonomy){
      new_car -> prev =  index -> prev;
      new_car -> next = index;
      index -> prev -> next = new_car;
      index -> prev = new_car;
    }
    else if(new_car -> autonomy < index -> autonomy){
      new_car -> next = index -> next;
      new_car -> prev = index;
      index -> next = new_car;
    }
  }
}

//Creazione nuovo nodo nell'albero
station* add_station(station* head, int distance, int car_numbers){
  station* new_station = (station*) malloc(sizeof(station));
  station* index;
  int i;
  int car_autonomy;

  new_station -> distance = distance;
  new_station -> car_list = NULL;

    if(head == NULL){
      new_station -> next = NULL;
      new_station -> prev = NULL;
      new_station -> left = NULL;
      new_station -> right = NULL;
      new_station -> father = NULL;
      head = new_station;

        for(i = 0; i < car_numbers; i++){
          scanf("%d", &car_autonomy);
          add_car (head, car_autonomy);
        }

      return head;
    }

    else {
      new_station -> left = NULL;
      new_station -> right = NULL;
      new_station -> next = NULL;
      new_station -> prev = NULL;

      int max = head -> distance;
      int min = head -> distance;

      if(new_station -> distance < head -> distance){
        new_station -> next = head;
      }
      else if(new_station -> distance > head -> distance){
        new_station -> prev = head;
      }
      //head non viene modificato nell'assegnamento delle next e prev iniziali

        for(index = head; (index -> right != NULL && new_station -> distance > index -> distance) || (index -> left != NULL && new_station -> distance < index -> distance) ;){
            if(new_station -> distance > index -> distance){
              index = index -> right;
            }
            else if(new_station -> distance < index -> distance){
              index = index -> left;
            }
          }

          if(index -> right == NULL && new_station -> distance > index -> distance){
            index -> right = new_station;
            new_station -> father = index;

            new_station -> prev = index;
            new_station -> next = index -> next;
            if(new_station -> next != NULL && new_station -> next -> prev != NULL)
              new_station -> next -> prev = new_station;
            index -> next = new_station;
            //codice aggiunto per linking delle prev e next^

              for(i = 0; i < car_numbers; i++){
                scanf("%d", &car_autonomy);
                add_car (new_station, car_autonomy);
              }
          }

          else if(index -> left == NULL && new_station -> distance < index -> distance){
            index -> left = new_station;
            new_station -> father = index;

            new_station -> next = index;
            new_station -> prev = index -> prev;
              if(new_station -> prev != NULL && new_station -> prev -> next != NULL)
                new_station -> prev -> next = new_station;
              index -> prev = new_station;
            //codice aggiunto per linking delle prev e next^

              for(i = 0; i < car_numbers; i++){
                scanf("%d", &car_autonomy);
                add_car (new_station, car_autonomy);
              }
          }

          return head;
    }
  }

/****************************************************************************************/

//Controlla che nell'albero non ci sia già una stazione con lo stesso valore
int valid_node(station* head, int value){
  if(head == NULL)
    return 1;
  if(value < 0){
    printf("non aggiunta\n");
      return 0;
    }

  station* index;
  for(index = head; index != NULL;){
    if(value == index -> distance){
      printf("non aggiunta\n");
      return 0;
    }
    if(value > index -> distance)
      index = index -> right;
    else if(value < index -> distance)
      index = index -> left;
  }
  return 1;
}

//Vista in ordine LRR dell'albero
void tree_view(station* head){
  if(head == NULL){
    return;
  }
  tree_view(head -> left);
  printf("Stazione %d\n", head -> distance);
  tree_view(head -> right);
}


//Aggiunge 1 auto alla stazione già esistente indicata
void add_single_car(station* head, int distance, int autonomy){
  if(head == NULL){
    printf("non aggiunta\n");
    return;
  }

  station* index;
  for(index = head; index != NULL;){


    if(distance > index -> distance)
      index = index -> right;
    else if(distance < index -> distance)
      index = index -> left;


          //entro nella if se ho trovato la stazione con la distanza corretta
          if(index != NULL && index -> distance == distance){
            car* car_index;
            car* new_car = (car*) malloc(sizeof(car));
            new_car -> autonomy = autonomy;
            printf("aggiunta\n");

            //caso in cui la stazione non abbia auto
            if(index -> car_list == NULL){
              new_car -> next = NULL;
              new_car -> prev = NULL;
              index -> car_list = new_car;
              return;
            }

            //caso in cui la stazione ha auto ma devo tenere la lista in ordine decrescente, quindi scorro
            for(car_index = index -> car_list; (new_car -> autonomy < car_index -> autonomy) && car_index -> next != NULL; car_index = car_index -> next);

            //caso head
              if(car_index == index -> car_list && (new_car -> autonomy > car_index -> autonomy || new_car -> autonomy == car_index -> autonomy)){
                new_car -> next = car_index;
                new_car -> prev = NULL;
                car_index -> prev = new_car;
                index -> car_list = new_car;
                return;
              }
              else if(new_car -> autonomy > car_index -> autonomy || new_car -> autonomy == car_index -> autonomy){
                new_car -> next = car_index;
                new_car -> prev = car_index -> prev;
                new_car -> prev -> next = new_car;
                car_index -> prev = new_car;
                return;
              }
              else{
                car_index -> next = new_car;
                new_car -> prev = car_index;
                new_car -> next = NULL;
                return;
              }
          }

  }

  printf("non aggiunta\n");
}

//Distrugge tutte le auto presenti in una stazione, serve quando si distrugge un'intera stazione
car* destroy_all_cars(car* car_list){
  car* index;
  car* destroy;
  for(index = car_list; index!= NULL;){
    destroy = index;
    index = index -> next;
    free(destroy);
  }

  return NULL;
}


//Distrugge 1 stazione dall'albero
station* destroy_station(station* head, int distance){

  station* index;
  for(index = head; index != NULL;){
    if(index -> distance > distance)
        index = index -> left;
    else if(index -> distance < distance)
        index = index -> right;

    if(index != NULL && index -> distance == distance)
      break;

  }

  if(index == NULL){
    printf("non demolita\n");
    return head;
  }

  printf("demolita\n");

//Nodo da distruggere è ai rami in fondo dell'albero
  if(index -> right == NULL && index -> left == NULL){
    index -> car_list = destroy_all_cars(index -> car_list);

    if(index -> prev != NULL)
      index -> prev -> next = index -> next;

    if(index -> next != NULL)
      index -> next -> prev = index -> prev;

    if(index -> father != NULL){
    //Unico caso in cui father è NULL è se ho la testa dell'albero da eliminare ed è l'unica stazione nell'albero
      if(index -> father -> right == index)
        index -> father -> right = NULL;
      else
        index -> father -> left = NULL;
    }
    else
      head = NULL;

    free(index);
    return head;
  }

//Nodo da distruggere ha nodi alla destra ma è vuota a sinistra
  if(index -> left == NULL){
    index -> car_list = destroy_all_cars(index -> car_list);

    if(index -> prev != NULL)
      index -> prev -> next = index -> next;

    if(index -> next != NULL)
      index -> next -> prev = index -> prev;

    if(index -> father != NULL){
    //Unico caso in cui father è NULL è se ho la testa dell'albero da eliminare ed ha nodi a destra
      if(index -> father -> right == index){
        index -> father -> right = index -> right;
        index -> right -> father = index -> father;
      }
      else{
        index -> father -> left = index -> right;
        index -> right -> father = index -> father;
      }
    }
    else{
      head = index -> right;
      head -> father = NULL;
    }
    free(index);
    return head;
  }

//Nodo da distruggere ha nodi alla sinistra ma è vuota a destra
  if(index -> right == NULL){
    index -> car_list = destroy_all_cars(index -> car_list);

    if(index -> prev != NULL)
      index -> prev -> next = index -> next;

    if(index -> next != NULL)
      index -> next -> prev = index -> prev;

    if(index -> father != NULL){
    //Unico caso in cui father è NULL è se ho la testa dell'albero da eliminare ed ha nodi a sinistra
      if(index -> father -> right == index){
        index -> father -> right = index -> left;
        index -> left -> father = index -> father;
      }
      else{
        index -> father -> left = index -> left;
        index -> left -> father = index -> father;
      }
    }
    else{
      head = index -> left;
      head -> father = NULL;
    }
    free(index);
    return head;
  }

//Nodo da distruggere ha entrambi nodi a destra e a sinistra!
  if(index -> right != NULL && index -> left != NULL){
    station* replacement;
    index -> car_list = destroy_all_cars(index -> car_list);

      replacement = index -> next;
      index -> distance = replacement -> distance;
      index -> car_list = replacement -> car_list;

        if(replacement -> father -> right == replacement){
          replacement -> father -> right = replacement -> right;
          if(replacement -> right != NULL)
            replacement -> right -> father = replacement -> father;
        }
        else if(replacement -> father -> left == replacement){
          replacement -> father -> left = replacement -> right;
          if(replacement -> right != NULL)
            replacement -> right -> father = replacement -> father;
        }
      if(replacement -> prev != NULL)
        replacement -> prev -> next = replacement -> next;
      if(replacement ->next != NULL)
      replacement -> next -> prev = replacement -> prev;

    free(replacement);
    return head;
  }
}

//Distrugge una singola auto da una stazione
void destroy_single_car(station* head, int distance, int autonomy){
  station* index;
  for(index = head; index != NULL;){
    if(distance > index -> distance)
      index = index -> right;
    else if(distance < index -> distance)
      index = index -> left;
    if(index != NULL && index -> distance == distance)
        break;
  }

  if(index == NULL){
    printf("non rottamata\n");
    return;
  }

car* car_index;
for(car_index = index -> car_list; car_index != NULL && car_index -> autonomy != autonomy; car_index = car_index -> next);

if(car_index == NULL){
  printf("non rottamata\n");
  return;
}

printf("rottamata\n");

if(car_index == index -> car_list){
    index -> car_list = car_index -> next;
    if(car_index -> next != NULL)
      car_index -> next -> prev = NULL;
      free(car_index);
      return;
  }

else{
    car_index -> prev -> next = car_index -> next;
    if(car_index -> next != NULL)
      car_index -> next -> prev = car_index -> prev;
      free(car_index);
      return;
  }
}

//Pianifica percorso da sx verso dx
void route_planner_sx(station* start, station* end){
  station* index_out;
  station* index_in;
  station* pivot;
  memory* head = NULL;
  memory* memory_index;
  memory* delete_index;
  int pivot_range;
  int check_one;
  int check_two;
  int min_distance = end -> distance;

  for(index_out = end; index_out != start;){
    check_two = 0;

    for(index_in = index_out -> prev; index_in != start -> prev;){
      check_one = 0;
      pivot_range = 0;

      if(index_in -> car_list != NULL){
        check_one = 1;
        pivot_range = index_in -> distance + index_in -> car_list -> autonomy;
      }

      if(check_one && (pivot_range > index_out -> distance || pivot_range == index_out -> distance)){
        check_two = 1;
        if(index_in -> distance < min_distance){
          pivot = index_in;
          min_distance = pivot -> distance;
        }
      }
      index_in = index_in -> prev;
    }

    if(check_two){
      memory* new_memory = (memory*) malloc(sizeof(memory));
      new_memory -> station_number = min_distance;
      if(head == NULL){
        head = new_memory;
        head -> next = NULL;
      }
      else{
        new_memory -> next = head;
        head = new_memory;
      }
    }
    else{
      printf("nessun percorso\n");
      for(memory_index = head; memory_index != NULL;){
        delete_index = memory_index;
        memory_index = memory_index -> next;
        free(delete_index);
      }
      return;
    }
    index_out = pivot;
  }

  for(memory_index = head; memory_index!= NULL;){
    delete_index = memory_index;
    printf("%d ", memory_index -> station_number);
    memory_index = memory_index -> next;
    free(delete_index);
  }
  printf("%d\n", end -> distance);
  return;
}

//Pianifica percorso da dx verso sx
void route_planner_dx(station* start, station* end, station* true_end){
  station* index_out;
  station* index_in;
  station* pivot;
  station* special_index;
  int special_distance;
  int special_station_number;
  int pivot_range;
  int min_distance;

  if(start == end){
    printf("%d ", start -> distance);
    return;
  }

for(index_out = start; index_out != end;){
//printf("Index_out %d\n", index_out -> distance);
  if(index_out -> car_list != NULL){
    if(index_out -> distance - index_out -> car_list -> autonomy < end -> distance || index_out -> distance - index_out -> car_list -> autonomy == end -> distance){
      break;
    }
    min_distance = index_out -> distance - index_out -> car_list -> autonomy;
    for(index_in = index_out; index_in -> distance > (index_out -> distance - index_out -> car_list -> autonomy) || index_in -> distance == (index_out -> distance - index_out -> car_list -> autonomy);){
      if(index_in -> car_list != NULL && index_in -> car_list -> autonomy != 0){
        pivot_range = index_in -> distance - index_in -> car_list -> autonomy;

        if(pivot_range < min_distance || pivot_range == min_distance){
          pivot = index_in;
          min_distance = pivot_range;
          special_distance = min_distance;
        }

      }

      index_in = index_in -> prev;
    }
    if(pivot == index_out){
      printf("nessun percorso\n");
      return;
    }
  }
  else{
    printf("nessun percorso\n");
    return;
  }

special_station_number = -2147483648;
//se ci sono problemi, bisogna cambiare questo valore e cambiare algoritmo di verifica
//qui ho aggiunto una end che fa la special_index => end -> distance
for(special_index = pivot; (special_index != NULL) && (special_index -> distance > end -> distance || special_index -> distance == end -> distance) && ((special_index -> distance > pivot -> distance - pivot -> car_list -> autonomy) || (special_index -> distance == pivot -> distance - pivot -> car_list -> autonomy));){
  if(special_index -> car_list != NULL && special_index -> car_list -> autonomy != 0){
      if((special_index -> distance - special_index -> car_list -> autonomy < end -> distance || special_index -> distance - special_index -> car_list -> autonomy == end -> distance)){
        special_station_number = special_index -> distance;
        special_distance = special_index -> distance;
      }

      if(special_index -> distance - special_index -> car_list -> autonomy < special_distance || (special_index -> distance - special_index -> car_list -> autonomy == special_distance && special_index -> distance < pivot -> distance)){
      special_distance = special_index -> distance - special_index -> car_list -> autonomy;
      special_station_number = special_index -> distance;
      }
    }
  special_index = special_index -> prev;
}

for(special_index = index_out;((special_index -> distance > index_out -> distance - index_out -> car_list -> autonomy) || (special_index -> distance == index_out -> distance - index_out -> car_list -> autonomy));){
  if(special_index -> car_list != NULL && special_index -> car_list -> autonomy != 0){
    if(special_index -> distance - special_index -> car_list -> autonomy < special_station_number || special_index -> distance - special_index -> car_list -> autonomy == special_station_number){
        pivot = special_index;
      }
    }
  special_index = special_index -> prev;
  }

index_out = pivot;
}
//fine della for index_out
//codice aggiunto V
route_planner_dx(start, index_out, true_end);
if(end == true_end){
  printf("%d\n", end -> distance);
  return;
}
printf("%d ", end -> distance);
  return;
}

void route_validation(station* head, int start, int end){
  int check_one = 0;
  int check_two = 0;
  station* index;

  station* starting_point;
  station* ending_point;

  if(end == start || start < 0 || end < 0){
    printf("nessun percorso\n");
    return;
  }

  if(end > start){
    //primo algoritmo se il senso di marcia è da sinistra verso destra
    for(index = head; index != NULL;){
      if(start > index -> distance)
          index = index -> right;
      else if(start < index -> distance)
          index = index -> left;

      if(index != NULL && index -> distance == start){
        starting_point = index;
        check_one = 1;
        break;
      }
    }

    if(check_one){
      for(index = head; index != NULL;){
        if(end > index -> distance)
            index = index -> right;
        else if(end < index -> distance)
            index = index -> left;

        if(index != NULL && index -> distance == end){
          ending_point = index;
          check_two = 1;
          break;
        }
      }
    }

    if(check_one == 1 && check_two == 1){
      //se le stazioni a cui vado a pianificare il percorso esistono, posso proseguire
      route_planner_sx(starting_point, ending_point);
      return;
    }
    else{
      printf("nessun percorso\n");
      return;
    }
  }

  else if(start > end){
    //secondo algoritmo se il senso di marcia è da destra verso sinistra
    for(index = head; index != NULL;){
      if(start > index -> distance)
          index = index -> right;
      else if(start < index -> distance)
          index = index -> left;

      if(index != NULL && index -> distance == start){
        starting_point = index;
        check_one = 1;
        break;
      }
    }

    if(check_one){
      for(index = head; index != NULL;){
        if(end > index -> distance)
            index = index -> right;
        else if(end < index -> distance)
            index = index -> left;

        if(index != NULL && index -> distance == end){
          ending_point = index;
          check_two = 1;
          break;
        }
      }
    }

    if(check_one == 1 && check_two == 1){
      //se le stazioni a cui vado a pianificare il percorso esistono, posso proseguire
      route_planner_dx(starting_point, ending_point, ending_point);
      return;
    }
    else{
      printf("nessun percorso\n");
      return;
    }
  }
}

int main(){
  char command[20]; //commando di input
  int distance; //distanza della stazione dal punto inizio
  int car_numbers; //numeri di auto in una stazione
  int autonomy; //autonomia dell'auto
  station* head = NULL;
  car* car_index;
  int i = 1; //selettore per uscire dal while
  int dumb;
  int start, end;

  while(i){
    int gtfo = scanf("%s", command); //scelta del comando
    if (gtfo == EOF) {
           return 0;
         }
      switch(command[0]){

        case 'a':
        //aggiungi-stazione 100 2 10 20
          if(command[9]=='s'){
            scanf("%d", &distance);
            scanf("%d", &car_numbers);


            if(valid_node(head, distance)){
              printf("aggiunta\n");
              head = add_station(head, distance, car_numbers);
              }
            else{
              for(i = 0; i < car_numbers; i++)
                scanf("%d", &dumb);
            }
            break;
            }

            if(command[9]=='a'){
        //aggiungi-auto 100 30
              scanf("%d", &distance);
              scanf("%d", &autonomy);
              add_single_car(head, distance, autonomy);
              break;
            }

            else if(command[9] != 's' && command[9] != 'a'){
              printf("comando non valido\n");
              break;
            }

        case 'p':
        //pianifica-percorso 100 20
        scanf("%d", &start);
        scanf("%d", &end);
        route_validation(head, start, end);
          break;

        case 'd':
        //demolisci-stazione 100
            scanf("%d", &distance);
            head = destroy_station(head, distance);
          break;

        case 'r':
        //rottama-auto 100 20
            scanf("%d", &distance);
            scanf("%d", &autonomy);
            destroy_single_car(head, distance, autonomy);
          break;

          case 'o' :
          //stampa per i valori dell'albero
          printf("\nAhoy LRR view\n");
          tree_view(head);
          if(head != NULL){
          printf("\nAhoy next view\n");
          station* index;
          for(index = head; index -> prev != NULL; index = index -> prev);
            while(index != NULL){
              printf("Distance %d\n", index -> distance);
              for(car_index = index -> car_list; car_index != NULL; car_index = car_index -> next)
                printf("Auto con autonomia %d\n", car_index -> autonomy);
              index = index -> next;
            }
            printf("\nAhoy prev view\n");
            for(index = head; index -> next != NULL; index = index -> next);
              while(index != NULL){
                printf("Distance %d\n", index -> distance);
                for(car_index = index -> car_list; car_index != NULL; car_index = car_index -> next)
                  printf("Auto con autonomia %d\n", car_index -> autonomy);
                index = index -> prev;
              }
            }
            break;
            default:
            printf("comando non valido\n");
            break;
      }
    }

}
