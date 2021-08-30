#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LISTLEN 8

typedef struct node {
  char name[5];
  unsigned short int value;
  int hasvalue;
  struct node *next;
} Node;

typedef Node* HeadNode;

typedef struct line {
  char *value;
  int parsed;
  struct line *next;
} Line;

typedef Line* HeadLine;

typedef struct qline {
  Line *head;
  Line *end;
  Line *pstart; // start of non-parsed lines
} QuLine;

void LineAdd(QuLine *pql,char* str);
void LinePrint(QuLine *pql);

void NodeAdd(HeadNode *head,char *name);
Node* NodeExist(HeadNode head,char *name);
void NodePrint(HeadNode head);
void NodeSetValue(Node *el,unsigned short int val);

int IsNumber(char* str);

int main() {
  int i;
  int val1,val2;
  char tmpstr[100];
  char *pch[5];

  HeadNode nhead = NULL;
  QuLine *pql;

  FILE *fp;

  pql = (QuLine *)malloc(sizeof(QuLine));
  pql->head = NULL;
  pql->pstart = NULL;
  pql->end = NULL;

  fp = fopen("day7.dat","r");
  while(fgets(tmpstr,100,fp) != NULL) {
    tmpstr[strlen(tmpstr)-1] = '\0';
    LineAdd(pql,tmpstr);
  }
  fclose(fp);

//  LinePrint(pql);

  Line *tmp = NULL;
  int finished;
  int npass = 0;
  do {
    npass++;
    finished = 1;
    tmp = pql->head;
    while(tmp != NULL) {
      if(tmp->parsed == 0) {
        finished = 0;

        strcpy(tmpstr,tmp->value);
//        printf("%s\n",tmpstr);
        i = 0;
        pch[i] = strtok(tmpstr," ->");
        while(pch[i] != NULL) {
//          printf("%d %s\n",i,pch[i]);
          i++;
          pch[i] = strtok(NULL," ->");
        }
//        printf("%d %s %p\n",i,pch[i-1],NodeExist(nhead,pch[i-1]));
        if(NodeExist(nhead,pch[i-1]) == NULL)
          NodeAdd(&nhead,pch[i-1]); 

        if(i == 2 && IsNumber(pch[0])) { // simple case of assignment
          NodeSetValue(NodeExist(nhead,pch[1]),(unsigned short int)strtol(pch[0],NULL,10));
          tmp->parsed = 1;
        } // i == 2
        else if(i == 2 && ! IsNumber(pch[0])) {
          if(NodeExist(nhead,pch[0]) == NULL)
            NodeAdd(&nhead,pch[0]);
          else if(NodeExist(nhead,pch[0])->hasvalue == 1) {
            NodeSetValue(NodeExist(nhead,pch[1]),NodeExist(nhead,pch[0])->value); 
            tmp->parsed = 1;
          }
        } // i == 2

        if(i == 3 && strcmp(pch[0],"NOT") == 0) { // NOT case
          if(IsNumber(pch[1])) {
            NodeSetValue(NodeExist(nhead,pch[2]),~(unsigned short int)strtol(pch[1],NULL,10));
            tmp->parsed = 1;
          }
          else {
            if(NodeExist(nhead,pch[1]) == NULL)
              NodeAdd(&nhead,pch[1]);
            else if(NodeExist(nhead,pch[1])->hasvalue == 1){
              NodeSetValue(NodeExist(nhead,pch[2]),~(NodeExist(nhead,pch[1])->value)); 
              tmp->parsed = 1;
            }
          }
        } // i == 3

        if(i == 4) {
          if(! IsNumber(pch[0]) && NodeExist(nhead,pch[0]) == NULL)
            NodeAdd(&nhead,pch[0]);
          if(! IsNumber(pch[2]) && NodeExist(nhead,pch[2]) == NULL)
            NodeAdd(&nhead,pch[2]);

          if(IsNumber(pch[0]))
            val1 = strtol(pch[0],NULL,10);
          else if(NodeExist(nhead,pch[0])->hasvalue == 1)
            val1 = NodeExist(nhead,pch[0])->value;

          if(IsNumber(pch[2]))
            val2 = strtol(pch[2],NULL,10);
          else if(NodeExist(nhead,pch[2])->hasvalue == 1)
            val2 = NodeExist(nhead,pch[2])->value;

          if((IsNumber(pch[0]) || NodeExist(nhead,pch[0])->hasvalue == 1) && (IsNumber(pch[2]) || NodeExist(nhead,pch[2])->hasvalue == 1)) {
            if(strcmp(pch[1],"OR") == 0)
              NodeSetValue(NodeExist(nhead,pch[3]),val1 | val2);
            else if(strcmp(pch[1],"AND") == 0)
              NodeSetValue(NodeExist(nhead,pch[3]),val1 & val2);
            else if(strcmp(pch[1],"LSHIFT") == 0)
              NodeSetValue(NodeExist(nhead,pch[3]),val1 << val2);
            else if(strcmp(pch[1],"RSHIFT") == 0)
              NodeSetValue(NodeExist(nhead,pch[3]),val1 >> val2);
            tmp->parsed = 1;
          }
        } // i == 4
      }

      tmp = tmp->next;
    }
  } while(! finished);

  NodePrint(nhead);

  printf("Number of passes: %d\n",npass);

  return 0;
}

void NodeSetValue(Node *el,unsigned short int val) {
  el->value = val;
  el->hasvalue = 1;

  return;
}

int IsNumber(char* str) {
  if(str[0] >= 48 && str[0] <= 57)
    return 1;
  else 
    return 0;
}

void NodeAdd(HeadNode *head, char* name) {
  Node *tmp = (Node *)malloc(sizeof(Node));
  strcpy(tmp->name,name);
  tmp->value = 0;
  tmp->hasvalue = 0;

  if(*head == NULL) {
    *head = tmp;
    tmp->next = NULL;
  }
  else {
    tmp->next = *head;
    *head = tmp;
  }

  return;
}

Node* NodeExist(HeadNode head, char* name) {
  if(head == NULL)
    return NULL;

  Node *tmp = head;
  while(tmp != NULL) {
    if(strcmp(tmp->name,name) == 0)
      return tmp;
    tmp = tmp->next;
  }

  return NULL;
}

void NodePrint(HeadNode head) {
  Node *tmp = head;

  printf("Node Print:\n");
  while(tmp != NULL) {
    printf("%4s %4d %4d\n",tmp->name,tmp->hasvalue,tmp->value);
    tmp = tmp->next;
  }

  return;
}

void LineAdd(QuLine *pql, char *str) {
  Line *tmp;

  tmp = (Line *)malloc(sizeof(Line));
  tmp->value = (char *)malloc((strlen(str)+1)*sizeof(char));
  strcpy(tmp->value,str);
  tmp->parsed = 0;
  tmp->next = NULL;

  if(pql->head == NULL) {
    pql->head = tmp;
    pql->pstart = tmp;
    pql->end = tmp;
  }
  else {
    pql->end->next = tmp;
    pql->end = tmp;
  }

  return;
}

void LinePrint(QuLine *pql) {
  Line *tmp = pql->head;

  while(tmp != NULL) {
    printf("%d : %s\n",tmp->parsed,tmp->value);
    tmp = tmp->next;
  }

  return;
}